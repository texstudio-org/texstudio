#include "maketemplatedialog.h"
#include "ui_maketemplatedialog.h"
#include "smallUsefulFunctions.h"

MakeTemplateDialog::MakeTemplateDialog(QString templateDir, QString editorFilename, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::MakeTemplateDialog),
	m_templateDir(templateDir),
	m_editorFilename(editorFilename)
{
	ui->setupUi(this);

	connect(ui->buttonBox, SIGNAL(accepted()), SLOT(tryAccept()));
	connect(ui->buttonBox, SIGNAL(rejected()), SLOT(reject()));

	ui->leAuthor->setText(getUserName());
	ui->leVersion->setText("1.0");
	ui->cbLicense->clearEditText();
}

MakeTemplateDialog::~MakeTemplateDialog()
{
	delete ui;
}

void MakeTemplateDialog::tryAccept()
{
	QString fn = ui->leName->text();
	QString invalidChars = "\\/:*?\"<>|"; // for windows, OSX and linux is less restrictive but we use this to guarantee compatibility
	foreach (const QChar &c, invalidChars)
		fn.remove(c);
	if (fn.length() > 80) {
		fn.remove(80);
	}
	fn.prepend("template_");
	QString ext = QFileInfo(m_editorFilename).completeSuffix();
	if (ext.isEmpty()) {
		ext = "tex";
	}
	fn.append("."+ext);
	m_suggestedFile = QFileInfo(QDir(m_templateDir), fn);
	if (m_suggestedFile.exists()) {
		bool overwrite = txsConfirmWarning(tr("A template with the given name already exists.\nDo you want to overwrite it?")+"\n"+m_suggestedFile.canonicalFilePath());
		if (!overwrite)
			return;
	}
	accept();
}

QString MakeTemplateDialog::generateMetaData()
{
	QString s = "{\n";
	s += formatJsonStringParam("Name", ui->leName->text(), 13) + ",\n";
	s += formatJsonStringParam("Author", ui->leAuthor->text(), 13) + ",\n";
	s += formatJsonStringParam("Date", QDate::currentDate().toString(Qt::ISODate), 13) + ",\n";
	s += formatJsonStringParam("Version", ui->leVersion->text(), 13) + ",\n";
	s += formatJsonStringParam("Description", ui->leDescription->toPlainText(), 13) + ",\n";
	s += formatJsonStringParam("License", ui->cbLicense->currentText(), 13) + "\n"; // last entry does not have colon
	s += "}";
	return s;
}
