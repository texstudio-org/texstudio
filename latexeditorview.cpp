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
#include "latexeditorview_config.h"

#include "latexcompleter.h"
#include "latexdocument.h"
#include "smallUsefulFunctions.h"
#include "spellerutility.h"

#include "qdocumentline.h"
#include "qdocumentline_p.h"
#include "qdocumentcommand.h"

#include "qlinemarksinfocenter.h"
#include "qformatfactory.h"
#include "qlanguagedefinition.h"
#include "qnfadefinition.h"
#include "qnfa.h"

#include "qcodeedit.h"
#include "qeditor.h"
#include "qeditorinputbinding.h"
#include "qlinemarkpanel.h"
#include "qlinenumberpanel.h"
#include "qfoldpanel.h"
#include "qgotolinepanel.h"
#include "qlinechangepanel.h"
#include "qstatuspanel.h"
#include "qsearchreplacepanel.h"

//------------------------------Default Input Binding--------------------------------
class DefaultInputBinding: public QEditorInputBinding {
//  Q_OBJECT not possible because inputbinding is no qobject
public:
	DefaultInputBinding():keyToReplace(0),contextMenu(0) {}
	virtual QString id() const {
		return "TexMakerX::DefaultInputBinding";
	}
	virtual QString name() const {
		return "TexMakerX::DefaultInputBinding";
	}

	virtual bool keyPressEvent(QKeyEvent *event, QEditor *editor);
	virtual bool contextMenuEvent(QContextMenuEvent *event, QEditor *editor);
private:
	friend class LatexEditorView;
	QStringList *keyToReplace;
	QStringList *keyReplaceAfterWord;
	QStringList *keyReplaceBeforeWord;
	QList<QAction *> baseActions;

	QMenu* contextMenu;
	QString lastSpellCheckedWord;

};
bool DefaultInputBinding::keyPressEvent(QKeyEvent *event, QEditor *editor) {
	if (LatexEditorView::completer && LatexEditorView::completer->acceptTriggerString(event->text()))  {
		//update completer if necessary
		editor->updateCompleterNow();
		editor->insertText(event->text());
		LatexEditorView::completer->complete(editor,false);
		return true;
	}
	if (event->modifiers()==Qt::ControlModifier && (event->key()==Qt::Key_Left || event->key()==Qt::Key_Right))	 {
		int tccFormat=QDocument::formatFactory()->id("temporaryCodeCompletion");
		if (editor->cursor().line().hasOverlay(tccFormat) || editor->cursor().line().next().hasOverlay(tccFormat) || editor->cursor().line().previous().hasOverlay(tccFormat)) {
			int cn=editor->cursor().columnNumber();
			int an=editor->cursor().anchorColumnNumber();
			QFormatRange fr(0,0,0);
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
	if (!event->text().isEmpty()) {
		int pos=keyToReplace->indexOf(event->text());
		if (pos >=0) {
			QString whitespace(" \t\n");
			QChar prev=editor->cursor().previousChar();
			editor->insertText(whitespace.contains(prev)||prev==QChar(0)?keyReplaceBeforeWord->at(pos):keyReplaceAfterWord->at(pos));
			editor->emitCursorPositionChanged(); //prevent rogue parenthesis highlightations
			return true;
		}
	}
	if (LatexEditorView::hideTooltipWhenLeavingLine!=-1 && editor->cursor().lineNumber()!=LatexEditorView::hideTooltipWhenLeavingLine) {
		LatexEditorView::hideTooltipWhenLeavingLine=-1;
		QToolTip::hideText();
	}
	return false;
}
bool DefaultInputBinding::contextMenuEvent(QContextMenuEvent *event, QEditor *editor) {
	if (!contextMenu) contextMenu=new QMenu(0);
	contextMenu->clear();
	QDocumentCursor cursor;
	if (event->reason()==QContextMenuEvent::Mouse) cursor=editor->cursorForPosition(editor->mapToContents(event->pos()));
	else cursor=editor->cursor();
	if (cursor.isValid() && cursor.line().isValid())  {
		LatexEditorView *edView=qobject_cast<LatexEditorView *>(editor->parentWidget()); //a qobject is necessary to retrieve events
		QFormatRange fr;
		//spell checking
		if (edView && LatexEditorView::speller){
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
					QFont ignoreFont;
					ignoreFont.setItalic(true);
					QAction* act=new QAction(LatexEditorView::tr("always ignore"),contextMenu);
					act->setFont(ignoreFont);
					edView->connect(act,SIGNAL(triggered()),edView,SLOT(spellCheckingAlwaysIgnore()));
					contextMenu->addAction(act);
					contextMenu->addSeparator();
				}
			}
		}
		//citation checking
		int f=QDocument::formatFactory()->id("citationMissing");
		if (cursor.hasSelection()) fr= cursor.line().getOverlayAt((cursor.columnNumber()+cursor.anchorColumnNumber()) / 2,f);
		else fr = cursor.line().getOverlayAt(cursor.columnNumber(),f);
		if (fr.length>0 && fr.format==f) {
			QString word=cursor.line().text().mid(fr.offset,fr.length);
			editor->setCursor(editor->document()->cursor(cursor.lineNumber(),fr.offset,cursor.lineNumber(),fr.offset+fr.length));
			QAction* act=new QAction(LatexEditorView::tr("New BibTeX Entry %1").arg(word),contextMenu);
			edView->connect(act,SIGNAL(triggered()),edView,SLOT(requestCitation()));
			contextMenu->addAction(act);
			contextMenu->addSeparator();
		}
                //check input/include
                //find context of cursor
                QString line=cursor.line().text();
                QString command, value;
                LatexParser::ContextType result=LatexParser::findContext(line, cursor.columnNumber(), command, value);
                static const QStringList inputTokens = QStringList() << "\\input" << "\\include";
                if( (result==LatexParser::Command || result==LatexParser::Option) && inputTokens.contains(command)){
                    QAction* act=new QAction(LatexEditorView::tr("Open %1").arg(value),contextMenu);
                    act->setData(value);
                    edView->connect(act,SIGNAL(triggered()),edView,SLOT(openExternalFile()));
                    contextMenu->addAction(act);
                }

	}
	contextMenu->addActions(baseActions);
	if (event->reason()==QContextMenuEvent::Mouse) contextMenu->exec(event->globalPos());
	else {
		QPoint curPoint=editor->cursor().documentPosition();
		curPoint.ry() += editor->document()->getLineSpacing();
		contextMenu->exec(editor->mapToGlobal(editor->mapFromContents(curPoint)));
	}
	return true;
}

DefaultInputBinding *defaultInputBinding = new DefaultInputBinding();



//----------------------------------LatexEditorView-----------------------------------
SpellerUtility* LatexEditorView::speller=0;
LatexCompleter* LatexEditorView::completer=0;
int LatexEditorView::hideTooltipWhenLeavingLine = -1;

