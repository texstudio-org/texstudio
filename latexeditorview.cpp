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

#include "latexeditorview.h"

#include "smallUsefulFunctions.h"

#include "qdocumentline.h"
#include "qdocumentcommand.h"
 

#include "qlinemarksinfocenter.h"
#include "qformatfactory.h"

#include "qlinemarkpanel.h"
#include "qlinenumberpanel.h"
#include "qfoldpanel.h"
#include "qlinechangepanel.h"
#include "qstatuspanel.h"
#include "qsearchreplacepanel.h"

#include <QVBoxLayout>
#include <QFrame>
#include <QKeyEvent>
#include <QMenu>
#include <QMessageBox>
#include <QToolTip>

//------------------------------Default Input Binding--------------------------------
bool DefaultInputBinding::keyPressEvent(QKeyEvent *event, QEditor *editor)
{
    if (event->text()==QString("\\") && LatexEditorView::completer)  { //workaround because trigger doesn't seem work
        editor->cursor().removeSelectedText();
        editor->cursor().insertText("\\");
        LatexEditorView::completer->complete(editor,false);
        return true;
    }
    if (event->modifiers()==Qt::ControlModifier && (event->key()==Qt::Key_Left || event->key()==Qt::Key_Right)){
        int tccFormat=QDocument::formatFactory()->id("temporaryCodeCompletion");
        if (editor->cursor().line().hasOverlay(tccFormat) || editor->cursor().line().next().hasOverlay(tccFormat) || editor->cursor().line().previous().hasOverlay(tccFormat)) {
            int cn=editor->cursor().columnNumber();
            int an=editor->cursor().anchorColumnNumber();
            QFormatRange fr (0,0,0);
            QDocumentCursor selector=editor->cursor();
            if (event->key()==Qt::Key_Right) {
                fr = selector.line().getFirstOverlayBetween((an>cn?an:cn)+1,editor->cursor().line().length(),tccFormat);
                if (fr.length==0 && selector.line().next().isValid()) {
                    selector.movePosition(1,QDocumentCursor::Down,QDocumentCursor::MoveAnchor);
                    fr = selector.line().getFirstOverlayBetween(0,selector.line().length(),tccFormat);
                }
            } else {
                fr = selector.line().getLastOverlayBetween(0,(an<cn?an:cn)-1,tccFormat);
                if (fr.length==0 && selector.line().previous().isValid()) {
                    selector.movePosition(1,QDocumentCursor::Up,QDocumentCursor::MoveAnchor);
                    fr = selector.line().getLastOverlayBetween(0,selector.line().length(),tccFormat);
                }
            }
            if (fr.length!=0) {
                selector.setColumnNumber(fr.offset);
                selector.movePosition(fr.length,QDocumentCursor::Right,QDocumentCursor::KeepAnchor);
                editor->setCursor(selector);
                return true;
            }
            return editor->cursor().line().hasOverlay(tccFormat);
        }
    }
    if (!keyToReplace) return false;
    int pos;
    if ((pos=keyToReplace->indexOf(event->text()))>=0) {
        QString whitespace(" \t\n");
        QChar prev=editor->cursor().previousChar();
        editor->cursor().removeSelectedText();
        if (whitespace.contains(prev)||prev==QChar(0))  editor->cursor().insertText(keyReplaceBeforeWord->at(pos));
        else editor->cursor().insertText(keyReplaceAfterWord->at(pos));
        return true;
    }
    if (LatexEditorView::hideTooltipWhenLeavingLine!=-1 && editor->cursor().lineNumber()!=LatexEditorView::hideTooltipWhenLeavingLine) {
        LatexEditorView::hideTooltipWhenLeavingLine=-1;
        QToolTip::hideText();
    }
    return false;
}
bool DefaultInputBinding::contextMenuEvent(QContextMenuEvent *event, QEditor *editor){
    if (!contextMenu) contextMenu=new QMenu(0);
    contextMenu->clear();
    if (LatexEditorView::speller) {
        LatexEditorView *edView=qobject_cast<LatexEditorView *>(editor->parentWidget()); //a qobject is necessary to retrieve events
        QDocumentCursor cursor;
        if (event->reason()==QContextMenuEvent::Mouse) cursor=editor->cursorForPosition(editor->mapToContents(event->pos()));
        else cursor=editor->cursor();
        if (edView && cursor.isValid() && cursor.line().isValid())  {
            QFormatRange fr;
            if (cursor.hasSelection()) fr= cursor.line().getOverlayAt((cursor.columnNumber()+cursor.anchorColumnNumber()) / 2,LatexEditorView::speller->spellcheckErrorFormat);
            else fr = cursor.line().getOverlayAt(cursor.columnNumber(),LatexEditorView::speller->spellcheckErrorFormat);
            if (fr.length>0 && fr.format==LatexEditorView::speller->spellcheckErrorFormat) {
                QString word=cursor.line().text().mid(fr.offset,fr.length);
                if (!(editor->cursor().hasSelection() && editor->cursor().selectedText().length()>0) || editor->cursor().selectedText()==word 
                    || editor->cursor().selectedText()==lastSpellCheckedWord) {
                    lastSpellCheckedWord=word;
                    word=latexToPlainWord(word);
                    QDocumentCursor wordSelection(editor->document(),cursor.lineNumber(),fr.offset);
                    wordSelection.movePosition(fr.length,QDocumentCursor::Right,QDocumentCursor::KeepAnchor);
                    editor->setCursor(wordSelection);

                    if (event->modifiers() & Qt::ShiftModifier) {
                        QAction* aReplacement=new QAction(LatexEditorView::tr("shift pressed => suggestions hidden"),contextMenu);
                        edView->connect(aReplacement,SIGNAL(triggered()),edView,SLOT(spellCheckingListSuggestions()));
                        contextMenu->addAction(aReplacement);
                    } else edView->spellCheckingListSuggestions();
                    QFont ignoreFont; ignoreFont.setItalic(true);
                    QAction* act=new QAction (LatexEditorView::tr("always ignore"),contextMenu);
                    act->setFont(ignoreFont);
                    edView->connect(act,SIGNAL(triggered()),edView,SLOT(spellCheckingAlwaysIgnore()));
                    contextMenu->addAction(act);
                    contextMenu->addSeparator();
                }
            }
        }
    }
    contextMenu->addActions(baseActions);
    if (event->reason()==QContextMenuEvent::Mouse) contextMenu->exec(event->globalPos());
    else {
        QPoint curPoint=editor->cursor().documentPosition();
        curPoint.ry() += editor->document()->fontMetrics().lineSpacing();
        contextMenu->exec(editor->mapToGlobal(editor->mapFromContents(curPoint)));
    }
    return true;
}

