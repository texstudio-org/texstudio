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



void GrammarCheck::check(const QString& language, const void * doc, QList<LineInfo> inlines, int firstLineNr, int linesToSkipDelta){
	ticket++;
	uint currentTicket = ticket;
	for (int i=0;i<inlines.size();i++)
		tickets[inlines[i].line] = ticket;
	
	REQUIRE(latexParser);
	//gather words
	QStringList words;
	QList<int> indices, lengths, lines;
	for (int l = 0; l < inlines.size(); l++, firstLineNr++) {
		LatexReader lr(*latexParser, inlines[l].text);
		int type;
		while ((type = lr.nextWord(false))) {
			if (type == LatexReader::NW_ENVIRONMENT) continue;
			if (type == LatexReader::NW_TEXT) words << " "+lr.word;
			else if (type == LatexReader::NW_PUNCTATION) words << lr.word;
			else break;
			indices << lr.wordStartIndex;
			lengths << lr.index - lr.wordStartIndex;
			lines << l;
		}
	}
	

	QVector<QList<GrammarError> > errors;
	errors.resize(inlines.size());
	
	if (config.longRangeRepetitionCheck) {
		const int MAX_REP_DELTA = config.maxRepetitionDelta;
		//check repetition	
		QHash<QString, int> repeatedWordCheck;
		int totalWords = 0;
		for (int w=0 ;w < words.size(); w++){
			if (words[w].length() == 1 /* && getCommonEOW().contains(words[i][0])*/) continue; //punctation
			totalWords++;
	
			//check words
			bool realCheck = lines[w] >= linesToSkipDelta;
			QString normalized = words[w].toLower();
			if (realCheck) {
				int lastSeen = repeatedWordCheck.value(normalized, -1);
				if (lastSeen > -1 && totalWords - lastSeen <= MAX_REP_DELTA) 
					errors[lines[w]] << GrammarError(indices[w], lengths[w], GET_WORD_REPETITION, tr("Word repetition"), QStringList() << "");
			}
			repeatedWordCheck.insert(normalized, totalWords);
		}
	}

	//real grammar check
	QString lang = language;
	if (lang.contains('_')) lang = lang.left(lang.indexOf('_'));
	QList<GrammarError> backendErrors;
	if (!words.isEmpty()) backendErrors = backend->check(lang, words.join(""));
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
				if (tempOffset + words[curWord].length() >=  offsetEnd) {
					if (lines[curWord] == lines[w]) {
						int trueOffsetEnd = indices[w] + qMax(0, offsetEnd - tempOffset);
						if (words[w].startsWith(' ')) trueOffsetEnd--;
						trueLength = trueOffsetEnd - trueIndex;
					}
					break;
				} else tempOffset += words[curWord].length();
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


GrammarCheckLanguageToolSOAP::GrammarCheckLanguageToolSOAP(QObject* parent):GrammarCheckBackend(parent),nam(0){
	
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
	while (!replied.value(currentTicket, false)) QCoreApplication::processEvents(); //if there are pending texts to check, they will be called first, causing an reentry in this function
	
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
		QString context = atts.namedItem("context").nodeValue();
		int contextoffset = atts.namedItem("contextoffset").nodeValue().toInt();
		if (context.endsWith("..")) context.chop(3);
		if (context.startsWith("..")) context = context.mid(3), contextoffset -= 3;
		int from = atts.namedItem("fromx").nodeValue().toInt();
		int realfrom = text.indexOf(context, qMax(from-5-context.length(),0)); //don't trust from
		qDebug() << realfrom << context;
		if (realfrom == -1) realfrom = from;
		else  realfrom += contextoffset;
		int len = atts.namedItem("errorlength").nodeValue().toInt();
		results << GrammarError(realfrom, len, GET_BACKEND, atts.namedItem("msg").nodeValue(), atts.namedItem("replacements").nodeValue().split("#"));
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
	this->replied.insert(ct, true);
	reply->deleteLater();
}
