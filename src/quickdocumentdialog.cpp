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
#include "utilsUI.h"

qreal convertLatexLengthToMetre(const qreal &length, const QString &unit)
{
	static const qreal inchInMetre = 0.0254;
	static const qreal pointInMetre = inchInMetre / 72.27;
	static const qreal bigPointInMetre = inchInMetre / 72;
	QString lunit = unit.toLower();
	if (lunit == "pt") return length * pointInMetre;
	if (lunit == "bp") return length * bigPointInMetre;
	if (lunit == "cm") return length * 0.01;
	if (lunit == "dm") return length * 0.1;
	if (lunit == "in") return length * inchInMetre;
	/*if (unit == "mm")*/ return length * 0.001;
}

//options for the configmanager
QStringList QuickDocumentDialog::otherClassList, QuickDocumentDialog::otherPaperList, QuickDocumentDialog::otherInputEncodingList, QuickDocumentDialog::otherFontEncodingList, QuickDocumentDialog::otherBabelOptionsList, QuickDocumentDialog::otherOptionsList;
QString QuickDocumentDialog::document_class, QuickDocumentDialog::typeface_size, QuickDocumentDialog::paper_size, QuickDocumentDialog::document_encoding, QuickDocumentDialog::font_encoding, QuickDocumentDialog::babel_language, QuickDocumentDialog::author;
bool QuickDocumentDialog::ams_packages, QuickDocumentDialog::makeidx_package, QuickDocumentDialog::graphicx_package;
double geometryPageWidth, geometryPageHeight, geometryMarginLeft, geometryMarginRight, geometryMarginTop, geometryMarginBottom;
QString geometryPageWidthUnit, geometryPageHeightUnit, geometryMarginLeftUnit, geometryMarginRightUnit, geometryMarginTopUnit, geometryMarginBottomUnit;
bool geometryPageWidthEnabled, geometryPageHeightEnabled, geometryMarginLeftEnabled, geometryMarginRightEnabled, geometryMarginTopEnabled, geometryMarginBottomEnabled;

ConfigManagerInterface *QuickDocumentDialog::configManagerInterface;


