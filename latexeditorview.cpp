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
#include "tablemanipulation.h"

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

#include "latexcompleter_config.h"

#include "scriptengine.h"
#include "diffoperations.h"

//------------------------------Default Input Binding--------------------------------
class DefaultInputBinding: public QEditorInputBinding {
	//  Q_OBJECT not possible because inputbinding is no qobject
public:
	DefaultInputBinding():completerConfig(0),contextMenu(0) {}
	virtual QString id() const {
		return "TXS::DefaultInputBinding";
	}
	virtual QString name() const {
		return "TXS::DefaultInputBinding";
	}

	virtual bool keyPressEvent(QKeyEvent *event, QEditor *editor);
	virtual bool contextMenuEvent(QContextMenuEvent *event, QEditor *editor);
private:
	friend class LatexEditorView;
	const LatexCompleterConfig* completerConfig;
	QList<QAction *> baseActions;

	QMenu* contextMenu;
	QString lastSpellCheckedWord;

};
bool DefaultInputBinding::keyPressEvent(QKeyEvent *event, QEditor *editor) {
	if (LatexEditorView::completer && LatexEditorView::completer->acceptTriggerString(event->text()) &&
	    (editor->currentPlaceHolder() < 0 || editor->currentPlaceHolder() >= editor->placeHolderCount() || editor->getPlaceHolder(editor->currentPlaceHolder()).mirrors.isEmpty() ||  editor->getPlaceHolder(editor->currentPlaceHolder()).affector != BracketInvertAffector::instance()))  {
		//update completer if necessary
		editor->emitNeedUpdatedCompleter();
		bool autoOverriden = editor->isAutoOverrideText(event->text());
		editor->insertText(event->text());
		if (autoOverriden) LatexEditorView::completer->complete(editor,LatexCompleter::CF_OVERRIDEN_BACKSLASH);
		else LatexEditorView::completer->complete(editor,0);
		return true;
	}
	if (!event->text().isEmpty()) {
		Q_ASSERT(completerConfig); 
		QString prev = editor->cursor().selectionStart().line().text().mid(0, editor->cursor().selectionStart().columnNumber())+event->text(); //TODO: optimize
		for (int i=0;i<completerConfig->userMacro.size();i++) {
			const Macro& m = completerConfig->userMacro[i];
			if (m.trigger.isEmpty()) continue;
			QRegExp& r = const_cast<QRegExp&>(m.triggerRegex);//a const qregexp doesn't exist
			if (r.indexIn(prev)!=-1){
				QDocumentCursor c = editor->cursor();
				bool block = false;
				int realMatchLen = r.matchedLength();
				if (m.triggerLookBehind) realMatchLen -= r.cap(1).length();
				if (c.hasSelection() || realMatchLen > 1)
					block = true;
				if (block) editor->document()->beginMacro();
				if (c.hasSelection()) c.removeSelectedText();
				if (completerConfig->userMacro[i].triggerRegex.matchedLength() > 1) {
					c.movePosition(realMatchLen-1, QDocumentCursor::Left, QDocumentCursor::KeepAnchor);
					c.removeSelectedText();
				}

				LatexEditorView* view = editor->property("latexEditor").value<LatexEditorView*>();
				Q_ASSERT(view);
				view->insertMacro(completerConfig->userMacro[i].tag);
				//editor->insertText(c, completerConfig->userMacro[i].tag);
				if (block) editor->document()->endMacro();
				editor->emitCursorPositionChanged(); //prevent rogue parenthesis highlightations
				/*			if (editor->languageDefinition())
								editor->languageDefinition()->clearMatches(editor->document());
*/
				return true;
			}
		}
		//		for (int i=0;i<LatexEditorView::completer)

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

		if (edView && edView->speller){
			if (cursor.hasSelection()) fr= cursor.line().getOverlayAt((cursor.columnNumber()+cursor.anchorColumnNumber()) / 2, SpellerUtility::spellcheckErrorFormat);
			else fr = cursor.line().getOverlayAt(cursor.columnNumber(), SpellerUtility::spellcheckErrorFormat);
			if (fr.length>0 && fr.format==SpellerUtility::spellcheckErrorFormat) {
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
		//package help
		if( (result==LatexParser::Command || result==LatexParser::Option) && command=="\\usepackage"){
			QAction* act=new QAction(LatexEditorView::tr("Open package documentation"),contextMenu);
			QString packageName;
			if (value.contains(',')) {
				// multiple packages included in one \usepackage command
				QStringList packages;
				foreach (QString pkg, value.split(',')) {
					packages.append(pkg.simplified());
				}
				QDocumentCursor wordCursor = cursor;
				wordCursor.select(QDocumentCursor::WordUnderCursor);
				if (packages.contains(wordCursor.selectedText())) {
					packageName = wordCursor.selectedText();
				} else {
					packageName = packages.first();
				}
			} else {
				packageName = value;
			}
			act->setText(act->text().append(QString(" (%1)").arg(packageName)));
			act->setData(packageName);
			edView->connect(act,SIGNAL(triggered()),edView,SLOT(openPackageDocumentation()));
			contextMenu->addAction(act);
		}

                //resolve differences
                if (edView){
                        QList<int> fids;
			fids<<edView->deleteFormat<<edView->insertFormat<<edView->replaceFormat;
                        foreach(int fid,fids){
                            if (cursor.hasSelection()) fr= cursor.line().getOverlayAt((cursor.columnNumber()+cursor.anchorColumnNumber()) / 2,fid);
                            else fr = cursor.line().getOverlayAt(cursor.columnNumber(),fid);
                            if (fr.length>0 ) {
                                QVariant var=cursor.line().getCookie(2);
                                if(var.isValid()){
                                    DiffList diffList=var.value<DiffList>();
				    //QString word=cursor.line().text().mid(fr.offset,fr.length);
				    DiffOp op;
				    op.start=-1;
				    foreach(op,diffList){
					if(op.start<=cursor.columnNumber() && op.start+op.length>=cursor.columnNumber()){
					    break;
					}
					op.start=-1;
				    }
				    if(op.start>=0){
					QAction* act=new QAction(LatexEditorView::tr("use yours"),contextMenu);
					act->setData(QPoint(cursor.lineNumber(),cursor.columnNumber()));
					edView->connect(act,SIGNAL(triggered()),edView,SLOT(emitChangeDiff()));
					contextMenu->addAction(act);
					act=new QAction(LatexEditorView::tr("use other's"),contextMenu);
					act->setData(QPoint(-cursor.lineNumber()-1,cursor.columnNumber()));
					edView->connect(act,SIGNAL(triggered()),edView,SLOT(emitChangeDiff()));
					contextMenu->addAction(act);
					break;
				    }
                                }
                            }
                        }
                }
		// add action to thesaurus
		QAction* act=new QAction(LatexEditorView::tr("Thesaurus..."),contextMenu);
		act->setData(QPoint(cursor.anchorLineNumber(),cursor.anchorColumnNumber()));
		edView->connect(act,SIGNAL(triggered()),edView,SLOT(triggeredThesaurus()));
		contextMenu->addAction(act);
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
LatexCompleter* LatexEditorView::completer=0;
int LatexEditorView::hideTooltipWhenLeavingLine = -1;

Q_DECLARE_METATYPE(LatexEditorView*);

LatexEditorView::LatexEditorView(QWidget *parent, LatexEditorViewConfig* aconfig,LatexDocument *doc) : QWidget(parent),speller(0),bibTeXIds(0),curChangePos(-1),lastSetBookmark(0),config(aconfig) {
	Q_ASSERT(config);
	QVBoxLayout* mainlay = new QVBoxLayout(this);
	mainlay->setSpacing(0);
	mainlay->setMargin(0);

	codeeditor = new QCodeEdit(false,this,doc);
	editor=codeeditor->editor();

	editor->setProperty("latexEditor", QVariant::fromValue<LatexEditorView*>(this));

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
	//connect(editor->document(),SIGNAL(contentsChange(int, int)),this,SLOT(documentContentChanged(int, int)));
	connect(editor->document(),SIGNAL(lineDeleted(QDocumentLineHandle*)),this,SLOT(lineDeleted(QDocumentLineHandle*)));

	connect(doc, SIGNAL(spellingLanguageChanged(QLocale)), this, SLOT(changeSpellingLanguage(QLocale)));

	//editor->setFlag(QEditor::CursorJumpPastWrap,false);
	editor->disableAccentHack(config->hackDisableAccentWorkaround);

	editor->setInputBinding(defaultInputBinding);
	defaultInputBinding->completerConfig = completer->getConfig();
	Q_ASSERT(defaultInputBinding->completerConfig);
	editor->document()->setLineEndingDirect(QDocument::Local);
	mainlay->addWidget(editor);

	setFocusProxy(editor);

	environmentFormat=0;
	structureFormat=0;
	//containedLabels.setPattern("(\\\\label)\\{(.+)\\}");
	//containedReferences.setPattern("(\\\\ref|\\\\pageref)\\{(.+)\\}");
	updateSettings();
	SynChecker.verbatimFormat=QDocument::formatFactory()->id("verbatim");
	SynChecker.start();

	connect(&SynChecker, SIGNAL(checkNextLine(QDocumentLineHandle*,bool,int,int)), SLOT(checkNextLine(QDocumentLineHandle *,bool,int,int)), Qt::QueuedConnection);
}

LatexEditorView::~LatexEditorView() {
	delete searchReplacePanel; // to force deletion of m_search before document. Otherwise crashes can come up (linux)
	delete codeeditor; //explicit call destructor of codeeditor (although it has a parent, it is no qobject itself, but passed it to editor)

	SynChecker.stop();
	SynChecker.wait();
}

void LatexEditorView::updateLtxCommands(){
	if(!document)
		return;
	if(!document->parent)
		return;

	LatexParser ltxCommands=document->parent->ltxCommands;
	foreach(const LatexDocument *elem,document->getListOfDocs()){
		ltxCommands.append(elem->ltxCommands);
	}
	SynChecker.setLtxCommands(ltxCommands);
}

void LatexEditorView::paste(){
	if(completer->isVisible()){
		const QMimeData *d = QApplication::clipboard()->mimeData();

		if ( d ) {
			QString txt;
			if ( d->hasFormat("text/plain") )
				txt = d->text();
			else if ( d->hasFormat("text/html") )
				txt = d->html();

			if(txt.contains("\n"))
				txt.clear();

			if(txt.isEmpty()){
				completer->close();
				editor->paste();
			}else{
				completer->insertText(txt);
			}
		}
	}else{
		editor->paste();
	}
}

void LatexEditorView::insertMacro(QString macro){
	if (macro.isEmpty()) return;
	if (macro.left(8)=="%SCRIPT\n"){
		scriptengine eng;
		eng.setEditor(editor);
		macro=macro.remove(0,8);
		eng.setScript(macro);
		eng.run();
	} else if (macro.size() > 1 && macro.left(1)=="%" && macro != "%%") {
		macro=macro.remove(0,1);
		CodeSnippet s("\\begin{"+macro+"}");
		s.insert(editor);
	} else CodeSnippet(macro).insert(editor);
}

void LatexEditorView::viewActivated(){
	if (!LatexEditorView::completer) return;
}


void LatexEditorView::complete(int flags) {
	if (!LatexEditorView::completer) return;
	setFocus();
	LatexEditorView::completer->complete(editor,LatexCompleter::CompletionFlags(flags));
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
	int cnt=document->countLabels(label);
	if (cnt==0) return false;
	QMultiHash<QDocumentLineHandle*,int> result=document->getLabels(label);
	QDocumentLine line(result.keys().first());
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
	QFoldedLineIterator fli = ld->foldedLineIterator(doc, 0);
	for (int i=0; i < doc->lines(); i++, ++fli)
		if (fli.open){
		if (unFold) ld->expand(doc, i);
		else ld->collapse(doc, i);
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


QList<QAction *> LatexEditorView::getBaseActions(){
	if (!defaultInputBinding) return QList<QAction *>();
	return defaultInputBinding->baseActions;
}
void LatexEditorView::setBaseActions(QList<QAction *> baseActions) {
	if (!defaultInputBinding) return;
	defaultInputBinding->baseActions=baseActions;
}
void LatexEditorView::setSpellerManager(SpellerManager* manager) {
	spellerManager = manager;
	connect(spellerManager, SIGNAL(defaultSpellerChanged()), this, SLOT(reloadSpeller()));
}
void LatexEditorView::setSpeller(const QString &name) {
	if (!spellerManager) return;

	useDefaultSpeller = (name == "<default>");

	SpellerUtility* su;
	if (spellerManager->hasSpeller(name)) {
		su = spellerManager->getSpeller(name);
	} else {
		su = spellerManager->getSpeller(spellerManager->defaultSpellerName());
		useDefaultSpeller = true;
	}
	if (su == speller) return;
	if (speller) {
		disconnect(speller, SIGNAL(aboutToDelete()), this, SLOT(reloadSpeller()));
	}
	speller = su;
	connect(speller, SIGNAL(aboutToDelete()), this, SLOT(reloadSpeller()));
	emit spellerChanged(name);
	// force new highlighting
	documentContentChanged(0,editor->document()->lines());
}
void LatexEditorView::reloadSpeller() {
	if (useDefaultSpeller) {
		setSpeller("<default>");
		return;
	}

	SpellerUtility *su = qobject_cast<SpellerUtility *>(sender());
	if (!su) return;
	setSpeller(su->name());
}
QString LatexEditorView::getSpeller() {
	if (useDefaultSpeller) return QString("<default>");
	return speller->name();
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
	editor->setLineWrapping(config->wordwrap>0);
	editor->setSoftLimitedLineWrapping(config->wordwrap==2);
	editor->setHardLineWrapping(config->wordwrap>2);
	if(config->wordwrap>1){
		int lw=config->lineWidth<20?20:config->lineWidth;
		int w=QFontMetrics(QFont(config->fontFamily, config->fontSize)).averageCharWidth()*lw;
		editor->setWrapLineWidth(w);
	}else{
		editor->setWrapLineWidth(0);
	}
	editor->setFlag(QEditor::AutoIndent,config->autoindent);
	editor->setFlag(QEditor::WeakIndent,config->weakindent);
	editor->setFlag(QEditor::ReplaceTabs,config->indentWithSpaces);
	editor->setFlag(QEditor::MouseWheelZoom, config->mouseWheelZoom);
	//TODO: parenmatch
	editor->setFlag(QEditor::AutoCloseChars, config->parenComplete);;
	editor->setCursorSurroundingLines(config->cursorSurroundLines);
	lineMarkPanelAction->setChecked((config->showlinemultiples!=0) ||config->folding||config->showlinestate);
	lineNumberPanelAction->setChecked(config->showlinemultiples!=0);
	lineFoldPanelAction->setChecked(config->folding);
	lineChangePanelAction->setChecked(config->showlinestate);
	statusPanelAction->setChecked(config->showcursorstate);
	editor->setDisplayModifyTime(config->displayModifyTime);
	searchReplacePanel->setUseLineForSearch(config->useLineForSearch);
	searchReplacePanel->setSearchOnlyInSelection(config->searchOnlyInSelection);
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
        deleteFormat=QDocument::formatFactory()->id("diffDelete");
        insertFormat=QDocument::formatFactory()->id("diffAdd");
        replaceFormat=QDocument::formatFactory()->id("diffReplace");

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

void LatexEditorView::openPackageDocumentation(){
	QAction *act = qobject_cast<QAction*>(sender());
	QString packageName = act->data().toString();
	if (!packageName.isEmpty()) {
		QStringList args;
		args << "--view" << packageName;
		QProcess proc(this);
		connect(&proc, SIGNAL(readyReadStandardError()), this, SLOT(openPackageDocumentationError()));
		proc.start("texdoc", args);
		if (!proc.waitForFinished(2000)) {
			txsWarning("texdoc took too long to open the package documentation");
			return;
		}
	}
}

void LatexEditorView::openPackageDocumentationError() {
	QProcess *proc = qobject_cast<QProcess*>(sender());
	if (proc) {
		txsWarning(proc->readAllStandardError());
	}
}

void LatexEditorView::emitChangeDiff(){
	QAction *act = qobject_cast<QAction*>(sender());
	QPoint pt=act->data().toPoint();
	emit changeDiff(pt);
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
void LatexEditorView::checkNextLine(QDocumentLineHandle *dlh,bool clearOverlay,int excessCols,int ticket){
	Q_ASSERT_X(dlh!=0,"checkNextLine","empty dlh used in checkNextLine");
	if(dlh->getRef()>1 && dlh->getCurrentTicket()==ticket){
		StackEnvironment env;
		QVariant envVar=dlh->getCookie(1);
		if(envVar.isValid())
			env=envVar.value<StackEnvironment>();
		int index = document->indexOf(dlh);
		if (index == -1) return; //deleted
		REQUIRE(dlh->document() == document);
		if (index + 1 >= document->lines()) return;
		SynChecker.putLine(document->line(index+1).handle(), env, clearOverlay, excessCols);
	}
	dlh->deref();
}

void LatexEditorView::clearOverlays(){
	for (int i=0; i<editor->document()->lineCount(); i++) {
		QDocumentLine line = editor->document()->line(i);
		if (!line.isValid()) continue;

		//remove all overlays used for latex things, in descending frequency
		line.clearOverlays(SpellerUtility::spellcheckErrorFormat);
		line.clearOverlays(referencePresentFormat);
		line.clearOverlays(citationPresentFormat);
		line.clearOverlays(referenceMissingFormat);
		line.clearOverlays(referenceMultipleFormat);
		line.clearOverlays(citationMissingFormat);
		line.clearOverlays(environmentFormat);
		line.clearOverlays(syntaxErrorFormat);
		line.clearOverlays(styleHintFormat);
		line.clearOverlays(structureFormat);
	}
}

void LatexEditorView::documentContentChanged(int linenr, int count) {
	Q_ASSERT(editor);
	QDocumentLine startline=editor->document()->line(linenr);
	if ((linenr>=0 || count<editor->document()->lines()) && editor->cursor().isValid() &&
	    !editor->cursor().atLineStart() && editor->cursor().line().text().trimmed().length()>0 &&
	    startline.isValid()) {
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

	if (autoPreviewCursor.size() > 0) {
		for (int i=0;i<autoPreviewCursor.size();i++) {
			const QDocumentCursor& c = autoPreviewCursor[i];
			if (c.lineNumber() >= linenr && c.lineNumber() < linenr+count)
				emit showPreview(c); //may modify autoPreviewCursor
		}

	}

	// checking
	if (!QDocument::formatFactory()) return;
	if (!config->realtimeChecking) return; //disable all => implicit disable environment color correction (optimization)
	if (editor->languageDefinition() && editor->languageDefinition()->language()!="(La-)TeX") return; // no online checking in other files than tex
	Q_ASSERT(speller);
	for (int i=linenr; i<linenr+count; i++) {
		QDocumentLine line = editor->document()->line(i);
		if (!line.isValid()) continue;

		//remove all overlays used for latex things, in descending frequency
		line.clearOverlays(SpellerUtility::spellcheckErrorFormat);
		line.clearOverlays(referencePresentFormat);
		line.clearOverlays(citationPresentFormat);
		line.clearOverlays(referenceMissingFormat);
		line.clearOverlays(referenceMultipleFormat);
		line.clearOverlays(citationMissingFormat);
		line.clearOverlays(environmentFormat);
		line.clearOverlays(syntaxErrorFormat);
		line.clearOverlays(styleHintFormat);
		line.clearOverlays(structureFormat);
                line.clearOverlays(insertFormat);
                line.clearOverlays(deleteFormat);
                line.clearOverlays(replaceFormat);

		bool addedOverlaySpellCheckError = false;
		bool addedOverlayReference = false;
		bool addedOverlayCitation = false;
		bool addedOverlayEnvironment = false;
		bool addedOverlayStyleHint = false;
		bool addedOverlayStructure = false;

                // diff presentation
                QVariant cookie=line.getCookie(2);
                if(!cookie.isNull()){
                    DiffList diffList=cookie.value<DiffList>();
                    for(int i=0;i<diffList.size();i++){
                        DiffOp op=diffList.at(i);
                        switch (op.type){
                            case DiffOp::Delete:
                                line.addOverlay(QFormatRange(op.start,op.length,deleteFormat));
                                break;
                            case DiffOp::Insert:
                                line.addOverlay(QFormatRange(op.start,op.length,insertFormat));
                                break;
                            case DiffOp::Replace:
                                line.addOverlay(QFormatRange(op.start,op.length,replaceFormat));
                                break;
			    default:
				;
                        }

                    }
                }

		// start syntax checking
		if(config->inlineSyntaxChecking) {
			StackEnvironment env;
			getEnv(i,env);
			QString text=line.text();
			if(!text.isEmpty() || SyntaxCheck::containsEnv("tabular",env)){
				QVector<int>fmts=line.getFormats();
				for(int i=0;i<text.length() && i < fmts.size();i++){
					if(fmts[i]==verbatimFormat){
						text[i]=QChar(' ');
					}
				}
				QDocumentLineHandle *previous=line.handle()->previous();
				int excessCols=0;
				if(previous)
					excessCols=previous->getCookie(0).toInt();
				SynChecker.putLine(line.handle(),env,false,excessCols);
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
				//QString secName=extractSectionName(lineText.mid(wordstart),true);
				//line.addOverlay(QFormatRange(wordstart,secName.length(),structureFormat));
				QStringList result;
				QList<int> starts;
				LatexParser::resolveCommandOptions(lineText,wordstart-1,result,&starts);
				for(int j=0;j<starts.count() && j<2;j++){
					QString text=result.at(j);
					line.addOverlay(QFormatRange(starts.at(j)+1,text.length()-2,structureFormat));
					if(text.startsWith("{")) break;
				}
				inStructure=false;
				addedOverlayStructure = true;
			}
			if (status==NW_ENVIRONMENT) {
				if(line.getFormatAt(wordstart)==verbatimFormat) continue;
				line.addOverlay(QFormatRange(wordstart,start-wordstart,environmentFormat));
				QRegExp rx("[ ]*(\\[.*\\])*\\{.+\\}");
				rx.setMinimal(true);
				int l=rx.indexIn(lineText,start);
				if (l==start+1) start=start+rx.cap(0).length();
				addedOverlayEnvironment = true;
			}
			if (status==NW_REFERENCE && config->inlineReferenceChecking) {
				if(line.getFormatAt(wordstart)==verbatimFormat) continue;
				QString ref=word;//lineText.mid(wordstart,start-wordstart);
				/*
				containedReferences->insert(ref,dlh);
				int cnt=containedLabels->count(ref);
				*/
				int cnt=document->countLabels(ref);
				if(cnt>1) {
					line.addOverlay(QFormatRange(wordstart,start-wordstart,referenceMultipleFormat));
				}else if (cnt==1) line.addOverlay(QFormatRange(wordstart,start-wordstart,referencePresentFormat));
				else line.addOverlay(QFormatRange(wordstart,start-wordstart,referenceMissingFormat));
				addedOverlayReference = true;
			}
			if (status==NW_LABEL && config->inlineReferenceChecking) {
				if(line.getFormatAt(wordstart)==verbatimFormat) continue;
				QString ref=word;//lineText.mid(wordstart,start-wordstart);
				/*
				containedLabels->insert(ref,dlh);
				int cnt=containedLabels->count(ref);
				*/
				int cnt=document->countLabels(ref);
				if(cnt>1) {
					line.addOverlay(QFormatRange(wordstart,start-wordstart,referenceMultipleFormat));
				}else line.addOverlay(QFormatRange(wordstart,start-wordstart,referencePresentFormat));
				// look for corresponding reeferences and adapt format respectively
				//containedLabels->updateByKeys(QStringList(ref),containedReferences);
				document->updateRefsLabels(ref);
				addedOverlayReference = true;
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
				addedOverlayCitation = true;
			}
			if (status==NW_COMMENT) break;
			if (status==NW_TEXT && config->inlineSpellChecking){
				if(!previousTextWord.isEmpty() && previousTextWord==word){
					if(!lineText.mid(previousTextWordIndex,wordstart-previousTextWordIndex).contains(QRegExp("\\S"))){
						line.addOverlay(QFormatRange(wordstart,start-wordstart,styleHintFormat));
						addedOverlayStyleHint = true;
					}
				}
				if(!word.isEmpty() && !word.at(0).isNumber()){
					previousTextWord=word;
					previousTextWordIndex=start;
				} else previousTextWord.clear();
			} else previousTextWord.clear();
			if (status==NW_TEXT && word.length()>=3 && speller && !speller->check(word) && config->inlineSpellChecking) {
				if(word.endsWith('.')) start--;
				line.addOverlay(QFormatRange(wordstart,start-wordstart,SpellerUtility::spellcheckErrorFormat));
				addedOverlaySpellCheckError = true;
			}
		}// while

		//update wrapping if the an overlay changed the width of the text
		//TODO: should be handled by qce to be consistent (with syntax check and search)
		if (!editor->document()->getFixedPitch() && editor->flag(QEditor::LineWrap)) {
			bool updateWrapping = false;
			QFormatScheme* ff = QDocument::formatFactory();
			updateWrapping |= addedOverlaySpellCheckError && ff->format(SpellerUtility::spellcheckErrorFormat).widthChanging();
			updateWrapping |= addedOverlayReference && (ff->format(referenceMissingFormat).widthChanging() || ff->format(referencePresentFormat).widthChanging() || ff->format(referenceMultipleFormat).widthChanging());
			updateWrapping |= addedOverlayCitation && (ff->format(citationPresentFormat).widthChanging() || ff->format(citationMissingFormat).widthChanging());
			updateWrapping |= addedOverlayEnvironment && ff->format(environmentFormat).widthChanging();
			updateWrapping |= addedOverlayStyleHint && ff->format(styleHintFormat).widthChanging();
			updateWrapping |= addedOverlayStructure && ff->format(structureFormat).widthChanging();
			if (updateWrapping)
				line.handle()->updateWrapAndNotifyDocument(i);

		}
	}
	editor->document()->markViewDirty();
}


void LatexEditorView::lineDeleted(QDocumentLineHandle* l) {

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
			QList<QFormatRange> li=editor->document()->line(i).getOverlays(SpellerUtility::spellcheckErrorFormat);
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
	QStringList suggestions= speller->suggest(defaultInputBinding->lastSpellCheckedWord);
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

void LatexEditorView::closeCompleter(){
	completer->close();
}

void LatexEditorView::reCheckSyntax(int linenr, int count){
	// expensive function ... however if \newcommand is changed valid commands become invalid and vice versa
	if(!config->inlineSyntaxChecking || !config->realtimeChecking) return;
	if(linenr<0 || linenr>=editor->document()->lineCount()) linenr=0;
	QDocumentLine line=editor->document()->line(linenr);
	QDocumentLine prev;
	if (linenr > 0) prev = editor->document()->line(linenr - 1);
	int lineNrEnd = count < 0 ? editor->document()->lineCount() : qMin(count + linenr, editor->document()->lineCount());
	for (int i=linenr; i < lineNrEnd; i++) {
		Q_ASSERT(line.isValid());
		StackEnvironment env;
		getEnv(i,env);
		QDocumentLineHandle *previous=line.handle()->previous();
		int excessCols=0;
		if(previous)
			excessCols=previous->getCookie(0).toInt();
		SynChecker.putLine(line.handle(),env,true,excessCols);
		prev = line;
		line = editor->document()->line(i+1);
	}
}

void LatexEditorView::mouseHovered(QPoint pos){
	// reimplement to what is necessary

	if(pos.x()<0) return;  // hover event on panel
	QDocumentCursor cursor;
	cursor=editor->cursorForPosition(editor->mapToContents(pos));
	QString line=cursor.line().text();
	QDocumentLine l=cursor.line();

	QFormatRange fr = cursor.line().getOverlayAt(cursor.columnNumber(),replaceFormat);
	if (fr.length>0 && fr.format==replaceFormat) {
		QVariant var=l.getCookie(2);
		if(var.isValid()){
		    DiffList diffList=var.value<DiffList>();
		    DiffOp op;
		    op.start=-1;
		    foreach(op,diffList){
			if(op.start<=cursor.columnNumber() && op.start+op.length>=cursor.columnNumber()){
			    break;
			}
			op.start=-1;
		    }

		    if(op.start>=0 && !op.text.isEmpty()){
			    QString message=op.text;
			    QToolTip::showText(editor->mapToGlobal(editor->mapFromFrame(pos)),message);
			    return;
		    }
		}
	}
	// check for latex error
	//syntax checking
	int f=QDocument::formatFactory()->id("latexSyntaxMistake");
	fr = cursor.line().getOverlayAt(cursor.columnNumber(),f);
	if (fr.length>0 && fr.format==f) {
		StackEnvironment env;
		getEnv(l.lineNumber(),env);
		QString text=l.text();
		if(!text.isEmpty()){
			QString message=SynChecker.getErrorAt(l.handle(),cursor.columnNumber(),env);
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
		if(cursor.nextChar()==QChar('$') && config->toolTipPreview){
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
							last=parens[i].offset + parens[i].length;
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
		if(MathEnvirons.contains(value)&&config->toolTipPreview){
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
			if(config->toolTipHelp){
				topic=completer->lookupWord(command);
				if(!topic.isEmpty()) QToolTip::showText(editor->mapToGlobal(editor->mapFromFrame(pos)), topic);
			}
		}
		break;
		case LatexParser::Environment:
		if(config->toolTipHelp){
			topic=completer->lookupWord("\\begin{"+value+"}");
			if(!topic.isEmpty()) QToolTip::showText(editor->mapToGlobal(editor->mapFromFrame(pos)), topic);
		}
		break;
		case LatexParser::Reference:
		{
			//l=editor->document()->findLineContaining("\\label{"+ref+"}",0,Qt::CaseSensitive);
			//QList<QDocumentLineHandle*> lst=containedLabels->values(value);
			int cnt=document->countLabels(value);
			QString mText="";
			if(cnt==0){
				mText=tr("label missing!");
			} else if(cnt>1) {
				mText=tr("label multiple times defined!");
			} else {
				QMultiHash<QDocumentLineHandle*,int> result=document->getLabels(value);
				QDocumentLineHandle *mLine=result.keys().first();
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
		if(document->countLabels(value)>1){
			QToolTip::showText(editor->mapToGlobal(editor->mapFromFrame(pos)),tr("label multiple times defined!"));
		} else {
			int cnt=document->countRefs(value);
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
		searchReplacePanel->closeSomething(config->closeSearchAndReplace);
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

void LatexEditorView::getEnv(int lineNumber,StackEnvironment &env){
	Environment newEnv;
	newEnv.name="normal";
	newEnv.id=1;
	env.push(newEnv);
	if (lineNumber > 0) {
		QDocumentLine prev = editor->document()->line(lineNumber - 1);
		REQUIRE(prev.isValid());
		QVariant result=prev.getCookie(1);
		if(result.isValid())
			env=result.value<StackEnvironment>();
	}
}

void LatexEditorView::triggeredThesaurus(){
	QAction *act = qobject_cast<QAction*>(sender());
	QPoint pt=act->data().toPoint();
	emit thesaurus(pt.x(),pt.y());
}

void LatexEditorView::changeSpellingLanguage(const QLocale &loc) {
	if (spellerManager->hasSpeller(loc.name())) {
		setSpeller(loc.name());
	}
}

QString BracketInvertAffector::affect(const QKeyEvent *, const QString& base, int, int) const{
	static const QString& brackets = "<>()[]{}";
	QString after;
	for (int i=0; i < base.length(); i++)
		if (brackets.indexOf(base[i]) >= 0)
			after += brackets[brackets.indexOf(base[i]) + 1 - 2*(brackets.indexOf(base[i]) & 1) ];
	else if (base[i] == '\\') {
		if (base.mid(i, 7) == "\\begin{") {
			after += "\\end{" + base.mid(i+7);
			return after;
		} else if (base.mid(i, 5) == "\\end{") {
			after += "\\begin{" + base.mid(i+5);
			return after;
		} else if (base.mid(i, 5) == "\\left") {
			after += "\\right";
			i+=4;
		} else if (base.mid(i, 6) == "\\right") {
			after += "\\left";
			i+=5;
		}
		else after += '\\';
	} else after += base[i];
	return after;
}
BracketInvertAffector* inverterSingleton = 0;
BracketInvertAffector* BracketInvertAffector::instance(){
	if (!inverterSingleton) inverterSingleton = new BracketInvertAffector();
	return inverterSingleton;
}
