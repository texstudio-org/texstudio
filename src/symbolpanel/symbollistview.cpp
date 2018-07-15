#include "symbollistview.h"
#include "symbollistmodel.h"
#include "utilsUI.h"

SymbolListView::SymbolListView(QWidget *parent) : QListView(parent)
{
	setViewMode(QListView::IconMode);
	setWrapping(true);
	setResizeMode(QListView::Adjust);
	setFrameShape(QFrame::NoFrame);
	UtilsUi::enableTouchScrolling(this);
}

void SymbolListView::setSymbolSize(int size)
{
	m_symbolSize = size;
	m_gridSize = size + 8;
	setIconSize(QSize(m_symbolSize, m_symbolSize));
	setGridSize(QSize(m_gridSize, m_gridSize));
}

QSize SymbolListView::sizeHint() const
{
	QSize sz = QListView::sizeHint();
	return QSize(sz.width(), 2*m_gridSize);
}

QSize SymbolListView::minimumSizeHint() const
{
	QSize sz = QListView::minimumSizeHint();
	return QSize(sz.width(), m_gridSize);
}

void SymbolListView::contextMenuEvent(QContextMenuEvent *event)
{
	QModelIndex index = indexAt(event->pos());
	if (index.isValid()) {
		QMenu menu(this);
		if (index.data(SymbolListModel::FavoriteRole).toBool()) {
			QAction *act = menu.addAction(tr("Remove from Favorites"));
			act->setData(index.model()->data(index, SymbolListModel::IdRole));
			connect(act, SIGNAL(triggered()), this, SLOT(emitRemoveFromFavorites()));
		} else {
			QAction *act = menu.addAction(tr("Add to Favorites"));
			act->setData(index.model()->data(index, SymbolListModel::IdRole));
			connect(act, SIGNAL(triggered()), this, SLOT(emitAddToFavorites()));
		}
		if (index.data(SymbolListModel::CommandRole).toString().length()) {
			QAction *act = menu.addAction(tr("Insert command"));
			act->setData(index.data(SymbolListModel::CommandRole));
			connect(act, SIGNAL(triggered()), this, SLOT(emitInsertSymbol()));
		}
		if (index.data(SymbolListModel::UnicodeRole).toString().length()) {
			QAction *act = menu.addAction(tr("Insert unicode"));
			act->setData(index.data(SymbolListModel::UnicodeRole));
			connect(act, SIGNAL(triggered()), this, SLOT(emitInsertSymbol()));
		}
		menu.exec(event->globalPos());
	}
}

void SymbolListView::emitAddToFavorites()
{
	QAction *act = qobject_cast<QAction *>(sender());
	if (act) {
		QString id = act->data().toString();
		emit addToFavorites(id);
	}
}

void SymbolListView::emitRemoveFromFavorites()
{
	QAction *act = qobject_cast<QAction *>(sender());
	if (act) {
		QString id = act->data().toString();
		emit removeFromFavorites(id);
	}
}

void SymbolListView::emitInsertSymbol()
{
	QAction *act = qobject_cast<QAction *>(sender());
	if (act) {
		QString s = act->data().toString();
		emit insertSymbol(s);
	}
}

