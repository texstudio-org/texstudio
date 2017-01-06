#include "searchresultmodel.h"
#include "qdocument.h"
#include "qdocumentsearch.h"
#include "smallUsefulFunctions.h"

const int SearchResultModel::LineNumberRole = Qt::UserRole;

/* *** internal id (iid) semantics ***
 * the internal id associates QModelIndex with the internal data structure. The iid is structured as followed
 *
 * < search index >  < line index >
 * 00000000 00000000 00000000 00000000
 *
 * - The upper 16 bits encode the search (i.e. a top-level group):
 *     m_searches[i] maps to (i + 1) * (1 << 16)
 * - Bit 16 (1<<15) is a flag indcating that the item is a result entry within a search
 * - Bits 1-15 indicate the position of the result entry within the search
 *
 * Example:
 *  * tree structure *   ** iid **     * internal data *
 *  Search in file A     0x00010000    searches[0]
 *    Result entry a0    0x00018000    searches[0].lines[0]
 *    Result entry a1    0x00018001    searches[0].lines[1]
 *  Search in file B     0x00020000    seraches[1]
 *    Result entry a0    0x00018000    searches[1].lines[0]
 *    Result entry a1    0x00018001    searches[1].lines[1]
 */

#define RESULT_ENTRY_FLAG (1<<15)
#define SEARCH_MASK 0xFFFF0000

bool iidIsResultEntry(quint32 iid)
{
	return iid & RESULT_ENTRY_FLAG;
}

quint32 makeResultEntryIid(quint32 searchIid, int row)
{
	return searchIid + RESULT_ENTRY_FLAG + row;
}

quint32 searchIid(quint32 iid)
{
	return iid & SEARCH_MASK;
}

int searchIndexFromIid(quint32 iid)
{
	return int(iid >> 16) - 1;
}

quint32 iidFromSearchIndex(int searchIndex)
{
	return (searchIndex + 1) * (1 << 16);
}


SearchResultModel::SearchResultModel(QObject *parent): QAbstractItemModel(parent), mIsWord(false), mIsCaseSensitive(false), mIsRegExp(false), mAllowPartialSelection(true)
{
	m_searches.clear();
	mExpression.clear();
}

SearchResultModel::~SearchResultModel()
{
}

void SearchResultModel::addSearch(const SearchInfo &search)
{
#if QT_VERSION<0x050000
#else
	beginResetModel();
#endif
	m_searches.append(search);
	int lineNumber = 0;
	m_searches.last().lineNumberHints.clear();
	for (int i = 0; i < search.lines.size(); i++) {
		lineNumber = search.doc->indexOf(search.lines[i], lineNumber);
		m_searches.last().lineNumberHints << lineNumber;
	}
#if QT_VERSION<0x050000
	reset();
#else
	endResetModel();
#endif
}

QList<SearchInfo> SearchResultModel::getSearches()
{
	return m_searches;
}

void SearchResultModel::clear()
{
#if QT_VERSION<0x050000
#else
	beginResetModel();
#endif

	m_searches.clear();
	mExpression.clear();
	mAllowPartialSelection = true;

#if QT_VERSION<0x050000
	reset();
#else
	endResetModel();
#endif
}

void SearchResultModel::removeSearch(const QDocument *doc)
{
	return;
	// TODO: currently unused, also it requires beginResetModel() or similar
	for (int i = m_searches.size() - 1; i >= 0; i--)
		if (m_searches[i].doc == doc)
			m_searches.removeAt(i);
}

void SearchResultModel::removeAllSearches()
{
	beginResetModel();
	m_searches.clear();
	endResetModel();
}

int SearchResultModel::columnCount(const QModelIndex &parent) const
{
	return parent.isValid() ? 1 : 1;
}

int SearchResultModel::rowCount(const QModelIndex &parent) const
{
	//return parent.isValid()?0:1;
	if (!parent.isValid()) {
		return m_searches.size();
	} else {
		int i = parent.row();
		if (i < m_searches.size() && !iidIsResultEntry(parent.internalId())) {
			return qMin(m_searches[i].lines.size(), 1000); // maximum search results limited
		} else return 0;
	}
}

QModelIndex SearchResultModel::index(int row, int column, const QModelIndex &parent)
const
{
	if (parent.isValid()) {
		return createIndex(row, column, makeResultEntryIid(parent.internalId(), row));
	} else {
		return createIndex(row, column, iidFromSearchIndex(row));
	}
}

QModelIndex SearchResultModel::parent(const QModelIndex &index)
const
{
	quint32 iid = index.internalId();
	if (iidIsResultEntry(iid)) {
		return createIndex(searchIndexFromIid(iid), 0, searchIid(iid));
	} else return QModelIndex();
}

