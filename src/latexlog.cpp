#include "latexlog.h"
#include "qlinemarksinfocenter.h"

LatexLogModel::LatexLogModel(QObject *parent): QAbstractTableModel(parent)
{
	markIDs[LT_NONE] = -1;
	markIDs[LT_ERROR] = QLineMarksInfoCenter::instance()->markTypeId("error");
	markIDs[LT_WARNING] = QLineMarksInfoCenter::instance()->markTypeId("warning");
	markIDs[LT_BADBOX] = QLineMarksInfoCenter::instance()->markTypeId("badbox");
	foundType[LT_NONE] = foundType[LT_ERROR] = foundType[LT_WARNING] = foundType[LT_BADBOX] = false;
}

int LatexLogModel::columnCount(const QModelIndex &parent) const
{
	return parent.isValid() ? 0 : 4;
}

int LatexLogModel::rowCount(const QModelIndex &parent) const
{
	return parent.isValid() ? 0 : log.count();
}

QVariant LatexLogModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid()) return QVariant();
	if (index.row() >= log.count() || index.row() < 0) return QVariant();
	if (role == Qt::ToolTipRole) return tr("Click to jump to the line");
	if (role == Qt::ForegroundRole) return LatexLogEntry::textColor(log.at(index.row()).type);
	if (role != Qt::DisplayRole) return QVariant();
	switch (index.column()) {
	case 0:
		return log.at(index.row()).file.mid(log.at(index.row()).file.lastIndexOf("/") + 1); //show relative names
	case 1:
		switch (log.at(index.row()).type) {
		case LT_ERROR:
			return tr("error");
		case LT_WARNING:
			return tr("warning");
		case LT_BADBOX:
			return tr("bad box");
		default:
			return QVariant(); //return Texstudio::tr("unknown");
		}
	case 2: {
		int line = log.at(index.row()).oldline;
		if (line > 0)
			return tr("line") + QString(" %1").arg(line);
		return QString();
	}
	case 3:
		return log.at(index.row()).message;
	default:
		return QVariant();
	}
}

QVariant LatexLogModel::headerData(int section, Qt::Orientation orientation, int role) const
{
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

int LatexLogModel::count() const
{
	return log.count();
}

void LatexLogModel::clear()
{
	beginResetModel();
	log.clear();
	endResetModel();
}

const LatexLogEntry &LatexLogModel::at(int i)
{
	return log.at(i);
}

//Parse a latex log file to find errors, warnings, bad boxes...
void LatexLogModel::parseLogDocument(QTextDocument *doc, QString baseFileName)
{
	LatexOutputFilter outputFilter;
	//TODO: investigate why it crashes if outputFilter is a member variable, m_infoList is set to a global variable by the LatexLogModel constructor instead here, but only if the m_filelookup member of LatexOutputFilter does exist
	outputFilter.setSource(baseFileName);
	outputFilter.run(doc);

	beginResetModel();
	log.clear();
	QList<LatexLogEntry> laterLog;
	for (int i = 0; i < outputFilter.m_infoList.count(); i++) {
		LatexLogEntry cur = outputFilter.m_infoList.at(i);
		if (cur.type == LT_ERROR) log << cur;
		else laterLog << cur;
	}
	log << laterLog;

	foundType[LT_ERROR] = outputFilter.m_nErrors > 0;
	foundType[LT_BADBOX] = outputFilter.m_nBadBoxes > 0;
	foundType[LT_WARNING] = outputFilter.m_nWarnings > 0;
	endResetModel();
}

bool LatexLogModel::found(LogType lt) const
{
	Q_ASSERT_X(lt > 0 && lt < 4, "found logtype", "unbound array index");
	return foundType[lt];
}

int LatexLogModel::markID(LogType lt) const
{
	Q_ASSERT_X(lt > 0 && lt < 4, "markID logtype", "unbound array index");
	return markIDs[lt];
}

int LatexLogModel::logLineNumberToLogEntryNumber(int logLine) const
{
	int res = -1;
	for (int i = 0; i < log.count(); i++)
		if (log.at(i).logline <= logLine)
			if (res == -1 || log.at(i).logline > log.at(res).logline)
				res = i;
	return res;
}

bool LatexLogModel::existsReRunWarning() const
{
	if (!found(LT_WARNING)) return false;
    const QRegularExpression rReRun ("(No file.*\\.(aux|toc))|"
	                       "( Rerun )");
	foreach (const LatexLogEntry &l, log) {
		if (l.type != LT_WARNING || l.oldline != 0) continue;
		if (l.message.contains(rReRun) && !l.message.contains("No file \\jobname .aux")) return true;
	}
	return false;
}

QStringList LatexLogModel::getMissingCitations() const
{
	QStringList sl;
	static QRegExp rCitation ("Citation +[`'\"]([^`'\"]+)[`'\"] +.*undefined");
	foreach (const LatexLogEntry &l, log) {
		if (l.type != LT_WARNING) continue;
		if (rCitation.indexIn(l.message) >= 0)
			sl.append(rCitation.cap(1));
	}
	return sl;
}

QString LatexLogModel::htmlErrorTable(const QList<int> &errors)
{
	QString msg = "<table>";
	foreach (int error, errors) {
		if (error < 0 || error >= count()) continue;
		msg.append(at(error).niceMessage());
	}
	return msg.append("</table>");
}

QString LatexLogModel::returnString(LogType type)
{
	switch (type) {
	case LT_ERROR:
		return tr("error");
	case LT_WARNING:
		return tr("warning");
	case LT_BADBOX:
		return tr("bad box");
	default:
		return QString();
	}
}
