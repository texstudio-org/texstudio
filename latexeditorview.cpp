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

#include "help.h"

QStringList LatexEditorView::checkedLanguages = QStringList() << "(La)TeX" << "Pweave" << "Sweave" << "TeX dtx file"; // languages for online checking (exact name from qnfa file)

//------------------------------Default Input Binding--------------------------------
class DefaultInputBinding: public QEditorInputBinding {
	//  Q_OBJECT not possible because inputbinding is no qobject
public:
	DefaultInputBinding():completerConfig(0),contextMenu(0),isDoubleClick(false) {}
	virtual QString id() const {
		return "TXS::DefaultInputBinding";
	}
	virtual QString name() const {
		return "TXS::DefaultInputBinding";
	}
	
	virtual bool keyPressEvent(QKeyEvent *event, QEditor *editor);
	virtual void postKeyPressEvent(QKeyEvent *event, QEditor *editor);
	virtual bool keyReleaseEvent(QKeyEvent *event, QEditor *editor);
	virtual bool mousePressEvent(QMouseEvent *event, QEditor *editor);
	virtual bool mouseReleaseEvent(QMouseEvent *event, QEditor *editor);
	virtual bool mouseDoubleClickEvent(QMouseEvent *event, QEditor *editor);
	virtual bool mouseMoveEvent(QMouseEvent *event, QEditor *editor);
	virtual bool contextMenuEvent(QContextMenuEvent *event, QEditor *editor);
private:
	bool runMacros(QKeyEvent *event, QEditor *editor);
	bool autoInsertLRM(QKeyEvent *event, QEditor *editor);
	friend class LatexEditorView;
	const LatexCompleterConfig* completerConfig;
	const LatexEditorViewConfig* editorViewConfig;
	QList<QAction *> baseActions;
	
	QMenu* contextMenu;
	QString lastSpellCheckedWord;
	
	QPoint lastMousePressLeft;
	bool isDoubleClick;  // event sequence of a double click: press, release, double click, release - this is true on the second release
};

static const QString LRMStr = QChar(LRM);

bool DefaultInputBinding::runMacros(QKeyEvent *event, QEditor *editor) {
	Q_ASSERT(completerConfig);
	QLanguageDefinition *language = editor->document() ? editor->document()->languageDefinition() : 0;
	QDocumentLine line = editor->cursor().selectionStart().line();
	int column = editor->cursor().selectionStart().columnNumber();
	QString prev = line.text().mid(0, column) + event->text(); //TODO: optimize
	foreach (const Macro &m, completerConfig->userMacros) {
		if (!m.isActiveForTrigger(Macro::ST_REGEX)) continue;
		if (!m.isActiveForLanguage(language)) continue;
		if (!(m.isActiveForFormat(line.getFormatAt(column)) || (column > 0 && m.isActiveForFormat(line.getFormatAt(column-1))))) continue; //two checks, so it works at beginning and end of an environment
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
			if (m.triggerRegex.matchedLength() > 1) {
				c.movePosition(realMatchLen-1, QDocumentCursor::PreviousCharacter, QDocumentCursor::KeepAnchor);
				c.removeSelectedText();
			}

			LatexEditorView* view = editor->property("latexEditor").value<LatexEditorView*>();
			REQUIRE_RET(view, true);
			view->insertMacro(m.tag, r, Macro::ST_REGEX);
			//editor->insertText(c, m.tag);
			if (block) editor->document()->endMacro();
			editor->emitCursorPositionChanged(); //prevent rogue parenthesis highlightations
			/*			if (editor->languageDefinition())
editor->languageDefinition()->clearMatches(editor->document());
*/
			return true;
		}
	}
	return false;
}

bool DefaultInputBinding::autoInsertLRM(QKeyEvent *event, QEditor *editor) {
	const QString & text = event->text();
	if (editorViewConfig->autoInsertLRM && text.length() == 1 && editor->cursor().isRTL()) {
		if (text.at(0) == '}') {
			bool autoOverride = editor->isAutoOverrideText("}");
			bool previousIsLRM = editor->cursor().previousChar().unicode() == LRM;
			bool block = previousIsLRM || autoOverride;
			if (block) editor->document()->beginMacro();
			if (previousIsLRM) editor->cursor().deletePreviousChar(); //todo mirrors
			if (autoOverride) {
				editor->write("}"); //separated, so autooverride works
				editor->write(LRMStr);
			} else editor->write("}"+LRMStr);
			if (block) editor->document()->endMacro();
			return true;
		}
	}
	return false;
}

bool DefaultInputBinding::keyPressEvent(QKeyEvent *event, QEditor *editor) {
	if (LatexEditorView::completer && LatexEditorView::completer->acceptTriggerString(event->text()) &&
	              (editor->currentPlaceHolder() < 0 || editor->currentPlaceHolder() >= editor->placeHolderCount() || editor->getPlaceHolder(editor->currentPlaceHolder()).mirrors.isEmpty() ||  editor->getPlaceHolder(editor->currentPlaceHolder()).affector != BracketInvertAffector::instance()))  {
		//update completer if necessary
		editor->emitNeedUpdatedCompleter();
		bool autoOverriden = editor->isAutoOverrideText(event->text());
		if (editorViewConfig->autoInsertLRM && event->text() == "\\" && editor->cursor().isRTL())
			editor->write(LRMStr + event->text());
		else
			editor->write(event->text());
		if (autoOverriden) LatexEditorView::completer->complete(editor,LatexCompleter::CF_OVERRIDEN_BACKSLASH);
		else LatexEditorView::completer->complete(editor,0);
		return true;
	}
	if (!event->text().isEmpty()) {
		if (runMacros(event, editor))
			return true;
		if (autoInsertLRM(event, editor))
			return true;
	} else {
		if (event->key() == Qt::Key_Control) {
			editor->setMouseTracking(true);
		}
	}
	if (LatexEditorView::hideTooltipWhenLeavingLine!=-1 && editor->cursor().lineNumber()!=LatexEditorView::hideTooltipWhenLeavingLine) {
		LatexEditorView::hideTooltipWhenLeavingLine=-1;
		QToolTip::hideText();
	}
	return false;
}

void DefaultInputBinding::postKeyPressEvent(QKeyEvent *event, QEditor *editor) {
	if (event->text() == ",") {
		LatexEditorView* view = editor->property("latexEditor").value<LatexEditorView*>();
		Q_ASSERT(view);
		emit view->colonTyped();
	}
}


bool DefaultInputBinding::keyReleaseEvent(QKeyEvent *event, QEditor *editor) {
	if (event->key() == Qt::Key_Control) {
		editor->setMouseTracking(false);
		LatexEditorView *edView=qobject_cast<LatexEditorView *>(editor->parentWidget()); //a qobject is necessary to retrieve events
		edView->removeLinkOverlay();
	}
	return false;
}

bool DefaultInputBinding::mousePressEvent(QMouseEvent *event, QEditor *editor){
	LatexEditorView *edView = 0;

	switch (event->button()) {
	case Qt::XButton1:
		edView=qobject_cast<LatexEditorView *>(editor->parentWidget());
		emit edView->mouseBackPressed();
		return true;
	case Qt::XButton2:
		edView=qobject_cast<LatexEditorView *>(editor->parentWidget());
		emit edView->mouseForwardPressed();
		return true;
	case Qt::LeftButton:
		edView=qobject_cast<LatexEditorView *>(editor->parentWidget());
		emit edView->cursorChangeByMouse();
		lastMousePressLeft = event->pos();
		return false;
	default:
		return false;
	}

	return false;
}

bool DefaultInputBinding::mouseReleaseEvent(QMouseEvent *event, QEditor *editor) {
	if (isDoubleClick) {
		isDoubleClick = false;
		return false;
	}
	isDoubleClick = false;

	if (event->modifiers() == Qt::ControlModifier && event->button() == Qt::LeftButton) {
		// Ctrl+LeftClick
		int distanceSqr = (event->pos().x() - lastMousePressLeft.x())*(event->pos().x() - lastMousePressLeft.x()) + (event->pos().y() - lastMousePressLeft.y())*(event->pos().y() - lastMousePressLeft.y());
		if (distanceSqr > 4) // allow the user to accidentially move the mouse a bit
			return false;

		LatexEditorView *edView=qobject_cast<LatexEditorView *>(editor->parentWidget()); //a qobject is necessary to retrieve events
		if (!edView) return false;
		QDocumentCursor cursor = editor->cursorForPosition(editor->mapToContents(event->pos()));

		if (edView->hasLinkOverlay()) {
			LinkOverlay lo = edView->getLinkOverlay();
			switch (lo.type) {
			case LinkOverlay::RefOverlay:
				emit edView->gotoDefinition(cursor);
				return true;
			case LinkOverlay::FileOverlay:
				edView->openFile(lo.text());
				return true;
			case LinkOverlay::UsepackageOverlay:
				edView->openPackageDocumentation(lo.text());
				return true;
			case LinkOverlay::BibFileOverlay:
				edView->openFile(lo.text(), "bib");
				return true;
			case LinkOverlay::CiteOverlay:
				emit edView->gotoDefinition(cursor);
				return true;
			case LinkOverlay::Invalid:
				break;
			}
		}

		if (!editor->languageDefinition()) return false;
		if (editor->languageDefinition()->language() != "(La)TeX")
			return false;
		emit edView->syncPDFRequested(cursor);
		return true;
	}
	return false;
}

bool DefaultInputBinding::mouseDoubleClickEvent(QMouseEvent *event, QEditor *editor) {
	Q_UNUSED(event);
	Q_UNUSED(editor);
	isDoubleClick = true;
	return false;
}

