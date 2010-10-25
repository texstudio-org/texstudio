#ifndef UNICODEINSERTION_H
#define UNICODEINSERTION_H

#include "mostQtHeaders.h"

class UnicodeInsertion : public QWidget
{
	Q_OBJECT
public:
	UnicodeInsertion(QWidget* parent);
private:
	QLineEdit* edit;
	QTableWidget* table;

	void setTableText(int r, int c, const QString& s);
protected:
	virtual void keyPressEvent(QKeyEvent * e);
private slots:
	void editChanged(const QString& newtext);

	void tableCellClicked(int r, int c);
	void tableCellDoubleClicked(int r, int c);

public: signals:
	void insertCharacter(const QString& c);

};

#endif // UNICODEINSERTION_H
