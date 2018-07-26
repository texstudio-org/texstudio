#include "searchresultwidget.h"
#include "latexdocument.h"
#include "configmanagerinterface.h"


SearchResultWidget::SearchResultWidget(QWidget *parent) : QWidget(parent), query(nullptr)
{
	query = new SearchQuery("", "", SearchQuery::NoFlags);
	QString editorFontFamily = ConfigManagerInterface::getInstance()->getOption("Editor/Font Family").toString();
	SearchTreeDelegate *searchDelegate = new SearchTreeDelegate(editorFontFamily, this);

	QHBoxLayout *hLayout = new QHBoxLayout;
	hLayout->setContentsMargins(4, 2, 4, 1);
	hLayout->setSpacing(8);

	searchScopeBox = new QComboBox;
	searchScopeBox->setEditable(false);
	searchScopeBox->addItem(tr("Current Doc"), static_cast<uint>(SearchQuery::CurrentDocumentScope));
	searchScopeBox->addItem(tr("All Docs"), static_cast<uint>(SearchQuery::GlobalScope));
	searchScopeBox->addItem(tr("Project"), static_cast<uint>(SearchQuery::ProjectScope));
	searchScopeBox->setCurrentIndex(ConfigManagerInterface::getInstance()->getOption("Search/ScopeIndex").toInt());
	connect(searchScopeBox, SIGNAL(currentIndexChanged(int)), SLOT(updateSearch()));

	searchTypeLabel = new QLabel;
	searchTextLabel = new QLabel;
	QFont font = searchTextLabel->font();
	font.setItalic(true);
	searchTextLabel->setFont(font);
    searchAgainButton = new QPushButton(tr("Update Search"));
	connect(searchAgainButton, SIGNAL(clicked()), this, SLOT(updateSearch()));
	replaceTextEdit = new QLineEdit;
#if QT_VERSION >= 0x050200
	replaceTextEdit->setClearButtonEnabled(true);
#endif
	replaceButton = new QPushButton(tr("Replace all"));

	hLayout->addWidget(searchScopeBox);

	hLayout->addWidget(searchTypeLabel);
	hLayout->addWidget(searchTextLabel, 1);
	hLayout->addWidget(searchAgainButton);
	hLayout->addWidget(new QLabel(tr("Replace by:")));
	hLayout->addWidget(replaceTextEdit, 1);
	hLayout->addWidget(replaceButton);

	searchTree = new QTreeView(this);
	searchTree->header()->hide();
	searchTree->setUniformRowHeights(true);
	searchTree->setItemDelegate(searchDelegate);
	searchTree->setFrameShape(QFrame::NoFrame);

	QVBoxLayout *vLayout = new QVBoxLayout();
	setLayout(vLayout);
	vLayout->setContentsMargins(0, 0, 0, 0);
	vLayout->setSpacing(0);

	vLayout->addLayout(hLayout);
	QFrame *hLine = new QFrame();
	hLine->setFrameShape(QFrame::HLine);
	vLayout->addWidget(hLine);
	vLayout->addWidget(searchTree, 1);

	QAction *actExpand = new QAction(tr("Expand All"), this);
	connect(actExpand, SIGNAL(triggered()), searchTree, SLOT(expandAll()));
	searchTree->addAction(actExpand);
	QAction *actCollapse = new QAction(tr("Collapse All"), this);
	connect(actCollapse, SIGNAL(triggered()), searchTree, SLOT(collapseAll()));
	searchTree->addAction(actCollapse);
	QAction *actClear = new QAction(tr("Clear"), this);
	connect(actClear, SIGNAL(triggered()), this, SLOT(clearSearch()));
	searchTree->addAction(actClear);
	searchTree->setContextMenuPolicy(Qt::ActionsContextMenu);

	connect(searchTree, SIGNAL(clicked(QModelIndex)), this, SLOT(clickedSearchResult(QModelIndex)));
}

/*!
 * The widget takes ownership of the result. It will be destoyed when a new SearchResult is set
 */
void SearchResultWidget::setQuery(SearchQuery *sq)
{
    delete query;
	query = sq;
	query->setParent(this);
	searchTypeLabel->setText(query->type() + ":");
	searchTextLabel->setText(query->searchExpression());
	searchScopeBox->setEnabled(query->flag(SearchQuery::ScopeChangeAllowed));
	updateSearchScopeBox(query->scope());
	searchAgainButton->setEnabled(query->flag(SearchQuery::SearchAgainAllowed));
	bool replaceAllowed = query->flag(SearchQuery::ReplaceAllowed);
	replaceTextEdit->setEnabled(replaceAllowed);
	replaceTextEdit->setText(query->replacementText());
	replaceButton->setEnabled(replaceAllowed);
	connect(replaceTextEdit, SIGNAL(textChanged(QString)), query, SLOT(setReplacementText(QString)));
	connect(replaceTextEdit, SIGNAL(returnPressed()), query, SLOT(replaceAll()));
	connect(replaceButton, SIGNAL(clicked()), query, SLOT(replaceAll()));

	searchTree->setModel(query->model());
	connect(query, SIGNAL(runCompleted()), this, SLOT(searchCompleted()));
}

void SearchResultWidget::updateSearch()
{
	if (query) query->setScope(searchScope());
	emit runSearch(query);
}

void SearchResultWidget::searchCompleted()
{
	if (query && query->model()->rowCount(QModelIndex()) == 1) {
		// only one top-level element. i.e. file
		searchTree->expandAll();
	}
}

void SearchResultWidget::updateSearchExpr(QString searchText){
	searchTextLabel->setText(searchText);
}

void SearchResultWidget::saveConfig()
{
	ConfigManagerInterface::getInstance()->setOption("Search/ScopeIndex", searchScopeBox->currentIndex());
}

