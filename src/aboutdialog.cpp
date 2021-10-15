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

const QString git =

#ifdef TEXSTUDIO_GIT_REVISION
    QString(" (git %1)").arg(TEXSTUDIO_GIT_REVISION);
#else
    "";
#endif

const QString aboutTemplate =
    "<p style = 'font-family:monospace'>                                            "
    "   %1                                                                      <br>"
    "                                                                           <br>"
    "   %2                                                                      <br>"
    "                                                                           <br>"
    "  「 <a href='https://texstudio.org/'>Website</a> 」                            "
    "  「 <a href='https://github.com/texstudio-org/texstudio'>Github</a> 」     <br>"
    "                                                                           <br>"
    "   <h2>Copyright ©</h2>                                                    <br>"
    "                                                                           <br>"
    "   %3 %4                                                                       "
    "                                                                           <br>"
    "   <h3> %5 </h3> %6                                                        <br>"
    "                                                                           <br>"
    "                                                                           <br>"
    "   <i> %7 </i>                                                             <br>"
    "                                                                           <br>"
    "</p>";

const QString texInfo = "<b> %1 %2 </b> %3";

const QString qtInfo =
        "<b>QT Version</b>  <br>"
        "%1: %2             <br>"
        "%3: %4 %5          <br>";

const QString copyright =
    "   <b>%1</b>                                         <br>"
    "   - Benito van der Zander                           <br>"
    "   - Jan Sundermeyer                                 <br>"
    "   - Daniel Braun                                    <br>"
    "   - Tim Hoffmann                                    <br>"
    "                                                     <br>"
    "   <b>TeXMaker:</b> Pascal Brachet                   <br>"
    "                                                     <br>"
    "   <b>QCodeEdit:</b> Luc Bruant                      <br>"
    "                                                     <br>"
    "   <b>%2:</b> Joël Amblard                           <br>"
    "                                                     <br>"
    "   <b> %3 :</b>                                      <br>"
    "   - QtCreator ( GPL | Copyright (C) Nokia )         <br>"
    "   - SyncTeX ( Jerome Laurens )                      <br>"
    "   - Hunspell ( GPL )                                <br>"
    "   - KILE ( GPL )                                    <br>"
    "                                                     <br>";

const QString uses =
    "   <h3> %1 %2 </h3>                                                        <br>"
    "   %3 <br> %4                                                                  "
    "                                                                               "
    "   <h4> %5 </h4>                                                               "
    "   - Crystal Project (LGPL)                                                <br>"
    "   - Oxygen Icon Yheme (CC-BY-SA 3.0)                                      <br>"
    "                                                                           <br>"
    "   <h4> Adwaitaa-QT </h4>                                                      "
    "   %6: GPL2                                                                <br>"
    "   %7: 「 <a href='https://github.com/FedoraQt/adwaita-qt'>Github</a> 」   <br>";

const QString simpleUses =
    "<h5> %1 </h5>"
    "<h5> %2 </h5>"
    "<h5> %3 </h5>";

const QString thanksTo = QString::fromUtf8(
    "Frédéric Devernay, Denis Bitouzé, Vesselin Atanasov, Yukai Chou, Jean-Côme Charpentier, "
    "Luis Silvestre, Enrico Vittorini, Aleksandr Zolotarev, David Sichau, Grigory Mozhaev, "
    "mattgk, A. Weder, Pavel Fric, András Somogyi, István Blahota, Edson Henriques, Grant McLean, "
    "Tom Jampen, Kostas Oikinimou, Lion Guillaume, ranks.nl, AI Corleone, Diego Andrés Jarrín, "
    "Matthias Pospiech, Zulkifli Hidayat, Christian Spieß, Robert Diaz, Kirill Müller, "
    "Atsushi Nakajima Yuriy Kolerov, Victor Kozyakin, Mattia Meneguzzo, Andriy Bandura, "
    "Carlos Eduardo Valencia Urbina, Koutheir Attouchi, Stefan Kraus, Bjoern Menke, "
    "Charles Brunet, François Gannaz, Marek Kurdej, Paulo Silva, Thiago de Melo, YoungFrog, "
    "Klaus Schneider-Zapp, Jakob Nixdorf, Thomas Leitz, Quoc Ho, Matthew Bertucci");

const char * license =
    "This program is licensed to you under the terms of the GNU General "
    "Public License Version 2 as published by the Free Software Foundation.";



QString AboutDialog::use(QString name,QString copyright,QString license,QString author){
    return "<h4>" + (name) + "</h4>" +
           tr("Copyright") + ": " + (copyright) + "<br>" +
           tr("License")   + ": " + (license)   + "<br>" +
           tr("Author")    + ": " + (author)    + "<br>" + "<br>";
};

AboutDialog::AboutDialog(QWidget * parent) : QDialog(parent) {

    const QString html = aboutTemplate.arg(

        /* 1 */ texInfo.arg(
            TEXSTUDIO , TXSVERSION , git
        ),

        /* 2 */ qtInfo.arg(
            tr("Using") , qVersion(),
            tr("Compiled") , QT_VERSION_STR , COMPILED_DEBUG_OR_RELEASE
        ),

        /* 3 */ copyright.arg(
            TEXSTUDIO,
            tr("HTML Conversion"),
            tr("TeXstudio contains code from")
        ),

        /* 4 */ uses.arg(

            TEXSTUDIO , tr("Uses"),

            simpleUses.arg(
                tr("PDF Viewer of TeXworks"),
                tr("An image by Alexander Klink."),
                tr("Flowlayout from QT 5.6 examples")
            ),

            use("DSingleApplication Class","BioImage Informatics","GPL","Dima Fedorov Levit") +
            use("QuaZip","2005 - 2012","LGPL","Sergey A. Tachenov & Contributors") +
            use("Title Case","2008 - 2013","MIT","David Gouch") +
            use("TexTablet","2012","MIT","Steven Lovegrove"),

            tr("Icons"),
            tr("License") , tr("Source")
        ),

        /* 5 */ tr("Thanks to ") , thanksTo,
        /* 7 */ tr( license )
     );


	ui.setupUi(this);
    ui.textBrowser -> setOpenExternalLinks(true);
    ui.textBrowser -> setHtml(html);

    QAction * action = new QAction("large",this);
    connect(action,SIGNAL(triggered()),SLOT(largeLogo()));
    ui.label -> addAction(action);
    ui.label -> setContextMenuPolicy(Qt::ActionsContextMenu);
}



AboutDialog::~AboutDialog(){}

void AboutDialog::largeLogo(){

    QDialog * dialog = new QDialog(nullptr);
    dialog -> setAttribute(Qt::WA_DeleteOnClose);
    dialog -> setLayout(new QHBoxLayout(dialog));

    QLabel * label = new QLabel(dialog);
    label -> setPixmap(QPixmap(":/images/splash_large.png"));
    dialog -> layout() -> addWidget(label);
    dialog -> setWindowTitle("TeXstudio");
    dialog -> exec();
}
