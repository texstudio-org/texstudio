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


#include "svn_revision.h"
#ifndef SVN_REVISION_NUMBER
#define SVN_REVISION_NUMBER ""
#endif


AboutDialog::AboutDialog(QWidget *parent)
		:QDialog(parent) {
	ui.setupUi(this);
	ui.textBrowser->setOpenExternalLinks(true);
	ui.textBrowser->setHtml(tr("<b>TexMakerX 2.0 (SVN " SVN_REVISION_NUMBER ")</b>")  + "<br>" +
				tr("Using Qt Version %1, compiled with Qt %2").arg(qVersion()).arg(QT_VERSION_STR) + "<br>" +
				tr("Copyright (c) (original TexMaker) 2004-2010 by Pascal Brachet<br>")+
				tr("TexMakerX: Benito van der Zander, Jan Sundermeyer, Daniel Braun<br>QCodeEdit: Luc Bruant <br>html conversion: ")+QString::fromUtf8("Joël Amblard.</i><br>")+
				tr("TexMakerX contains code from the Hunspell (GPL), QtCreator (GPL, Copyright (C) Nokia) and KILE (GPL) program.<br> TexMakerX uses the DSingleApplication class (Author: Dima Fedorov Levit - Copyright (C) BioImage Informatics - Licence: GPL)<br>")+
				tr("Thanks to ")+QString::fromUtf8("Frederic Devernay, Denis Bitouzé, Jean-Côme Charpentier, Luis Silvestre, Enrico Vittorini, Aleksandr Zolotarev, David Sichau, Grigory Mozhaev, mattgk, A. Weder, Pavel Fric, András Somogyi & István Blahota.<br><br>")+
				tr("Project home site : <a href=\"http://texmakerx.sourceforge.net/\">http://texmakerx.sourceforge.net/</a><br><br>")+
				tr("Home site of original Texmaker: <a href=\"http://www.xm1math.net/texmaker/\">http://www.xm1math.net/texmaker/</a><br><br>")+
				tr("This program is licensed to you under the terms of the GNU General Public License Version 2 as published by the Free Software Foundation."));
}

AboutDialog::~AboutDialog() {
}
