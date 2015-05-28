#include "searchresultwidget.h"

#include "qdocument.h"
#include "latexdocument.h"


SearchResultWidget::SearchResultWidget(QWidget *parent) : QWidget(parent) {
	searchResultModel = new SearchResultModel(this);
	SearchTreeDelegate *searchDelegate = new SearchTreeDelegate(this);

	QHBoxLayout *hLayout = new QHBoxLayout;
	hLayout->setContentsMargins(4, 2, 4, 2);
	hLayout->setSpacing(8);

	searchScopeBox = new QComboBox;
	searchScopeBox->setEditable(false);
	searchScopeBox->addItem(tr("Current Doc"));
	searchScopeBox->addItem(tr("All Docs"));
	searchScopeBox->addItem(tr("Project"));
	connect(searchScopeBox, SIGNAL(currentIndexChanged(int)), SIGNAL(updateTheSearch(int)));


	searchTextLabel = new QLabel;
	QFont font = searchTextLabel->font();
	font.setItalic(true);
	searchTextLabel->setFont(font);
	searchAgainButton = new QPushButton(tr("Search Again"));
	connect(searchAgainButton, SIGNAL(clicked()), this, SLOT(updateSearch()));
	replaceTextEdit = new QLineEdit;
	connect(replaceTextEdit, SIGNAL(textChanged(QString)), this, SLOT(replaceTextChanged(QString)));
	replaceButton = new QPushButton(tr("Replace all"));
	connect(replaceButton, SIGNAL(clicked()), this, SLOT(replaceAll()));

	hLayout->addWidget(searchScopeBox);
	hLayout->addWidget(new QLabel(tr("Search:")));
	hLayout->addWidget(searchTextLabel, 1);
	hLayout->addWidget(searchAgainButton);
	hLayout->addWidget(new QLabel(tr("Replace by:")));
	hLayout->addWidget(replaceTextEdit, 1);
	hLayout->addWidget(replaceButton);

	searchTree = new QTreeView(this);
	searchTree->header()->hide();
	searchTree->setUniformRowHeights(true);
	searchTree->setModel(searchResultModel);
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

	connect(searchTree, SIGNAL(clicked(QModelIndex)), this, SLOT(clickedSearchResult(QModelIndex)));
}

SearchResultWidget::~SearchResultWidget() {

}

void SearchResultWidget::replaceTextChanged(QString text) {
	searchResultModel->setReplacementText(text);
}

void SearchResultWidget::updateSearch() {
	emit updateTheSearch(searchScopeBox->currentIndex());
}

void SearchResultWidget::replaceAll() {
	QList<SearchInfo> searches = searchResultModel->getSearches();
	QString replaceText = replaceTextEdit->text();
	bool isWord, isCase, isReg;
	searchResultModel->getSearchConditions(isCase, isWord, isReg);
	foreach (SearchInfo search, searches) {
		LatexDocument *doc = qobject_cast<LatexDocument *>(search.doc.data());
		if (!doc) {
			continue;
		}
		QDocumentCursor *cur = new QDocumentCursor(doc);
		for (int i=0; i<search.checked.size(); i++) {
			if (search.checked.value(i, false)) {
				QDocumentLineHandle *dlh = search.lines.value(i, 0);
				if (dlh) {
					QList<QPair<int, int> > results = searchResultModel->getSearchResults(dlh->text());
					if (!results.isEmpty()) {
						QPair<int, int> elem;
						int offset = 0;
						foreach (elem, results) {
							if (isReg) {
								QRegExp rx(searchResultModel->searchExpression(), isCase ? Qt::CaseSensitive : Qt::CaseInsensitive);
								QString txt = dlh->text();
								QString newText = txt.replace(rx, replaceText);
								int lineNr = doc->indexOf(dlh, search.lineNumberHints.value(i, -1));
								cur->select(lineNr, elem.first + offset, lineNr, elem.second + offset);
								newText = newText.mid(elem.first);
								newText.chop(txt.length() - elem.second - 1);
								cur->replaceSelectedText(newText);
								offset += newText.length() - elem.second + elem.first;
							} else {
								// simple replacement
								int lineNr = doc->indexOf(dlh, search.lineNumberHints.value(i, -1));
								cur->select(lineNr, elem.first + offset, lineNr, elem.second + offset);
								cur->replaceSelectedText(replaceText);
								offset += replaceText.length() - elem.second + elem.first;
							}
						}
					}
				}
			}
		}
		delete cur;
	}
}