LatexEditorView::LatexEditorView(QWidget *parent, LatexEditorViewConfig* aconfig,LatexDocument *doc) : QWidget(parent), bibTeXIds(0),curChangePos(-1),lastSetBookmark(0), config(aconfig) {
	Q_ASSERT(config);
	QVBoxLayout* mainlay = new QVBoxLayout(this);
	mainlay->setSpacing(0);
	mainlay->setMargin(0);

	codeeditor = new QCodeEdit(false,this,doc);
	editor=codeeditor->editor();

	lineMarkPanel=new QLineMarkPanel;
	lineMarkPanelAction=codeeditor->addPanel(lineMarkPanel, QCodeEdit::West, false);
	lineNumberPanel=new QLineNumberPanel;
	lineNumberPanelAction=codeeditor->addPanel(lineNumberPanel, QCodeEdit::West, false);;
	lineFoldPanelAction=codeeditor->addPanel(new QFoldPanel, QCodeEdit::West, false);
	lineChangePanelAction=codeeditor->addPanel(new QLineChangePanel, QCodeEdit::West, false);

	statusPanel=new QStatusPanel;
	statusPanel->setFont(QApplication::font());
	statusPanelAction=codeeditor->addPanel(statusPanel, QCodeEdit::South, false);

	gotoLinePanel=new QGotoLinePanel;
	gotoLinePanel->setFont(QApplication::font());
	gotoLinePanelAction=codeeditor->addPanel(gotoLinePanel, QCodeEdit::South, false);

	searchReplacePanel=new QSearchReplacePanel;
	searchReplacePanel->setFont(QApplication::font());
	searchReplacePanelAction=codeeditor->addPanel(searchReplacePanel, QCodeEdit::South,false);
	searchReplacePanel->hide();


	connect(lineMarkPanel,SIGNAL(lineClicked(int)),this,SLOT(lineMarkClicked(int)));
	connect(lineMarkPanel,SIGNAL(toolTipRequested(int,int)),this,SLOT(lineMarkToolTip(int,int)));
	connect(editor,SIGNAL(hovered(QPoint)),this,SLOT(mouseHovered(QPoint)));
	connect(editor->document(),SIGNAL(contentsChange(int, int)),this,SLOT(documentContentChanged(int, int)));
	connect(editor->document(),SIGNAL(formatsChange(int,int)),this,SLOT(documentFormatsChanged(int, int)));
	connect(editor->document(),SIGNAL(lineDeleted(QDocumentLineHandle*)),this,SLOT(lineDeleted(QDocumentLineHandle*)));
	connect(editor->document(),SIGNAL(lineRemoved(QDocumentLineHandle*)),this,SLOT(lineRemoved(QDocumentLineHandle*)));

	connect(LatexEditorView::speller,SIGNAL(reloadDictionary()),this,SLOT(dictionaryReloaded()));

	//editor->setFlag(QEditor::CursorJumpPastWrap,false);

	editor->setInputBinding(defaultInputBinding);
	editor->document()->setLineEnding(QDocument::Local);
	mainlay->addWidget(editor);

	setFocusProxy(editor);

	containedLabels=new References("(\\\\label)\\{(.+)\\}");
	containedReferences=new References("(\\\\ref|\\\\pageref)\\{(.+)\\}");
	environmentFormat=0;
	structureFormat=0;
	//containedLabels.setPattern("(\\\\label)\\{(.+)\\}");
	//containedReferences.setPattern("(\\\\ref|\\\\pageref)\\{(.+)\\}");
	updateSettings();
	SynChecker.start();
}

LatexEditorView::~LatexEditorView() {
	delete searchReplacePanel; // to force deletion of m_search before document. Otherwise crashes can come up (linux)
	delete codeeditor; //explicit call destructor of codeeditor (although it has a parent, it is no qobject itself, but passed it to editor)
	containedLabels->numberOfViews--;
	if(!containedLabels->numberOfViews){
		delete containedLabels;
		delete containedReferences;
	}
        SynChecker.stop();
        SynChecker.wait();
}

void LatexEditorView::viewActivated(){
	if (!LatexEditorView::completer) return;
	LatexEditorView::completer->setLabelDatabase(containedLabels);
}


void LatexEditorView::complete(bool forceVisibleList, bool normalText, bool forceRef) {
	if (!LatexEditorView::completer) return;
	REQUIRE(containedLabels);
	setFocus();
	LatexEditorView::completer->setLabelDatabase(containedLabels);
	LatexEditorView::completer->complete(editor,forceVisibleList,normalText,forceRef);
}
void LatexEditorView::jumpChangePositionBackward() {
	if (changePositions.size()==0) return;
	for (int i=changePositions.size()-1; i>=0; i--)
		if (!QDocumentLine(changePositions[i].first).isValid() || QDocumentLine(changePositions[i].first).lineNumber()<0) {
			changePositions.removeAt(i);
			if (i<=curChangePos) curChangePos--;
		}
	if (curChangePos >= changePositions.size()-1) curChangePos = changePositions.size()-1;
	else if (curChangePos>=0 && curChangePos < changePositions.size()-1) curChangePos++;
	else if (editor->cursor().line().handle()==changePositions.first().first) curChangePos=1;
	else curChangePos=0;
	if (curChangePos>=0 && curChangePos < changePositions.size())
		editor->setCursorPosition(QDocumentLine(changePositions[curChangePos].first).lineNumber(),changePositions[curChangePos].second);
}
void LatexEditorView::jumpChangePositionForward() {
	for (int i=changePositions.size()-1; i>=0; i--)
		if (!QDocumentLine(changePositions[i].first).isValid() || QDocumentLine(changePositions[i].first).lineNumber()<0) {
			changePositions.removeAt(i);
			if (i<=curChangePos) curChangePos--;
		}
	if (curChangePos>0) {
		curChangePos--;
		editor->setCursorPosition(QDocumentLine(changePositions[curChangePos].first).lineNumber(),changePositions[curChangePos].second);
	}
}
void LatexEditorView::jumpToBookmark(int bookmarkNumber) {
	int markLine=editor->document()->findNextMark(bookMarkId(bookmarkNumber),editor->cursor().line().lineNumber(),editor->cursor().line().lineNumber()-1);
	if (markLine>=0) {
		editor->setCursorPosition(markLine,0);
		editor->setFocus();
	}
}
void LatexEditorView::toggleBookmark(int bookmarkNumber) {
	int rmid=bookMarkId(bookmarkNumber);
	if (editor->cursor().line().hasMark(rmid)) {
		editor->cursor().line().removeMark(rmid);
		return;
	}
	if (bookmarkNumber>=0) editor->document()->line(editor->document()->findNextMark(rmid)).removeMark(rmid);
	for (int i=-1; i<10; i++) editor->cursor().line().removeMark(bookMarkId(i));
	editor->cursor().line().addMark(rmid);
	editor->ensureCursorVisible();
	if (bookmarkNumber>=1 && bookmarkNumber<=3) lastSetBookmark=bookmarkNumber;
}

bool LatexEditorView::gotoToLabel(const QString& label){
	QList<QDocumentLineHandle*> lst=containedLabels->values(label);
	if (lst.empty()) return false;
	QDocumentLine line(lst[0]);
	int ln=line.lineNumber();
	if (ln<0) return false;
	editor->setCursorPosition(ln, line.text().indexOf("\\label{"+label) + 7);
	editor->ensureCursorVisible();
	return true;
}

