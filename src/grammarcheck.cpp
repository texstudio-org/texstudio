#include "grammarcheck.h"
#include "smallUsefulFunctions.h"
#include "latexparser/latexreader.h"
#include "QThread"
#if QT_VERSION >= 0x050000
#include <QJsonDocument>
#include <QJsonArray>
#endif
GrammarError::GrammarError(): offset(0), length(0), error(GET_UNKNOWN) {}
GrammarError::GrammarError(int offset, int length, const GrammarErrorType &error, const QString &message): offset(offset), length(length), error(error), message(message) {}
GrammarError::GrammarError(int offset, int length, const GrammarErrorType &error, const QString &message, const QStringList &corrections): offset(offset), length(length), error(error), message(message), corrections(corrections) {}
GrammarError::GrammarError(int offset, int length, const GrammarError &other): offset(offset), length(length), error(other.error), message(other.message), corrections(other.corrections) {}

GrammarCheck::GrammarCheck(QObject *parent) :
    QObject(parent), ltstatus(LTS_Unknown), backend(nullptr), ticket(0), pendingProcessing(false), shuttingDown(false)
{
	latexParser = new LatexParser();
}
/*!
 * \brief GrammarCheck::~GrammarCheck
 * Destructor
 */
GrammarCheck::~GrammarCheck()
{
	if (latexParser) delete latexParser;
}
/*!
 * \brief GrammarCheck::init
 * initialize grammar checker
 * \param lp reference to latex parser
 * \param config reference to config
 */
void GrammarCheck::init(const LatexParser &lp, const GrammarCheckerConfig &config)
{
	*latexParser = lp;
	this->config = config;

    if (!backend) {
#if QT_VERSION >= 0x050000
            backend = new GrammarCheckLanguageToolJSON(this);
#else
            backend = new GrammarCheckLanguageToolSOAP(this);
#endif
            connect(backend, SIGNAL(checked(uint, int, QList<GrammarError>)), this, SLOT(backendChecked(uint, int, QList<GrammarError>)));
            connect(backend, SIGNAL(errorMessage(QString)),this,SIGNAL(errorMessage(QString)));
            connect(backend, SIGNAL(languageToolStatusChanged()),this,SLOT(updateLTStatus()));
    }
	backend->init(config);

	if (floatingEnvs.isEmpty())
		floatingEnvs << "figure" << "table" << "SCfigure" << "wrapfigure" << "subfigure" << "floatbox";

	// this is a heuristic, some LanguageTool languages have the format de-DE, others just it (instead of it-IT)
	// this list contains all two-character languages that do not have a four-character equivalent.
	languageMapping.insert("ca-CA", "ca");
	languageMapping.insert("en-EN", "en");
	languageMapping.insert("es-ES", "es");
	languageMapping.insert("fa-FA", "fa");
	languageMapping.insert("fr-FR", "fr");
	languageMapping.insert("it-IT", "it");
	languageMapping.insert("nl-NL", "nl");
	languageMapping.insert("sv-SV", "sv");
}

QString GrammarCheck::serverUrl() {
	return backend->url();
}

/*!
 * \brief readWordList
 * Read bad words/stop words from file
 * \param file
 * \return word list as set
 */
QSet<QString> readWordList(const QString &file)
{
	QFile f(file);
	if (!f.open(QFile::ReadOnly)) return QSet<QString>();
	QSet<QString> res;
	foreach (const QByteArray &ba, f.readAll().split('\n')) {
		QByteArray bas = ba.simplified();
		if (bas.startsWith('#')) continue;
		res << QString::fromUtf8(bas);
	}
	return res;
}

struct TokenizedBlock {
	QStringList words;
	QList<int> indices, endindices, lines;
	//int firstLineNr;
};

struct CheckRequest {
	bool pending;
	QString language;
	void *doc;
	QList<LineInfo> inlines;
	int firstLineNr;
	uint ticket;
	int handledBlocks;
	CheckRequest(const QString &language, const void *doc, const QList<LineInfo> inlines, const int firstLineNr, const int ticket):
		pending(true), language(language), doc(const_cast<void *>(doc)), inlines(inlines), firstLineNr(firstLineNr), ticket(ticket), handledBlocks(0) {}

	QList<int> linesToSkip;

	QList<TokenizedBlock> blocks;
	QVector<QList<GrammarError> > errors;
};

void GrammarCheck::check(const QString &language, const void *doc, const QList<LineInfo> &inlines, int firstLineNr)
{
	if (shuttingDown || inlines.isEmpty()) return;

	ticket++;
	for (int i = 0; i < inlines.size(); i++) {
		TicketHash::iterator it = tickets.find(inlines[i].line);
		if (it == tickets.end()) tickets[inlines[i].line] = QPair<uint, int> (ticket, 1);
		else {
			it.value().first = ticket;
			it.value().second++;
		}
	}

	//qDebug()<<"CHECK:"<<inlines.first().text;

	requests << CheckRequest(languageFromHunspellToLanguageTool(language), doc, inlines, firstLineNr, ticket);

	//Delay processing, because there might be more requests for the same line in the event queue and only the last one needs to be checked
	if (!pendingProcessing) {
		pendingProcessing = true;
		QTimer::singleShot(50, this, SLOT(processLoop()));
	}
}

