/***************************************************************************
 *   copyright       : (C) 2008 by Benito van der Zander                   *
 *   http://www.xm1math.net/texmaker/                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef LATEXEDITORVIEW_H
#define LATEXEDITORVIEW_H

#include <qwidget.h>
#include <qfont.h>
#include <qcolor.h>


#include "spellerutility.h"

#include "qcodeedit.h"
#include "qeditor.h"
#include "qlinemarkpanel.h"
#include "qlinenumberpanel.h"
//#include "qpanel.h"

class DefaultInputBinding: public QEditor::InputBinding{
 //  Q_OBJECT not possible because inputbinding is no qobject
public:
    DefaultInputBinding():keyToReplace(0),contextMenu(0){}
	virtual QString id() const{return "TexMakerX::DefaultInputBinding";}
    virtual QString name() const{return "TexMakerX::DefaultInputBinding";}

    virtual bool keyPressEvent(QKeyEvent *event, QEditor *editor);
    virtual bool contextMenuEvent(QContextMenuEvent *event, QEditor *editor);
private:
    friend class LatexEditorView;
    QVector<QString> *keyToReplace;
    QVector<QString> *keyReplaceAfterWord;
    QVector<QString> *keyReplaceBeforeWord;
    QList<QAction *> baseActions;
    
    QMenu* contextMenu;
    QString lastSpellCheckedWord;
    
};

class LatexEditorView : public QWidget  {
   Q_OBJECT
public:
    enum NextWordFlags{
        NW_NOTHING=0,
        NW_TEXT=1,
        NW_COMMAND=2,
        NW_COMMENT=4
    };

	LatexEditorView(QWidget *parent);
	~LatexEditorView();
    
    QCodeEdit *codeeditor;
    QEditor *editor;
    
    
//  FindWidget *findwidget;

    void jumpChangePositionBackward();
    void jumpChangePositionForward();
    void jumpToBookmark(int bookmarkNumber);
    void toggleBookmark(int bookmarkNumber);
    
    void cleanBib();
    static void setKeyReplacements(QVector<QString> *UserKeyReplace, QVector<QString> *UserKeyReplaceAfterWord, QVector<QString> *UserKeyReplaceBeforeWord);
    static void setBaseActions(QList<QAction *> baseActions);
    static void setSpeller(SpellerUtility* mainSpeller);

    static bool nextWord(QString line,int &index,QString &outWord,int &wordStartIndex);    
    static int nextWord(QString line,int &index,QString &outWord,int &wordStartIndex, int flags);    
    static QString latexToPlainWord(QString word);    

    QAction *lineNumberPanelAction, *lineMarkPanelAction, *lineFoldPanel, *lineChangePanel, *statusPanel, *searchReplacePanel;
    QLineMarkPanel* lineMarkPanel;
    QLineNumberPanel* lineNumberPanel;
private:
    friend class DefaultInputBinding;
    static int bookMarkId(int bookmarkNumber);
    
    static SpellerUtility* speller;
    QList<QPair<QDocumentLine, int> > changePositions; //line, index
    int curChangePos;
    int lastSetBookmark; //only looks at 1..3 (mouse range)
public slots:
    void lineMarkClicked(int line);
    void documentContentChanged(int linenr, int count);
    void lineDeleted(QDocumentLineHandle* l);
    void spellCheckingReplace();
    void spellCheckingAlwaysIgnore();
    void dictionaryReloaded();
};

#endif
