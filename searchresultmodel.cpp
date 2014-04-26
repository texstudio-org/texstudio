#include "searchresultmodel.h"
#include "qdocument.h"
#include "qdocumentsearch.h"
#include "smallUsefulFunctions.h"

SearchResultModel::SearchResultModel(QObject * parent): QAbstractItemModel(parent)
{
	m_searches.clear();
	mExpression.clear();
}

SearchResultModel::~SearchResultModel(){
}

void SearchResultModel::addSearch(const SearchInfo& search){
#if QT_VERSION<0x050000
#else
    beginResetModel();
#endif

    m_searches.append(search);
    int lineNumber = 0;
    m_searches.last().lineNumberHints.clear();
    for (int i=0;i<search.lines.size();i++){
        lineNumber = search.doc->indexOf(search.lines[i], lineNumber);
        m_searches.last().lineNumberHints << lineNumber;
    }
#if QT_VERSION<0x050000
	reset();
#else
    endResetModel();
#endif
}

void SearchResultModel::clear(){
#if QT_VERSION<0x050000
#else
    beginResetModel();
#endif

    m_searches.clear();
	mExpression.clear();

#if QT_VERSION<0x050000
    reset();
#else
    endResetModel();
#endif

}

void SearchResultModel::removeSearch(const QDocument* doc){
	for (int i=m_searches.size()-1;i>=0;i--)
		if (m_searches[i].doc == doc) 
			m_searches.removeAt(i);
	if(m_searches.isEmpty()) mExpression.clear();
}
int SearchResultModel::columnCount(const QModelIndex & parent) const {
	return parent.isValid()?1:1;
}
int SearchResultModel::rowCount(const QModelIndex &parent) const {
	//return parent.isValid()?0:1;
	if(!parent.isValid()){
		return m_searches.size();
	}else{
		int i=parent.row();
		if(i<m_searches.size()&&((parent.internalId()&(1<<15))==0)){
			return qMin(m_searches[i].lines.size(),1000); // maximum search results limited
		} else return 0;
	}
}
QModelIndex SearchResultModel::index(int row, int column, const QModelIndex &parent)
const
{
	if(parent.isValid()){
		int i=(parent.internalId()&0xFFFF0000)+(1<<15)+row;
		return createIndex(row,column,i);
	}else{
		return createIndex(row,column,(row+1)*(1<<16));
	}
}

QModelIndex SearchResultModel::parent(const QModelIndex &index)
const
{
	quint32 i=index.internalId();
	if((i&(1<<15))>0){
		return createIndex(int(i>>16)-1,0,i&0xFFFF0000);
	}else return QModelIndex();
}

