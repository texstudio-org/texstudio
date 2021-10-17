#ifndef Header_TexDoc_Dialog
#define Header_TexDoc_Dialog

#include "mostQtHeaders.h"
#include "help.h"


namespace Ui {
class TexdocDialog;
}

class TexdocDialog : public QDialog
{
	Q_OBJECT

public:
    TexdocDialog(QWidget *parent,Help *obj);
	void setPackageNames(const QStringList &packages);
	void setPreferredPackage(const QString &package);

	QString selectedPackage() const;

	~TexdocDialog();

private slots:
	void searchTermChanged(const QString &text);
	void delayedCheckDocAvailable(const QString &package);
	void checkDockAvailable();
	void updateDocAvailableInfo(const QString &package, bool available, QString customWarning = QString());

private:
	Ui::TexdocDialog *ui;
    QRegularExpressionValidator packageNameValidator;
	QAbstractButton *openButton;
	QTimer checkTimer;
	QString lastDocRequest;
    Help *help;
};

#endif // TEXDOCDIALOG_H
