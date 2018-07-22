#include "symbolwidget.h"
#include "symbollistmodel.h"
#include "symbollistview.h"
#include "proxymodels.h"
#include "configmanagerinterface.h"
#include <QSortFilterProxyModel>


SymbolWidget::SymbolWidget(SymbolListModel *model, bool &insertUnicode, QWidget *parent) : QWidget(parent), insertUnicode(insertUnicode)
{
	setupData(model);

	QVBoxLayout *vLayout = new QVBoxLayout();
	setLayout(vLayout);
	vLayout->setContentsMargins(0, 0, 0, 0);
	vLayout->setSpacing(0);

	setupFavoritesArea(vLayout);
	addHLine(vLayout);
	setupMostUsedArea(vLayout);
	addHLine(vLayout);
	setupSearchArea(vLayout);

	setSymbolSize(32);
}

void SymbolWidget::setupData(SymbolListModel *model)
{
	categories = QStringList() << "operators" << "relation" << "arrows" << "delimiters" << "greek"
							   << "cyrillic" << "misc-math" << "misc-text" << "wasysym" << "special";
	categoryNames["operators"] = tr("Operators", "Operator category");
	categoryNames["relation"] = tr("Relations", "Operator category");
	categoryNames["arrows"] = tr("Arrows", "Operator category");
	categoryNames["delimiters"] = tr("Delimiters", "Operator category");
	categoryNames["greek"] = tr("Greek", "Operator category");
	categoryNames["cyrillic"] = tr("Cyrillic", "Operator category");
	categoryNames["misc-math"] = tr("Misc. Math", "Operator category");
	categoryNames["misc-text"] = tr("Misc. Text", "Operator category");
	categoryNames["wasysym"] = tr("wasysym", "Operator category");
	categoryNames["special"] = tr("Special", "Operator category");

	Q_ASSERT(categories.count() == categoryNames.count());

	symbolListModel = model;
	foreach (const QString &category, categories) {
		symbolListModel->load(category);
	}

	favoritesProxyModel = new BooleanFilterProxyModel;
	favoritesProxyModel->setSourceModel(symbolListModel);
	favoritesProxyModel->setFilterRole(SymbolListModel::FavoriteRole);

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

	hLayout->addWidget(new QLabel(tr("Favorites")));

	addHLine(vLayout);

	favoritesListView = new SymbolListView();
	favoritesListView->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
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

	hLayout->addWidget(new QLabel(tr("Most Used")));

	addHLine(vLayout);

	mostUsedListView = new SymbolListView();
	mostUsedListView->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
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
#if QT_VERSION >= 0x040700
	leFilter->setPlaceholderText(tr("Search"));
#endif
	hLayout->addWidget(leFilter);

	categoryFilterButton = new QToolButton();
	categoryFilterButton->setToolTip(tr("Category"));
	categoryFilterButton->setPopupMode(QToolButton::InstantPopup);
	categoryFilterButton->setAutoRaise(true);
	int width = 0;
	QFontMetrics fm = fontMetrics();
	foreach (const QString &name, categoryNames.values()) {
		width = qMax(width, fm.width(name) + 20);
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

