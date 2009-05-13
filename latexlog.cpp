#include "latexlog.h"
#include <QTextBlock>
#include "qlinemarksinfocenter.h"
LatexLogEntry::LatexLogEntry(QString aFile, LogType aType, QString aOldline, int aLogline, QString aMessage)
		: file(aFile), type(aType), oldline(aOldline), logline(aLogline), message(aMessage) {
	bool ok;
	oldLineNumber=oldline.toInt(&ok,10)-1;
	if (!ok) oldLineNumber=-1;
};

QString LatexLogEntry::niceMessage() const {
	QString pre="";
	switch (type) {
	case LT_BADBOX:
		pre=LatexLogModel::tr("BadBox: ");
		break;
	case LT_WARNING:
		pre=LatexLogModel::tr("Warning: ");
		break;
	case LT_ERROR:
		pre=LatexLogModel::tr("Error: ");
		break;
	}
	return pre+message;
}

LatexLogModel::LatexLogModel(QObject * parent): QAbstractTableModel(parent) {
	markIDs[0]=QLineMarksInfoCenter::instance()->markTypeId("error");
	markIDs[1]=QLineMarksInfoCenter::instance()->markTypeId("warning");
	markIDs[2]=QLineMarksInfoCenter::instance()->markTypeId("badbox");
}

int LatexLogModel::columnCount(const QModelIndex & parent) const {
	return parent.isValid()?0:4;
}
int LatexLogModel::rowCount(const QModelIndex &parent) const {
	return parent.isValid()?0:log.count();
}
QVariant LatexLogModel::data(const QModelIndex &index, int role) const {
	if (!index.isValid()) return QVariant();
	if (index.row() >= log.count() || index.row() < 0) return QVariant();
	if (role == Qt::ToolTipRole) return tr("Click to jump to the line");
	if (role == Qt::ForegroundRole) return log.at(index.row()).type==LT_ERROR?QBrush(QColor(Qt::red)):QBrush(QColor(Qt::blue));
	if (role != Qt::DisplayRole) return QVariant();
	switch (index.column()) {
	case 0:
		return log.at(index.row()).file;
	case 1:
		switch (log.at(index.row()).type) {
		case LT_ERROR:
			return tr("error");
		case LT_WARNING:
			return tr("warning");
		case LT_BADBOX:
			return tr("bad box");
		default:
			return QVariant(); //return Texmaker::tr("unknown");
		}
	case 2:
		return tr("line")+ QString(" %1").arg(log.at(index.row()).oldline);
	case 3:
		return log.at(index.row()).message;
	default:
		return QVariant();
	}
}
QVariant LatexLogModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (role != Qt::DisplayRole) return QVariant();
	if (orientation != Qt::Horizontal) return QVariant();
	switch (section) {
	case 0:
		return tr("File");
	case 1:
		return tr("Type");
	case 2:
		return tr("Line");
	case 3:
		return tr("Message");
	default:
		return QVariant();
	}
}

void LatexLogModel::reset() {
	QAbstractTableModel::reset();
}

int LatexLogModel::count() {
	return log.count();
}
void LatexLogModel::clear() {
	log.clear();
}
const LatexLogEntry& LatexLogModel::at(int i) {
	return log.at(i);
}
void LatexLogModel::append(QString aFile, LogType aType, QString aOldline, int aLogline, QString aMessage) {
	log.append(LatexLogEntry(aFile, aType, aOldline, aLogline, aMessage));
}