void GrammarCheck::shutdown()
{
	if (backend) backend->shutdown();
	shuttingDown = true;
	deleteLater();
}

void GrammarCheck::processLoop()
{
	if (shuttingDown) return;
	for (int i = requests.size() - 1; i >= 0; i--)
		if (requests[i].pending) {
			requests[i].pending = false;
			process(i);
		}
	pendingProcessing = false;
}

const QString uselessPunctation = "!:?,.;-"; //useful: \"(
const QString punctuationNotPreceededBySpace = "!:?,.;)\u00A0";  // \u00A0 is non-breaking space: assuming it is not surrounded by natural space (wouldn't make sense)
const QString punctuationNotFollowedBySpace = "(\"\u00A0";


/* Determine if words[i] should be preceeded by a space in the context of words.
 * If not continue.
 * If i > words.length() break;
 * This does always increase i by one. (Note: the checks below are written based on i++)
 * This is used in loops for selectively joining words with spaces. */
#define CHECK_FOR_SPACE_AND_CONTINUE_LOOP(i, words) i++; \
  if (i >= words.length()) break; \
  if (words[i].length() == 1 && punctuationNotPreceededBySpace.contains(words[i][0])) continue; \
  if (words[i-1].length() == 1 && punctuationNotFollowedBySpace.contains(words[i-1][0])) continue; \
  if (words[i-1].length() == 2 && words[i-1][1] == '.' && words[i].length() == 2 && words[i][1] == '.') continue; /* abbeviations like "e.g." */ \

void GrammarCheck::process(int reqId)
{
	REQUIRE(latexParser);
	REQUIRE(!requests.isEmpty());

	CheckRequest &cr = requests[reqId];

	LIST_RESERVE(cr.linesToSkip, cr.inlines.size());
	if (cr.ticket != ticket) {
		//processing an old request
		for (int i = 0; i < cr.inlines.size(); i++) {
			TicketHash::iterator it = tickets.find(cr.inlines[i].line);
			Q_ASSERT(it != tickets.end());
			if (it == tickets.end()) continue;
			if (it.value().first != cr.ticket) {
				it.value().second--;
				Q_ASSERT(it.value().second >= 0);
				cr.linesToSkip << i;
				if (it.value().second <= 0) tickets.erase(it);
			}
		}
		if (cr.linesToSkip.size() == cr.inlines.size())  {
			requests.removeAt(reqId);
			return;
		}
	}

	//gather words
	int nonTextIndex = 0;
	QList<TokenizedBlock> blocks;
	blocks << TokenizedBlock();
	//blocks.last().firstLineNr = cr.firstLineNr;
	int floatingBlocks = 0;
	int firstLineNr = cr.firstLineNr;
	for (int l = 0; l < cr.inlines.size(); l++, firstLineNr++) {
		TokenizedBlock &tb = blocks.last();
		LatexReader lr(*latexParser, cr.inlines[l].text);
		int type;
		while ((type = lr.nextWord(false))) {
			if (type == LatexReader::NW_ENVIRONMENT) {
				if (lr.word == "figure") { //config.floatingEnvs.contains(lr.word)) {
					if (lr.lastCommand == "\\begin") {
						floatingBlocks ++;
					} else if (lr.lastCommand == "\\end") {
						floatingBlocks --;
					}
				}
				continue;
			};

			if (type == LatexReader::NW_COMMENT) break;
			if (type != LatexReader::NW_TEXT && type != LatexReader::NW_PUNCTATION) {
				//reference, label, citation
				tb.words << QString("keyxyz%1").arg(nonTextIndex++);
				tb.indices << lr.wordStartIndex;
				tb.endindices << lr.index;
				tb.lines << l;
				continue;
			}

			if (latexParser->structureCommandLevel(lr.lastCommand) >= 0) {
				//don't check captions
				QStringList temp;
				QList<int> starts;
				LatexParser::resolveCommandOptions(lr.line, lr.wordStartIndex - 1, temp, &starts);
				for (int j = 0; j < starts.count() && j < 2; j++) {
					lr.index = starts.at(j) + temp.at(j).length() - 1;
					if (temp.at(j).startsWith("{")) break;
				}
				tb.words << ".";
				tb.indices << lr.wordStartIndex;
				tb.endindices << 1;
				tb.lines << l;
				continue;
			}


			if (type == LatexReader::NW_TEXT) tb.words << lr.word;
			else if (type == LatexReader::NW_PUNCTATION) {
				if ((lr.word == "-") && !tb.words.isEmpty()) {
					//- can either mean a word-separator or a sentence -- separator
					// => if no space, join the words at both sides of the - (this could be easier handled in nextToken, but spell checking usually doesn't support - within words)
					if (lr.wordStartIndex == tb.endindices.last()) {
                        tb.words.last() += lr.word;
						tb.endindices.last()++;

						int tempIndex = lr.index;
						int type = lr.nextWord(false);
						if (type == LatexReader::NW_COMMENT) break;
						if (tempIndex != lr.wordStartIndex) {
							lr.index = tempIndex;
							continue;
						}
						tb.words.last() += lr.word;
						tb.endindices.last() = lr.index;
						continue;
					}
				} else if (lr.word == "\"") {
					lr.word = "'";  // replace " by ' because " is encoded as &quot; and screws up the (old) LT position calculation
				} else if (lr.word == "~") {
					lr.word =  "\u00A0";  // rewrite LaTeX non-breaking space to unicode non-braking space
				} else if (punctuationNotPreceededBySpace.contains(lr.word) && !tb.words.isEmpty() && tb.words.last() == "\u00A0") {
					// rewrite non-breaking space followed by punctuation to punctuation only. e.g. "figure~\ref{abc}." -> "figure."
					// \ref{} is dropped by the reader and an erronous would leave "figure\u00A0."
					// As a heuristic no space before punctuation takes precedence over non-breaking space.
					// This is the best we can do for now. A complete handling of all cases is only possible with a full tokenization.
					tb.words.last() = lr.word;
					tb.endindices.last() = lr.index;
					continue;
				}
				tb.words << lr.word;
			}

			tb.indices << lr.wordStartIndex;
			tb.endindices << lr.index;
			tb.lines << l;

		}


		while (floatingBlocks > blocks.size() - 1) blocks << TokenizedBlock();
		while (floatingBlocks >= 0 && floatingBlocks < blocks.size() - 1)
			cr.blocks << blocks.takeLast();
	}
	while (blocks.size()) cr.blocks << blocks.takeLast();


	for (int b = 0; b < cr.blocks.size(); b++) {
		TokenizedBlock &tb = cr.blocks[b];
		while (!tb.words.isEmpty() && tb.words.first().length() == 1 && uselessPunctation.contains(tb.words.first()[0])) {
			tb.words.removeFirst();
			tb.indices.removeFirst();
			tb.endindices.removeFirst();
			tb.lines.removeFirst();
		}
	}

	bool backendAvailable = backend->isAvailable();
    LTStatus newstatus = backend->isWorking() ? LTS_Working : LTS_Error;
	if (newstatus != ltstatus) {
		ltstatus = newstatus;
		emit languageToolStatusChanged();
	}

	QList<TokenizedBlock> crBlocks = cr.blocks; //cr itself might become invalid during the following loop
	int crTicket = cr.ticket;
	QString crLanguage = cr.language;

	for (int b = 0; b < crBlocks.size(); b++) {
		const TokenizedBlock &tb = crBlocks.at(b);
		if (tb.words.isEmpty() || !backendAvailable) backendChecked(crTicket, b, QList<GrammarError>(), true);
		else  {
			const QStringList &words = tb.words;
            QString joined;
			int expectedLength = 0;
			foreach (const QString & s, words) expectedLength += s.length();
            joined.reserve(expectedLength + words.length());
            for (int i = 0;;) {
                joined += words[i];
                CHECK_FOR_SPACE_AND_CONTINUE_LOOP(i, words);
                joined += " ";
			}
			backend->check(crTicket, b, crLanguage, joined);
		}
	}
}

