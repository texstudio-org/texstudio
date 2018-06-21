#include "cleandialog.h"
#include "ui_cleandialog.h"

#include "configmanager.h"
#include "utilsUI.h"

QString CleanDialog::defaultExtensions = "log,aux,dvi,lof,lot,bit,idx,glo,bbl,bcf,ilg,toc,ind,out,blg,fdb_latexmk,fls";
QString CleanDialog::currentExtensions = CleanDialog::defaultExtensions;
int CleanDialog::scopeID = 0;

static const int AbsFilePathRole = Qt::UserRole;

CleanDialog::CleanDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::CleanDialog)
{
	ui->setupUi(this);
	UtilsUi::resizeInFontHeight(this, 38, 22);

	ConfigManagerInterface *config = ConfigManager::getInstance();
	config->registerOption("CleanDialog/Extensions", &currentExtensions, defaultExtensions);
	config->registerOption("CleanDialog/Scope", &scopeID, 0);
	if (scopeID < 0 || scopeID >= MAX_SCOPE) scopeID = 0;

	QString allowedChars = "[^\\\\/\\?\\%\\*:|\"<>\\s,;]";
	QRegExpValidator *rxValExtensionList = new QRegExpValidator(QRegExp(QString("(%1+\\.)*%1+(,(%1+\\.)*%1+)*").arg(allowedChars)), this);
	int dummyPos;
	if (rxValExtensionList->validate(currentExtensions, dummyPos) == QValidator::Acceptable) {
		ui->leExtensions->setText(currentExtensions);
	} else {
		UtilsUi::txsWarning("Invalid extension list found. Resetting to default.");
		currentExtensions = defaultExtensions;
		ui->leExtensions->setText(currentExtensions);
	}
	ui->leExtensions->setValidator(rxValExtensionList);

	ui->pbResetExtensions->setIcon(getRealIcon("edit-undo"));

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
	ui->cbScope->blockSignals(true);  // don't emit currentIndexChanged while populating the combo box
	if (docs.masterDocument) {
		masterFile = docs.masterDocument->getFileName();
		ui->cbScope->addItem(tr("Project (Master file folder and all subfolders)"), CleanDialog::Project);
		if (scopeID == CleanDialog::Project) ui->cbScope->setCurrentIndex(ui->cbScope->count()-1);
		somethingToClean = true;
	}
	if (docs.currentDocument && docs.currentDocument->getFileInfo().suffix().toLower() == "tex") {
		currentTexFile = docs.currentDocument->getFileName();
		ui->cbScope->addItem(tr("Current File"), CleanDialog::CurrentTexFile);
		if (scopeID == CleanDialog::CurrentTexFile) ui->cbScope->setCurrentIndex(ui->cbScope->count()-1);
		ui->cbScope->addItem(tr("Current File Folder"), CleanDialog::CurrentFileFolder);
		if (scopeID == CleanDialog::CurrentFileFolder) ui->cbScope->setCurrentIndex(ui->cbScope->count()-1);
		somethingToClean = true;
	}
	foreach (LatexDocument *doc, docs.documents) {
		if (doc->getFileInfo().suffix().toLower() == "tex") openTexFiles.append(doc->getFileName());
	}
	if (!openTexFiles.isEmpty()) {
		ui->cbScope->addItem(tr("Open Files"), CleanDialog::OpenTexFiles);
		if (scopeID == CleanDialog::OpenTexFiles) ui->cbScope->setCurrentIndex(ui->cbScope->count()-1);
		somethingToClean = true;
	}
	ui->cbScope->blockSignals(false);

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
	scopeID = ui->cbScope->itemData(ui->cbScope->currentIndex()).toInt();
	Scope scope = (Scope) scopeID;
	QStringList extList(ui->leExtensions->text().split(',', QString::SkipEmptyParts));
	QStringList forbiddenExtensions = QStringList() << "tex" << "lytex";
	QStringList found;
	foreach (const QString &ext, forbiddenExtensions) {
		if (extList.contains(ext))
			found << ext;
	}
	if (!found.isEmpty()) {
		UtilsUi::txsWarning(tr("For your own safety clean will not delete the files with the following extensions:") + QString("\n") + extList.join(", "));
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
    default:
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
            if(fi.fileName().startsWith("."))
                continue; // filter directories starting with . (e.g. .git) since they are not automatiocally hidden on windows
			files << filesToRemoveFromDir(fi.absoluteFilePath(), extensionFilter, recursive);
		}
	}
	return files;
}
