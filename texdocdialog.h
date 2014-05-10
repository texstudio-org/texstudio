#ifndef TEXDOCDIALOG_H
#define TEXDOCDIALOG_H

#include "mostQtHeaders.h"


namespace Ui {
class TexdocDialog;
}

class TexdocDialog : public QDialog
{
	Q_OBJECT
	
public:
	explicit TexdocDialog(QWidget *parent = 0);
	void setPackageNames(const QStringList &packages);
	void setPreferredPackage(const QString &package);

	QString selectedPackage() const;

	~TexdocDialog();

private slots:
	void searchTermChanged(const QString &text);
	void delayedCheckDocAvailable(const QString &package);
	void checkDockAvailable();
	void updateDocAvailableInfo(const QString &package, bool available);

private:
	Ui::TexdocDialog *ui;
	QRegExpValidator packageNameValidator;
	QAbstractButton *openButton;
	QTimer checkTimer;
	QString lastDocRequest;
};

#endif // TEXDOCDIALOG_H
