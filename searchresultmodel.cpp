#include "searchresultmodel.h"
#include "qdocument.h"

SearchResultModel::SearchResultModel(QObject *parent)
{
	m_searches.clear();
}

SearchResultModel::~SearchResultModel(){
}

void SearchResultModel::addSearch(QDocumentSearch *newSearch,QString name){
	m_searches.append(newSearch);
	m_files.append(name);
	reset();
}

void SearchResultModel::clear(){
	m_searches.clear();
	m_files.clear();
	reset();
}

void SearchResultModel::removeSearch(QDocumentSearch *search){
	int i=m_searches.indexOf(search);
	m_searches.removeAt(i);
	m_files.removeAt(i);
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
			QDocumentSearch *search=m_searches.at(i);
			return qMin(search->indexedMatchCount(),1000); // maximum search results limited
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
	if (role != Qt::DisplayRole) return QVariant();
	QDocumentSearch* search;
	QString text;
	QDocumentCursor c;
	int i=index.internalId();
	if(i&(1<<15)){
		i=(i>>16)-1;
		search=m_searches.at(i);
		c=search->match(index.row());
		if(c.isValid()&&c.hasSelection()){
			return QString("Line %1: ").arg(c.lineNumber()+1)+c.line().text();
		}else{
			return "";
		}
	} else {
		i=(i>>16)-1;
		search=m_searches.at(i);
		return index.row()<m_files.size() ? m_files.at(index.row())+QString(" (%1)").arg(search->indexedMatchCount()) : "";
	}
}

QString SearchResultModel::getFilename(const QModelIndex &index){
	int i=index.internalId();
	i=(i>>16)-1;
	return i<m_files.size() ? m_files.at(i) : "";
}
int SearchResultModel::getLineNumber(const QModelIndex &index){
	int i=index.internalId();
	QDocumentSearch* search;
	QDocumentCursor c;
	if(i&(1<<15)){
		i=(i>>16)-1;
		search=m_searches.at(i);
		c=search->match(index.row());
		if(c.isValid()&&c.hasSelection()){
			return c.lineNumber();
		}else{
			return -1;
		}
	}else return -1;
}