//collapse/expand every possible line
void LatexEditorView::foldEverything(bool unFold) {
	QDocument* doc = editor->document();
	QLanguageDefinition* ld = doc->languageDefinition();
	if (unFold) {
		for (int i=0; i<doc->lines(); i++) ld->expand(doc,i);
	} else {
		for (int i=0; i<doc->lines(); i++) ld->collapse(doc,i);
	}
}
//collapse/expand lines at the top level
void LatexEditorView::foldLevel(bool unFold, int level) {	
	QDocument* doc = editor->document();
	QLanguageDefinition* ld = doc->languageDefinition();
	for (QFoldedLineIterator fli = ld->foldedLineIterator(doc);
	fli.line.isValid(); ++fli){
		if (fli.openParentheses.size()==level && fli.open) {
			if (unFold) ld->expand(doc, fli.lineNr);
			else ld->collapse(doc, fli.lineNr);
		}
	}/*
	QDocument* doc = editor->document();
	QLanguageDefinition* ld = doc->languageDefinition();
	int depth=0;
	for (int n = 0; n < doc->lines(); ++n) {
		QDocumentLine b=doc->line(n);
		if (b.isHidden()) continue;

		int flags = ld->blockFlags(doc, n, depth);
		short open = QCE_FOLD_OPEN_COUNT(flags);
		short close = QCE_FOLD_CLOSE_COUNT(flags);

		depth -= close;

		if (depth < 0)
			depth = 0;

		depth += open;

		if (depth==level) {
			if (unFold && (flags & QLanguageDefinition::Collapsed))
				ld->expand(doc,n);
			else if (!unFold && (flags & QLanguageDefinition::Collapsible))
				ld->collapse(doc,n);
		}
		if (ld->blockFlags(doc, n, depth) & QLanguageDefinition::Collapsed)
			depth -= open; // outermost block folded : none of the opening is actually opened
	}*/
}
//Collapse at the first possible point before/at line
void LatexEditorView::foldBlockAt(bool unFold, int line) {
	editor->document()->foldBlockAt(unFold,line);
}



void LatexEditorView::cleanBib() {
	QDocument* doc = editor->document();
	for (int i=doc->lines()-1; i>=0; i--) {
		QString trimLine=doc->line(i).text().trimmed();
		if (trimLine.startsWith("OPT") || trimLine.startsWith("ALT"))
			doc->execute(new QDocumentEraseCommand(i,0,i+1,0,doc));
	}
	setFocus();
}



void LatexEditorView::setKeyReplacements(QStringList *UserKeyReplace, QStringList *UserKeyReplaceAfterWord, QStringList *UserKeyReplaceBeforeWord) {
	if (!defaultInputBinding) return;
	defaultInputBinding->keyToReplace=UserKeyReplace;
	defaultInputBinding->keyReplaceAfterWord=UserKeyReplaceAfterWord;
	defaultInputBinding->keyReplaceBeforeWord=UserKeyReplaceBeforeWord;
}
 QList<QAction *> LatexEditorView::getBaseActions(){
	if (!defaultInputBinding) return QList<QAction *>();
	return defaultInputBinding->baseActions;
}
void LatexEditorView::setBaseActions(QList<QAction *> baseActions) {
	if (!defaultInputBinding) return;
	defaultInputBinding->baseActions=baseActions;
}
void LatexEditorView::setSpeller(SpellerUtility* speller) {
	LatexEditorView::speller=speller;
}
void LatexEditorView::setCompleter(LatexCompleter* newCompleter) {
	LatexEditorView::completer=newCompleter;
}
LatexCompleter* LatexEditorView::getCompleter(){
	return LatexEditorView::completer;
}

void LatexEditorView::setBibTeXIds(QSet<QString>* newIds){
	bibTeXIds=newIds;

	Q_ASSERT(bibTeXIds);
	for (int i=0; i<editor->document()->lines(); i++) {
		QList<QFormatRange> li=editor->document()->line(i).getOverlays();
		QString curLineText=editor->document()->line(i).text();
		for (int j=0; j<li.size(); j++)
			if (li[j].format == citationPresentFormat || li[j].format == citationMissingFormat){
				int newFormat=bibTeXIds->contains(curLineText.mid(li[j].offset,li[j].length))?citationPresentFormat:citationMissingFormat;
				if (newFormat!=li[j].format) {
					editor->document()->line(i).removeOverlay(li[j]);
					li[j].format=newFormat;
					editor->document()->line(i).addOverlay(li[j]);
				}
			}
	}
}
int LatexEditorView::bookMarkId(int bookmarkNumber) {
	if (bookmarkNumber==-1) return  QLineMarksInfoCenter::instance()->markTypeId("bookmark"); //unnumbered mark
	else return QLineMarksInfoCenter::instance()->markTypeId("bookmark"+QString::number(bookmarkNumber));
}

void LatexEditorView::setLineMarkToolTip(const QString& tooltip){
	lineMarkPanel->setToolTipForTouchedMark(tooltip);
}
void LatexEditorView::updateSettings(){
	lineNumberPanel->setVerboseMode(config->showlinemultiples!=10);
	editor->setFont(QFont(config->fontFamily, config->fontSize));
	editor->setLineWrapping(config->wordwrap);
	editor->setHardLineWrapping(config->hardwordwrap);
	if(config->hardwordwrap){
	    int lw=config->lineWidth<20?20:config->lineWidth;
	    int w=QFontMetrics(QFont(config->fontFamily, config->fontSize)).averageCharWidth()*lw;
	    editor->setWrapLineWidth(w);
	}else{
	    editor->setWrapLineWidth(0);
	}
	editor->setFlag(QEditor::AutoIndent,config->autoindent);
	editor->setFlag(QEditor::WeakIndent,config->weakindent);
	editor->setFlag(QEditor::ReplaceTabs,config->indentWithSpaces);
	//TODO: parenmatch
	editor->setFlag(QEditor::AutoCloseChars, config->parenComplete);;
	lineMarkPanelAction->setChecked((config->showlinemultiples!=0) ||config->folding||config->showlinestate);
	lineNumberPanelAction->setChecked(config->showlinemultiples!=0);
	lineFoldPanelAction->setChecked(config->folding);
	lineChangePanelAction->setChecked(config->showlinestate);
	statusPanelAction->setChecked(config->showcursorstate);
	editor->setDisplayModifyTime(config->displayModifyTime);
	editor->setUseLineForSearch(config->useLineForSearch);
	QDocument::setShowSpaces(config->showWhitespace?(QDocument::ShowTrailing | QDocument::ShowLeading | QDocument::ShowTabs):QDocument::ShowNone);
	QDocument::setTabStop(config->tabStop);

	environmentFormat=QDocument::formatFactory()->id("environment");
	referenceMultipleFormat=QDocument::formatFactory()->id("referenceMultiple");
	referencePresentFormat=QDocument::formatFactory()->id("referencePresent");
	referenceMissingFormat=QDocument::formatFactory()->id("referenceMissing");
	citationPresentFormat=QDocument::formatFactory()->id("citationPresent");
	citationMissingFormat=QDocument::formatFactory()->id("citationMissing");
	styleHintFormat=QDocument::formatFactory()->id("styleHint");
	syntaxErrorFormat=QDocument::formatFactory()->id("latexSyntaxMistake");
	SynChecker.setErrFormat(syntaxErrorFormat);
	structureFormat=QDocument::formatFactory()->id("structure");
	verbatimFormat=QDocument::formatFactory()->id("verbatim");
	containedLabels->setFormats(referenceMultipleFormat,referencePresentFormat,referenceMissingFormat);
	containedReferences->setFormats(referenceMultipleFormat,referencePresentFormat,referenceMissingFormat);

	QDocument::setWorkAround(QDocument::DisableFixedPitchMode, config->hackDisableFixedPitch);
	QDocument::setWorkAround(QDocument::DisableWidthCache, config->hackDisableWidthCache);
}

