#include "searchquery.h"

SearchQuery::SearchQuery(QString expr, QString replaceText, SearchFlags f)
{
	searchFlags = f;
	mModel = new SearchResultModel(this);
	mModel->setSearchExpression(expr, replaceText, flag(IsCaseSensitive), flag(IsWord), flag(IsRegExp));
}

SearchQuery::SearchQuery(QString expr, QString replaceText, bool isCaseSensitive, bool isWord, bool isRegExp)
{
	searchFlags = NoFlags;
	setFlag(IsCaseSensitive, isCaseSensitive);
	setFlag(IsWord, isWord);
	setFlag(IsRegExp, isRegExp);
	if (!expr.isEmpty()) {
		setFlag(ScopeChangeAllowed);
		setFlag(SearchAgainAllowed);
		setFlag(ReplaceAllowed);
	}
	mType = tr("Search");
	mModel = new SearchResultModel(this);
	mModel->setSearchExpression(expr, replaceText, flag(IsCaseSensitive), flag(IsWord), flag(IsRegExp));
}

bool SearchQuery::flag(SearchQuery::SearchFlag f) const
{
	return searchFlags & f;
}

void SearchQuery::setFlag(SearchQuery::SearchFlag f, bool b)
{
	if (b) {
		searchFlags |= f;
	} else {
		searchFlags &= ~f;
	}
}

void SearchQuery::addDocSearchResult(QDocument *doc, QList<QDocumentLineHandle *> lines) {
	SearchInfo search;
	search.doc = doc;
	search.lines = lines;
	for (int i = 0; i < lines.count(); i++) {
		search.checked << true;
	}
	mModel->addSearch(search);
}

int SearchQuery::getNextSearchResultColumn(QString text, int col) const {
	return mModel->getNextSearchResultColumn(text, col);
}

void SearchQuery::setReplacementText(QString text) {
	mModel->setReplacementText(text);
}


LabelSearchQuery::LabelSearchQuery(QString label) : 
	SearchQuery(label, QString(), SearchQuery::IsWord | SearchQuery::IsCaseSensitive)
{
	mType = tr("Label Search");
}

