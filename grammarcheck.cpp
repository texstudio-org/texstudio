#include "grammarcheck.h"
#include "smallUsefulFunctions.h"

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

void GrammarCheck::init(LatexParser lp, GrammarCheckerConfig config){
	*latexParser = lp;
	this->config = config;
	if (!backend) backend = new GrammarCheckLanguageToolSOAP(this);
	backend->init(config);
}


QSet<QString> readWordList(const QString& file){
	QFile f(file);
	if (!f.open(QFile::ReadOnly)) return QSet<QString>();
	QSet<QString> res;
	foreach (const QByteArray& ba, f.readAll().split('\n')){
		QByteArray bas = ba.simplified();
		if (bas.startsWith('#')) continue;
		res << " " + QString::fromUtf8(bas);
	}
	return res;
}

void GrammarCheck::check(const QString& language, const void * doc, QList<LineInfo> inlines, int firstLineNr, int linesToSkipDelta){
	ticket++;
	uint currentTicket = ticket;
	for (int i=0;i<inlines.size();i++)
		tickets[inlines[i].line] = ticket;
	
	QString lang = language;
	if (lang.contains('_')) lang = lang.left(lang.indexOf('_'));
	QMap<QString,LanguageGrammarData>::const_iterator it = languages.constFind(lang);
	if (it == languages.constEnd()) { 
		LanguageGrammarData lgd;
		lgd.stopWords = readWordList(config.wordlistsDir+"/"+lang+".stopWords");
		languages.insert(lang, lgd);
		it = languages.constFind(lang);
	}
	const LanguageGrammarData& ld = *it;
	
	REQUIRE(latexParser);
	//gather words
	QStringList words;
	QList<int> indices, endindices, lines;
	for (int l = 0; l < inlines.size(); l++, firstLineNr++) {
		LatexReader lr(*latexParser, inlines[l].text);
		int type;
		while ((type = lr.nextWord(false))) {
			if (type == LatexReader::NW_ENVIRONMENT) continue;

			if (type != LatexReader::NW_TEXT && type != LatexReader::NW_PUNCTATION) break;
			
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
			
			
			if (type == LatexReader::NW_TEXT) words << " "+lr.word;
			else /*if (type == LatexReader::NW_PUNCTATION) */{
				if (lr.word == "-" && !words.isEmpty()) {
					//- can either mean a word-separator or a sentence -- separator
					// => if no space, join the words at both sides of the - (this could be easier handled in nextToken, but spell checking usually doesn't support - within words)
					if (lr.wordStartIndex == endindices.last()) {
						words.last() += '-';
						endindices.last()++;
						
						int tempIndex = lr.index;
						int type = lr.nextWord(false);
						if (type != LatexReader::NW_TEXT && type != LatexReader::NW_PUNCTATION) break;
						if (tempIndex != lr.wordStartIndex) {
							lr.index = tempIndex;
							continue;
						}
						words.last() += lr.word;
						endindices.last() = lr.index;
						continue;
					}
				}
				if (lr.word == "\"") 
					lr.word = "'"; //replace " by ' because " is encoded as &quot; and screws up the LT position calculation
				words << lr.word;
			}
			
			indices << lr.wordStartIndex;
			endindices << lr.index;
			lines << l;
			
		}
	}
	
	
	while (!words.isEmpty() && words.first().length() == 1 && words.first() != QChar('"')) {
		words.removeFirst();
		indices.removeFirst();
		endindices.removeFirst();
		lines.removeFirst();
	}

	QVector<QList<GrammarError> > errors;
	errors.resize(inlines.size());
	
	bool backendAvailable = backend->isAvailable();
	
	if (config.longRangeRepetitionCheck) {
		const int MAX_REP_DELTA = config.maxRepetitionDelta;
		bool checkLastWord = !backendAvailable;
		QString prevSW;
		//check repetition	
		QHash<QString, int> repeatedWordCheck;
		int totalWords = 0;
		for (int w=0 ;w < words.size(); w++){
			if (words[w].length() == 1 /* && getCommonEOW().contains(words[i][0])*/) continue; //punctation
			totalWords++;
	
			//check words
			bool realCheck = lines[w] >= linesToSkipDelta;
			QString normalized = words[w].toLower();
			if (ld.stopWords.contains(normalized)) {
				if (checkLastWord) {
					if (prevSW == normalized) 
						errors[lines[w]] << GrammarError(indices[w], endindices[w]-indices[w], GET_WORD_REPETITION, tr("Word repetition"), QStringList() << "");
					prevSW = normalized;
				}
				continue;
			} else prevSW.clear();
			if (realCheck) {
				int lastSeen = repeatedWordCheck.value(normalized, -1);
				if (lastSeen > -1 && totalWords - lastSeen <= MAX_REP_DELTA) 
					errors[lines[w]] << GrammarError(indices[w], endindices[w]-indices[w], GET_WORD_REPETITION, tr("Word repetition"), QStringList() << "");
			}
			repeatedWordCheck.insert(normalized, totalWords);
		}
	}

	//real grammar check
	QList<GrammarError> backendErrors;
	if (!words.isEmpty() && backendAvailable) backendErrors = backend->check(lang, words.join(""));
	//qDebug() << words.join("");
	//backendErrors << GrammarError(0,3,GET_UNKNOWN);
	
	if (ticket != currentTicket) {
		//reentered, 
		bool stillValid = false;
		for (int i=0;i<inlines.size();i++)
			if (tickets.value(inlines[i].line, 0) == currentTicket) {
				stillValid = true;
				break;
			}
		if (!stillValid) return;
		
	}
	
	//map indices to latex lines and indices
	int curWord = 0, curOffset = 0; int err = 0;
	while (err < backendErrors.size() && curWord < words.size()) {
		if (backendErrors[err].offset >= curOffset + words[curWord].length()) {
			curOffset += words[curWord].length();
			curWord++;
		} else { //if (backendErrors[err].offset >= curOffset) {
			int trueIndex = indices[curWord] + qMax(0, backendErrors[err].offset - curOffset);
			if (words[curWord].startsWith(' ')) trueIndex--;
			int trueLength = -1;
			int offsetEnd = backendErrors[err].offset + backendErrors[err].length;
			int tempOffset = curOffset;
			for (int w = curWord; w < words.size(); w++) {
				tempOffset += words[w].length();
				if (tempOffset >=  offsetEnd) {
					if (lines[curWord] == lines[w]) {
						int trueOffsetEnd = endindices[w] - qMax(0, tempOffset - offsetEnd);
						if (words[curWord].startsWith(' ')) trueOffsetEnd--;
						trueLength = trueOffsetEnd - trueIndex + 1;
					}
					break;
				} 
			}
			if (trueLength == -1)
				trueLength = inlines[lines[curWord]].text.length() - trueIndex;
			errors[lines[curWord]] << GrammarError(trueIndex, trueLength, backendErrors[err]);
			err++;
		}
	}
	

	//notify
	for (int l=linesToSkipDelta;l<inlines.size();l++){
		if (tickets.value(inlines[l].line,0) != currentTicket) continue; //too late
		
		emit checked(doc, inlines[l].line, inlines[l].lineNr, errors[l]);
		
		tickets.remove(inlines[l].line);
	}
}




















