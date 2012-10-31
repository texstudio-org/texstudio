/***************************************************************************
 *   copyright       : (C) 2009 by Jan Sundermeyer                         *
 *   http://texstudio.sourceforge.net/                                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "templateselector.h"
#include "smallUsefulFunctions.h"

const int TemplateSelector::TemplateHandleRole = Qt::UserRole;
const int TemplateSelector::RessourceRole = Qt::UserRole+1;


void PreviewLabel::setScaledPixmap(const QPixmap &pm) {
	currentPixmap = pm;
	setPixmapWithResizing(pm);
}

void PreviewLabel::resizeEvent(QResizeEvent *event) {
	Q_UNUSED(event);
	setPixmapWithResizing(currentPixmap);
}

void PreviewLabel::setPixmapWithResizing(const QPixmap &pm) {
	if (pm.isNull()) {
		setText(TemplateSelector::tr("No Preview"));
		return;
	}

	double relWidth = pm.width() / ((double) contentsRect().width());
	double relHeight = pm.height() / ((double) contentsRect().height());
	if (relWidth > 1.0 || relHeight > 1.0) {
		setPixmap(pm.scaled(contentsRect().size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	} else {
		setPixmap(pm);
	}
}




TemplateSelector::TemplateSelector(QString name, QWidget *parent)
	: QDialog(parent) {
	setModal(true);
	ui.setupUi(this);
	setWindowTitle(name);

	QGridLayout *gl = qobject_cast<QGridLayout *>(layout());
	if (gl) {
		// TODO is there a more elegant way to replace the label?
		gl->removeWidget(ui.previewLabelDummy);
		delete ui.previewLabelDummy;
		previewLabel = new PreviewLabel(this);
		previewLabel->setFrameShape(QFrame::Box);
		previewLabel->setFrameShadow(QFrame::Plain);
		previewLabel->setAlignment(Qt::AlignCenter);
		previewLabel->setMargin(5);
		previewLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
		gl->addWidget(previewLabel, 0, 2);
	}

	connect(ui.buttonBox, SIGNAL(accepted()), SLOT(accept()));
	connect(ui.buttonBox, SIGNAL(rejected()), SLOT(reject()));

	ui.templatesTree->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui.templatesTree, SIGNAL(customContextMenuRequested(QPoint)), SLOT(templatesTreeContextMenu(QPoint)));
	connect(ui.templatesTree, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), SLOT(showInfo(QTreeWidgetItem*,QTreeWidgetItem*)));

	showInfo(0,0);
}

TemplateSelector::~TemplateSelector() {
}

void TemplateSelector::addTemplateFiles() {
	// works for table templates and latex templates
	QRegExp rxTemplate("(^|^.*/)(table)?(template_)?");
	QRegExp rxSuffix(".(tex|js)$");

	//QStringList files=findResourceFiles("templates/", mFilter, mAdditonalSearchPaths);

	/*
	foreach(const QString &file, files) {
		QString title = file;
		title.replace(rxTemplate, "");
		title.replace(rxSuffix, "");
		QListWidgetItem *item = new QListWidgetItem(title);

		item->setData(FileNameRole, file);
		ui.listWidget->addItem(item);
	}*/
}

void TemplateSelector::addRessource(AbstractTemplateRessource *res)
{
	QTreeWidgetItem *topitem = new QTreeWidgetItem(QStringList() << res->name());
	topitem->setIcon(0, res->icon());
	QFont ft = topitem->font(0);
	ft.setBold(true);
	topitem->setFont(0, ft);
	topitem->setData(0, RessourceRole, QVariant::fromValue<AbstractTemplateRessource*>(res));
	ui.templatesTree->addTopLevelItem(topitem);

	foreach (TemplateHandle th, res->getTemplates()) {
		QTreeWidgetItem *twi = new QTreeWidgetItem(QStringList() << th.name());
		twi->setData(0, TemplateHandleRole, QVariant::fromValue<TemplateHandle>(th));
		topitem->addChild(twi);
	}
	topitem->setExpanded(true);
}

TemplateHandle TemplateSelector::selectedTemplate() const {
	if (!ui.templatesTree->currentItem())
		return TemplateHandle();

	return ui.templatesTree->currentItem()->data(0, TemplateHandleRole).value<TemplateHandle>();
}

void TemplateSelector::on_templatesTree_doubleClicked(const QModelIndex& /*item*/) {
	QPushButton *pbOk = ui.buttonBox->button(QDialogButtonBox::Ok);
	Q_ASSERT(pbOk);
	if (pbOk->isEnabled())
		accept();
}

