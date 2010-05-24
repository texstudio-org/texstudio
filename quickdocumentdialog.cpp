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

#include "quickdocumentdialog.h"
#include "universalinputdialog.h"
#include "configmanagerinterface.h"

QStringList QuickDocumentDialog::otherClassList, QuickDocumentDialog::otherPaperList, QuickDocumentDialog::otherEncodingList, QuickDocumentDialog::otherOptionsList;
QString QuickDocumentDialog::document_class, QuickDocumentDialog::typeface_size, QuickDocumentDialog::paper_size, QuickDocumentDialog::document_encoding, QuickDocumentDialog::author;
bool QuickDocumentDialog::ams_packages, QuickDocumentDialog::makeidx_package;

QuickDocumentDialog::QuickDocumentDialog(QWidget *parent, const QString& name)
		:QDialog(parent) {
	setWindowTitle(name);
	setModal(true);
	ui.setupUi(this);
	connect(ui.pushButtonClass , SIGNAL(clicked()), SLOT(addUserClass()));
	ui.comboBoxSize->addItem("10pt");
	ui.comboBoxSize->addItem("11pt");
	ui.comboBoxSize->addItem("12pt");
	connect(ui.pushButtonPaper , SIGNAL(clicked()), SLOT(addUserPaper()));
	connect(ui.pushButtonEncoding , SIGNAL(clicked()), SLOT(addUserEncoding()));
	connect(ui.pushButtonOptions , SIGNAL(clicked()), SLOT(addUserOptions()));
	ui.listWidgetOptions->setSelectionMode(QAbstractItemView::ExtendedSelection);
	setWindowTitle(tr("Quick Start"));
}

QuickDocumentDialog::~QuickDocumentDialog() {
}

QString QuickDocumentDialog::getNewDocumentText(){
	QString opt="";
	int li=3;

	QString tag=QString("\\documentclass[");
	tag+=ui.comboBoxSize->currentText()+QString(",");
	tag+=ui.comboBoxPaper->currentText();
	QList<QListWidgetItem *> selectedItems=ui.listWidgetOptions->selectedItems();
	for (int i = 0; i < selectedItems.size(); ++i) {
		if (selectedItems.at(i)) opt+=QString(",")+selectedItems.at(i)->text();
	}
	tag+=opt+QString("]{");
	tag+=ui.comboBoxClass->currentText()+QString("}");
	tag+=QString("\n");
	if (ui.comboBoxEncoding->currentText()!="NONE") tag+=QString("\\usepackage[")+ui.comboBoxEncoding->currentText()+QString("]{inputenc}");
	tag+=QString("\n");
	if (ui.comboBoxEncoding->currentText().startsWith("utf8x")) {
		tag+=QString("\\usepackage{ucs}\n");
		li=li+1;
	}
	if (ui.checkBoxAMS->isChecked()) {
		tag+=QString("\\usepackage{amsmath}\n\\usepackage{amsfonts}\n\\usepackage{amssymb}\n");
		li=li+3;
	}
	if (ui.checkBoxIDX->isChecked()) {
		tag+=QString("\\usepackage{makeidx}\n");
		li=li+1;
	}
	if (ui.lineEditAuthor->text()!="") {
		tag+="\\author{"+ui.lineEditAuthor->text()+"}\n";
		li=li+1;
	}
	if (ui.lineEditTitle->text()!="") {
		tag+="\\title{"+ui.lineEditTitle->text()+"}\n";
		li=li+1;
	}
	tag+=QString("\\begin{document}\n\n\\end{document}");
	return tag;
}

void QuickDocumentDialog::registerOptions(ConfigManagerInterface& configManager){
	configManager.registerOption("Tools/User Class", &otherClassList);
	configManager.registerOption("Tools/User Paper", &otherPaperList);
	configManager.registerOption("Tools/User Encoding", &otherEncodingList);
	configManager.registerOption("Tools/User Options", &otherOptionsList);
	configManager.registerOption("Quick/Class", &document_class, "article");
	configManager.registerOption("Quick/Typeface", &typeface_size, "10pt");
	configManager.registerOption("Quick/Papersize",&paper_size, "a4paper");
	configManager.registerOption("Quick/Encoding",&document_encoding, "latin1");
	configManager.registerOption("Quick/AMS",&ams_packages, true);
	configManager.registerOption("Quick/MakeIndex",&makeidx_package, false);
	configManager.registerOption("Quick/Author",&author, "");
}

