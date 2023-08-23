#include "texdocdialog.h"
#include "ui_texdocdialog.h"
#include "latexrepository.h"
#include "utilsUI.h"

TexdocDialog::TexdocDialog(QWidget *parent,Help *obj) :
	QDialog(parent),
	ui(new Ui::TexdocDialog),
    openButton(nullptr),
    help(obj)
{
	ui->setupUi(this);
	UtilsUi::resizeInFontHeight(this, 28, 26);

	foreach (QAbstractButton *bt, ui->buttonBox->buttons()) {
		if (ui->buttonBox->buttonRole(bt) == QDialogButtonBox::AcceptRole) {
			openButton = bt;
			break;
		}
	}

	checkTimer.setSingleShot(true);
	connect(&checkTimer, SIGNAL(timeout()), SLOT(checkDockAvailable()));
	connect(ui->lineEditSearch, SIGNAL(textChanged(QString)),SLOT(tableSearchTermChanged(QString)));
	connect(ui->tbPackages, SIGNAL(currentItemChanged(QTableWidgetItem *, QTableWidgetItem *)), SLOT(itemChanged(QTableWidgetItem *)));
	connect(help, SIGNAL(texdocAvailableReply(QString, bool, QString)), SLOT(updateDocAvailableInfo(QString, bool, QString)));
	connect(ui->buttonCTAN, SIGNAL(clicked()), SLOT(openCtanUrl()));
    connect(ui->cbShowAllPackages,&QCheckBox::stateChanged,this,&TexdocDialog::regenerateTable);

	updateDocAvailableInfo("", false); // initially disable warning message
	ui->buttonCTAN->setEnabled(false);
	ui->lineEditSearch->setEnabled(false);
}

TexdocDialog::~TexdocDialog()
{
    delete ui;
}
/*!
 * \brief generate all rows for table
 * \param all filter to used packages or all ctan packages
 */
void TexdocDialog::regenerateTable(int state)
{
    ui->tbPackages->disconnect(SIGNAL(currentItemChanged(QTableWidgetItem *, QTableWidgetItem *)));
    ui->tbPackages->clearContents();
    ui->tbPackages->setRowCount(0);
    ui->tbPackages->horizontalHeader()->setStretchLastSection(true);
    if (!m_packages.isEmpty() || (state>0)) {
        ui->tbPackages->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tbPackages->setSelectionBehavior(QAbstractItemView::SelectRows);
        LatexRepository *repo = LatexRepository::instance();

        QStringList pkgs;
        if(state>0){
            pkgs=repo->LatexRepository::availablePackages();
        }else{
            pkgs=m_packages;
        }

        ui->tbPackages->setRowCount(pkgs.size());
        int n=0;
        for (int i=0;i<pkgs.size();i++) {
            QString name = pkgs.at(i);
            if(state==0 && !repo->LatexRepository::packageExists(name)) continue;
            QString desc = repo->LatexRepository::shortDescription(name);
            QTableWidgetItem *itemPkgName = new QTableWidgetItem(name);
            QTableWidgetItem *itemPkgDesc = new QTableWidgetItem(desc);
            itemPkgName->setFlags(Qt::ItemIsEnabled|Qt::ItemIsSelectable);
            itemPkgDesc->setFlags(Qt::ItemIsEnabled|Qt::ItemIsSelectable);
            ui->tbPackages->setItem(n,0,itemPkgName);
            ui->tbPackages->setItem(n,1,itemPkgDesc);
            ++n;
        }
        ui->tbPackages->setRowCount(n);
        ui->tbPackages->sortItems(0,Qt::AscendingOrder);
        QTableWidgetItem *itemPkgName = ui->tbPackages->item(0,0);
        ui->tbPackages->setCurrentItem(itemPkgName);
        ui->buttonCTAN->setEnabled(true);
        ui->lineEditSearch->setEnabled(true);
    }
    connect(ui->tbPackages, SIGNAL(currentItemChanged(QTableWidgetItem *, QTableWidgetItem *)), SLOT(itemChanged(QTableWidgetItem *)));
    tableSearchTermChanged(ui->lineEditSearch->text());
}