bool DefaultInputBinding::contextMenuEvent(QContextMenuEvent *event, QEditor *editor) {
	if (!contextMenu) contextMenu=new QMenu(0);
	contextMenu->clear();
	QDocumentCursor cursor;
	if (event->reason()==QContextMenuEvent::Mouse) cursor=editor->cursorForPosition(editor->mapToContents(event->pos()));
	else cursor=editor->cursor();
	LatexEditorView *edView=qobject_cast<LatexEditorView *>(editor->parentWidget()); //a qobject is necessary to retrieve events
	REQUIRE_RET(edView, false);

	// check for context menu on preview picture
	QRect pictRect = cursor.line().getCookie(QDocumentLine::PICTURE_COOKIE_DRAWING_POS).toRect();
	if (pictRect.isValid()) {
		QPoint posInDocCoordinates(event->pos().x() + edView->editor->horizontalOffset(), event->pos().y() + edView->editor->verticalOffset());
		if (pictRect.contains(posInDocCoordinates)) {
			// get removePreviewAction
			// ok, this is not an ideal way of doing it because (i) it has to be in the baseActions (at least we Q_ASSERT this) and (ii) the iteration over the baseActions
			// Alternatives: 1) include configmanager and use ConfigManager->getInstance()->getManagedAction() - Disadvantage: additional dependency
			//               2) explicitly pass it to the editorView (like the base actions, but separate) - Disadvantage: code overhead
			//               3) Improve the concept of base actions:
			//                    LatexEditorView::addContextAction(QAction); called when creating the editorView
			//                    LatexEditorView::getContextAction(QString); used here to populate the menu
			bool removePreviewActionFound = false;
			foreach(QAction *act, baseActions) {
				if (act->objectName().endsWith("removePreviewLatex")) {
					act->setData(posInDocCoordinates);
					contextMenu->addAction(act);
					removePreviewActionFound = true;
					break;
				}
			}
			Q_ASSERT(removePreviewActionFound);


			QVariant vPixmap = cursor.line().getCookie(QDocumentLine::PICTURE_COOKIE);
			if (vPixmap.isValid()) {
				(contextMenu->addAction("Copy Image", edView, SLOT(copyImageFromAction())))->setData(vPixmap);
				(contextMenu->addAction("Save Image As...", edView, SLOT(saveImageFromAction())))->setData(vPixmap);
			}
			contextMenu->exec(event->globalPos());
			return true;
		}
	}

	// normal context menu
	bool validPosition = cursor.isValid() && cursor.line().isValid();
	LatexParser::ContextType context = LatexParser::Unknown;
	QString ctxCommand, ctxValue;
	if (validPosition) {
		QFormatRange fr;
		//spell checking
		
		if (edView->speller){
			int pos;
			if (cursor.hasSelection()) pos = (cursor.columnNumber()+cursor.anchorColumnNumber()) / 2;
			else pos = cursor.columnNumber();

			foreach (const int f, edView->grammarFormats){
				fr = cursor.line().getOverlayAt(pos, f); 
				if (fr.length>0 && fr.format==f) {
					QVariant var=cursor.line().getCookie(QDocumentLine::GRAMMAR_ERROR_COOKIE);
					if (var.isValid()){
						QDocumentCursor wordSelection(editor->document(),cursor.lineNumber(),fr.offset);
						wordSelection.movePosition(fr.length,QDocumentCursor::NextCharacter,QDocumentCursor::KeepAnchor);
						editor->setCursor(wordSelection);
	
						const QList<GrammarError>& errors = var.value<QList<GrammarError> >();
						for (int i=0;i<errors.size();i++)
							if (errors[i].offset <= cursor.columnNumber() && errors[i].offset+errors[i].length >= cursor.columnNumber()) {
								edView->addListToContextMenu(errors[i].corrections, true, SLOT(spellCheckingReplace()));
								break;
							}
					}
				}
			}
			
			fr = cursor.line().getOverlayAt(pos, SpellerUtility::spellcheckErrorFormat);
			if (fr.length>0 && fr.format==SpellerUtility::spellcheckErrorFormat) {
				QString word=cursor.line().text().mid(fr.offset,fr.length);
				if (!(editor->cursor().hasSelection() && editor->cursor().selectedText().length()>0) || editor->cursor().selectedText()==word
				              || editor->cursor().selectedText()==lastSpellCheckedWord) {
					lastSpellCheckedWord=word;
					word=latexToPlainWord(word);
					QDocumentCursor wordSelection(editor->document(),cursor.lineNumber(),fr.offset);
					wordSelection.movePosition(fr.length,QDocumentCursor::NextCharacter,QDocumentCursor::KeepAnchor);
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
		int f=edView->citationMissingFormat;
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
		context = LatexParser::getInstance().findContext(line, cursor.columnNumber(), ctxCommand, ctxValue);
        //static const QStringList inputTokens = QStringList() << "\\input" << "\\include" << "\\includeonly";
        LatexParser ltxCommands=LatexParser::getInstance();
        if( (context==LatexParser::Command || context==LatexParser::Option) && ltxCommands.possibleCommands["%include"].contains(ctxCommand)){
			QAction* act=new QAction(LatexEditorView::tr("Open %1").arg(ctxValue),contextMenu);
			act->setData(ctxValue);
			edView->connect(act,SIGNAL(triggered()),edView,SLOT(openExternalFile()));
			contextMenu->addAction(act);
		}
		// bibliography command
		if ( (context==LatexParser::Command || context==LatexParser::Option) && ltxCommands.possibleCommands["%bibliography"].contains(ctxCommand)) {
			QAction *act = new QAction(LatexEditorView::tr("Open Bibliography"),contextMenu);
			QString bibFile;
			if (context == LatexParser::Option) {
				QDocumentCursor c(cursor);
				LatexEditorView::selectOptionInLatexArg(c);
				bibFile = c.selectedText() + ".bib";
			} else {
				// context==LatexParser::Command -> open first entry in arg list.
				bibFile = ctxValue.split(',').first() + ".bib";
			}
			act->setData(bibFile);
			edView->connect(act,SIGNAL(triggered()),edView,SLOT(openExternalFile()));
			contextMenu->addAction(act);
		}
		//package help
		if( (context==LatexParser::Command && ctxCommand=="\\usepackage") || context==LatexParser::Package){
			QAction* act=new QAction(LatexEditorView::tr("Open package documentation"),contextMenu);
			QString packageName;
			if (ctxValue.contains(',')) {
				// multiple packages included in one \usepackage command
				QStringList packages;
				foreach (const QString& pkg, ctxValue.split(',')) {
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
				packageName = ctxValue;
			}
			act->setText(act->text().append(QString(" (%1)").arg(packageName)));
			act->setData(packageName);
			edView->connect(act,SIGNAL(triggered()),edView,SLOT(openPackageDocumentation()));
			contextMenu->addAction(act);
		}
        // help for any "known" command
        if( context==LatexParser::Command){
            QString command=ctxCommand;
            if(ctxCommand=="\\begin"||ctxCommand=="\\end")
                command=ctxCommand+"{"+ctxValue+"}";
            QString package=edView->document->parent->findPackageByCommand(command);
            package.chop(4);
            if(!package.isEmpty()){
                QAction* act=new QAction(LatexEditorView::tr("Open package documentation"),contextMenu);
                act->setText(act->text().append(QString(" (%1)").arg(package)));
                act->setData(package+"#"+command);
                edView->connect(act,SIGNAL(triggered()),edView,SLOT(openPackageDocumentation()));
                contextMenu->addAction(act);
            }
        }

		//resolve differences
		if (edView){
			QList<int> fids;
			fids<<edView->deleteFormat<<edView->insertFormat<<edView->replaceFormat;
			foreach(int fid,fids){
				if (cursor.hasSelection()) fr= cursor.line().getOverlayAt((cursor.columnNumber()+cursor.anchorColumnNumber()) / 2,fid);
				else fr = cursor.line().getOverlayAt(cursor.columnNumber(),fid);
				if (fr.length>0 ) {
					QVariant var=cursor.line().getCookie(QDocumentLine::DIFF_LIST_COOCKIE);
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
		contextMenu->addSeparator();
	}
	contextMenu->addActions(baseActions);
	if (validPosition) {
		contextMenu->addSeparator();

		if (context == LatexParser::Citation || context == LatexParser::Reference) {
			QAction *act = new QAction(LatexEditorView::tr("Go to Definition"), contextMenu);
			act->setData(QVariant().fromValue<QDocumentCursor>(cursor));
			edView->connect(act, SIGNAL(triggered()), edView, SLOT(emitGotoDefinitionFromAction()));
			contextMenu->addAction(act);
		}

		QAction *act = new QAction(LatexEditorView::tr("Go to PDF"), contextMenu);
		act->setData(QVariant().fromValue<QDocumentCursor>(cursor));
		edView->connect(act, SIGNAL(triggered()), edView, SLOT(emitSyncPDFFromAction()));
		contextMenu->addAction(act);
	}


	if (event->reason()==QContextMenuEvent::Mouse) contextMenu->exec(event->globalPos());
	else {
		QPoint curPoint=editor->cursor().documentPosition();
		curPoint.ry() += editor->document()->getLineSpacing();
		contextMenu->exec(editor->mapToGlobal(editor->mapFromContents(curPoint)));
	}
	return true;
}

bool DefaultInputBinding::mouseMoveEvent(QMouseEvent *event, QEditor *editor) {
	if(event->modifiers() == Qt::ControlModifier) {
		LatexEditorView *edView=qobject_cast<LatexEditorView *>(editor->parentWidget());
		QDocumentCursor cursor = editor->cursorForPosition(editor->mapToContents(event->pos()));
		edView->checkForLinkOverlay(cursor);
	} else {
		// reached for example when Ctrl+Shift is pressed
		LatexEditorView *edView=qobject_cast<LatexEditorView *>(editor->parentWidget()); //a qobject is necessary to retrieve events
		edView->removeLinkOverlay();
	}
	return false;
}

DefaultInputBinding *defaultInputBinding = new DefaultInputBinding();



//----------------------------------LatexEditorView-----------------------------------
LatexCompleter* LatexEditorView::completer=0;
int LatexEditorView::hideTooltipWhenLeavingLine = -1;

Q_DECLARE_METATYPE(LatexEditorView*);

LatexEditorView::LatexEditorView(QWidget *parent, LatexEditorViewConfig* aconfig,LatexDocument *doc) : QWidget(parent),document(0),speller(0),curChangePos(-1),config(aconfig),bibReader(0) {
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
	QFoldPanel *foldPanel = new QFoldPanel;
	lineFoldPanelAction=codeeditor->addPanel(foldPanel, QCodeEdit::West, false);
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
	connect(lineMarkPanel,SIGNAL(contextMenuRequested(int,QPoint)),this,SLOT(lineMarkContextMenuRequested(int,QPoint)));
	connect(foldPanel, SIGNAL(contextMenuRequested(int,QPoint)),this,SLOT(foldContextMenuRequested(int,QPoint)));
	connect(editor,SIGNAL(hovered(QPoint)),this,SLOT(mouseHovered(QPoint)));
	//connect(editor->document(),SIGNAL(contentsChange(int, int)),this,SLOT(documentContentChanged(int, int)));
	connect(editor->document(),SIGNAL(lineDeleted(QDocumentLineHandle*)),this,SLOT(lineDeleted(QDocumentLineHandle*)));
	
	connect(doc, SIGNAL(spellingDictChanged(QString)), this, SLOT(changeSpellingDict(QString)));
    connect(doc, SIGNAL(bookmarkRemoved(QDocumentLineHandle*)),this,SIGNAL(bookmarkRemoved(QDocumentLineHandle*)));
    connect(doc, SIGNAL(bookmarkAdded(QDocumentLineHandle*,int)),this,SIGNAL(bookmarkAdded(QDocumentLineHandle*,int)));
	
	//editor->setFlag(QEditor::CursorJumpPastWrap,false);
	editor->disableAccentHack(config->hackDisableAccentWorkaround);
	
	editor->setInputBinding(defaultInputBinding);
	defaultInputBinding->completerConfig = completer->getConfig();
	defaultInputBinding->editorViewConfig = config;
	Q_ASSERT(defaultInputBinding->completerConfig);
	editor->document()->setLineEndingDirect(QDocument::Local);
	mainlay->addWidget(editor);
	
	setFocusProxy(editor);
	
	//containedLabels.setPattern("(\\\\label)\\{(.+)\\}");
	//containedReferences.setPattern("(\\\\ref|\\\\pageref)\\{(.+)\\}");
	updateSettings();
	SynChecker.verbatimFormat=editor->document()->getFormatId("verbatim");
	SynChecker.setLtxCommands(LatexParser::getInstance());
	SynChecker.start();
    unclosedEnv.id=-1;
	
	connect(&SynChecker, SIGNAL(checkNextLine(QDocumentLineHandle*,bool,int)), SLOT(checkNextLine(QDocumentLineHandle *,bool,int)), Qt::QueuedConnection);
}

LatexEditorView::~LatexEditorView() {
	delete searchReplacePanel; // to force deletion of m_search before document. Otherwise crashes can come up (linux)
	delete codeeditor; //explicit call destructor of codeeditor (although it has a parent, it is no qobject itself, but passed it to editor)
	
	SynChecker.stop();
	SynChecker.wait();
    if(bibReader){
        bibReader->quit();
        bibReader->wait();
    }
}

void LatexEditorView::updateLtxCommands(bool updateAll){
	if(!document)
		return;
	if(!document->parent)
		return;
	
	LatexParser ltxCommands=LatexParser::getInstance();
    QList<LatexDocument *>listOfDocs=document->getListOfDocs();
    foreach(const LatexDocument *elem,listOfDocs){
		ltxCommands.append(elem->ltxCommands);
	}

    if(updateAll){
        foreach(const LatexDocument *elem,listOfDocs){

            LatexEditorView *view=elem->getEditorView();
            if(view){
                view->setLtxCommands(ltxCommands);
                view->reCheckSyntax();
            }
        }
    }else{
        SynChecker.setLtxCommands(ltxCommands);
    }
}

void LatexEditorView::setLtxCommands(const LatexParser& cmds){
    SynChecker.setLtxCommands(cmds);
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

void LatexEditorView::insertMacro(QString macro, const QRegExp& trigger, int triggerId, bool allowWrite){
	if (macro.isEmpty()) return;
	if (macro.left(8)=="%SCRIPT\n"){
		scriptengine* eng = new scriptengine();
		for (int i=0;i<=trigger.captureCount();i++)
			eng->triggerMatches << trigger.cap(i);
		eng->triggerId = triggerId;
		if (this) eng->setEditorView(this);
		macro=macro.remove(0,8);
        eng->setScript(macro,allowWrite);
		eng->run();
		if (!eng->globalObject) delete eng;
		else QObject::connect(reinterpret_cast<QObject*>(eng->globalObject), SIGNAL(destroyed()), eng, SLOT(deleteLater()));
		return;
	} 
	if (!this) return;
	if (macro.size() > 1 && macro.left(1)=="%" && macro != "%%") {
		macro=macro.remove(0,1);
		CodeSnippet s("\\begin{"+macro+"}");
		s.insert(editor);
	} else CodeSnippet(macro).insert(editor);
}

void LatexEditorView::checkForLinkOverlay(QDocumentCursor cursor) {
	if (cursor.atBlockEnd()) {
		removeLinkOverlay();
		return;
	}

	bool validPosition = cursor.isValid() && cursor.line().isValid();
	if (validPosition) {
		LatexParser::ContextType context = LatexParser::Unknown;
		QString ctxCommand, ctxValue;
		QString line=cursor.line().text();
		context = LatexParser::getInstance().findContext(line, cursor.columnNumber(), ctxCommand, ctxValue);
		if (context == LatexParser::Reference) {
			setLinkOverlay(LinkOverlay(cursor, context, LinkOverlay::RefOverlay));
		} else if (context==LatexParser::Option && LatexParser::getInstance().possibleCommands["%include"].contains(ctxCommand)) {
			setLinkOverlay(LinkOverlay(cursor, context, LinkOverlay::FileOverlay));
		} else if (context==LatexParser::Package) {
			setLinkOverlay(LinkOverlay(cursor, context, LinkOverlay::UsepackageOverlay));
		} else if (context==LatexParser::Option && LatexParser::getInstance().possibleCommands["%bibliography"].contains(ctxCommand)) {
			setLinkOverlay(LinkOverlay(cursor, context, LinkOverlay::BibFileOverlay));
		} else if (context==LatexParser::Citation) {
			setLinkOverlay(LinkOverlay(cursor, context, LinkOverlay::CiteOverlay));
		} else {
			if (linkOverlay.isValid()) removeLinkOverlay();
		}
	} else {
		if (linkOverlay.isValid()) removeLinkOverlay();
	}
}

void LatexEditorView::setLinkOverlay(const LinkOverlay & overlay) {
	if (linkOverlay.isValid()) {
		if (overlay == linkOverlay) {
			return; // same overlay
		} else {
			removeLinkOverlay();
		}
	}

	linkOverlay = overlay;
	linkOverlay.docLine.addOverlay(linkOverlay.formatRange);
	editor->viewport()->update(); // immediately apply the overlay
	linkOverlayStoredCursor = editor->viewport()->cursor();
	editor->viewport()->setCursor(Qt::PointingHandCursor);
}

void LatexEditorView::removeLinkOverlay() {
	if (linkOverlay.isValid()) {
		linkOverlay.docLine.removeOverlay(linkOverlay.formatRange);
		linkOverlay = LinkOverlay();
		editor->viewport()->update(); // immediately apply the overlay
		editor->viewport()->setCursor(linkOverlayStoredCursor);
	}
}

bool LatexEditorView::isNonTextFormat(int format){
	if (format <= 0) return false;
	return format == numbersFormat
			|| format == verbatimFormat
			|| format == pictureFormat
			|| format == pweaveDelimiterFormat
			|| format == pweaveBlockFormat
			|| format == sweaveDelimiterFormat
			|| format == sweaveBlockFormat
			|| format == math_DelimiterFormat;
}

void LatexEditorView::selectOptionInLatexArg(QDocumentCursor &cur) {
	QString startDelims = "[{, \t\n";
	int startCol = cur.columnNumber();
	while (!cur.atLineStart() && !startDelims.contains(cur.previousChar())) {
		cur.movePosition(1, QDocumentCursor::PreviousCharacter);
	}
	cur.setColumnNumber(startCol, QDocumentCursor::KeepAnchor);
	QString endDelims = "]}, \t\n";
	while (!cur.atLineEnd() && !endDelims.contains(cur.nextChar())) {
		cur.movePosition(1, QDocumentCursor::NextCharacter, QDocumentCursor::KeepAnchor);
	}
}

void LatexEditorView::temporaryHighlight(QDocumentCursor cur) {
	if (!cur.hasSelection()) return;
	REQUIRE(editor->document());

	QDocumentLine docLine(cur.selectionStart().line());
	if (cur.endLineNumber() != cur.startLineNumber()) {
		// TODO: proper highlighting of selections spanning more than one line. Currently just highlight to the end of the first line:
		cur = cur.selectionStart();
		cur.movePosition(1, QDocumentCursor::EndOfLine, QDocumentCursor::KeepAnchor);
	}

	QFormatRange highlight(cur.startColumnNumber(), cur.endColumnNumber()-cur.startColumnNumber(), editor->document()->getFormatId("search"));
	docLine.addOverlay(highlight);
	tempHighlightQueue.append(QPair<QDocumentLine, QFormatRange>(docLine, highlight));
	QTimer::singleShot(1000, this, SLOT(removeTemporaryHighlight()));
}

void LatexEditorView::removeTemporaryHighlight() {
	if (!tempHighlightQueue.isEmpty()) {
		QDocumentLine docLine(tempHighlightQueue.first().first);
		docLine.removeOverlay(tempHighlightQueue.first().second);
		tempHighlightQueue.removeFirst();
	}
}




void LatexEditorView::displayLineGrammarErrorsInternal(int lineNr, const QList<GrammarError>& errors){
	QDocumentLine line = document->line(lineNr);	
	foreach (const int f, grammarFormats)
		line.clearOverlays(f); 
	foreach (const GrammarError& error, errors) {
		int f;
		if (error.error == GET_UNKNOWN) f = grammarMistakeFormat;
		else {
			int index = (int)(error.error) - 1;
			REQUIRE(index < grammarFormats.size());
			if (grammarFormatsDisabled[index]) continue;
			f = grammarFormats[index];
		}
		if (config->hideNonTextGrammarErrors && (isNonTextFormat(line.getFormatAt(error.offset)) || isNonTextFormat(line.getFormatAt(error.offset+error.length-1))))
			continue;
		line.addOverlay(QFormatRange(error.offset,error.length,f));
	}
}

void LatexEditorView::lineGrammarChecked(const void* doc, const void* lineHandle, int lineNr, const QList<GrammarError>& errors){
	if (doc != this->document) return;
	lineNr = document->indexOf(const_cast<QDocumentLineHandle*>(static_cast<const QDocumentLineHandle*>(lineHandle)), lineNr);
	if (lineNr < 0) return; //line already deleted
	displayLineGrammarErrorsInternal(lineNr, errors);
	document->line(lineNr).setCookie(QDocumentLine::GRAMMAR_ERROR_COOKIE, QVariant::fromValue<QList<GrammarError> >(errors));
}

void LatexEditorView::setGrammarOverlayDisabled(int type, bool newValue){
	REQUIRE(type >= 0 && type < grammarFormatsDisabled.size());
	if (newValue == grammarFormatsDisabled[type]) return;
	grammarFormatsDisabled[type] = newValue;
}

void LatexEditorView::updateGrammarOverlays(){
	for (int i=0;i<document->lineCount();i++) 
		displayLineGrammarErrorsInternal(i, document->line(i).getCookie(QDocumentLine::GRAMMAR_ERROR_COOKIE).value<QList<GrammarError> >());
	editor->viewport()->update();
}

void LatexEditorView::viewActivated(){
	if (!LatexEditorView::completer) return;
}

QString LatexEditorView::displayName() const{
	return (!editor || editor->fileName().isEmpty() ? tr("untitled") : editor->name());
}


void LatexEditorView::complete(int flags) {
	if (!LatexEditorView::completer) return;
	setFocus();
	LatexEditorView::completer->complete(editor,LatexCompleter::CompletionFlags(flags));
}
void LatexEditorView::jumpChangePositionBackward() {
	if (changePositions.size()==0) return;
	for (int i=changePositions.size()-1; i>=0; i--)
		if (!changePositions[i].isValid()) {
			changePositions.removeAt(i);
			if (i<=curChangePos) curChangePos--;
		}
	if (curChangePos >= changePositions.size()-1) curChangePos = changePositions.size()-1;
	else if (curChangePos>=0 && curChangePos < changePositions.size()-1) curChangePos++;
	else if (editor->cursor().line().handle()==changePositions.first().dlh()) curChangePos=1;
	else curChangePos=0;
	if (curChangePos>=0 && curChangePos < changePositions.size())
		editor->setCursorPosition(changePositions[curChangePos].lineNumber(),changePositions[curChangePos].columnNumber());
}
void LatexEditorView::jumpChangePositionForward() {
	for (int i=changePositions.size()-1; i>=0; i--)
		if (!changePositions[i].isValid()) {
			changePositions.removeAt(i);
			if (i<=curChangePos) curChangePos--;
		}
	if (curChangePos>0) {
		curChangePos--;
		editor->setCursorPosition(changePositions[curChangePos].lineNumber(),changePositions[curChangePos].columnNumber());
	}
}
void LatexEditorView::jumpToBookmark(int bookmarkNumber) {
	int markLine=editor->document()->findNextMark(bookMarkId(bookmarkNumber),editor->cursor().lineNumber(),editor->cursor().lineNumber()-1);
	if (markLine>=0) {
		emit saveCurrentCursorToHistoryRequested();
		editor->setCursorPosition(markLine,0);
		editor->setFocus();
	}
}

void LatexEditorView::removeBookmark(QDocumentLineHandle *dlh,int bookmarkNumber){
	if(!dlh)
		return;
	int rmid=bookMarkId(bookmarkNumber);
	if(hasBookmark(dlh,bookmarkNumber)) {
		document->removeMark(dlh,rmid);
		emit bookmarkRemoved(dlh);
	}
}

void LatexEditorView::removeBookmark(int lineNr,int bookmarkNumber){
	removeBookmark(document->line(lineNr).handle(), bookmarkNumber);
}

void LatexEditorView::addBookmark(int lineNr,int bookmarkNumber){
    int rmid=bookMarkId(bookmarkNumber);
    if (bookmarkNumber>=0)
        document->line(document->findNextMark(rmid)).removeMark(rmid);
    if(!document->line(lineNr).hasMark(rmid))
        document->line(lineNr).addMark(rmid);
}
bool LatexEditorView::hasBookmark(int lineNr,int bookmarkNumber){
    int rmid=bookMarkId(bookmarkNumber);
    return document->line(lineNr).hasMark(rmid);
}

bool LatexEditorView::hasBookmark(QDocumentLineHandle *dlh,int bookmarkNumber){
    if(!dlh)
        return false;
    int rmid=bookMarkId(bookmarkNumber);
    QList<int> m_marks=document->marks(dlh);
    return m_marks.contains(rmid);
}

bool LatexEditorView::toggleBookmark(int bookmarkNumber, QDocumentLine line) {
	if (!line.isValid()) line = editor->cursor().line();
	int rmid=bookMarkId(bookmarkNumber);
	if (line.hasMark(rmid)) {
		line.removeMark(rmid);
		emit bookmarkRemoved(line.handle());
        return false;
	}
    if (bookmarkNumber>=0){
        int ln=editor->document()->findNextMark(rmid);
        if(ln>=0){
            editor->document()->line(ln).removeMark(rmid);
            emit bookmarkRemoved(editor->document()->line(ln).handle());
        }
    }
    for (int i=-1; i<10; i++) {
        int rmid=bookMarkId(i);
		if(line.hasMark(rmid)){
			line.removeMark(rmid);
			emit bookmarkRemoved(line.handle());
        }
    }
	line.addMark(rmid);
	emit bookmarkAdded(line.handle(),bookmarkNumber);
    return true;
}
bool LatexEditorView::gotoLineHandleAndSearchCommand(const QDocumentLineHandle* dlh, const QSet<QString>& searchFor, const QString& id){
	if (!dlh) return false;
	int ln=dlh->document()->indexOf(dlh);
	if (ln<0) return false;
	QString lineText = dlh->document()->line(ln).text();
	int col = 0;
	foreach (const QString &cmd, searchFor) {
		col = lineText.indexOf(cmd+"{"+id);
		if (col < 0) col = lineText.indexOf(QRegExp(QRegExp::escape(cmd)+"\\[[^\\]{}()\\\\]+\\]\\{"+QRegExp::escape(id))); //for \command[options]{id}
		if (col >= 0) {
			col += cmd.length()+1;
			break;
		}
	}
	//Q_ASSERT(col >= 0);
	if (col < 0) col = 0;
	editor->setCursorPosition(ln, col, false);
	editor->ensureCursorVisible(QEditor::Navigation);
	return true;

}

bool LatexEditorView::gotoToLabel(const QString& label){
	int cnt=document->countLabels(label);
	if (cnt==0) return false;
	QMultiHash<QDocumentLineHandle*,int> result=document->getLabels(label);
	if (result.isEmpty()) return false;
	return gotoLineHandleAndSearchCommand(result.keys().first(), LatexParser::getInstance().possibleCommands["%label"], label);
}

bool LatexEditorView::gotoToBibItem(const QString &bibId) {
	// only supports local bibitems. BibTeX has to be handled on a higher level
	QMultiHash<QDocumentLineHandle*,int> result=document->getBibItems(bibId);
	if (result.isEmpty()) return false;
	return gotoLineHandleAndSearchCommand(result.keys().first(), LatexParser::getInstance().possibleCommands["%bibitem"], bibId);
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
bool LatexEditorView::setSpeller(const QString &name) {
	if (!spellerManager) return false;
	
	useDefaultSpeller = (name == "<default>");
	
	SpellerUtility* su;
	if (spellerManager->hasSpeller(name)) {
		su = spellerManager->getSpeller(name);
		if (!su) return false;
	} else {
		su = spellerManager->getSpeller(spellerManager->defaultSpellerName());
		REQUIRE_RET(su, false);
		useDefaultSpeller = true;
	}
	if (su == speller) return true; // nothing to do

	if (speller) {
		disconnect(speller, SIGNAL(aboutToDelete()), this, SLOT(reloadSpeller()));
		disconnect(speller, SIGNAL(ignoredWordAdded(QString)), this, SLOT(spellRemoveMarkers(QString)));
	}
	speller = su;
	connect(speller, SIGNAL(aboutToDelete()), this, SLOT(reloadSpeller()));
	connect(speller, SIGNAL(ignoredWordAdded(QString)), this, SLOT(spellRemoveMarkers(QString)));
	emit spellerChanged(name);
	
	if (document) {
		document->updateMagicComment("spellcheck", speller->name());
	}
	
	// force new highlighting
	documentContentChanged(0,editor->document()->lines());
	return true;
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

void LatexEditorView::updatePackageFormats(){
    for (int i=0; i<editor->document()->lines(); i++) {
        QList<QFormatRange> li=editor->document()->line(i).getOverlays();
        QString curLineText=editor->document()->line(i).text();
        for (int j=0; j<li.size(); j++)
			if (li[j].format == packagePresentFormat || li[j].format == packageMissingFormat || li[j].format == packageUndefinedFormat){
				int newFormat = packageUndefinedFormat;
				if (!latexPackageList->isEmpty()) {
					newFormat = latexPackageList->contains(curLineText.mid(li[j].offset,li[j].length))?packagePresentFormat:packageMissingFormat;
				}
                if (newFormat!=li[j].format) {
                    editor->document()->line(i).removeOverlay(li[j]);
                    li[j].format=newFormat;
                    editor->document()->line(i).addOverlay(li[j]);
                }
            }
	}
}

void LatexEditorView::clearLogMarks() {
	setLogMarksVisible(false);
	logEntryToLine.clear();
	logEntryToMarkID.clear();
	lineToLogEntries.clear();
}

void LatexEditorView::addLogEntry(int logEntryNumber, int lineNumber, int markID) {
	QDocumentLine l=editor->document()->line(lineNumber);
	lineToLogEntries.insert(l.handle(), logEntryNumber);
	logEntryToLine[logEntryNumber] = l.handle();
	logEntryToMarkID[logEntryNumber] = markID;
}

void LatexEditorView::setLogMarksVisible(bool visible) {
	if (visible) {
		foreach(int logEntryNumber, logEntryToMarkID.keys()) {
			int markID = logEntryToMarkID[logEntryNumber];
			if (markID >= 0) {
				QDocumentLine(logEntryToLine[logEntryNumber]).addMark(markID);
			}
		}
	} else {
		int errorMarkID = QLineMarksInfoCenter::instance()->markTypeId("error");
		int warningMarkID = QLineMarksInfoCenter::instance()->markTypeId("warning");
		int badboxMarkID = QLineMarksInfoCenter::instance()->markTypeId("badbox");
		editor->document()->removeMarks(errorMarkID);
		editor->document()->removeMarks(warningMarkID);
		editor->document()->removeMarks(badboxMarkID);
	}
}

void LatexEditorView::updateCitationFormats(){
    for (int i=0; i<editor->document()->lines(); i++) {
        QList<QFormatRange> li=editor->document()->line(i).getOverlays();
        QString curLineText=editor->document()->line(i).text();
        for (int j=0; j<li.size(); j++)
            if (li[j].format == citationPresentFormat || li[j].format == citationMissingFormat){
                int newFormat=document->bibIdValid(curLineText.mid(li[j].offset,li[j].length))?citationPresentFormat:citationMissingFormat;
                if (newFormat!=li[j].format) {
                    editor->document()->line(i).removeOverlay(li[j]);
                    li[j].format=newFormat;
                    editor->document()->line(i).addOverlay(li[j]);
                }
            }
    }
}

bool LatexEditorView::containsBibTeXId(QString id){
    return document->bibIdValid(id);
}

int LatexEditorView::bookMarkId(int bookmarkNumber) {
    if (bookmarkNumber==-1) return  QLineMarksInfoCenter::instance()->markTypeId("bookmark"); //unnumbered mark
    else return QLineMarksInfoCenter::instance()->markTypeId("bookmark"+QString::number(bookmarkNumber));
    //return document->bookMarkId(bookmarkNumber);
}

void LatexEditorView::setLineMarkToolTip(const QString& tooltip){
	lineMarkPanel->setToolTipForTouchedMark(tooltip);
}

int LatexEditorView::environmentFormat, LatexEditorView::referencePresentFormat, LatexEditorView::referenceMissingFormat, LatexEditorView::referenceMultipleFormat, LatexEditorView::citationMissingFormat, LatexEditorView::citationPresentFormat,LatexEditorView::structureFormat,LatexEditorView::packageMissingFormat,LatexEditorView::packagePresentFormat,LatexEditorView::packageUndefinedFormat,
    LatexEditorView::wordRepetitionFormat, LatexEditorView::wordRepetitionLongRangeFormat, LatexEditorView::badWordFormat, LatexEditorView::grammarMistakeFormat, LatexEditorView::grammarMistakeSpecial1Format, LatexEditorView::grammarMistakeSpecial2Format, LatexEditorView::grammarMistakeSpecial3Format, LatexEditorView::grammarMistakeSpecial4Format,
	LatexEditorView::numbersFormat, LatexEditorView::verbatimFormat, LatexEditorView::pictureFormat, LatexEditorView::math_DelimiterFormat,
	LatexEditorView::pweaveDelimiterFormat, LatexEditorView::pweaveBlockFormat, LatexEditorView::sweaveDelimiterFormat, LatexEditorView::sweaveBlockFormat;
int LatexEditorView::syntaxErrorFormat,LatexEditorView::preEditFormat;
int LatexEditorView::deleteFormat,LatexEditorView::insertFormat,LatexEditorView::replaceFormat;

QList<int> LatexEditorView::grammarFormats;
QVector<bool> LatexEditorView::grammarFormatsDisabled;
QList<int> LatexEditorView::formatsList;

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
	editor->setFlag(QEditor::SmoothScrolling, config->smoothScrolling);
	editor->setFlag(QEditor::AutoInsertLRM, config->autoInsertLRM);
	editor->setFlag(QEditor::BidiVisualColumnMode, config->visualColumnMode);
	//TODO: parenmatch
	editor->setFlag(QEditor::AutoCloseChars, config->parenComplete);
	editor->setFlag(QEditor::SilentReloadOnExternalChanges, config->silentReload);
	editor->setCursorSurroundingLines(config->cursorSurroundLines);
	editor->setCursorBold(config->boldCursor);
	lineMarkPanelAction->setChecked((config->showlinemultiples!=0) ||config->folding||config->showlinestate);
	lineNumberPanelAction->setChecked(config->showlinemultiples!=0);
	lineFoldPanelAction->setChecked(config->folding);
	lineChangePanelAction->setChecked(config->showlinestate);
	statusPanelAction->setChecked(config->showcursorstate);
	editor->setDisplayModifyTime(false);
	searchReplacePanel->setUseLineForSearch(config->useLineForSearch);
	searchReplacePanel->setSearchOnlyInSelection(config->searchOnlyInSelection);
	QDocument::setShowSpaces(config->showWhitespace?(QDocument::ShowTrailing | QDocument::ShowLeading | QDocument::ShowTabs):QDocument::ShowNone);
	QDocument::setTabStop(config->tabStop);
	QDocument::setLineSpacingFactor(config->lineSpacingPercent / 100.0);

	SynChecker.setErrFormat(syntaxErrorFormat);
    editor->m_preEditFormat=preEditFormat;
	
	QDocument::setWorkAround(QDocument::DisableFixedPitchMode, config->hackDisableFixedPitch);
	QDocument::setWorkAround(QDocument::DisableWidthCache, config->hackDisableWidthCache);
	QDocument::setWorkAround(QDocument::DisableLineCache, config->hackDisableLineCache);

	QDocument::setWorkAround(QDocument::ForceQTextLayout, config->hackRenderingMode == 1);
	QDocument::setWorkAround(QDocument::ForceSingleCharacterDrawing, config->hackRenderingMode == 2);
}

void LatexEditorView::updateFormatSettings(){
	static bool formatsLoaded = false;
	if (!formatsLoaded) {
		REQUIRE(QDocument::defaultFormatScheme());
#define F(n) &n##Format, #n, 
		const void * formats[] = {F(environment)
															F(referenceMultiple) F(referencePresent) F(referenceMissing)
															F(citationPresent) F(citationMissing)
															F(packageMissing) F(packagePresent)
															&packageUndefinedFormat, "normal",
															&syntaxErrorFormat, "latexSyntaxMistake", //TODO: rename all to xFormat, "x"
															F(structure)
															&deleteFormat, "diffDelete",
															&insertFormat, "diffAdd",
															&replaceFormat, "diffReplace",
															F(wordRepetition) F(wordRepetitionLongRange) F(badWord)
															F(grammarMistake)
															F(grammarMistakeSpecial1) F(grammarMistakeSpecial2) F(grammarMistakeSpecial3) F(grammarMistakeSpecial4)
															F(numbers) F(verbatim) F(picture)
															&pweaveDelimiterFormat, "pweave-delimiter",
															&pweaveBlockFormat, "pweave-block",
															&sweaveDelimiterFormat, "sweave-delimiter",
															&sweaveBlockFormat, "sweave-block",
															&math_DelimiterFormat, "math-delimiter",
															&preEditFormat,"preedit",
															0, 0
														 };
#undef F
		const void ** temp = formats;
		while (*temp) {
			int * c = (static_cast<int*>(const_cast<void*>(*temp)));
			*c = QDocument::defaultFormatScheme()->id(QString(static_cast<const char*>(*(temp+1))));
			Q_ASSERT(c != 0);
			temp+=2;
		}
		//int f=QDocument::formatFactory()->id("citationMissing");
		formatsLoaded = true;
		grammarFormats << wordRepetitionFormat << wordRepetitionLongRangeFormat << badWordFormat << grammarMistakeFormat << grammarMistakeSpecial1Format << grammarMistakeSpecial2Format << grammarMistakeSpecial3Format << grammarMistakeSpecial4Format; //don't change the order, it corresponds to GrammarErrorType
		grammarFormatsDisabled.resize(9);
		grammarFormatsDisabled.fill(false);
		formatsList<<SpellerUtility::spellcheckErrorFormat<<referencePresentFormat<<citationPresentFormat<<referenceMissingFormat;
		formatsList<<referenceMultipleFormat<<citationMissingFormat<<packageMissingFormat<<packagePresentFormat<<packageUndefinedFormat<<environmentFormat<<syntaxErrorFormat;
		formatsList<<wordRepetitionFormat<<structureFormat<<insertFormat<<deleteFormat<<replaceFormat;
	}	
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

void LatexEditorView::openPackageDocumentation(QString package){
	QString command;
	if (package.isEmpty()) {
		QAction *act = qobject_cast<QAction*>(sender());
		if (!act) return;
		package = act->data().toString();
	}
	if (package.contains("#")) {
		int i = package.indexOf("#");
		command = package.mid(i+1);
		package = package.left(i);
	}
	// replace some package denominations
	if (package=="latex-document" || package=="latex-dev" || package=="latex-mathsymbols")
		package = "latex2e";
	if (package=="class-scrartcl,scrreprt,scrbook")
		package = "scrartcl";
	if (package.startsWith("class-"))
		package = package.mid(6);
	if (!package.isEmpty()) {
		if(config->texdocHelpInInternalViewer) {
			QString docfile = Help::packageDocFile(package);
			if (docfile.isEmpty())
				return;
			if (docfile.endsWith(".pdf"))
				emit openInternalDocViewer(docfile, command);
			else
				Help::instance()->viewTexdoc(package); // fallback e.g. for dvi
		}else{
			Help::instance()->viewTexdoc(package);
		}
	}
}

void LatexEditorView::emitChangeDiff(){
	QAction *act = qobject_cast<QAction*>(sender());
	QPoint pt=act->data().toPoint();
	emit changeDiff(pt);
}

void LatexEditorView::emitGotoDefinitionFromAction() {
	QDocumentCursor c;
	QAction *act = qobject_cast<QAction *>(sender());
	if (act) {
		c = act->data().value<QDocumentCursor>();
	}
	emit gotoDefinition(c);
}

void LatexEditorView::emitSyncPDFFromAction() {
	QDocumentCursor c;
	QAction *act = qobject_cast<QAction *>(sender());
	if (act) {
		c = act->data().value<QDocumentCursor>();
	}
	emit syncPDFRequested(c);
}

void LatexEditorView::lineMarkClicked(int line) {
	QDocumentLine l=editor->document()->line(line);
	if (!l.isValid()) return;
	//remove old mark (when possible)
	for (int i=-1; i<10; i++)
		if (l.hasMark(bookMarkId(i))) {
			l.removeMark(bookMarkId(i));
			emit bookmarkRemoved(l.handle());
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
	//add unused mark (1,2 .. 9,0) (when possible)
	for (int i=1; i<=10; i++) {
		if (editor->document()->findNextMark(bookMarkId(i%10))<0) {
			l.addMark(bookMarkId(i%10));
			emit bookmarkAdded(l.handle(),i);
			return;
		}
	}
	l.addMark(bookMarkId(-1));
    emit bookmarkAdded(l.handle(),-1);
}
void LatexEditorView::lineMarkToolTip(int line, int mark){
	if (line < 0 || line>=editor->document()->lines()) return;
	int errorMarkID = QLineMarksInfoCenter::instance()->markTypeId("error");
	int warningMarkID = QLineMarksInfoCenter::instance()->markTypeId("warning");
	int badboxMarkID = QLineMarksInfoCenter::instance()->markTypeId("badbox");
	if (mark != errorMarkID && mark != warningMarkID && mark != badboxMarkID) return;
	QList<int> errors = lineToLogEntries.values(editor->document()->line(line).handle());
	if (!errors.isEmpty())
		emit showMarkTooltipForLogMessage(errors);
}
void LatexEditorView::checkNextLine(QDocumentLineHandle *dlh,bool clearOverlay,int ticket){
	Q_ASSERT_X(dlh!=0,"checkNextLine","empty dlh used in checkNextLine");
	if(dlh->getRef()>1 && dlh->getCurrentTicket()==ticket){
		StackEnvironment env;
		QVariant envVar=dlh->getCookie(QDocumentLine::STACK_ENVIRONMENT_COOKIE);
		if(envVar.isValid())
			env=envVar.value<StackEnvironment>();
		int index = document->indexOf(dlh);
		if (index == -1) return; //deleted
		REQUIRE(dlh->document() == document);
		if (index + 1 >= document->lines()) {
			//remove old errror marker
			if(unclosedEnv.id!=-1){
				unclosedEnv.id = -1;
				int unclosedEnvIndex = document->indexOf(unclosedEnv.dlh);
				if (unclosedEnvIndex >= 0 && unclosedEnv.dlh->getCookie(QDocumentLine::UNCLOSED_ENVIRONMENT_COOKIE).isValid()){
					StackEnvironment env;
					Environment newEnv;
					newEnv.name="normal";
					newEnv.id=1;
					env.push(newEnv);
					if (unclosedEnvIndex >= 1) {
						QDocumentLineHandle *prev = document->line(unclosedEnvIndex-1).handle();
						QVariant result=prev->getCookie(QDocumentLine::STACK_ENVIRONMENT_COOKIE);
						if(result.isValid())
							env=result.value<StackEnvironment>();
					} 
					SynChecker.putLine(unclosedEnv.dlh, env, true);
				}
			}
			if(env.size()>1){
				//at least one env has not been closed
				Environment environment=env.top();
				unclosedEnv=env.top();
				SynChecker.markUnclosedEnv(environment);
			}
			return;
		}
		SynChecker.putLine(document->line(index+1).handle(), env, clearOverlay);
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
		line.clearOverlays(structureFormat);
		foreach (const int f, grammarFormats)
			line.clearOverlays(f);
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
			if (changePositions.first().dlh()!=startline.handle()) add=true;
			else changePositions.first().setColumnNumber(editor->cursor().columnNumber());
		} else if (curChangePos>=changePositions.size()-1) {
			if (changePositions.last().dlh()!=startline.handle()) add=true;
			else changePositions.last().setColumnNumber(editor->cursor().columnNumber());
		}  else if (changePositions[curChangePos].dlh()==startline.handle()) changePositions[curChangePos].setColumnNumber(editor->cursor().columnNumber());
		else if (changePositions[curChangePos+1].dlh()==startline.handle()) changePositions[curChangePos+1].setColumnNumber(editor->cursor().columnNumber());
		else add=true;
		if (add) {
			curChangePos=-1;
			changePositions.insert(0,CursorPosition(editor->document()->cursor(linenr, editor->cursor().columnNumber())));
			if (changePositions.size()>20) changePositions.removeLast();
		}
	}
	
	if (autoPreviewCursor.size() > 0) {
		for (int i=0;i<autoPreviewCursor.size();i++) {
			const QDocumentCursor& c = autoPreviewCursor[i];
			if (c.lineNumber() >= linenr && c.anchorLineNumber() < linenr+count)
				emit showPreview(c); //may modify autoPreviewCursor
		}
		
	}
	
	// checking
	if (!QDocument::defaultFormatScheme()) return;
	if (!config->realtimeChecking) return; //disable all => implicit disable environment color correction (optimization)
	if(!editor->languageDefinition())
	    return;
	if (!checkedLanguages.contains(editor->languageDefinition()->language())) return;
	
	if (config->inlineGrammarChecking) {
		QList<LineInfo> changedLines;
		int lookBehind = 0;
		for (;linenr - lookBehind >= 0; lookBehind++) 
			if (editor->document()->line(linenr - lookBehind).firstChar() == -1) break;
		if (lookBehind > 0) lookBehind--;
		if (lookBehind > linenr) lookBehind = linenr;
		
		LIST_RESERVE(changedLines, linenr+count+lookBehind+1);
		int truefirst = linenr - lookBehind;
		for (int i=linenr - lookBehind; i<editor->document()->lineCount(); i++) {
			QDocumentLine line = editor->document()->line(i);
			if (!line.isValid()) break;
			LineInfo temp; 
			temp.line = line.handle();
			temp.text = line.text();
			changedLines << temp;
			if (line.firstChar() == -1) {
				emit linesChanged(speller->name(), document, changedLines, truefirst);
				truefirst += changedLines.size();
				changedLines.clear();
				if (i >= linenr+count) break;
			}		
		}
		if (!changedLines.isEmpty())
			emit linesChanged(speller->name(), document, changedLines, truefirst);
		
	}
	
	Q_ASSERT(speller);
	for (int i=linenr; i<linenr+count; i++) {
		QDocumentLine line = editor->document()->line(i);
		if (!line.isValid()) continue;
		
		//remove all overlays used for latex things, in descending frequency
        line.clearOverlays(formatsList); //faster as it avoids multiple lock/unlock operations
		
		bool addedOverlaySpellCheckError = false;
		bool addedOverlayReference = false;
		bool addedOverlayCitation = false;
		bool addedOverlayEnvironment = false;
		bool addedOverlayStyleHint = false;
		bool addedOverlayStructure = false;
        bool addedOverlayPackage = false;
		
		// diff presentation
		QVariant cookie=line.getCookie(QDocumentLine::DIFF_LIST_COOCKIE);
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

            QVector<int>fmts=line.getFormats();
            for(int i=0;i<text.length() && i < fmts.size();i++){
                if(fmts[i]==verbatimFormat){
                    text[i]=QChar(' ');
                }
            }
            SynChecker.putLine(line.handle(),env,false);
		}
		
		
		if (line.length()<=3) continue;
		//if (!config->realtimespellchecking) continue;
		
		
		QString lineText = line.text();
		int status;
		const LatexParser& lp = LatexParser::getInstance();
		LatexReader lr(LatexParser::getInstance(), lineText);
		while ((status=lr.nextWord(false))){
			// hack to color the environment given in \begin{environment}...
			if (lp.structureCommands.contains(lr.lastCommand)){
				if(line.getFormatAt(lr.wordStartIndex)==verbatimFormat) continue;
				//QString secName=extractSectionName(lineText.mid(lr.lr.wordStartIndex),true);
				//line.addOverlay(QFormatRange(lr.wordStartIndex,secName.length(),structureFormat));
				QStringList result;
				QList<int> starts;
				LatexParser::resolveCommandOptions(lineText,lr.wordStartIndex-1,result,&starts);
				for(int j=0;j<starts.count() && j<2;j++){
					QString text=result.at(j);
					line.addOverlay(QFormatRange(starts.at(j)+1,text.length()-2,structureFormat));
					if(text.startsWith("{")) break;
				}
				addedOverlayStructure = true;
			}
			if (status==LatexReader::NW_ENVIRONMENT) {
				if(line.getFormatAt(lr.wordStartIndex)==verbatimFormat) continue;
				line.addOverlay(QFormatRange(lr.wordStartIndex,lr.index-lr.wordStartIndex,environmentFormat));
				QRegExp rx("[ ]*(\\[.*\\])*\\{.+\\}");
				rx.setMinimal(true);
				int l=rx.indexIn(lineText,lr.index);
				if (l==lr.index+1) lr.index=lr.index+rx.cap(0).length();
				addedOverlayEnvironment = true;
			}
			if (status==LatexReader::NW_REFERENCE && config->inlineReferenceChecking) {
				if(line.getFormatAt(lr.wordStartIndex)==verbatimFormat) continue;
				QString ref=lr.word;//lineText.mid(lr.wordStartIndex,lr.index-lr.wordStartIndex);
				int cnt=document->countLabels(ref);
				if(cnt>1) {
					line.addOverlay(QFormatRange(lr.wordStartIndex,lr.index-lr.wordStartIndex,referenceMultipleFormat));
				}else if (cnt==1) line.addOverlay(QFormatRange(lr.wordStartIndex,lr.index-lr.wordStartIndex,referencePresentFormat));
				else line.addOverlay(QFormatRange(lr.wordStartIndex,lr.index-lr.wordStartIndex,referenceMissingFormat));
				addedOverlayReference = true;
			}
			if (status==LatexReader::NW_LABEL && config->inlineReferenceChecking) {
				if(line.getFormatAt(lr.wordStartIndex)==verbatimFormat) continue;
				QString ref=lr.word;//lineText.mid(lr.wordStartIndex,lr.index-lr.wordStartIndex);

				int cnt=document->countLabels(ref);
				if(cnt>1) {
					line.addOverlay(QFormatRange(lr.wordStartIndex,lr.index-lr.wordStartIndex,referenceMultipleFormat));
				}else line.addOverlay(QFormatRange(lr.wordStartIndex,lr.index-lr.wordStartIndex,referencePresentFormat));
				// look for corresponding reeferences and adapt format respectively
				//containedLabels->updateByKeys(QStringList(ref),containedReferences);
				document->updateRefsLabels(ref);
				addedOverlayReference = true;
			}
			if (status==LatexReader::NW_CITATION && config->inlineCitationChecking) {
					QStringList citations=lr.word.split(",");
					int pos=lr.wordStartIndex;
					foreach ( const QString &cit, citations) {
						QString rcit =  trimLeft(cit); // left spaces are ignored by \cite, right space not
						//check and highlight
                        if(document->bibIdValid(rcit))
							line.addOverlay(QFormatRange(pos+cit.length()-rcit.length(),rcit.length(),citationPresentFormat));
						else
							line.addOverlay(QFormatRange(pos+cit.length()-rcit.length(),rcit.length(),citationMissingFormat));
						pos+=cit.length()+1;
					}
				addedOverlayCitation = true;
			}
			if (status==LatexReader::NW_PACKAGE && config->inlinePackageChecking) {
                QStringList packages=lr.word.split(",");
                int pos=lr.wordStartIndex;
                QString preambel;
                if(lr.lastCommand.endsWith("theme")){ // special treatment for  \usetheme
                    preambel=lr.lastCommand;
                    preambel.remove(0,4);
                    preambel.prepend("beamer");
                }
                foreach ( const QString &pck, packages) {
                    QString rpck =  trimLeft(pck); // left spaces are ignored by \cite, right space not
                    //check and highlight
					if (latexPackageList->isEmpty())
						line.addOverlay(QFormatRange(pos+pck.length()-rpck.length(),rpck.length(),packageUndefinedFormat));
					else if(latexPackageList->contains(preambel+rpck))
                        line.addOverlay(QFormatRange(pos+pck.length()-rpck.length(),rpck.length(),packagePresentFormat));
                    else
                        line.addOverlay(QFormatRange(pos+pck.length()-rpck.length(),rpck.length(),packageMissingFormat));
                    pos+=pck.length()+1;
                }
                addedOverlayPackage = true;
            }
			if (status==LatexReader::NW_COMMENT) break;
			if (status==LatexReader::NW_TEXT && config->inlineSpellChecking && lr.word.length()>=3 && speller
					&& (!config->hideNonTextSpellingErrors || (!isNonTextFormat(line.getFormatAt(lr.wordStartIndex)) && !isNonTextFormat(line.getFormatAt(lr.index-1)) ))
					&& !speller->check(lr.word) ) {
				if(lr.word.endsWith('.')) lr.index--;
				line.addOverlay(QFormatRange(lr.wordStartIndex,lr.index-lr.wordStartIndex,SpellerUtility::spellcheckErrorFormat));
				addedOverlaySpellCheckError = true;
			}
		}// while
		
		//update wrapping if the an overlay changed the width of the text
		//TODO: should be handled by qce to be consistent (with syntax check and search)
		if (!editor->document()->getFixedPitch() && editor->flag(QEditor::LineWrap)) {
			bool updateWrapping = false;
			QFormatScheme* ff = QDocument::defaultFormatScheme();
			REQUIRE(ff);
			updateWrapping |= addedOverlaySpellCheckError && ff->format(SpellerUtility::spellcheckErrorFormat).widthChanging();
			updateWrapping |= addedOverlayReference && (ff->format(referenceMissingFormat).widthChanging() || ff->format(referencePresentFormat).widthChanging() || ff->format(referenceMultipleFormat).widthChanging());
			updateWrapping |= addedOverlayCitation && (ff->format(citationPresentFormat).widthChanging() || ff->format(citationMissingFormat).widthChanging());
            updateWrapping |= addedOverlayPackage && (ff->format(packagePresentFormat).widthChanging() || ff->format(packageMissingFormat).widthChanging());
			updateWrapping |= addedOverlayEnvironment && ff->format(environmentFormat).widthChanging();
			updateWrapping |= addedOverlayStyleHint && ff->format(wordRepetitionFormat).widthChanging();
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
		if (changePositions[i].dlh()==l)
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
		if (action->text().isEmpty()) editor->cursor().removeSelectedText();
		else editor->write(action->text());
		editor->setCursor(editor->cursor()); //to remove selection range
	}
}
void LatexEditorView::spellCheckingAlwaysIgnore() {
	if (speller && editor && editor->cursor().hasSelection() && (editor->cursor().selectedText()==defaultInputBinding->lastSpellCheckedWord)) {
		QString newToIgnore = editor->cursor().selectedText();
		speller->addToIgnoreList(newToIgnore);
	}
}
void LatexEditorView::addListToContextMenu(const QStringList& list, bool italic, const char* action){
	if (list.isEmpty()) return;
	QMenu* contextMenu = defaultInputBinding->contextMenu;
	if (!contextMenu) return;
	QAction* before=0;
	if (!contextMenu->actions().isEmpty()) before=contextMenu->actions()[0];
	
	QFont correctionFont;
	correctionFont.setBold(true);
	correctionFont.setItalic(italic);
	for (int i=0; i<list.size(); i++) {
		QAction* aReplacement=new QAction(list[i],contextMenu);
		aReplacement->setFont(correctionFont);
		connect(aReplacement,SIGNAL(triggered()),this,action);
		contextMenu->insertAction(before,aReplacement);
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
	QStringList suggestions= speller->suggest(defaultInputBinding->lastSpellCheckedWord);
	addListToContextMenu(suggestions,false, SLOT(spellCheckingReplace()));
	if (repopup) {
		//    contextMenu->close();
		contextMenu->show();
	}
}
void LatexEditorView::spellRemoveMarkers(const QString& newIgnoredWord){
	REQUIRE(editor);
	//documentContentChanged(editor->cursor().lineNumber(),1);
	for (int i=0; i<editor->document()->lines(); i++) {
		QList<QFormatRange> li=editor->document()->line(i).getOverlays(SpellerUtility::spellcheckErrorFormat);
		QString curLineText=editor->document()->line(i).text();
		for (int j=0; j<li.size(); j++)
			if (latexToPlainWord(curLineText.mid(li[j].offset,li[j].length))==newIgnoredWord){
				editor->document()->line(i).removeOverlay(li[j]);
				editor->document()->line(i).setFlag(QDocumentLine::LayoutDirty,true);
			}
	}
	editor->viewport()->update();
}

void LatexEditorView::closeCompleter(){
	completer->close();
}

void LatexEditorView::reCheckSyntax(int linenr, int count){
	// expensive function ... however if \newcommand is changed valid commands become invalid and vice versa
	if(!config->inlineSyntaxChecking || !config->realtimeChecking) return;
	if(!editor->languageDefinition())
	    return;
	if (!checkedLanguages.contains(editor->languageDefinition()->language())) return; // no online checking in other files than tex

	if(linenr<0 || linenr>=editor->document()->lineCount()) linenr=0;
	QDocumentLine line=editor->document()->line(linenr);
	QDocumentLine prev;
	if (linenr > 0) prev = editor->document()->line(linenr - 1);
	int lineNrEnd = count < 0 ? editor->document()->lineCount() : qMin(count + linenr, editor->document()->lineCount());
	for (int i=linenr; i < lineNrEnd; i++) {
		Q_ASSERT(line.isValid());
		StackEnvironment env;
		getEnv(i,env);
		SynChecker.putLine(line.handle(),env,true);
		prev = line;
		line = editor->document()->line(i+1);
	}
}


/*
 * Extracts the math formula at the given cursor position including math delimiters.
 * Current limitations: the cursor needs to be on one of the delimiters. This does
 * not work for math environments
 * Returns an empty string if there is no math formula.
 */
QString LatexEditorView::extractMath(QDocumentCursor cursor) {
    if (cursor.line().getFormatAt(cursor.columnNumber())!=math_DelimiterFormat)
		return QString();
	int col = cursor.columnNumber();
	while (col > 0 && cursor.line().getFormatAt(col-1)==math_DelimiterFormat) col--;
	cursor.setColumnNumber(col);
	return parenthizedTextSelection(cursor).selectedText();
}

void LatexEditorView::showMathEnvPreview(QDocumentCursor cursor, QString command, QString environment, QPoint pos) {
    LatexParser ltxCommands=LatexParser::getInstance();
    QStringList envAliases = ltxCommands.environmentAliases.values(environment);
	if (((command=="\\begin" || command=="\\end") && envAliases.contains("math")) || command=="\\[" || command=="\\]") {
		while (!cursor.atLineStart() && cursor.nextChar()!='\\') {
			cursor.movePosition(1, QDocumentCursor::PreviousCharacter);
		}
		QString text = parenthizedTextSelection(cursor).selectedText();
		if (!text.isEmpty()) {
			m_point=editor->mapToGlobal(editor->mapFromFrame(pos));
			emit showPreview(text);
		}
	} else {
		QToolTip::hideText();
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
		QVariant var=l.getCookie(QDocumentLine::DIFF_LIST_COOCKIE);
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
	foreach (const int f, grammarFormats){
		fr = cursor.line().getOverlayAt(cursor.columnNumber(), f);
		if (fr.length>0 && fr.format==f) {
			QVariant var=l.getCookie(QDocumentLine::GRAMMAR_ERROR_COOKIE);
			if (var.isValid()){
				const QList<GrammarError>& errors = var.value<QList<GrammarError> >();
				for (int i=0;i<errors.size();i++)
					if (errors[i].offset <= cursor.columnNumber() && errors[i].offset+errors[i].length >= cursor.columnNumber()) {
						QString message=errors[i].message;
						QToolTip::showText(editor->mapToGlobal(editor->mapFromFrame(pos)),message);
						return;
					}
			}
		}
	}
	// check for latex error
	//syntax checking
	fr = cursor.line().getOverlayAt(cursor.columnNumber(),syntaxErrorFormat);
	if (fr.length>0 && fr.format==syntaxErrorFormat) {
		StackEnvironment env;
		getEnv(cursor.lineNumber(),env);
		QString text=l.text();
		if(!text.isEmpty()){
			QString message=SynChecker.getErrorAt(l.handle(),cursor.columnNumber(),env);
			QToolTip::showText(editor->mapToGlobal(editor->mapFromFrame(pos)),message);
			return;
		}
	}
	
	// do rest
	QString command, value;
	switch (LatexParser::getInstance().findContext(line, cursor.columnNumber(), command, value)){
	case LatexParser::Unknown:
		if (config->toolTipPreview) {
			QString command = extractMath(cursor);
			if (!command.isEmpty()) {
				m_point = editor->mapToGlobal(editor->mapFromFrame(pos));
				emit showPreview(command);
			} else {
				QToolTip::hideText();
			}
		}
		break;
	case LatexParser::Command:
		// workaround: The latex parser returns "\" as command if the cursor is on the brackets of \[ or \]
		// TODO: should be fixed in the parser itself
		if (command == "\\") {
			if (cursor.nextChar()=='[') command = "\\[";
			else if (cursor.nextChar()==']') command = "\\]";
		}

		if (config->toolTipPreview) {
			showMathEnvPreview(cursor, command, value, pos);
		} else {
			if(config->toolTipHelp){
				QString topic=completer->lookupWord(command);
				if(!topic.isEmpty()) QToolTip::showText(editor->mapToGlobal(editor->mapFromFrame(pos)), topic);
			}
		}
		break;
	case LatexParser::Environment:
		{
			QString text;
			if(config->toolTipHelp) {
                text = completer->lookupWord("\\begin{"+value+"}");
				if(!text.isEmpty()) QToolTip::showText(editor->mapToGlobal(editor->mapFromFrame(pos)), text);
			}
			if (text.isEmpty() && config->toolTipPreview) {
				showMathEnvPreview(cursor, command, value, pos);
			}
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
			int l=mLine->document()->indexOf(mLine);
			LatexDocument *doc=qobject_cast<LatexDocument*> (editor->document());
			if(mLine->document()!=editor->document()){
				doc=document->parent->findDocument(mLine->document());
				if(doc) mText=tr("<p style='white-space:pre'><b>Filename: %1</b>\n").arg(doc->getFileName());
			}
			if(doc)
				mText+=doc->exportAsHtml(doc->cursor(qMax(0,l-2), 0, l+2),true,true,60);
			/*for(int i=qMax(0,l-2);i<qMin(mLine->document()->lines(),l+3);i++){
		mText+=mLine->document()->line(i).text();
		if(i<l+2) mText+="\n";
	 }*/
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
    case LatexParser::Package:
        {
            QString preambel;
            if(command.endsWith("theme")){ // special treatment for  \usetheme
                preambel=command;
                preambel.remove(0,4);
                preambel.prepend("beamer");
            }
            if(latexPackageList->contains(preambel+value)){
                QToolTip::showText(editor->mapToGlobal(editor->mapFromFrame(pos)),tr("Package present"));
            } else {
				QToolTip::showText(editor->mapToGlobal(editor->mapFromFrame(pos)),tr("Package not found"));
            }
        }
        break;
    case LatexParser::Citation:;
    case LatexParser::Citation_Ext:
    {
        QString tooltip(tr("Citation correct (reading ...)"));
        QString bibID;
        // get bibID at cursor
        int col_start=cursor.columnNumber();
        if(col_start>=line.length())
            col_start=line.length()-1;
        if (QString("{,}").contains(line[col_start])) break;

        int col_stop=col_start;
        QString eow="{,";
        while(col_start>=0 && !eow.contains(line[col_start]))
            col_start--;
        eow="},";
        while(col_stop<line.length() && !eow.contains(line[col_stop]))
            col_stop++;
        bibID = trimLeft(line.mid(col_start+1,col_stop-col_start-1));

        if(!document->bibIdValid(bibID)) {
            tooltip = "<b>" + tr("Citation missing") + ":</b> " + bibID;

            if (!bibID.isEmpty() && bibID[bibID.length()-1].isSpace()) {
                tooltip.append("<br><br><i>" + tr("Warning:") +"</i> " +tr("BibTeX ID ends with space. Trailing spaces are not ignored by BibTeX."));
            }
        } else {
            if (document->isBibItem(bibID)) {
                // by bibitem defined citation
                tooltip.clear();
                QMultiHash<QDocumentLineHandle*,int> result=document->getBibItems(bibID);
                if(result.keys().isEmpty())
                    return;
                QDocumentLineHandle *mLine=result.keys().first();
                if(!mLine)
                    return;
                int l=mLine->document()->indexOf(mLine);
                LatexDocument *doc=qobject_cast<LatexDocument*> (editor->document());
                if (mLine->document()!=editor->document()) {
                    doc=document->parent->findDocument(mLine->document());
                    if (doc) tooltip=tr("<p style='white-space:pre'><b>Filename: %1</b>\n").arg(doc->getFileName());
                }
                if (doc)
                    tooltip+=doc->exportAsHtml(doc->cursor(l, 0, l+4),true,true,60);
            } else {
                // read entry in bibtex file
                if (!bibReader) {
                    bibReader=new bibtexReader(this);
                    connect(bibReader,SIGNAL(sectionFound(QString)),this,SLOT(bibtexSectionFound(QString)));
                    connect(this,SIGNAL(searchBibtexSection(QString,QString)),bibReader,SLOT(searchSection(QString,QString)));
                    bibReader->start(); //The thread is started, but it is doing absolutely nothing! Signals/slots called in the thread object are execute in the emitting thread, not the thread itself.  TODO: fix
                }
                QString file=document->findFileFromBibId(bibID);
                lastPos=pos;
                if(!file.isEmpty())
                    emit searchBibtexSection(file,bibID);
                return;
            }
        }
        QToolTip::showText(editor->mapToGlobal(editor->mapFromFrame(pos)), tooltip);
    }
		break;
	case LatexParser::Graphics:
		if(config->toolTipPreview){
			QString fname=getDocument()->getAbsoluteFilePath(value,"");
            QFileInfo fi(fname);
            if(!fi.exists()){
                fname=getDocument()->getAbsoluteFilePath(value,"png");  // try png
                fi.setFile(fname);
            }
            if(!fi.exists()){
                fname=getDocument()->getAbsoluteFilePath(value,"pdf");  // try pdf
                fi.setFile(fname);
            }
            if(!fi.exists()){
                fname=getDocument()->getAbsoluteFilePath(value,"jpg");  // try jpg
                fi.setFile(fname);
                if(!fi.exists())
                    return; // no image file found
            }
			m_point=editor->mapToGlobal(editor->mapFromFrame(pos));
			emit showImgPreview(fname);
		}
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
                    //qDebug() << lineString;
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
                    //qDebug() << lineString;
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
		QStringList lines;
		for (int i=startLine; i <= endLine; i++)
			lines << doc->line(i).text();
		lines = joinLinesExceptCommentsAndEmptyLines(lines);
		lines = splitLines(lines, newLength, breakChars);

		QDocumentCursor vCur = doc->cursor(startLine, 0, endLine, doc->line(endLine).length());
		editor->insertText(vCur, lines.join("\n"));
		editor->setCursor(cur);
		return;
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
		QVariant result=prev.getCookie(QDocumentLine::STACK_ENVIRONMENT_COOKIE);
		if(result.isValid())
			env=result.value<StackEnvironment>();
	}
}

/*
 * If the cursor is at the border of a parenthesis, this returns a QDocumentCursor with a selection of the parenthized text.
 * Otherwise, a default QDocumentCursor is returned.
 */
QDocumentCursor LatexEditorView::parenthizedTextSelection(const QDocumentCursor &cursor, bool includeParentheses) {
	QDocumentCursor from, to;
	cursor.getMatchingPair(from, to);
	if (!from.hasSelection() || !to.hasSelection()) return QDocumentCursor();
	QDocumentCursor::sort(from, to);
	if (includeParentheses) {
		return QDocumentCursor(from.selectionStart(), to.selectionEnd());
	} else {
		return QDocumentCursor(from.selectionStart(), to.selectionEnd());
	}
}

void LatexEditorView::triggeredThesaurus(){
	QAction *act = qobject_cast<QAction*>(sender());
	QPoint pt=act->data().toPoint();
	emit thesaurus(pt.x(),pt.y());
}

void LatexEditorView::changeSpellingDict(const QString &name) {
	QString similarName;
	if (spellerManager->hasSpeller(name)) {
		setSpeller(name);
	} else if (spellerManager->hasSimilarSpeller(name, similarName)) {
		setSpeller(similarName);
	}
}

void LatexEditorView::copyImageFromAction() {
	QAction *act = qobject_cast<QAction *>(sender());
	if (!act) return;

	QPixmap pm = act->data().value<QPixmap>();
	if (!pm.isNull()) {
		QApplication::clipboard()->setImage(pm.toImage());
	}
}

void LatexEditorView::saveImageFromAction() {
	static QString lastSaveDir;

	QAction *act = qobject_cast<QAction *>(sender());
	if (!act) return;

	QPixmap pm = act->data().value<QPixmap>();

	QString fname = QFileDialog::getSaveFileName(this , tr("Save Preview Image"), lastSaveDir, tr("Images")+" (*.png *.jpg)");
	if (fname.isEmpty()) return;

	QFileInfo fi(fname);
	lastSaveDir = fi.absolutePath();
	pm.save(fname);
}


void LatexEditorViewConfig::settingsChanged(){
	if (!hackAutoChoose) { lastFontFamily = ""; return; }
	if (lastFontFamily == fontFamily && lastFontSize == fontSize) return;
	
	QFont f(fontFamily, fontSize);
#if QT_VERSION >= 0x040700
	f.setStyleHint(QFont::Courier, QFont::ForceIntegerMetrics);
#else
	const QFont::StyleStrategy ForceIntegerMetrics = (QFont::StyleStrategy)0x0400;
	f.setStyleHint(QFont::Courier, (hasAtLeastQt(4,7) ? ForceIntegerMetrics : QFont::PreferQuality));
	
#endif
	f.setKerning(false);
	
	QList<QFontMetrics> fms;
	for (int b = 0; b<2;b++) for (int i = 0; i<2;i++) {
		QFont ft(f);
		ft.setBold(b);
		ft.setItalic(i);
		fms << QFontMetrics(ft);
	}
	
	bool lettersHaveDifferentWidth = false, sameLettersHaveDifferentWidth = false;
	int letterWidth = fms.first().width('a');
	
	static QString lettersToCheck("abcdefghijklmnoqrstuvwxyzABCDEFHIJKLMNOQRSTUVWXYZ_+ 123/()=.,;#");
	
	foreach (const QChar& c, lettersToCheck) {
		foreach (const QFontMetrics& fm, fms) {
			int currentWidth = fm.width(c);
			if (currentWidth != letterWidth) lettersHaveDifferentWidth = true;
			QString testString;
			for (int i=1;i<10;i++) {
				testString += c;
				int stringWidth = fm.width(testString);
				if (stringWidth % i != 0) sameLettersHaveDifferentWidth = true;
				if (currentWidth != stringWidth / i) sameLettersHaveDifferentWidth = true;
			}
			if (lettersHaveDifferentWidth && sameLettersHaveDifferentWidth) break;
		}
		if (lettersHaveDifferentWidth && sameLettersHaveDifferentWidth) break;
	}
	
	if (!QFontInfo(f).fixedPitch()) hackDisableFixedPitch = false; //won't be enabled anyways
	else hackDisableFixedPitch = lettersHaveDifferentWidth;
	hackDisableWidthCache = sameLettersHaveDifferentWidth;

	hackDisableLineCache = isRetinaMac();
	hackRenderingMode = 0; //always use qce, best tested
	
	lastFontFamily = fontFamily;
	lastFontSize = fontSize;
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

void LatexEditorView::bibtexSectionFound(QString content){
	QToolTip::showText(editor->mapToGlobal(editor->mapFromFrame(lastPos)), content);
}

void LatexEditorView::lineMarkContextMenuRequested(int lineNumber, QPoint globalPos) {
	if (!document) return;

	QDocumentLine line(document->line(lineNumber));
	QMenu menu(this);

	for (int i=-1; i<10; i++) {
		int rmid=bookMarkId(i);
		if(line.hasMark(rmid)){
			QAction *act =  new QAction(tr("Remove Bookmark"), &menu);
			act->setData(-2);
			menu.addAction(act);
			menu.addSeparator();
			break;
		}
	}

    QAction *act = new QAction(getRealIconCached("lbook"),tr("Unnamed Bookmark"), &menu);
	act->setData(-1);
	menu.addAction(act);

	for (int i=0; i<10; i++) {
        QAction *act = new QAction(getRealIconCached(QString("lbook%1").arg(i)), tr("Bookmark")+QString(" %1").arg(i), &menu);
		act->setData(i);
		menu.addAction(act);
	}

	act = menu.exec(globalPos);
	if (act) {
		int bookmarkNumber = act->data().toInt();
		if (bookmarkNumber == -2) {
			for (int i=-1; i<10; i++) {
				int rmid=bookMarkId(i);
				if(line.hasMark(rmid)){
					removeBookmark(line.handle(), i);
					return;
				}
			}
		} else {
			toggleBookmark(bookmarkNumber, line);
		}
	}
}

void LatexEditorView::foldContextMenuRequested(int lineNumber, QPoint globalPos) {
	Q_UNUSED(lineNumber);

	QMenu menu;
	QAction *act = new QAction(tr("Collapse All"), &menu);
	act->setData(-5);
	menu.addAction(act);
	for (int i=1; i<=4; i++) {
		act = new QAction(QString(tr("Collapse Level %1")).arg(i), &menu);
		act->setData(-i);
		menu.addAction(act);
	}
	menu.addSeparator();
	act = new QAction(tr("Expand All"), &menu);
	act->setData(5);
	menu.addAction(act);
	for (int i=1; i<=4; i++) {
		act = new QAction(QString(tr("Expand Level %1")).arg(i), &menu);
		act->setData(i);
		menu.addAction(act);
	}

	act = menu.exec(globalPos);
	if (act) {
		int level = act->data().toInt();
		if (qAbs(level)<5) {
			foldLevel(level>0, qAbs(level));
		} else {
			foldEverything(level>0);
		}
	}
}

LinkOverlay::LinkOverlay(const LinkOverlay &o) {
	type = o.type;
	if (o.isValid()) {
		docLine = o.docLine;
		context = o.context;
		formatRange = o.formatRange;
	}
}

LinkOverlay::LinkOverlay(const QDocumentCursor &cur, LatexParser::ContextType ctx, LinkOverlay::LinkOverlayType ltype) :
	type(ltype), context(ctx)
{
	if (type == Invalid) return;

	int from, to;

	if (type == UsepackageOverlay || type == BibFileOverlay || type == CiteOverlay) {
		// link one of the colon separated options
		QDocumentCursor c(cur);
		LatexEditorView::selectOptionInLatexArg(c);
		from = c.anchorColumnNumber();
		to = c.columnNumber()-1;
		if (from<0 || to<0 || to<=from)
			return;
	} else {
		// link everything between {}
		QString text = cur.line().text();
		int col = cur.columnNumber();
		from = findOpeningBracket(text, col);
		to = findClosingBracket(text, col);
		if (from<0 || to<0)
			return;
		from +=1; to -= 1; // leave out brackets
	}

	REQUIRE(QDocument::defaultFormatScheme());
	formatRange = QFormatRange(from, to-from+1, QDocument::defaultFormatScheme()->id("link"));
	docLine = cur.line();
}

QString LinkOverlay::text() const {
	if (!isValid()) return QString();
	return docLine.text().mid(formatRange.offset, formatRange.length);
}


