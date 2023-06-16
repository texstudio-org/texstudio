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

qreal unit2Metre(const qreal &length, const QString &unit, const bool &inverse = false)
{
	static const qreal inchInMetre = 0.0254;
	static const qreal pointInMetre = inchInMetre / 72.27;
	static const qreal bigPointInMetre = inchInMetre / 72;
	QString lunit = unit.toLower();
	if (lunit == "pt")    if (!inverse) return length * pointInMetre;      else  return length / pointInMetre;   
	if (lunit == "bp")    if (!inverse) return length * bigPointInMetre;   else  return length / bigPointInMetre;
	if (lunit == "cm")    if (!inverse) return length * 0.01;              else  return length * 100.;           
	if (lunit == "dm")    if (!inverse) return length * 0.1;               else  return length * 10.;            
	if (lunit == "in")    if (!inverse) return length * inchInMetre;       else  return length / inchInMetre;    
	/*if (unit == "mm")*/ if (!inverse) return length * 0.001;             else  return length * 1000.;          
}

//options for the configmanager
QStringList QuickDocumentDialog::otherClassList, QuickDocumentDialog::otherPaperList, QuickDocumentDialog::otherFontEncodingList, QuickDocumentDialog::otherBabelOptionsList, QuickDocumentDialog::otherOptionsList, QuickDocumentDialog::packagesUsed, QuickDocumentDialog::otherPackagesList;
QString QuickDocumentDialog::document_class, QuickDocumentDialog::typeface_size, QuickDocumentDialog::paper_size, QuickDocumentDialog::document_encoding, QuickDocumentDialog::font_encoding, QuickDocumentDialog::babel_language, QuickDocumentDialog::author;
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
	connect(ui.pushButtonFontEncoding , SIGNAL(clicked()), SLOT(addUserFontEncoding()));
	connect(ui.pushButtonBabel, SIGNAL(clicked()), SLOT(addBabelOption()));
	connect(ui.pushButtonOptions , SIGNAL(clicked()), SLOT(addUserOptions()));
	ui.listWidgetOptions->setSelectionMode(QAbstractItemView::ExtendedSelection);
	connect(ui.pushButtonPackages , SIGNAL(clicked()), SLOT(addUserPackages()));
	setWindowTitle(tr("Quick Start"));

	//Package Tab
	connect(ui.tabWidget, SIGNAL(tabBarClicked(int)), SLOT(setPkgTabToolTip(int)));

	//Geometry package
	connect(ui.comboBoxUnitGeometryPageWidth, SIGNAL(currentTextChanged(QString)), SLOT(geometryUnitsChanged()));
	connect(ui.comboBoxUnitGeometryPageHeight, SIGNAL(currentTextChanged(QString)), SLOT(geometryUnitsChanged()));
	connect(ui.comboBoxUnitGeometryMarginLeft, SIGNAL(currentTextChanged(QString)), SLOT(geometryUnitsChanged()));
	connect(ui.comboBoxUnitGeometryMarginRight, SIGNAL(currentTextChanged(QString)), SLOT(geometryUnitsChanged()));
	connect(ui.comboBoxUnitGeometryMarginTop, SIGNAL(currentTextChanged(QString)), SLOT(geometryUnitsChanged()));
	connect(ui.comboBoxUnitGeometryMarginBottom, SIGNAL(currentTextChanged(QString)), SLOT(geometryUnitsChanged()));

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
	QString amssymb, amsthm, babel, fontenc, geometry, graphicx, hyperref, mathtools, nameref, thmtools, xcolor;  // packages initially available in the dialog to be sorted
	QString  cleveref, inputenc, userPackages;  // packages added by user, special cases cleveref, inputenc need to be sorted

	QString classOpt;
	if (ui.comboBoxBabel->currentText() != "NONE") {
		classOpt += ui.comboBoxBabel->currentText() + QString(",");
		babel = QString("\\usepackage{babel}\n");
	}
	classOpt += ui.comboBoxSize->currentText() + QString(",") + ui.comboBoxPaper->currentText();
	for (int i = 0; i < ui.listWidgetOptions->count(); ++i) {
		QListWidgetItem *item=ui.listWidgetOptions->item(i);
		if (item->checkState()==Qt::Checked) classOpt += QString(",") + item->text();
	}
	QString tag = QString("\\documentclass[%1]{%2}\n").arg(classOpt).arg(ui.comboBoxClass->currentText());

	if (ui.comboBoxFontEncoding->currentText() != "NONE")
		fontenc = QString("\\usepackage[%1]{fontenc}\n").arg(ui.comboBoxFontEncoding->currentText());
	if (ui.checkBoxGeometryPageWidth->isChecked() ||
	        ui.checkBoxGeometryPageHeight->isChecked() ||
	        ui.checkBoxGeometryMarginLeft->isChecked() ||
	        ui.checkBoxGeometryMarginRight->isChecked() ||
	        ui.checkBoxGeometryMarginBottom->isChecked() ||
	        ui.checkBoxGeometryMarginTop->isChecked()) {
		QString geometryOptions;
		if (ui.checkBoxGeometryPageWidth->isChecked()) geometryOptions += QString(", width=%1").arg(ui.spinBoxGeometryPageWidth->value()) + ui.comboBoxUnitGeometryPageWidth->currentText();
		if (ui.checkBoxGeometryPageHeight->isChecked()) geometryOptions += QString(", height=%1").arg(ui.spinBoxGeometryPageHeight->value()) + ui.comboBoxUnitGeometryPageHeight->currentText();
		if (ui.checkBoxGeometryMarginLeft->isChecked()) geometryOptions += QString(", left=%1").arg(ui.spinBoxGeometryMarginLeft->value()) + ui.comboBoxUnitGeometryMarginLeft->currentText();
		if (ui.checkBoxGeometryMarginRight->isChecked()) geometryOptions += QString(", right=%1").arg(ui.spinBoxGeometryMarginRight->value()) + ui.comboBoxUnitGeometryMarginRight->currentText();
		if (ui.checkBoxGeometryMarginTop->isChecked()) geometryOptions += QString(", top=%1").arg(ui.spinBoxGeometryMarginTop->value()) + ui.comboBoxUnitGeometryMarginTop->currentText();
		if (ui.checkBoxGeometryMarginBottom->isChecked()) geometryOptions += QString(", bottom=%1").arg(ui.spinBoxGeometryMarginBottom->value()) + ui.comboBoxUnitGeometryMarginBottom->currentText();
		geometryOptions.remove(0, 2);
		geometry = QString("\\usepackage[%1]{geometry}\n").arg(geometryOptions);
	}

	QTableWidget *table = ui.tableWidgetPackages;
	packagesUsed = QStringList();
	for (int i=0; i < table->rowCount(); ++i) {
		QTableWidgetItem *itemPkgName = table->item(i,0);
		if (itemPkgName->checkState()==Qt::Checked) {
			QString text = itemPkgName->text();
			packagesUsed << text;
			// packages initially available from Packages tab
			if (text=="amssymb"  ) amssymb   = QString("\\usepackage{amssymb}\n"); else
			if (text=="amsthm"   ) amsthm    = QString("\\usepackage{amsthm}\n"); else
			if (text=="cleveref" ) cleveref  = QString("\\usepackage{cleveref}\n"); else   // special case for user (s. definition of cleveref)
			if (text=="graphicx" ) graphicx  = QString("\\usepackage{graphicx}\n"); else
			if (text=="hyperref" ) hyperref  = QString("\\usepackage{hyperref}\n"); else
			if (text=="inputenc" ) inputenc  = QString("\\usepackage{inputenc}\n"); else   // special case for user (s. definition of inputenc)
			if (text=="mathtools") mathtools = QString("\\usepackage{mathtools}\n"); else
			if (text=="nameref"  ) nameref   = QString("\\usepackage{nameref}\n"); else
			if (text=="thmtools" ) thmtools  = QString("\\usepackage{thmtools}\n"); else
			if (text=="xcolor"   ) xcolor    = QString("\\usepackage{xcolor}\n"); else
				userPackages += QString("\\usepackage{%1}\n").arg(text);
		}
	}
