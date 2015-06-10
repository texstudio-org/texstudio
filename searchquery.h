#ifndef SEARCHQUERY_H
#define SEARCHQUERY_H

#include "mostQtHeaders.h"
#include "searchresultmodel.h"
#include "qdocument.h"


class SearchQuery : public QObject {
	Q_OBJECT
public:
	enum SearchFlag
	{
		NoFlags				= 0x0000,
		SearchParams		= 0x00FF,
		IsCaseSensitive		= 0x0001,
		IsWord				= 0x0002,
		IsRegExp			= 0x0004,
		
		SearchCapabilities	= 0xFF00,
		ScopeChangeAllowed	= 0x0100,
		ReplaceAllowed		= 0x0200,
		SearchAgainAllowed	= 0x0400,
	};
	Q_DECLARE_FLAGS(SearchFlags, SearchFlag)

	SearchQuery(QString expr, QString replaceText, SearchFlags f);
	SearchQuery(QString expr, QString replaceText, bool isCaseSensitive, bool isWord, bool isRegExp);

	bool flag(SearchFlag f) const;
	QString type() { return mType; }

	QString searchExpression() const { return mModel->searchExpression(); }
	SearchResultModel * model() const { return mModel; }
	int getNextSearchResultColumn(QString text, int col) const;
	
public slots:
	void addDocSearchResult(QDocument *doc, QList<QDocumentLineHandle *> search);
	void setReplacementText(QString text);
	
protected:
	void setFlag(SearchFlag f, bool b=true);
	QString mType;
	
private:
	SearchResultModel *mModel;
	SearchFlags searchFlags;
};
Q_DECLARE_OPERATORS_FOR_FLAGS(SearchQuery::SearchFlags)


class LabelSearchQuery : public SearchQuery {
	Q_OBJECT
public:
	LabelSearchQuery(QString label);
};


#endif // SEARCHQUERY_H