QVariant SearchResultModel::dataForResultEntry(const SearchInfo &search, int lineIndex, int role) const
{
	if (!search.doc) return QVariant();
	bool lineIndexValid = (lineIndex >= 0 && lineIndex < search.lines.size() && lineIndex < search.lineNumberHints.size());
	switch (role) {
	case Qt::CheckStateRole:
		if (!lineIndexValid) return QVariant();
		return (search.checked.value(lineIndex, true) ? Qt::Checked : Qt::Unchecked);
	case LineNumberRole: {
		if (!lineIndexValid) return QVariant();
		int lineNo = search.doc->indexOf(search.lines[lineIndex], search.lineNumberHints[lineIndex]);
		search.lineNumberHints[lineIndex] = lineNo;
		if (lineNo < 0) return 0;
		return lineNo + 1; // internal line number is 0-based
	}
	case Qt::DisplayRole:
	case Qt::ToolTipRole:
		if (!lineIndexValid) return "";
		search.lineNumberHints[lineIndex] = search.doc->indexOf(search.lines[lineIndex], search.lineNumberHints[lineIndex]);
		if (search.lineNumberHints[lineIndex] < 0) return "";
		QDocumentLine ln = search.doc->line(search.lineNumberHints[lineIndex]);
		if (role == Qt::DisplayRole) {
			return prepareResultText(ln.text());
		} else {  // tooltip role
			return prepareReplacedText(ln.text());
		}
	}
	return QVariant();
}

QVariant SearchResultModel::dataForSearchResult(const SearchInfo &search, int role) const
{
	switch (role) {
	case Qt::ToolTipRole:
		return QVariant();
	case Qt::CheckStateRole: {
		if (search.checked.isEmpty())
			return QVariant();
		bool state = search.checked.first();
		int cnt = search.checked.count(state);
		if (cnt == search.checked.size()) {
			return state ? Qt::Checked : Qt::Unchecked;
		} else {
			return Qt::PartiallyChecked;
		}
	}
	case Qt::DisplayRole:
		return (search.doc ? QDir::toNativeSeparators(search.doc->getFileName()) : tr("File closed")) + QString(" (%1)").arg(search.lines.size());
	}
	return QVariant();
}

QVariant SearchResultModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid()) return QVariant();
	if (role != Qt::DisplayRole && role != Qt::CheckStateRole && role != Qt::ToolTipRole && role != LineNumberRole) return QVariant();
	if (role == Qt::CheckStateRole && !mAllowPartialSelection) return QVariant();

	int iid = index.internalId();
	int searchIndex = searchIndexFromIid(iid);
	if (searchIndex < 0 || searchIndex >= m_searches.size()) return QVariant();
	const SearchInfo &search = m_searches.at(searchIndex);
	if (iidIsResultEntry(iid)) {
		return dataForResultEntry(search, index.row(), role);
	} else {
		return dataForSearchResult(search, role);
	}
}

Qt::ItemFlags SearchResultModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return 0;

	return Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable ;
}

bool SearchResultModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (role != Qt::CheckStateRole || !mAllowPartialSelection )
		return false;

	int iid = index.internalId();
	int searchIndex = searchIndexFromIid(iid);
	if (searchIndex < 0 || searchIndex >= m_searches.size()) return false;
	SearchInfo &search = m_searches[searchIndex];
	if (iidIsResultEntry(iid)) {
		if (!search.doc) return false;
		int lineIndex = index.row();
		if (lineIndex < 0 || lineIndex > search.lines.size() || lineIndex > search.lineNumberHints.size()) {
			return false;
		}
		if (role == Qt::CheckStateRole) {
			search.checked.replace(lineIndex, (value == Qt::Checked));
			//m_searches.at(searchIndex).checked.replace(lineIndex,(value==Qt::Checked));
		}
		emit dataChanged(index, index);
	} else {
		bool state = (value == Qt::Checked);
		for (int l = 0; l < search.checked.size(); l++) {
			search.checked.replace(l, state);
		}
		int lastRow = search.checked.size() - 1;
		QModelIndex endIndex = createIndex(lastRow, 0, makeResultEntryIid(iid, lastRow));
		emit dataChanged(index, endIndex);
	}
	return true;
}

void SearchResultModel::setSearchExpression(const QString &exp, const QString &repl, const bool isCaseSensitive, const bool isWord, const bool isRegExp)
{
	mExpression = exp;
	mReplacementText = repl;
	mIsCaseSensitive = isCaseSensitive;
	mIsWord = isWord;
	mIsRegExp = isRegExp;
}