void LatexEditorView::requestCitation(){
	QString id = editor->cursor().selectedText();
	emit needCitation(id);
}

void LatexEditorView::openExternalFile(){
	QAction *act = qobject_cast<QAction*>(sender());
	QString name=act->data().toString();
	if(!name.isEmpty())
		emit openFile(name);
}

void LatexEditorView::lineMarkClicked(int line) {
	QDocumentLine l=editor->document()->line(line);
	if (!l.isValid()) return;
	//remove old mark (when possible)
	for (int i=-1; i<10; i++)
		if (l.hasMark(bookMarkId(i))) {
			l.removeMark(bookMarkId(i));
			return;
		}
	// remove error marks
	if (l.hasMark(QLineMarksInfoCenter::instance()->markTypeId("error"))) {
		l.removeMark(QLineMarksInfoCenter::instance()->markTypeId("error"));
		return;
	}
	if (l.hasMark(QLineMarksInfoCenter::instance()->markTypeId("warning"))) {
		l.removeMark(QLineMarksInfoCenter::instance()->markTypeId("warning"));
		return;
	}
	if (l.hasMark(QLineMarksInfoCenter::instance()->markTypeId("badbox"))) {
		l.removeMark(QLineMarksInfoCenter::instance()->markTypeId("badbox"));
		return;
	}
	//add unused mark (1..3) (when possible)
	for (int i=1; i<=3; i++)
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
void LatexEditorView::lineMarkToolTip(int line, int mark){
	if (line < 0 || line>=editor->document()->lines()) return;
	int errorMarkID = QLineMarksInfoCenter::instance()->markTypeId("error");
	int warningMarkID = QLineMarksInfoCenter::instance()->markTypeId("warning");
	int badboxMarkID = QLineMarksInfoCenter::instance()->markTypeId("badbox");
	if (mark != errorMarkID && mark != warningMarkID && mark != badboxMarkID) return;
	int error = lineToLogEntries.value(editor->document()->line(line).handle(),-1);
	if (error>=0)
		emit showMarkTooltipForLogMessage(error);
}

void LatexEditorView::documentFormatsChanged(int linenr, int count) {
    if(config->realtimeChecking && config->inlineSyntaxChecking){
	reCheckSyntax(linenr,count);
    }
}

void LatexEditorView::documentContentChanged(int linenr, int count) {
	QDocumentLine startline=editor->document()->line(linenr);
	if ((linenr>=0 || count<editor->document()->lines()) && editor->cursor().isValid() &&
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
			if (changePositions.first().first!=startline.handle()) add=true;
			else changePositions.first().second=editor->cursor().columnNumber();
		} else if (curChangePos>=changePositions.size()-1) {
			if (changePositions.last().first!=startline.handle()) add=true;
			else changePositions.last().second=editor->cursor().columnNumber();
		}  else if (changePositions[curChangePos].first==startline.handle()) changePositions[curChangePos].second=editor->cursor().columnNumber();
		else if (changePositions[curChangePos+1].first==startline.handle()) changePositions[curChangePos+1].second=editor->cursor().columnNumber();
		else add=true;
		if (add) {
			curChangePos=-1;
			changePositions.insert(0,QPair<QDocumentLineHandle*,int>(startline.handle(),editor->cursor().columnNumber()));
			if (changePositions.size()>20) changePositions.removeLast();
		}
	}

	// checking
	if (!QDocument::formatFactory()) return;
	if (!config->realtimeChecking) return; //disable all => implicit disable environment color correction (optimization)
	if (editor && editor->languageDefinition() && editor->languageDefinition()->language()!="(La-)TeX") return; // no online checking in other files than tex

	for (int i=linenr; i<linenr+count; i++) {
		QDocumentLine line = editor->document()->line(i);
		if (!line.isValid()) continue;

		QDocumentLineHandle* dlh = line.handle();
		// remove all labels/references of current line
		containedLabels->removeUpdateByHandle(dlh,containedReferences);
		containedReferences->removeUpdateByHandle(dlh,0);

		//remove all overlays used for latex things, in descending frequency
		line.clearOverlays(speller->spellcheckErrorFormat);
		line.clearOverlays(referencePresentFormat);
		line.clearOverlays(citationPresentFormat);
		line.clearOverlays(referenceMissingFormat);
		line.clearOverlays(referenceMultipleFormat);
		line.clearOverlays(citationMissingFormat);
		line.clearOverlays(environmentFormat);
		line.clearOverlays(syntaxErrorFormat);
		line.clearOverlays(styleHintFormat);

		// start syntax checking
		if(config->inlineSyntaxChecking) {
		    SyntaxCheck::Environment env=SyntaxCheck::ENV_normal;
		    QDocumentLine prev=line.previous();
		    if(prev.isValid()){
			QNFA* cxt=line.previous().matchContext()->context;
			QString cxtDef=QNFADefinition::getContextName(cxt);
			if(!cxtDef.isEmpty()){
			    int sep=cxtDef.indexOf(":");
			    cxtDef=cxtDef.mid(sep+1);
			    if(cxtDef.startsWith("math")) env=SyntaxCheck::ENV_math;
			    if(cxtDef.startsWith("tabular")) env=SyntaxCheck::ENV_tabular;
			    if(cxtDef.startsWith("mathmodeEqnArray")) env=SyntaxCheck::ENV_matrix;
			    if(cxtDef.startsWith("mathmodeMatrix")) env=SyntaxCheck::ENV_matrix;
			}
		    }
		    QString text=line.text();
		    if(!text.isEmpty()){
			QVector<int>fmts=line.getFormats();
			for(int i=0;i<text.length() && i < fmts.size();i++){
			    if(fmts[i]==verbatimFormat){
				text[i]=QChar(' ');
			    }
			}
			SynChecker.putLine(text,line.handle(),env);
		    }
		}


		if (line.length()<=3) continue;
		//if (!config->realtimespellchecking) continue;

		QString lineText = line.text();

		QString word;
		int start=0;
		int wordstart;
		int status;
		bool inStructure=false;
		QString previousTextWord;
		int previousTextWordIndex=-1;
		while ((status=nextWord(lineText,start,word,wordstart,false,true,&inStructure))){
			// hack to color the environment given in \begin{environment}...
			if (inStructure){
				if(line.getFormatAt(wordstart)==verbatimFormat) continue;
                                QString secName=extractSectionName(lineText.mid(wordstart),true);
                                line.addOverlay(QFormatRange(wordstart,secName.length(),structureFormat));
                                inStructure=false;
			}
			if (status==NW_ENVIRONMENT) {
				if(line.getFormatAt(wordstart)==verbatimFormat) continue;
				line.addOverlay(QFormatRange(wordstart,start-wordstart,environmentFormat));
				QRegExp rx("[ ]*(\\[.*\\])*\\{.+\\}");
				rx.setMinimal(true);
				int l=rx.indexIn(lineText,start);
				if (l==start+1) start=start+rx.cap(0).length();
			}
			if (status==NW_REFERENCE && config->inlineReferenceChecking) {
				if(line.getFormatAt(wordstart)==verbatimFormat) continue;
				QString ref=word;//lineText.mid(wordstart,start-wordstart);
				containedReferences->insert(ref,dlh);
				int cnt=containedLabels->count(ref);
				if(cnt>1) {
					line.addOverlay(QFormatRange(wordstart,start-wordstart,referenceMultipleFormat));
				}else if (cnt==1) line.addOverlay(QFormatRange(wordstart,start-wordstart,referencePresentFormat));
				else line.addOverlay(QFormatRange(wordstart,start-wordstart,referenceMissingFormat));
			}
			if (status==NW_LABEL && config->inlineReferenceChecking) {
				if(line.getFormatAt(wordstart)==verbatimFormat) continue;
				QString ref=word;//lineText.mid(wordstart,start-wordstart);
				containedLabels->insert(ref,dlh);
				int cnt=containedLabels->count(ref);
				if(cnt>1) {
					line.addOverlay(QFormatRange(wordstart,start-wordstart,referenceMultipleFormat));
				}else line.addOverlay(QFormatRange(wordstart,start-wordstart,referencePresentFormat));
				// look for corresponding reeferences and adapt format respectively
				containedLabels->updateByKeys(QStringList(ref),containedReferences);
			}
			if (status==NW_CITATION && config->inlineCitationChecking) {
				if (bibTeXIds) {
					QStringList citations=word.split(",");
					int pos=wordstart;
					foreach ( const QString &cit, citations) {
						QString rcit =  cit;
						//trim left (left spaces are ignored by \cite, right space not)
						for (int j=0; j<cit.length();j++)
							if (cit[j]!=' '){
							if (j!=0) rcit=cit.mid(j);
							break;
						}
						//check and highlight
						if (bibTeXIds->contains(rcit))
							line.addOverlay(QFormatRange(pos+cit.length()-rcit.length(),rcit.length(),citationPresentFormat));
						else
							line.addOverlay(QFormatRange(pos+cit.length()-rcit.length(),rcit.length(),citationMissingFormat));
						pos+=cit.length()+1;
					}
				}
			}
			if (status==NW_COMMENT) break;
			if (status==NW_TEXT && config->inlineSpellChecking){
				if(!previousTextWord.isEmpty() && previousTextWord==word){
					if(!lineText.mid(previousTextWordIndex,wordstart-previousTextWordIndex).contains(QRegExp("\\S")))
						line.addOverlay(QFormatRange(wordstart,start-wordstart,styleHintFormat));
				}
				if(!word.isEmpty() && !word.at(0).isNumber()){
					previousTextWord=word;
					previousTextWordIndex=start;
				} else previousTextWord.clear();
			} else previousTextWord.clear();
			if (status==NW_TEXT && word.length()>=3 && !speller->check(word) && config->inlineSpellChecking) {
				if(word.endsWith('.')) start--;
				line.addOverlay(QFormatRange(wordstart,start-wordstart,speller->spellcheckErrorFormat));
			}
		}// while
	}
	editor->document()->markViewDirty();
}

