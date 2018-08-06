#include "searchquery.h"
#include "latexdocument.h"
// TODO: dependency should be refactored
#include "buildmanager.h"

SearchQuery::SearchQuery(QString expr, QString replaceText, SearchFlags f) :
    mType(tr("Search")), mScope(CurrentDocumentScope), mModel(nullptr), searchFlags(f)
{
	mModel = new SearchResultModel(this);
	mModel->setSearchExpression(expr, replaceText, flag(IsCaseSensitive), flag(IsWord), flag(IsRegExp));
}

SearchQuery::SearchQuery(QString expr, QString replaceText, bool isCaseSensitive, bool isWord, bool isRegExp) :
    mType(tr("Search")), mScope(CurrentDocumentScope), mModel(nullptr), searchFlags(NoFlags)
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

void SearchQuery::addDocSearchResult(QDocument *doc, QList<QDocumentLineHandle *> lines)
{
	SearchInfo search;
	search.doc = doc;
	search.lines = lines;
	for (int i = 0; i < lines.count(); i++) {
		search.checked << true;
	}
	mModel->addSearch(search);
}

int SearchQuery::getNextSearchResultColumn(QString text, int col) const
{
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

	foreach (LatexDocument *doc, docs) {
		if (!doc) continue;
		QList<QDocumentLineHandle *> lines;
		for (int l = 0; l < doc->lineCount(); l++) {
			l = doc->findLineRegExp(searchExpression(), l,
			                        flag(IsCaseSensitive) ? Qt::CaseSensitive : Qt::CaseInsensitive, flag(IsWord), flag(IsRegExp));
			if (l < 0) break;
			lines << doc->line(l).handle();
		}

		if (!lines.isEmpty()) { // don't add empty searches
			if (doc->getFileName().isEmpty() && doc->getTemporaryFileName().isEmpty())
				doc->setTemporaryFileName(BuildManager::createTemporaryFileName());
			addDocSearchResult(doc, lines);
		}
	}
	emit runCompleted();
}

void SearchQuery::setReplacementText(QString text)
{
	mModel->setReplacementText(text);
}

QString SearchQuery::replacementText()
{
	return mModel->replacementText();
}
void SearchQuery::setExpression(QString expr){
	mModel->setSearchExpression(expr, flag(IsCaseSensitive) ? Qt::CaseSensitive : Qt::CaseInsensitive, flag(IsWord), flag(IsRegExp));
}

void SearchQuery::replaceAll()
{
	QList<SearchInfo> searches = mModel->getSearches();
	QString replaceText = mModel->replacementText();
	bool isWord, isCase, isReg;
	mModel->getSearchConditions(isCase, isWord, isReg);
	foreach (SearchInfo search, searches) {
		LatexDocument *doc = qobject_cast<LatexDocument *>(search.doc.data());
		if (!doc) {
			continue;
		}
		QDocumentCursor *cur = new QDocumentCursor(doc);
		for (int i = 0; i < search.checked.size(); i++) {
			if (search.checked.value(i, false)) {
				QDocumentLineHandle *dlh = search.lines.value(i, 0);
				if (dlh) {
					if (isReg) {
						QRegExp rx(searchExpression(), isCase ? Qt::CaseSensitive : Qt::CaseInsensitive);
						QString txt = dlh->text();
						QString newText = txt;
						newText.replace(rx, replaceText);
						int lineNr = doc->indexOf(dlh, search.lineNumberHints.value(i, -1));
						cur->select(lineNr, 0, lineNr, txt.length());
						cur->replaceSelectedText(newText);
					} else {
						// simple replacement
						QList<SearchMatch> results = mModel->getSearchMatches(QDocumentLine(dlh));
						if (!results.isEmpty()) {
							int lineNr = doc->indexOf(dlh, search.lineNumberHints.value(i, -1));
							int offset = 0;
							foreach (const SearchMatch &match, results) {
								cur->select(lineNr, offset + match.pos, lineNr, offset + match.pos + match.length);
								cur->replaceSelectedText(replaceText);
								offset += replaceText.length() - match.length;
							}
						}
					}
				}
			}
		}
		delete cur;
	}
}


LabelSearchQuery::LabelSearchQuery(QString label) :
	SearchQuery(label, label, IsWord | IsCaseSensitive | SearchAgainAllowed | ReplaceAllowed)
{
	mModel = new LabelSearchResultModel(this);
	mModel->setSearchExpression(label, label, flag(IsCaseSensitive), flag(IsWord), flag(IsRegExp));

	mScope = ProjectScope;
	mType = tr("Label Search");
	mModel->setAllowPartialSelection(false);
}

void LabelSearchQuery::run(LatexDocument *doc)
{
	mModel->removeAllSearches();
	QString labelText = searchExpression();
	QMultiHash<QDocumentLineHandle *, int> usages = doc->getLabels(labelText);
	usages += doc->getRefs(labelText);
	QHash<QDocument *, QList<QDocumentLineHandle *> > usagesByDocument;
	foreach (QDocumentLineHandle *dlh, usages.keys()) {
		QDocument *doc = dlh->document();
		QList<QDocumentLineHandle *> dlhs = usagesByDocument[doc];
		dlhs.append(dlh);
		usagesByDocument.insert(doc, dlhs);
	}

	foreach (QDocument *doc, usagesByDocument.keys()) {
		addDocSearchResult(doc, usagesByDocument.value(doc));
	}

	emit runCompleted();
}

void LabelSearchQuery::replaceAll()
{
	QList<SearchInfo> searches = mModel->getSearches();
	QString oldLabel = searchExpression();
	QString newLabel = mModel->replacementText();
	foreach (SearchInfo search, searches) {
		LatexDocument *doc = qobject_cast<LatexDocument *>(search.doc.data());
		if (doc) {
			doc->replaceLabelsAndRefs(oldLabel, newLabel);
		}
	}
}