DefaultInputBinding *defaultInputBinding = new DefaultInputBinding();



//----------------------------------LatexEditorView-----------------------------------
SpellerUtility* LatexEditorView::speller=0;
LatexCompleter* LatexEditorView::completer=0;
int LatexEditorView::hideTooltipWhenLeavingLine = -1;

LatexEditorView::LatexEditorView(QWidget *parent) : QWidget(parent),curChangePos(-1),lastSetBookmark(0)
{
    QVBoxLayout* mainlay = new QVBoxLayout( this );
    mainlay->setSpacing(0);
    mainlay->setMargin(0);

	codeeditor = new QCodeEdit(false,this);
    editor=codeeditor->editor();
    
    lineMarkPanel=new QLineMarkPanel;
    lineMarkPanelAction=codeeditor->addPanel(lineMarkPanel, QCodeEdit::West, false);
    lineNumberPanel=new QLineNumberPanel;
    lineNumberPanelAction=codeeditor->addPanel(lineNumberPanel, QCodeEdit::West, false);;
    lineFoldPanel=codeeditor->addPanel(new QFoldPanel, QCodeEdit::West, false);
    lineChangePanel=codeeditor->addPanel(new QLineChangePanel, QCodeEdit::West, false);
    statusPanel=codeeditor->addPanel(new QStatusPanel, QCodeEdit::South, false);
	searchReplacePanel=codeeditor->addPanel(new QSearchReplacePanel, QCodeEdit::South,false);

    
    connect(lineMarkPanel,SIGNAL(lineClicked(int)),this,SLOT(lineMarkClicked(int)));
    connect(editor->document(),SIGNAL(contentsChange(int, int)),this,SLOT(documentContentChanged(int, int)));
    connect(editor->document(),SIGNAL(lineDeleted(QDocumentLineHandle*)),this,SLOT(lineDeleted(QDocumentLineHandle*)));

    connect(LatexEditorView::speller,SIGNAL(reloadDictionary()),this,SLOT(dictionaryReloaded()));

    //editor->setFlag(QEditor::CursorJumpPastWrap,false);
        
    editor->setInputBinding(defaultInputBinding);
    mainlay->addWidget(editor);

    setFocusProxy( editor );
}