void LatexEditorView::lineRemoved(QDocumentLineHandle* l) {
	// delete References
	containedReferences->removeByHandle(l);
	// delete Labels and update referenced refs
	containedLabels->removeUpdateByHandle(l,containedReferences);
}

void LatexEditorView::lineDeleted(QDocumentLineHandle* l) {
	lineRemoved(l);

	QHash<QDocumentLineHandle*, int>::iterator it;
	while ((it=lineToLogEntries.find(l))!=lineToLogEntries.end()) {
		logEntryToLine.remove(it.value());
		lineToLogEntries.erase(it);
	}

	QPair<int, int> p;
	//QMessageBox::information(0,QString::number(nr),"",0);
	for (int i=changePositions.size()-1; i>=0; i--)
		if (changePositions[i].first==l)
			/*if (QDocumentLine(changePositions[i].first).previous().isValid()) changePositions[i].first=QDocumentLine(changePositions[i].first).previous().handle();
			else if (QDocumentLine(changePositions[i].first).next().isValid()) changePositions[i].first=QDocumentLine(changePositions[i].first).next().handle();
			else  */ //creating a QDocumentLine with a deleted handle is not possible (it will modify the handle reference count which will trigger another delete event, leading to an endless loop)
			changePositions.removeAt(i);
			//    QMessageBox::information(0,"trig",0);

	emit lineHandleDeleted(l);
	editor->document()->markViewDirty();
}
void LatexEditorView::spellCheckingReplace() {
	QAction* action = qobject_cast<QAction*>(QObject::sender());
	if (editor && action) {
		editor->insertText(action->text());
		editor->setCursor(editor->cursor()); //to remove selection range
	}
}
void LatexEditorView::spellCheckingAlwaysIgnore() {
	if (speller && editor && editor->cursor().hasSelection() && (editor->cursor().selectedText()==defaultInputBinding->lastSpellCheckedWord)) {
		QString newToIgnore = editor->cursor().selectedText();
		speller->addToIgnoreList(newToIgnore);
		//documentContentChanged(editor->cursor().lineNumber(),1);
		for (int i=0; i<editor->document()->lines(); i++) {
			QList<QFormatRange> li=editor->document()->line(i).getOverlays(LatexEditorView::speller->spellcheckErrorFormat);
			QString curLineText=editor->document()->line(i).text();
			for (int j=0; j<li.size(); j++)
				if (curLineText.mid(li[j].offset,li[j].length)==newToIgnore){
					editor->document()->line(i).removeOverlay(li[j]);
					editor->document()->line(i).setFlag(QDocumentLine::LayoutDirty,true);
				}
		}
		editor->viewport()->update();
	}
}
void LatexEditorView::spellCheckingListSuggestions() {
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
		QFont correctionFont;
		correctionFont.setBold(true);
		for (int i=0; i<suggestions.size(); i++) {
			QAction* aReplacement=new QAction(suggestions[i],contextMenu);
			aReplacement->setFont(correctionFont);
			connect(aReplacement,SIGNAL(triggered()),this,SLOT(spellCheckingReplace()));
			contextMenu->insertAction(before,aReplacement);
		}
	}
	if (repopup) {
		//    contextMenu->close();
		contextMenu->show();
	}
}
void LatexEditorView::dictionaryReloaded() {
	//   QMessageBox::information(0,"trig","",0);
	documentContentChanged(0,editor->document()->lines());
}

