#include "symbolwidget.h"
#include "symbollistmodel.h"
#include "symbollistview.h"
#include "proxymodels.h"
#include "configmanagerinterface.h"
#include "utilsUI.h"
#include <QSortFilterProxyModel>


SymbolWidget::SymbolWidget(SymbolListModel *model, bool &insertUnicode, QWidget *parent) : QWidget(parent), insertUnicode(insertUnicode)
{
	setupData(model);

	QVBoxLayout *vLayout = new QVBoxLayout();
	setLayout(vLayout);
    splitter=new QSplitter(Qt::Vertical);
    vLayout->addWidget(splitter);

    QWidget *frame=new QWidget();
    vLayout = new QVBoxLayout();
    frame->setLayout(vLayout);
    splitter->addWidget(frame);
	vLayout->setContentsMargins(0, 0, 0, 0);
	vLayout->setSpacing(0);
	setupFavoritesArea(vLayout);

    frame=new QWidget();
    vLayout = new QVBoxLayout();
    frame->setLayout(vLayout);
    splitter->addWidget(frame);
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(0);
	setupMostUsedArea(vLayout);

    frame=new QWidget();
    vLayout = new QVBoxLayout();
    frame->setLayout(vLayout);
    splitter->addWidget(frame);
    splitter->setCollapsible(2,false);
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(0);
	setupSearchArea(vLayout);

	setSymbolSize(32);
}

void SymbolWidget::setupData(SymbolListModel *model)
{
	categories = QStringList() << "operators" << "relation" << "arrows" << "delimiters" << "greek"
                               << "cyrillic" << "misc-math" << "misc-text" << "wasysym" << "fontawesome5" << "special";
	categoryNames["operators"] = tr("Operators", "Operator category");
	categoryNames["relation"] = tr("Relations", "Operator category");
	categoryNames["arrows"] = tr("Arrows", "Operator category");
	categoryNames["delimiters"] = tr("Delimiters", "Operator category");
	categoryNames["greek"] = tr("Greek", "Operator category");
	categoryNames["cyrillic"] = tr("Cyrillic", "Operator category");
	categoryNames["misc-math"] = tr("Misc. Math", "Operator category");
	categoryNames["misc-text"] = tr("Misc. Text", "Operator category");
	categoryNames["wasysym"] = tr("wasysym", "Operator category");
    categoryNames["fontawesome5"] = tr("fontawesome5", "Operator category");
	categoryNames["special"] = tr("Special", "Operator category");

	Q_ASSERT(categories.count() == categoryNames.count());

	symbolListModel = model;
	foreach (const QString &category, categories) {
		symbolListModel->load(category);
	}

	favoritesProxyModel = new BooleanFilterProxyModel;
	favoritesProxyModel->setSourceModel(symbolListModel);
	favoritesProxyModel->setFilterRole(SymbolListModel::FavoriteRole);
	connect(symbolListModel, SIGNAL(favoritesChanged()), favoritesProxyModel, SLOT(invalidate()));

	mostUsedProxyModel = new MostUsedProxyModel;
	mostUsedProxyModel->setSourceModel(symbolListModel);
	mostUsedProxyModel->setSortRole(SymbolListModel::UsageCountRole);

	categoryFilterProxyModel = new QSortFilterProxyModel;
	categoryFilterProxyModel->setSourceModel(symbolListModel);
	categoryFilterProxyModel->setFilterRole(SymbolListModel::CategoryRole);
	categoryFilterProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

	commandFilterProxyModel = new QSortFilterProxyModel;
	commandFilterProxyModel->setSourceModel(categoryFilterProxyModel);
	commandFilterProxyModel->setFilterRole(SymbolListModel::CommandRole);
	commandFilterProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
}

void SymbolWidget::setupFavoritesArea(QVBoxLayout *vLayout)
{
	QHBoxLayout *hLayout = new QHBoxLayout;
	hLayout->setContentsMargins(4, 6, 4, 6);
	hLayout->setSpacing(8);
	vLayout->addLayout(hLayout);

    QLabel *lbl=new QLabel(tr("Favorites"));
    lbl->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Minimum);
    hLayout->addWidget(lbl);

	addHLine(vLayout);

	favoritesListView = new SymbolListView();
    favoritesListView->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
	favoritesListView->setModel(favoritesProxyModel);
	initSymbolListView(favoritesListView);
	vLayout->addWidget(favoritesListView);
}

void SymbolWidget::setupMostUsedArea(QVBoxLayout *vLayout)
{
	QHBoxLayout *hLayout = new QHBoxLayout;
	hLayout->setContentsMargins(4, 6, 4, 6);
	hLayout->setSpacing(8);
	vLayout->addLayout(hLayout);

    QLabel *lbl=new QLabel(tr("Most Used"));
    lbl->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Maximum);
    hLayout->addWidget(lbl);

	addHLine(vLayout);

	mostUsedListView = new SymbolListView();
    mostUsedListView->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
	mostUsedListView->setModel(mostUsedProxyModel);
	initSymbolListView(mostUsedListView);
	vLayout->addWidget(mostUsedListView);
}