void LatexLogModel::parseLogDocument(QTextDocument* doc) {
	QStringList errorFileList, errorLineList, errorMessageList;
	QList<LogType> errorTypeList;
	QList<int> errorLogList;
	QString mot,suivant,lettre,expression,warning,latexerror,badbox;
	QStringList pile,filestack;
	filestack.clear();
	pile.clear();

	int j;


	int par=0;
	int errorpar=0;

	QRegExp rxWarning1("Warning: (.*) on.*line *(\\d+)");
	QRegExp rxWarning2("Warning: (.*)");
	QRegExp rxLatexError("(! )*(LaTeX Error:)* *(.*)\\.l\\.(\\d+) *(.*)");
	QRegExp rxLineError("l\\.(\\d+)");
	QRegExp rxBadBox("at (line|lines) ([0-9]+)");


	QTextBlock tb = doc->begin();
	while (tb.isValid()) {
		errorpar=par;
		expression=tb.text();
		j=0;
		pile.clear();
		while (j<expression.length()) {
			lettre=expression.mid(j,1);
			if (lettre=="(" || lettre==")") {
				pile.prepend(lettre);
				j+=1;
			} else {
				mot="";
				while (j<expression.length() && (expression.mid(j,1)!="(" && expression.mid(j,1)!=")")) {
					mot+=expression.mid(j,1);
					j+=1;
				}
				pile.prepend(mot);
			}
		}
		while (pile.count()>0) {
			mot=pile.last();
			pile.removeLast();
			if (mot=="(" && pile.count()>0) {
				suivant=pile.last();
				pile.removeLast();
				filestack.append(suivant.remove("./"));
			} else if (mot==")" && filestack.count()>0) filestack.removeLast();
		}
		if (expression.contains("Warning")) {
			warning=expression.trimmed();
			while (tb.isValid() && !expression.contains(QRegExp("\\.$"))) {
				par++;
				tb=tb.next();
				if (tb.isValid()) {
					expression=tb.text();
					warning+=expression.trimmed();
				}
			}
			if (rxWarning1.indexIn(warning) != -1) {
				if (!filestack.isEmpty()) errorFileList.append(filestack.last());
				else errorFileList.append("");
				errorTypeList.append(LT_WARNING);
				errorLineList.append(rxWarning1.cap(2));
				errorMessageList.append(rxWarning1.cap(1).replace("*",""));
				errorLogList<<errorpar;
			} else if (rxWarning2.indexIn(warning) != -1) {
				if (!filestack.isEmpty()) errorFileList.append(filestack.last());
				else errorFileList.append("");
				errorTypeList.append(LT_WARNING);
				errorLineList.append("1");
				errorMessageList.append(rxWarning2.cap(1).replace("*",""));
				errorLogList<<errorpar;
			} else {
				if (!filestack.isEmpty()) errorFileList.append(filestack.last());
				else errorFileList.append("");
				errorTypeList.append(LT_WARNING);
				errorLineList.append("1");
				errorMessageList.append(warning.replace("*",""));
				errorLogList<<errorpar;
			}
			errorpar=par;
		} else if (expression.contains(QRegExp("^!"))) {
			latexerror=expression.trimmed();
			while (tb.isValid() && !expression.contains(rxLineError)) {
				par++;
				tb=tb.next();
				if (tb.isValid()) {
					expression=tb.text();
					latexerror+=expression.trimmed();
				}
			}
			//qDebug() << latexerror;
// 		if ( rxLatexError.indexIn(latexerror) != -1 )
// 			{
// 			qDebug() << rxLatexError.cap(1);
// 			qDebug() << rxLatexError.cap(2);
// 			qDebug() << rxLatexError.cap(3);
// 			qDebug() << rxLatexError.cap(4);
// 			qDebug() << rxLatexError.cap(5);
// 			errorFileList.append(filestack.last());
// 			errorTypeList.append("Error");
// 			errorLineList.append(rxLatexError.cap(1));
// 			errorMessageList.append(rxLatexError.cap(3)+" :"+rxLatexError.cap(5));
// 			}
			if (rxLineError.indexIn(latexerror) != -1) {
				//qDebug() << "Error";
				if (!filestack.isEmpty()) errorFileList.append(filestack.last());
				else errorFileList.append("");
				errorTypeList.append(LT_ERROR);
				errorLineList.append(rxLineError.cap(1));
				errorMessageList.append(latexerror.remove(rxLineError).replace("*",""));
				errorLogList<<errorpar;
			} else {
				//qDebug() << "Error";
				if (!filestack.isEmpty()) errorFileList.append(filestack.last());
				else errorFileList.append("");
				errorTypeList.append(LT_ERROR);
				errorLineList.append("1");
				errorMessageList.append(latexerror.replace("*",""));
				errorLogList<<errorpar;
			}
			errorpar=par;
		} else if (expression.contains(QRegExp("^(Over|Under)(full \\\\[hv]box .*)"))) {
			badbox=expression.trimmed();
			while (tb.isValid() && !expression.contains(QRegExp("(.*) at line"))) {
				par++;
				tb=tb.next();
				if (tb.isValid()) {
					expression=tb.text();
					badbox+=expression.trimmed();
				}
			}
			if (rxBadBox.indexIn(badbox) != -1) {
				if (!filestack.isEmpty()) errorFileList.append(filestack.last());
				else errorFileList.append("");
				errorTypeList.append(LT_BADBOX);
				errorLineList.append(rxBadBox.cap(2));
				errorMessageList.append(badbox.replace("*",""));
				errorLogList<<errorpar;
			}
			errorpar=par;
		}
		if (tb.isValid()) {
			par++;
			tb = tb.next();
		}
	}

	foundType[0]=false;
	foundType[1]=false;
	foundType[2]=false;
	QList<int> errorPos, otherPos;
	for (int i = 0; i <errorFileList.count(); i++)
		switch (errorTypeList.at(i)) {
		case LT_ERROR:
			errorPos << i;
			foundType[0]=true;
			break;
		case LT_WARNING:
			otherPos << i;
			foundType[1]=true;
			break;
		case LT_BADBOX:
			otherPos << i;
			foundType[2]=true;
			break;
		default:
			otherPos << i;
		}
	errorPos << otherPos;

	clear();
	for (int i = 0; i < errorPos.count(); i++) {
		int cur=errorPos[i];
		append(errorFileList[cur], errorTypeList[cur],errorLineList[cur], errorLogList[cur], errorMessageList[cur]);
	}

	reset(); //show changes
}

bool LatexLogModel::found(LogType lt) {
	return foundType[lt];
}
int LatexLogModel::markID(LogType lt) {
	return markIDs[lt];
}