void LatexEditorView::setReferenceDatabase(References *Ref,References *Label){
	containedLabels->appendTo(Label);
	containedReferences->appendTo(Ref);
	delete containedLabels;
	delete containedReferences;
	containedLabels=Label;
	containedReferences=Ref;
	containedLabels->numberOfViews++;
	containedReferences->numberOfViews++;
	if(completer){
		completer->setLabelDatabase(Label);
	}
}
void LatexEditorView::getReferenceDatabase(References *&Ref,References *&Label){
	Label=containedLabels;
	Ref=containedReferences;
}
void LatexEditorView::resetReferenceDatabase(){
	containedLabels=new References("(\\\\label)\\{(.+)\\}");
	containedReferences=new References("(\\\\ref|\\\\pageref)\\{(.+)\\}");
	environmentFormat=QDocument::formatFactory()->id("environment");
	referenceMultipleFormat=QDocument::formatFactory()->id("referenceMultiple");
	referencePresentFormat=QDocument::formatFactory()->id("referencePresent");
	referenceMissingFormat=QDocument::formatFactory()->id("referenceMissing");
	citationPresentFormat=QDocument::formatFactory()->id("citationPresent");
	citationMissingFormat=QDocument::formatFactory()->id("citationMissing");
	structureFormat=QDocument::formatFactory()->id("structure");
        verbatimFormat=QDocument::formatFactory()->id("verbatim");
	containedLabels->setFormats(referenceMultipleFormat,referencePresentFormat,referenceMissingFormat);
	containedReferences->setFormats(referenceMultipleFormat,referencePresentFormat,referenceMissingFormat);

	documentContentChanged(0,editor->document()->lines());
}

void LatexEditorView::purgeLinksTo(QDocument *doc){
	containedLabels->purgeLinksTo(doc);
	containedReferences->purgeLinksTo(doc);
}

void LatexEditorView::reCheckSyntax(int linenr, int count){
    // expensive function ... however if \newcommand is changed valid commands become invalid and vice versa
    if(!config->inlineSyntaxChecking || !config->realtimeChecking) return;
    if(linenr<0&&linenr>=editor->document()->lineCount()) linenr=0;
    QDocumentLine line=editor->document()->line(linenr);
    QDocumentLine prev=line.previous();
    for (int i=linenr; i<editor->document()->lineCount()&&(i<count+linenr || count<0); i++) {
	SyntaxCheck::Environment env=SyntaxCheck::ENV_normal;
	if(prev.isValid()){
	    QNFA* cxt=prev.matchContext()->context;
	    QString cxtDef=QNFADefinition::getContextName(cxt);
	    if(!cxtDef.isEmpty()){
		int sep=cxtDef.indexOf(":");
		cxtDef=cxtDef.mid(sep+1);
		if(cxtDef.startsWith("math")) env=SyntaxCheck::ENV_math;
		if(cxtDef.startsWith("tabular")) env=SyntaxCheck::ENV_tabular;
		if(cxtDef.startsWith("mathmodeEqnArray")) env=SyntaxCheck::ENV_matrix;
		if(cxtDef.startsWith("mathmodeMatrix")) env=SyntaxCheck::ENV_matrix;
	    }
	}
	QString text=line.text();
	if(!text.isEmpty()){
	    QVector<int>fmts=line.getFormats();
	    for(int i=0;i<text.length() && i < fmts.size();i++){
		if(fmts[i]==verbatimFormat){
		    text[i]=QChar(' ');
		}
	    }
	    SynChecker.putLine(text,line.handle(),env,true);
	}
	prev=line;
	if(line.isValid()) //double check against crash
	    line++;
	else
	    break;
    }
}

void LatexEditorView::mouseHovered(QPoint pos){
	// reimplement to what is necessary

	if(pos.x()<0) return;  // hover event on panel
	QDocumentCursor cursor;
	cursor=editor->cursorForPosition(editor->mapToContents(pos));
	QString line=cursor.line().text();
	QDocumentLine l=cursor.line();
	// check for latex error
	//syntax checking
	int f=QDocument::formatFactory()->id("latexSyntaxMistake");
	QFormatRange fr = cursor.line().getOverlayAt(cursor.columnNumber(),f);
	if (fr.length>0 && fr.format==f) {
	    SyntaxCheck::Environment env=SyntaxCheck::ENV_normal;
	    QDocumentLine prev=l.previous();
	    if(prev.isValid()){
		QNFA* cxt=l.previous().matchContext()->context;
		QString cxtDef=QNFADefinition::getContextName(cxt);
		if(!cxtDef.isEmpty()){
		    int sep=cxtDef.indexOf(":");
		    cxtDef=cxtDef.mid(sep+1);
		    if(cxtDef.startsWith("math")) env=SyntaxCheck::ENV_math;
		    if(cxtDef.startsWith("tabular")) env=SyntaxCheck::ENV_tabular;
		    if(cxtDef.startsWith("mathmodeEqnArray")) env=SyntaxCheck::ENV_matrix;
		    if(cxtDef.startsWith("mathmodeMatrix")) env=SyntaxCheck::ENV_matrix;
		}
	    }
	    QString text=l.text();
	    if(!text.isEmpty()){
		QVector<int>fmts=l.getFormats();
		for(int i=0;i<text.length() && i < fmts.size();i++){
		    if(fmts[i]==verbatimFormat){
			text[i]=QChar(' ');
		    }
		}
		QString message=SynChecker.getErrorAt(text,cursor.columnNumber(),env);
		QToolTip::showText(editor->mapToGlobal(editor->mapFromFrame(pos)),message);
		return;
	    }
	}
	// do rest
	QString command, value;
	QString topic;
	QStringList MathEnvirons;
	int i,first,last;
	int id_first;
	QVector<QParenthesis> parens;
	switch(LatexParser::findContext(line, cursor.columnNumber(), command, value)){
		case LatexParser::Unknown:
			if(cursor.nextChar()==QChar('$')){
				i=cursor.columnNumber();
				parens=l.parentheses();
				first=i;
				last=-1;
				for(i=0;i<parens.size();i++){
					if(parens[i].offset==first) {
						last=i;
						id_first=parens[i].id;
						break;
					}
				}
				if(last>-1){
					if(parens[i].role&1){
						last=-1;
						for(;i<parens.size();i++){
							if(parens[i].id==id_first && parens[i].role&2) {
								last=parens[i].offset;
								break;
							}
						}
						if(last>-1){
							command=line.mid(first,last-first);
							m_point=editor->mapToGlobal(editor->mapFromFrame(pos));
							emit showPreview(command);
						}
					}
				}
			} else {
				QToolTip::hideText();
			}
			break;
		case LatexParser::Command:
			if (command=="\\begin" || command=="\\end")
				command="\\begin{"+value+"}";

			MathEnvirons << "equation" << "math" << "displaymath" << "eqnarray" << "eqnarray*";
			if(MathEnvirons.contains(value)){
				if(command.startsWith("\\begin")){
					// find closing
					if(value=="eqnarray"||value=="eqnarray*")
						command="\\begin{eqnarray*}";
					else command="\\begin{displaymath}";

					int endingLine=editor->document()->findLineContaining(QString("\\end{%1}").arg(value),cursor.lineNumber(),Qt::CaseSensitive,false);
					QString text;
					text=command+"\n";
					for(int i=cursor.lineNumber()+1;i<endingLine;i++){
						text=text+editor->document()->line(i).text()+"\n";
					}

					if(value=="eqnarray"||value=="eqnarray*")
						text+="\\end{eqnarray*}";
					else text+="\\end{displaymath}";

					emit showPreview(text);
				}
			} else {
				topic=completer->lookupWord(command);
				if(!topic.isEmpty()) QToolTip::showText(editor->mapToGlobal(editor->mapFromFrame(pos)), topic);
			}
			break;
		case LatexParser::Environment:
			topic=completer->lookupWord("\\begin{"+value+"}");
			if(!topic.isEmpty()) QToolTip::showText(editor->mapToGlobal(editor->mapFromFrame(pos)), topic);
			break;
		case LatexParser::Reference:
			{
				//l=editor->document()->findLineContaining("\\label{"+ref+"}",0,Qt::CaseSensitive);
				QList<QDocumentLineHandle*> lst=containedLabels->values(value);
				QString mText="";
				if(lst.isEmpty()){
					mText=tr("label missing!");
				} else if(lst.count()>1) {
					mText=tr("label multiple times defined!");
				} else {
					QDocumentLineHandle *mLine=lst.first();
					int l=mLine->line();
					if(mLine->document()!=editor->document()){
						LatexDocument *doc=document->parent->findDocument(mLine->document());
						if(doc) mText=tr("<p style='white-space:pre'><b>Filename: %1</b>\n").arg(doc->getFileName());
					}
					for(int i=qMax(0,l-2);i<qMin(mLine->document()->lines(),l+3);i++){
						mText+=mLine->document()->line(i).text();
						if(i<l+2) mText+="\n";
					}
				}
				QToolTip::showText(editor->mapToGlobal(editor->mapFromFrame(pos)), mText);
				break;
			}
		case LatexParser::Label:
			if(containedLabels->count(value)>1){
				QToolTip::showText(editor->mapToGlobal(editor->mapFromFrame(pos)),tr("label multiple times defined!"));
			} else {
				int cnt=containedReferences->count(value);
				QToolTip::showText(editor->mapToGlobal(editor->mapFromFrame(pos)),tr("%n reference(s) to this label","",cnt));
			}
			break;
		case LatexParser::Citation:
			if (bibTeXIds)
				QToolTip::showText(editor->mapToGlobal(editor->mapFromFrame(pos)),
					bibTeXIds->contains(value)?tr("citation correct"):tr("citation missing!"));
			break;
		default:
			QToolTip::hideText();
	}
	//QToolTip::showText(editor->mapToGlobal(pos), line);
}
bool LatexEditorView::closeSomething(){
	if (completer->close()) return true;
	if (gotoLinePanel->isVisible()) {
		gotoLinePanel->hide();
		editor->setFocus();
		return true;
	}
	if (searchReplacePanel->isVisible()) {
		if (searchReplacePanel->isReplaceModeActive() & !config->closeSearchAndReplace)
			searchReplacePanel->display(1,false);
		else
			searchReplacePanel->display(0,false);
		return true;
	}
	return false;
}

