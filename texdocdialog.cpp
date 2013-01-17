#include "texdocdialog.h"
#include "ui_texdocdialog.h"
#include "help.h"
#include "latexpackages.h"

TexdocDialog::TexdocDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::TexdocDialog),
	packageNameValidator(this),
	openButton(0)
{
	ui->setupUi(this);
	foreach (QAbstractButton *bt, ui->buttonBox->buttons()) {
		if (ui->buttonBox->buttonRole(bt) == QDialogButtonBox::AcceptRole) {
			openButton = bt;
			break;
		}
	}
	packageNameValidator.setRegExp(QRegExp("[0-9a-zA-Z\\-\\.]*"));
	ui->cbPackages->lineEdit()->setValidator(&packageNameValidator);
	ui->cbPackages->setMaxVisibleItems(15);

	checkTimer.setSingleShot(true);
	connect(&checkTimer, SIGNAL(timeout()), SLOT(checkDockAvailable()));
	connect(ui->cbPackages, SIGNAL(editTextChanged(QString)), SLOT(searchTermChanged(QString)));
	connect(Help::instance(), SIGNAL(texdocAvailableReply(QString,bool)), SLOT(updateDocAvailableInfo(QString, bool)));

	updateDocAvailableInfo("", false); // initially disable warning message
}

TexdocDialog::~TexdocDialog()
{
	delete ui;
}

void TexdocDialog::searchTermChanged(const QString &text)
{
	ui->lbShortDescription->setText(LatexPackages::instance()->shortDescription(text));
	delayedCheckDocAvailable(text);
}

void TexdocDialog::setPackageNames(const QStringList &packages)
{
	ui->cbPackages->clear();
	if (!packages.isEmpty()) {
		QStringList pkgs(packages);
		pkgs.sort();
		ui->cbPackages->addItems(pkgs);
		ui->cbPackages->setCurrentIndex(0);
	}
}

void TexdocDialog::setPreferredPackage(const QString &package)
{
	int index = ui->cbPackages->findText(package);
	int dummyPos = 0;
	QString pkgName = package; // copy because valitdate may modify it
	if (index < 0 && QValidator::Acceptable == packageNameValidator.validate(pkgName, dummyPos)) {
		ui->cbPackages->addItem(package);
		index = ui->cbPackages->findText(package);
	}
	ui->cbPackages->setCurrentIndex(index);
}

QString TexdocDialog::selectedPackage() const
{
	return ui->cbPackages->currentText();
}

// use delayed checking because the auto completion of the combo box fires two events
// one with the actually typed text and one with the completed text
void TexdocDialog::delayedCheckDocAvailable(const QString &package)
{
	lastDocRequest = package;
	checkTimer.start(10);
}

void TexdocDialog::checkDockAvailable()
{
	if (lastDocRequest.isEmpty())
		updateDocAvailableInfo("", false);
	else
		Help::instance()->texdocAvailableRequest(lastDocRequest);
}

void TexdocDialog::updateDocAvailableInfo(const QString &package, bool available)
{
	if (package != lastDocRequest) return; // the request may have come from someone else

	bool showWarning = !package.isEmpty() && !available;

	if (openButton) openButton->setEnabled(available);
	ui->lbInfo->setText(showWarning ? tr("No Documentation Available") : "");
	ui->lbWarnIcon->setVisible(showWarning);
}