QuickDocumentDialog::QuickDocumentDialog(QWidget *parent, const QString &name)
	: QDialog(parent)
{
	setWindowTitle(name);
	setModal(true);
	ui.setupUi(this);
	UtilsUi::resizeInFontHeight(this, 39, 37);

	connect(ui.pushButtonClass , SIGNAL(clicked()), SLOT(addUserClass()));
	ui.comboBoxSize->addItem("10pt");
	ui.comboBoxSize->addItem("11pt");
	ui.comboBoxSize->addItem("12pt");
	connect(ui.pushButtonPaper , SIGNAL(clicked()), SLOT(addUserPaper()));
	connect(ui.pushButtonInputEncoding , SIGNAL(clicked()), SLOT(addUserInputEncoding()));
	connect(ui.pushButtonFontEncoding , SIGNAL(clicked()), SLOT(addUserFontEncoding()));
	connect(ui.pushButtonBabel, SIGNAL(clicked()), SLOT(addBabelOption()));
	connect(ui.pushButtonOptions , SIGNAL(clicked()), SLOT(addUserOptions()));
	ui.listWidgetOptions->setSelectionMode(QAbstractItemView::ExtendedSelection);
	setWindowTitle(tr("Quick Start"));

	//Geometry package
	connect(ui.spinBoxUnitGeometryPageWidth, SIGNAL(editTextChanged(QString)), SLOT(geometryUnitsChanged()));
	connect(ui.spinBoxUnitGeometryPageHeight, SIGNAL(editTextChanged(QString)), SLOT(geometryUnitsChanged()));
	connect(ui.spinBoxUnitGeometryMarginLeft, SIGNAL(editTextChanged(QString)), SLOT(geometryUnitsChanged()));
	connect(ui.spinBoxUnitGeometryMarginRight, SIGNAL(editTextChanged(QString)), SLOT(geometryUnitsChanged()));
	connect(ui.spinBoxUnitGeometryMarginTop, SIGNAL(editTextChanged(QString)), SLOT(geometryUnitsChanged()));
	connect(ui.spinBoxUnitGeometryMarginBottom, SIGNAL(editTextChanged(QString)), SLOT(geometryUnitsChanged()));

	connect(ui.spinBoxGeometryPageWidth, SIGNAL(valueChanged(double)), SLOT(geometryValuesChanged()));
	connect(ui.spinBoxGeometryPageHeight, SIGNAL(valueChanged(double)), SLOT(geometryValuesChanged()));
	connect(ui.spinBoxGeometryMarginLeft, SIGNAL(valueChanged(double)), SLOT(geometryValuesChanged()));
	connect(ui.spinBoxGeometryMarginRight, SIGNAL(valueChanged(double)), SLOT(geometryValuesChanged()));
	connect(ui.spinBoxGeometryMarginTop, SIGNAL(valueChanged(double)), SLOT(geometryValuesChanged()));
	connect(ui.spinBoxGeometryMarginBottom, SIGNAL(valueChanged(double)), SLOT(geometryValuesChanged()));

	connect(ui.checkBoxGeometryPageWidth, SIGNAL(toggled(bool)), SLOT(geometryValuesChanged()));
	connect(ui.checkBoxGeometryPageHeight, SIGNAL(toggled(bool)), SLOT(geometryValuesChanged()));
	connect(ui.checkBoxGeometryMarginLeft, SIGNAL(toggled(bool)), SLOT(geometryValuesChanged()));
	connect(ui.checkBoxGeometryMarginRight, SIGNAL(toggled(bool)), SLOT(geometryValuesChanged()));
	connect(ui.checkBoxGeometryMarginTop, SIGNAL(toggled(bool)), SLOT(geometryValuesChanged()));
	connect(ui.checkBoxGeometryMarginBottom, SIGNAL(toggled(bool)), SLOT(geometryValuesChanged()));

	connect(ui.tabWidget, SIGNAL(currentChanged(int)), SLOT(geometryValuesChanged()));
}

QuickDocumentDialog::~QuickDocumentDialog()
{
}

QString QuickDocumentDialog::getNewDocumentText()
{
	QString opt = "";
	QString tag = QString("\\documentclass[");
	tag += ui.comboBoxSize->currentText() + QString(",");
	tag += ui.comboBoxPaper->currentText();
	QList<QListWidgetItem *> selectedItems = ui.listWidgetOptions->selectedItems();
	for (int i = 0; i < selectedItems.size(); ++i) {
		if (selectedItems.at(i)) opt += QString(",") + selectedItems.at(i)->text();
	}
	tag += opt + QString("]{");
	tag += ui.comboBoxClass->currentText() + QString("}");
	tag += QString("\n");
	if (ui.comboBoxInputEncoding->currentText() != "NONE") {
		tag += QString("\\usepackage[") + ui.comboBoxInputEncoding->currentText() + QString("]{inputenc}");
		tag += QString("\n");
	}
	if (ui.comboBoxFontEncoding->currentText() != "NONE") {
		tag += QString("\\usepackage[") + ui.comboBoxFontEncoding->currentText() + QString("]{fontenc}");
		tag += QString("\n");
	}
	if (ui.comboBoxInputEncoding->currentText().startsWith("utf8x"))
		tag += QString("\\usepackage{ucs}\n");
	if (ui.comboBoxBabel->currentText() != "NONE")
		tag += QString("\\usepackage[%1]{babel}\n").arg(ui.comboBoxBabel->currentText());
	if (ui.checkBoxAMS->isChecked())
		tag += QString("\\usepackage{amsmath}\n\\usepackage{amsfonts}\n\\usepackage{amssymb}\n");
	if (ui.checkBoxIDX->isChecked())
		tag += QString("\\usepackage{makeidx}\n");
	if (ui.checkBoxGraphicx->isChecked())
		tag += QString("\\usepackage{graphicx}\n");

	if (ui.checkBoxGeometryPageWidth->isChecked() ||
	        ui.checkBoxGeometryPageHeight->isChecked() ||
	        ui.checkBoxGeometryMarginLeft->isChecked() ||
	        ui.checkBoxGeometryMarginRight->isChecked() ||
	        ui.checkBoxGeometryMarginBottom->isChecked() ||
	        ui.checkBoxGeometryMarginTop->isChecked()) {
		QString geometryOptions;
		if (ui.checkBoxGeometryPageWidth->isChecked()) geometryOptions += ", width=" + ui.spinBoxGeometryPageWidth->text();
		if (ui.checkBoxGeometryPageHeight->isChecked()) geometryOptions += ", height=" + ui.spinBoxGeometryPageHeight->text();
		if (ui.checkBoxGeometryMarginLeft->isChecked()) geometryOptions += ", left=" + ui.spinBoxGeometryMarginLeft->text();
		if (ui.checkBoxGeometryMarginRight->isChecked()) geometryOptions += ", right=" + ui.spinBoxGeometryMarginRight->text();
		if (ui.checkBoxGeometryMarginTop->isChecked()) geometryOptions += ", top=" + ui.spinBoxGeometryMarginTop->text();
		if (ui.checkBoxGeometryMarginBottom->isChecked()) geometryOptions += ", bottom=" + ui.spinBoxGeometryMarginBottom->text();
		geometryOptions.remove(0, 2);
		tag += "\\usepackage[" + geometryOptions + "]{geometry}\n";
	}

	if (ui.lineEditAuthor->text() != "")
		tag += "\\author{" + ui.lineEditAuthor->text() + "}\n";
	if (ui.lineEditTitle->text() != "")
		tag += "\\title{" + ui.lineEditTitle->text() + "}\n";

	tag += QString("\\begin{document}\n%|\n\\end{document}");
	return tag;
}