void SearchResultWidget::updateSearchScopeBox(SearchQuery::Scope sc)
{
	int index = searchScopeBox->findData(sc);
	if (index >= 0)
		searchScopeBox->setCurrentIndex(index);
}

void SearchResultWidget::clickedSearchResult(const QModelIndex &index)
{

	QDocument *doc = query->model()->getDocument(index);
	int lineNr = query->model()->getLineNumber(index);
	if (!doc || lineNr < 0) {
		return;
	}
	emit jumpToSearchResult(doc, lineNr, query);
}

void SearchResultWidget::clearSearch()
{
	setQuery(new SearchQuery("", "", SearchQuery::NoFlags));
}

SearchQuery::Scope SearchResultWidget::searchScope() const
{
	return static_cast<SearchQuery::Scope>(searchScopeBox->itemData(searchScopeBox->currentIndex()).toUInt());
}


//====================================================================
// CustomDelegate for search results
//====================================================================
SearchTreeDelegate::SearchTreeDelegate(QString editorFontFamily, QObject *parent): QItemDelegate(parent), m_editorFontFamily(editorFontFamily)
{
	;
}

void SearchTreeDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                               const QModelIndex &index) const
{
	QPalette::ColorGroup    cg  = option.state & QStyle::State_Enabled ? QPalette::Normal : QPalette::Disabled;

	/*if( cg == QPalette::Normal && !(option.state & QStyle::State_Active) )
	    cg = QPalette::Inactive;*/

	painter->save();
	if (option.state & QStyle::State_Selected) {
		painter->fillRect(option.rect, option.palette.brush(cg, QPalette::Highlight));
		painter->setPen(option.palette.color(cg, QPalette::HighlightedText));
	} else {
		painter->setPen(option.palette.color(cg, QPalette::Text));
	}
	QRect r = option.rect;  // active area. Will be moved during drawing actions

	// draw checkbox
	QSize size;
	if (index.data(Qt::CheckStateRole).isValid()) {
#if QT_VERSION >= 0x050200  /* QItemDelegate::check is an internal function which has been renamed (maybe already in Qt5.2?) */
		size = doCheck(option, option.rect, Qt::Checked).size();
#else
		size = check(option, option.rect, Qt::Checked).size();
#endif
		QRect checkboxRect(option.rect.x(), option.rect.y(), size.width(), size.height());
		QItemDelegate::drawCheck(painter, option, checkboxRect, (Qt::CheckState) index.data(Qt::CheckStateRole).toInt());
	}
	int spacing = 2;
	r.adjust(size.width() + spacing, 0, 0, 0);

	if (index.data().toString().isEmpty()) {
		painter->restore();
		return;
	}

	// draw filename line
	bool isFileName = !index.parent().isValid();
	if (isFileName) {
		QString text = index.data().toString();
		QFont font = painter->font();
		font.setBold(true);
		painter->setFont(font);
		painter->drawText(r, Qt::AlignLeft | Qt::AlignTop | Qt::TextSingleLine, text);
		painter->restore();
		return;
	}

	// draw regular line
	bool isSelected = option.state & QStyle::State_Selected;
	if (!m_editorFontFamily.isEmpty()) {
		QFont font = painter->font();
		font.setFamily(m_editorFontFamily);
		painter->setFont(font);
	}

	// draw line number
	QVariant vLineNumber = index.data(SearchResultModel::LineNumberRole);
	if (vLineNumber.isValid()) {
		int hPadding = 1;
		int lwidth = painter->fontMetrics().width("00000") + 2 * hPadding;
		QRect lineNumberRect = QRect(r.left(), r.top(), lwidth, r.height());
		if (!isSelected) {
			painter->fillRect(lineNumberRect, option.palette.window());
		}
		painter->drawText(lineNumberRect.adjusted(hPadding, 0, -hPadding, 0), Qt::AlignRight | Qt::AlignTop | Qt::TextSingleLine, vLineNumber.toString());
		r.adjust(lwidth + spacing, 0, 0, 0);
	}

	// draw text
	QString text = index.data().toString();
	QList<SearchMatch> matches = index.data(SearchResultModel::MatchesRole).value<QList<SearchMatch> >();

	int pos = 0;
	foreach (SearchMatch match, matches) {
		// text before match
		QString part = text.mid(pos, match.pos - pos);
		int w = painter->fontMetrics().width(part);
		painter->drawText(r, Qt::AlignLeft | Qt::AlignTop | Qt::TextSingleLine, part);
		r.setLeft(r.left() + w + 1);
		// matched text
		part = text.mid(match.pos, match.length);
		w = painter->fontMetrics().width(part);
		painter->save();
		painter->fillRect(QRect(r.left(), r.top(), w, r.height()), QBrush(QColor(255, 239, 11)));
		painter->setPen(option.palette.color(cg, QPalette::Text));
		painter->drawText(r, Qt::AlignLeft | Qt::AlignTop | Qt::TextSingleLine, part);
		painter->restore();
		r.setLeft(r.left() + w + 1);
		pos = match.pos + match.length;
	}
	if (pos < text.length()) {
		// text after last match
		QString part = text.mid(pos);
		painter->drawText(r, Qt::AlignLeft | Qt::AlignTop | Qt::TextSingleLine, part);
	}
	painter->restore();
}

QSize SearchTreeDelegate::sizeHint(const QStyleOptionViewItem &option,
                                   const QModelIndex &index) const
{
	// TODO: the size hint is not exact because the with of the checkbox is missing and
	// result lines do not use option.font but m_editorFontFamily
	QFontMetrics fontMetrics = option.fontMetrics;
	QRect rect = fontMetrics.boundingRect(index.data().toString());
	return QSize(rect.width(), rect.height());
}
