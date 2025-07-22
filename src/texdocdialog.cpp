#include "texdocdialog.h"
#include "ui_texdocdialog.h"
#include "utilsUI.h"

TexdocDialog::TexdocDialog(QWidget *parent,Help *obj) :
	QDialog(parent,Qt::Dialog|Qt::WindowMaximizeButtonHint|Qt::WindowCloseButtonHint),
	ui(new Ui::TexdocDialog),
    openButton(nullptr),
    help(obj)
{
	ui->setupUi(this);
    UtilsUi::resizeInFontHeight(this, 50, 50);

	foreach (QAbstractButton *bt, ui->buttonBox->buttons()) {
		if (ui->buttonBox->buttonRole(bt) == QDialogButtonBox::AcceptRole) {
			openButton = bt;
			break;
		}
	}
    int w = this->width();
    int h = this->height();
    ui->splitter->setSizes(QList<int>{static_cast<int>(0.8*h),static_cast<int>(0.2*h)});
    ui->splitter_2->setSizes(QList<int>{static_cast<int>(0.3*w),static_cast<int>(0.7*w)});

	checkTimer.setSingleShot(true);
	ui->lineEditSearch->setClearButtonEnabled(true);
	connect(&checkTimer, SIGNAL(timeout()), SLOT(checkDockAvailable()));
	connect(ui->lineEditSearch, SIGNAL(textChanged(QString)),SLOT(tableSearchTermChanged(QString)));
	connect(ui->tbPackages, SIGNAL(currentItemChanged(QTableWidgetItem *, QTableWidgetItem *)), SLOT(itemChanged(QTableWidgetItem *)));
	connect(help, SIGNAL(texdocAvailableReply(QString, bool, QString)), SLOT(updateDocAvailableInfo(QString, bool, QString)));
	connect(ui->buttonCTAN, SIGNAL(clicked()), SLOT(openCtanUrl()));
	connect(ui->cbShowAllPackages,&QCheckBox::stateChanged,this,&TexdocDialog::regenerateTable);
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
    int n=0;
    if (!m_packages.isEmpty() || (state==Qt::Checked)) {
        ui->tbPackages->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tbPackages->setSelectionBehavior(QAbstractItemView::SelectRows);
        LatexRepository *repo = LatexRepository::instance();

        QStringList pkgs;
        if(state==Qt::Checked){
            pkgs=repo->LatexRepository::availablePackages();
        }else{
            pkgs=m_packages;
        }

        ui->tbPackages->setRowCount(pkgs.size());
        QHash<QString, LatexPackageInfo> packageHash = repo->LatexRepository::getPackageHash();
        for (QString pkgname : pkgs) {
            LatexPackageInfo pkg = packageHash.value(pkgname);
            QString name = pkg.id;
            if(state==Qt::Unchecked && !repo->LatexRepository::packageExists(name)) continue;
            QTableWidgetItem *itemPkgName = new QTableWidgetItem(name);
            itemPkgName->setData(Qt::UserRole,QVariant::fromValue(pkg));
            itemPkgName->setFlags(Qt::ItemIsEnabled|Qt::ItemIsSelectable);
            ui->tbPackages->setItem(n,0,itemPkgName);
            ++n;
        }
        ui->tbPackages->setRowCount(n);
        ui->tbPackages->sortItems(0,Qt::AscendingOrder);
    }
    ui->lineEditSearch->setEnabled(n>0);
    if (n>0) ui->lineEditSearch->setFocus();
    connect(ui->tbPackages, SIGNAL(currentItemChanged(QTableWidgetItem *, QTableWidgetItem *)), SLOT(itemChanged(QTableWidgetItem *)));
    tableSearchTermChanged(ui->lineEditSearch->text());
}

