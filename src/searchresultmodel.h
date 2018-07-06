#ifndef SEARCHRESULTMODEL_H
#define SEARCHRESULTMODEL_H

#include "mostQtHeaders.h"

class QDocument;
class QDocumentLine;
class QDocumentLineHandle;
struct SearchInfo {
	QPointer<QDocument> doc;
	QList<QDocumentLineHandle *> lines;
	QList<bool> checked;
	mutable QList<int> lineNumberHints;
};

struct SearchMatch {
	int pos;
	int length;
};

class SearchResultModel : public QAbstractItemModel
{
	Q_OBJECT

public:
	enum UserRoles {LineNumberRole = Qt::UserRole, MatchesRole};

	SearchResultModel(QObject *parent = 0);
	~SearchResultModel();

	QVariant data(const QModelIndex &index, int role) const;
	QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
	QModelIndex parent(const QModelIndex &index) const;
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	bool setData(const QModelIndex &index, const QVariant &value, int role);

	void addSearch(const SearchInfo &search);
	void removeSearch(const QDocument *doc);
	void removeAllSearches();
	QList<SearchInfo> getSearches();
	void clear();
	QDocument *getDocument(const QModelIndex &index);
	int getLineNumber(const QModelIndex &index);
	void setSearchExpression(const QString &exp, const bool isCaseSensitive, const bool isWord, const bool isRegExp);
	void setSearchExpression(const QString &exp, const QString &repl, const bool isCaseSensitive, const bool isWord, const bool isRegExp);
	QString searchExpression()
	{
		return mExpression;
	}
	int getNextSearchResultColumn(const QString &text, int col);
	void getSearchConditions(bool &isCaseSensitive, bool &isWord, bool &isRegExp)
	{
		isWord = mIsWord;
		isCaseSensitive = mIsCaseSensitive;
		isRegExp = mIsRegExp;
	}
	void setReplacementText(QString text) { mReplacementText = text; }
	QString replacementText() { return mReplacementText; }

	void setAllowPartialSelection(bool b) { mAllowPartialSelection = b; }

	virtual QList<SearchMatch> getSearchMatches(const QDocumentLine &docline) const;

private:
	QVariant dataForResultEntry(const SearchInfo &search, int lineIndex, int role) const;
	QVariant dataForSearchResult(const SearchInfo &search, int role) const;
	QString prepareReplacedText(const QDocumentLine &docline) const;

	QList< SearchInfo > m_searches;
	QString mExpression, mReplacementText;
	bool mIsWord, mIsCaseSensitive, mIsRegExp;
	bool mAllowPartialSelection;
	QFont mLineFont;
};

Q_DECLARE_METATYPE(SearchMatch);
Q_DECLARE_METATYPE(QList<SearchMatch>);


class LabelSearchResultModel : public SearchResultModel
{
	Q_OBJECT

public:
	LabelSearchResultModel(QObject *parent = 0);

	QList<SearchMatch> getSearchMatches(const QDocumentLine &docline) const;
};

#endif // SEARCHRESULTMODEL_H