void GrammarCheck::backendChecked(uint crticket, int subticket, const QList<GrammarError> &backendErrors, bool directCall)
{
	if (shuttingDown) return;
	int reqId = -1;
	for (int i = requests.size() - 1; i >= 0; i--)
		if (requests[i].ticket == crticket) reqId = i;
	//REQUIRE(reqId != -1);
	if (reqId == -1) return;

	CheckRequest &cr = requests[reqId];
	REQUIRE(subticket >= 0 && subticket < cr.blocks.size());
	TokenizedBlock &tb = cr.blocks[subticket];

	cr.handledBlocks++;

	for (int i = 0; i < cr.inlines.size(); i++) {
		if (cr.linesToSkip.contains(i)) continue;
		TicketHash::iterator it = tickets.find(cr.inlines[i].line);
		Q_ASSERT(it != tickets.end());
		if (it == tickets.end()) continue;
		Q_ASSERT(it.value().second >= 0);
		bool remove = cr.handledBlocks == cr.blocks.size();
		if (it.value().first != cr.ticket) {
			cr.linesToSkip << i;
			remove = true;
		}
		if (remove) {
			it.value().second--;
			if (it.value().second <= 0) tickets.erase(it);
		}
	}
	if (cr.linesToSkip.size() == cr.inlines.size()) {
		requests.removeAt(reqId);
		return;
	}

	QMap<QString, LanguageGrammarData>::const_iterator it = languages.constFind(cr.language);
	if (it == languages.constEnd()) {
		LanguageGrammarData lgd;
        lgd.stopWords = readWordList(config.wordlistsDir + "/" + languageFromLanguageToolToHunspell(cr.language) + ".stopWords");
        lgd.badWords = readWordList(config.wordlistsDir + "/" + languageFromLanguageToolToHunspell(cr.language) + ".badWords");
		languages.insert(cr.language, lgd);
		it = languages.constFind(cr.language);
	}
	const LanguageGrammarData &ld = *it;

	if (cr.errors.size() != cr.inlines.size())
		cr.errors.resize(cr.inlines.size());

	QStringList &words = tb.words;

	if (config.longRangeRepetitionCheck) {
		const int MAX_REP_DELTA = config.maxRepetitionDelta;
		bool checkLastWord = directCall;
		QString prevSW;
		//check repetition
		QHash<QString, int> repeatedWordCheck;
		int totalWords = 0;
		for (int w = 0 ; w < words.size(); w++) {
			totalWords++;
			if (words[w].length() == 1  && getCommonEOW().contains(words[w][0])) continue; //punctation

			//check words
			bool realCheck = true; //cr.lines[w] >= cr.linesToSkipDelta;
			int truncatedChars = 0;
			QString normalized = words[w].toLower();
			if (normalized.endsWith('.')) {
				normalized = normalized.left(normalized.length() -1);
				truncatedChars =  1;
			}
			if (ld.stopWords.contains(normalized)) {
				if (checkLastWord) {
					if (prevSW == normalized)
						cr.errors[tb.lines[w]] << GrammarError(tb.indices[w], tb.endindices[w] - tb.indices[w], GET_WORD_REPETITION, tr("Word repetition"), QStringList() << "");
					prevSW = normalized;
				}
				continue;
			} else prevSW.clear();
			if (realCheck) {
				int lastSeen = repeatedWordCheck.value(normalized, -1);
				if (lastSeen > -1) {
					int delta = totalWords - lastSeen;
					if (delta <= MAX_REP_DELTA)
						cr.errors[tb.lines[w]] << GrammarError(tb.indices[w], tb.endindices[w] - tb.indices[w] - truncatedChars, GET_WORD_REPETITION, tr("Word repetition. Distance %1").arg(delta), QStringList() << "");
					else if (config.maxRepetitionLongRangeDelta > config.maxRepetitionDelta && delta <= config.maxRepetitionLongRangeDelta && normalized.length() >= config.maxRepetitionLongRangeMinWordLength)
						cr.errors[tb.lines[w]] << GrammarError(tb.indices[w], tb.endindices[w] - tb.indices[w], GET_LONG_RANGE_WORD_REPETITION, tr("Long range word repetition. Distance %1").arg(delta), QStringList() << "");
				}
			}
			repeatedWordCheck.insert(normalized, totalWords);
		}
	}
	if (config.badWordCheck) {
		for (int w = 0 ; w < words.size(); w++) {
			if (ld.badWords.contains(words[w]))
				cr.errors[tb.lines[w]] << GrammarError(tb.indices[w], tb.endindices[w] - tb.indices[w], GET_BAD_WORD, tr("Bad word"), QStringList() << "");
			else if (words[w].length() > 1 && words[w].endsWith('.') && ld.badWords.contains(words[w].left(words[w].length() - 1)))
				cr.errors[tb.lines[w]] << GrammarError(tb.indices[w], tb.endindices[w] - tb.indices[w] - 1, GET_BAD_WORD, tr("Bad word"), QStringList() << "");
		}

	}


	//map indices to latex lines and indices
	int curWord = 0, curOffset = 0;
	int err = 0;
	while (err < backendErrors.size()) {
		if (backendErrors[err].offset >= curOffset + words[curWord].length()) {
			curOffset += words[curWord].length();
			CHECK_FOR_SPACE_AND_CONTINUE_LOOP(curWord, words);
			curOffset++; //space
		} else { //if (backendErrors[err].offset >= curOffset) {
			int trueIndex = tb.indices[curWord] + qMax(0, backendErrors[err].offset - curOffset);
			int trueLength = -1;
			int offsetEnd = backendErrors[err].offset + backendErrors[err].length;
			int tempOffset = curOffset;
			for (int w = curWord; ; ) {
				tempOffset += words[w].length();
				if (tempOffset >=  offsetEnd) {
					if (tb.lines[curWord] == tb.lines[w]) {
						int trueOffsetEnd = tb.endindices[w] - qMax(0, tempOffset - offsetEnd);
						trueLength = trueOffsetEnd - trueIndex;
					}
					break;
				}
				CHECK_FOR_SPACE_AND_CONTINUE_LOOP(w, words);
				tempOffset++; //space
			}
			if (trueLength == -1)
				trueLength = cr.inlines[tb.lines[curWord]].text.length() - trueIndex;
			cr.errors[tb.lines[curWord]] << GrammarError(trueIndex, trueLength, backendErrors[err]);
			err++;
		}
	}

	if (cr.handledBlocks == cr.blocks.size()) {
		//notify
		for (int l = 0; l < cr.inlines.size(); l++) {
			if (cr.linesToSkip.contains(l)) continue; //too late

			emit checked(cr.doc, cr.inlines[l].line, cr.firstLineNr + l, cr.errors[l]);
		}

		requests.removeAt(reqId);
	}
}

