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

AboutDialog::AboutDialog(QWidget *parent)
		:QDialog(parent) {
	ui.setupUi(this);
	ui.textBrowser->setOpenExternalLinks(true);
	ui.textBrowser->setHtml(QString::fromUtf8("<b>TexmakerX 1.8.1</b><br>Copyright (c) (original TexMaker) 2004-2008 by Pascal Brachet<br>")+
	                        QString::fromUtf8("TexMakerX: Benito van der Zander, Jan Sundermeyer, Daniel Braun<br>QCodeEdit: Luc Bruant <br>html conversion: Joël Amblard.</i><br>")+
	                        QString::fromUtf8("TexMakerX contains code from the Hunspell program (GPL).<br>TexMakerX uses the DSingleApplication class (Author: Dima Fedorov Levit - Copyright (C) BioImage Informatics - Licence: GPL)<br>")+
	                        QString::fromUtf8("Thanks to Frederic Devernay, Denis Bitouzé, Jean-Côme Charpentier, Luis Silvestre & Enrico Vittorini.<br><br>")+
	                        QString::fromUtf8("Project home site : <a href=\"http://texmakerx.sourceforge.net/\">http://texmakerx.sourceforge.net/</a><br><br>")+
	                        QString::fromUtf8("Home site of original Texmaker: <a href=\"http://www.xm1math.net/texmaker/\">http://www.xm1math.net/texmaker/</a><br><br>")+
	                        QString::fromUtf8("This program is licensed to you under the terms of the GNU General Public License Version 2 as published by the Free Software Foundation."));
}

AboutDialog::~AboutDialog() {
}
