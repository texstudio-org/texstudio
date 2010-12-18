/***************************************************************************
 *   copyright       : (C) 2003-2007 by Pascal Brachet                     *
 *   http://www.xm1math.net/texmaker/                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "usermenudialog.h"

#include "qcodeedit.h"
#include "qeditor.h"
#include "qlanguagefactory.h"
#include "qlinemarkpanel.h"
#include "qlinenumberpanel.h"
#include "qstatuspanel.h"
#include "qgotolinepanel.h"
#include "qsearchreplacepanel.h"
#include "qfoldpanel.h"

UserMenuDialog::UserMenuDialog(QWidget* parent,  QString name, QLanguageFactory* languageFactory)
		: QDialog(parent), languages(languageFactory) {
	setWindowTitle(name);
	setModal(true);
	ui.setupUi(this);

	previous_index=0;

	connect(ui.comboBox, SIGNAL(activated(int)),this,SLOT(change(int)));

	connect(ui.okButton, SIGNAL(clicked()), SLOT(slotOk()));

	connect(ui.pushButtonAdd, SIGNAL(clicked()), SLOT(slotAdd()));
	connect(ui.pushButtonRemove, SIGNAL(clicked()), SLOT(slotRemove()));


	connect(ui.radioButtonNormal, SIGNAL(clicked()), SLOT(changeTypeToNormal()));
	connect(ui.radioButtonEnvironment, SIGNAL(clicked()), SLOT(changeTypeToEnvironment()));
	connect(ui.radioButtonScript, SIGNAL(clicked()), SLOT(changeTypeToScript()));

	//editor options
	ui.tagEdit->setLayout(new QVBoxLayout());
	codeedit = new QCodeEdit(ui.tagEdit);
	QLineMarkPanel* lineMarkPanel=new QLineMarkPanel;
	QAction* lineMarkPanelAction=codeedit->addPanel(lineMarkPanel, QCodeEdit::West, false);
	Q_UNUSED(lineMarkPanelAction)
	QLineNumberPanel* lineNumberPanel=new QLineNumberPanel;
	QAction* lineNumberPanelAction=codeedit->addPanel(lineNumberPanel, QCodeEdit::West, false);;
	Q_UNUSED(lineNumberPanelAction)
	QAction* lineFoldPanelAction=codeedit->addPanel(new QFoldPanel, QCodeEdit::West, false);
	Q_UNUSED(lineFoldPanelAction)
	//QAction* vlineChangePanelAction=codeedit->addPanel(new QLineChangePanel, QCodeEdit::West, false);

	QStatusPanel* statusPanel=new QStatusPanel;
	statusPanel->setFont(QApplication::font());
	QAction* statusPanelAction=codeedit->addPanel(statusPanel, QCodeEdit::South, false);
	Q_UNUSED(statusPanelAction)

	QGotoLinePanel* gotoLinePanel=new QGotoLinePanel;
	gotoLinePanel->setFont(QApplication::font());
	QAction* gotoLinePanelAction=codeedit->addPanel(gotoLinePanel, QCodeEdit::South, false);
	Q_UNUSED(gotoLinePanelAction)

	searchReplacePanel=new QSearchReplacePanel;
	searchReplacePanel->setFont(QApplication::font());
	QAction* searchReplacePanelAction=codeedit->addPanel(searchReplacePanel, QCodeEdit::South,false);
	searchReplacePanel->display(0,false);
	Q_UNUSED(searchReplacePanelAction)

	ui.tagEdit->layout()->addWidget(codeedit->editor());

	connect(codeedit->editor()->document(), SIGNAL(contentsChanged()), SLOT(textChanged()));
}

UserMenuDialog::~UserMenuDialog() {
	delete searchReplacePanel;
	delete codeedit;
}

void UserMenuDialog::init() {
	for(int i=1;i<=Tag.size();i++)
		ui.comboBox->insertItem(i-1, tr("Menu %1").arg(i));

	codeedit->editor()->setText(Tag.value(0,""));
	ui.itemEdit->setText(Name.value(0,""));
	ui.abbrevEdit->setText(Abbrev.value(0,""));
	ui.comboBox->setCurrentIndex(0);
	if (languages){
		if (codeedit->editor()->text(0)=="%SCRIPT") languages->setLanguage(codeedit->editor(), ".qs");
		else if (codeedit->editor()->text(0).startsWith("%")) languages->setLanguage(codeedit->editor(), "");
		else languages->setLanguage(codeedit->editor(), "(La-)TeX Macro");
	}
}

void UserMenuDialog::change(int index) {
	if (Tag.isEmpty() || Name.isEmpty() || Abbrev.isEmpty())  return;
	Q_ASSERT(previous_index < Tag.size() && previous_index < Name.size() && previous_index < Abbrev.size());

	if (previous_index != -1) {
		Tag[previous_index] = codeedit->editor()->text();
		Name[previous_index] = ui.itemEdit->text();
		Abbrev[previous_index] = ui.abbrevEdit->text();
	}

	codeedit->editor()->setText(Tag.value(index,""));
	ui.itemEdit->setText(Name.value(index,""));
	ui.abbrevEdit->setText(Abbrev.value(index,""));

	previous_index=index;
	if (languages){
		if (codeedit->editor()->text(0)=="%SCRIPT") languages->setLanguage(codeedit->editor(), ".qs");
		else if (codeedit->editor()->text(0).startsWith("%")) languages->setLanguage(codeedit->editor(), "");
		else languages->setLanguage(codeedit->editor(), "(La-)TeX Macro");
	}
}

void UserMenuDialog::slotOk() {
	if (!Tag.isEmpty() && !Name.isEmpty() && !Abbrev.isEmpty() && previous_index != -1)  {
		Q_ASSERT(previous_index < Tag.size() && previous_index < Name.size() && previous_index < Abbrev.size());
		Tag[previous_index]=codeedit->editor()->text();
		Name[previous_index]=ui.itemEdit->text();
		Abbrev[previous_index]=ui.abbrevEdit->text();
	}
	accept();
}
void UserMenuDialog::slotAdd(){
	Name << "";
	Tag << "";
	Abbrev << "";
	ui.comboBox->addItem(tr("Menu %1").arg(ui.comboBox->count()+1));
}

void UserMenuDialog::slotRemove(){
	if (QMessageBox::question(this, "TexMakerX", "Do you really want to delete the current macro?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
		Name.removeAt(ui.comboBox->currentIndex());
		Tag.removeAt(ui.comboBox->currentIndex());
		Abbrev.removeAt(ui.comboBox->currentIndex());
		previous_index = -1;
		ui.comboBox->removeItem(ui.comboBox->currentIndex());
		change(ui.comboBox->currentIndex());
	}
}

void UserMenuDialog::changeTypeToNormal(){
	QString cur = codeedit->editor()->text();
	if (languages) languages->setLanguage(codeedit->editor(), "(La-)TeX Macro");
	if (cur.startsWith("%SCRIPT\n")) codeedit->editor()->setText(cur.mid(8));
	else if (cur.startsWith("%")) codeedit->editor()->setText(cur.mid(1));
}
void UserMenuDialog::changeTypeToEnvironment(){
	QString cur = codeedit->editor()->text();
	if (languages) languages->setLanguage(codeedit->editor(), "");
	if (cur.startsWith("%SCRIPT")) {
		codeedit->editor()->setText("%"+cur.mid(8));
	} else {
		if (cur.startsWith("%")) return;
		codeedit->editor()->setText("%"+cur);
	}
}
void UserMenuDialog::changeTypeToScript(){
	QString cur = codeedit->editor()->text();
	if (languages) languages->setLanguage(codeedit->editor(), ".qs");
	if (cur.startsWith("%SCRIPT\n")) return;
	if (cur.startsWith("%")) cur = cur.mid(1);
	codeedit->editor()->setText("%SCRIPT\n"+cur);
}
void UserMenuDialog::textChanged(){
	QString line = codeedit->editor()->text(0);
	if (line=="%SCRIPT") ui.radioButtonScript->setChecked(true);
	else if (line.startsWith("%")) ui.radioButtonEnvironment->setChecked(true);
	else ui.radioButtonNormal->setChecked(true);
}