void GrammarCheck::updateLTStatus(){
    LTStatus newstatus = backend->isWorking() ? LTS_Working : LTS_Error;
    if (newstatus != ltstatus) {
        ltstatus = newstatus;
        emit languageToolStatusChanged();
    }
}

/*!
 * Reformats a language identifier from the Hunspell notation to LanguageTool notation
 * e.g. en_GB -> en-GB and it_IT -> it
 */
QString GrammarCheck::languageFromHunspellToLanguageTool(QString language)
{
	language.replace('_', '-');
	return languageMapping.value(language, language);
}

/*!
 * Reformats a language identifier from the LanguageTool notation to hunspell notation
 * e.g. en-GB -> en_GB and it -> it
 */
QString GrammarCheck::languageFromLanguageToolToHunspell(QString language)
{
    if(languageMapping.values().contains(language)){
        language=languageMapping.key(language);
    }
    language.replace('-', '_');
    return language;
}


GrammarCheckBackend::GrammarCheckBackend(QObject *parent): QObject(parent) {}

#include "QtNetwork/QNetworkAccessManager"
#include "QtNetwork/QNetworkReply"
#include "QtNetwork/QNetworkRequest"

struct CheckRequestBackend {
	int ticket;
	int subticket;
	QString language;
	QString text;
	CheckRequestBackend(int ti, int st, const QString &la, const QString &te): ticket(ti), subticket(st), language(la), text(te) {}
};

