#ifndef UNICODEINSERTION_H
#define UNICODEINSERTION_H

#include "mostQtHeaders.h"


class QLineEditWithMetaText: public QLineEdit
{
	Q_OBJECT

public:
	QLineEditWithMetaText(QWidget *parent);
	void setMetaText(const QString &s);

protected:
	QString metaText;
	virtual void paintEvent ( QPaintEvent *ev);
};


class UnicodeInsertion : public QWidget
{
	Q_OBJECT

public:
    UnicodeInsertion(QWidget *parent, uint defCharCode = 0);

private:
	QLineEditWithMetaText *edit;
	QTableWidget *table;
    uint defaultCharCode;

	void setTableText(int r, int c, const QString &s);

protected:
	virtual void keyPressEvent(QKeyEvent *e);

private slots:
	void editChanged(const QString &newtext);
	void tableCellClicked(int r, int c);
	void tableCellDoubleClicked(int r, int c);

public:
signals:
	void insertCharacter(const QString &c);
};

#endif // UNICODEINSERTION_H
