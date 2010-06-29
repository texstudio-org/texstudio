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

	ui.comboBox->insertItem(0, "Menu 1");
	ui.comboBox->insertItem(1, "Menu 2");
	ui.comboBox->insertItem(2, "Menu 3");
	ui.comboBox->insertItem(3, "Menu 4");
	ui.comboBox->insertItem(4, "Menu 5");
	ui.comboBox->insertItem(5, "Menu 6");
	ui.comboBox->insertItem(6, "Menu 7");
	ui.comboBox->insertItem(7, "Menu 8");
	ui.comboBox->insertItem(8, "Menu 9");
	ui.comboBox->insertItem(9, "Menu 10");
        if(Tag.size()>10) {
            for(int i=10;i<Tag.size();i++)
                   ui.comboBox->insertItem(i, QString("Menu %1").arg(i));
        }
	connect(ui.comboBox, SIGNAL(activated(int)),this,SLOT(change(int)));

	connect(ui.okButton, SIGNAL(clicked()), SLOT(slotOk()));

	connect(ui.radioButtonNormal, SIGNAL(clicked()), SLOT(changeTypeToNormal()));
	connect(ui.radioButtonEnvironment, SIGNAL(clicked()), SLOT(changeTypeToEnvironment()));
	connect(ui.radioButtonScript, SIGNAL(clicked()), SLOT(changeTypeToScript()));

	//editor options
	ui.tagEdit->setLayout(new QVBoxLayout());
	codeedit = new QCodeEdit(ui.tagEdit);
	QLineMarkPanel* lineMarkPanel=new QLineMarkPanel;
	QAction* lineMarkPanelAction=codeedit->addPanel(lineMarkPanel, QCodeEdit::West, false);
	QLineNumberPanel* lineNumberPanel=new QLineNumberPanel;
	QAction* lineNumberPanelAction=codeedit->addPanel(lineNumberPanel, QCodeEdit::West, false);;
	QAction* lineFoldPanelAction=codeedit->addPanel(new QFoldPanel, QCodeEdit::West, false);
	//QAction* vlineChangePanelAction=codeedit->addPanel(new QLineChangePanel, QCodeEdit::West, false);

	QStatusPanel* statusPanel=new QStatusPanel;
	statusPanel->setFont(QApplication::font());
	QAction* statusPanelAction=codeedit->addPanel(statusPanel, QCodeEdit::South, false);

	QGotoLinePanel* gotoLinePanel=new QGotoLinePanel;
	gotoLinePanel->setFont(QApplication::font());
	QAction* gotoLinePanelAction=codeedit->addPanel(gotoLinePanel, QCodeEdit::South, false);

	QSearchReplacePanel* searchReplacePanel=new QSearchReplacePanel;
	searchReplacePanel->setFont(QApplication::font());
	QAction* searchReplacePanelAction=codeedit->addPanel(searchReplacePanel, QCodeEdit::South,false);

	ui.tagEdit->layout()->addWidget(codeedit->editor());

	connect(codeedit->editor()->document(), SIGNAL(contentsChanged()), SLOT(textChanged()));
}

UserMenuDialog::~UserMenuDialog() {
	delete codeedit;
}

void UserMenuDialog::init() {
	codeedit->editor()->setText(Tag[0]);
	ui.itemEdit->setText(Name[0]);
	ui.abbrevEdit->setText(Abbrev[0]);
	ui.comboBox->setCurrentIndex(0);
	if (languages) languages->setLanguage(codeedit->editor(), codeedit->editor()->text(0)!="%SCRIPT"?".tex":".qs");
}

void UserMenuDialog::change(int index) {
	Tag[previous_index]=codeedit->editor()->text();
	Name[previous_index]=ui.itemEdit->text();
	codeedit->editor()->setText(Tag[index]);
	ui.itemEdit->setText(Name[index]);
	ui.abbrevEdit->setText(Abbrev[index]);
	previous_index=index;
	if (languages) languages->setLanguage(codeedit->editor(), codeedit->editor()->text(0)!="%SCRIPT"?".tex":".qs");
}

void UserMenuDialog::slotOk() {
	Tag[previous_index]=codeedit->editor()->text();
	Name[previous_index]=ui.itemEdit->text();
	Abbrev[previous_index]=ui.abbrevEdit->text();
	accept();
}
void UserMenuDialog::changeTypeToNormal(){
	QString cur = codeedit->editor()->text();
	if (languages) languages->setLanguage(codeedit->editor(), ".tex");
	if (cur.startsWith("%SCRIPT\n")) codeedit->editor()->setText(cur.mid(8));
	else if (cur.startsWith("%")) codeedit->editor()->setText(cur.mid(1));
}
void UserMenuDialog::changeTypeToEnvironment(){
	QString cur = codeedit->editor()->text();
	if (languages) languages->setLanguage(codeedit->editor(), ".tex");
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
