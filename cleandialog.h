#ifndef CLEANDIALOG_H
#define CLEANDIALOG_H

#include "latexdocument.h"
#include "mostQtHeaders.h"

namespace Ui {
class CleanDialog;
}

class CleanDialog : public QDialog
{
	Q_OBJECT
	
public:
	explicit CleanDialog(QWidget *parent = 0);
	~CleanDialog();

	bool checkClean(const LatexDocuments &docs);

private slots:
	void updateFilesToRemove();
	void resetExtensions();
	void onAccept();
	void onReject();

private:
	enum Scope {None, Project, CurrentTexFile, CurrentFileFolder, OpenTexFiles};

	Ui::CleanDialog *ui;
	static QString defaultExtensions;
	static QString currentExtensions;

	QString masterFile;
	QString currentTexFile;
	QStringList openTexFiles;

	QStringList filesToRemove(CleanDialog::Scope scope, const QStringList &extensionFilter);
	QStringList filesToRemoveFromDir(const QDir &dir, const QStringList &extensionFilter, bool recursive=true);
};

#endif // CLEANDIALOG_H
