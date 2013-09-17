#include "grammarcheck.h"
#include "smallUsefulFunctions.h"
#include "QThread"
GrammarError::GrammarError(){}
GrammarError::GrammarError(int offset, int length, const GrammarErrorType& error, const QString& message):offset(offset),length(length), error(error), message(message){}
GrammarError::GrammarError(int offset, int length, const GrammarErrorType& error, const QString& message, const QStringList& corrections):offset(offset),length(length), error(error), message(message), corrections(corrections){}
GrammarError::GrammarError(int offset, int length, const GrammarError& other):offset(offset),length(length),error(other.error),message(other.message),corrections(other.corrections){}

GrammarCheck::GrammarCheck(QObject *parent) :
QObject(parent), backend(0), ticket(0)
{
	latexParser = new LatexParser();
}

GrammarCheck::~GrammarCheck(){
	if (latexParser) delete latexParser;
}

void GrammarCheck::init(const LatexParser& lp, const GrammarCheckerConfig& config){
	*latexParser = lp;
	this->config = config;
	if (!backend) {
		backend = new GrammarCheckLanguageToolSOAP(this);
		connect(backend,SIGNAL(checked(uint,QList<GrammarError>)),this,SLOT(backendChecked(uint,QList<GrammarError>)));
	}
	backend->init(config);
}


QSet<QString> readWordList(const QString& file){
	QFile f(file);
	if (!f.open(QFile::ReadOnly)) return QSet<QString>();
	QSet<QString> res;
	foreach (const QByteArray& ba, f.readAll().split('\n')){
		QByteArray bas = ba.simplified();
		if (bas.startsWith('#')) continue;
		res << QString::fromUtf8(bas);
	}
	return res;
}

struct CheckRequest{
	bool pending;
	QString language;
	void* doc;
	QList<LineInfo> inlines;
	int firstLineNr;
	uint ticket;
	CheckRequest(const QString& language, const void* doc, const QList<LineInfo> inlines, const int firstLineNr, const int ticket):
	       pending(true), language(language),doc(const_cast<void*>(doc)),inlines(inlines),firstLineNr(firstLineNr), ticket(ticket){}

	QList<int> linesToSkip;
	QStringList words;
	QList<int> indices, endindices, lines;
};

void GrammarCheck::check(const QString& language, const void * doc, const QList<LineInfo>& inlines, int firstLineNr){
	if (inlines.isEmpty()) return;
	
	ticket++;
	for (int i=0;i<inlines.size();i++){
		TicketHash::iterator it = tickets.find(inlines[i].line);
		if (it == tickets.end()) tickets[inlines[i].line] = QPair<uint, int> (ticket,1);
		else {
			it.value().first = ticket;
			it.value().second++;
		}
	}
	
	//qDebug()<<"CHECK:"<<inlines.first().text;
	
	QString lang = language;
	if (lang.contains('_')) lang = lang.left(lang.indexOf('_'));		
	if (lang.contains('-')) lang = lang.left(lang.indexOf('-'));		
	requests << CheckRequest(lang,doc,inlines,firstLineNr,ticket);

	//Delay processing, because there might be more requests for the same line in the event queue and only the last one needs to be checked
	QTimer::singleShot(50, this, SLOT(process()));
}

const QString uselessPunctation = "!:?,.;-"; //useful: \"(
const QString noSpacePunctation = "!:?,.;)"; 

#define CHECK_FOR_SPACE_AND_CONTINUE_LOOP(i, words) i++; \
  if (i >= (words).length()) break; \
  if ((words)[i].length() == 1 && noSpacePunctation.contains((words)[i][0])) continue; \
  if ((words)[i-1].length() == 1 && ((words)[i-1] == "(" || (words)[i-1] == "\"")) continue; \