void SearchResultModel::setSearchExpression(const QString &exp, const bool isCaseSensitive, const bool isWord, const bool isRegExp)
{
	mExpression = exp;
	// keep mReplacementText
	mIsCaseSensitive = isCaseSensitive;
	mIsWord = isWord;
	mIsRegExp = isRegExp;
}

QString SearchResultModel::prepareReplacedText(const QString &text) const
{
	QString result = text;
	QList<QPair<int, int> > placements = getSearchResults(text);
	QPair<int, int> elem;
	int offset = 0;
	foreach (elem, placements) {
		if (mIsRegExp) {
			QRegExp rx(mExpression, mIsCaseSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive);
			//QString newText=text.replace(rx,mReplacementText);
			/*int lineNr=doc->indexOf(dlh,search.lineNumberHints.value(i,-1));
			cur->select(lineNr,elem.first,lineNr,elem.second);
			newText=newText.mid(elem.first);
			newText.chop(txt.length()-elem.second-1);
			cur->replaceSelectedText(newText);*/
		} else {
			// simple replacement
			/*int lineNr=doc->indexOf(dlh,search.lineNumberHints.value(i,-1));
			cur->select(lineNr,elem.first,lineNr,elem.second);
			cur->replaceSelectedText(replaceText);*/
			result = result.left(elem.first + offset) + "<b>" + mReplacementText + "</b>" + result.mid(elem.second + offset);
			offset += mReplacementText.length() - elem.second + elem.first + 7;
		}
	}
	return result;
}

QString SearchResultModel::prepareResultText(const QString &text) const
{
	QString result;
	QList<QPair<int, int> > placements = getSearchResults(text);
	int second;
	if (placements.size() > 0) {
		second = 0;
	} else return text;
	for (int i = 0; i < placements.size(); i++) {
		int first = placements.at(i).first;
		result.append(text.mid(second, first - second)); // add normal text
		second = placements.at(i).second;
		result.append("<|" + text.mid(first, second - first) + "|>"); // add highlighted text
	}
	result.append(text.mid(placements.last().second));
	return result;
}

QList<QPair<int, int> > SearchResultModel::getSearchResults(const QString &text) const
{
	if (mExpression.isEmpty()) return QList<QPair<int, int> >();

	QRegExp m_regexp = generateRegExp(mExpression, mIsCaseSensitive, mIsWord, mIsRegExp);

	int i = 0;
	QList<QPair<int, int> > result;
	while (i < text.length() && i > -1) {
		i = m_regexp.indexIn(text, i);
		if (i > -1) {
			if (!result.isEmpty() && result.last().second > i) {
				result.last().second = m_regexp.matchedLength() + i;
			} else
				result << qMakePair(i, m_regexp.matchedLength() + i);

			i++;
		}
	}
	return result;
}

QDocument *SearchResultModel::getDocument(const QModelIndex &index)
{
	int i = searchIndexFromIid(index.internalId());
	if (i < 0 || i >= m_searches.size()) return 0;
	if (!m_searches[i].doc) return 0;
	return m_searches[i].doc;
}

int SearchResultModel::getLineNumber(const QModelIndex &index)
{
	int iid = index.internalId();
	if (!iidIsResultEntry(iid)) return -1;
	int searchIndex = searchIndexFromIid(iid);
	if (searchIndex < 0 || searchIndex >= m_searches.size()) return -1;
	const SearchInfo &search = m_searches.at(searchIndex);
	if (!search.doc) return -1;
	int lineIndex = index.row();
	if (lineIndex < 0 || lineIndex > search.lines.size() || lineIndex > search.lineNumberHints.size()) return -1;
	search.lineNumberHints[lineIndex] = search.doc->indexOf(search.lines[lineIndex], search.lineNumberHints[lineIndex]);
	return search.lineNumberHints[lineIndex];
}

QVariant SearchResultModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role != Qt::DisplayRole) return QVariant();
	if (orientation != Qt::Horizontal) return QVariant();
	switch (section) {
	case 0:
		return tr("Results");
	default:
		return QVariant();
	}
}

int SearchResultModel::getNextSearchResultColumn(const QString &text, int col)
{
	QRegExp m_regexp = generateRegExp(mExpression, mIsCaseSensitive, mIsWord, mIsRegExp);

	int i = 0;
	int i_old = 0;
	while (i <= col && i > -1) {
		i = m_regexp.indexIn(text, i);
		if (i > -1) {
			i_old = i;
			i++;
		}
	}
	return i_old;
}