void TexdocDialog::tableSearchTermChanged(QString term) {
	QTableWidget *tb = ui->tbPackages;
	int rows = tb->rowCount();
    uint foundLevel = 0;
	for (int i=0; i<rows; i++) {
		QTableWidgetItem *itemPkgName = tb->item(i,0);
        bool match = itemPkgName->text().contains(term,Qt::CaseInsensitive);
        if (match){
            if(foundLevel<1){
                tb->setCurrentItem(itemPkgName);
                foundLevel=1;
            }
            if(foundLevel<2 && itemPkgName->text().startsWith(term,Qt::CaseInsensitive)){
                tb->setCurrentItem(itemPkgName);
                foundLevel=2;
            }
            if(foundLevel<3 && itemPkgName->text().startsWith(term)){
                tb->setCurrentItem(itemPkgName);
                foundLevel=3;
            }
		}
        if(!match){
            // check description
            QTableWidgetItem *itemPkgName = tb->item(i,1);
            match = itemPkgName->text().contains(term,Qt::CaseInsensitive);
        }
		tb->setRowHidden(i,!match);
	}
    if (foundLevel==0 && rows>0) {
		QTableWidgetItem *itemPkgName = tb->item(0,0);
		tb->setCurrentItem(itemPkgName);
	}
}

void TexdocDialog::itemChanged(QTableWidgetItem* item)
{
	openButton->setEnabled(false);
	int row = item->row();
	QString text = ui->tbPackages->item(row,0)->text();
	delayedCheckDocAvailable(text);
}

void TexdocDialog::setPackageNames(const QStringList &packages)
{
    m_packages=packages;
    regenerateTable();
}

void TexdocDialog::setPreferredPackage(const QString &package)
{
	int i = 0;
	int rows = ui->tbPackages->rowCount();
	LatexRepository *repo = LatexRepository::instance();
	if (repo->LatexRepository::packageExists(package)) {
		for (;i<rows;i++) {
			if (ui->tbPackages->item(i,0)->text() == package) break;
		}
		if (i>=rows) {
			QString desc = repo->LatexRepository::shortDescription(package);
			QTableWidgetItem *itemPkgName = new QTableWidgetItem(package);
			QTableWidgetItem *itemPkgDesc = new QTableWidgetItem(desc);
			rows++;
			ui->tbPackages->setRowCount(rows);
			ui->tbPackages->setItem(i,0,itemPkgName);
			ui->tbPackages->setItem(i,1,itemPkgDesc);
		}
	}
	if (rows>0) {
		QTableWidgetItem *itemPkgName = ui->tbPackages->item(i,0);
		ui->tbPackages->setCurrentItem(itemPkgName);
		itemPkgName->setSelected(true);
	}
}

QString TexdocDialog::selectedPackage() const
{
	return ui->tbPackages->item(ui->tbPackages->currentRow(),0)->text();
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
    if (lastDocRequest.isEmpty()){
		updateDocAvailableInfo("", false);
    } else {
        help->texdocAvailableRequest(lastDocRequest);
    }
}

void TexdocDialog::updateDocAvailableInfo(const QString &package, bool available, QString customWarning)
{
	if (package != lastDocRequest) return; // the request may have come from someone else

	bool showWarning = !package.isEmpty() && !available;
	QString warning = customWarning.isNull() ? tr("No Documentation Available") : customWarning;
	if (openButton) openButton->setEnabled(available);
	ui->lbInfo->setText(showWarning ? warning : "");
	ui->lbWarnIcon->setVisible(showWarning);
}

void TexdocDialog::openCtanUrl()
{
	int row = ui->tbPackages->currentRow();
	if (row<0) return;
	QString package = ui->tbPackages->item(row,0)->text();
	QUrl packageUrl(QString("https://www.ctan.org/pkg/%1").arg(package));
	QDesktopServices::openUrl(packageUrl);
}