void TemplateSelector::showInfo(QTreeWidgetItem *currentItem,QTreeWidgetItem *previousItem) {
	Q_UNUSED(previousItem);

	QPushButton *pbOk = ui.buttonBox->button(QDialogButtonBox::Ok);
	Q_ASSERT(pbOk);

	QVariant varth = (currentItem) ? currentItem->data(0, TemplateHandleRole) : QVariant();

	if (varth.isValid()) {
		// selected template
		TemplateHandle th = varth.value<TemplateHandle>();

		pbOk->setEnabled(true);
		ui.lbName->setText(orDefault(th.name(), tr("<No Name>")));
		ui.lbDescription->setText(orDefault(th.description(),"<No Description>"));
		ui.lbAuthor->setText(orDefault(th.author(), "<Unknown Author>"));
		ui.lbDate->setText(tr("Date")+": "+th.date().toString(Qt::ISODate));
		ui.lbVersion->setText(tr("Version")+": "+th.version());
		ui.lbLicense->setText(tr("License")+": "+th.license());
		ui.lbAuthorTag->setVisible(true);
		previewLabel->setScaledPixmap(th.previewImage());
	} else {
		AbstractTemplateRessource *res = (currentItem) ? (currentItem->data(0, RessourceRole).value<AbstractTemplateRessource *>()) : 0;
		// if !res the currentItem is invalid
		pbOk->setEnabled(false);
		ui.lbName->setText(res ? res->name() : "");
		ui.lbDescription->setText(res ? res->description() : "");
		ui.lbAuthor->setText("");
		ui.lbDate->setText("");
		ui.lbVersion->setText("");
		ui.lbLicense->setText("");
		ui.lbAuthorTag->setVisible(false);
		previewLabel->setScaledPixmap(QPixmap());
	}
}

void TemplateSelector::templatesTreeContextMenu(QPoint point) {
	TemplateHandle th = selectedTemplate();
	if (!th.isValid()) return;

	QMenu menu(this);
	if (th.isEditable()) {
		menu.addAction(tr("Edit Template"), this, SLOT(editTemplate()));
		menu.addAction(tr("Edit Template Info"), this, SLOT(editTemplateInfo()));
		menu.addAction(tr("Remove"),this , SLOT(removeTemplate()));
		menu.addSeparator();
	}
	menu.addAction(tr("Open Template Location"), this, SLOT(openTemplateLocation()));
	menu.exec(ui.templatesTree->mapToGlobal(point));
}

void TemplateSelector::editTemplate() {
	TemplateHandle th = selectedTemplate();
	if (!th.isEditable()) {
		txsCritical(tr("This template cannot be edited."));
		return;
	}
	emit editTemplateRequest(th);
	close();
}

void TemplateSelector::editTemplateInfo() {
	TemplateHandle th = selectedTemplate();
	if (!th.isEditable()) {
		txsCritical(tr("This template cannot be edited."));
		return;
	}
	emit editTemplateInfoRequest(th);
	close();
}

void TemplateSelector::removeTemplate() {
	TemplateHandle th = selectedTemplate();
	if (!th.isEditable()) {
		txsCritical(tr("This template cannot be edited."));
		return;
	}
	QString fname = th.file();

	if(QMessageBox::question(this,tr("Please Confirm"), tr("Are you sure to delete the following template?")+QString("\n%1").arg(fname)
							 ,QMessageBox::Yes|QMessageBox::No,QMessageBox::No)==QMessageBox::Yes) {
		QTreeWidgetItem *currentItem = ui.templatesTree->currentItem();
		if (currentItem) {
			currentItem->parent()->removeChild(currentItem);
		}
		QFile file(fname);
		if(!file.remove()) txsCritical(tr("You do not have permission to remove this file.")+"\n"+fname);
		QFileInfo fi(fname);
		QFileInfo metafi(fi.dir(), fi.baseName()+".json");
		if (metafi.exists()) {
			file.setFileName(metafi.absoluteFilePath());
			if(!file.remove()) txsCritical(tr("You do not have permission to remove this file.")+"\n"+fname);
		}
	}
}

void TemplateSelector::openTemplateLocation() {
	TemplateHandle th = selectedTemplate();
	QString url = "file:///"+QFileInfo(th.file()).absolutePath();
	if (!QDesktopServices::openUrl(QUrl(url))) {
		txsCritical(tr("Could not open location")+QString("\n%1").arg(url));
	}
}