void QuickDocumentDialog::registerOptions(ConfigManagerInterface &configManager)
{
	configManager.registerOption("Tools/User Class", &otherClassList);
	configManager.registerOption("Tools/User Paper", &otherPaperList);
	configManager.registerOption("Tools/User Encoding", &otherInputEncodingList);
	configManager.registerOption("Tools/User Font Encoding", &otherFontEncodingList);
	configManager.registerOption("Tools/User Babel Options", &otherBabelOptionsList);
	configManager.registerOption("Tools/User Options", &otherOptionsList);
	configManager.registerOption("Quick/Class", &document_class, "article");
	configManager.registerOption("Quick/Typeface", &typeface_size, "10pt");
	configManager.registerOption("Quick/Papersize", &paper_size, "a4paper");
	configManager.registerOption("Quick/Encoding", &document_encoding, "utf8");
	configManager.registerOption("Quick/FontEncoding", &font_encoding, "T1");
	configManager.registerOption("Quick/Babel", &babel_language, "NONE");
	configManager.registerOption("Quick/AMS", &ams_packages, true);
	configManager.registerOption("Quick/MakeIndex", &makeidx_package, false);
	configManager.registerOption("Quick/graphicx", &graphicx_package, true);
	configManager.registerOption("Quick/Author", &author, "");

	configManager.registerOption("Quick/Geometry Page Width", &geometryPageWidth, 0.0f);
	configManager.registerOption("Quick/Geometry Page Height", &geometryPageHeight, 0.0f);
	configManager.registerOption("Quick/Geometry Margin Left", &geometryMarginLeft, 0.0f);
	configManager.registerOption("Quick/Geometry Margin Right", &geometryMarginRight, 0.0f);
	configManager.registerOption("Quick/Geometry Margin Top", &geometryMarginTop, 0.0f);
	configManager.registerOption("Quick/Geometry Margin Bottom", &geometryMarginBottom, 0.0f);

	configManager.registerOption("Quick/Geometry Page Width Unit", &geometryPageWidthUnit, "cm");
	configManager.registerOption("Quick/Geometry Page Height Unit", &geometryPageHeightUnit, "cm");
	configManager.registerOption("Quick/Geometry Margin Left Unit", &geometryMarginLeftUnit, "cm");
	configManager.registerOption("Quick/Geometry Margin Right Unit", &geometryMarginRightUnit, "cm");
	configManager.registerOption("Quick/Geometry Margin Top Unit", &geometryMarginTopUnit, "cm");
	configManager.registerOption("Quick/Geometry Margin Bottom Unit", &geometryMarginBottomUnit, "cm");

	configManager.registerOption("Quick/Geometry Page Width Enabled", &geometryPageWidthEnabled, false);
	configManager.registerOption("Quick/Geometry Page Height Enabled", &geometryPageHeightEnabled, false);
	configManager.registerOption("Quick/Geometry Margin Left Enabled", &geometryMarginLeftEnabled, false);
	configManager.registerOption("Quick/Geometry Margin Right Enabled", &geometryMarginRightEnabled, false);
	configManager.registerOption("Quick/Geometry Margin Top Enabled", &geometryMarginTopEnabled, false);
	configManager.registerOption("Quick/Geometry Margin Bottom Enabled", &geometryMarginBottomEnabled, false);

	configManagerInterface = &configManager;
}

