#include "latexlog.h"
#include <QTextBlock>
#include "qlinemarksinfocenter.h"

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
		return log.at(index.row()).file.mid(log.at(index.row()).file.lastIndexOf("/")+1); //show relative names
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
		return tr("line")+ QString(" %1").arg(log.at(index.row()).oldline+1);
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
//void LatexLogModel::append(QString aFile, LogType aType, QString aOldline, int aLogline, QString aMessage) {
	//log.append(LatexLogEntry(aFile, aType, aOldline, aLogline, aMessage));
//}


//Parse a latex log file to find errors, warnings, bad boxes...

//However, there is a big problem with latex log files, when there are ( ) paranthesis in the document it
//is impossible to reliably determine the file which contains the error. (when there are \includes)
//Therefore it is necessary to guess the file, but the texmaker heuristic isn't great (KILE seems to be a better)
//TODO: improve this heuristic
//Workaround: Normally the error appears in the same document you edit, so if overrideFileName is != "", 
//the filename is just set to overrideFileName (=the current document). That's ugly, but still works better 
//than this reading of the log
void LatexLogModel::parseLogDocument(QTextDocument* doc, QString baseFileName, QString overrideFileName) {
	LatexOutputFilter outputFilter;
	//TODO: investigate why it crashes if outputFilter is a member variable, m_infoList is set to a global variable by the LatexLogModel constructor instead here, but only if the m_filelookup member of LatexOutputFilter does exist
	outputFilter.setSource(baseFileName);	
	outputFilter.run(doc);
	
	log.clear();
	QList<LatexLogEntry> laterLog;
	for (int i = 0; i <outputFilter.m_infoList.count(); i++) {
		LatexLogEntry cur = outputFilter.m_infoList.at(i);
		if (overrideFileName!="") cur.file=overrideFileName;
		if (cur.type == LT_ERROR) log << cur;
		else laterLog << cur;
	}
	log << laterLog;

	foundType[LT_ERROR]=outputFilter.m_nErrors>0;
	foundType[LT_BADBOX]=outputFilter.m_nBadBoxes>0;
	foundType[LT_WARNING]=outputFilter.m_nWarnings>0;
	reset(); //show changes
}

bool LatexLogModel::found(LogType lt) {
	return foundType[lt];
}
int LatexLogModel::markID(LogType lt) {
	return markIDs[lt];
}