GrammarCheckLanguageToolSOAP::GrammarCheckLanguageToolSOAP(QObject *parent): GrammarCheckBackend(parent), nam(nullptr), connectionAvailability(Unknown), triedToStart(false), firstRequest(true)
{

}

GrammarCheckLanguageToolSOAP::~GrammarCheckLanguageToolSOAP()
{
	if (nam) delete nam;
}
/*!
 * \brief GrammarCheckLanguageToolSOAP::init
 * Initialize LanguageTool as grammar backend
 * \param config reference to config
 */
void GrammarCheckLanguageToolSOAP::init(const GrammarCheckerConfig &config)
{

	server = config.languageToolURL;
	ltPath = config.languageToolAutorun ? config.languageToolPath : "";
	if (!ltPath.endsWith("jar")) {
		QStringList jars;
		jars << "/LanguageTool.jar" << "/languagetool-server.jar" << "/languagetool-standalone.jar";
		foreach (const QString &j, jars)
			if (QFile::exists(ltPath + j)) {
				ltPath = ltPath + j;
				break;
			}
	}
	ltArguments = config.languageToolArguments;
	javaPath = config.languageToolJavaPath;

	ignoredRules.clear();
	foreach (const QString &r, config.languageToolIgnoredRules.split(","))
		ignoredRules << r.trimmed();
	connectionAvailability = Unknown;
	if (config.languageToolURL.isEmpty()) connectionAvailability = Broken;
	triedToStart = false;
	firstRequest = true;


	specialRules.clear();
	QList<const QString *> sr = QList<const QString *>() << &config.specialIds1 << &config.specialIds2 << &config.specialIds3 << &config.specialIds4;
	foreach (const QString *s, sr) {
		QSet<QString> temp;
		foreach (const QString &r, s->split(","))
			temp << r.trimmed();
		specialRules << temp;
	}
}
/*!
 * \brief GrammarCheckLanguageToolSOAP::isAvailable
 * \return LanguageTool is available (or possibly so)
 */
bool GrammarCheckLanguageToolSOAP::isAvailable()
{
	return connectionAvailability == Unknown || connectionAvailability == WorkedAtLeastOnce;
}

/*!
 * \brief GrammarCheckLanguageToolSOAP::isWorking
 * \return LanguageTool is known to work
 */
bool GrammarCheckLanguageToolSOAP::isWorking()
{
    return connectionAvailability == WorkedAtLeastOnce;
}

QString GrammarCheckLanguageToolSOAP::url()
{
#if QT_VERSION < 0x050000
    return server.toString();
#else
	return server.toDisplayString();
#endif
}

QString quoteSpaces(const QString &s)
{
	if (!s.contains(' ')) return s;
	return '"' + s + '"';
}
/*!
 * \brief GrammarCheckLanguageToolSOAP::tryToStart
 * try to start LanguageTool-Server on local machine
 */
void GrammarCheckLanguageToolSOAP::tryToStart()
{
	if (triedToStart) {
		if (QDateTime::currentDateTime().toTime_t() - startTime < 60 * 1000 ) {
			connectionAvailability = Unknown;
			ThreadBreaker::sleep(1);
		}
		return;
	}
	triedToStart = true;
	startTime = 0;
	if (ltPath == "" || !QFileInfo(ltPath).exists()) return;
	javaProcess = new QProcess();
	connect(javaProcess, SIGNAL(finished(int)), javaProcess, SLOT(deleteLater()));
	connect(this, SIGNAL(destroyed()), javaProcess, SLOT(deleteLater()));

	javaProcess->start(quoteSpaces(javaPath) + " -cp " + quoteSpaces(ltPath) + "  " + ltArguments);
	javaProcess->waitForStarted();

	connectionAvailability = Unknown;
	startTime = QDateTime::currentDateTime().toTime_t(); //TODO: fix this in year 2106 when hopefully noone uses qt4.6 anymore
}

const QNetworkRequest::Attribute AttributeTicket = (QNetworkRequest::Attribute)(QNetworkRequest::User);
const QNetworkRequest::Attribute AttributeLanguage = (QNetworkRequest::Attribute)(QNetworkRequest::User + 2);
const QNetworkRequest::Attribute AttributeText = (QNetworkRequest::Attribute)(QNetworkRequest::User + 3);
const QNetworkRequest::Attribute AttributeSubTicket = (QNetworkRequest::Attribute)(QNetworkRequest::User + 4);
/*!
 * \brief GrammarCheckLanguageToolSOAP::check
 * Place data to be checked on LT-Server
 * \param ticket
 * \param subticket
 * \param language
 * \param text
 */