QStringList babelLanguages = QStringList()
  << "arabic"
  << "czech"
  << "dutch"
  << "english"
  << "farsi"
  << "finnish"
  << "french"
  << "ngerman"
  << "greek"
  << "icelandic"
  << "italian"
  << "magyar"
  << "polish"
  << "portuguese"
  << "russian"
  << "slovak"
  << "spanish" ;

void QuickDocumentDialog::Init()
{
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

	ui.comboBoxInputEncoding->clear();
	ui.comboBoxInputEncoding->addItem("latin1");
	ui.comboBoxInputEncoding->addItem("latin2");
	ui.comboBoxInputEncoding->addItem("latin3");
	ui.comboBoxInputEncoding->addItem("latin5");
	ui.comboBoxInputEncoding->addItem("utf8");
	ui.comboBoxInputEncoding->addItem("utf8x");
	ui.comboBoxInputEncoding->addItem("ascii");
	ui.comboBoxInputEncoding->addItem("decmulti");
	ui.comboBoxInputEncoding->addItem("cp850");
	ui.comboBoxInputEncoding->addItem("cp852");
	ui.comboBoxInputEncoding->addItem("cp437");
	ui.comboBoxInputEncoding->addItem("cp437de");
	ui.comboBoxInputEncoding->addItem("cp865");
	ui.comboBoxInputEncoding->addItem("applemac");
	ui.comboBoxInputEncoding->addItem("next");
	ui.comboBoxInputEncoding->addItem("ansinew");
	ui.comboBoxInputEncoding->addItem("cp1252");
	ui.comboBoxInputEncoding->addItem("cp1250");
	ui.comboBoxInputEncoding->addItem("NONE");
	if (!otherInputEncodingList.isEmpty()) ui.comboBoxInputEncoding->addItems(otherInputEncodingList);

	ui.comboBoxFontEncoding->clear();
	ui.comboBoxFontEncoding->addItem("OT1");
	ui.comboBoxFontEncoding->addItem("OT2");
	ui.comboBoxFontEncoding->addItem("OT3");
	ui.comboBoxFontEncoding->addItem("OT4");
	ui.comboBoxFontEncoding->addItem("OT5");
	ui.comboBoxFontEncoding->addItem("OT6");
	ui.comboBoxFontEncoding->addItem("T1");
	ui.comboBoxFontEncoding->addItem("T2A");
	ui.comboBoxFontEncoding->addItem("T2B");
	ui.comboBoxFontEncoding->addItem("T2C");
	ui.comboBoxFontEncoding->addItem("T3");
	ui.comboBoxFontEncoding->addItem("T4");
	ui.comboBoxFontEncoding->addItem("T5");
	ui.comboBoxFontEncoding->addItem("T6");
	ui.comboBoxFontEncoding->addItem("T7");
	ui.comboBoxFontEncoding->addItem("TS1");
	ui.comboBoxFontEncoding->addItem("TS3");
	ui.comboBoxFontEncoding->addItem("X2");
	ui.comboBoxFontEncoding->addItem("OML");
	ui.comboBoxFontEncoding->addItem("OMS");
	ui.comboBoxFontEncoding->addItem("OMX");
	ui.comboBoxFontEncoding->addItem("C..");
	ui.comboBoxFontEncoding->addItem("E..");
	ui.comboBoxFontEncoding->addItem("L..");
	ui.comboBoxFontEncoding->addItem("LY1");
	ui.comboBoxFontEncoding->addItem("LV1");
	ui.comboBoxFontEncoding->addItem("LGR");
	ui.comboBoxFontEncoding->addItem("PD1");
	ui.comboBoxFontEncoding->addItem("PU");
	ui.comboBoxFontEncoding->addItem("U");
	ui.comboBoxFontEncoding->addItem("NONE");
	if (!otherFontEncodingList.isEmpty()) ui.comboBoxFontEncoding->addItems(otherFontEncodingList);

	ui.comboBoxBabel->clear();
	ui.comboBoxBabel->addItem("NONE");
	ui.comboBoxBabel->addItems(babelLanguages);
	if (!otherBabelOptionsList.isEmpty()) ui.comboBoxBabel->addItems(otherBabelOptionsList);

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


	configManagerInterface->linkOptionToDialogWidget(&document_class, ui.comboBoxClass);
	configManagerInterface->linkOptionToDialogWidget(&typeface_size, ui.comboBoxSize);
	configManagerInterface->linkOptionToDialogWidget(&paper_size, ui.comboBoxPaper);
	configManagerInterface->linkOptionToDialogWidget(&document_encoding, ui.comboBoxInputEncoding);
	configManagerInterface->linkOptionToDialogWidget(&font_encoding, ui.comboBoxFontEncoding);
	configManagerInterface->linkOptionToDialogWidget(&babel_language, ui.comboBoxBabel);
	configManagerInterface->linkOptionToDialogWidget(&ams_packages, ui.checkBoxAMS);
	configManagerInterface->linkOptionToDialogWidget(&makeidx_package, ui.checkBoxIDX);
	configManagerInterface->linkOptionToDialogWidget(&graphicx_package, ui.checkBoxGraphicx);
	configManagerInterface->linkOptionToDialogWidget(&author, ui.lineEditAuthor);

	configManagerInterface->linkOptionToDialogWidget(&geometryPageWidth, ui.spinBoxGeometryPageWidth);
	configManagerInterface->linkOptionToDialogWidget(&geometryPageHeight, ui.spinBoxGeometryPageHeight);
	configManagerInterface->linkOptionToDialogWidget(&geometryMarginLeft, ui.spinBoxGeometryMarginLeft);
	configManagerInterface->linkOptionToDialogWidget(&geometryMarginRight, ui.spinBoxGeometryMarginRight);
	configManagerInterface->linkOptionToDialogWidget(&geometryMarginTop, ui.spinBoxGeometryMarginTop);
	configManagerInterface->linkOptionToDialogWidget(&geometryMarginBottom, ui.spinBoxGeometryMarginBottom);

	configManagerInterface->linkOptionToDialogWidget(&geometryPageWidthUnit, ui.spinBoxUnitGeometryPageWidth);
	configManagerInterface->linkOptionToDialogWidget(&geometryPageHeightUnit, ui.spinBoxUnitGeometryPageHeight);
	configManagerInterface->linkOptionToDialogWidget(&geometryMarginLeftUnit, ui.spinBoxUnitGeometryMarginLeft);
	configManagerInterface->linkOptionToDialogWidget(&geometryMarginRightUnit, ui.spinBoxUnitGeometryMarginRight);
	configManagerInterface->linkOptionToDialogWidget(&geometryMarginTopUnit, ui.spinBoxUnitGeometryMarginTop);
	configManagerInterface->linkOptionToDialogWidget(&geometryMarginBottomUnit, ui.spinBoxUnitGeometryMarginBottom);

	configManagerInterface->linkOptionToDialogWidget(&geometryPageWidthEnabled, ui.checkBoxGeometryPageWidth);
	configManagerInterface->linkOptionToDialogWidget(&geometryPageHeightEnabled, ui.checkBoxGeometryPageHeight);
	configManagerInterface->linkOptionToDialogWidget(&geometryMarginLeftEnabled, ui.checkBoxGeometryMarginLeft);
	configManagerInterface->linkOptionToDialogWidget(&geometryMarginRightEnabled, ui.checkBoxGeometryMarginRight);
	configManagerInterface->linkOptionToDialogWidget(&geometryMarginTopEnabled, ui.checkBoxGeometryMarginTop);
	configManagerInterface->linkOptionToDialogWidget(&geometryMarginBottomEnabled, ui.checkBoxGeometryMarginBottom);
}