// LaTeX code for all packages used
	tag += inputenc + fontenc + geometry + graphicx + mathtools + amssymb + amsthm + thmtools + xcolor + nameref + babel + userPackages + hyperref + cleveref;

	QString makeTitle;
	if (ui.lineEditTitle->text() != "") {
		makeTitle = "\\maketitle\n";
		tag += QString("\\title{%1}\n").arg(ui.lineEditTitle->text());
		if (ui.lineEditAuthor->text() != "")
			tag += QString("\\author{%1}\n").arg(ui.lineEditAuthor->text());
	}

	tag += "\\begin{document}\n" + makeTitle + "%|\n\\end{document}";
	return tag;
}

void QuickDocumentDialog::registerOptions(ConfigManagerInterface &configManager)
{
	configManager.registerOption("Tools/User Class", &otherClassList);
	configManager.registerOption("Tools/User Paper", &otherPaperList);
	configManager.registerOption("Tools/User Font Encoding", &otherFontEncodingList);
	configManager.registerOption("Tools/User Babel Options", &otherBabelOptionsList);
	configManager.registerOption("Tools/User Options", &otherOptionsList);
	configManager.registerOption("Tools/User Packages", &otherPackagesList);
	configManager.registerOption("Quick/Class", &document_class, "article");
	configManager.registerOption("Quick/Typeface", &typeface_size, "10pt");
	configManager.registerOption("Quick/Papersize", &paper_size, "a4paper");
	configManager.registerOption("Quick/Encoding", &document_encoding, "utf8");
	configManager.registerOption("Quick/FontEncoding", &font_encoding, "T1");
	configManager.registerOption("Quick/Babel", &babel_language, "NONE");
	configManager.registerOption("Quick/Author", &author, "");
	configManager.registerOption("Quick/Packages Used", &packagesUsed, QStringList());

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
	ui.lineEditTitle->setFocus();
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
    QListWidgetItem *item;
    QStringList options{"landscape","draft","final","oneside","twoside","openright","openany","onecolumn",
                       "twocolumn","titlepage","notitlepage","openbib","leqno","fleqn"};
    for(const QString& text:options){
        item=new QListWidgetItem(text,ui.listWidgetOptions);
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        item->setCheckState(Qt::Unchecked);
    }
    for(const QString& text:otherOptionsList){
        item=new QListWidgetItem(text,ui.listWidgetOptions);
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        item->setCheckState(Qt::Unchecked);
    }

	QTableWidget *table = ui.tableWidgetPackages;
	table->clearContents();
	table->horizontalHeader()->setStretchLastSection(true);
	table->setSelectionMode(QAbstractItemView::NoSelection);
	table->verticalHeader()->hide();

	// each QStringList holds 2 items: the name of the package, and a short package description. These constitute a row of the table of the packages tab.
	QList<QStringList> packages = QList<QStringList>()
		<< QStringList( {"amssymb"     , tr("Mathematical symbols from AMS")} )
		<< QStringList( {"graphicx"    , tr("Graphics package, easily include images (s. Insert Graphic Wizard)")} )
		<< QStringList( {"hyperref"    , tr("Support for hyperlinks in your document")} )
		<< QStringList( {"mathtools"   , tr("Extension package to amsmath incl. fixes for bugs in amsmath, loads amsmath")} )
		<< QStringList( {"amsthm"      , tr("Define your theorem like env., has to be loaded after amsmath")} )
		<< QStringList( {"nameref"     , tr("Reference to names of chapters, sections, ..., loaded by hyperref")} )
		<< QStringList( {"thmtools"    , tr("Extension package to amsthm")} )
		<< QStringList( {"xcolor"      , tr("Sophisticated package for colors, with table option to use colors in tables")} )
		;
	//add user given packages
	for (const QString& package:otherPackagesList){
		packages << QStringList( { package, "" } );
	}
	//setup packages table 
	table->setRowCount(packages.size());
	for (int row=0;row<packages.length();++row){
		QStringList data=packages.value(row);

		QString pkgName = data[0];
		QString pkgDescription = data[1];

		QTableWidgetItem *itemPkgName = new QTableWidgetItem(pkgName);
		QTableWidgetItem *itemPkgDescription = new QTableWidgetItem(pkgDescription);

		itemPkgName->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
		itemPkgDescription->setFlags(Qt::ItemIsEnabled);

		table->setItem(row,0,itemPkgName);
		table->setItem(row,1,itemPkgDescription);

		bool found = packagesUsed.contains(pkgName);
		itemPkgName->setCheckState( found ? Qt::Checked : Qt::Unchecked );
	}

	configManagerInterface->linkOptionToDialogWidget(&document_class, ui.comboBoxClass);
	configManagerInterface->linkOptionToDialogWidget(&typeface_size, ui.comboBoxSize);
	configManagerInterface->linkOptionToDialogWidget(&paper_size, ui.comboBoxPaper);
	configManagerInterface->linkOptionToDialogWidget(&font_encoding, ui.comboBoxFontEncoding);
	configManagerInterface->linkOptionToDialogWidget(&babel_language, ui.comboBoxBabel);
	configManagerInterface->linkOptionToDialogWidget(&author, ui.lineEditAuthor);

	configManagerInterface->linkOptionToDialogWidget(&geometryPageWidth, ui.spinBoxGeometryPageWidth);
	configManagerInterface->linkOptionToDialogWidget(&geometryPageHeight, ui.spinBoxGeometryPageHeight);
	configManagerInterface->linkOptionToDialogWidget(&geometryMarginLeft, ui.spinBoxGeometryMarginLeft);
	configManagerInterface->linkOptionToDialogWidget(&geometryMarginRight, ui.spinBoxGeometryMarginRight);
	configManagerInterface->linkOptionToDialogWidget(&geometryMarginTop, ui.spinBoxGeometryMarginTop);
	configManagerInterface->linkOptionToDialogWidget(&geometryMarginBottom, ui.spinBoxGeometryMarginBottom);

	configManagerInterface->linkOptionToDialogWidget(&geometryPageWidthUnit, ui.comboBoxUnitGeometryPageWidth);
	configManagerInterface->linkOptionToDialogWidget(&geometryPageHeightUnit, ui.comboBoxUnitGeometryPageHeight);
	configManagerInterface->linkOptionToDialogWidget(&geometryMarginLeftUnit, ui.comboBoxUnitGeometryMarginLeft);
	configManagerInterface->linkOptionToDialogWidget(&geometryMarginRightUnit, ui.comboBoxUnitGeometryMarginRight);
	configManagerInterface->linkOptionToDialogWidget(&geometryMarginTopUnit, ui.comboBoxUnitGeometryMarginTop);
	configManagerInterface->linkOptionToDialogWidget(&geometryMarginBottomUnit, ui.comboBoxUnitGeometryMarginBottom);

	configManagerInterface->linkOptionToDialogWidget(&geometryPageWidthEnabled, ui.checkBoxGeometryPageWidth);
	configManagerInterface->linkOptionToDialogWidget(&geometryPageHeightEnabled, ui.checkBoxGeometryPageHeight);
	configManagerInterface->linkOptionToDialogWidget(&geometryMarginLeftEnabled, ui.checkBoxGeometryMarginLeft);
	configManagerInterface->linkOptionToDialogWidget(&geometryMarginRightEnabled, ui.checkBoxGeometryMarginRight);
	configManagerInterface->linkOptionToDialogWidget(&geometryMarginTopEnabled, ui.checkBoxGeometryMarginTop);
	configManagerInterface->linkOptionToDialogWidget(&geometryMarginBottomEnabled, ui.checkBoxGeometryMarginBottom);

	ui.spinBoxGeometryPageWidth->setEnabled(ui.checkBoxGeometryPageWidth->isChecked());
	ui.comboBoxUnitGeometryPageWidth->setEnabled(ui.checkBoxGeometryPageWidth->isChecked());
	ui.spinBoxGeometryPageHeight->setEnabled(ui.checkBoxGeometryPageHeight->isChecked());
	ui.comboBoxUnitGeometryPageHeight->setEnabled(ui.checkBoxGeometryPageHeight->isChecked());
	ui.spinBoxGeometryMarginLeft->setEnabled(ui.checkBoxGeometryMarginLeft->isChecked());
	ui.comboBoxUnitGeometryMarginLeft->setEnabled(ui.checkBoxGeometryMarginLeft->isChecked());
	ui.spinBoxGeometryMarginRight->setEnabled(ui.checkBoxGeometryMarginRight->isChecked());
	ui.comboBoxUnitGeometryMarginRight->setEnabled(ui.checkBoxGeometryMarginRight->isChecked());
	ui.spinBoxGeometryMarginTop->setEnabled(ui.checkBoxGeometryMarginTop->isChecked());
	ui.comboBoxUnitGeometryMarginTop->setEnabled(ui.checkBoxGeometryMarginTop->isChecked());
	ui.spinBoxGeometryMarginBottom->setEnabled(ui.checkBoxGeometryMarginBottom->isChecked());
	ui.comboBoxUnitGeometryMarginBottom->setEnabled(ui.checkBoxGeometryMarginBottom->isChecked());
}

