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
    searchScopeBox->addItem(tr("Files on disk"), static_cast<uint>(SearchQuery::FilesScope));
	searchScopeBox->setCurrentIndex(ConfigManagerInterface::getInstance()->getOption("Search/ScopeIndex").toInt());
    connect(searchScopeBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeScope(int)));

	searchTypeLabel = new QLabel;
	searchTextLabel = new QLabel;
	QFont font = searchTextLabel->font();
	font.setItalic(true);
	searchTextLabel->setFont(font);
    searchAgainButton = new QPushButton(tr("Update Search"));
	connect(searchAgainButton, SIGNAL(clicked()), this, SLOT(updateSearch()));
	replaceTextEdit = new QLineEdit;
	replaceTextEdit->setClearButtonEnabled(true);
	replaceButton = new QPushButton(tr("Replace all"));
    m_replaceByLabel=new QLabel(tr("Replace by:"));

    // special widgets for search in files
    m_fileFilterBox = new QComboBox;
    m_fileFilterBox->addItem(tr("TeX files")+" (*.tex)");
    m_fileFilterBox->addItem(tr("Bib files")+" (*.bib)");
    m_fileFilterBox->addItem(tr("All files")+" (*)");
    m_fileFilterBox->setEditable(true);
    m_fileFilterBox->setVisible(false);

    connect(m_fileFilterBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeFileFilter(int)));

	hLayout->addWidget(searchScopeBox);

	hLayout->addWidget(searchTypeLabel);
	hLayout->addWidget(searchTextLabel, 1);
	hLayout->addWidget(searchAgainButton);
    hLayout->addWidget(m_replaceByLabel);
	hLayout->addWidget(replaceTextEdit, 1);
	hLayout->addWidget(replaceButton);
    hLayout->addWidget(m_fileFilterBox);

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
    connect(replaceTextEdit, &QLineEdit::textChanged, this, &SearchResultWidget::replaceTextEditChanged);
	connect(replaceTextEdit, SIGNAL(returnPressed()), query, SLOT(replaceAll()));
    connect(replaceButton, &QPushButton::clicked, this, &SearchResultWidget::replaceButtonClicked);

	searchTree->setModel(query->model());
    connect(query, &SearchQuery::runCompleted, this, &SearchResultWidget::searchCompleted);
    adaptGUItoScope();
}

void SearchResultWidget::updateSearch()
{
	if (query) query->setScope(searchScope());
	emit runSearch(query);
}
/*!
 * \brief change UI and update search when mode is changed
 * \param mode
 */
void SearchResultWidget::changeScope(int)
{
    adaptGUItoScope();
    updateSearch();
}
/*!
 * \brief change the file filter for search in file
 * Stop current search and start a new one
 * \param mode
 */
void SearchResultWidget::changeFileFilter(int)
{
    if(query){
        query->setFileFilter(m_fileFilterBox->currentText());
        updateSearch();
    }
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
/*!
 * \brief adapt replace text/current directory to current scope
 */
void SearchResultWidget::adaptGUItoScope()
{
    const auto scope=searchScope();
    if(scope<SearchQuery::FilesScope){
        m_fileFilterBox->setVisible(false);
        m_replaceByLabel->setText(tr("Replace by:"));
        replaceButton->setIcon(QIcon());
        replaceButton->setText(tr("Replace all"));
        replaceTextEdit->setText(query->replacementText());
        replaceTextEdit->setEnabled(true);
    }else{
        m_fileFilterBox->setVisible(true);
        m_replaceByLabel->setText(tr("Search in:"));
        replaceButton->setIcon(getRealIcon("document-open"));
        replaceButton->setText("");
        replaceTextEdit->setText(query->searchFolder());
        replaceTextEdit->setEnabled(false);
    }
}

void SearchResultWidget::clickedSearchResult(const QModelIndex &index)
{

    LatexDocument *doc = qobject_cast<LatexDocument*>(query->model()->getDocument(index));
    int lineNr = query->model()->getLineNumber(index);
    if (lineNr < 0) return;

    if(doc){
        emit jumpToSearchResult(doc, lineNr, query);
    }else{
        // result from search in files
        QString fn=query->model()->getFileName(index);
        emit jumpToFileSearchResult(fn, lineNr, query);
    }
}
/*!
 * \brief handle click on replace button
 * Acts differently depending on the search scope
 * + Current Doc/All Docs/Projects: replace all in txs documents
 * + Files on disk: show folder browse dialog to select the folder where to search
 */
 void SearchResultWidget::replaceButtonClicked()
{
    const auto scope=searchScope();
    if(scope<SearchQuery::FilesScope){
        query->replaceAll();
    }else{
        // search in files
        QString folder=QFileDialog::getExistingDirectory(this, tr("Select folder where to search"),query->searchFolder());
        if(folder.isEmpty()) return;
        query->setSearchFolder(folder);
        replaceTextEdit->setText(folder);
        updateSearch();
    }
}
/*!
 * \brief replaceTextEditChanged slot
 * update query if scope is not FileScope
 * Otherwise only update folder with update button
 * \param text
 */
void SearchResultWidget::replaceTextEditChanged(const QString &text)
{
    if(searchScope()<SearchQuery::FilesScope){
        query->setReplacementText(text);
    }
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
    QPalette::ColorGroup    cg  = (option.state & QStyle::State_Enabled) ? QPalette::Normal : QPalette::Disabled;

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
		size = doCheck(option, option.rect, Qt::Checked).size();

		QRect checkboxRect(option.rect.x(), option.rect.y(), size.width(), size.height());
        QItemDelegate::drawCheck(painter, option, checkboxRect, static_cast<Qt::CheckState>(index.data(Qt::CheckStateRole).toInt()));
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
		int lwidth = UtilsUi::getFmWidth(painter->fontMetrics(), "00000") + 2 * hPadding;
		QRect lineNumberRect = QRect(r.left(), r.top(), lwidth, r.height());
		if (!isSelected) {
			painter->fillRect(lineNumberRect, option.palette.window());
		}
		painter->drawText(lineNumberRect.adjusted(hPadding, 0, -hPadding, 0), Qt::AlignRight | Qt::AlignTop | Qt::TextSingleLine, vLineNumber.toString());
		r.adjust(lwidth + spacing, 0, 0, 0);
	}

	// draw text
    QString text = index.data().toString();
    text.replace("\t"," ");
	QList<SearchMatch> matches = index.data(SearchResultModel::MatchesRole).value<QList<SearchMatch> >();

	int pos = 0;
	foreach (SearchMatch match, matches) {
		// text before match
		QString part = text.mid(pos, match.pos - pos);
        int w = UtilsUi::getFmWidth(painter->fontMetrics(), part);
		painter->drawText(r, Qt::AlignLeft | Qt::AlignTop | Qt::TextSingleLine, part);
		r.setLeft(r.left() + w + 1);
		// matched text
		part = text.mid(match.pos, match.length);
		w = UtilsUi::getFmWidth(painter->fontMetrics(), part);
		painter->save();
        if(darkMode){
            painter->fillRect(QRect(r.left(), r.top(), w, r.height()), QBrush(QColor(255, 239, 11)));
            painter->setPen(Qt::black);
        }else{
            painter->fillRect(QRect(r.left(), r.top(), w, r.height()), QBrush(QColor(255, 239, 11)));
            painter->setPen(option.palette.color(cg, QPalette::Text));
        }
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
