#ifndef Header_MakeTemplate_Dialog
#define Header_MakeTemplate_Dialog

#include <QDialog>
#include <QFileInfo>

namespace Ui {
class MakeTemplateDialog;
}

class MakeTemplateDialog : public QDialog
{
	Q_OBJECT

public:
    explicit MakeTemplateDialog(QString templateDir, QString editorFilename, QWidget *parent = nullptr);
	~MakeTemplateDialog();

	QString generateMetaData();
	QString suggestedFile() const { return m_suggestedFile.absoluteFilePath(); }

private slots:
	void tryAccept();

private:
	Ui::MakeTemplateDialog *ui;
	QString m_templateDir;
	QString m_editorFilename;
	QFileInfo m_suggestedFile;
};

#endif // MAKETEMPLATEDIALOG_H
