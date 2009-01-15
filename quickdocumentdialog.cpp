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


QuickDocumentDialog::QuickDocumentDialog(QWidget *parent, const char *name)
    :QDialog( parent)
{
setWindowTitle(name);
setModal(true);
ui.setupUi(this);
connect(ui.pushButtonClass , SIGNAL(clicked()), SLOT(addUserClass()) );
ui.comboBoxSize->addItem( "10pt" );
ui.comboBoxSize->addItem( "11pt" );
ui.comboBoxSize->addItem( "12pt" );
connect(ui.pushButtonPaper , SIGNAL(clicked()), SLOT(addUserPaper()) );
connect(ui.pushButtonEncoding , SIGNAL(clicked()), SLOT(addUserEncoding()) );
connect(ui.pushButtonOptions , SIGNAL(clicked()), SLOT(addUserOptions()) );
ui.listWidgetOptions->setSelectionMode(QAbstractItemView::ExtendedSelection  );
setWindowTitle(tr("Quick Start"));
}

QuickDocumentDialog::~QuickDocumentDialog(){
}

void QuickDocumentDialog::Init()
{
ui.comboBoxClass->clear();
ui.comboBoxClass->addItem( "article" );
ui.comboBoxClass->addItem( "report");
ui.comboBoxClass->addItem( "letter" );
ui.comboBoxClass->addItem( "book" );
ui.comboBoxClass->addItem( "beamer" );
if (!otherClassList.isEmpty ()) ui.comboBoxClass->addItems(otherClassList);

ui.comboBoxPaper->clear();
ui.comboBoxPaper->addItem( "a4paper" );
ui.comboBoxPaper->addItem( "a5paper" );
ui.comboBoxPaper->addItem( "b5paper" );
ui.comboBoxPaper->addItem( "letterpaper" );
ui.comboBoxPaper->addItem( "legalpaper" );
ui.comboBoxPaper->addItem( "executivepaper" );
if (!otherPaperList.isEmpty ()) ui.comboBoxPaper->addItems(otherPaperList);

ui.comboBoxEncoding->clear();
ui.comboBoxEncoding->addItem( "latin1" );
ui.comboBoxEncoding->addItem( "latin2" );
ui.comboBoxEncoding->addItem( "latin3" );
ui.comboBoxEncoding->addItem( "latin5" );
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
if (!otherEncodingList.isEmpty ()) ui.comboBoxEncoding->addItems(otherEncodingList);

ui.listWidgetOptions->clear();
ui.listWidgetOptions->addItem("landscape" );
ui.listWidgetOptions->addItem("draft" );
ui.listWidgetOptions->addItem("final" );
ui.listWidgetOptions->addItem("oneside" );
ui.listWidgetOptions->addItem("twoside" );
ui.listWidgetOptions->addItem("openright" );
ui.listWidgetOptions->addItem("openany" );
ui.listWidgetOptions->addItem("onecolumn" );
ui.listWidgetOptions->addItem("twocolumn" );
ui.listWidgetOptions->addItem("titlepage" );
ui.listWidgetOptions->addItem("notitlepage" );
ui.listWidgetOptions->addItem("openbib" );
ui.listWidgetOptions->addItem("leqno" );
ui.listWidgetOptions->addItem("fleqn" );
if (!otherOptionsList.isEmpty ()) ui.listWidgetOptions->addItems(otherOptionsList);
}

void QuickDocumentDialog::addUserClass()
{
QString newoption="";
dlg = new AddOptionDialog(this,"New");
  if ( dlg->exec() )
  {
  newoption=dlg->ui.lineEdit->text();
  if (newoption!="") otherClassList.append(newoption);
  Init();
  }
delete (dlg);
}

void QuickDocumentDialog::addUserPaper()
{
QString newoption="";
dlg = new AddOptionDialog(this,"New");
  if ( dlg->exec() )
  {
  newoption=dlg->ui.lineEdit->text();
  if (newoption!="") otherPaperList.append(newoption);
  Init();
  }
delete (dlg);
}

void QuickDocumentDialog::addUserEncoding()
{
QString newoption="";
dlg = new AddOptionDialog(this,"New");
  if ( dlg->exec() )
  {
  newoption=dlg->ui.lineEdit->text();
  if (newoption!="") otherEncodingList.append(newoption);
  Init();
  }
delete (dlg);
}

void QuickDocumentDialog::addUserOptions()
{
QString newoption="";
dlg = new AddOptionDialog(this,"New");
  if ( dlg->exec() )
  {
  newoption=dlg->ui.lineEdit->text();
  if (newoption!="") otherOptionsList.append(newoption);
  Init();
  }
delete (dlg);
}
