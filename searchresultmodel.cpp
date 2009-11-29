#include "searchresultmodel.h"
#include "qdocument.h"

SearchResultModel::SearchResultModel(QObject *)
{
	m_searches.clear();
        mExpression.clear();
}

SearchResultModel::~SearchResultModel(){
}

void SearchResultModel::addSearch(QList<QDocumentLineHandle *>newSearch,QString name){
	m_searches.append(newSearch);
	m_files.append(name);
	reset();
}

void SearchResultModel::clear(){
	m_searches.clear();
	m_files.clear();
        mExpression.clear();
	reset();
}

void SearchResultModel::removeSearch(QString name){
        int i=m_files.indexOf(name);
	m_searches.removeAt(i);
	m_files.removeAt(i);
        if(m_files.isEmpty()) mExpression.clear();
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
                        QList<QDocumentLineHandle *> search=m_searches.at(i);
                        return qMin(search.size(),1000); // maximum search results limited
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
        QList<QDocumentLineHandle *> search;
        QDocumentLineHandle *c;
	int i=index.internalId();
	if(i&(1<<15)){
		i=(i>>16)-1;
		search=m_searches.at(i);
                c=search.value(index.row(),0);
                if(c){
                        QDocumentLine ln(c);
                        QString temp=prepareResulText(ln.text());
                        return QString("Line %1: ").arg(ln.lineNumber()+1)+temp;
		}else{
			return "";
		}
	} else {
		i=(i>>16)-1;
		search=m_searches.at(i);
                return index.row()<m_files.size() ? m_files.at(index.row())+QString(" (%1)").arg(search.size()) : "";
	}
}


void SearchResultModel::setSearchExpression(const QString &exp,const bool isCaseSensitive,const bool isWord,const bool isRegExp){
    mExpression=exp;
    mIsCaseSensitive=isCaseSensitive;
    mIsWord=isWord;
    mIsRegExp=isRegExp;
}

QString SearchResultModel::prepareResulText(QString text) const{
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
    Qt::CaseSensitivity cs= mIsCaseSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive;
    QRegExp m_regexp;
    if ( mIsRegExp )
    {
        m_regexp = QRegExp(mExpression, cs, QRegExp::RegExp);
    } else if ( mIsWord ) {
        //todo: screw this? it prevents searching of "world!" and similar things
        //(qtextdocument just checks the surrounding character when searching for whole words, this would also allow wholewords|regexp search)
        m_regexp = QRegExp(
                QString("\\b%1\\b").arg(QRegExp::escape(mExpression)),
                cs,
                QRegExp::RegExp
                );
    } else {
        m_regexp = QRegExp(mExpression, cs, QRegExp::FixedString);
    }

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


QString SearchResultModel::getFilename(const QModelIndex &index){
	int i=index.internalId();
	i=(i>>16)-1;
	return i<m_files.size() ? m_files.at(i) : "";
}
int SearchResultModel::getLineNumber(const QModelIndex &index){
	int i=index.internalId();
        QList<QDocumentLineHandle*> search;
        QDocumentLineHandle* c;
	if(i&(1<<15)){
		i=(i>>16)-1;
		search=m_searches.at(i);
                c=search.value(index.row(),0);
                if(c){
                        QDocumentLine ln(c);
                        return ln.lineNumber();
		}else{
			return -1;
		}
	}else return -1;
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