LatexEditorView::~LatexEditorView()
{
}

void LatexEditorView::complete(bool forceVisibleList, bool normalText){
    if (!LatexEditorView::completer) return;
    setFocus();
    LatexEditorView::completer->complete(editor,forceVisibleList,normalText);
}
void LatexEditorView::jumpChangePositionBackward(){
    if (changePositions.size()==0) return;
    for (int i=changePositions.size()-1;i>=0;i--)
        if (!changePositions[i].first.isValid() || changePositions[i].first.lineNumber()<0) {
            changePositions.removeAt(i);
            if (i<=curChangePos) curChangePos--;
        }
    if (curChangePos >= changePositions.size()-1) curChangePos = changePositions.size()-1;
    else if (curChangePos>=0 && curChangePos < changePositions.size()-1) curChangePos++;
    else if (editor->cursor().line()==changePositions.first().first) curChangePos=1;
    else curChangePos=0;
    if (curChangePos>=0 && curChangePos < changePositions.size()) 
        editor->setCursorPosition(changePositions[curChangePos].first.lineNumber(),changePositions[curChangePos].second);
}
void LatexEditorView::jumpChangePositionForward(){
    for (int i=changePositions.size()-1;i>=0;i--)
        if (!changePositions[i].first.isValid() || changePositions[i].first.lineNumber()<0) {
            changePositions.removeAt(i);
            if (i<=curChangePos) curChangePos--;
        }
    if (curChangePos>0) {
        curChangePos--;
        editor->setCursorPosition(changePositions[curChangePos].first.lineNumber(),changePositions[curChangePos].second);
    }    
}
void LatexEditorView::jumpToBookmark(int bookmarkNumber){
    int markLine=editor->document()->findNextMark(bookMarkId(bookmarkNumber),editor->cursor().line().lineNumber(),editor->cursor().line().lineNumber()-1);
    if (markLine>=0) {
        editor->setCursorPosition(markLine,0);
        editor->setFocus();
    }
}
void LatexEditorView::toggleBookmark(int bookmarkNumber){
    int rmid=bookMarkId(bookmarkNumber);
    if (editor->cursor().line().hasMark(rmid)) {
        editor->cursor().line().removeMark(rmid);
        return;
    }
    if (bookmarkNumber>=0) editor->document()->line(editor->document()->findNextMark(rmid)).removeMark(rmid);
    for (int i=-1;i<10;i++) editor->cursor().line().removeMark(bookMarkId(i));
    editor->cursor().line().addMark(rmid);
    editor->ensureCursorVisible();
    if (bookmarkNumber>=1 && bookmarkNumber<=3) lastSetBookmark=bookmarkNumber;
}

void LatexEditorView::cleanBib(){
    QDocument* doc = editor->document();
    for (int i=doc->lines()-1;i>=0;i--){
        QString trimLine=doc->line(i).text().trimmed();
        if (trimLine.startsWith("OPT") || trimLine.startsWith("ALT")) 
           doc->execute(new QDocumentEraseCommand(i,0,i+1,0,doc));
        }
    setFocus();
}