void QuickDocumentDialog::accept()
{
	QDialog::accept();
}

void QuickDocumentDialog::geometryUnitsChanged()
{
	// it was decided not to recalculate number part (s. https://github.com/texstudio-org/texstudio/pull/3156) and to not use suffix in spinBoxGeometry...
	geometryValuesChanged();
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
	qreal physicalPaperWidth = unit2Metre(paperFormats[paperFormat + 1].toDouble(), paperFormats[paperFormat + 3]);
	qreal physicalPaperHeight = unit2Metre(paperFormats[paperFormat + 2].toDouble(), paperFormats[paperFormat + 3]);

	qreal textWidth = (ui.checkBoxGeometryPageWidth->isChecked() ? unit2Metre(ui.spinBoxGeometryPageWidth->value(), ui.comboBoxUnitGeometryPageWidth->currentText()) : -1);
	qreal textHeight = (ui.checkBoxGeometryPageWidth->isChecked() ? unit2Metre(ui.spinBoxGeometryPageHeight->value(), ui.comboBoxUnitGeometryPageHeight->currentText()) : -1);

	qreal marginLeft = (ui.checkBoxGeometryMarginLeft->isChecked() ? unit2Metre(ui.spinBoxGeometryMarginLeft->value(), ui.comboBoxUnitGeometryMarginLeft->currentText()) : -1);
	qreal marginRight = (ui.checkBoxGeometryMarginRight->isChecked() ? unit2Metre(ui.spinBoxGeometryMarginRight->value(), ui.comboBoxUnitGeometryMarginRight->currentText()) : -1);
	qreal marginTop = (ui.checkBoxGeometryMarginTop->isChecked() ? unit2Metre(ui.spinBoxGeometryMarginTop->value(), ui.comboBoxUnitGeometryMarginTop->currentText()) : -1);
	qreal marginBottom = (ui.checkBoxGeometryMarginBottom->isChecked() ? unit2Metre(ui.spinBoxGeometryMarginBottom->value(), ui.comboBoxUnitGeometryMarginBottom->currentText()) : -1);

    bool twoSide = ui.listWidgetOptions->findItems("twoside", Qt::MatchExactly).constFirst()->checkState() == Qt::Checked;
    bool landscape = ui.listWidgetOptions->findItems("landscape", Qt::MatchExactly).constFirst()->checkState() == Qt::Checked;

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
	painter.drawLine(QPointF(0, physicalPaperHeight -  marginBottom), QPointF(physicalPaperWidth, physicalPaperHeight - marginBottom));

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

void QuickDocumentDialog::addUserPackages()
{
	QStringList packagesList;
	QTableWidget *table = ui.tableWidgetPackages;
	for (int i=0; i < table->rowCount(); ++i) {
		QTableWidgetItem *itemPkgName = table->item(i,0);
		packagesList << itemPkgName->text();
	}
	packagesList << "fontenc" << "geometry" << "babel"; // additional packages you shouldn't add

	QString newoption;
	UniversalInputDialog dialog;
	dialog.addVariable(&newoption, tr("New:"));

	if (dialog.exec() == QDialog::Accepted) {
		if (packagesList.contains(newoption)) {
			QMessageBox::information(this, tr("Hint"), tr("Package %1 is already defined.").arg(newoption));
		}
		else if (!newoption.isEmpty()) {
			otherPackagesList.append(newoption);
			Init();
		}
	}
}

void QuickDocumentDialog::setPkgTabToolTip(int idx)
{
	int tabPos = ui.tabWidget->indexOf(ui.tabPackages);
	if (idx == tabPos) {
		ui.tabWidget->setTabToolTip(tabPos, tr("All packages that have the checkbox checked will appear in a new document within \\usepackage commands after pressing OK."));
	}
	else ui.tabWidget->setTabToolTip(tabPos, "");
}