void QuickDocumentDialog::accept()
{
	QDialog::accept();
}

void QuickDocumentDialog::geometryUnitsChanged()
{
	//update all units (easier than just the changed one, slower, but need probably less memory)
	ui.spinBoxGeometryPageWidth->setSuffix(ui.spinBoxUnitGeometryPageWidth->currentText());
	ui.spinBoxGeometryPageHeight->setSuffix(ui.spinBoxUnitGeometryPageHeight->currentText());
	ui.spinBoxGeometryMarginLeft->setSuffix(ui.spinBoxUnitGeometryMarginLeft->currentText());
	ui.spinBoxGeometryMarginRight->setSuffix(ui.spinBoxUnitGeometryMarginRight->currentText());
	ui.spinBoxGeometryMarginTop->setSuffix(ui.spinBoxUnitGeometryMarginTop->currentText());
	ui.spinBoxGeometryMarginBottom->setSuffix(ui.spinBoxUnitGeometryMarginBottom->currentText());

	if (sender() == ui.spinBoxUnitGeometryPageWidth) ui.checkBoxGeometryPageWidth->setChecked(true);
	else if (sender() == ui.spinBoxUnitGeometryPageHeight) ui.checkBoxGeometryPageHeight->setChecked(true);
	else if (sender() == ui.spinBoxUnitGeometryMarginLeft) ui.checkBoxGeometryMarginLeft->setChecked(true);
	else if (sender() == ui.spinBoxUnitGeometryMarginRight) ui.checkBoxGeometryMarginRight->setChecked(true);
	else if (sender() == ui.spinBoxUnitGeometryMarginTop) ui.checkBoxGeometryMarginTop->setChecked(true);
	else if (sender() == ui.spinBoxUnitGeometryMarginBottom) ui.checkBoxGeometryMarginBottom->setChecked(true);
}