void GrammarCheckLanguageToolSOAP::check(uint ticket, int subticket, const QString &language, const QString &text)
{
    if (!nam) {
		nam = new QNetworkAccessManager();
		connect(nam, SIGNAL(finished(QNetworkReply *)), SLOT(finished(QNetworkReply *)));
	}

	REQUIRE(nam);

	QString lang = language;
	if (languagesCodesFail.contains(lang) && lang.contains('-'))
		lang = lang.left(lang.indexOf('-'));

	if (connectionAvailability == Unknown) {
		if (firstRequest) firstRequest = false;
		else {
			delayedRequests << CheckRequestBackend(ticket, subticket, lang, text);
			return;
		}
	}

	QNetworkRequest req(server);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "text/xml; charset=UTF-8");
    req.setRawHeader("User-Agent", QString("texstudio %1").arg(TXSVERSION).toUtf8());
	QByteArray post;
	post.reserve(text.length() + 50);
	post.append("language=" + lang + "&text=");
	post.append(QUrl::toPercentEncoding(text, QByteArray(), QByteArray(" ")));
	post.append("\n");

	//qDebug() << text;

	req.setAttribute(AttributeTicket, ticket);
	req.setAttribute(AttributeLanguage, lang);
	req.setAttribute(AttributeText, text);
	req.setAttribute(AttributeSubTicket, subticket);

	nam->post(req, post);
}
/*!
 * \brief GrammarCheckLanguageToolSOAP::shutdown
 * shutdown LT-Server
 */
void GrammarCheckLanguageToolSOAP::shutdown()
{
	if (javaProcess) {
		javaProcess->terminate();
		javaProcess->deleteLater();
	}
	connectionAvailability = Terminated;
	if (nam) {
		nam->deleteLater();
        nam = nullptr;
	}
}
/*!
 * \brief GrammarCheckLanguageToolSOAP::finished
 * Slot for postprocessing LT data
 * \param nreply
 */
void GrammarCheckLanguageToolSOAP::finished(QNetworkReply *nreply)
{
	if (connectionAvailability == Terminated) return;  // shutting down
	if (connectionAvailability == Broken) return;  // don't continue if failed before
	if (nam != sender()) return; //safety check, in case nam was deleted and recreated

	uint ticket = nreply->request().attribute(AttributeTicket).toUInt();
	int subticket = nreply->request().attribute(AttributeSubTicket).toInt();
	QString text = nreply->request().attribute(AttributeText).toString();
	int status = nreply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

	//qDebug() << status << ": " << reply;

	if (status == 0) {
		//no response
		connectionAvailability = Broken; //assume no backend
		tryToStart();
		if (connectionAvailability == Broken) {
			if (delayedRequests.size()) delayedRequests.clear();
			nam->deleteLater(); // shutdown unnecessary network manager (Bug 1717/1738)
            nam = nullptr;
			return; //confirmed: no backend
		}
		//there might be a backend now, but we still don't have the results
		firstRequest = true; //send this request directly, queue later ones
		check(ticket, subticket, nreply->request().attribute(AttributeLanguage).toString(), text);
		nreply->deleteLater();
		return;
	}

	QByteArray reply = nreply->readAll();

	if (status == 500 && reply.contains("language code") && reply.contains("IllegalArgumentException")) {
		QString lang = nreply->request().attribute(AttributeLanguage).toString();
		if (lang.contains('-')) {
			languagesCodesFail.insert(lang);
			check(ticket, subticket, lang, text);
		}
		return;
	}

	connectionAvailability = WorkedAtLeastOnce;

	QDomDocument dd;
	dd.setContent(reply);
	QList<GrammarError> results;
	QDomNode n = dd.documentElement();
	QDomNodeList lterrors = n.childNodes();
	for (int i = 0; i < lterrors.size(); i++) {
		if (lterrors.at(i).nodeType() != QDomNode::ElementNode) continue;
		if (lterrors.at(i).nodeName() != "error") continue;
		QDomNamedNodeMap atts = lterrors.at(i).attributes();
		QString id = atts.namedItem("ruleId").nodeValue();
		if (ignoredRules.contains(id)) continue;
		QString context = atts.namedItem("context").nodeValue();
		int contextoffset = atts.namedItem("contextoffset").nodeValue().toInt();
		if (context.endsWith("..")) context.chop(3);
		if (context.startsWith("..")) context = context.mid(3), contextoffset -= 3;
		int from = atts.namedItem("fromx").nodeValue().toInt();
		int realfrom = text.indexOf(context, qMax(from - 5 - context.length(), 0)); //don't trust from
		//qDebug() << realfrom << context;
		if (realfrom == -1) {
			realfrom = from;
		} // qDebug() << "discard => " << from; }
		else  realfrom += contextoffset;
		int len = atts.namedItem("errorlength").nodeValue().toInt();
		QStringList cors = atts.namedItem("replacements").nodeValue().split("#");
		if (cors.size() == 1 && cors.first() == "") cors.clear();

		int type = GET_BACKEND;
		for (int j = 0; j < specialRules.size(); j++)
			if (specialRules[j].contains(id)) {
				type += j + 1;
				break;
			}
		results << GrammarError(realfrom, len, (GrammarErrorType)type, atts.namedItem("msg").nodeValue() + " (" + id + ")", cors);
		//qDebug() << realfrom << len;
	}

	emit checked(ticket, subticket, results);

	nreply->deleteLater();

	if (delayedRequests.size()) {
		QList<CheckRequestBackend> delayedRequestsCopy = delayedRequests;
		delayedRequests.clear();
		foreach (const CheckRequestBackend &cr, delayedRequestsCopy)
			check(cr.ticket, cr.subticket, cr.language, cr.text);
	}
}