void SymbolWidget::setupSearchArea(QVBoxLayout *vLayout)
{
	QHBoxLayout *hLayout = new QHBoxLayout;
	hLayout->setContentsMargins(4, 2, 4, 2);
	hLayout->setSpacing(8);
	vLayout->addLayout(hLayout);

	leFilter = new QLineEdit();
	leFilter->setPlaceholderText(tr("Search"));
	hLayout->addWidget(leFilter);

	categoryFilterButton = new QToolButton();
	categoryFilterButton->setToolTip(tr("Category"));
	categoryFilterButton->setPopupMode(QToolButton::InstantPopup);
	categoryFilterButton->setAutoRaise(true);
	int width = 0;
	QFontMetrics fm = fontMetrics();
    foreach (const QString &name, categoryNames) {
		width = qMax(width, UtilsUi::getFmWidth(fm, name) + 20);
	}
	categoryFilterButton->setMinimumWidth(width);
	hLayout->addWidget(categoryFilterButton);

    QAction *actAllCategories = new QAction(tr("All"),nullptr);  // does not need data
	connect(actAllCategories, SIGNAL(triggered()), this, SLOT(setCategoryFilterFromAction()));
	categoryFilterButton->addAction(actAllCategories);
	bool isFirst = true;
	foreach (const QString &category, categories) {
        QAction *act = new QAction(categoryNames[category],nullptr);
		categoryFilterButton->addAction(act);
		act->setData(category);
		connect(act, SIGNAL(triggered()), this, SLOT(setCategoryFilterFromAction()));
		if (isFirst) {
			act->trigger();  // initialize the title and category filter
			isFirst = false;
		}
	}

	connect(leFilter, SIGNAL(textChanged(QString)), commandFilterProxyModel, SLOT(setFilterFixedString(QString)));

	addHLine(vLayout);

	symbolListView = new SymbolListView();
	symbolListView->setModel(commandFilterProxyModel);
	initSymbolListView(symbolListView);
	vLayout->addWidget(symbolListView);
}

void SymbolWidget::initSymbolListView(SymbolListView *symbolListView){
	connect(symbolListView, SIGNAL(clicked(QModelIndex)), this, SLOT(symbolClicked(QModelIndex)));
	connect(symbolListView, SIGNAL(addToFavorites(QString)), symbolListModel, SLOT(addFavorite(QString)));
	connect(symbolListView, SIGNAL(removeFromFavorites(QString)), symbolListModel, SLOT(removeFavorite(QString)));
	connect(symbolListView, SIGNAL(insertSymbol(QString)), this, SIGNAL(insertSymbol(QString)));
}

void SymbolWidget::addHLine(QVBoxLayout *vLayout)
{
	QFrame *hLine = new QFrame();
	hLine->setFrameShape(QFrame::HLine);
	vLayout->addWidget(hLine);
}

void SymbolWidget::setSymbolSize(int size)
{
	favoritesListView->setSymbolSize(size);
	mostUsedListView->setSymbolSize(size);
	symbolListView->setSymbolSize(size);

}

void SymbolWidget::restoreSplitter(const QByteArray &ba)
{
    if(ba.isEmpty()){
        QList<int> lst{64,64,2000}; // basically trick the splitter in using minimum heigth for the first two widgets
        splitter->setSizes(lst);
    }else{
        splitter->restoreState(ba);
    }
}

void SymbolWidget::saveSplitterState(QByteArray &ba)
{
    ba=splitter->saveState();
}
/*!
 * \brief reload data
 * Necessary to adapt to changed palette, i.e. switch light/dark mode
 */
void SymbolWidget::reloadData()
{
    foreach (const QString &category, categories) {
        symbolListModel->load(category);
    }
}

void SymbolWidget::setCategoryFilterFromAction()
{
	QAction *act = qobject_cast<QAction *>(sender());
	if (!act) return;
	categoryFilterButton->setText(act->text());
	categoryFilterProxyModel->setFilterFixedString(act->data().toString());
}

void SymbolWidget::symbolClicked(const QModelIndex &index)
{
	QString command;
	if (insertUnicode) command = index.model()->data(index, SymbolListModel::UnicodeRole).toString();
	if (command.isEmpty()) command = index.model()->data(index, SymbolListModel::CommandRole).toString();
	QString id = index.model()->data(index, SymbolListModel::IdRole).toString();
	if (!id.isEmpty()) {
		symbolListModel->incrementUsage(id);
	}
	emit insertSymbol(command);
	mostUsedProxyModel->invalidate();
	mostUsedProxyModel->sort(0, Qt::DescendingOrder);
}