QVariant SearchResultModel::data(const QModelIndex &index, int role) const {
	if (!index.isValid()) return QVariant();
	//if (index.row() >= log.count() || index.row() < 0) return QVariant();
	if (role == Qt::ToolTipRole) return tr("Click to jump to the line");

    if (role != Qt::DisplayRole && role != Qt::CheckStateRole) return QVariant();

	int i=index.internalId();
	int searchIndex = (i>>16)-1;
	if (searchIndex < 0 || searchIndex >= m_searches.size()) return QVariant();
	const SearchInfo& search = m_searches.at(searchIndex); 
	if(i&(1<<15)){
		if (!search.doc) return QVariant();
		int lineIndex = index.row();
        if (lineIndex < 0 || lineIndex > search.lines.size() || lineIndex > search.lineNumberHints.size()){
            if(role==Qt::CheckStateRole)
                return QVariant();
            return "";
        }
        if(role==Qt::CheckStateRole){
            qDebug()<<lineIndex << search.checked.value(lineIndex,true);
            return (search.checked.value(lineIndex,true) ? Qt::Checked : Qt::Unchecked);
        }

		search.lineNumberHints[lineIndex] = search.doc->indexOf(search.lines[lineIndex], search.lineNumberHints[lineIndex]);
        if(search.lineNumberHints[lineIndex] < 0) {
            return "";
        }
		QDocumentLine ln = search.doc->line(search.lineNumberHints[lineIndex]);
		QString temp=prepareResultText(ln.text());

		return QString("Line %1: ").arg(search.lineNumberHints[lineIndex]+1)+temp;
	} else {
        if(role==Qt::CheckStateRole){
            if(search.checked.isEmpty())
                return QVariant();
            bool state=search.checked.first();
            int cnt=search.checked.count(state);
            if(cnt==search.checked.size()){
                return state ? Qt::Checked : Qt::Unchecked;
            }else{
                return Qt::PartiallyChecked;
            }
        }
        REQUIRE_RET(index.row() == searchIndex, QVariant());
		return (search.doc?search.doc->getFileName():tr("File closed")) + QString(" (%1)").arg(search.lines.size());
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
    if (role != Qt::CheckStateRole )
        return false;

    int i=index.internalId();
    int searchIndex = (i>>16)-1;
    if (searchIndex < 0 || searchIndex >= m_searches.size()) return false;
    SearchInfo& search = m_searches[searchIndex];
    if(i&(1<<15)){
        if (!search.doc) return false;
        int lineIndex = index.row();
        if (lineIndex < 0 || lineIndex > search.lines.size() || lineIndex > search.lineNumberHints.size()){
            return false;
        }
        if(role==Qt::CheckStateRole){
            search.checked.replace(lineIndex,(value==Qt::Checked));
            //m_searches.at(searchIndex).checked.replace(lineIndex,(value==Qt::Checked));
        }
         emit dataChanged(index, index);
    }else{
        bool state=(value==Qt::Checked);
        for(int i=0;i<search.checked.size();i++){
            search.checked.replace(i,state);
        }
        int row=search.checked.size()-1;
        int j=(i&0xFFFF0000)+(1<<15)+row;
        QModelIndex endIndex=createIndex(row,0,j);
        emit dataChanged(index,endIndex);
    }

    return true;
}

void SearchResultModel::setSearchExpression(const QString &exp,const bool isCaseSensitive,const bool isWord,const bool isRegExp){
	mExpression=exp;
	mIsCaseSensitive=isCaseSensitive;
	mIsWord=isWord;
	mIsRegExp=isRegExp;
}

QString SearchResultModel::prepareResultText(const QString& text) const{
	QString result;
	QList<QPair<int,int> > placements=getSearchResults(text);
	int second;
	if(placements.size()>0){
		second=0;
	} else return text;
	for(int i=0;i<placements.size();i++){
		int first=placements.at(i).first;
		result.append(text.mid(second,first-second)); // add normal text
		second=placements.at(i).second;
		result.append("|"+text.mid(first,second-first)+"|"); // add highlighted text
	}
	result.append(text.mid(placements.last().second));
	return result;
}

QList<QPair<int,int> > SearchResultModel::getSearchResults(const QString &text) const{
	if(mExpression.isEmpty()) return QList<QPair<int,int> >();
	
	QRegExp m_regexp=generateRegExp(mExpression,mIsCaseSensitive,mIsWord,mIsRegExp);
	
	int i=0;
	QList<QPair<int,int> > result;
	while(i<text.length() && i>-1){
		i=m_regexp.indexIn(text,i);
		if(i>-1){
			if(!result.isEmpty() && result.last().second>i){
				result.last().second=m_regexp.matchedLength()+i;
			} else
				result << qMakePair(i,m_regexp.matchedLength()+i);
			
			i++;
		}
	}
	return result;
}


QDocument* SearchResultModel::getDocument(const QModelIndex &index){
	int i=index.internalId();
	i=(i>>16)-1;
	if (i < 0 || i >= m_searches.size()) return 0;
	if (!m_searches[i].doc) return 0;
	return m_searches[i].doc;
}
int SearchResultModel::getLineNumber(const QModelIndex &index){
	int i=index.internalId();
	if (!(i&(1<<15))) return -1;
	int searchIndex = (i>>16)-1;
	if (searchIndex < 0 || searchIndex >= m_searches.size()) return -1;
	const SearchInfo& search = m_searches.at(searchIndex); 
	if (!search.doc) return -1;
	int lineIndex = index.row();
	if (lineIndex < 0 || lineIndex > search.lines.size() || lineIndex > search.lineNumberHints.size()) return -1;
	search.lineNumberHints[lineIndex] = search.doc->indexOf(search.lines[lineIndex], search.lineNumberHints[lineIndex]);
	return search.lineNumberHints[lineIndex];
}

QVariant SearchResultModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (role != Qt::DisplayRole) return QVariant();
	if (orientation != Qt::Horizontal) return QVariant();
	switch (section) {
	case 0:
		return tr("Results");
	default:
		return QVariant();
	}
}

int SearchResultModel::getNextSearchResultColumn(const QString& text,int col){
	QRegExp m_regexp=generateRegExp(mExpression,mIsCaseSensitive,mIsWord,mIsRegExp);
	
	int i=0;
	int i_old=0;
	while(i<=col && i>-1){
		i=m_regexp.indexIn(text,i);
		if(i>-1) {
			i_old=i;
			i++;
		}
	}
	return i_old;
}
