#include "grammarcheck.h"
#include "smallUsefulFunctions.h"
#include "latexparser/latexreader.h"
#include "latexparser/latex2text.h"
#include "QThread"
#include <QJsonDocument>
#include <QJsonArray>


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
	delete latexParser;
    delete backend;
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

        backend = new GrammarCheckLanguageToolJSON(this);

        connect(backend, SIGNAL(checked(uint,int,QList<GrammarError>)), this, SLOT(backendChecked(uint,int,QList<GrammarError>)));
        connect(backend, SIGNAL(errorMessage(QString)),this,SIGNAL(errorMessage(QString)));
        connect(backend, SIGNAL(languageToolStatusChanged()),this,SLOT(updateLTStatus()));
    }
	backend->init(config);

	if (floatingEnvs.isEmpty())
		floatingEnvs << "figure" << "table" << "SCfigure" << "wrapfigure" << "subfigure" << "floatbox";

	// this is a heuristic, some LanguageTool languages have the format de-DE, others just it (instead of it-IT)
	// this list contains all two-character languages that do not have a four-character equivalent.
    languageMapping.insert("ast-ES","ast-ES");
    languageMapping.insert("be-BY","be-BY");
    languageMapping.insert("br-FR","br-FR");
    languageMapping.insert("ca-CA", "ca");
    languageMapping.insert("ca-ES","ca-ES");
    languageMapping.insert("ca-ES-valencia","ca-ES-valencia");
    languageMapping.insert("da-DK","da-DK");
    languageMapping.insert("de-AT","de-AT");
    languageMapping.insert("de-CH","de-CH");
    languageMapping.insert("de-DE","de-DE");
    languageMapping.insert("de-DE-x-simple-language-DE","de-DE-x-simple-language-DE");
    languageMapping.insert("de-LU","de-LU");
    languageMapping.insert("el-GR","el-GR");
    languageMapping.insert("en-AU","en-AU");
    languageMapping.insert("en-CA","en-CA");
    languageMapping.insert("en-EN", "en");
    languageMapping.insert("en-GB","en-GB");
    languageMapping.insert("en-NZ","en-NZ");
    languageMapping.insert("en-US","en-US");
    languageMapping.insert("en-ZA","en-ZA");
    languageMapping.insert("es-AR","es-AR");
    //languageMapping.insert("es-ES", "es");
    languageMapping.insert("es-ES","es-ES");
    languageMapping.insert("fa-FA", "fa");
    languageMapping.insert("fa-IR","fa-IR");
    //languageMapping.insert("fr-FR", "fr");
    languageMapping.insert("fr-FR","fr-FR");
    languageMapping.insert("ga-IE","ga-IE");
    languageMapping.insert("gl-ES","gl-ES");
    //languageMapping.insert("it-IT", "it");
    languageMapping.insert("it-IT","it-IT");
    languageMapping.insert("ja-JP","ja-JP");
    languageMapping.insert("km-KH","km-KH");
    languageMapping.insert("nl-BE","nl-BE");
    //languageMapping.insert("nl-NL", "nl");
    languageMapping.insert("nl-NL","nl-NL");
    languageMapping.insert("pl-PL","pl-PL");
    languageMapping.insert("pt-AO","pt-AO");
    languageMapping.insert("pt-BR","pt-BR");
    languageMapping.insert("pt-MZ","pt-MZ");
    languageMapping.insert("pt-PT","pt-PT");
    languageMapping.insert("ro-RO","ro-RO");
    languageMapping.insert("ru-RU","ru-RU");
    languageMapping.insert("sk-SK","sk-SK");
    languageMapping.insert("sl-SI","sl-SI");
    languageMapping.insert("sv-SE","sv-SE");
    languageMapping.insert("sv-SV", "sv");
    languageMapping.insert("ta-IN","ta-IN");
    languageMapping.insert("tl-PH","tl-PH");
    languageMapping.insert("uk-UA","uk-UA");
    languageMapping.insert("zh-CN","zh-CN");
}

QString GrammarCheck::serverUrl() {
    return backend->url();
}