void LatexEditorView::insertHardLineBreaks(int newLength, bool smartScopeSelection, bool joinLines){
	QRegExp breakChars("[ \t\n\r]");
	QDocumentCursor cur=editor->cursor();
	QDocument* doc=editor->document();
	int startLine=0; int endLine=doc->lines()-1;

	if (cur.isValid()) {
		if (cur.hasSelection()) {
			startLine=cur.selectionStart().lineNumber();
			endLine=cur.selectionEnd().lineNumber();
			if (cur.selectionEnd().columnNumber()==0 && startLine<endLine) endLine--;
		} else if (smartScopeSelection){
			QDocumentCursor currentCur=cur;
			QDocumentCursor lineCursor=currentCur;
			do {
				QString lineString  = lineCursor.line().text().trimmed();
				if ((lineString == QLatin1String("")) ||
				    (lineString.contains("\\begin")) ||
				    (lineString.contains("\\end")) ||
				    (lineString.contains("$$")) ||
				    (lineString.contains("\\[")) ||
				    (lineString.contains("\\]"))) {
					qDebug() << lineString;
					break;
				}
			} while (lineCursor.movePosition(1, QDocumentCursor::Up, QDocumentCursor::MoveAnchor));
			startLine = lineCursor.lineNumber();
			if (lineCursor.atStart()) startLine--;

			lineCursor = currentCur;
			do {
				QString lineString  = lineCursor.line().text().trimmed();
				if ((lineString == QLatin1String("")) ||
				    (lineString.contains("\\begin")) ||
				    (lineString.contains("\\end")) ||
				    (lineString.contains("$$")) ||
				    (lineString.contains("\\[")) ||
				    (lineString.contains("\\]"))) {
					qDebug() << lineString;
					break;
				}
			} while (lineCursor.movePosition(1, QDocumentCursor::Down, QDocumentCursor::MoveAnchor));
			endLine = lineCursor.lineNumber();
			if (lineCursor.atEnd()) endLine++	;

			if ((endLine - startLine) < 2) { // lines near, therefore no need to line break
				return ;
			}

			startLine++;
			endLine--;
		}
	}
	if (joinLines) { // start of smart formatting, similar to what emacs (AucTeX) can do, but much simple
		QStringList lines;  QString tmpLine;
		for (int i=startLine; i <= endLine; i++)  {
			QString fullString  = doc->line(i).text();
			int commentStart    = LatexParser::commentStart(fullString);
			if (commentStart==-1) {
				tmpLine.append(" ");
				tmpLine.append(fullString);
			} else {
				lines << tmpLine;
				lines << fullString;
				tmpLine.clear();
			}
		}
		lines.append(tmpLine);
		lines[0].remove(0,1); // remove needless space character from first line

		QStringList formattedList;
		for (int i=0; i < lines.size(); i++) {
			QString bigString = lines.at(i);
			while (bigString.size() > newLength) {
				int breakAt=bigString.lastIndexOf(breakChars,newLength);
				formattedList << bigString.left(breakAt);
				if (breakAt >= 0) {
					bigString.remove(0, breakAt+1);
				} else {
					bigString.clear();
					break;
				}
			}
			if (bigString.size() > 0)  formattedList << bigString;
		}

		QDocumentCursor vCur = doc->cursor(startLine, 0, endLine, doc->line(endLine).length());
		editor->insertText(vCur,formattedList.join("\n"));

		editor->setCursor(cur);

		return ;
	}

	bool areThereLinesToBreak=false;
	for (int i=startLine;i<=endLine;i++)
		if (doc->line(i).length()>newLength) {
			areThereLinesToBreak=true;
			break;
		}
	if (!areThereLinesToBreak) return;
	//remove all lines and reinsert them wrapped
	if (endLine+1<doc->lines())
		cur = doc->cursor(startLine,0,endLine+1,0);//+1,0);
	else
		cur = doc->cursor(startLine,0,endLine,doc->line(endLine).length());//+1,0);
	QStringList lines;
	for (int i=startLine;i<=endLine;i++)
		lines<<doc->line(i).text();
	QString insertBlock;
	for (int i=0;i<lines.count();i++){
		QString line=lines[i];
		int commentStart=LatexParser::commentStart(line);
		if (commentStart==-1) commentStart=line.length();
		while (line.length()>newLength) {
			int breakAt=line.lastIndexOf(breakChars,newLength);
			if (breakAt<0) breakAt=line.indexOf(breakChars,newLength);
			if (breakAt<0) break;
			if (breakAt>=commentStart && breakAt+1 > newLength) {
				int newBreakAt=line.indexOf(breakChars,breakAt-1);
				if (newBreakAt >-1) breakAt=newBreakAt;
			}
			insertBlock+=line.left(breakAt)+"\n";
			if (breakAt<commentStart) {
				line=line.mid(breakAt+1);
				commentStart-=breakAt+1;
			} else {
				line="%"+line.mid(breakAt+1);
				commentStart=0;
			}
		}
		insertBlock+=line+"\n";
	}
	editor->insertText(cur,insertBlock);

	editor->setCursor(cur);
}