void GrammarCheck::process(){
	REQUIRE(latexParser);
	REQUIRE(!requests.isEmpty());
		
	int reqId = -1;
	for (int i=requests.size()-1;i>=0;i--)
		if (requests[i].pending) {
			reqId = i;
			requests[i].pending = false;
			break;
		}
	REQUIRE(reqId != -1);
	
	CheckRequest &cr = requests[reqId];
	
	
	LIST_RESERVE(cr.linesToSkip, cr.inlines.size());
	if (cr.ticket != ticket) {
		//processing an old request
		for (int i=0;i<cr.inlines.size();i++){
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
	QStringList words;
	QList<int> indices, endindices, lines;
	int firstLineNr = cr.firstLineNr;
	for (int l = 0; l < cr.inlines.size(); l++, firstLineNr++) {
		LatexReader lr(*latexParser, cr.inlines[l].text);
		int type;
		while ((type = lr.nextWord(false))) {
			if (type == LatexReader::NW_ENVIRONMENT) continue;

			if (type == LatexReader::NW_COMMENT) break;
			if (type != LatexReader::NW_TEXT && type != LatexReader::NW_PUNCTATION) {
				//environment, reference, label, citation
				if (type == LatexReader::NW_ENVIRONMENT) continue;
				words << QString("keyxyz%1").arg(nonTextIndex++);
				indices << lr.wordStartIndex;
				endindices << lr.index;
				lines << l;
				continue;
			}
			
			if (latexParser->structureCommands.contains(lr.lastCommand)) {
				//don't check captions
				QStringList temp; QList<int> starts;
				LatexParser::resolveCommandOptions(lr.line,lr.wordStartIndex-1,temp,&starts);
				for(int j=0;j<starts.count() && j<2;j++){
					lr.index = starts.at(j) + temp.at(j).length()-1;
					if(temp.at(j).startsWith("{")) break;
				}
				words << ".";
				indices << lr.wordStartIndex;
				endindices << 1;
				lines << l;
				continue;
			}
			
			
			if (type == LatexReader::NW_TEXT) words << lr.word;
			else /*if (type == LatexReader::NW_PUNCTATION) */{
				if (lr.word == "-" && !words.isEmpty()) {
					//- can either mean a word-separator or a sentence -- separator
					// => if no space, join the words at both sides of the - (this could be easier handled in nextToken, but spell checking usually doesn't support - within words)
					if (lr.wordStartIndex == endindices.last()) {
						words.last() += '-';
						endindices.last()++;
						
						int tempIndex = lr.index;
						int type = lr.nextWord(false);
						if (type == LatexReader::NW_COMMENT) break;			
						if (tempIndex != lr.wordStartIndex) {
							lr.index = tempIndex;
							continue;
						}
						words.last() += lr.word;
						endindices.last() = lr.index;
						continue;
					}
				} else if (lr.word == "\"") 
					lr.word = "'"; //replace " by ' because " is encoded as &quot; and screws up the (old) LT position calculation
				words << lr.word;
			}
			
			indices << lr.wordStartIndex;
			endindices << lr.index;
			lines << l;
			
		}
	}
	
	
	while (!words.isEmpty() && words.first().length() == 1 && uselessPunctation.contains(words.first()[0])) {
		words.removeFirst();
		indices.removeFirst();
		endindices.removeFirst();
		lines.removeFirst();
	}
	
	cr.words = words;
	cr.indices = indices;
	cr.endindices = endindices;
	cr.lines = lines;

	bool backendAvailable = backend->isAvailable();
	if (words.isEmpty() || !backendAvailable) backendChecked(cr.ticket, QList<GrammarError>(), true);
	else {
		QString joined;
		int expectedLength = 0; foreach (const QString& s, words) expectedLength += s.length();
		joined.reserve(expectedLength+words.length());
		for (int i=0;;) {
			joined += words[i];
			CHECK_FOR_SPACE_AND_CONTINUE_LOOP(i,words);
			joined += " ";
		}
		backend->check(cr.ticket,cr.language, joined); 
		
	}
}
	
void GrammarCheck::backendChecked(uint crticket, const QList<GrammarError>& backendErrors, bool directCall){
	int reqId = -1;
	for (int i=requests.size()-1;i>=0;i--)
		if (requests[i].ticket == crticket) reqId = i;
	REQUIRE(reqId != -1);
	
	CheckRequest &cr = requests[reqId];
	

	for (int i=0;i<cr.inlines.size();i++){
		if (cr.linesToSkip.contains(i)) continue;
		TicketHash::iterator it = tickets.find(cr.inlines[i].line);
		Q_ASSERT(it != tickets.end());
		if (it == tickets.end()) continue;
		it.value().second--;
		Q_ASSERT(it.value().second >= 0);
		if (it.value().first != cr.ticket) 
			cr.linesToSkip << i;
		if (it.value().second <= 0) tickets.erase(it);
	}
	if (cr.linesToSkip.size() == cr.inlines.size()) {
		requests.removeAt(reqId);
		return;
	}

	QMap<QString,LanguageGrammarData>::const_iterator it = languages.constFind(cr.language);
	if (it == languages.constEnd()) { 
		LanguageGrammarData lgd;
		lgd.stopWords = readWordList(config.wordlistsDir+"/"+cr.language+".stopWords");
		lgd.badWords = readWordList(config.wordlistsDir+"/"+cr.language+".badWords");
		languages.insert(cr.language, lgd);
		it = languages.constFind(cr.language);
	}
	const LanguageGrammarData& ld = *it;
	

	QVector<QList<GrammarError> > errors;
	errors.resize(cr.inlines.size());
	
	QStringList& words = cr.words;
	
	if (config.longRangeRepetitionCheck) {
		const int MAX_REP_DELTA = config.maxRepetitionDelta;
		bool checkLastWord = directCall;
		QString prevSW;
		//check repetition	
		QHash<QString, int> repeatedWordCheck;
		int totalWords = 0;
		for (int w=0 ;w < words.size(); w++){
			totalWords++;
			if (words[w].length() == 1  && getCommonEOW().contains(words[w][0])) continue; //punctation
	
			//check words
			bool realCheck = true; //cr.lines[w] >= cr.linesToSkipDelta;
			QString normalized = words[w].toLower();
			if (ld.stopWords.contains(normalized)) {
				if (checkLastWord) {
					if (prevSW == normalized) 
						errors[cr.lines[w]] << GrammarError(cr.indices[w], cr.endindices[w]-cr.indices[w], GET_WORD_REPETITION, tr("Word repetition"), QStringList() << "");
					prevSW = normalized;
				}
				continue;
			} else prevSW.clear();
			if (realCheck) {
				int lastSeen = repeatedWordCheck.value(normalized, -1);
				if (lastSeen > -1) {
					int delta = totalWords - lastSeen;
					if (delta <= MAX_REP_DELTA) 
						errors[cr.lines[w]] << GrammarError(cr.indices[w], cr.endindices[w]-cr.indices[w], GET_WORD_REPETITION, tr("Word repetition. Distance %1").arg(delta), QStringList() << "");
					else if (config.maxRepetitionLongRangeDelta > config.maxRepetitionDelta && delta <= config.maxRepetitionLongRangeDelta && normalized.length() >= config.maxRepetitionLongRangeMinWordLength) 
						errors[cr.lines[w]] << GrammarError(cr.indices[w], cr.endindices[w]-cr.indices[w], GET_LONG_RANGE_WORD_REPETITION, tr("Long range word repetition. Distance %1").arg(delta), QStringList() << "");
				}
			}
			repeatedWordCheck.insert(normalized, totalWords);
		}
	}
	if (config.badWordCheck) {
		for (int w=0 ;w < words.size(); w++){
			if (ld.badWords.contains(words[w]))
				errors[cr.lines[w]] << GrammarError(cr.indices[w], cr.endindices[w]-cr.indices[w], GET_BAD_WORD, tr("Bad word"), QStringList() << "");
			else if (words[w].length() > 1 && words[w].endsWith('.') && ld.badWords.contains(words[w].left(words[w].length()-1)))
				errors[cr.lines[w]] << GrammarError(cr.indices[w], cr.endindices[w]-cr.indices[w]-1, GET_BAD_WORD, tr("Bad word"), QStringList() << "");
		}

	}

	
	
	
	//map indices to latex lines and indices
	int curWord = 0, curOffset = 0; int err = 0;
	while (err < backendErrors.size()) {
		if (backendErrors[err].offset >= curOffset + words[curWord].length()) {
			curOffset += words[curWord].length();
			CHECK_FOR_SPACE_AND_CONTINUE_LOOP(curWord,words);
			curOffset++; //space
		} else { //if (backendErrors[err].offset >= curOffset) {
			int trueIndex = cr.indices[curWord] + qMax(0, backendErrors[err].offset - curOffset);
			int trueLength = -1;
			int offsetEnd = backendErrors[err].offset + backendErrors[err].length;
			int tempOffset = curOffset;
			for (int w = curWord; ; ) {
				tempOffset += words[w].length();
				if (tempOffset >=  offsetEnd) {
					if (cr.lines[curWord] == cr.lines[w]) {
						int trueOffsetEnd = cr.endindices[w] - qMax(0, tempOffset - offsetEnd);
						trueLength = trueOffsetEnd - trueIndex;
					}
					break;
				} 
				CHECK_FOR_SPACE_AND_CONTINUE_LOOP(w,words);
				tempOffset++; //space
			}
			if (trueLength == -1)
				trueLength = cr.inlines[cr.lines[curWord]].text.length() - trueIndex;
			errors[cr.lines[curWord]] << GrammarError(trueIndex, trueLength, backendErrors[err]);
			err++;
		}
	}
	

	//notify
	for (int l=0;l<cr.inlines.size();l++){
		if (cr.linesToSkip.contains(l)) continue; //too late
		
		emit checked(cr.doc, cr.inlines[l].line, cr.firstLineNr+l, errors[l]);
	}
	
	requests.removeAt(reqId);
}




















GrammarCheckBackend::GrammarCheckBackend(QObject* parent):QObject(parent){}



#include "QtNetwork/QNetworkAccessManager"
#include "QtNetwork/QNetworkReply"
#include "QtNetwork/QNetworkRequest"


struct CheckRequestBackend{
	int ticket;
	QString language;
	QString text;
	CheckRequestBackend(int ti, const QString& la, const QString& te): ticket(ti), language(la), text(te) {}
};

GrammarCheckLanguageToolSOAP::GrammarCheckLanguageToolSOAP(QObject* parent):GrammarCheckBackend(parent),nam(0),connectionAvailability(false),triedToStart(false),firstRequest(true){
	
}

GrammarCheckLanguageToolSOAP::~GrammarCheckLanguageToolSOAP(){
	if (nam) delete nam;
}

void GrammarCheckLanguageToolSOAP::init(const GrammarCheckerConfig& config){
	if (!nam) {
		nam = new QNetworkAccessManager();
		connect(nam,SIGNAL(finished(QNetworkReply*)),SLOT(finished(QNetworkReply*)));
	}
	server = config.languageToolURL;
	ltPath = config.languageToolAutorun ? config.languageToolPath : "";
	if (!ltPath.endsWith("jar")) {
		QStringList jars; jars << "/LanguageTool.jar" << "/languagetool-server.jar" << "/languagetool-standalone.jar";
		foreach (const QString& j, jars)
			if (QFile::exists(ltPath + j)) {
				ltPath = ltPath + j;
				break;
			}
	}
	javaPath = config.languageToolJavaPath;
	
	ignoredRules.clear();
	foreach (const QString& r, config.languageToolIgnoredRules.split(","))
		ignoredRules << r.trimmed();
	connectionAvailability = 0;
	if (config.languageToolURL.isEmpty()) connectionAvailability = -1;
	triedToStart = false;
	firstRequest = true;
	
	
	specialRules.clear();
	QList<const QString*> sr = QList<const QString*>() << &config.specialIds1 << &config.specialIds2 << &config.specialIds3 << &config.specialIds4;
	foreach (const QString* s, sr) {
		QSet<QString> temp;
		foreach (const QString& r, s->split(","))
			temp << r.trimmed();
		specialRules << temp;
	}
}

bool GrammarCheckLanguageToolSOAP::isAvailable(){
	return connectionAvailability >= 0;
}

void GrammarCheckLanguageToolSOAP::tryToStart(){
	if (triedToStart) {
		if (QDateTime::currentDateTime().toTime_t() - startTime < 60*1000 ) {
			connectionAvailability = 0;
			ThreadBreaker::sleep(1);
		}
		return;
	}
	triedToStart = true;
	startTime = 0;
	if (ltPath == "" || !QFileInfo(ltPath).exists()) return;
	QProcess *p = new QProcess();
	connect(p, SIGNAL(finished(int)), p, SLOT(deleteLater()));
	connect(this, SIGNAL(destroyed()), p, SLOT(deleteLater()));
	p->start(javaPath + " -cp "+ltPath+ "  org.languagetool.server.HTTPServer");
	//qDebug() <<javaPath + " -cp "+ltPath+ "  org.languagetool.server.HTTPServer";
	p->waitForStarted();
	
	connectionAvailability = 0;
	startTime = QDateTime::currentDateTime().toTime_t(); //TODO: fix this in year 2106 when hopefully noone uses qt4.6 anymore
}

const QNetworkRequest::Attribute AttributeTicket = (QNetworkRequest::Attribute)(QNetworkRequest::User);
const QNetworkRequest::Attribute AttributeLanguage = (QNetworkRequest::Attribute)(QNetworkRequest::User+2);
const QNetworkRequest::Attribute AttributeText = (QNetworkRequest::Attribute)(QNetworkRequest::User+3);

void GrammarCheckLanguageToolSOAP::check(uint ticket, const QString& language, const QString& text){
	REQUIRE(nam);
		
	if (connectionAvailability == 0) {
		if (firstRequest) firstRequest = false;
		else {
			delayedRequests << CheckRequestBackend(ticket, language, text);
			return;
		}
	}

	QNetworkRequest req(server);
	req.setHeader(QNetworkRequest::ContentTypeHeader, "text/xml; charset=UTF-8");
	QByteArray post;
	post.reserve(text.length()+50);
	post.append("language="+language+"&text=");
	post.append(QUrl::toPercentEncoding(text, QByteArray(), QByteArray(" ")));
	post.append("\n");
	
	//qDebug() << text;

	req.setAttribute(AttributeTicket, ticket);
	req.setAttribute(AttributeLanguage, language);
	req.setAttribute(AttributeText, text);

	nam->post(req, post);
	
	
}

void GrammarCheckLanguageToolSOAP::finished(QNetworkReply* nreply){
	uint ticket = nreply->request().attribute(AttributeTicket).toUInt();
	QString text = nreply->request().attribute(AttributeText).toString();
	QByteArray reply = nreply->readAll();
	int status = nreply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

	//qDebug() << status << ": " << reply;
	
	if (status == 0) {
		//no response
		connectionAvailability = -1; //assume no backend
		tryToStart();
		if (connectionAvailability == -1) {
			if (delayedRequests.size()) delayedRequests.clear();
			return; //confirmed: no backend
		}
		//there might be a backend now, but we still don't have the results
		firstRequest = true;
		check(ticket, nreply->request().attribute(AttributeLanguage).toString(), text);
		nreply->deleteLater();		
		return;
	}

	connectionAvailability = 1;
				
	QDomDocument dd;
	dd.setContent(reply);
	QList<GrammarError> results;
	QDomNode n = dd.documentElement();
	QDomNodeList lterrors = n.childNodes();
	for (int i=0;i<lterrors.size();i++) {
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
		int realfrom = text.indexOf(context, qMax(from-5-context.length(),0)); //don't trust from
		//qDebug() << realfrom << context;
		if (realfrom == -1) { realfrom = from; } // qDebug() << "discard => " << from; }
		else  realfrom += contextoffset;
		int len = atts.namedItem("errorlength").nodeValue().toInt();
		QStringList cors = atts.namedItem("replacements").nodeValue().split("#");
		if (cors.size() == 1 && cors.first() == "") cors.clear();
		
		int type = GET_BACKEND;
		for (int j=0;j<specialRules.size();j++)
			if (specialRules[j].contains(id)) { type += j+1; break; }
		results << GrammarError(realfrom, len, (GrammarErrorType)type, atts.namedItem("msg").nodeValue()+ " ("+id+")", cors);
		//qDebug() << realfrom << len;
	}
	
	emit checked(ticket, results);
	
	nreply->deleteLater();
	
	if (delayedRequests.size()) {
		QList<CheckRequestBackend> delayedRequestsCopy = delayedRequests;
		delayedRequests.clear();
		foreach (const CheckRequestBackend& cr, delayedRequestsCopy)
			check(cr.ticket, cr.language, cr.text);
	}
	
	return;	
}