#if QT_VERSION >= 0x050000
GrammarCheckLanguageToolJSON::GrammarCheckLanguageToolJSON(QObject *parent): GrammarCheckBackend(parent), nam(nullptr), connectionAvailability(Unknown), triedToStart(false), firstRequest(true),startTime(0)
{

}

GrammarCheckLanguageToolJSON::~GrammarCheckLanguageToolJSON()
{
    if (nam) delete nam;
}
/*!
 * \brief GrammarCheckLanguageToolJSON::init
 * Initialize LanguageTool as grammar backend
 * \param config reference to config
 */
void GrammarCheckLanguageToolJSON::init(const GrammarCheckerConfig &config)
{
    QString url = config.languageToolURL;
    if(!url.endsWith("/v2/check")){
        if(!config.languageToolURL.endsWith("/"))
            url += "/";
        url += "v2/check";
    }
    if(!url.contains("://")){
        //protocol missing, set to default
        url.prepend("http://");
    }
    server=url;

    ltPath = config.languageToolAutorun ? config.languageToolPath : "";
    if (!ltPath.endsWith("jar")) {
        QStringList jars;
        jars << "/LanguageTool.jar" << "/languagetool-server.jar" << "/languagetool-standalone.jar";
        foreach (const QString &j, jars)
            if (QFile::exists(ltPath + j)) {
                ltPath = ltPath + j;
                break;
            }
    }
    ltArguments = config.languageToolArguments;
    javaPath = config.languageToolJavaPath;

    ignoredRules.clear();
    foreach (const QString &r, config.languageToolIgnoredRules.split(","))
        ignoredRules << r.trimmed();
    connectionAvailability = Unknown;
    if (config.languageToolURL.isEmpty()) connectionAvailability = Broken;
    triedToStart = false;
    firstRequest = true;


    specialRules.clear();
    QList<const QString *> sr = QList<const QString *>() << &config.specialIds1 << &config.specialIds2 << &config.specialIds3 << &config.specialIds4;
    foreach (const QString *s, sr) {
        QSet<QString> temp;
        foreach (const QString &r, s->split(","))
            temp << r.trimmed();
        specialRules << temp;
    }
}
/*!
 * \brief GrammarCheckLanguageToolJSON::isAvailable
 * \return LanguageTool is available (or possibly so)
 */
bool GrammarCheckLanguageToolJSON::isAvailable()
{
    return connectionAvailability == Unknown || connectionAvailability == WorkedAtLeastOnce;
}

/*!
 * \brief GrammarCheckLanguageToolJSON::isWorking
 * \return LanguageTool is available and *known* to work
 */
bool GrammarCheckLanguageToolJSON::isWorking()
{
    return connectionAvailability == WorkedAtLeastOnce;
}

QString GrammarCheckLanguageToolJSON::url()
{
#if QT_VERSION < 0x050000
    return server.toString();
#else
    return server.toDisplayString();
#endif
}

/*!
 * \brief GrammarCheckLanguageToolJSON::tryToStart
 * try to start LanguageTool-Server on local machine
 */
void GrammarCheckLanguageToolJSON::tryToStart()
{
    if (triedToStart) {
        if (QDateTime::currentDateTime().toTime_t() - startTime < 60 * 1000 ) {
            connectionAvailability = Unknown;
            ThreadBreaker::sleep(1);
        }
        return;
    }
    triedToStart = true;
    startTime = 0;
    if (ltPath == "" || !QFileInfo(ltPath).exists()) return;
    javaProcess = new QProcess();
    connect(javaProcess, SIGNAL(finished(int)), javaProcess, SLOT(deleteLater()));
    connect(this, SIGNAL(destroyed()), javaProcess, SLOT(deleteLater()));

    javaProcess->start(quoteSpaces(javaPath) + " -cp " + quoteSpaces(ltPath) + "  " + ltArguments);
    javaProcess->waitForStarted();

    connectionAvailability = Unknown;
    startTime = QDateTime::currentDateTime().toTime_t(); //TODO: fix this in year 2106 when hopefully noone uses qt4.6 anymore
}

/*!
 * \brief GrammarCheckLanguageToolJSON::check
 * Place data to be checked on LT-Server
 * \param ticket
 * \param subticket
 * \param language
 * \param text
 */
void GrammarCheckLanguageToolJSON::check(uint ticket, int subticket, const QString &language, const QString &text)
{
    if (!nam) {
        nam = new QNetworkAccessManager();
        connect(nam, SIGNAL(finished(QNetworkReply *)), SLOT(finished(QNetworkReply *)));
    }

    REQUIRE(nam);

    QString lang = language;
    if (languagesCodesFail.contains(lang) && lang.contains('-'))
        lang = lang.left(lang.indexOf('-'));

    if (connectionAvailability == Unknown) {
        if (firstRequest) firstRequest = false;
        else {
            delayedRequests << CheckRequestBackend(ticket, subticket, lang, text);
            return;
        }
    }

    QNetworkRequest req(server);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "text/json");
    QByteArray post;
    post.reserve(text.length() + 50);
    post.append("language=" + lang + "&text=");
    post.append(QUrl::toPercentEncoding(text, QByteArray(), QByteArray(" ")));
    post.append("\n");

    //qDebug() << text;

    req.setAttribute(AttributeTicket, ticket);
    req.setAttribute(AttributeLanguage, lang);
    req.setAttribute(AttributeText, text);
    req.setAttribute(AttributeSubTicket, subticket);

    nam->post(req, post);
}
/*!
 * \brief GrammarCheckLanguageToolJSON::shutdown
 * shutdown LT-Server
 */