void LatexEditorView::setKeyReplacements(QStringList *UserKeyReplace, QStringList *UserKeyReplaceAfterWord, QStringList *UserKeyReplaceBeforeWord){
    if (!defaultInputBinding) return;
    defaultInputBinding->keyToReplace=UserKeyReplace;
    defaultInputBinding->keyReplaceAfterWord=UserKeyReplaceAfterWord;
    defaultInputBinding->keyReplaceBeforeWord=UserKeyReplaceBeforeWord;
}
void LatexEditorView::setBaseActions(QList<QAction *> baseActions){
    if (!defaultInputBinding) return;
    defaultInputBinding->baseActions=baseActions;
}
void LatexEditorView::setSpeller(SpellerUtility* speller){
    LatexEditorView::speller=speller;
}
void LatexEditorView::setCompleter(LatexCompleter* newCompleter){
    LatexEditorView::completer=newCompleter;
}
int LatexEditorView::bookMarkId(int bookmarkNumber){
    if (bookmarkNumber==-1) return  QLineMarksInfoCenter::instance()->markTypeId("bookmark"); //unnumbered mark
    else return QLineMarksInfoCenter::instance()->markTypeId("bookmark"+QString::number(bookmarkNumber));
}

void LatexEditorView::lineMarkClicked(int line){
    QDocumentLine l=editor->document()->line(line);
    if (!l.isValid()) return;
    //remove old mark (when possible)
    for (int i=-1;i<10;i++)
      if (l.hasMark(bookMarkId(i))) {
        l.removeMark(bookMarkId(i));
        return;
      }
    //add unused mark (1..3) (when possible)
    for (int i=1;i<=3;i++) 
        if (editor->document()->findNextMark(bookMarkId(i))<0) {
            l.addMark(bookMarkId(i));
            return;
        }
    //remove/add used mark
    lastSetBookmark++;
    if (lastSetBookmark<1 || lastSetBookmark>3) lastSetBookmark=1;
    editor->document()->line(editor->document()->findNextMark(bookMarkId(lastSetBookmark))).removeMark(bookMarkId(lastSetBookmark));
    l.addMark(bookMarkId(lastSetBookmark));
}