GrammarCheckBackend::GrammarCheckBackend(QObject* parent):QObject(parent){}



#include "QtNetwork/QNetworkAccessManager"
#include "QtNetwork/QNetworkReply"
#include "QtNetwork/QNetworkRequest"


GrammarCheckLanguageToolSOAP::GrammarCheckLanguageToolSOAP(QObject* parent):GrammarCheckBackend(parent),nam(0),connectionAvailability(false),triedToStart(false){
	
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
	if (!ltPath.endsWith("jar")) ltPath += "/LanguageTool.jar";
	javaPath = config.languageToolJavaPath;
	
	ignoredRules.clear();
	foreach (const QString& r, config.languageToolIgnoredRules.split(","))
		ignoredRules << r.trimmed();
	connectionAvailability = 0;
	triedToStart = false;
}

bool GrammarCheckLanguageToolSOAP::isAvailable(){
	return connectionAvailability >= 0;
}

void GrammarCheckLanguageToolSOAP::tryToStart(){
	if (triedToStart) {
		if (QDateTime::currentDateTime().toTime_t() - startTime < 60*1000 ) {
			connectionAvailability = 0;
			sleep(1);
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

QList<GrammarError> GrammarCheckLanguageToolSOAP::check(const QString& language, const QString& text){
	REQUIRE_RET(nam, QList<GrammarError>());
	QNetworkRequest req(server);
	int currentTicket = ticket;
	ticket++;
	req.setAttribute(QNetworkRequest::User, currentTicket);
	req.setHeader(QNetworkRequest::ContentTypeHeader, "text/xml; charset=UTF-8");
	QByteArray post;
	post.reserve(text.length()+50);
	post.append("language="+language+"&text=");
	post.append(QUrl::toPercentEncoding(text, QByteArray(), QByteArray(" ")));
	post.append("\n");
	qDebug() << text;
	nam->post(req, post);
	while (replied.value(currentTicket, -1) == -1) QCoreApplication::processEvents(); //if there are pending texts to check, they will be called first, causing an reentry in this function
	
	if (replied.value(currentTicket, -1) == 0) {
		tryToStart();
		if (connectionAvailability == -1) return QList<GrammarError>();
		return check(language, text);
	}
	
	QString EOW = getCommonEOW();
	
	QDomDocument dd;
	dd.setContent(reply.value(currentTicket));
	QList<GrammarError> results;
	QDomNode n = dd.documentElement();
	QDomNodeList lterrors = n.childNodes();
	for (int i=0;i<lterrors.size();i++) {
		if (lterrors.at(i).nodeType() != QDomNode::ElementNode) continue;
		if (lterrors.at(i).nodeName() != "error") continue;
		QDomNamedNodeMap atts = lterrors.at(i).attributes();
		if (ignoredRules.contains(atts.namedItem("ruleId").nodeValue())) continue;
		QString context = atts.namedItem("context").nodeValue();
		int contextoffset = atts.namedItem("contextoffset").nodeValue().toInt();
		if (context.endsWith("..")) context.chop(3);
		if (context.startsWith("..")) context = context.mid(3), contextoffset -= 3;
		int from = atts.namedItem("fromx").nodeValue().toInt();
		int realfrom = text.indexOf(context, qMax(from-5-context.length(),0)); //don't trust from
		qDebug() << realfrom << context;
		if (realfrom == -1) { realfrom = from; } // qDebug() << "discard => " << from; }
		else  realfrom += contextoffset;
		int len = atts.namedItem("errorlength").nodeValue().toInt();
		QStringList cors = atts.namedItem("replacements").nodeValue().split("#");
		if (cors.size() == 1 && cors.first() == "") cors.clear();
		results << GrammarError(realfrom, len, GET_BACKEND, atts.namedItem("msg").nodeValue(), cors);
		qDebug() << realfrom << len;
	}
	qDebug() << reply.value(currentTicket);
	
	replied.remove(currentTicket);
	reply.remove(currentTicket);
	
	return results;
}

void GrammarCheckLanguageToolSOAP::finished(QNetworkReply* reply){
	int ct = reply->request().attribute(QNetworkRequest::User).toInt();
	this->reply.insert(ct, reply->readAll());
	int status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	this->replied.insert(ct, status);
	if (!connectionAvailability) {
		if (status == 0) connectionAvailability = -1;
		else connectionAvailability = 1;
	}
	reply->deleteLater();
}
