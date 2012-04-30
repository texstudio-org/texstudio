#include "cleandialog.h"
#include "ui_cleandialog.h"

#include "configmanager.h"

QString CleanDialog::defaultExtensions = "log,aux,dvi,lof,lot,bit,idx,glo,bbl,ilg,toc,ind,out,blg";
QString CleanDialog::currentExtensions = CleanDialog::defaultExtensions;

CleanDialog::CleanDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::CleanDialog)
{
	ui->setupUi(this);

	ConfigManager::getInstance()->registerOption("CleanDialog/Extensions", &currentExtensions, defaultExtensions);

	QRegExpValidator *rxValExtensionList = new QRegExpValidator(QRegExp("[0-9a-z_]*(,[0-9a-z_]*)*"), this);
	int dummyPos;
	if (rxValExtensionList->validate(currentExtensions, dummyPos) == QValidator::Acceptable) {
		ui->leExtensions->setText(currentExtensions);
	} else {
		txsWarning("Invalid extension list found. Resetting to default.");
		currentExtensions = defaultExtensions;
		ui->leExtensions->setText(currentExtensions);
	}
	ui->leExtensions->setValidator(rxValExtensionList);

	ui->pbResetExtensions->setIcon(getRealIcon("undo"));

	connect(ui->pbResetExtensions, SIGNAL(clicked()), SLOT(resetExtensions()));
	connect(ui->buttonBox, SIGNAL(accepted()), SLOT(onAccept()));
	connect(ui->buttonBox, SIGNAL(rejected()), SLOT(onReject()));
}

CleanDialog::~CleanDialog() {
	delete ui;
}

/* internally sets up possible clean variants. Call before exec()
   Returns true, if at least one variant can be applied. */
bool CleanDialog::checkClean(const LatexDocuments &docs) {
	bool somethingToClean = false;
	if (docs.masterDocument) {
		masterFile = docs.masterDocument->getFileName();
		ui->cbScope->addItem(tr("Project (Master file folder and all subfolders)"), CleanDialog::Project);
		somethingToClean = true;
	}
	if (docs.currentDocument && docs.currentDocument->getFileInfo().suffix()=="tex") {
		currentTexFile = docs.currentDocument->getFileName();
		ui->cbScope->addItem(tr("Current File"), CleanDialog::CurrentTexFile);
		somethingToClean = true;
	}
	foreach (LatexDocument *doc, docs.documents) {
		if (doc->getFileInfo().suffix()=="tex") openTexFiles.append(doc->getFileName());
	}
	if (!openTexFiles.isEmpty()) {
		ui->cbScope->addItem(tr("Open Files"), CleanDialog::OpenTexFiles);
		somethingToClean = true;
	}

	return somethingToClean;
}

void CleanDialog::resetExtensions() {
	ui->leExtensions->setText(defaultExtensions);
}

void CleanDialog::onAccept() {

	QStringList extList(ui->leExtensions->text().split(',', QString::SkipEmptyParts));
		if (extList.contains("tex")) {
		txsWarning("For your own safety clean will not delete *.tex files.");
		extList.removeAll("tex");
	}
		currentExtensions = extList.join(",");

	int scope = ui->cbScope->itemData(ui->cbScope->currentIndex()).toInt();
	switch (scope) {
	case Project:
		{
			QStringList filterList;
			foreach (const QString &ext, extList) filterList << "*." + ext;

			removeFromDir(QFileInfo(masterFile).absoluteDir(), filterList);
		}
		break;
	case CurrentTexFile:
		{
			QFileInfo fi(currentTexFile);
			QString basename=fi.absolutePath()+"/"+fi.completeBaseName();
			foreach(const QString& ext, extList)
				//qDebug() << basename + "." + ext;
				QFile::remove(basename + "." + ext);
		}
		break;
	case OpenTexFiles:
		{
			foreach(const QString& finame, openTexFiles){
				QFileInfo fi(finame);
				QString basename=fi.absolutePath()+"/"+fi.completeBaseName();
				foreach(const QString& ext, extList)
					//qDebug() << basename + "." + ext;
					QFile::remove(basename + "." + ext);
			}
		}
		break;
	}
	accept();
}

void CleanDialog::onReject() {
	reject();
}

void CleanDialog::removeFromDir(const QDir &dir, const QStringList &extensionFilter, bool recursive) {
	foreach (const QFileInfo &fi, dir.entryInfoList(extensionFilter, QDir::Files)) {
		//qDebug() << fi.absoluteFilePath();
		QFile::remove(fi.absoluteFilePath());
	}
	if (recursive) {
		foreach (const QFileInfo &fi, dir.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot)) {
			removeFromDir(fi.absoluteFilePath(), extensionFilter, recursive);
		}
	}
}
