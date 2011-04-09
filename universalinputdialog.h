#ifndef UNIVERSALINPUTDIALOG_H
#define UNIVERSALINPUTDIALOG_H

#include "mostQtHeaders.h"

/* This class works almost like QInputDialog, except that it can ask for
   multiple values */
class UniversalInputDialog : public QDialog
{
	Q_OBJECT
private:
	QGridLayout* gridLayout;
	void addWidget(QWidget* widget, const QString& description="", void* storage=0);
private slots:
	void myAccept();
public:
	UniversalInputDialog(QWidget* parent=0);
	void addVariable(bool* var, const QString& description="");
	void addVariable(int* var, const QString& description="");
	void addVariable(QString* var, const QString& description="");
	void addVariable(QStringList* var, const QString& description="");
	void addTextEdit(QString* var, const QString& description="");
	void addVariable(float* var, const QString& description="");
	virtual void showEvent(QShowEvent* event);
};

//seems to be not necessary in qt4.5, but I'm not sure about older versions
Q_DECLARE_METATYPE(void*);

#endif // UNIVERSALDIALOG_H