void TexdocDialog::tableSearchTermChanged(QString term) {
    QTableWidget *tb = ui->tbPackages;
    int rows = tb->rowCount();
    QTableWidgetItem *currentItem = nullptr;
    ui->buttonCTAN->setEnabled(false);
    uint foundLevel = 0;
    int n = 0;
    for (int i=0; i<rows; i++) {
        QTableWidgetItem *itemPkgName = tb->item(i,0);
        bool match = itemPkgName->text().contains(term,Qt::CaseInsensitive);
        if (match){
            if(foundLevel<1){
                currentItem = itemPkgName;
                foundLevel=1;
            }
            if(foundLevel<2 && itemPkgName->text().startsWith(term,Qt::CaseInsensitive)){
                currentItem = itemPkgName;
                foundLevel=2;
            }
            if(foundLevel<3 && itemPkgName->text().startsWith(term)){
                currentItem = itemPkgName;
                foundLevel=3;
            }
        }
        if(!match){
            // check description
            QTableWidgetItem *itemPkgName = tb->item(i,0);
            LatexPackageInfo packageInfo = itemPkgName->data(Qt::UserRole).value<LatexPackageInfo>();
            match = packageInfo.caption.contains(term,Qt::CaseInsensitive);
            if (n==0 && match) currentItem = itemPkgName;
        }
        if (match) n++;
        tb->setRowHidden(i,!match);
    }
    if (n>0) {
        ui->buttonCTAN->setEnabled(true);
        if (tb->currentItem() != currentItem) {
            ui->lbInfo->setText("");
            ui->lbWarnIcon->setVisible(false);
            openButton->setEnabled(false);
            tb->scrollToItem(currentItem,QAbstractItemView::PositionAtTop);
            tb->setCurrentItem(currentItem);
        }
        else {
            tb->scrollToItem(currentItem,QAbstractItemView::PositionAtTop);
            itemChanged(currentItem);
        }
    }
    else {
        ui->buttonCTAN->setEnabled(false);
        ui->lbInfo->setText("");
        ui->lbWarnIcon->setVisible(false);
        openButton->setEnabled(false);
    }
}

void TexdocDialog::itemChanged(QTableWidgetItem* item)
{
	ui->buttonCTAN->setEnabled(true);
	ui->lbInfo->setText("");
	ui->lbWarnIcon->setVisible(false);
	openButton->setEnabled(false);
	int row = item->row();
	QString text = ui->tbPackages->item(row,0)->text();
    LatexPackageInfo package = item->data(Qt::UserRole).value<LatexPackageInfo>();
    QString Info = LatexRepository::packageInfo(package);
    ui->packageInfoBrowser->setOpenExternalLinks(true);
#if QT_VERSION>=QT_VERSION_CHECK(5,14,0)
    ui->packageInfoBrowser->setMarkdown(Info);
#else
    ui->packageInfoBrowser->setText(Info); // no markdown interpretation, just keep old qt version running
#endif

    delayedCheckDocAvailable(text);
    buttonGroup.setExclusive(true);

    while(buttonGroup.buttons().count()>0){
        QAbstractButton * bt = buttonGroup.buttons().first();
        ui->languagesLayout->removeWidget(bt);
        buttonGroup.removeButton(bt);
        delete bt;
    }
    switch(package.descriptions.count()) {
        case 0: break;
        case 1: ui->packageDescriptions->setHtml(package.descriptions.first().text);
                break;
        default:
            for(const CTANDescription &description : package.descriptions){
                QPushButton * langButton = new QPushButton(description.language,this);
                langButton->setCheckable(true);
                buttonGroup.addButton(langButton);
                ui->languagesLayout->addWidget(langButton);
                connect(langButton,&QPushButton::toggled,this,[=](){
                    ui->packageDescriptions->setHtml(description.text);
                });
                langButton->setChecked(true);
            }
    }
}

void TexdocDialog::setPackageNames(const QStringList &packages)
{
    m_packages=packages;
    if (m_packages.count()>0){
        regenerateTable();
    }
}

void TexdocDialog::setPreferredPackage(const QString &package)
{
	ui->lineEditSearch->setText(package);
}
/*!
 * \brief setShowAllPackages
 * \param showAll
 */
void TexdocDialog::setShowAllPackages(bool showAll)
{
    ui->cbShowAllPackages->setChecked(showAll);
}
/*!
 * \brief return the state of the checkbox showallpackages
 * \return
 */
bool TexdocDialog::showAllPackages() const
{
    return ui->cbShowAllPackages->isChecked();
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
        LatexRepository *repo = LatexRepository::instance();
        if (repo->LatexRepository::packageExists(lastDocRequest)) {
            TeXdocStatus status = repo->LatexRepository::docStatus(lastDocRequest);
            if (status == Undefined)
                help->texdocAvailableRequest(lastDocRequest);
            else {
                updateDocAvailableInfo(lastDocRequest, status==Available);
            }
        }
        else {
            help->texdocAvailableRequest(lastDocRequest);
        }
    }
}

void TexdocDialog::updateDocAvailableInfo(const QString &package, bool available, QString customWarning)
{
	if (package != lastDocRequest) return; // the request may have come from someone else

	bool showWarning = !package.isEmpty() && !available;
	QString warning = customWarning.isNull() ? tr("No Documentation Available") : customWarning;
	TeXdocStatus status = available ? Available : Unavailable;
	LatexRepository::instance()->updatePackageInfo(package, status);
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
