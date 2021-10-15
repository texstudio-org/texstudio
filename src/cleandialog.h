#ifndef Header_Clean_Dialog
#define Header_Clean_Dialog

#include "latexdocument.h"
#include "mostQtHeaders.h"

namespace Ui {
class CleanDialog;
}

class CleanDialog : public QDialog
{
	Q_OBJECT

public:
    explicit CleanDialog(QWidget *parent = nullptr);
	~CleanDialog();

	bool checkClean(const LatexDocuments &docs);

private slots:
	void updateFilesToRemove();
	void resetExtensions();
	void onAccept();
	void onReject();

private:
	enum Scope {None, Project, CurrentTexFile, CurrentFileFolder, OpenTexFiles, MAX_SCOPE};

	Ui::CleanDialog *ui;
	static QString defaultExtensions;
	static QString currentExtensions;
	static int scopeID;

	QString masterFile;
	QString currentTexFile;
	QStringList openTexFiles;

	QStringList filesToRemove(CleanDialog::Scope scope, const QStringList &extensionFilter);
	QStringList filesToRemoveFromDir(const QDir &dir, const QStringList &extensionFilter, bool recursive = true);
};

#endif // CLEANDIALOG_H