QString GrammarCheck::getLastErrorMessage()
{
    return backend->getLastErrorMessage();
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


struct CheckRequest {
	bool pending;
	QString language;
    LatexDocument *doc;
	QList<LineInfo> inlines;
	int firstLineNr;
	uint ticket;
	int handledBlocks;
    CheckRequest(const QString &language, LatexDocument *doc, const QList<LineInfo> inlines, const int firstLineNr, const uint ticket):
        pending(true), language(language), doc(doc), inlines(inlines), firstLineNr(firstLineNr), ticket(ticket), handledBlocks(0) {}

	QList<int> linesToSkip;

	QList<TokenizedBlock> blocks;
	QVector<QList<GrammarError> > errors;
};

void GrammarCheck::check(const QString &language, LatexDocument *doc, const QList<LineInfo> &inlines, int firstLineNr)
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



void GrammarCheck::process(int reqId)
{
	REQUIRE(latexParser);
	REQUIRE(!requests.isEmpty());

	CheckRequest &cr = requests[reqId];

    cr.linesToSkip.reserve(cr.inlines.size());

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

	cr.blocks = tokenizeWords(latexParser, cr.inlines);

    LTStatus newstatus = backend->isWorking() ? LTS_Working : LTS_Error;
	if (newstatus != ltstatus) {
		ltstatus = newstatus;
		emit languageToolStatusChanged();
	}

	QList<TokenizedBlock> crBlocks = cr.blocks; //cr itself might become invalid during the following loop
	uint crTicket = cr.ticket;
	QString crLanguage = cr.language;

	for (int b = 0; b < crBlocks.size(); b++) {
		const TokenizedBlock &tb = crBlocks.at(b);
		if (tb.words.isEmpty() || !backend->isAvailable() ) backendChecked(crTicket, b, QList<GrammarError>(), true);
		else  {
			QString joined = tb.toString();
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
        QString path=config.wordlistsDir + "/" + languageFromLanguageToolToHunspell(cr.language) + ".stopWords";
        path = ConfigManagerInterface::getInstance()->parseDir(path);
        lgd.stopWords = readWordList(path);
        path=config.wordlistsDir + "/" + languageFromLanguageToolToHunspell(cr.language) + ".badWords";
        path = ConfigManagerInterface::getInstance()->parseDir(path);
        lgd.badWords = readWordList(path);
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

            int lastSeen = repeatedWordCheck.value(normalized, -1);
            if (lastSeen > -1) {
                int delta = totalWords - lastSeen;
                if (delta <= MAX_REP_DELTA)
                    cr.errors[tb.lines[w]] << GrammarError(tb.indices[w], tb.endindices[w] - tb.indices[w] - truncatedChars, GET_WORD_REPETITION, tr("Word repetition. Distance %1").arg(delta), QStringList() << "");
                else if (config.maxRepetitionLongRangeDelta > config.maxRepetitionDelta && delta <= config.maxRepetitionLongRangeDelta && normalized.length() >= config.maxRepetitionLongRangeMinWordLength)
                    cr.errors[tb.lines[w]] << GrammarError(tb.indices[w], tb.endindices[w] - tb.indices[w], GET_LONG_RANGE_WORD_REPETITION, tr("Long range word repetition. Distance %1").arg(delta), QStringList() << "");
            }

			repeatedWordCheck.insert(normalized, totalWords);
		}
	}
	if (config.badWordCheck) {
		for (int w = 0 ; w < words.size(); w++) {
			QString normalized = words[w].toLower();
			if (ld.badWords.contains(normalized))
				cr.errors[tb.lines[w]] << GrammarError(tb.indices[w], tb.endindices[w] - tb.indices[w], GET_BAD_WORD, tr("Bad word"), QStringList() << "");
			else if (normalized.length() > 1 && normalized.endsWith('.') && ld.badWords.contains(normalized.left(normalized.length() - 1)))
				cr.errors[tb.lines[w]] << GrammarError(tb.indices[w], tb.endindices[w] - tb.indices[w] - 1, GET_BAD_WORD, tr("Bad word"), QStringList() << "");
		}

	}


	//map indices to latex lines and indices
	TokenizedBlock::StringOffsetIterator tbit(tb, cr.inlines);
	for (int err=0;err < backendErrors.size(); err++) {
		int lineIndex, trueOffset, trueLength;
		if (!tbit.map(backendErrors[err].offset, backendErrors[err].length, &lineIndex, &trueOffset, &trueLength))
			break;
		cr.errors[lineIndex] << GrammarError(trueOffset, trueLength, backendErrors[err]);
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
    QString result=language;
    if(languageMapping.contains(language)){
        result=languageMapping.value(language, language);
    }else{
        // just deliver the first part of the language code if no mapping is known
        int i=language.indexOf('-');
        if(i>=0){
            result=language.left(i);
        }
    }
    return result;
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
    uint ticket;
    uint subticket;
	QString language;
	QString text;
    CheckRequestBackend(uint ti, uint st, const QString &la, const QString &te): ticket(ti), subticket(st), language(la), text(te) {}
};

const QNetworkRequest::Attribute AttributeTicket = static_cast<QNetworkRequest::Attribute>(QNetworkRequest::User);
const QNetworkRequest::Attribute AttributeLanguage = static_cast<QNetworkRequest::Attribute>(QNetworkRequest::User + 2);
const QNetworkRequest::Attribute AttributeText = static_cast<QNetworkRequest::Attribute>(QNetworkRequest::User + 3);
const QNetworkRequest::Attribute AttributeSubTicket = static_cast<QNetworkRequest::Attribute>(QNetworkRequest::User + 4);


GrammarCheckLanguageToolJSON::GrammarCheckLanguageToolJSON(QObject *parent): GrammarCheckBackend(parent), nam(nullptr), connectionAvailability(Unknown), triedToStart(false), firstRequest(true),startTime(0)
{

}

GrammarCheckLanguageToolJSON::~GrammarCheckLanguageToolJSON()
{
    delete nam;
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
    ltPath.replace("[txs-settings-dir]", config.configDir);
    ltPath.replace("[txs-app-dir]", config.appDir);
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
    return (connectionAvailability == Unknown) || (connectionAvailability == WorkedAtLeastOnce);
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
    return server.toDisplayString();
}

/*!
 * \brief GrammarCheckLanguageToolJSON::tryToStart
 * try to start LanguageTool-Server on local machine
 */
void GrammarCheckLanguageToolJSON::tryToStart()
{
    if (triedToStart) {
        if (QDateTime::currentDateTime().toSecsSinceEpoch() - startTime < 60 * 1000 ) {
            connectionAvailability = Unknown;
            ThreadBreaker::sleep(1);
        }
        return;
    }
    triedToStart = true;
    startTime = 0;
    if (ltPath == "")
        return;
    if(!QFileInfo::exists(ltPath)){
        errorText=QString("LT path \" %1 \" not found !").arg(ltPath);
        emit errorMessage(errorText);
        return;
    }
    javaProcess = new QProcess();
    connect(javaProcess, SIGNAL(finished(int,QProcess::ExitStatus)), javaProcess, SLOT(deleteLater()));
    connect(this, SIGNAL(destroyed()), javaProcess, SLOT(deleteLater()));

    javaProcess->start(javaPath,QStringList()<< "-cp" << ltPath << ltArguments.split(" ")); // check sdm
    javaProcess->waitForStarted(500);
    javaProcess->waitForReadyRead(500);
    errorText=javaProcess->readAllStandardError();
    if(!errorText.isEmpty()){
        emit errorMessage(errorText);
    }

    connectionAvailability = Unknown;
    startTime = QDateTime::currentDateTime().toSecsSinceEpoch(); //TODO: fix this in year 2106 when hopefully noone uses qt4.6 anymore
}

/*!
 * \brief GrammarCheckLanguageToolJSON::check
 * Place data to be checked on LT-Server
 * \param ticket
 * \param subticket
 * \param language
 * \param text
 */
void GrammarCheckLanguageToolJSON::check(uint ticket, uint subticket, const QString &language, const QString &text)
{
    if (!nam) {
        nam = new QNetworkAccessManager();
        connect(nam, SIGNAL(finished(QNetworkReply*)), SLOT(finished(QNetworkReply*)));
    }

    REQUIRE(nam);

    QString lang = language;
    if(lang.count('-')>1){
        // chop language code to country_variant
        lang=lang.left(5);
    }
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
    QString post;
    post.reserve(text.length() + 50);
    post.append("language=" + lang + "&text=");
    post.append(QUrl::toPercentEncoding(text, QByteArray(), QByteArray(" ")));
    post.append("\n");

    //qDebug() << text;

    req.setAttribute(AttributeTicket, ticket);
    req.setAttribute(AttributeLanguage, lang);
    req.setAttribute(AttributeText, text);
    req.setAttribute(AttributeSubTicket, subticket);

    nam->post(req, post.toUtf8());
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
 * \brief GrammarCheckLanguageToolJSON::getLastErrorMessage
 * gets the latest error message which occured when operating LT or the start of LT with java
 * \return error message
 */
QString GrammarCheckLanguageToolJSON::getLastErrorMessage()
{
    return errorText;
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
            errorText=nreply->errorString();
            emit errorMessage(errorText);
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
        errorText=QString(reply);
        emit errorMessage(errorText);
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
        for(const QJsonValue &elem: repl) {
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
        results << GrammarError(realfrom, len, static_cast<GrammarErrorType>(type), message.join("<br>"), cors);
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

