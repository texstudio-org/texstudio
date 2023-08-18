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
    void regenerateTable(int state=0);
    void tableSearchTermChanged(QString term);
	void itemChanged(QTableWidgetItem* item);
	void delayedCheckDocAvailable(const QString &package);
	void checkDockAvailable();
	void updateDocAvailableInfo(const QString &package, bool available, QString customWarning = QString());
	void openCtanUrl();

private:
	Ui::TexdocDialog *ui;
	QAbstractButton *openButton;
	QTimer checkTimer;
	QString lastDocRequest;
    Help *help;
    QStringList m_packages;
};

#endif // TEXDOCDIALOG_H