void calculatePaperLength(qreal paper, qreal &left, qreal &body, qreal &right, qreal defaultLeftRatio)
{
	//all can be unknown
	if (body == -1 && (left == -1 || right == -1)) body = 0.7 * paper; //this is the behaviour of geometry package 5, in version 4 it would first set the other margin if one is given
	//either body or both margins are known
	if (left == -1 && right == -1) {
		left = (paper - body) * defaultLeftRatio;
		right = paper - body - left;
	}
	//only one value can be unknown
	if (left == -1) left = paper - body - right;
	if (right == -1) right = paper - left - body;

	//forget body
	body = paper - left - right;

}

void QuickDocumentDialog::geometryValuesChanged()
{
	//if a value is changed, enable it (I just don't like to create 12 slots for this, where are you lambda?)
	if (sender() == ui.spinBoxGeometryPageWidth) ui.checkBoxGeometryPageWidth->setChecked(true);
	else if (sender() == ui.spinBoxGeometryPageHeight) ui.checkBoxGeometryPageHeight->setChecked(true);
	else if (sender() == ui.spinBoxGeometryMarginLeft) ui.checkBoxGeometryMarginLeft->setChecked(true);
	else if (sender() == ui.spinBoxGeometryMarginRight) ui.checkBoxGeometryMarginRight->setChecked(true);
	else if (sender() == ui.spinBoxGeometryMarginTop) ui.checkBoxGeometryMarginTop->setChecked(true);
	else if (sender() == ui.spinBoxGeometryMarginBottom) ui.checkBoxGeometryMarginBottom->setChecked(true);

	static const QStringList paperFormats = QStringList()
	                                        << "a0paper" << "841" << "1189" << "mm"
	                                        << "a1paper" << "594" << "841" << "mm"
	                                        << "a2paper" << "420" << "594" << "mm"
	                                        << "a3paper" << "297" << "420" << "mm"
	                                        << "a4paper" << "210" << "297" << "mm"
	                                        << "a5paper" << "148" << "210" << "mm"
	                                        << "a6paper" << "105" << "148" << "mm"
	                                        << "b0paper" << "1000" << "1414" << "mm"
	                                        << "b1paper" << "707" << "1000" << "mm"
	                                        << "b2paper" << "500" << "707" << "mm"
	                                        << "b3paper" << "353" << "500" << "mm"
	                                        << "b4paper" << "250" << "353" << "mm"
	                                        << "b5paper" << "176" << "250" << "mm"
	                                        << "b6paper" << "125" << "176" << "mm"
	                                        << "b0j" << "1030" << "1456" << "mm"
	                                        << "b1j" << "728" << "1030" << "mm"
	                                        << "b2j" << "515" << "728" << "mm"
	                                        << "b3j" << "364" << "515" << "mm"
	                                        << "b4j" << "257" << "364" << "mm"
	                                        << "b5j" << "182" << "257" << "mm"
	                                        << "b6j" << "128" << "182" << "mm"
	                                        << "ansiapaper" << "8.5" << "11" << "in"
	                                        << "ansibpaper" << "11" << "17" << "in"
	                                        << "ansicpaper" << "17" << "22" << "in"
	                                        << "ansidpaper" << "22" << "34" << "in"
	                                        << "ansiepaper" << "34" << "44" << "in"
	                                        << "letterpaper" << "8.5" << "11" << "in"
	                                        << "legalpaper" << "8.5" << "14" << "in"
	                                        << "executivepaper" << "7.25" << "10.5" << "in"
	                                        << "screen" << "225" << "180" << "mm";

	int paperFormat = paperFormats.indexOf(ui.comboBoxPaper->currentText().toLower());
	if (paperFormat == -1) {
		ui.geometryPreviewLabel->setText("unknown paper format");
		return;
	}
	qreal physicalPaperWidth = convertLatexLengthToMetre(paperFormats[paperFormat + 1].toDouble(), paperFormats[paperFormat + 3]);
	qreal physicalPaperHeight = convertLatexLengthToMetre(paperFormats[paperFormat + 2].toDouble(), paperFormats[paperFormat + 3]);

	qreal textWidth = (ui.checkBoxGeometryPageWidth->isChecked() ? convertLatexLengthToMetre(ui.spinBoxGeometryPageWidth->value(), ui.spinBoxGeometryPageWidth->suffix()) : -1);
	qreal textHeight = (ui.checkBoxGeometryPageWidth->isChecked() ? convertLatexLengthToMetre(ui.spinBoxGeometryPageHeight->value(), ui.spinBoxGeometryPageHeight->suffix()) : -1);

	qreal marginLeft = (ui.checkBoxGeometryMarginLeft->isChecked() ? convertLatexLengthToMetre(ui.spinBoxGeometryMarginLeft->value(), ui.spinBoxGeometryMarginLeft->suffix()) : -1);
	qreal marginRight = (ui.checkBoxGeometryMarginRight->isChecked() ? convertLatexLengthToMetre(ui.spinBoxGeometryMarginRight->value(), ui.spinBoxGeometryMarginRight->suffix()) : -1);
	qreal marginTop = (ui.checkBoxGeometryMarginTop->isChecked() ? convertLatexLengthToMetre(ui.spinBoxGeometryMarginTop->value(), ui.spinBoxGeometryMarginTop->suffix()) : -1);
	qreal marginBottom = (ui.checkBoxGeometryMarginBottom->isChecked() ? convertLatexLengthToMetre(ui.spinBoxGeometryMarginBottom->value(), ui.spinBoxGeometryMarginBottom->suffix()) : -1);

	bool twoSide = ui.listWidgetOptions->findItems("twoside", Qt::MatchExactly).first()->isSelected();
	bool landscape = ui.listWidgetOptions->findItems("landscape", Qt::MatchExactly).first()->isSelected();

	if (landscape) qSwap(physicalPaperWidth, physicalPaperHeight);

	//calculate missing parametres like the geometry package does it
	calculatePaperLength(physicalPaperWidth, marginLeft, textWidth, marginRight, twoSide ? (2.0f / 5.0f) : (1 / 2.0f));
	calculatePaperLength(physicalPaperHeight, marginTop, textHeight, marginBottom, 2.0f / 5.0f);

	//draw paper
	qreal resolution = qMin((ui.geometryPreviewLabel->width() - 5) / physicalPaperWidth, (ui.geometryPreviewLabel->height() - 5) / physicalPaperHeight);
	QPixmap preview((int)(physicalPaperWidth * resolution + 6), (int)(physicalPaperHeight * resolution + 5));
	preview.fill(QColor(0, 0, 0));

	QPainter painter(&preview);
	QBrush brush(QColor(255, 255, 255));
	brush.setStyle(Qt::SolidPattern);
	painter.setBrush(brush);
	painter.drawRect(2, 2, qRound(physicalPaperWidth * resolution), qRound(physicalPaperHeight * resolution));

	painter.setTransform(QTransform().scale(resolution, resolution)*QTransform().translate(2, 2));

	QPen pen(QColor(128, 128, 128));
	pen.setWidth(0);
	painter.setPen(pen);

	painter.drawLine(QPointF(marginLeft, 0), QPointF(marginLeft, physicalPaperHeight));
	painter.drawLine(QPointF(0, marginTop), QPointF(physicalPaperWidth, marginTop));
	painter.drawLine(QPointF(physicalPaperWidth - marginRight, 0), QPointF(physicalPaperWidth - marginRight, physicalPaperHeight));
	painter.drawLine(QPointF(0, physicalPaperHeight -  marginTop), QPointF(physicalPaperWidth, physicalPaperHeight - marginTop));

	ui.geometryPreviewLabel->setPixmap(preview);
}