void GrammarCheckLanguageToolJSON::shutdown()
{
    if (javaProcess) {
        javaProcess->terminate();
        javaProcess->deleteLater();
    }
    connectionAvailability = Terminated;
    if (nam) {
        nam->deleteLater();
        nam = nullptr;
    }
}
/*!
 * \brief GrammarCheckLanguageToolJSON::finished
 * Slot for postprocessing LT data
 * \param nreply
 */
void GrammarCheckLanguageToolJSON::finished(QNetworkReply *nreply)
{
    if (connectionAvailability == Terminated) return;  // shutting down
    if (connectionAvailability == Broken) return;  // don't continue if failed before
    if (nam != sender()) return; //safety check, in case nam was deleted and recreated

    uint ticket = nreply->request().attribute(AttributeTicket).toUInt();
    int subticket = nreply->request().attribute(AttributeSubTicket).toInt();
    QString text = nreply->request().attribute(AttributeText).toString();
    int status = nreply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    //qDebug() << status << ": " << reply;

    if (status == 0) {
        //no response
        connectionAvailability = Broken; //assume no backend
        int error=nreply->error();
        //qDebug()<<error<<":"<<nreply->errorString();
        if(error==1){
            tryToStart();
        }else{
            emit errorMessage(nreply->errorString());
        }
        if (connectionAvailability == Broken) {
            if (delayedRequests.size()) delayedRequests.clear();
            nam->deleteLater(); // shutdown unnecessary network manager (Bug 1717/1738)
            nam = nullptr;
            return; //confirmed: no backend
        }
        //there might be a backend now, but we still don't have the results
        firstRequest = true; //send this request directly, queue later ones
        check(ticket, subticket, nreply->request().attribute(AttributeLanguage).toString(), text);
        nreply->deleteLater();
        return;
    }

    QByteArray reply = nreply->readAll();

    if( status== 400 && reply.startsWith("Error:")){
        // LT announces error in set-up, probably with the language code
        // put error message into status symbol
        emit errorMessage(QString(reply));
    }

    if (status == 500 && reply.contains("language code") && reply.contains("IllegalArgumentException")) {
        QString lang = nreply->request().attribute(AttributeLanguage).toString();
        if (lang.contains('-')) {
            languagesCodesFail.insert(lang);
            check(ticket, subticket, lang, text);
        }
        return;
    }

    if(connectionAvailability!=WorkedAtLeastOnce){
        connectionAvailability = WorkedAtLeastOnce;
        emit languageToolStatusChanged();
    }

    QJsonDocument jsonDoc=QJsonDocument::fromJson(reply);
    QJsonObject dd=jsonDoc.object();
    QList<GrammarError> results;
    QJsonArray matches=dd["matches"].toArray();
    for (QJsonArray::const_iterator lterrors = matches.constBegin(); lterrors != matches.constEnd(); lterrors++) {
        QJsonValue v=*lterrors;
        QJsonObject obj= v.toObject();

        QJsonObject rule=obj["rule"].toObject();
        QString id=rule["id"].toString();
        if (ignoredRules.contains(id)) continue;
        int len = obj["length"].toInt();
        int from = obj["offset"].toInt();
        QJsonObject contextObj=obj["context"].toObject();
        QString context = contextObj["text"].toString();
        int contextoffset = contextObj["offset"].toInt();
        /*



        if (context.endsWith("..")) context.chop(3);
        if (context.startsWith("..")) context = context.mid(3), contextoffset -= 3;
        */

        int realfrom = text.indexOf(context, qMax(from - 5 - context.length(), 0)); //don't trust from
        //qDebug() << realfrom << context;
        if (realfrom == -1) {
            realfrom = from;
        } // qDebug() << "discard => " << from; }
        else  realfrom += contextoffset;

        QStringList cors;
        QJsonArray repl=obj["replacements"].toArray();
        foreach (QJsonValue elem, repl) {
            QJsonObject i=elem.toObject();
            cors<<i["value"].toString();
        }

        if (cors.size() == 1 && cors.first() == "") cors.clear();

        int type = GET_BACKEND;
        for (int j = 0; j < specialRules.size(); j++)
            if (specialRules[j].contains(id)) {
                type += j + 1;
                break;
            }
        // TODO: message is only needed in the tooltip and should be formatted there. We should extend the Grammar error to
        // contain the raw information.
        QStringList message;
        QString title = obj["shortMessage"].toString();
        if (title.length() > 0)
            message << "<b>" + title + "</b>";
        QString description = obj["message"].toString();
        if (description.length() > 0 && description != title)
            message << description;
        message << ("(" + id + ")");
        results << GrammarError(realfrom, len, (GrammarErrorType)type, message.join("<br>"), cors);
        //qDebug() << realfrom << len;
    }

    emit checked(ticket, subticket, results);

    nreply->deleteLater();

    if (delayedRequests.size()) {
        QList<CheckRequestBackend> delayedRequestsCopy = delayedRequests;
        delayedRequests.clear();
        foreach (const CheckRequestBackend &cr, delayedRequestsCopy)
            check(cr.ticket, cr.subticket, cr.language, cr.text);
    }
}
#endif