void LatexEditorView::documentContentChanged(int linenr, int count){
    QDocumentLine startline=editor->document()->line(linenr);
    if  ((linenr>=0 || count<editor->document()->lines()) && editor->cursor().isValid() &&
          !editor->cursor().atLineStart() && editor->cursor().line().text().trimmed().length()>0 &&
          startline.isValid()) {
        /*if (curChangePos<1) {
            if (changePositions.size()==0 || changePositions.first.first<>linenr) 
                changePositions.insert(0,QPair<linenr,editor->cursor().columnNumber());
        } else if (curChangePos==changePositions.size()-1) {
            if (changePositions[curChangePos].first!=linenr) 
                changePositions.append(QPair<linenr,editor->cursor().columnNumber());
        } else {
            if (changePositions[curChangePos].first!=linenr && changePositions[curChangePos+1].first!=linenr) 
                changePositions.insert(curChangePos,QPair<linenr,editor->cursor().columnNumber());
        }*/

        bool add=false;
        if (changePositions.size()<=0) add=true;
        else if (curChangePos<1) {            
            if (changePositions.first().first!=startline) add=true;
            else changePositions.first().second=editor->cursor().columnNumber();               
        } else if (curChangePos>=changePositions.size()-1) {
            if (changePositions.last().first!=startline) add=true;
            else changePositions.last().second=editor->cursor().columnNumber();                
        }  else if (changePositions[curChangePos].first==startline) changePositions[curChangePos].second=editor->cursor().columnNumber();
        else if(changePositions[curChangePos+1].first==startline) changePositions[curChangePos+1].second=editor->cursor().columnNumber();
        else add=true;
        if (add) {
            curChangePos=-1;
            changePositions.insert(0,QPair<QDocumentLine,int>(startline,editor->cursor().columnNumber()));
            if (changePositions.size()>20) changePositions.removeLast();
        }   
    }
    
    if (!speller || !QDocument::formatFactory()) return;
    int tccFormat=QDocument::formatFactory()->id("temporaryCodeCompletion");
    for (int i=linenr;i<linenr+count;i++){
        QDocumentLine line = editor->document()->line(i);
        if (!line.isValid() || line.hasOverlay(tccFormat)) continue;
        line.clearOverlays();
        if (line.length()<=3) continue;
        if (!speller->isActive()) continue;
        
        QString lineText = line.text();
        QString word;
        int start=0;int wordstart;
        while (nextWord(lineText,start,word,wordstart))
            if (word.length()>=3 && !speller->check(word)) 
                line.addOverlay(QFormatRange(wordstart,start-wordstart,speller->spellcheckErrorFormat));
    }
}
void LatexEditorView::lineDeleted(QDocumentLineHandle* l ){
    QHash<QDocumentLineHandle*, int>::iterator it;
    while ((it=lineToLogEntries.find(l))!=lineToLogEntries.end()) {
        logEntryToLine.remove(it.value());        
        lineToLogEntries.erase(it);
    }
        
    QPair<int, int> p;
    //QMessageBox::information(0,QString::number(nr),"",0);
    for (int i=0;i<changePositions.size();i++) 
      if (changePositions[i].first==l) {
          if (changePositions[i].first.previous().isValid()) changePositions[i].first=changePositions[i].first.previous();
          else if (changePositions[i].first.next().isValid()) changePositions[i].first=changePositions[i].first.next();
          else changePositions.removeAt(i);
      //    QMessageBox::information(0,"trig",0);
      }
}
void LatexEditorView::spellCheckingReplace(){
    QAction* action = qobject_cast<QAction*>(QObject::sender());
    if (editor && action) {
        editor->cursor().removeSelectedText();
        editor->cursor().insertText(action->text());
    }
}
void LatexEditorView::spellCheckingAlwaysIgnore(){
    if (speller && editor && editor->cursor().hasSelection() && (editor->cursor().selectedText()==defaultInputBinding->lastSpellCheckedWord)) {
        QString newToIgnore = editor->cursor().selectedText();
        speller->addToIgnoreList(newToIgnore);
        //documentContentChanged(editor->cursor().lineNumber(),1);
        for (int i=0;i<editor->document()->lines();i++){
            QList<QFormatRange> li=editor->document()->line(i).getOverlays();
            QString curLineText=editor->document()->line(i).text();
            for (int j=0;j<li.size();j++) 
                if (curLineText.mid(li[j].offset,li[j].length)==newToIgnore) 
                    editor->document()->line(i).removeOverlay(li[j]);
        }
        editor->viewport()->update();
    }
}
void LatexEditorView::spellCheckingListSuggestions(){
    QMenu* contextMenu = defaultInputBinding->contextMenu;
    if (!contextMenu) return;
    bool repopup=false;
    if (!contextMenu->actions().isEmpty() && contextMenu->actions()[0]->text()==tr("shift pressed => suggestions hidden")) {
        contextMenu->removeAction(contextMenu->actions()[0]);
        repopup=true;
    }
    QAction* before=0;
    if (!contextMenu->actions().isEmpty()) before=contextMenu->actions()[0];
    QStringList suggestions= LatexEditorView::speller->suggest(defaultInputBinding->lastSpellCheckedWord);
    if (!suggestions.empty()) {
        QFont correctionFont;correctionFont.setBold(true);
        for (int i=0;i<suggestions.size();i++) {
            QAction* aReplacement=new QAction(suggestions[i],contextMenu);
            aReplacement->setFont(correctionFont);
            connect(aReplacement,SIGNAL(triggered()),this,SLOT(spellCheckingReplace()));
            contextMenu->insertAction(before,aReplacement);
        }
    }
    if (repopup) {
    //    contextMenu->close();
        contextMenu->exec();
    }
}
void LatexEditorView::dictionaryReloaded(){
   //   QMessageBox::information(0,"trig","",0);
    documentContentChanged(0,editor->document()->lines());
}
