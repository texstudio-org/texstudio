#ifndef Header_SymbolList_View
#define Header_SymbolList_View

#include "mostQtHeaders.h"

class SymbolListView : public QListView
{
	Q_OBJECT
public:
	explicit SymbolListView(QWidget *parent = Q_NULLPTR);

	void setSymbolSize(int size);

	QSize sizeHint() const;
	QSize minimumSizeHint() const;

	void contextMenuEvent(QContextMenuEvent *event);

signals:
	void addToFavorites(const QString &id);
	void removeFromFavorites(const QString &id);
	void insertSymbol(const QString &id);

protected slots:
	void emitAddToFavorites();
	void emitRemoveFromFavorites();
	void emitInsertSymbol();

private:
	int m_symbolSize;
	int m_gridSize;
};

#endif // SYMBOLLISTVIEW_H