QStringList References::removeByHandle(QDocumentLineHandle* handle){
	QStringList result;
	QMultiHash<QString, QDocumentLineHandle*>::iterator mIt = mReferences.begin();
	while (mIt != mReferences.end()) {
		if (mIt.value() == handle){
			result << mIt.key();
			mIt = mReferences.erase(mIt);
		} else
			++mIt;
	}
	return result;
}

void References::removeUpdateByHandle(QDocumentLineHandle* handle,References* altRefs){
	QStringList refs=removeByHandle(handle);
	if(altRefs) updateByKeys(refs,altRefs);
}

void References::updateByKeys(const QStringList& refs,References* altRefs){
	QRegExp rxRef(altRefs?altRefs->pattern():"");
	QRegExp rxLabel(pattern());
	rxLabel.setMinimal(true);
	rxRef.setMinimal(true);
	foreach(const QString &ref,refs){
		QList<QDocumentLineHandle*> lst;
		if(altRefs) {
			lst=altRefs->values(ref);
			foreach(QDocumentLineHandle* elem,lst){
				QDocumentLine mLine(elem);
				QString text=mLine.text();
				text=LatexParser::cutComment(text);
				int offset=0;
				while(rxRef.indexIn(text)!=-1){
					int cnt=count(ref);
					mLine.removeOverlay(QFormatRange(rxRef.pos(2)+offset,rxRef.cap(2).length(),referenceMultipleFormat));
					mLine.removeOverlay(QFormatRange(rxRef.pos(2)+offset,rxRef.cap(2).length(),referencePresentFormat));
					mLine.removeOverlay(QFormatRange(rxRef.pos(2)+offset,rxRef.cap(2).length(),referenceMissingFormat));
					if (cnt>1) {
						mLine.addOverlay(QFormatRange(rxRef.pos(2)+offset,rxRef.cap(2).length(),referenceMultipleFormat));
					} else if (cnt==1) mLine.addOverlay(QFormatRange(rxRef.pos(2)+offset,rxRef.cap(2).length(),referencePresentFormat));
					else mLine.addOverlay(QFormatRange(rxRef.pos(2)+offset,rxRef.cap(2).length(),referenceMissingFormat));

					text=text.mid(rxRef.pos(0)+rxRef.cap(0).length());
					offset += rxRef.pos(0)+rxRef.cap(0).length();
				}
			}
		}
		lst=values(ref);
		foreach(QDocumentLineHandle* elem,lst){
			QDocumentLine mLine(elem);
			QString text=mLine.text();
			text=LatexParser::cutComment(text); // remove comments
			int offset=0;
			while(rxLabel.indexIn(text)!=-1){
				int cnt=count(ref);
				mLine.removeOverlay(QFormatRange(rxLabel.pos(2)+offset,rxLabel.cap(2).length(),referenceMultipleFormat));
				mLine.removeOverlay(QFormatRange(rxLabel.pos(2)+offset,rxLabel.cap(2).length(),referenceMissingFormat));
				mLine.removeOverlay(QFormatRange(rxLabel.pos(2)+offset,rxLabel.cap(2).length(),referencePresentFormat));
				if(cnt>1) {
					mLine.addOverlay(QFormatRange(rxLabel.pos(2)+offset,rxLabel.cap(2).length(),referenceMultipleFormat));
				} else if (cnt==1) mLine.addOverlay(QFormatRange(rxLabel.pos(2)+offset,rxLabel.cap(2).length(),referencePresentFormat));
				else mLine.addOverlay(QFormatRange(rxLabel.pos(2)+offset,rxLabel.cap(2).length(),referenceMissingFormat));

				text=text.mid(rxLabel.pos(0)+rxLabel.cap(0).length());
				offset += rxLabel.pos(0)+rxLabel.cap(0).length();
			}
		}
	} //foreach
}

void References::appendTo(References *ref){
	if(!ref) return;
	QMultiHash<QString,QDocumentLineHandle*>::const_iterator i = mReferences.constBegin();
	 while (i != mReferences.constEnd()) {
		 ref->insert(i.key(),i.value());
		 ++i;
	 }
}

void References::purgeLinksTo(QDocument *doc){
	if(!doc) return;
	QMutableHashIterator<QString,QDocumentLineHandle*> i(mReferences);
	 while (i.hasNext()) {
		 i.next();
		 if(i.value()->document()==doc) i.remove();
	 }
}


QString LatexEditorViewConfig::translateEditOperation(int key){
	return QEditor::translateEditOperation((QEditor::EditOperation)key);
}

QList<int> LatexEditorViewConfig::possibleEditOperations(){
	int  temp[] = {
		QEditor::NoOperation,
		QEditor::Invalid,
		
		QEditor::CursorUp,
		QEditor::CursorDown,
		QEditor::CursorLeft,
		QEditor::CursorRight,
		QEditor::CursorWordLeft,
		QEditor::CursorWordRight,
		QEditor::CursorStartOfLine,
		QEditor::CursorEndOfLine,
		QEditor::CursorStartOfDocument,
		QEditor::CursorEndOfDocument,

		QEditor::CursorPageUp,
		QEditor::CursorPageDown,

		QEditor::SelectCursorUp,
		QEditor::SelectCursorDown,
		QEditor::SelectCursorLeft,
		QEditor::SelectCursorRight,
		QEditor::SelectCursorWordLeft,
		QEditor::SelectCursorWordRight,
		QEditor::SelectCursorStartOfLine,
		QEditor::SelectCursorEndOfLine,
		QEditor::SelectCursorStartOfDocument,
		QEditor::SelectCursorEndOfDocument,

		QEditor::SelectPageUp,
		QEditor::SelectPageDown,

		QEditor::EnumForCursorEnd,

		QEditor::DeleteLeft,
		QEditor::DeleteRight,
		QEditor::DeleteLeftWord,
		QEditor::DeleteRightWord,
		QEditor::NewLine,

		QEditor::ChangeOverwrite,
		QEditor::Undo,
		QEditor::Redo,
		QEditor::Copy,
		QEditor::Paste,
		QEditor::Cut,
		QEditor::Print,
		QEditor::SelectAll,
		QEditor::Find,
		QEditor::FindNext,
		QEditor::Replace,

		QEditor::CreateMirrorUp,
		QEditor::CreateMirrorDown,
		QEditor::NextPlaceHolder,
		QEditor::PreviousPlaceHolder,
		QEditor::NextPlaceHolderOrWord,
		QEditor::PreviousPlaceHolderOrWord,
		QEditor::IndentSelection,
		QEditor::UnindentSelection};
	QList<int> res;
	int operationCount = (int)(sizeof(temp)/sizeof(int)); //sizeof(array) is possible with c-arrays
	for (int i=0;i<operationCount;i++)
		res << temp[i];
	return res;
}