void SearchResultWidget::clickedSearchResult(const QModelIndex &index) {
	QDocument *doc = searchResultModel->getDocument(index);
	if (!searchResultModel->parent(index).isValid()) {
		return;
	}
	if (!doc) {
		return;
	}
	emit jumpToSearch(doc, searchResultModel->getLineNumber(index));
}

void SearchResultWidget::addSearch(QList<QDocumentLineHandle *> lines, QDocument *doc) {
	SearchInfo search;
	search.doc = doc;
	search.lines = lines;
	for (int i = 0; i < lines.count(); i++) {
		search.checked << true;
	}
	searchResultModel->addSearch(search);
}

void SearchResultWidget::clearSearch() {
	searchResultModel->clear();
	setScopeChangeAllowed(true);
	setSearchAgainAllowed(true);
	setReplaceAllowed(true);
}

void SearchResultWidget::setScopeChangeAllowed(bool b) {
	searchScopeBox->setEnabled(b);
}

void SearchResultWidget::setSearchAgainAllowed(bool b) {
	searchAgainButton->setEnabled(b);
}

void SearchResultWidget::setReplaceAllowed(bool b) {
	replaceTextEdit->setEnabled(b);
	replaceButton->setEnabled(b);
}

void SearchResultWidget::setSearchExpression(QString exp, QString replaceText, bool isCase, bool isWord,
        bool isRegExp) {
	replaceTextEdit->setText(replaceText);
	searchTextLabel->setText(exp);
	searchResultModel->setSearchExpression(exp, replaceText, isCase, isWord, isRegExp);
}

void SearchResultWidget::setSearchExpression(QString exp, bool isCase, bool isWord, bool isRegExp) {
	searchTextLabel->setText(exp);
	searchResultModel->setSearchExpression(exp, isCase, isWord, isRegExp);
}

QString SearchResultWidget::searchExpression() const {
	return searchResultModel->searchExpression();
}

int SearchResultWidget::getNextSearchResultColumn(QString text, int col) {
	return searchResultModel->getNextSearchResultColumn(text, col);
}

int SearchResultWidget::getSearchScope() const {
	return searchScopeBox->currentIndex();
}



//====================================================================
// CustomDelegate for search results
//====================================================================
SearchTreeDelegate::SearchTreeDelegate(QObject *parent): QItemDelegate(parent) {
	;
}

void SearchTreeDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                               const QModelIndex &index) const {
	QPalette::ColorGroup    cg  = option.state & QStyle::State_Enabled ? QPalette::Normal : QPalette::Disabled;

	/*if( cg == QPalette::Normal && !(option.state & QStyle::State_Active) )
	    cg = QPalette::Inactive;*/

	if (option.state & QStyle::State_Selected) {
		painter->fillRect(option.rect, option.palette.brush(cg, QPalette::Highlight));
		painter->setPen(option.palette.color(cg, QPalette::HighlightedText));
	} else {
		painter->setPen(option.palette.color(cg, QPalette::Text));
	}

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

	if (index.data().toString().isEmpty()) {
		return;
	}
	painter->save();
	
	QRect r = option.rect;
	int spacing = 2;
	r.adjust(size.width() + spacing, 0, 0, 0);
	bool isSelected = option.state & QStyle::State_Selected;
	
	// draw line number 
	QVariant vLineNumber = index.data(SearchResultModel::LineNumberRole);
	if (vLineNumber.isValid()) {
		int lwidth = option.fontMetrics.width("00000");
		QRect lineNumberRect = QRect(r.left(), r.top(), lwidth, r.height());
		if (!isSelected) {
			painter->fillRect(lineNumberRect, option.palette.alternateBase());
		}
		painter->drawText(lineNumberRect, Qt::AlignRight | Qt::AlignTop | Qt::TextSingleLine, vLineNumber.toString());
		r.adjust(lwidth + spacing, 0, 0, 0);
	}
	// draw text
	QString text = index.data().toString();
	QStringList textList = text.split("|");
	for (int i=0; i<textList.size(); i++) {
		QString temp = textList.at(i);
		int w = option.fontMetrics.width(temp);
		if (i % 2 && !isSelected) {
			painter->fillRect(QRect(r.left(), r.top(), w, r.height()), QBrush(Qt::yellow));
		}
		painter->drawText(r, Qt::AlignLeft | Qt::AlignTop | Qt::TextSingleLine, temp);
		r.setLeft(r.left() + w + 1);
	}
	painter->restore();
}

QSize SearchTreeDelegate::sizeHint(const QStyleOptionViewItem &option,
                                   const QModelIndex &index) const {
	QFontMetrics fontMetrics = option.fontMetrics;
	QRect rect = fontMetrics.boundingRect(index.data().toString());
	return QSize(rect.width(), rect.height());
}


