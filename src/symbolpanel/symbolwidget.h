#ifndef Header_Symbol_Widget
#define Header_Symbol_Widget

#include "mostQtHeaders.h"

class SymbolListModel;
class SymbolListView;
class QSortFilterProxyModel;


class SymbolWidget : public QWidget
{
	Q_OBJECT
public:
	SymbolWidget(SymbolListModel *model, bool &insertUnicode, QWidget *parent = Q_NULLPTR);

	void setSymbolSize(int size);
	const SymbolListModel * model() const { return symbolListModel; }
    void restoreSplitter(const QByteArray &ba);
    void saveSplitterState(QByteArray &ba);
    void reloadData();

signals:
	void insertSymbol(const QString &text);

public slots:

protected:
	void setupData(SymbolListModel *model);
	void setupFavoritesArea(QVBoxLayout *vLayout);
	void setupMostUsedArea(QVBoxLayout *vLayout);
	void setupSearchArea(QVBoxLayout *vLayout);
	void initSymbolListView(SymbolListView *symbolListView);
	SymbolListView *newSymbolListView();

protected slots:
	void addHLine(QVBoxLayout *vLayout);
	void setCategoryFilterFromAction();
	void symbolClicked(const QModelIndex &index);

private:
	bool &insertUnicode;
	QLineEdit *leFilter;
	QToolButton *categoryFilterButton;
	SymbolListView *favoritesListView;
	SymbolListView *mostUsedListView;
	SymbolListView *symbolListView;

    QSplitter *splitter;

	QStringList categories;
	QHash<QString, QString> categoryNames;

	SymbolListModel *symbolListModel;
	QSortFilterProxyModel *favoritesProxyModel;
	QSortFilterProxyModel *mostUsedProxyModel;
	QSortFilterProxyModel *categoryFilterProxyModel;
	QSortFilterProxyModel *commandFilterProxyModel;
};

#endif // SYMBOLWIDGET_H
