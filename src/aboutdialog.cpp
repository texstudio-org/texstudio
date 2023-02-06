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

#include "aboutdialog.h"
#include "utilsVersion.h"
#include "utilsSystem.h"

AboutDialog::AboutDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
    QString changelogPath = findResourceFile("CHANGELOG.md");
    if(changelogPath.isEmpty()){
        changelogPath="https://texstudio-org.github.io/CHANGELOG.html";
    }else{
        if(!changelogPath.startsWith("/")){
            changelogPath="/"+changelogPath;
        }
        changelogPath="file://"+changelogPath;
    }
	ui.textBrowser->setOpenExternalLinks(true);
    ui.textBrowser->setHtml(QString("<b>%1 %2</b> (git %3)").arg(TEXSTUDIO,TXSVERSION,TEXSTUDIO_GIT_REVISION ? TEXSTUDIO_GIT_REVISION : "n/a") + "<br>" +
                            tr("Using Qt Version %1, compiled with Qt %2 %3").arg(qVersion(),QT_VERSION_STR,COMPILED_DEBUG_OR_RELEASE) + "<br>" +
                            "<a href=\""+changelogPath+"\">"+tr("Changelog")+"</a><br><br>" +
	                        "Copyright (c)<br>" +
	                        TEXSTUDIO + ": Benito van der Zander, Jan Sundermeyer, Daniel Braun, Tim Hoffmann<br>" +
	                        "Texmaker: Pascal Brachet<br>" +
	                        "QCodeEdit: Luc Bruant<br>" +
	                        tr("html conversion: ") + QString::fromUtf8("Joël Amblard</i><br>") +
	                        tr("TeXstudio contains code from Hunspell (GPL), QtCreator (GPL, Copyright (C) Nokia), KILE (GPL) and SyncTeX (by Jerome Laurens).") + "<br>" +
	                        tr("TeXstudio uses the PDF viewer of TeXworks.") + "<br>" +
	                        tr("TeXstudio uses the DSingleApplication class (Author: Dima Fedorov Levit - Copyright (C) BioImage Informatics - Licence: GPL).") + "<br>" +
	                        tr("TeXstudio uses TexTablet (MIT License, Copyright (c) 2012 Steven Lovegrove).") + "<br>" +
	                        tr("TeXstudio uses QuaZip (LGPL, Copyright (C) 2005-2012 Sergey A. Tachenov and contributors).") + "<br>" +
	                        tr("TeXstudio uses To Title Case (MIT License, Copyright (c) 2008-2013 David Gouch).") + "<br>" +
	                        tr("TeXstudio contains an image by Alexander Klink.") + "<br>" +
	                        tr("TeXstudio uses icons from the Crystal Project (LGPL), the Oxygen icon theme (CC-BY-SA 3.0) and the Colibre icon theme (CC0) of LibreOffice.") + "<br>" +
	                        tr("TeXstudio uses flowlayout from Qt5.6 examples.") + "<br>" +
                            tr("TeXstudio uses adwaita-qt (GPL2) from ") + "<a href=\"https://github.com/FedoraQt/adwaita-qt\">https://github.com/FedoraQt/adwaita-qt</a><br>" +
	                        "<br>" +
                            tr("Thanks to ") + QString::fromUtf8("Frédéric Devernay, Denis Bitouzé, Vesselin Atanasov, Yukai Chou, Jean-Côme Charpentier, Luis Silvestre, Enrico Vittorini, Aleksandr Zolotarev, David Sichau, Grigory Mozhaev, mattgk, A. Weder, Pavel Fric, András Somogyi, István Blahota, Edson Henriques, Grant McLean, Tom Jampen, Kostas Oikinimou, Lion Guillaume, ranks.nl, AI Corleone, Diego Andrés Jarrín, Matthias Pospiech, Zulkifli Hidayat, Christian Spieß, Robert Diaz, Kirill Müller, Atsushi Nakajima Yuriy Kolerov, Victor Kozyakin, Mattia Meneguzzo, Andriy Bandura, Carlos Eduardo Valencia Urbina, Koutheir Attouchi, Stefan Kraus, Bjoern Menke, Charles Brunet, François Gannaz, Marek Kurdej, Paulo Silva, Thiago de Melo, YoungFrog, Klaus Schneider-Zapp, Jakob Nixdorf, Thomas Leitz, Quoc Ho, Matthew Bertucci, geolta.<br><br>") +
                            tr("Project home site:") + " <a href=\"https://texstudio.org/\">https://texstudio.org/</a><br><br>" +
	                        tr("This program is licensed to you under the terms of the GNU General Public License Version 2 as published by the Free Software Foundation."));
	QAction *act = new QAction("large", this);
	connect(act, SIGNAL(triggered()), SLOT(largeLogo()));
	ui.label->addAction(act);
	ui.label->setContextMenuPolicy(Qt::ActionsContextMenu);
}

AboutDialog::~AboutDialog()
{
}

void AboutDialog::largeLogo()
{
    QDialog *dlg = new QDialog(nullptr);
	dlg->setAttribute(Qt::WA_DeleteOnClose);
	dlg->setLayout(new QHBoxLayout(dlg));
	QLabel *label = new QLabel(dlg);
	label->setPixmap(QPixmap(":/images/splash_large.png"));
	dlg->layout()->addWidget(label);
	dlg->setWindowTitle("TeXstudio");
	dlg->exec();
}
