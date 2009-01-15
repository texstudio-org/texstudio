/***************************************************************************
 *   copyright       : (C) 2007 by Pascal Brachet                          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef SPELLERDIALOG_H
#define SPELLERDIALOG_H

#include "ui_spellerdialog.h"
#include "latexeditor.h"
#include "hunspell/hunspell.hxx"

#include <QTextCursor>

class SpellerDialog : public QDialog  {
   Q_OBJECT
public:
	SpellerDialog(QWidget *parent=0,LatexEditor *ed=0, QString SpellDic="", QString ignoredWords="");
	~SpellerDialog();
	Ui::SpellerDialog ui;
QStringList alwaysignoredwordList;
private :
QString spell_dic, spell_encoding;
LatexEditor *editor;
QStringList ignoredwordList;
int startpos, endpos, deltacol;
Hunspell * pChecker;
bool go;
QTextCursor c;
protected:
void closeEvent( QCloseEvent* );
private slots:
void accept();
void spellingInit();
void slotIgnore();
void slotAlwaysIgnore();
void slotReplace();
void updateItem();
void SpellingNextWord();
};


#endif