void QuickDocumentDialog::addUserClass()
{
	QString newoption;
	UniversalInputDialog dialog;
	dialog.addVariable(&newoption, tr("New:"));
	if (dialog.exec() && !newoption.isEmpty()) {
		otherClassList.append(newoption);
		Init();
	}
}

void QuickDocumentDialog::addUserPaper()
{
	QString newoption;
	UniversalInputDialog dialog;
	dialog.addVariable(&newoption, tr("New:"));
	if (dialog.exec() && !newoption.isEmpty()) {
		otherPaperList.append(newoption);
		Init();
	}
}

void QuickDocumentDialog::addUserInputEncoding()
{
	QString newoption;
	UniversalInputDialog dialog;
	dialog.addVariable(&newoption, tr("New:"));
	if (dialog.exec() && !newoption.isEmpty()) {
		otherInputEncodingList.append(newoption);
		Init();
	}
}

void QuickDocumentDialog::addUserFontEncoding()
{
	QString newoption;
	UniversalInputDialog dialog;
	dialog.addVariable(&newoption, tr("New:"));
	if (dialog.exec() && !newoption.isEmpty()) {
		otherFontEncodingList.append(newoption);
		Init();
	}
}

void QuickDocumentDialog::addBabelOption()
{
	QString newoption;
	UniversalInputDialog dialog;
	dialog.addVariable(&newoption, tr("New:"));
	if (dialog.exec() && !newoption.isEmpty()) {
		otherBabelOptionsList.append(newoption);
		Init();
	}
}

void QuickDocumentDialog::addUserOptions()
{
	QString newoption;
	UniversalInputDialog dialog;
	dialog.addVariable(&newoption, tr("New:"));
	if (dialog.exec() && !newoption.isEmpty()) {
		otherOptionsList.append(newoption);
		Init();
	}
}
