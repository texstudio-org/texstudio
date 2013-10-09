#include "cleandialog.h"
#include "ui_cleandialog.h"

#include "configmanager.h"

QString CleanDialog::defaultExtensions = "log,aux,dvi,lof,lot,bit,idx,glo,bbl,ilg,toc,ind,out,blg";
QString CleanDialog::currentExtensions = CleanDialog::defaultExtensions;

static const int AbsFilePathRole = Qt::UserRole;

CleanDialog::CleanDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::CleanDialog)
{
	ui->setupUi(this);

	ConfigManager::getInstance()->registerOption("CleanDialog/Extensions", &currentExtensions, defaultExtensions);

	QString allowedChars = "[^\\\\/\\?\\%\\*:|\"<>\\s,;]";
	QRegExpValidator *rxValExtensionList = new QRegExpValidator(QRegExp(QString("(%1+\\.)*%1+(,(%1+\\.)*%1+)*").arg(allowedChars)), this);
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
	connect(ui->cbScope, SIGNAL(currentIndexChanged(int)), SLOT(updateFilesToRemove()));
	connect(ui->leExtensions, SIGNAL(editingFinished()), SLOT(updateFilesToRemove()));
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
		ui->cbScope->addItem(tr("Current File Folder"), CleanDialog::CurrentFileFolder);
		somethingToClean = true;
	}
	foreach (LatexDocument *doc, docs.documents) {
		if (doc->getFileInfo().suffix()=="tex") openTexFiles.append(doc->getFileName());
	}
	if (!openTexFiles.isEmpty()) {
		ui->cbScope->addItem(tr("Open Files"), CleanDialog::OpenTexFiles);
		somethingToClean = true;
	}

	if (somethingToClean)
		updateFilesToRemove();
	return somethingToClean;
}

void CleanDialog::resetExtensions() {
	ui->leExtensions->setText(defaultExtensions);
}

void CleanDialog::onAccept() {
	for (int i=0; i<ui->lwFiles->count(); i++) {
		QFile::remove(ui->lwFiles->item(i)->data(AbsFilePathRole).toString());
	}
	accept();
}

void CleanDialog::onReject() {
	reject();
}

void CleanDialog::updateFilesToRemove() {
	Scope scope = (Scope) ui->cbScope->itemData(ui->cbScope->currentIndex()).toInt();
	QStringList extList(ui->leExtensions->text().split(',', QString::SkipEmptyParts));
	QStringList forbiddenExtensions = QStringList() << "tex" << "lytex";
	QStringList found;
	foreach (const QString &ext, forbiddenExtensions) {
		if (extList.contains(ext))
			found << ext;
	}
	if (!found.isEmpty()) {
		txsWarning(tr("For your own safety clean will not delete the files with the following extensions:") + QString("\n") + extList.join(", "));
		foreach (QString ext, found)
			extList.removeAll(ext);
	}
	currentExtensions = extList.join(",");
	ui->leExtensions->setText(currentExtensions);

	QStringList files;
	files << filesToRemove(scope, extList);
	ui->lwFiles->clear();

	foreach (const QString &absName, files) {
		QFileInfo f(absName);
		QListWidgetItem *item = new QListWidgetItem(f.fileName());
		item->setData(AbsFilePathRole, absName);
		item->setToolTip(absName);
		ui->lwFiles->addItem(item);
	}
}

QStringList CleanDialog::filesToRemove(CleanDialog::Scope scope, const QStringList &extensionFilter) {
	QStringList files;
	switch (scope) {
	case Project:
		{
			QStringList filterList;
			foreach (const QString &ext, extensionFilter) filterList << "*." + ext;
			files << filesToRemoveFromDir(QFileInfo(masterFile).absoluteDir(), filterList);
		}
		break;
	case CurrentTexFile:
		{
			QFileInfo fi(currentTexFile);
			QString basename=fi.absolutePath()+"/"+fi.completeBaseName();
			foreach(const QString& ext, extensionFilter) {
				QFileInfo f(basename + "." + ext);
				if (f.exists())
					files << f.absoluteFilePath();
			}
		}
		break;
	case CurrentFileFolder:
		{
			QStringList filterList;
			foreach (const QString &ext, extensionFilter) filterList << "*." + ext;
			files << filesToRemoveFromDir(QFileInfo(currentTexFile).absoluteDir(), filterList);
		}
		break;
	case OpenTexFiles:
		{
			foreach(const QString& finame, openTexFiles){
				QFileInfo fi(finame);
				QString basename=fi.absolutePath()+"/"+fi.completeBaseName();
				foreach(const QString& ext, extensionFilter) {
					QFileInfo f(basename + "." + ext);
					if (f.exists())
						files << f.absoluteFilePath();
				}
			}
		}
		break;
	case None:
		break;
	}
	return files;
}

QStringList CleanDialog::filesToRemoveFromDir(const QDir &dir, const QStringList &extensionFilter, bool recursive) {
	QStringList files;
	foreach (const QFileInfo &fi, dir.entryInfoList(extensionFilter, QDir::Files)) {
		files << fi.absoluteFilePath();
	}
	if (recursive) {
		foreach (const QFileInfo &fi, dir.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot)) {
			files << filesToRemoveFromDir(fi.absoluteFilePath(), extensionFilter, recursive);
		}
	}
	return files;
}


