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
    "   <b> %1 %2 </b> %3                                                       <br>"
    "                                                                           <br>"
    "   <b>QT Version</b>                                                       <br>"
    "   %4: %5                                                                  <br>"
    "   %6: %7 %8                                                               <br>"
    "                                                                           <br>"
    "  「 <a href='https://texstudio.org/'>Website</a> 」                            "
    "  「 <a href='https://github.com/texstudio-org/texstudio'>Github</a> 」     <br>"
    "                                                                           <br>"
    "   <h2>Copyright ©</h2>                                                    <br>"
    "                                                                           <br>"
    "   <b>%1</b>                                                               <br>"
    "   - Benito van der Zander                                                 <br>"
    "   - Jan Sundermeyer                                                       <br>"
    "   - Daniel Braun                                                          <br>"
    "   - Tim Hoffmann                                                          <br>"
    "                                                                           <br>"
    "   <b>TeXMaker:</b> Pascal Brachet                                         <br>"
    "                                                                           <br>"
    "   <b>QCodeEdit:</b> Luc Bruant                                            <br>"
    "                                                                           <br>"
    "   <b>%9:</b> Joël Amblard                                                 <br>"
    "                                                                           <br>"
    "   <b> %10 :</b>                                                           <br>"
    "   - QtCreator ( GPL | Copyright (C) Nokia )                               <br>"
    "   - SyncTeX ( Jerome Laurens )                                            <br>"
    "   - Hunspell ( GPL )                                                      <br>"
    "   - KILE ( GPL )                                                          <br>"
    "                                                                           <br>"
    "   <h3> %1 %11 </h3>                                                           "
    "                                                                           <br>"
    "   <h5> %12 </h5>                                                              "
    "                                                                           <br>"
    "   <h5> %13 </h5>                                                              "
    "                                                                           <br>"
    "   <h5> %14 </h5>                                                              "
    "                                                                           <br>"
    "                                                                           <br>"
    "   %15                                                                     <br>"
    "                                                                               "
    "   %16                                                                     <br>"
    "                                                                               "
    "   %17                                                                     <br>"
    "                                                                               "
    "   %18                                                                     <br>"
    "                                                                               "
    "   <h4> %19 </h4>                                                              "
    "   - Crystal Project (LGPL)                                                <br>"
    "   - Oxygen Icon Yheme (CC-BY-SA 3.0)                                      <br>"
    "                                                                           <br>"
    "   <h4> Adwaitaa-QT </h4>                                                      "
    "   %20: GPL2                                                               <br>"
    "   %21: 「 <a href='https://github.com/FedoraQt/adwaita-qt'>Github</a> 」   <br>"
    "                                                                           <br>"
    "   <h3> %22 </h3> %23                                                      <br>"
    "                                                                           <br>"
    "                                                                           <br>"
    "   <i> %24 </i>                                                            <br>"
    "                                                                           <br>"
    "</p>"
;


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


QString AboutDialog::use(QString name,QString copyright,QString license,QString author){
    return "<h4>" + (name) + "</h4>" +
           tr("Copyright") + ": " + (copyright) + "<br>" +
           tr("License")   + ": " + (license)   + "<br>" +
           tr("Author")    + ": " + (author)    + "<br>" + "<br>";
};

AboutDialog::AboutDialog(QWidget * parent) : QDialog(parent) {

    const QString html = aboutTemplate.arg(

        /*  1 */ TEXSTUDIO , TXSVERSION , git,
        /*  4 */ tr("Using") , qVersion(),
        /*  6 */ tr("Compiled") , QT_VERSION_STR , COMPILED_DEBUG_OR_RELEASE,
        /*  9 */ tr("HTML Conversion"),
        /* 10 */ tr("TeXstudio contains code from"),
        /* 11 */ tr("Uses"),

        /* 12 */ tr("PDF Viewer of TeXworks"),
        /* 13 */ tr("An image by Alexander Klink."),
        /* 14 */ tr("Flowlayout from QT 5.6 examples"),

        /* 15 */ use("DSingleApplication Class","BioImage Informatics","GPL","Dima Fedorov Levit"),
        /* 16 */ use("TexTablet","2012","MIT","Steven Lovegrove"),
        /* 17 */ use("QuaZip","2005 - 2012","LGPL","Sergey A. Tachenov & Contributors"),
        /* 18 */ use("Title Case","2008 - 2013","MIT","David Gouch"),

        /* 19 */ tr("Icons"),
        /* 20 */ tr("License") , tr("Source"),
        /* 22 */ tr("Thanks to ") , thanksTo,
        /* 24 */ tr(
            "This program is licensed to you under the terms of the GNU General "
            "Public License Version 2 as published by the Free Software Foundation."
        )
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
