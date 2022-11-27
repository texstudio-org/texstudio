/***************************************************************************
 *   copyright       : (C) 2003-2013, 2017 by Pascal Brachet                     *
 *   http://www.xm1math.net/texmaker/                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "quickbeamerdialog.h"
#include "universalinputdialog.h"
#include "configmanagerinterface.h"
#include "utilsUI.h"

QString QuickBeamerDialog::document_encoding;

ConfigManagerInterface *QuickBeamerDialog::configManagerInterface;

QuickBeamerDialog::QuickBeamerDialog(QWidget *parent, const QString &name)
	: QDialog(parent)
{
	setWindowTitle(name);
	setModal(true);
	ui.setupUi(this);
	UtilsUi::resizeInFontHeight(this, 72, 36);

	ui.listWidgetBabel->setSelectionMode(QAbstractItemView::ExtendedSelection);
	setWindowTitle(tr("Quick Beamer Presentation"));
	labelImage = new QLabel(ui.scrollArea);
	labelImage->setScaledContents(true);
	int imgWidth = 564;  // sizes of the preview .png images
	int imgHeight = 853;
	int scrollbarWidth = qApp->style()->pixelMetric(QStyle::PM_ScrollBarExtent);
	int margin = 2;
	labelImage->setMinimumSize(imgWidth, imgHeight);
	labelImage->setMaximumSize(imgWidth, imgHeight);
	ui.scrollArea->setMinimumWidth(imgWidth + scrollbarWidth + margin);
	ui.scrollArea->setMaximumWidth(imgWidth + scrollbarWidth + margin);
    if (qApp->devicePixelRatio() > 1.01) {
        qreal ratio=qApp->devicePixelRatio();
        labelImage->setMinimumSize(imgWidth / ratio, imgHeight / ratio);
        labelImage->setMaximumSize(imgWidth / ratio, imgHeight / ratio);
        ui.scrollArea->setMinimumWidth(imgWidth / ratio + scrollbarWidth + margin);
        ui.scrollArea->setMaximumWidth(imgWidth / ratio + scrollbarWidth + margin);
	}
	ui.scrollArea->setBackgroundRole(QPalette::Dark);
	ui.scrollArea->setWidget(labelImage);
}

QuickBeamerDialog::~QuickBeamerDialog()
{
}

void QuickBeamerDialog::registerOptions(ConfigManagerInterface &configManager)
{
	configManagerInterface = &configManager;
	configManager.registerOption("Beamer/Encoding", &document_encoding, "utf8");
}

extern QStringList babelLanguages;

void QuickBeamerDialog::Init()
{
	ui.comboBoxSize->clear();
	ui.comboBoxSize->addItem( "8pt" );
	ui.comboBoxSize->addItem( "9pt" );
	ui.comboBoxSize->addItem( "10pt" );
	ui.comboBoxSize->addItem( "11pt" );
	ui.comboBoxSize->addItem( "12pt" );
	ui.comboBoxSize->addItem( "14pt" );
	ui.comboBoxSize->addItem( "17pt" );
	ui.comboBoxSize->addItem( "20pt" );
	ui.comboBoxSize->setCurrentIndex(3);

	ui.comboBoxTheme->clear();
	ui.comboBoxTheme->addItem( "default" );
	ui.comboBoxTheme->addItem( "AnnArbor" );
	ui.comboBoxTheme->addItem( "Antibes" );
	ui.comboBoxTheme->addItem( "Bergen" );
	ui.comboBoxTheme->addItem( "Berkeley" );
	ui.comboBoxTheme->addItem( "Berlin" );
	ui.comboBoxTheme->addItem( "Boadilla" );
	ui.comboBoxTheme->addItem( "CambridgeUS" );
	ui.comboBoxTheme->addItem( "Copenhagen" );
	ui.comboBoxTheme->addItem( "Cuerna" );
	ui.comboBoxTheme->addItem( "Darmstadt" );
	ui.comboBoxTheme->addItem( "Dresden" );
	ui.comboBoxTheme->addItem( "EastLansing" );
	ui.comboBoxTheme->addItem( "focus" );
	ui.comboBoxTheme->addItem( "Frankfurt" );
	ui.comboBoxTheme->addItem( "Goettingen" );
	ui.comboBoxTheme->addItem( "Hannover" );
	ui.comboBoxTheme->addItem( "Ilmenau" );
	ui.comboBoxTheme->addItem( "JuanLesPins" );
	ui.comboBoxTheme->addItem( "Luebeck" );
	ui.comboBoxTheme->addItem( "Madrid" );
	ui.comboBoxTheme->addItem( "Malmoe" );
	ui.comboBoxTheme->addItem( "Marburg" );
	ui.comboBoxTheme->addItem( "metropolis" );
	ui.comboBoxTheme->addItem( "Montpellier" );
	ui.comboBoxTheme->addItem( "PaloAlto" );
	ui.comboBoxTheme->addItem( "Pittsburgh" );
	ui.comboBoxTheme->addItem( "Rochester" );
	ui.comboBoxTheme->addItem( "Singapore" );
	ui.comboBoxTheme->addItem( "Szeged" );
	ui.comboBoxTheme->addItem( "Warsaw" );

    connect(ui.comboBoxTheme, SIGNAL(currentTextChanged(const QString&)), this, SLOT(updatePreview(const QString&)));
	ui.comboBoxTheme->setCurrentIndex(0);
	updatePreview("default");

	ui.comboBoxEncoding->clear();
	ui.comboBoxEncoding->addItem( "latin1" );
	ui.comboBoxEncoding->addItem( "latin2" );
	ui.comboBoxEncoding->addItem( "latin3" );
	ui.comboBoxEncoding->addItem( "latin5" );
	ui.comboBoxEncoding->addItem( "utf8" );
	ui.comboBoxEncoding->addItem( "utf8x" );
	ui.comboBoxEncoding->addItem( "ascii" );
	ui.comboBoxEncoding->addItem( "decmulti" );
	ui.comboBoxEncoding->addItem( "cp850" );
	ui.comboBoxEncoding->addItem( "cp852" );
	ui.comboBoxEncoding->addItem( "cp437" );
	ui.comboBoxEncoding->addItem( "cp437de" );
	ui.comboBoxEncoding->addItem( "cp865" );
	ui.comboBoxEncoding->addItem( "applemac" );
	ui.comboBoxEncoding->addItem( "next" );
	ui.comboBoxEncoding->addItem( "ansinew" );
	ui.comboBoxEncoding->addItem( "cp1252" );
	ui.comboBoxEncoding->addItem( "cp1250" );
	ui.comboBoxEncoding->addItem( "NONE" );

	ui.listWidgetBabel->clear();
	ui.listWidgetBabel->addItems(babelLanguages);

	configManagerInterface->linkOptionToDialogWidget(&document_encoding, ui.comboBoxEncoding);
}

void QuickBeamerDialog::updatePreview(const QString &theme)
{
	QPixmap pixmap(":/images/beamer/" + theme + ".png");
	if (qApp->devicePixelRatio() == 2) pixmap.setDevicePixelRatio(qApp->devicePixelRatio());
	labelImage->setPixmap(pixmap);
}

QString QuickBeamerDialog::getNewDocumentText()
{
	QString opt = "";
	QString tag = QString("\\documentclass[");

	tag += ui.comboBoxSize->currentText();
	tag += opt + QString("]{beamer}\n");

	if (ui.comboBoxEncoding->currentText() != "NONE") {
		tag += QString("\\usepackage[") + ui.comboBoxEncoding->currentText() + QString("]{inputenc}");
	}
	tag += QString("\n");
	if (ui.comboBoxEncoding->currentText().startsWith("utf8x"))
		tag += QString("\\usepackage{ucs}\n");
	// TODO: babel
	if (ui.checkBoxBabel->isChecked()) {
		QString optbabel = "";
		QString fontenc = "";
		QList<QListWidgetItem *> babelItems = ui.listWidgetBabel->selectedItems();
		for (int i = 0; i < babelItems.size(); ++i) {
			if ( babelItems.at(i) ) {
				if ((babelItems.at(i)->text() == "arabic") && fontenc.isEmpty()) fontenc = "LAE,LFE";
				else if ((babelItems.at(i)->text() == "russian") && fontenc.isEmpty()) fontenc = "OT1";
				else if ((babelItems.at(i)->text() == "slovak") && fontenc.isEmpty()) fontenc = "IL2";
				else if ((babelItems.at(i)->text() == "french") && fontenc.isEmpty()) fontenc = "T1";
				else if ((babelItems.at(i)->text() == "portuguese") && fontenc.isEmpty()) fontenc = "T1";
				else if ((babelItems.at(i)->text() == "icelandic") && fontenc.isEmpty()) fontenc = "T1";
				else if ((babelItems.at(i)->text() == "czech") && fontenc.isEmpty()) fontenc = "T1";
				else if ((babelItems.at(i)->text() == "magyar") && fontenc.isEmpty()) fontenc = "T1";
				else if ((babelItems.at(i)->text() == "finnish") && fontenc.isEmpty()) fontenc = "T1";
				if (i == 0) {
					optbabel += babelItems.at(i)->text();
				} else
					optbabel += QString(",") + babelItems.at(i)->text();
			}
		}
		if (fontenc.isEmpty()) {
			fontenc = "T1";
		}
		tag += QString("\\usepackage[" + fontenc + "]{fontenc}\n");
		tag += QString("\\usepackage{lmodern}\n");
		tag += QString("\\usepackage[" + optbabel + "]{babel}\n");
	} else {
		tag += QString("\\usepackage[T1]{fontenc}\n");
		tag += QString("\\usepackage{lmodern}\n");
	}

    tag += "\\usetheme{" + ui.comboBoxTheme->currentText() + "}\n";

    tag += QString("\\begin{document}\n");
    if (ui.lineEditAuthor->text() != "")
        tag += "\\author{" + ui.lineEditAuthor->text() + "}\n";
    else
        tag += "%%\\author{}\n";
    if (ui.lineEditTitle->text() != "")
        tag += "\\title{" + ui.lineEditTitle->text() + "}\n";
    else
        tag += "%%\\title{}\n";
    tag += QString("%%\\subtitle{}\n");
    tag += QString("%%\\logo{}\n");
    tag += QString("%%\\institute{}\n");
    tag += QString("%%\\date{}\n");
    tag += QString("%%\\subject{}\n");
    tag += QString("%%\\setbeamercovered{transparent}\n");
    tag += QString("%%\\setbeamertemplate{navigation symbols}{}\n");
    tag += QString("\\begin{frame}[plain]\n\t\\maketitle\n\\end{frame}\n\n\\begin{frame}\n\t\\frametitle{%|}\n\\end{frame}\n");
	tag += QString("\\end{document}");
	return tag;
}
