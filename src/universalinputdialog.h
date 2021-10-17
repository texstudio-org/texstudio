#ifndef Header_UniversalInput_Dialog
#define Header_UniversalInput_Dialog

#include "mostQtHeaders.h"

#include "configmanagerinterface.h"

/* This class works almost like QInputDialog, except that it can ask for
   multiple values */
class UniversalInputDialog : public QDialog
{
	Q_OBJECT

protected:
	QGridLayout *gridLayout;
	QList<ManagedProperty> properties;
	void addWidget(QWidget *widget, const QString &description = "", const ManagedProperty &prop = ManagedProperty());
	QCheckBox *addCheckBox(const ManagedProperty &mp, const QString &description);
	QComboBox *addComboBox(const ManagedProperty &mp, const QString &description);
	QSpinBox *addSpinBox(const ManagedProperty &mp, const QString &description);
	QDoubleSpinBox *addDoubleSpinBox(const ManagedProperty &mp, const QString &description);
	QLineEdit *addLineEdit(const ManagedProperty &mp, const QString &description);
	QTextEdit *addTextEdit(const ManagedProperty &mp, const QString &description);

private slots:
	void myAccept();

public:
	UniversalInputDialog(QWidget *parent = 0);
	QCheckBox *addVariable(bool *var, const QString &description = "");
	QSpinBox *addVariable(int *var, const QString &description = "");
	QLineEdit *addVariable(QString *var, const QString &description = "");
	QComboBox *addVariable(int *var, const QStringList &options, const QString &description = "");
	QComboBox *addVariable(QStringList *var, const QString &description = "");
	QTextEdit *addTextEdit(QString *var, const QString &description = "");
	QDoubleSpinBox *addVariable(float *var, const QString &description = "");
	virtual void showEvent(QShowEvent *event);
};

//seems to be not necessary in qt4.5, but I'm not sure about older versions
Q_DECLARE_METATYPE(void *)

#endif // UNIVERSALDIALOG_H
