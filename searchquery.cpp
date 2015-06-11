#include "searchquery.h"
#include "latexdocument.h"
// TODO: dependency should be refactored
#include "buildmanager.h"

SearchQuery::SearchQuery(QString expr, QString replaceText, SearchFlags f) : 
	mType(tr("Search")), mScope(CurrentDocumentScope), mModel(0), searchFlags(f)
{
	mModel = new SearchResultModel(this);
	mModel->setSearchExpression(expr, replaceText, flag(IsCaseSensitive), flag(IsWord), flag(IsRegExp));
}

SearchQuery::SearchQuery(QString expr, QString replaceText, bool isCaseSensitive, bool isWord, bool isRegExp) : 
	mType(tr("Search")), mScope(CurrentDocumentScope), mModel(0), searchFlags(NoFlags)
{
	setFlag(IsCaseSensitive, isCaseSensitive);
	setFlag(IsWord, isWord);
	setFlag(IsRegExp, isRegExp);
	if (!expr.isEmpty()) {
		setFlag(ScopeChangeAllowed);
		setFlag(SearchAgainAllowed);
		setFlag(ReplaceAllowed);
	}
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

void SearchQuery::run(LatexDocument *doc)
{
	mModel->removeAllSearches();

	QList<LatexDocument *> docs;
	switch (mScope) {
	case CurrentDocumentScope:
		docs << doc;
		break;
	case GlobalScope:
		docs << doc->parent->getDocuments();
		break;
	case ProjectScope:
		docs << doc->getListOfDocs();
		break;
	default:
		break;
	}
	
	qDebug() << mScope;
	
	foreach(LatexDocument *doc, docs) {
		if (!doc) continue;
		QList<QDocumentLineHandle *> lines;
		for(int l=0; l<doc->lineCount(); l++){
			l = doc->findLineRegExp(searchExpression(), l,
									flag(IsCaseSensitive) ? Qt::CaseSensitive : Qt::CaseInsensitive, flag(IsWord), flag(IsRegExp));
			if (l < 0) break;
			lines << doc->line(l).handle();
		}
		qDebug() << doc->getFileName() << lines.count();

		if (!lines.isEmpty()) { // don't add empty searches
			if (doc->getFileName().isEmpty() && doc->getTemporaryFileName().isEmpty())
				doc->setTemporaryFileName(BuildManager::createTemporaryFileName());
			addDocSearchResult(doc, lines);
		}
	}
}

void SearchQuery::setReplacementText(QString text) {
	mModel->setReplacementText(text);
}


LabelSearchQuery::LabelSearchQuery(QString label) : 
	SearchQuery(label, QString(), IsWord | IsCaseSensitive | SearchAgainAllowed)
{
	mScope = ProjectScope;
	mType = tr("Label Search");
}

void LabelSearchQuery::run(LatexDocument *doc)
{
	mModel->removeAllSearches();
	QString labelText = searchExpression();
	QMultiHash<QDocumentLineHandle*,int> usages = doc->getLabels(labelText);
	usages += doc->getRefs(labelText);
	QHash<QDocument*, QList<QDocumentLineHandle*> > usagesByDocument;
	foreach (QDocumentLineHandle *dlh, usages.keys()) {
		QDocument *doc = dlh->document();
		QList<QDocumentLineHandle*> dlhs = usagesByDocument[doc];
		dlhs.append(dlh);
		usagesByDocument.insert(doc, dlhs);
	}
	
	foreach (QDocument *doc, usagesByDocument.keys()) {
		addDocSearchResult(doc, usagesByDocument.value(doc));
	}
}