void QuickDocumentDialog::Init() {
	ui.comboBoxClass->clear();
	ui.comboBoxClass->addItem("article");
	ui.comboBoxClass->addItem("report");
	ui.comboBoxClass->addItem("letter");
	ui.comboBoxClass->addItem("book");
	ui.comboBoxClass->addItem("beamer");
	if (!otherClassList.isEmpty()) ui.comboBoxClass->addItems(otherClassList);

	ui.comboBoxPaper->clear();
	ui.comboBoxPaper->addItem("a4paper");
	ui.comboBoxPaper->addItem("a5paper");
	ui.comboBoxPaper->addItem("b5paper");
	ui.comboBoxPaper->addItem("letterpaper");
	ui.comboBoxPaper->addItem("legalpaper");
	ui.comboBoxPaper->addItem("executivepaper");
	if (!otherPaperList.isEmpty()) ui.comboBoxPaper->addItems(otherPaperList);

	ui.comboBoxEncoding->clear();
	ui.comboBoxEncoding->addItem("latin1");
	ui.comboBoxEncoding->addItem("latin2");
	ui.comboBoxEncoding->addItem("latin3");
	ui.comboBoxEncoding->addItem("latin5");
	ui.comboBoxEncoding->addItem("utf8");
	ui.comboBoxEncoding->addItem("utf8x");
	ui.comboBoxEncoding->addItem("ascii");
	ui.comboBoxEncoding->addItem("decmulti");
	ui.comboBoxEncoding->addItem("cp850");
	ui.comboBoxEncoding->addItem("cp852");
	ui.comboBoxEncoding->addItem("cp437");
	ui.comboBoxEncoding->addItem("cp437de");
	ui.comboBoxEncoding->addItem("cp865");
	ui.comboBoxEncoding->addItem("applemac");
	ui.comboBoxEncoding->addItem("next");
	ui.comboBoxEncoding->addItem("ansinew");
	ui.comboBoxEncoding->addItem("cp1252");
	ui.comboBoxEncoding->addItem("cp1250");
	ui.comboBoxEncoding->addItem("NONE");
	if (!otherEncodingList.isEmpty()) ui.comboBoxEncoding->addItems(otherEncodingList);

	ui.listWidgetOptions->clear();
	ui.listWidgetOptions->addItem("landscape");
	ui.listWidgetOptions->addItem("draft");
	ui.listWidgetOptions->addItem("final");
	ui.listWidgetOptions->addItem("oneside");
	ui.listWidgetOptions->addItem("twoside");
	ui.listWidgetOptions->addItem("openright");
	ui.listWidgetOptions->addItem("openany");
	ui.listWidgetOptions->addItem("onecolumn");
	ui.listWidgetOptions->addItem("twocolumn");
	ui.listWidgetOptions->addItem("titlepage");
	ui.listWidgetOptions->addItem("notitlepage");
	ui.listWidgetOptions->addItem("openbib");
	ui.listWidgetOptions->addItem("leqno");
	ui.listWidgetOptions->addItem("fleqn");
	if (!otherOptionsList.isEmpty()) ui.listWidgetOptions->addItems(otherOptionsList);

	int f=ui.comboBoxClass->findText(document_class,Qt::MatchExactly | Qt::MatchCaseSensitive);
	ui.comboBoxClass->setCurrentIndex(f);
	f=ui.comboBoxSize->findText(typeface_size,Qt::MatchExactly | Qt::MatchCaseSensitive);
	ui.comboBoxSize->setCurrentIndex(f);
	f=ui.comboBoxPaper->findText(paper_size,Qt::MatchExactly | Qt::MatchCaseSensitive);
	ui.comboBoxPaper->setCurrentIndex(f);
	f=ui.comboBoxEncoding->findText(document_encoding,Qt::MatchExactly | Qt::MatchCaseSensitive);
	ui.comboBoxEncoding->setCurrentIndex(f);
	ui.checkBoxAMS->setChecked(ams_packages);
	ui.checkBoxIDX->setChecked(makeidx_package);
	ui.lineEditAuthor->setText(author);

}

void QuickDocumentDialog::accept(){
	document_class=ui.comboBoxClass->currentText();
	typeface_size=ui.comboBoxSize->currentText();
	paper_size=ui.comboBoxPaper->currentText();
	document_encoding=ui.comboBoxEncoding->currentText();
	ams_packages=ui.checkBoxAMS->isChecked();
	makeidx_package=ui.checkBoxIDX->isChecked();
	author=ui.lineEditAuthor->text();
	QDialog::accept();
}

void QuickDocumentDialog::addUserClass() {
	QString newoption;
	UniversalInputDialog dialog;
	dialog.addVariable(&newoption, tr("New:"));
	if (dialog.exec() && !newoption.isEmpty()) {
		otherClassList.append(newoption);
		Init();
	}
}

void QuickDocumentDialog::addUserPaper() {
	QString newoption;
	UniversalInputDialog dialog;
	dialog.addVariable(&newoption, tr("New:"));
	if (dialog.exec() && !newoption.isEmpty()) {
		otherPaperList.append(newoption);
		Init();
	}
}

void QuickDocumentDialog::addUserEncoding() {
	QString newoption;
	UniversalInputDialog dialog;
	dialog.addVariable(&newoption, tr("New:"));
	if (dialog.exec() && !newoption.isEmpty()) {
		otherEncodingList.append(newoption);
		Init();
	}
}

void QuickDocumentDialog::addUserOptions() {
	QString newoption;
	UniversalInputDialog dialog;
	dialog.addVariable(&newoption, tr("New:"));
	if (dialog.exec() && !newoption.isEmpty()) {
		otherOptionsList.append(newoption);
		Init();
	}
}
