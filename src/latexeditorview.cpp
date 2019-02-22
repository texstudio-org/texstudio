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

#include "filedialog.h"
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
#include "latexrepository.h"

#include "latexparser/latexparsing.h"

#include "latexcompleter_config.h"

#include "scriptengine.h"
#include "diffoperations.h"

#include "help.h"

#include "bidiextender.h"

//------------------------------Default Input Binding--------------------------------
/*!
 * \brief default keyboard binding for normal operation
 */
class DefaultInputBinding: public QEditorInputBinding
{
	//  Q_OBJECT not possible because inputbinding is no qobject
public:
    DefaultInputBinding(): completerConfig(nullptr), editorViewConfig(nullptr), contextMenu(nullptr), isDoubleClick(false) {}
	virtual QString id() const
	{
		return "TXS::DefaultInputBinding";
	}
	virtual QString name() const
	{
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
	void checkLinkOverlay(QPoint mousePos, Qt::KeyboardModifiers modifiers, QEditor *editor);
	friend class LatexEditorView;
	const LatexCompleterConfig *completerConfig;
	const LatexEditorViewConfig *editorViewConfig;
	QList<QAction *> baseActions;

	QMenu *contextMenu;
	QString lastSpellCheckedWord;

	QPoint lastMousePressLeft;
	bool isDoubleClick;  // event sequence of a double click: press, release, double click, release - this is true on the second release
};

static const QString LRMStr = QChar(LRM);

bool DefaultInputBinding::runMacros(QKeyEvent *event, QEditor *editor)
{
	Q_ASSERT(completerConfig);
    QLanguageDefinition *language = editor->document() ? editor->document()->languageDefinition() : nullptr;
	QDocumentLine line = editor->cursor().selectionStart().line();
	int column = editor->cursor().selectionStart().columnNumber();
	QString prev = line.text().mid(0, column) + event->text(); //TODO: optimize
	foreach (const Macro &m, completerConfig->userMacros) {
		if (!m.isActiveForTrigger(Macro::ST_REGEX)) continue;
		if (!m.isActiveForLanguage(language)) continue;
		if (!(m.isActiveForFormat(line.getFormatAt(column)) || (column > 0 && m.isActiveForFormat(line.getFormatAt(column - 1))))) continue; //two checks, so it works at beginning and end of an environment
		QRegExp &r = const_cast<QRegExp &>(m.triggerRegex); //a const qregexp doesn't exist
		if (r.indexIn(prev) != -1) {
			QDocumentCursor c = editor->cursor();
			bool block = false;
			int realMatchLen = r.matchedLength();
			if (m.triggerLookBehind) realMatchLen -= r.cap(1).length();
			if (c.hasSelection() || realMatchLen > 1)
				block = true;
			if (block) editor->document()->beginMacro();
			if (c.hasSelection()) {
				editor->cutBuffer = c.selectedText();
				c.removeSelectedText();
			}
			if (m.triggerRegex.matchedLength() > 1) {
				c.movePosition(realMatchLen - 1, QDocumentCursor::PreviousCharacter, QDocumentCursor::KeepAnchor);
				c.removeSelectedText();
                editor->setCursor(c);
			}

			LatexEditorView *view = editor->property("latexEditor").value<LatexEditorView *>();
			REQUIRE_RET(view, true);
			emit view->execMacro(m, MacroExecContext(Macro::ST_REGEX, r.capturedTexts()));
			if (block) editor->document()->endMacro();
			editor->cutBuffer.clear();
			editor->emitCursorPositionChanged(); //prevent rogue parenthesis highlightations
			/*			if (editor->languageDefinition())
			editor->languageDefinition()->clearMatches(editor->document());
			*/
			return true;
		}
	}
	return false;
}

bool DefaultInputBinding::autoInsertLRM(QKeyEvent *event, QEditor *editor)
{
	const QString &text = event->text();
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
			} else editor->write("}" + LRMStr);
			if (block) editor->document()->endMacro();
			return true;
		}
	}
	return false;
}

void DefaultInputBinding::checkLinkOverlay(QPoint mousePos, Qt::KeyboardModifiers modifiers, QEditor *editor)
{
	if (modifiers == Qt::ControlModifier) {
		LatexEditorView *edView = qobject_cast<LatexEditorView *>(editor->parentWidget());
		QDocumentCursor cursor = editor->cursorForPosition(mousePos);
		edView->checkForLinkOverlay(cursor);
	} else {
		// reached for example when Ctrl+Shift is pressed
		LatexEditorView *edView = qobject_cast<LatexEditorView *>(editor->parentWidget()); //a qobject is necessary to retrieve events
		edView->removeLinkOverlay();
	}
}

bool DefaultInputBinding::keyPressEvent(QKeyEvent *event, QEditor *editor)
{
	if (LatexEditorView::completer && LatexEditorView::completer->acceptTriggerString(event->text())
	        && (editor->currentPlaceHolder() < 0 || editor->currentPlaceHolder() >= editor->placeHolderCount() || editor->getPlaceHolder(editor->currentPlaceHolder()).mirrors.isEmpty() ||  editor->getPlaceHolder(editor->currentPlaceHolder()).affector != BracketInvertAffector::instance())
	        && !editor->flag(QEditor::Overwrite))  {
		//update completer if necessary
		editor->emitNeedUpdatedCompleter();
		bool autoOverriden = editor->isAutoOverrideText(event->text());
		if (editorViewConfig->autoInsertLRM && event->text() == "\\" && editor->cursor().isRTL())
			editor->write(LRMStr + event->text());
		else
			editor->write(event->text());
		if (autoOverriden) LatexEditorView::completer->complete(editor, LatexCompleter::CF_OVERRIDEN_BACKSLASH);
		else {
			int flags = Parsing::getCompleterContext(editor->cursor().line().handle(), editor->cursor().columnNumber());
			LatexEditorView::completer->complete(editor, LatexCompleter::CompletionFlag(flags));
		}
		return true;
	}
	if (!event->text().isEmpty()) {
		if (!editor->flag(QEditor::Overwrite) && runMacros(event, editor))
			return true;
		if (autoInsertLRM(event, editor))
			return true;
		if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
			// if cursor is at the end of a placeholder, remove that placeholder
			int phId = editor->currentPlaceHolder();
			if (phId >= 0) {
				PlaceHolder ph = editor->getPlaceHolder(phId);
				if (editor->cursor().lineNumber() == ph.cursor.lineNumber() &&
				        editor->cursor().columnNumber() == ph.cursor.columnNumber()) {
					editor->removePlaceHolder(phId);
					return true;
				}
			}
		}
	} else {
		if (event->key() == Qt::Key_Control) {
			editor->setMouseTracking(true);
			QPoint mousePos(editor->mapToFrame(editor->mapFromGlobal(QCursor::pos())));
			checkLinkOverlay(mousePos, event->modifiers(), editor);
		}
	}
	if (LatexEditorView::hideTooltipWhenLeavingLine != -1 && editor->cursor().lineNumber() != LatexEditorView::hideTooltipWhenLeavingLine) {
		LatexEditorView::hideTooltipWhenLeavingLine = -1;
		QToolTip::hideText();
	}
	return false;
}

void DefaultInputBinding::postKeyPressEvent(QKeyEvent *event, QEditor *editor)
{
    QString txt=event->text();
    if(txt.length()!=1)
        return;
    QChar c=txt.at(0);
    if ( c== ',' || c.isLetter()) {
		LatexEditorView *view = editor->property("latexEditor").value<LatexEditorView *>();
		Q_ASSERT(view);
		if (completerConfig && completerConfig->enabled)
            view->mayNeedToOpenCompleter(c!=',');
	}
}

bool DefaultInputBinding::keyReleaseEvent(QKeyEvent *event, QEditor *editor)
{
	if (event->key() == Qt::Key_Control) {
		editor->setMouseTracking(false);
		LatexEditorView *edView = qobject_cast<LatexEditorView *>(editor->parentWidget()); //a qobject is necessary to retrieve events
		edView->removeLinkOverlay();
	}
	return false;
}

bool DefaultInputBinding::mousePressEvent(QMouseEvent *event, QEditor *editor)
{
    LatexEditorView *edView = nullptr;

	switch (event->button()) {
	case Qt::XButton1:
		edView = qobject_cast<LatexEditorView *>(editor->parentWidget());
		emit edView->mouseBackPressed();
		return true;
	case Qt::XButton2:
		edView = qobject_cast<LatexEditorView *>(editor->parentWidget());
		emit edView->mouseForwardPressed();
		return true;
	case Qt::LeftButton:
		edView = qobject_cast<LatexEditorView *>(editor->parentWidget());
		emit edView->cursorChangeByMouse();
		lastMousePressLeft = event->pos();
		return false;
	default:
		return false;
	}

	return false;
}

bool DefaultInputBinding::mouseReleaseEvent(QMouseEvent *event, QEditor *editor)
{
	if (isDoubleClick) {
		isDoubleClick = false;
		return false;
	}
	isDoubleClick = false;

	if (event->modifiers() == Qt::ControlModifier && event->button() == Qt::LeftButton) {
		// Ctrl+LeftClick
		int distanceSqr = (event->pos().x() - lastMousePressLeft.x()) * (event->pos().x() - lastMousePressLeft.x()) + (event->pos().y() - lastMousePressLeft.y()) * (event->pos().y() - lastMousePressLeft.y());
		if (distanceSqr > 4) // allow the user to accidentially move the mouse a bit
			return false;

		LatexEditorView *edView = qobject_cast<LatexEditorView *>(editor->parentWidget()); //a qobject is necessary to retrieve events
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
			case LinkOverlay::UrlOverlay:
				if (!QDesktopServices::openUrl(lo.text())) {
					UtilsUi::txsWarning(LatexEditorView::tr("Could not open url:") + "\n" + lo.text());
				}
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

bool DefaultInputBinding::mouseDoubleClickEvent(QMouseEvent *event, QEditor *editor)
{
	Q_UNUSED(event);
	Q_UNUSED(editor);
	isDoubleClick = true;
	return false;
}

bool DefaultInputBinding::contextMenuEvent(QContextMenuEvent *event, QEditor *editor)
{
    if (!contextMenu) contextMenu = new QMenu(nullptr);
	contextMenu->clear();
	contextMenu->setProperty("isSpellingPopulated", QVariant());  // delete information on spelling
	QDocumentCursor cursor;
	if (event->reason() == QContextMenuEvent::Mouse) cursor = editor->cursorForPosition(editor->mapToContents(event->pos()));
	else cursor = editor->cursor();
	LatexEditorView *edView = qobject_cast<LatexEditorView *>(editor->parentWidget()); //a qobject is necessary to retrieve events
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
			foreach (QAction *act, baseActions) {
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
	//LatexParser::ContextType context = LatexParser::Unknown;
	QString ctxCommand;
	if (validPosition) {
		QFormatRange fr;
		//spell checking

		if (edView->speller) {
			int pos;
			if (cursor.hasSelection()) pos = (cursor.columnNumber() + cursor.anchorColumnNumber()) / 2;
			else pos = cursor.columnNumber();

			foreach (const int f, edView->grammarFormats) {
				fr = cursor.line().getOverlayAt(pos, f);
				if (fr.length > 0 && fr.format == f) {
					QVariant var = cursor.line().getCookie(QDocumentLine::GRAMMAR_ERROR_COOKIE);
					if (var.isValid()) {
						QDocumentCursor wordSelection(editor->document(), cursor.lineNumber(), fr.offset);
						wordSelection.movePosition(fr.length, QDocumentCursor::NextCharacter, QDocumentCursor::KeepAnchor);
						editor->setCursor(wordSelection);

						const QList<GrammarError> &errors = var.value<QList<GrammarError> >();
						for (int i = 0; i < errors.size(); i++)
							if (errors[i].offset <= cursor.columnNumber() && errors[i].offset + errors[i].length >= cursor.columnNumber()) {
								edView->addReplaceActions(contextMenu, errors[i].corrections, true);
								break;
							}
					}
				}
			}

			fr = cursor.line().getOverlayAt(pos, SpellerUtility::spellcheckErrorFormat);
			if (fr.length > 0 && fr.format == SpellerUtility::spellcheckErrorFormat) {
				QString word = cursor.line().text().mid(fr.offset, fr.length);
				if (!(editor->cursor().hasSelection() && editor->cursor().selectedText().length() > 0) || editor->cursor().selectedText() == word
				        || editor->cursor().selectedText() == lastSpellCheckedWord) {
					lastSpellCheckedWord = word;
					word = latexToPlainWord(word);
					QDocumentCursor wordSelection(editor->document(), cursor.lineNumber(), fr.offset);
					wordSelection.movePosition(fr.length, QDocumentCursor::NextCharacter, QDocumentCursor::KeepAnchor);
					editor->setCursor(wordSelection);

					if ((editorViewConfig->contextMenuSpellcheckingEntryLocation == 0) ^ (event->modifiers() & editorViewConfig->contextMenuKeyboardModifiers)) {
						edView->addSpellingActions(contextMenu, lastSpellCheckedWord, false);
						contextMenu->addSeparator();
					} else {
						QMenu *spellingMenu = contextMenu->addMenu(LatexEditorView::tr("Spelling"));
						spellingMenu->setProperty("word", lastSpellCheckedWord);
						edView->connect(spellingMenu, SIGNAL(aboutToShow()), edView, SLOT(populateSpellingMenu()));
					}
				}
			}
		}
		//citation checking
		int f = edView->citationMissingFormat;
		if (cursor.hasSelection()) fr = cursor.line().getOverlayAt((cursor.columnNumber() + cursor.anchorColumnNumber()) / 2, f);
		else fr = cursor.line().getOverlayAt(cursor.columnNumber(), f);
		if (fr.length > 0 && fr.format == f) {
			QString word = cursor.line().text().mid(fr.offset, fr.length);
			editor->setCursor(editor->document()->cursor(cursor.lineNumber(), fr.offset, cursor.lineNumber(), fr.offset + fr.length));
			QAction *act = new QAction(LatexEditorView::tr("New BibTeX Entry %1").arg(word), contextMenu);
			edView->connect(act, SIGNAL(triggered()), edView, SLOT(requestCitation()));
			contextMenu->addAction(act);
			contextMenu->addSeparator();
		}
		//check input/include
		//find context of cursor
		QDocumentLineHandle *dlh = cursor.line().handle();
		TokenList tl = dlh->getCookieLocked(QDocumentLine::LEXER_COOKIE).value<TokenList>();
		int i = Parsing::getTokenAtCol(tl, cursor.columnNumber());
		Token tk;
		if (i >= 0)
			tk = tl.at(i);

		if ( tk.type == Token::file) {
			QAction *act = new QAction(LatexEditorView::tr("Open %1").arg(tk.getText()), contextMenu);
			act->setData(tk.getText());
			edView->connect(act, SIGNAL(triggered()), edView, SLOT(openExternalFile()));
			contextMenu->addAction(act);
		}
		// bibliography command
		if ( tk.type == Token::bibfile) {
			QAction *act = new QAction(LatexEditorView::tr("Open Bibliography"), contextMenu);
			QString bibFile;
			bibFile = tk.getText() + ".bib";
			act->setData(bibFile);
			edView->connect(act, SIGNAL(triggered()), edView, SLOT(openExternalFile()));
			contextMenu->addAction(act);
		}
		//package help
        if ( tk.type == Token::package || tk.type == Token::documentclass) {
			QAction *act = new QAction(LatexEditorView::tr("Open package documentation"), contextMenu);
			QString packageName = tk.getText();
			act->setText(act->text().append(QString(" (%1)").arg(packageName)));
			act->setData(packageName);
			edView->connect(act, SIGNAL(triggered()), edView, SLOT(openPackageDocumentation()));
			contextMenu->addAction(act);
		}
		// help for any "known" command
		if ( tk.type == Token::command) {
			ctxCommand = tk.getText();
			QString command = ctxCommand;
			if (ctxCommand == "\\begin" || ctxCommand == "\\end")
				command = ctxCommand + "{" + Parsing::getArg(tl.mid(i + 1), dlh, 0, ArgumentList::Mandatory) + "}";
			QString package = edView->document->parent->findPackageByCommand(command);
			package.chop(4);
			if (!package.isEmpty()) {
				QAction *act = new QAction(LatexEditorView::tr("Open package documentation"), contextMenu);
				act->setText(act->text().append(QString(" (%1)").arg(package)));
				act->setData(package + "#" + command);
				edView->connect(act, SIGNAL(triggered()), edView, SLOT(openPackageDocumentation()));
				contextMenu->addAction(act);
			}
		}
		if (/* tk.type==Tokens::bibRef || TODO: bibliography references not yet handled by token system */ tk.type == Token::labelRef) {
			QAction *act = new QAction(LatexEditorView::tr("Go to Definition"), contextMenu);
			act->setData(QVariant().fromValue<QDocumentCursor>(cursor));
			edView->connect(act, SIGNAL(triggered()), edView, SLOT(emitGotoDefinitionFromAction()));
			contextMenu->addAction(act);
		}
		if (tk.type == Token::label || tk.type == Token::labelRef || tk.type == Token::labelRefList) {
			QAction *act = new QAction(LatexEditorView::tr("Find Usages"), contextMenu);
			act->setData(tk.getText());
			act->setProperty("doc", QVariant::fromValue<LatexDocument *>(edView->document));
			edView->connect(act, SIGNAL(triggered()), edView, SLOT(emitFindLabelUsagesFromAction()));
			contextMenu->addAction(act);
		}
		if (tk.type == Token::word) {
			QAction *act = new QAction(LatexEditorView::tr("Thesaurus..."), contextMenu);
			act->setData(QPoint(cursor.anchorLineNumber(), cursor.anchorColumnNumber()));
			edView->connect(act, SIGNAL(triggered()), edView, SLOT(triggeredThesaurus()));
			contextMenu->addAction(act);
		}

		//resolve differences
		if (edView) {
			QList<int> fids;
			fids << edView->deleteFormat << edView->insertFormat << edView->replaceFormat;
			foreach (int fid, fids) {
				if (cursor.hasSelection()) fr = cursor.line().getOverlayAt((cursor.columnNumber() + cursor.anchorColumnNumber()) / 2, fid);
				else fr = cursor.line().getOverlayAt(cursor.columnNumber(), fid);
				if (fr.length > 0 ) {
					QVariant var = cursor.line().getCookie(QDocumentLine::DIFF_LIST_COOCKIE);
					if (var.isValid()) {
						DiffList diffList = var.value<DiffList>();
						//QString word=cursor.line().text().mid(fr.offset,fr.length);
						DiffOp op;
						op.start = -1;
						foreach (op, diffList) {
							if (op.start <= cursor.columnNumber() && op.start + op.length >= cursor.columnNumber()) {
								break;
							}
							op.start = -1;
						}
						if (op.start >= 0) {
							QAction *act = new QAction(LatexEditorView::tr("use yours"), contextMenu);
							act->setData(QPoint(cursor.lineNumber(), cursor.columnNumber()));
							edView->connect(act, SIGNAL(triggered()), edView, SLOT(emitChangeDiff()));
							contextMenu->addAction(act);
							act = new QAction(LatexEditorView::tr("use other's"), contextMenu);
							act->setData(QPoint(-cursor.lineNumber() - 1, cursor.columnNumber()));
							edView->connect(act, SIGNAL(triggered()), edView, SLOT(emitChangeDiff()));
							contextMenu->addAction(act);
							break;
						}
					}
				}
			}
		}
		contextMenu->addSeparator();
	}
	contextMenu->addActions(baseActions);
	if (validPosition) {
		contextMenu->addSeparator();

		QAction *act = new QAction(LatexEditorView::tr("Go to PDF"), contextMenu);
		act->setData(QVariant().fromValue<QDocumentCursor>(cursor));
		edView->connect(act, SIGNAL(triggered()), edView, SLOT(emitSyncPDFFromAction()));
		contextMenu->addAction(act);
	}


	if (event->reason() == QContextMenuEvent::Mouse) contextMenu->exec(event->globalPos());
	else {
		QPoint curPoint = editor->cursor().documentPosition();
		curPoint.ry() += editor->document()->getLineSpacing();
		contextMenu->exec(editor->mapToGlobal(editor->mapFromContents(curPoint)));
	}
	event->accept();

	return true;
}

bool DefaultInputBinding::mouseMoveEvent(QMouseEvent *event, QEditor *editor)
{
	checkLinkOverlay(editor->mapToContents(event->pos()), event->modifiers(), editor);
	return false;
}

DefaultInputBinding *defaultInputBinding = new DefaultInputBinding();



//----------------------------------LatexEditorView-----------------------------------
LatexCompleter *LatexEditorView::completer = nullptr;
int LatexEditorView::hideTooltipWhenLeavingLine = -1;

//Q_DECLARE_METATYPE(LatexEditorView *)

LatexEditorView::LatexEditorView(QWidget *parent, LatexEditorViewConfig *aconfig, LatexDocument *doc) : QWidget(parent), document(nullptr), latexPackageList(nullptr), spellerManager(nullptr), speller(nullptr), useDefaultSpeller(true), curChangePos(-1), config(aconfig), bibReader(nullptr)
{
	Q_ASSERT(config);

	QVBoxLayout *mainlay = new QVBoxLayout(this);
	mainlay->setSpacing(0);
	mainlay->setMargin(0);

	codeeditor = new QCodeEdit(false, this, doc);
	editor = codeeditor->editor();

	editor->setProperty("latexEditor", QVariant::fromValue<LatexEditorView *>(this));

	lineMarkPanel = new QLineMarkPanel;
	lineMarkPanelAction = codeeditor->addPanel(lineMarkPanel, QCodeEdit::West, false);
	lineNumberPanel = new QLineNumberPanel;
	lineNumberPanelAction = codeeditor->addPanel(lineNumberPanel, QCodeEdit::West, false);;
	QFoldPanel *foldPanel = new QFoldPanel;
	lineFoldPanelAction = codeeditor->addPanel(foldPanel, QCodeEdit::West, false);
	lineChangePanelAction = codeeditor->addPanel(new QLineChangePanel, QCodeEdit::West, false);

	statusPanel = new QStatusPanel;
	statusPanel->setFont(QApplication::font());
	statusPanelAction = codeeditor->addPanel(statusPanel, QCodeEdit::South, false);

	gotoLinePanel = new QGotoLinePanel;
	gotoLinePanel->setFont(QApplication::font());
	gotoLinePanelAction = codeeditor->addPanel(gotoLinePanel, QCodeEdit::South, false);

	searchReplacePanel = new QSearchReplacePanel;
	searchReplacePanel->setFont(QApplication::font());
	searchReplacePanelAction = codeeditor->addPanel(searchReplacePanel, QCodeEdit::South, false);
	searchReplacePanel->hide();
	connect(searchReplacePanel, SIGNAL(showExtendedSearch()), this, SIGNAL(showExtendedSearch()));

	connect(lineMarkPanel, SIGNAL(lineClicked(int)), this, SLOT(lineMarkClicked(int)));
	connect(lineMarkPanel, SIGNAL(toolTipRequested(int, int)), this, SLOT(lineMarkToolTip(int, int)));
	connect(lineMarkPanel, SIGNAL(contextMenuRequested(int, QPoint)), this, SLOT(lineMarkContextMenuRequested(int, QPoint)));
	connect(foldPanel, SIGNAL(contextMenuRequested(int, QPoint)), this, SLOT(foldContextMenuRequested(int, QPoint)));
	connect(editor, SIGNAL(hovered(QPoint)), this, SLOT(mouseHovered(QPoint)));
	//connect(editor->document(),SIGNAL(contentsChange(int, int)),this,SLOT(documentContentChanged(int, int)));
	connect(editor->document(), SIGNAL(lineDeleted(QDocumentLineHandle *)), this, SLOT(lineDeleted(QDocumentLineHandle *)));

	connect(doc, SIGNAL(spellingDictChanged(QString)), this, SLOT(changeSpellingDict(QString)));
	connect(doc, SIGNAL(bookmarkRemoved(QDocumentLineHandle *)), this, SIGNAL(bookmarkRemoved(QDocumentLineHandle *)));
	connect(doc, SIGNAL(bookmarkAdded(QDocumentLineHandle *, int)), this, SIGNAL(bookmarkAdded(QDocumentLineHandle *, int)));

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

	lp = LatexParser::getInstance();
}

LatexEditorView::~LatexEditorView()
{
	delete searchReplacePanel; // to force deletion of m_search before document. Otherwise crashes can come up (linux)
	delete codeeditor; //explicit call destructor of codeeditor (although it has a parent, it is no qobject itself, but passed it to editor)

	if (bibReader) {
		bibReader->quit();
		bibReader->wait();
	}
}

void LatexEditorView::updateReplamentList(const LatexParser &cmds, bool forceUpdate)
{
	QMap<QString, QString> replacementList;
	bool differenceExists = false;
	foreach (QString elem, cmds.possibleCommands["%replace"].values()) {
		int i = elem.indexOf(" ");
		if (i > 0) {
			replacementList.insert(elem.left(i), elem.mid(i + 1));
			if (mReplacementList.value(elem.left(i)) != elem.mid(i + 1))
				differenceExists = true;
		}
	}
	if (differenceExists || replacementList.count() != mReplacementList.count() || forceUpdate) {
		mReplacementList = replacementList;
		documentContentChanged(0, editor->document()->lines()); //force complete spellcheck
	}
}

void LatexEditorView::paste()
{
	if (completer->isVisible()) {
		const QMimeData *d = QApplication::clipboard()->mimeData();

		if ( d ) {
			QString txt;
			if ( d->hasFormat("text/plain") )
				txt = d->text();
			else if ( d->hasFormat("text/html") )
				txt = d->html();

			if (txt.contains("\n"))
				txt.clear();

			if (txt.isEmpty()) {
				completer->close();
				editor->paste();
			} else {
				completer->insertText(txt);
			}
		}
	} else {
		editor->paste();
	}
}

void LatexEditorView::insertSnippet(QString text)
{
	CodeSnippet(text).insert(editor);
}

void LatexEditorView::deleteLines(bool toStart, bool toEnd)
{
	QList<QDocumentCursor> cursors = editor->cursors();
	if (cursors.empty()) return;
	document->beginMacro();
	for (int i=0;i<cursors.size();i++)
		cursors[i].removeSelectedText();

	int cursorLine = cursors[0].lineNumber();
	QMultiMap< int, QDocumentCursor* > map = getSelectedLines(cursors);
	QList<int> lines = map.uniqueKeys();
	QList<QDocumentCursor> newMirrors;
	for (int i=lines.size()-1;i>=0;i--) {
		QList<QDocumentCursor*> cursors = map.values(lines[i]);
		REQUIRE(cursors.size());
		if (toStart && toEnd) cursors[0]->eraseLine();
		else {
			int len = document->line(lines[i]).length();
			int column = toStart ? 0 : len;
			foreach (QDocumentCursor* c, cursors)
				if (toStart) column = qMax(c->columnNumber(), column);
				else column = qMin(c->columnNumber(), column);
			QDocumentCursor c = document->cursor(lines[i], column, lines[i], toStart ? 0 : len);
			c.removeSelectedText();

			if (!toStart || !toEnd){
				if (lines[i] == cursorLine) editor->setCursor(c);
				else newMirrors << c;
			}
		}
	}
	document->endMacro();
    editor->setCursor(cursors[0]);
	if (!toStart || !toEnd)
		for (int i=0;i<newMirrors.size();i++)
			editor->addCursorMirror(newMirrors[i]); //one cursor / line
}

void LatexEditorView::moveLines(int delta)
{
	REQUIRE(delta == -1 || delta == +1);
	QList<QDocumentCursor> cursors = editor->cursors();
	for (int i=0;i<cursors.length();i++)
		cursors[i].setAutoUpdated(false);
	QList<QPair<int, int> > blocks = getSelectedLineBlocks();
	document->beginMacro();
	int i = delta < 0 ? blocks.size() - 1 : 0;
	while (i >= 0 && i < blocks.size()) {
		//edit
		QDocumentCursor edit = document->cursor(blocks[i].first, 0, blocks[i].second);
		QString text = edit.selectedText();
		edit.removeSelectedText();
		edit.eraseLine();
		if (delta < 0) {
			if (blocks[i].second < document->lineCount())
				edit.movePosition(1, QDocumentCursor::PreviousLine);
			edit.movePosition(1, QDocumentCursor::StartOfLine);
			edit.insertText(text + "\n");
		} else {
			edit.movePosition(1, QDocumentCursor::EndOfLine);
			edit.insertText("\n" + text);
		}
		i += delta;
	}
	document->endMacro();
	//move cursors
	for (int i=0;i<cursors.length();i++) {
		cursors[i].setAutoUpdated(true);
		if (cursors[i].hasSelection()) {
			cursors[i].setAnchorLineNumber(cursors[i].anchorLineNumber() + delta);
			cursors[i].setLineNumber(cursors[i].lineNumber() + delta, QDocumentCursor::KeepAnchor);
		} else
			cursors[i].setLineNumber(cursors[i].lineNumber() + delta);
		if (i == 0) editor->setCursor(cursors[i]);
		else editor->addCursorMirror(cursors[i]);
	}
}

QList<QPair<int, int> > LatexEditorView::getSelectedLineBlocks()
{
	QList<QDocumentCursor> cursors = editor->cursors();
	QList<int> lines;
	//get affected lines
	for (int i=0;i<cursors.length();i++) {
		if (cursors[i].hasSelection()) {
			QDocumentSelection sel = cursors[i].selection();
			for (int l=sel.startLine;l<=sel.endLine;l++)
				lines << l;
		} else lines << cursors[i].lineNumber();
	}
	qSort(lines);
	//merge blocks as speed up and to remove duplicates
	QList<QPair<int, int> > result;
	int i = 0;
	while (i < lines.size()) {
		int start = lines[i];
		int end = lines[i];
		i++;
		while ( i >= 0 && i < lines.size() && (lines[i] == end || lines[i] == end + 1)) {
			end = lines[i];
			i++;
		}
		result << QPair<int,int> (start, end);
	}
	return result;
}

QMultiMap<int, QDocumentCursor* > LatexEditorView::getSelectedLines(QList<QDocumentCursor>& cursors)
{
	QMultiMap<int, QDocumentCursor* > map;
	for (int i=0;i<cursors.length();i++) {
		if (cursors[i].hasSelection()) {
			QDocumentSelection sel = cursors[i].selection();
			for (int l=sel.startLine;l<=sel.endLine;l++)
				map.insert(l, &cursors[i]);
		} else map.insert(cursors[i].lineNumber(), &cursors[i]);
	}
	return map;
}

bool cursorPointerLessThan(QDocumentCursor* c1, QDocumentCursor* c2)
{
	return c1->columnNumber() < c2->columnNumber();
}

void LatexEditorView::alignMirrors()
{
	QList<QDocumentCursor> cursors = editor->cursors();
	QMultiMap<int, QDocumentCursor* > map = getSelectedLines(cursors);
	QList<int> lines = map.uniqueKeys();
	QList<QList<QDocumentCursor*> > cs;
	int colCount = 0;
	foreach (int l, lines) {
		QList<QDocumentCursor*> row = map.values(l);
		colCount = qMax(colCount, row.size());
		qSort(row.begin(), row.end(), cursorPointerLessThan);
		cs.append(row);
	}
	document->beginMacro();
	for (int col=0;col<colCount;col++) {
		int pos = 0;
		for (int j=0;j<cs.size();j++)
			if (col < cs[j].size())
				pos = qMax(pos, cs[j][col]->columnNumber());
		for (int j=0;j<cs.size();j++)
			if (col < cs[j].size() && pos > cs[j][col]->columnNumber()) {
				cs[j][col]->insertText(QString(pos -  cs[j][col]->columnNumber(), ' '));
			}
	}
	document->endMacro();
}

void LatexEditorView::checkForLinkOverlay(QDocumentCursor cursor)
{
	if (cursor.atBlockEnd()) {
		removeLinkOverlay();
		return;
	}

	bool validPosition = cursor.isValid() && cursor.line().isValid();
	if (validPosition) {
		QDocumentLineHandle *dlh = cursor.line().handle();

		Token tk = Parsing::getTokenAtCol(dlh, cursor.columnNumber());

		if (tk.type == Token::labelRef || tk.type == Token::labelRefList) {
			setLinkOverlay(LinkOverlay(cursor, LinkOverlay::RefOverlay));
		} else if (tk.type == Token::file) {
			setLinkOverlay(LinkOverlay(cursor, LinkOverlay::FileOverlay));
		} else if (tk.type == Token::url) {
			setLinkOverlay(LinkOverlay(cursor, LinkOverlay::UrlOverlay));
		} else if (tk.type == Token::package) {
			setLinkOverlay(LinkOverlay(cursor, LinkOverlay::UsepackageOverlay));
		} else if (tk.type == Token::bibfile) {
			setLinkOverlay(LinkOverlay(cursor, LinkOverlay::BibFileOverlay));
		} else if (tk.type == Token::bibItem) {
			setLinkOverlay(LinkOverlay(cursor, LinkOverlay::CiteOverlay));
		} else {
			if (linkOverlay.isValid()) removeLinkOverlay();
		}
	} else {
		if (linkOverlay.isValid()) removeLinkOverlay();
	}
}

void LatexEditorView::setLinkOverlay(const LinkOverlay &overlay)
{
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

void LatexEditorView::removeLinkOverlay()
{
	if (linkOverlay.isValid()) {
		linkOverlay.docLine.removeOverlay(linkOverlay.formatRange);
		linkOverlay = LinkOverlay();
		editor->viewport()->update(); // immediately apply the overlay
		editor->viewport()->setCursor(linkOverlayStoredCursor);
	}
}

bool LatexEditorView::isNonTextFormat(int format)
{
	if (format <= 0) return false;
	return format == numbersFormat
	       || format == verbatimFormat
	       || format == pictureFormat
	       || format == pweaveDelimiterFormat
	       || format == pweaveBlockFormat
	       || format == sweaveDelimiterFormat
	       || format == sweaveBlockFormat
	       || format == math_DelimiterFormat
	       || format == asymptoteBlockFormat;
}

void LatexEditorView::selectOptionInLatexArg(QDocumentCursor &cur)
{
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

void LatexEditorView::temporaryHighlight(QDocumentCursor cur)
{
	if (!cur.hasSelection()) return;
	REQUIRE(editor->document());

	QDocumentLine docLine(cur.selectionStart().line());
	if (cur.endLineNumber() != cur.startLineNumber()) {
		// TODO: proper highlighting of selections spanning more than one line. Currently just highlight to the end of the first line:
		cur = cur.selectionStart();
		cur.movePosition(1, QDocumentCursor::EndOfLine, QDocumentCursor::KeepAnchor);
	}

	QFormatRange highlight(cur.startColumnNumber(), cur.endColumnNumber() - cur.startColumnNumber(), editor->document()->getFormatId("search"));
	docLine.addOverlay(highlight);
	tempHighlightQueue.append(QPair<QDocumentLine, QFormatRange>(docLine, highlight));
	QTimer::singleShot(1000, this, SLOT(removeTemporaryHighlight()));
}

void LatexEditorView::removeTemporaryHighlight()
{
	if (!tempHighlightQueue.isEmpty()) {
		QDocumentLine docLine(tempHighlightQueue.first().first);
		docLine.removeOverlay(tempHighlightQueue.first().second);
		tempHighlightQueue.removeFirst();
	}
}

void LatexEditorView::displayLineGrammarErrorsInternal(int lineNr, const QList<GrammarError> &errors)
{
	QDocumentLine line = document->line(lineNr);
	foreach (const int f, grammarFormats)
		line.clearOverlays(f);
	foreach (const GrammarError &error, errors) {
		int f;
		if (error.error == GET_UNKNOWN) f = grammarMistakeFormat;
		else {
            int index = static_cast<int>(error.error) - 1;
			REQUIRE(index < grammarFormats.size());
			if (grammarFormatsDisabled[index]) continue;
			f = grammarFormats[index];
		}
		if (config->hideNonTextGrammarErrors && (isNonTextFormat(line.getFormatAt(error.offset)) || isNonTextFormat(line.getFormatAt(error.offset + error.length - 1))))
			continue;
		line.addOverlay(QFormatRange(error.offset, error.length, f));
	}
	//todo: check for width changing like if (changed && ff->format(wordRepetitionFormat).widthChanging()) line.handle()->updateWrapAndNotifyDocument(i);
}

void LatexEditorView::lineGrammarChecked(const void *doc, const void *lineHandle, int lineNr, const QList<GrammarError> &errors)
{
	if (doc != this->document) return;
	lineNr = document->indexOf(const_cast<QDocumentLineHandle *>(static_cast<const QDocumentLineHandle *>(lineHandle)), lineNr);
	if (lineNr < 0) return; //line already deleted
	displayLineGrammarErrorsInternal(lineNr, errors);
	document->line(lineNr).setCookie(QDocumentLine::GRAMMAR_ERROR_COOKIE, QVariant::fromValue<QList<GrammarError> >(errors));
}

void LatexEditorView::setGrammarOverlayDisabled(int type, bool newValue)
{
	REQUIRE(type >= 0 && type < grammarFormatsDisabled.size());
	if (newValue == grammarFormatsDisabled[type]) return;
	grammarFormatsDisabled[type] = newValue;
}

void LatexEditorView::updateGrammarOverlays()
{
	for (int i = 0; i < document->lineCount(); i++)
		displayLineGrammarErrorsInternal(i, document->line(i).getCookie(QDocumentLine::GRAMMAR_ERROR_COOKIE).value<QList<GrammarError> >());
	editor->viewport()->update();
}

void LatexEditorView::viewActivated()
{
	if (!LatexEditorView::completer) return;
}

/*!
 * Returns the name to be displayed when a short textual reference to the editor is required
 * such as in the tab or in a list of open documents.
 * This name is not necessarily unique.
 */
QString LatexEditorView::displayName() const
{
	return (!editor || editor->fileName().isEmpty() ? tr("untitled") : editor->name());
}

/*!
 * Returns the displayName() with properly escaped ampersands for UI elements
 * such as tabs and actions.
 */
QString LatexEditorView::displayNameForUI() const
{
	return displayName().replace('&', "&&");
}

void LatexEditorView::complete(int flags)
{
	if (!LatexEditorView::completer) return;
	setFocus();
	LatexEditorView::completer->complete(editor, LatexCompleter::CompletionFlags(flags));
}

void LatexEditorView::jumpChangePositionBackward()
{
	if (changePositions.size() == 0) return;
	for (int i = changePositions.size() - 1; i >= 0; i--)
		if (!changePositions[i].isValid()) {
			changePositions.removeAt(i);
			if (i <= curChangePos) curChangePos--;
		}
	if (curChangePos >= changePositions.size() - 1) curChangePos = changePositions.size() - 1;
	else if (curChangePos >= 0 && curChangePos < changePositions.size() - 1) curChangePos++;
	else if (editor->cursor().line().handle() == changePositions.first().dlh()) curChangePos = 1;
	else curChangePos = 0;
	if (curChangePos >= 0 && curChangePos < changePositions.size())
		editor->setCursorPosition(changePositions[curChangePos].lineNumber(), changePositions[curChangePos].columnNumber());
}

void LatexEditorView::jumpChangePositionForward()
{
	for (int i = changePositions.size() - 1; i >= 0; i--)
		if (!changePositions[i].isValid()) {
			changePositions.removeAt(i);
			if (i <= curChangePos) curChangePos--;
		}
	if (curChangePos > 0) {
		curChangePos--;
		editor->setCursorPosition(changePositions[curChangePos].lineNumber(), changePositions[curChangePos].columnNumber());
	}
}

void LatexEditorView::jumpToBookmark(int bookmarkNumber)
{
	int markLine = editor->document()->findNextMark(bookMarkId(bookmarkNumber), editor->cursor().lineNumber(), editor->cursor().lineNumber() - 1);
	if (markLine >= 0) {
		emit saveCurrentCursorToHistoryRequested();
		editor->setCursorPosition(markLine, 0, false);
		editor->ensureCursorVisible(QEditor::NavigationToHeader);
		editor->setFocus();
	}
}

void LatexEditorView::removeBookmark(QDocumentLineHandle *dlh, int bookmarkNumber)
{
	if (!dlh)
		return;
	int rmid = bookMarkId(bookmarkNumber);
	if (hasBookmark(dlh, bookmarkNumber)) {
		document->removeMark(dlh, rmid);
        editor->removeMark(dlh,"bookmark");
		emit bookmarkRemoved(dlh);
	}
}

void LatexEditorView::removeBookmark(int lineNr, int bookmarkNumber)
{
	removeBookmark(document->line(lineNr).handle(), bookmarkNumber);
}

void LatexEditorView::addBookmark(int lineNr, int bookmarkNumber)
{
	int rmid = bookMarkId(bookmarkNumber);
    if (bookmarkNumber >= 0){
        int ln=document->findNextMark(rmid);
		document->line(ln).removeMark(rmid);
        editor->removeMark(document->line(ln).handle(),"bookmark");
    }
    if (!document->line(lineNr).hasMark(rmid)){
		document->line(lineNr).addMark(rmid);
        editor->addMark(document->line(lineNr).handle(),Qt::darkMagenta,"bookmark");
    }
}

bool LatexEditorView::hasBookmark(int lineNr, int bookmarkNumber)
{
	int rmid = bookMarkId(bookmarkNumber);
	return document->line(lineNr).hasMark(rmid);
}

bool LatexEditorView::hasBookmark(QDocumentLineHandle *dlh, int bookmarkNumber)
{
	if (!dlh)
		return false;
	int rmid = bookMarkId(bookmarkNumber);
	QList<int> m_marks = document->marks(dlh);
	return m_marks.contains(rmid);
}

bool LatexEditorView::toggleBookmark(int bookmarkNumber, QDocumentLine line)
{
	if (!line.isValid()) line = editor->cursor().line();
	int rmid = bookMarkId(bookmarkNumber);
	if (line.hasMark(rmid)) {
		line.removeMark(rmid);
        editor->removeMark(line.handle(),"bookmark");
		emit bookmarkRemoved(line.handle());
		return false;
	}
	if (bookmarkNumber >= 0) {
		int ln = editor->document()->findNextMark(rmid);
		if (ln >= 0) {
			editor->document()->line(ln).removeMark(rmid);
            editor->removeMark(editor->document()->line(ln).handle(),"bookmark");
			emit bookmarkRemoved(editor->document()->line(ln).handle());
		}
	}
	for (int i = -1; i < 10; i++) {
		int rmid = bookMarkId(i);
		if (line.hasMark(rmid)) {
			line.removeMark(rmid);
            editor->removeMark(line.handle(),"bookmark");
			emit bookmarkRemoved(line.handle());
		}
	}
	line.addMark(rmid);
    editor->addMark(line.handle(),Qt::darkMagenta,"bookmark");
	emit bookmarkAdded(line.handle(), bookmarkNumber);
	return true;
}

bool LatexEditorView::gotoLineHandleAndSearchCommand(const QDocumentLineHandle *dlh, const QSet<QString> &searchFor, const QString &id)
{
	if (!dlh) return false;
	int ln = dlh->document()->indexOf(dlh);
	if (ln < 0) return false;
	QString lineText = dlh->document()->line(ln).text();
	int col = 0;
	foreach (const QString &cmd, searchFor) {
		col = lineText.indexOf(cmd + "{" + id);
		if (col < 0) col = lineText.indexOf(QRegExp(QRegExp::escape(cmd) + "\\[[^\\]{}()\\\\]+\\]\\{" + QRegExp::escape(id))); //for \command[options]{id}
		if (col >= 0) {
			col += cmd.length() + 1;
			break;
		}
	}
	//Q_ASSERT(col >= 0);
	bool colFound = (col >= 0);
	if (col < 0) col = 0;
	editor->setCursorPosition(ln, col, false);
	editor->ensureCursorVisible(QEditor::Navigation);
	if (colFound) {
		QDocumentCursor highlightCursor(editor->cursor());
		highlightCursor.movePosition(id.length(), QDocumentCursor::NextCharacter, QDocumentCursor::KeepAnchor);
		temporaryHighlight(highlightCursor);
	}
	return true;
}

bool LatexEditorView::gotoToLabel(const QString &label)
{
	int cnt = document->countLabels(label);
	if (cnt == 0) return false;
	QMultiHash<QDocumentLineHandle *, int> result = document->getLabels(label);
	if (result.isEmpty()) return false;
	return gotoLineHandleAndSearchCommand(result.keys().first(), LatexParser::getInstance().possibleCommands["%label"], label);
}

bool LatexEditorView::gotoToBibItem(const QString &bibId)
{
	// only supports local bibitems. BibTeX has to be handled on a higher level
	QMultiHash<QDocumentLineHandle *, int> result = document->getBibItems(bibId);
	if (result.isEmpty()) return false;
	return gotoLineHandleAndSearchCommand(result.keys().first(), LatexParser::getInstance().possibleCommands["%bibitem"], bibId);
}

//collapse/expand every possible line
void LatexEditorView::foldEverything(bool unFold)
{
	QDocument *doc = editor->document();
	QLanguageDefinition *ld = doc->languageDefinition();
	QFoldedLineIterator fli = ld->foldedLineIterator(doc, 0);
	for (int i = 0; i < doc->lines(); i++, ++fli)
		if (fli.open) {
			if (unFold) ld->expand(doc, i);
			else ld->collapse(doc, i);
		}
}

//collapse/expand lines at the top level
void LatexEditorView::foldLevel(bool unFold, int level)
{
	QDocument *doc = editor->document();
	QLanguageDefinition *ld = doc->languageDefinition();
	for (QFoldedLineIterator fli = ld->foldedLineIterator(doc);
	        fli.line.isValid(); ++fli) {
		if (fli.openParentheses.size() == level && fli.open) {
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
void LatexEditorView::foldBlockAt(bool unFold, int line)
{
	editor->document()->foldBlockAt(unFold, line);
}

void LatexEditorView::zoomIn()
{
	editor->zoom(1);
}

void LatexEditorView::zoomOut()
{
	editor->zoom(-1);
}

void LatexEditorView::resetZoom()
{
	editor->resetZoom();
}

void LatexEditorView::cleanBib()
{
	QDocument *doc = editor->document();
	for (int i = doc->lines() - 1; i >= 0; i--) {
		QString trimLine = doc->line(i).text().trimmed();
		if (trimLine.startsWith("OPT") || trimLine.startsWith("ALT"))
			doc->execute(new QDocumentEraseCommand(i, 0, i + 1, 0, doc));
	}
	setFocus();
}

QList<QAction *> LatexEditorView::getBaseActions()
{
	if (!defaultInputBinding) return QList<QAction *>();
	return defaultInputBinding->baseActions;
}

void LatexEditorView::setBaseActions(QList<QAction *> baseActions)
{
	if (!defaultInputBinding) return;
	defaultInputBinding->baseActions = baseActions;
}

void LatexEditorView::setSpellerManager(SpellerManager *manager)
{
	spellerManager = manager;
	connect(spellerManager, SIGNAL(defaultSpellerChanged()), this, SLOT(reloadSpeller()));
}

bool LatexEditorView::setSpeller(const QString &name)
{
	if (!spellerManager) return false;

	useDefaultSpeller = (name == "<default>");

	SpellerUtility *su;
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
	documentContentChanged(0, editor->document()->lines());
	return true;
}

void LatexEditorView::reloadSpeller()
{
	if (useDefaultSpeller) {
		setSpeller("<default>");
		return;
	}

	SpellerUtility *su = qobject_cast<SpellerUtility *>(sender());
	if (!su) return;
	setSpeller(su->name());
}

QString LatexEditorView::getSpeller()
{
	if (useDefaultSpeller) return QString("<default>");
	return speller->name();
}

void LatexEditorView::setCompleter(LatexCompleter *newCompleter)
{
	LatexEditorView::completer = newCompleter;
}

LatexCompleter *LatexEditorView::getCompleter()
{
	return LatexEditorView::completer;
}

void LatexEditorView::updatePackageFormats()
{
	for (int i = 0; i < editor->document()->lines(); i++) {
		QList<QFormatRange> li = editor->document()->line(i).getOverlays();
		QString curLineText = editor->document()->line(i).text();
		for (int j = 0; j < li.size(); j++)
			if (li[j].format == packagePresentFormat || li[j].format == packageMissingFormat || li[j].format == packageUndefinedFormat) {
				int newFormat = packageUndefinedFormat;
				if (!latexPackageList->isEmpty()) {
					newFormat = latexPackageList->contains(curLineText.mid(li[j].offset, li[j].length)) ? packagePresentFormat : packageMissingFormat;
				}
				if (newFormat != li[j].format) {
					editor->document()->line(i).removeOverlay(li[j]);
					li[j].format = newFormat;
					editor->document()->line(i).addOverlay(li[j]);
				}
			}
	}
}

void LatexEditorView::clearLogMarks()
{
	setLogMarksVisible(false);
	logEntryToLine.clear();
	logEntryToMarkID.clear();
	lineToLogEntries.clear();
}

void LatexEditorView::addLogEntry(int logEntryNumber, int lineNumber, int markID)
{
	QDocumentLine l = editor->document()->line(lineNumber);
	lineToLogEntries.insert(l.handle(), logEntryNumber);
	logEntryToLine[logEntryNumber] = l.handle();
	logEntryToMarkID[logEntryNumber] = markID;
}

void LatexEditorView::setLogMarksVisible(bool visible)
{
	if (visible) {
		foreach (int logEntryNumber, logEntryToMarkID.keys()) {
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

void LatexEditorView::updateCitationFormats()
{
	for (int i = 0; i < editor->document()->lines(); i++) {
		QList<QFormatRange> li = editor->document()->line(i).getOverlays();
		QString curLineText = editor->document()->line(i).text();
		for (int j = 0; j < li.size(); j++)
			if (li[j].format == citationPresentFormat || li[j].format == citationMissingFormat) {
				int newFormat = document->bibIdValid(curLineText.mid(li[j].offset, li[j].length)) ? citationPresentFormat : citationMissingFormat;
				if (newFormat != li[j].format) {
					editor->document()->line(i).removeOverlay(li[j]);
					li[j].format = newFormat;
					editor->document()->line(i).addOverlay(li[j]);
				}
			}
	}
}

bool LatexEditorView::containsBibTeXId(QString id)
{
	return document->bibIdValid(id);
}

int LatexEditorView::bookMarkId(int bookmarkNumber)
{
	if (bookmarkNumber == -1) return  QLineMarksInfoCenter::instance()->markTypeId("bookmark"); //unnumbered mark
	else return QLineMarksInfoCenter::instance()->markTypeId("bookmark" + QString::number(bookmarkNumber));
	//return document->bookMarkId(bookmarkNumber);
}

void LatexEditorView::setLineMarkToolTip(const QString &tooltip)
{
	lineMarkPanel->setToolTipForTouchedMark(tooltip);
}

int LatexEditorView::environmentFormat, LatexEditorView::referencePresentFormat, LatexEditorView::referenceMissingFormat, LatexEditorView::referenceMultipleFormat, LatexEditorView::citationMissingFormat, LatexEditorView::citationPresentFormat, LatexEditorView::structureFormat, LatexEditorView::todoFormat, LatexEditorView::packageMissingFormat, LatexEditorView::packagePresentFormat, LatexEditorView::packageUndefinedFormat,
    LatexEditorView::wordRepetitionFormat, LatexEditorView::wordRepetitionLongRangeFormat, LatexEditorView::badWordFormat, LatexEditorView::grammarMistakeFormat, LatexEditorView::grammarMistakeSpecial1Format, LatexEditorView::grammarMistakeSpecial2Format, LatexEditorView::grammarMistakeSpecial3Format, LatexEditorView::grammarMistakeSpecial4Format,
    LatexEditorView::numbersFormat, LatexEditorView::verbatimFormat, LatexEditorView::commentFormat, LatexEditorView::pictureFormat, LatexEditorView::math_DelimiterFormat, LatexEditorView::math_KeywordFormat,
    LatexEditorView::pweaveDelimiterFormat, LatexEditorView::pweaveBlockFormat, LatexEditorView::sweaveDelimiterFormat, LatexEditorView::sweaveBlockFormat,
    LatexEditorView::asymptoteBlockFormat;
int LatexEditorView::syntaxErrorFormat, LatexEditorView::preEditFormat;
int LatexEditorView::deleteFormat, LatexEditorView::insertFormat, LatexEditorView::replaceFormat;

QList<int> LatexEditorView::grammarFormats;
QVector<bool> LatexEditorView::grammarFormatsDisabled;
QList<int> LatexEditorView::formatsList;

void LatexEditorView::updateSettings()
{
	lineNumberPanel->setVerboseMode(config->showlinemultiples != 10);
	editor->setFont(QFont(config->fontFamily, config->fontSize));
	editor->setLineWrapping(config->wordwrap > 0);
	editor->setSoftLimitedLineWrapping(config->wordwrap == 2);
	editor->setHardLineWrapping(config->wordwrap > 2);
	if (config->wordwrap > 1) {
		editor->setWrapAfterNumChars(config->lineWidth);
	} else {
		editor->setWrapAfterNumChars(0);
	}
	editor->setFlag(QEditor::AutoIndent, config->autoindent);
	editor->setFlag(QEditor::WeakIndent, config->weakindent);
	editor->setFlag(QEditor::ReplaceIndentTabs, config->replaceIndentTabs);
	editor->setFlag(QEditor::ReplaceTextTabs, config->replaceTextTabs);
	editor->setFlag(QEditor::AllowDragAndDrop, config->allowDragAndDrop);
	editor->setFlag(QEditor::MouseWheelZoom, config->mouseWheelZoom);
	editor->setFlag(QEditor::SmoothScrolling, config->smoothScrolling);
	editor->setFlag(QEditor::AutoInsertLRM, config->autoInsertLRM);
	editor->setFlag(QEditor::BidiVisualColumnMode, config->visualColumnMode);
	editor->setFlag(QEditor::OverwriteOpeningBracketFollowedByPlaceholder, config->overwriteOpeningBracketFollowedByPlaceholder);
	editor->setFlag(QEditor::OverwriteClosingBracketFollowingPlaceholder, config->overwriteClosingBracketFollowingPlaceholder);
	//TODO: parenmatch
	editor->setFlag(QEditor::AutoCloseChars, config->parenComplete);
	editor->setFlag(QEditor::ShowPlaceholders, config->showPlaceholders);
	editor->setDoubleClickSelectionType(config->doubleClickSelectionIncludeLeadingBackslash ? QDocumentCursor::WordOrCommandUnderCursor : QDocumentCursor::WordUnderCursor);
	editor->setTripleClickSelectionType((QList<QDocumentCursor::SelectionType>()
										<< QDocumentCursor::WordUnderCursor
										<< QDocumentCursor::WordOrCommandUnderCursor
										<< QDocumentCursor::ParenthesesInner
										<< QDocumentCursor::ParenthesesOuter
										<< QDocumentCursor::LineUnderCursor).at(qMax(0, qMin(4, config->tripleClickSelectionIndex))));
	editor->setIgnoreExternalChanges(!config->monitorFilesForExternalChanges);
	editor->setSilentReloadOnExternalChanges(config->silentReload);
	editor->setUseQSaveFile(config->useQSaveFile);
	editor->setHidden(false);
	editor->setCursorSurroundingLines(config->cursorSurroundLines);
	editor->setCursorBold(config->boldCursor);
	lineMarkPanelAction->setChecked((config->showlinemultiples != 0) || config->folding || config->showlinestate);
	lineNumberPanelAction->setChecked(config->showlinemultiples != 0);
	lineFoldPanelAction->setChecked(config->folding);
	lineChangePanelAction->setChecked(config->showlinestate);
	statusPanelAction->setChecked(config->showcursorstate);
	editor->setDisplayModifyTime(false);
	searchReplacePanel->setUseLineForSearch(config->useLineForSearch);
	searchReplacePanel->setSearchOnlyInSelection(config->searchOnlyInSelection);
	QDocument::setShowSpaces(config->showWhitespace ? (QDocument::ShowTrailing | QDocument::ShowLeading | QDocument::ShowTabs) : QDocument::ShowNone);
	QDocument::setTabStop(config->tabStop);
	QDocument::setLineSpacingFactor(config->lineSpacingPercent / 100.0);
	QDocument::setCenterDocumentInEditor(config->centerDocumentInEditor);

	editor->m_preEditFormat = preEditFormat;

	QDocument::setWorkAround(QDocument::DisableFixedPitchMode, config->hackDisableFixedPitch);
	QDocument::setWorkAround(QDocument::DisableWidthCache, config->hackDisableWidthCache);
	QDocument::setWorkAround(QDocument::DisableLineCache, config->hackDisableLineCache);
	QDocument::setWorkAround(QDocument::QImageCache, config->hackQImageCache);

	QDocument::setWorkAround(QDocument::ForceQTextLayout, config->hackRenderingMode == 1);
	QDocument::setWorkAround(QDocument::ForceSingleCharacterDrawing, config->hackRenderingMode == 2);
	LatexDocument::syntaxErrorFormat = syntaxErrorFormat;
	if (document)
		document->updateSettings();
}

void LatexEditorView::updateFormatSettings()
{
	static bool formatsLoaded = false;
	if (!formatsLoaded) {
		REQUIRE(QDocument::defaultFormatScheme());
#define F(n) &n##Format, #n,
		const void *formats[] = {F(environment)
		                         F(referenceMultiple) F(referencePresent) F(referenceMissing)
		                         F(citationPresent) F(citationMissing)
		                         F(packageMissing) F(packagePresent)
		                         &packageUndefinedFormat, "normal",
		                         &syntaxErrorFormat, "latexSyntaxMistake", //TODO: rename all to xFormat, "x"
		                         F(structure)
		                         &todoFormat, "commentTodo",
		                         &deleteFormat, "diffDelete",
		                         &insertFormat, "diffAdd",
		                         &replaceFormat, "diffReplace",
		                         F(wordRepetition) F(wordRepetitionLongRange) F(badWord)
		                         F(grammarMistake)
		                         F(grammarMistakeSpecial1) F(grammarMistakeSpecial2) F(grammarMistakeSpecial3) F(grammarMistakeSpecial4)
		                         F(numbers) F(verbatim) F(comment) F(picture)
		                         &pweaveDelimiterFormat, "pweave-delimiter",
		                         &pweaveBlockFormat, "pweave-block",
		                         &sweaveDelimiterFormat, "sweave-delimiter",
		                         &sweaveBlockFormat, "sweave-block",
		                         &math_DelimiterFormat, "math-delimiter",
		                         &math_KeywordFormat, "math-keyword",
		                         &asymptoteBlockFormat, "asymptote:block",
		                         &preEditFormat, "preedit",
                                 nullptr, nullptr
		                        };
#undef F
		const void **temp = formats;
		while (*temp) {
			int *c = (static_cast<int *>(const_cast<void *>(*temp)));
            Q_ASSERT(c != nullptr);
			*c = QDocument::defaultFormatScheme()->id(QString(static_cast<const char *>(*(temp + 1))));
			temp += 2;
		}
		//int f=QDocument::formatFactory()->id("citationMissing");
		formatsLoaded = true;
		grammarFormats << wordRepetitionFormat << wordRepetitionLongRangeFormat << badWordFormat << grammarMistakeFormat << grammarMistakeSpecial1Format << grammarMistakeSpecial2Format << grammarMistakeSpecial3Format << grammarMistakeSpecial4Format; //don't change the order, it corresponds to GrammarErrorType
		grammarFormatsDisabled.resize(9);
		grammarFormatsDisabled.fill(false);
		formatsList << SpellerUtility::spellcheckErrorFormat << referencePresentFormat << citationPresentFormat << referenceMissingFormat;
		formatsList << referenceMultipleFormat << citationMissingFormat << packageMissingFormat << packagePresentFormat << packageUndefinedFormat << environmentFormat;
		formatsList << wordRepetitionFormat << structureFormat << todoFormat << insertFormat << deleteFormat << replaceFormat;
		LatexDocument::syntaxErrorFormat = syntaxErrorFormat;
	}
}

void LatexEditorView::requestCitation()
{
	QString id = editor->cursor().selectedText();
	emit needCitation(id);
}

void LatexEditorView::openExternalFile()
{
	QAction *act = qobject_cast<QAction *>(sender());
	QString name = act->data().toString();
	if (!name.isEmpty())
		emit openFile(name);
}

void LatexEditorView::openPackageDocumentation(QString package)
{
	QString command;
	if (package.isEmpty()) {
		QAction *act = qobject_cast<QAction *>(sender());
		if (!act) return;
		package = act->data().toString();
	}
	if (package.contains("#")) {
		int i = package.indexOf("#");
		command = package.mid(i + 1);
		package = package.left(i);
	}
	// replace some package denominations
	if (package == "latex-document" || package == "latex-dev" || package == "latex-mathsymbols")
		package = "latex2e";
	if (package == "class-scrartcl,scrreprt,scrbook")
		package = "scrartcl";
	if (package.startsWith("class-"))
		package = package.mid(6);
	if (!package.isEmpty()) {
		if (config->texdocHelpInInternalViewer) {
			QString docfile = Help::packageDocFile(package);
			if (docfile.isEmpty())
				return;
			if (docfile.endsWith(".pdf"))
				emit openInternalDocViewer(docfile, command);
			else
				Help::instance()->viewTexdoc(package); // fallback e.g. for dvi
		} else {
			Help::instance()->viewTexdoc(package);
		}
	}
}

void LatexEditorView::emitChangeDiff()
{
	QAction *act = qobject_cast<QAction *>(sender());
	QPoint pt = act->data().toPoint();
	emit changeDiff(pt);
}

void LatexEditorView::emitGotoDefinitionFromAction()
{
	QDocumentCursor c;
	QAction *act = qobject_cast<QAction *>(sender());
	if (act) {
		c = act->data().value<QDocumentCursor>();
	}
	emit gotoDefinition(c);
}

void LatexEditorView::emitFindLabelUsagesFromAction()
{
	QAction *action = qobject_cast<QAction *>(sender());
	if (!action) return;
	QString labelText = action->data().toString();
	LatexDocument *doc = action->property("doc").value<LatexDocument *>();
	emit findLabelUsages(doc, labelText);
}

void LatexEditorView::emitSyncPDFFromAction()
{
	QDocumentCursor c;
	QAction *act = qobject_cast<QAction *>(sender());
	if (act) {
		c = act->data().value<QDocumentCursor>();
	}
	emit syncPDFRequested(c);
}

void LatexEditorView::lineMarkClicked(int line)
{
	QDocumentLine l = editor->document()->line(line);
	if (!l.isValid()) return;
	//remove old mark (when possible)
	for (int i = -1; i < 10; i++)
		if (l.hasMark(bookMarkId(i))) {
			l.removeMark(bookMarkId(i));
            editor->removeMark(l.handle(),"bookmark");
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
	for (int i = 1; i <= 10; i++) {
		if (editor->document()->findNextMark(bookMarkId(i % 10)) < 0) {
			l.addMark(bookMarkId(i % 10));
            editor->addMark(l.handle(),Qt::darkMagenta,"bookmark");
			emit bookmarkAdded(l.handle(), i);
			return;
		}
	}
	l.addMark(bookMarkId(-1));
    editor->addMark(l.handle(),Qt::darkMagenta,"bookmark");
	emit bookmarkAdded(l.handle(), -1);
}

void LatexEditorView::lineMarkToolTip(int line, int mark)
{
	if (line < 0 || line >= editor->document()->lines()) return;
	int errorMarkID = QLineMarksInfoCenter::instance()->markTypeId("error");
	int warningMarkID = QLineMarksInfoCenter::instance()->markTypeId("warning");
	int badboxMarkID = QLineMarksInfoCenter::instance()->markTypeId("badbox");
	if (mark != errorMarkID && mark != warningMarkID && mark != badboxMarkID) return;
	QList<int> errors = lineToLogEntries.values(editor->document()->line(line).handle());
	if (!errors.isEmpty())
		emit showMarkTooltipForLogMessage(errors);
}

void LatexEditorView::clearOverlays()
{
	for (int i = 0; i < editor->document()->lineCount(); i++) {
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
		line.clearOverlays(todoFormat);
		foreach (const int f, grammarFormats)
			line.clearOverlays(f);
	}
}

/*!
	Will be called from certain events, that should maybe result in opening the
	completer. Since the completer depends on the context, the caller doesn't
	have to be sure that a completer is really necassary. The context is checked
	in this function and an appropriate completer is opened if necessary.
	For example, typing a colon within a citation should start the completer.
	Therefore, typing a colon will trigger this function. It's checked in here
	if the context is a citation.
 */
void LatexEditorView::mayNeedToOpenCompleter(bool fromSingleChar)
{
	QDocumentCursor c = editor->cursor();
	QDocumentLineHandle *dlh = c.line().handle();
	if (!dlh)
		return;
	TokenStack ts = Parsing::getContext(dlh, c.columnNumber());
	Token tk;
	if (!ts.isEmpty()) {
		tk = ts.top();
        if(fromSingleChar && tk.length!=1){
            return; // only open completer on first char
        }
		if (tk.type == Token::word && tk.subtype == Token::none && ts.size() > 1) {
			// set brace type
			ts.pop();
			tk = ts.top();
		}
    }else{
        return; // no context available
    }

	Token::TokenType type = tk.type;
	if (tk.subtype != Token::none)
		type = tk.subtype;

	QList<Token::TokenType> lst;
	lst << Token::package << Token::keyValArg << Token::keyVal_val << Token::keyVal_key << Token::bibItem << Token::labelRefList;
    if(fromSingleChar){
        lst << Token::labelRef;
    }
	if (lst.contains(type))
		emit openCompleter();
    if (ts.isEmpty() || fromSingleChar)
		return;
	ts.pop();
	if (!ts.isEmpty()) { // check next level if 1. check fails (e.g. key vals are set to real value)
		tk = ts.top();
		type = tk.type;
		if (lst.contains(type))
			emit openCompleter();
	}
}

void LatexEditorView::documentContentChanged(int linenr, int count)
{
	Q_ASSERT(editor);
	QDocumentLine startline = editor->document()->line(linenr);
	if ((linenr >= 0 || count < editor->document()->lines()) && editor->cursor().isValid() &&
	        !editor->cursor().atLineStart() && editor->cursor().line().text().trimmed().length() > 0 &&
	        startline.isValid()) {
		bool add = false;
		if (changePositions.size() <= 0) add = true;
		else if (curChangePos < 1) {
			if (changePositions.first().dlh() != startline.handle()) add = true;
			else changePositions.first().setColumnNumber(editor->cursor().columnNumber());
		} else if (curChangePos >= changePositions.size() - 1) {
			if (changePositions.last().dlh() != startline.handle()) add = true;
			else changePositions.last().setColumnNumber(editor->cursor().columnNumber());
		}  else if (changePositions[curChangePos].dlh() == startline.handle()) changePositions[curChangePos].setColumnNumber(editor->cursor().columnNumber());
		else if (changePositions[curChangePos + 1].dlh() == startline.handle()) changePositions[curChangePos + 1].setColumnNumber(editor->cursor().columnNumber());
		else add = true;
		if (add) {
			curChangePos = -1;
			changePositions.insert(0, CursorPosition(editor->document()->cursor(linenr, editor->cursor().columnNumber())));
			if (changePositions.size() > 20) changePositions.removeLast();
		}
	}

	if (autoPreviewCursor.size() > 0) {
		for (int i = 0; i < autoPreviewCursor.size(); i++) {
			const QDocumentCursor &c = autoPreviewCursor[i];
			if (c.lineNumber() >= linenr && c.anchorLineNumber() < linenr + count)
				emit showPreview(c); //may modify autoPreviewCursor
		}

	}

	// checking
	if (!QDocument::defaultFormatScheme()) return;
	if (!config->realtimeChecking) return; //disable all => implicit disable environment color correction (optimization)
	const LatexDocument *ldoc = qobject_cast<const LatexDocument *>(editor->document());
	bool latexLikeChecking = ldoc && ldoc->languageIsLatexLike();
	if (!latexLikeChecking && !config->inlineCheckNonTeXFiles) return;

	if (config->inlineGrammarChecking) {
		QList<LineInfo> changedLines;
		int lookBehind = 0;
		for (; linenr - lookBehind >= 0; lookBehind++)
			if (editor->document()->line(linenr - lookBehind).firstChar() == -1) break;
		if (lookBehind > 0) lookBehind--;
		if (lookBehind > linenr) lookBehind = linenr;

		LIST_RESERVE(changedLines, linenr + count + lookBehind + 1);
		int truefirst = linenr - lookBehind;
		for (int i = linenr - lookBehind; i < editor->document()->lineCount(); i++) {
			QDocumentLine line = editor->document()->line(i);
			if (!line.isValid()) break;
			LineInfo temp;
			temp.line = line.handle();
			temp.text = line.text();
            // blank irrelevant content, i.e. commands, non-text, comments, verbatim
            QDocumentLineHandle *dlh = line.handle();
            TokenList tl = dlh->getCookie(QDocumentLine::LEXER_COOKIE).value<TokenList>();
            foreach(Token tk,tl){
                if(tk.type==Token::word && (tk.subtype==Token::none||tk.subtype==Token::text))
                    continue;
                if(tk.type==Token::punctuation && (tk.subtype==Token::none||tk.subtype==Token::text))
                    continue;
                if(tk.type==Token::symbol && (tk.subtype==Token::none||tk.subtype==Token::text))
                    continue; // don't blank symbol like '~'
                if(tk.type==Token::braces && tk.subtype==Token::text){
                    //remove braces around text argument
                    temp.text.replace(tk.start,1,QString(' '));
                    temp.text.replace(tk.start+tk.length-1,1,QString(' '));
                    continue;
                }
                temp.text.replace(tk.start,tk.length,QString(tk.length,' '));
            }

			changedLines << temp;
			if (line.firstChar() == -1) {
				emit linesChanged(speller->name(), document, changedLines, truefirst);
				truefirst += changedLines.size();
				changedLines.clear();
				if (i >= linenr + count) break;
			}
		}
		if (!changedLines.isEmpty())
			emit linesChanged(speller->name(), document, changedLines, truefirst);

	}

	Q_ASSERT(speller);
	for (int i = linenr; i < linenr + count; i++) {
		QDocumentLine line = editor->document()->line(i);
		if (!line.isValid()) continue;

		//remove all overlays used for latex things, in descending frequency
		line.clearOverlays(formatsList); //faster as it avoids multiple lock/unlock operations
	}

	for (int i = linenr; i < linenr + count; i++) {
		QDocumentLine line = editor->document()->line(i);
		if (!line.isValid()) continue;

		bool addedOverlaySpellCheckError = false;
		bool addedOverlayReference = false;
		bool addedOverlayCitation = false;
		bool addedOverlayEnvironment = false;
		bool addedOverlayStructure = false;
		bool addedOverlayTodo = false;
		bool addedOverlayPackage = false;

		// diff presentation
		QVariant cookie = line.getCookie(QDocumentLine::DIFF_LIST_COOCKIE);
		if (!cookie.isNull()) {
			DiffList diffList = cookie.value<DiffList>();
			for (int i = 0; i < diffList.size(); i++) {
				DiffOp op = diffList.at(i);
				switch (op.type) {
				case DiffOp::Delete:
					line.addOverlay(QFormatRange(op.start, op.length, deleteFormat));
					break;
				case DiffOp::Insert:
					line.addOverlay(QFormatRange(op.start, op.length, insertFormat));
					break;
				case DiffOp::Replace:
					line.addOverlay(QFormatRange(op.start, op.length, replaceFormat));
					break;
				default:
					;
				}

			}
		}
        // handle % TODO
        QLineFormatAnalyzer lineFormatAnaylzer(line.getFormats());
        int col = lineFormatAnaylzer.firstCol(commentFormat);
        if(col>=0){
            QString curLine=line.text();
            QString text = curLine.mid(col, lineFormatAnaylzer.formatLength(col));
            QString regularExpression=ConfigManagerInterface::getInstance()->getOption("Editor/todo comment regExp").toString();
            QRegExp rx(regularExpression);
            if (rx.indexIn(text)==0) {
                line.addOverlay(QFormatRange(col, lineFormatAnaylzer.formatLength(col), todoFormat));
                addedOverlayTodo = true;
            }
        }

		// alternative context detection
		QDocumentLineHandle *dlh = line.handle();
		TokenList tl = dlh->getCookie(QDocumentLine::LEXER_COOKIE).value<TokenList>();
		for (int tkNr = 0; tkNr < tl.length(); tkNr++) {
			Token tk = tl.at(tkNr);
			if (tk.subtype == Token::verbatim)
				continue;
			if (tk.type == Token::comment)
				break;
			if (latexLikeChecking) {
                if ((tk.subtype == Token::title || tk.subtype == Token::shorttitle) && (tk.type == Token::braces || tk.type == Token::openBrace)) {
					line.addOverlay(QFormatRange(tk.innerStart(), tk.innerLength(), structureFormat));
					addedOverlayStructure = true;
				}
				if (tk.subtype == Token::todo && (tk.type == Token::braces || tk.type == Token::openBrace)) {
					line.addOverlay(QFormatRange(tk.innerStart(), tk.innerLength(), todoFormat));
					addedOverlayTodo = true;
				}
				if (tk.type == Token::env || tk.type == Token::beginEnv) {
					line.addOverlay(QFormatRange(tk.start, tk.length, environmentFormat));
					addedOverlayEnvironment = true;
				}
				if ((tk.type == Token::package || tk.type == Token::beamertheme || tk.type == Token::documentclass) && config->inlinePackageChecking) {
					// package
					QString preambel;
					if (tk.type == Token::beamertheme) { // special treatment for  \usetheme
						preambel = "beamertheme";
					}
					QString text = dlh->text();
					QString rpck =  trimLeft(text.mid(tk.start, tk.length)); // left spaces are ignored by \cite, right space not
					//check and highlight
					if (latexPackageList->isEmpty())
						dlh->addOverlay(QFormatRange(tk.start, tk.length, packageUndefinedFormat));
					else if (latexPackageList->contains(preambel + rpck))
						dlh->addOverlay(QFormatRange(tk.start, tk.length, packagePresentFormat));
					else
						dlh->addOverlay(QFormatRange(tk.start, tk.length, packageMissingFormat));

					addedOverlayPackage = true;
				}
				if ((tk.type == Token::labelRef || tk.type == Token::labelRefList) && config->inlineReferenceChecking) {
					QDocumentLineHandle *dlh = tk.dlh;
					QString ref = dlh->text().mid(tk.start, tk.length);
					if (ref.contains('#')) continue;  // don't highlight refs in definitions e.g. in \newcommand*{\FigRef}[1]{figure~\ref{#1}}
					int cnt = document->countLabels(ref);
					if (cnt > 1) {
						dlh->addOverlay(QFormatRange(tk.start, tk.length, referenceMultipleFormat));
					} else if (cnt == 1) dlh->addOverlay(QFormatRange(tk.start, tk.length, referencePresentFormat));
					else dlh->addOverlay(QFormatRange(tk.start, tk.length, referenceMissingFormat));
					addedOverlayReference = true;
				}
				if (tk.type == Token::label && config->inlineReferenceChecking) {
					QDocumentLineHandle *dlh = tk.dlh;
					QString ref = dlh->text().mid(tk.start, tk.length);
					int cnt = document->countLabels(ref);
					if (cnt > 1) {
						dlh->addOverlay(QFormatRange(tk.start, tk.length, referenceMultipleFormat));
					} else dlh->addOverlay(QFormatRange(tk.start, tk.length, referencePresentFormat));
					// look for corresponding reeferences and adapt format respectively
					//containedLabels->updateByKeys(QStringList(ref),containedReferences);
					document->updateRefsLabels(ref);
					addedOverlayReference = true;
				}
				if (tk.type == Token::bibItem && config->inlineCitationChecking) {
					QDocumentLineHandle *dlh = tk.dlh;
					QString text = dlh->text().mid(tk.start, tk.length);
					if (text.contains('#')) continue; // don't highlight cite in definitions e.g. in \newcommand*{\MyCite}[1]{see~\cite{#1}}
					QString rcit =  trimLeft(text); // left spaces are ignored by \cite, right space not
					//check and highlight
					if (document->bibIdValid(rcit))
						dlh->addOverlay(QFormatRange(tk.start, tk.length, citationPresentFormat));
					else
						dlh->addOverlay(QFormatRange(tk.start, tk.length, citationMissingFormat));
					addedOverlayCitation = true;
				}
			}// if latexLineCheking
            int tkLength=tk.length;
            if (tk.type == Token::word && (tk.subtype == Token::text || tk.subtype == Token::title || tk.subtype == Token::shorttitle || tk.subtype == Token::todo || tk.subtype == Token::none)  && config->inlineSpellChecking && tk.length >= 3 && speller) {
				QString word = tk.getText();
                if(tkNr+1 < tl.length()){
                    //check if next token is . or -
                    Token tk1 = tl.at(tkNr+1);
                    if(tk1.type==Token::punctuation && tk1.start==(tk.start+tk.length) && !word.endsWith("\"")){
                        QString add=tk1.getText();
                        if(add=="."||add=="-"){
                            word+=add;
                            tkNr++;
                            tkLength+=tk1.length;
                        }
                        if(add=="'"){
                            if(tkNr+2 < tl.length()){
                                Token tk2 = tl.at(tkNr+2);
                                if(tk2.type==Token::word && tk2.start==(tk1.start+tk1.length)){
                                    add+=tk2.getText();
                                    word+=add;
                                    tkNr+=2;
                                    tkLength+=tk1.length+tk2.length;
                                }
                            }
                        }
                    }
                }
				word = latexToPlainWordwithReplacementList(word, mReplacementList); //remove special chars
				if (config->hideNonTextSpellingErrors && (isNonTextFormat(line.getFormatAt(tk.start)) || isNonTextFormat(line.getFormatAt(tk.start + tk.length - 1)) )) // TODO:needs to be adapted
					continue;
				if (!speller->check(word) ) {
					if (word.endsWith('-') && speller->check(word.left(word.length() - 1)))
						continue; // word ended with '-', without that letter, word is correct (e.g. set-up / german hypehantion)
                    if(word.endsWith('.')){
                        tkLength--; // don't take point into misspelled word
                    }
                    line.addOverlay(QFormatRange(tk.start, tkLength, SpellerUtility::spellcheckErrorFormat));
					addedOverlaySpellCheckError = true;
				}
			}
		} // for Tokenslist

		//update wrapping if the an overlay changed the width of the text
		//TODO: should be handled by qce to be consistent (with syntax check and search)
		if (!editor->document()->getFixedPitch() && editor->flag(QEditor::LineWrap)) {
			bool updateWrapping = false;
			QFormatScheme *ff = QDocument::defaultFormatScheme();
			REQUIRE(ff);
			updateWrapping |= addedOverlaySpellCheckError && ff->format(SpellerUtility::spellcheckErrorFormat).widthChanging();
			updateWrapping |= addedOverlayReference && (ff->format(referenceMissingFormat).widthChanging() || ff->format(referencePresentFormat).widthChanging() || ff->format(referenceMultipleFormat).widthChanging());
			updateWrapping |= addedOverlayCitation && (ff->format(citationPresentFormat).widthChanging() || ff->format(citationMissingFormat).widthChanging());
			updateWrapping |= addedOverlayPackage && (ff->format(packagePresentFormat).widthChanging() || ff->format(packageMissingFormat).widthChanging());
			updateWrapping |= addedOverlayEnvironment && ff->format(environmentFormat).widthChanging();
			updateWrapping |= addedOverlayStructure && ff->format(structureFormat).widthChanging();
			updateWrapping |= addedOverlayTodo && ff->format(todoFormat).widthChanging();
			if (updateWrapping)
				line.handle()->updateWrapAndNotifyDocument(i);

		}
	}
	editor->document()->markViewDirty();
}

void LatexEditorView::lineDeleted(QDocumentLineHandle *l)
{
	QHash<QDocumentLineHandle *, int>::iterator it;
	while ((it = lineToLogEntries.find(l)) != lineToLogEntries.end()) {
		logEntryToLine.remove(it.value());
		lineToLogEntries.erase(it);
	}

	//QMessageBox::information(0,QString::number(nr),"",0);
	for (int i = changePositions.size() - 1; i >= 0; i--)
		if (changePositions[i].dlh() == l)
			/*if (QDocumentLine(changePositions[i].first).previous().isValid()) changePositions[i].first=QDocumentLine(changePositions[i].first).previous().handle();
			else if (QDocumentLine(changePositions[i].first).next().isValid()) changePositions[i].first=QDocumentLine(changePositions[i].first).next().handle();
			else  */ //creating a QDocumentLine with a deleted handle is not possible (it will modify the handle reference count which will trigger another delete event, leading to an endless loop)
			changePositions.removeAt(i);
	//    QMessageBox::information(0,"trig",0);

	emit lineHandleDeleted(l);
	editor->document()->markViewDirty();
}
void LatexEditorView::textReplaceFromAction()
{
	QAction *action = qobject_cast<QAction *>(QObject::sender());
	if (editor && action) {
		QString replacementText = action->data().toString();
		if (replacementText.isEmpty()) editor->cursor().removeSelectedText();
		else editor->write(replacementText);
		editor->setCursor(editor->cursor()); //to remove selection range
	}
}

void LatexEditorView::spellCheckingAlwaysIgnore()
{
	if (speller && editor && editor->cursor().hasSelection() && (editor->cursor().selectedText() == defaultInputBinding->lastSpellCheckedWord)) {
		QString newToIgnore = editor->cursor().selectedText();
		speller->addToIgnoreList(newToIgnore);
	}
}

void LatexEditorView::addReplaceActions(QMenu *menu, const QStringList &replacements, bool italic)
{
	if (!menu) return;
    QAction *before = nullptr;
	if (!menu->actions().isEmpty()) before = menu->actions()[0];

	foreach (const QString &text, replacements) {
		QAction *replaceAction = new QAction(this);
		if (text.isEmpty()) {
			replaceAction->setText(tr("Delete"));
			QFont deleteFont;
			deleteFont.setItalic(italic);
			replaceAction->setFont(deleteFont);
		} else {
			replaceAction->setText(text);
			QFont correctionFont;
			correctionFont.setBold(true);
			correctionFont.setItalic(italic);
			replaceAction->setFont(correctionFont);
		}
		replaceAction->setData(text);
		connect(replaceAction, SIGNAL(triggered()), this, SLOT(textReplaceFromAction()));
		menu->insertAction(before, replaceAction);
	}
}

void LatexEditorView::populateSpellingMenu()
{
	QMenu *menu = qobject_cast<QMenu *>(sender());
	if (!menu) return;
	QString word = menu->property("word").toString();
	if (word.isEmpty()) return;
	addSpellingActions(menu, word, true);
}

void LatexEditorView::addSpellingActions(QMenu *menu, QString word, bool dedicatedMenu)
{
	if (menu->property("isSpellingPopulated").toBool()) return;

	QStringList suggestions = speller->suggest(word);
	addReplaceActions(menu, suggestions, false);

	QAction *act = new QAction(LatexEditorView::tr("Add to Dictionary"), menu);
	connect(act, SIGNAL(triggered()), this, SLOT(spellCheckingAlwaysIgnore()));
	if (dedicatedMenu) {
		menu->addSeparator();
	} else {
		QFont ignoreFont;
		ignoreFont.setItalic(true);
		act->setFont(ignoreFont);
	}
	menu->addAction(act);
	menu->setProperty("isSpellingPopulated", true);
}

void LatexEditorView::spellRemoveMarkers(const QString &newIgnoredWord)
{
	REQUIRE(editor);
	QDocument* doc = editor->document();
	if (!doc) return;
	//documentContentChanged(editor->cursor().lineNumber(),1);
	for (int i = 0; i < doc->lines(); i++) {
		QList<QFormatRange> li = doc->line(i).getOverlays(SpellerUtility::spellcheckErrorFormat);
		QString curLineText = doc->line(i).text();
		for (int j = 0; j < li.size(); j++)
			if (latexToPlainWord(curLineText.mid(li[j].offset, li[j].length)) == newIgnoredWord) {
				doc->line(i).removeOverlay(li[j]);
				doc->line(i).setFlag(QDocumentLine::LayoutDirty, true);
			}
	}
	editor->viewport()->update();
}

void LatexEditorView::closeCompleter()
{
	completer->close();
}

/*
 * Extracts the math formula at the given cursor position including math delimiters.
 * Current limitations: the cursor needs to be on one of the delimiters. This does
 * not work for math environments
 * Returns an empty string if there is no math formula.
 */
QString LatexEditorView::extractMath(QDocumentCursor cursor)
{
	if (cursor.line().getFormatAt(cursor.columnNumber()) != math_DelimiterFormat)
		return QString();
	int col = cursor.columnNumber();
	while (col > 0 && cursor.line().getFormatAt(col - 1) == math_DelimiterFormat) col--;
	cursor.setColumnNumber(col);
	return parenthizedTextSelection(cursor).selectedText();
}

bool LatexEditorView::showMathEnvPreview(QDocumentCursor cursor, QString command, QString environment, QPoint pos)
{
    QStringList envAliases = document->lp.environmentAliases.values(environment);
	if (((command == "\\begin" || command == "\\end") && envAliases.contains("math")) || command == "\\[" || command == "\\]" || command == "$") {
		while (!cursor.atLineStart() && cursor.nextChar() != '\\') {
			cursor.movePosition(1, QDocumentCursor::PreviousCharacter);
		}
		QString text = parenthizedTextSelection(cursor).selectedText();
		if (!text.isEmpty()) {
			m_point = editor->mapToGlobal(editor->mapFromFrame(pos));
			emit showPreview(text);
			return true;
		}
	} else {
		QToolTip::hideText();
	}
	return false;
}

void LatexEditorView::mouseHovered(QPoint pos)
{
	// reimplement to what is necessary

	if (pos.x() < 0) return; // hover event on panel
	QDocumentCursor cursor;
	cursor = editor->cursorForPosition(editor->mapToContents(pos));
	QString line = cursor.line().text();
	QDocumentLine l = cursor.line();

	QFormatRange fr = cursor.line().getOverlayAt(cursor.columnNumber(), replaceFormat);
	if (fr.length > 0 && fr.format == replaceFormat) {
		QVariant var = l.getCookie(QDocumentLine::DIFF_LIST_COOCKIE);
		if (var.isValid()) {
			DiffList diffList = var.value<DiffList>();
			DiffOp op;
			op.start = -1;
			foreach (op, diffList) {
				if (op.start <= cursor.columnNumber() && op.start + op.length >= cursor.columnNumber()) {
					break;
				}
				op.start = -1;
			}

			if (op.start >= 0 && !op.text.isEmpty()) {
				QString message = op.text;
				QToolTip::showText(editor->mapToGlobal(editor->mapFromFrame(pos)), message);
				return;
			}
		}
	}
	foreach (const int f, grammarFormats) {
		fr = cursor.line().getOverlayAt(cursor.columnNumber(), f);
		if (fr.length > 0 && fr.format == f) {
			QVariant var = l.getCookie(QDocumentLine::GRAMMAR_ERROR_COOKIE);
			if (var.isValid()) {
				const QList<GrammarError> &errors = var.value<QList<GrammarError> >();
				for (int i = 0; i < errors.size(); i++)
					if (errors[i].offset <= cursor.columnNumber() && errors[i].offset + errors[i].length >= cursor.columnNumber()) {
						QString message = errors[i].message;
						QToolTip::showText(editor->mapToGlobal(editor->mapFromFrame(pos)), message);
						return;
					}
			}
		}
	}
	// check for latex error
	//syntax checking
	fr = cursor.line().getOverlayAt(cursor.columnNumber(), syntaxErrorFormat);
	if (fr.length > 0 && fr.format == syntaxErrorFormat) {
		StackEnvironment env;
		document->getEnv(cursor.lineNumber(), env);
		TokenStack remainder;
		int i = cursor.lineNumber();
		if (document->line(i - 1).handle())
			remainder = document->line(i - 1).handle()->getCookieLocked(QDocumentLine::LEXER_REMAINDER_COOKIE).value<TokenStack >();
		QString text = l.text();
		if (!text.isEmpty()) {
			QString message = document->getErrorAt(l.handle(), cursor.columnNumber(), env, remainder);
			QToolTip::showText(editor->mapToGlobal(editor->mapFromFrame(pos)), message);
			return;
		}
	}
	// new way
	QDocumentLineHandle *dlh = cursor.line().handle();

	TokenList tl = dlh ? dlh->getCookieLocked(QDocumentLine::LEXER_COOKIE).value<TokenList>() : TokenList();

	//Tokens tk=getTokenAtCol(dlh,cursor.columnNumber());
	TokenStack ts = Parsing::getContext(dlh, cursor.columnNumber());
	Token tk;
	if (!ts.isEmpty()) {
		tk = ts.top();
	}

	LatexParser &lp = LatexParser::getInstance();
	QString command, value;
	bool handled = false;
	if (tk.type != Token::none) {
		int tkPos = tl.indexOf(tk);
		if (tk.type == Token::command || tk.type == Token::commandUnknown) {
			handled = true;
			command = line.mid(tk.start, tk.length);
			CommandDescription cd = lp.commandDefs.value(command);
			if (cd.args > 0)
				value = Parsing::getArg(tl.mid(tkPos + 1), dlh, 0, ArgumentList::Mandatory);
			if (config->toolTipPreview && showMathEnvPreview(cursor, command, value, pos)) {
				; // action is already performed as a side effect
			} else if (config->toolTipHelp && completer->getLatexReference()) {
				QString topic = completer->getLatexReference()->getTextForTooltip(command);
				if (!topic.isEmpty()) QToolTip::showText(editor->mapToGlobal(editor->mapFromFrame(pos)), topic);
			}
		}
		value = tk.getText();
		if (tk.type == Token::env || tk.type == Token::beginEnv) {
			handled = true;
			if (config->toolTipPreview && showMathEnvPreview(cursor, "\\begin", value, pos)) {
				; // action is already performed as a side effect
			} else if (config->toolTipHelp && completer->getLatexReference()) {
				QString topic = completer->getLatexReference()->getTextForTooltip("\\begin{" + value);
				if (!topic.isEmpty()) QToolTip::showText(editor->mapToGlobal(editor->mapFromFrame(pos)), topic);
			}
		}
		if (tk.type == Token::labelRef || tk.type == Token::labelRefList) {
			handled = true;
			int cnt = document->countLabels(value);
			QString mText = "";
			if (cnt == 0) {
				mText = tr("label missing!");
			} else if (cnt > 1) {
				mText = tr("label multiple times defined!");
			} else {
				QMultiHash<QDocumentLineHandle *, int> result = document->getLabels(value);
				QDocumentLineHandle *mLine = result.keys().first();
				int l = mLine->document()->indexOf(mLine);
				LatexDocument *doc = qobject_cast<LatexDocument *> (editor->document());
				if (mLine->document() != editor->document()) {
					doc = document->parent->findDocument(mLine->document());
					if (doc) mText = tr("<p style='white-space:pre'><b>Filename: %1</b>\n").arg(doc->getFileName());
				}
				if (doc)
					mText += doc->exportAsHtml(doc->cursor(qMax(0, l - 2), 0, l + 2), true, true, 60);
			}
			QToolTip::showText(editor->mapToGlobal(editor->mapFromFrame(pos)), mText);
		}
		if (tk.type == Token::label) {
			handled = true;
			if (document->countLabels(value) > 1) {
				QToolTip::showText(editor->mapToGlobal(editor->mapFromFrame(pos)), tr("label multiple times defined!"));
			} else {
				int cnt = document->countRefs(value);
				QToolTip::showText(editor->mapToGlobal(editor->mapFromFrame(pos)), tr("%n reference(s) to this label", "", cnt));
			}
		}
		if (tk.type == Token::package || tk.type == Token::beamertheme || tk.type == Token::documentclass) {
			handled = true;
			QString type = (tk.type == Token::documentclass) ? tr("Class") : tr("Package");
			QString preambel;
			if (tk.type == Token::beamertheme) { // special treatment for  \usetheme
				preambel = "beamertheme";
				type = tr("Beamer Theme");
				type.replace(' ', "&nbsp;");
			}
			QString text = QString("%1:&nbsp;<b>%2</b>").arg(type).arg(value);
			if (latexPackageList->contains(preambel + value)) {
				QString description = LatexRepository::instance()->shortDescription(value);
				if (!description.isEmpty()) text += "<br>" + description;
				QToolTip::showText(editor->mapToGlobal(editor->mapFromFrame(pos)), text);
			} else {
				text += "<br><b>(" + tr("not found") + ")";
				QToolTip::showText(editor->mapToGlobal(editor->mapFromFrame(pos)), text);
			}
		}
		if (tk.subtype == Token::color) {
			QString text;
			if (ts.size() > 1) {
				ts.pop();
				tk = ts.top();
			}
			text = QString("\\noident{\\color%1 \\rule{1cm}{1cm} }").arg(tk.getText());
			m_point = editor->mapToGlobal(editor->mapFromFrame(pos));
			emit showPreview(text);
		}
		if (tk.type == Token::bibItem) {
			handled = true;
			QString tooltip(tr("Citation correct (reading ...)"));
			QString bibID;

			bibID = value;

			if (!document->bibIdValid(bibID)) {
				tooltip = "<b>" + tr("Citation missing") + ":</b> " + bibID;

				if (!bibID.isEmpty() && bibID[bibID.length() - 1].isSpace()) {
					tooltip.append("<br><br><i>" + tr("Warning:") + "</i> " + tr("BibTeX ID ends with space. Trailing spaces are not ignored by BibTeX."));
				}
			} else {
				if (document->isBibItem(bibID)) {
					// by bibitem defined citation
					tooltip.clear();
					QMultiHash<QDocumentLineHandle *, int> result = document->getBibItems(bibID);
					if (result.keys().isEmpty())
						return;
					QDocumentLineHandle *mLine = result.keys().first();
					if (!mLine)
						return;
					int l = mLine->document()->indexOf(mLine);
					LatexDocument *doc = qobject_cast<LatexDocument *> (editor->document());
					if (mLine->document() != editor->document()) {
						doc = document->parent->findDocument(mLine->document());
						if (doc) tooltip = tr("<p style='white-space:pre'><b>Filename: %1</b>\n").arg(doc->getFileName());
					}
					if (doc)
						tooltip += doc->exportAsHtml(doc->cursor(l, 0, l + 4), true, true, 60);
				} else {
					// read entry in bibtex file
					if (!bibReader) {
						bibReader = new bibtexReader(this);
						connect(bibReader, SIGNAL(sectionFound(QString)), this, SLOT(bibtexSectionFound(QString)));
						connect(this, SIGNAL(searchBibtexSection(QString, QString)), bibReader, SLOT(searchSection(QString, QString)));
						bibReader->start(); //The thread is started, but it is doing absolutely nothing! Signals/slots called in the thread object are execute in the emitting thread, not the thread itself.  TODO: fix
					}
					QString file = document->findFileFromBibId(bibID);
					lastPos = pos;
					if (!file.isEmpty())
						emit searchBibtexSection(file, bibID);
					return;
				}
			}
			QToolTip::showText(editor->mapToGlobal(editor->mapFromFrame(pos)), tooltip);
		}
		if (tk.type == Token::imagefile && config->imageToolTip) {
			handled = true;
			QStringList imageExtensions = QStringList() << "" << "png" << "pdf" << "jpg" << "jpeg";
			QString fname;
			QFileInfo fi;
			QStringList imagePaths = ConfigManagerInterface::getInstance()->getOption("Files/Image Paths").toString().split(getPathListSeparator());
			foreach (const QString &ext, imageExtensions) {
				fname = getDocument()->getAbsoluteFilePath(value, ext, imagePaths);
				fi.setFile(fname);
				if (fi.exists()) break;
			}
			if (!fi.exists()) return;
			m_point = editor->mapToGlobal(editor->mapFromFrame(pos));
			emit showImgPreview(fname);
		}

	}//if tk
	if (handled)
		return;

	QToolTip::hideText();

	/*
		switch (LatexParser::getInstance().findContext(line, cursor.columnNumber(), command, value)){
	    case LatexParser::Unknown: // when does this happen ????
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


	     }*/
	//QToolTip::showText(editor->mapToGlobal(pos), line);
}

bool LatexEditorView::closeElement()
{
	if (completer->close()) return true;
	if (gotoLinePanel->isVisible()) {
		gotoLinePanel->hide();
		editor->setFocus();
		return true;
	}
	if (searchReplacePanel->isVisible()) {
		searchReplacePanel->closeElement(config->closeSearchAndReplace);
		return true;
	}
	return false;
}

void LatexEditorView::insertHardLineBreaks(int newLength, bool smartScopeSelection, bool joinLines)
{
	QRegExp breakChars("[ \t\n\r]");
	QDocumentCursor cur = editor->cursor();
	QDocument *doc = editor->document();
	int startLine = 0;
	int endLine = doc->lines() - 1;

	if (cur.isValid()) {
		if (cur.hasSelection()) {
			startLine = cur.selectionStart().lineNumber();
			endLine = cur.selectionEnd().lineNumber();
			if (cur.selectionEnd().columnNumber() == 0 && startLine < endLine) endLine--;
		} else if (smartScopeSelection) {
			QDocumentCursor currentCur = cur;
			QDocumentCursor lineCursor = currentCur;
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
		for (int i = startLine; i <= endLine; i++)
			lines << doc->line(i).text();
		lines = joinLinesExceptCommentsAndEmptyLines(lines);
		lines = splitLines(lines, newLength, breakChars);

		QDocumentCursor vCur = doc->cursor(startLine, 0, endLine, doc->line(endLine).length());
		editor->insertText(vCur, lines.join("\n"));
		editor->setCursor(cur);
		return;
	}

	bool areThereLinesToBreak = false;
	for (int i = startLine; i <= endLine; i++)
		if (doc->line(i).length() > newLength) {
			areThereLinesToBreak = true;
			break;
		}
	if (!areThereLinesToBreak) return;
	//remove all lines and reinsert them wrapped
	if (endLine + 1 < doc->lines())
		cur = doc->cursor(startLine, 0, endLine + 1, 0); //+1,0);
	else
		cur = doc->cursor(startLine, 0, endLine, doc->line(endLine).length()); //+1,0);
	QStringList lines;
	for (int i = startLine; i <= endLine; i++)
		lines << doc->line(i).text();
	QString insertBlock;
	for (int i = 0; i < lines.count(); i++) {
		QString line = lines[i];
		int commentStart = LatexParser::commentStart(line);
		if (commentStart == -1) commentStart = line.length();
		while (line.length() > newLength) {
			int breakAt = line.lastIndexOf(breakChars, newLength);
			if (breakAt < 0) breakAt = line.indexOf(breakChars, newLength);
			if (breakAt < 0) break;
			if (breakAt >= commentStart && breakAt + 1 > newLength) {
				int newBreakAt = line.indexOf(breakChars, breakAt - 1);
				if (newBreakAt > -1) breakAt = newBreakAt;
			}
			insertBlock += line.left(breakAt) + "\n";
			if (breakAt < commentStart) {
				line = line.mid(breakAt + 1);
				commentStart -= breakAt + 1;
			} else {
				line = "%" + line.mid(breakAt + 1);
				commentStart = 0;
			}
		}
		insertBlock += line + "\n";
	}
	editor->insertText(cur, insertBlock);

	editor->setCursor(cur);
}

QString LatexEditorViewConfig::translateEditOperation(int key)
{
    return QEditor::translateEditOperation(static_cast<QEditor::EditOperation>(key));
}

QList<int> LatexEditorViewConfig::possibleEditOperations()
{
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
		QEditor::FindPrevious,
		QEditor::Replace,

		QEditor::CreateMirrorUp,
		QEditor::CreateMirrorDown,
		QEditor::NextPlaceHolder,
		QEditor::PreviousPlaceHolder,
		QEditor::NextPlaceHolderOrWord,
		QEditor::PreviousPlaceHolderOrWord,
		QEditor::NextPlaceHolderOrChar,
		QEditor::PreviousPlaceHolderOrChar,
		QEditor::TabOrIndentSelection,
		QEditor::IndentSelection,
		QEditor::UnindentSelection
	};
	QList<int> res;
    int operationCount = static_cast<int>(sizeof(temp) / sizeof(int)); //sizeof(array) is possible with c-arrays
	for (int i = 0; i < operationCount; i++)
		res << temp[i];
	return res;
}

/*
 * If the cursor is at the border of a parenthesis, this returns a QDocumentCursor with a selection of the parenthized text.
 * Otherwise, a default QDocumentCursor is returned.
 */
QDocumentCursor LatexEditorView::parenthizedTextSelection(const QDocumentCursor &cursor, bool includeParentheses)
{
	QDocumentCursor from, to;
	cursor.getMatchingPair(from, to, includeParentheses);
	if (!from.hasSelection() || !to.hasSelection()) return QDocumentCursor();
	QDocumentCursor::sort(from, to);
	return QDocumentCursor(from.selectionStart(), to.selectionEnd());
}

/*
 * finds the beginning of the specified allowedFormats
 * additional formats can be allowed at the line end (e.g. comments)
 */
QDocumentCursor LatexEditorView::findFormatsBegin(const QDocumentCursor &cursor, QSet<int> allowedFormats, QSet<int> allowedLineEndFormats)
{
	QDocumentCursor c(cursor);
	QVector<int> lineFormats = c.line().getFormats();
	int col = c.columnNumber();
	if ((col > 0 && allowedFormats.contains(lineFormats[col - 1])) // prev char or next char is allowed
	        || (col < lineFormats.size() && allowedFormats.contains(lineFormats[col]))
	   ) {
		while (true) {
			while (col > 0 && allowedFormats.contains(lineFormats[col - 1])) col--;
			if (col > 0) break;
			// continue on previous line
			c.movePosition(1, QDocumentCursor::PreviousLine);
			c.movePosition(1, QDocumentCursor::EndOfLine);
			lineFormats = c.line().getFormats();
			col = c.columnNumber();
			QString text = c.line().text();
			while (col > 0 && (allowedLineEndFormats.contains(lineFormats[col - 1]) || text[col - 1].isSpace())) col--;

		}
		c.setColumnNumber(col);
		return c;
	}
	return QDocumentCursor();
}

void LatexEditorView::triggeredThesaurus()
{
	QAction *act = qobject_cast<QAction *>(sender());
	QPoint pt = act->data().toPoint();
	emit thesaurus(pt.x(), pt.y());
}

void LatexEditorView::changeSpellingDict(const QString &name)
{
	QString similarName;
	if (spellerManager->hasSpeller(name)) {
		setSpeller(name);
	} else if (spellerManager->hasSimilarSpeller(name, similarName)) {
		setSpeller(similarName);
	}
}

void LatexEditorView::copyImageFromAction()
{
	QAction *act = qobject_cast<QAction *>(sender());
	if (!act) return;

	QPixmap pm = act->data().value<QPixmap>();
	if (!pm.isNull()) {
		QApplication::clipboard()->setImage(pm.toImage());
	}
}

void LatexEditorView::saveImageFromAction()
{
	static QString lastSaveDir;

	QAction *act = qobject_cast<QAction *>(sender());
	if (!act) return;

	QPixmap pm = act->data().value<QPixmap>();

	QString fname = FileDialog::getSaveFileName(this , tr("Save Preview Image"), lastSaveDir, tr("Images") + " (*.png *.jpg *.jpeg)");
	if (fname.isEmpty()) return;

	QFileInfo fi(fname);
	lastSaveDir = fi.absolutePath();
	pm.save(fname);
}


void LatexEditorViewConfig::settingsChanged()
{
	if (!hackAutoChoose) {
		lastFontFamily = "";
		return;
	}
	if (lastFontFamily == fontFamily && lastFontSize == fontSize) return;

	QFont f(fontFamily, fontSize);
#if QT_VERSION >= 0x040700
	f.setStyleHint(QFont::Courier, QFont::ForceIntegerMetrics);
#else
	const QFont::StyleStrategy ForceIntegerMetrics = (QFont::StyleStrategy)0x0400;
	f.setStyleHint(QFont::Courier, (hasAtLeastQt(4, 7) ? ForceIntegerMetrics : QFont::PreferQuality));

#endif
	f.setKerning(false);

	QList<QFontMetrics> fms;
	for (int b = 0; b < 2; b++) for (int i = 0; i < 2; i++) {
			QFont ft(f);
			ft.setBold(b);
			ft.setItalic(i);
			fms << QFontMetrics(ft);
		}

	bool lettersHaveDifferentWidth = false, sameLettersHaveDifferentWidth = false;
	int letterWidth = fms.first().width('a');

	const QString lettersToCheck("abcdefghijklmnoqrstuvwxyzABCDEFHIJKLMNOQRSTUVWXYZ_+ 123/()=.,;#");
	QVector<QMap<QChar, int> > widths;
	widths.resize(fms.size());

	foreach (const QChar &c, lettersToCheck) {
		for (int fmi = 0; fmi < fms.size(); fmi++) {
			const QFontMetrics &fm = fms[fmi];
			int currentWidth = fm.width(c);
			widths[fmi].insert(c, currentWidth);
			if (currentWidth != letterWidth) lettersHaveDifferentWidth = true;
			QString testString;
			for (int i = 1; i < 10; i++) {
				testString += c;
				int stringWidth = fm.width(testString);
				if (stringWidth % i != 0) sameLettersHaveDifferentWidth = true;
				if (currentWidth != stringWidth / i) sameLettersHaveDifferentWidth = true;
			}
			if (lettersHaveDifferentWidth && sameLettersHaveDifferentWidth) break;
		}
		if (lettersHaveDifferentWidth && sameLettersHaveDifferentWidth) break;
	}
	const QString ligatures[2] = {"aftt", "afit"};
	for (int l = 0; l < 2 && !sameLettersHaveDifferentWidth; l++) {
		for (int fmi = 0; fmi < fms.size(); fmi++) {
			int expectedWidth = 0;
			for (int i = 0; i < ligatures[l].size() && !sameLettersHaveDifferentWidth; i++) {
				expectedWidth += widths[fmi].value(ligatures[l][i]);
				if (expectedWidth != fms[fmi].width(ligatures[l].left(i + 1))) sameLettersHaveDifferentWidth = true;
			}
		}
	}

	if (!QFontInfo(f).fixedPitch()) hackDisableFixedPitch = false; //won't be enabled anyways
	else hackDisableFixedPitch = lettersHaveDifferentWidth || sameLettersHaveDifferentWidth;
	hackDisableWidthCache = sameLettersHaveDifferentWidth;

#if defined( Q_OS_LINUX ) || defined( Q_OS_WIN )
	hackDisableLineCache = true;
#else
	hackDisableLineCache = false;
	//hackDisableLineCache = isRetinaMac();
#endif
	hackRenderingMode = 0; //always use qce, best tested

	lastFontFamily = fontFamily;
	lastFontSize = fontSize;
}


QString BracketInvertAffector::affect(const QKeyEvent *, const QString &base, int, int) const
{
	static const QString &brackets = "<>()[]{}";
	QString after;
	for (int i = 0; i < base.length(); i++)
		if (brackets.indexOf(base[i]) >= 0)
			after += brackets[brackets.indexOf(base[i]) + 1 - 2 * (brackets.indexOf(base[i]) & 1) ];
		else if (base[i] == '\\') {
			if (base.mid(i, 7) == "\\begin{") {
				after += "\\end{" + base.mid(i + 7);
				return after;
			} else if (base.mid(i, 5) == "\\end{") {
				after += "\\begin{" + base.mid(i + 5);
				return after;
			} else if (base.mid(i, 5) == "\\left") {
				after += "\\right";
				i += 4;
			} else if (base.mid(i, 6) == "\\right") {
				after += "\\left";
				i += 5;
			} else after += '\\';
		} else after += base[i];
	return after;
}

BracketInvertAffector *inverterSingleton = nullptr;

BracketInvertAffector *BracketInvertAffector::instance()
{
	if (!inverterSingleton) inverterSingleton = new BracketInvertAffector();
	return inverterSingleton;
}

void LatexEditorView::bibtexSectionFound(QString content)
{
	QToolTip::showText(editor->mapToGlobal(editor->mapFromFrame(lastPos)), content);
}

void LatexEditorView::lineMarkContextMenuRequested(int lineNumber, QPoint globalPos)
{
	if (!document) return;

	QDocumentLine line(document->line(lineNumber));
	QMenu menu(this);

	for (int i = -1; i < 10; i++) {
		int rmid = bookMarkId(i);
		if (line.hasMark(rmid)) {
			QAction *act =  new QAction(tr("Remove Bookmark"), &menu);
			act->setData(-2);
			menu.addAction(act);
			menu.addSeparator();
			break;
		}
	}

	QAction *act = new QAction(getRealIconCached("lbook"), tr("Unnamed Bookmark"), &menu);
	act->setData(-1);
	menu.addAction(act);

	for (int i = 0; i < 10; i++) {
		QAction *act = new QAction(getRealIconCached(QString("lbook%1").arg(i)), tr("Bookmark") + QString(" %1").arg(i), &menu);
		act->setData(i);
		menu.addAction(act);
	}

	act = menu.exec(globalPos);
	if (act) {
		int bookmarkNumber = act->data().toInt();
		if (bookmarkNumber == -2) {
			for (int i = -1; i < 10; i++) {
				int rmid = bookMarkId(i);
				if (line.hasMark(rmid)) {
					removeBookmark(line.handle(), i);
					return;
				}
			}
		} else {
			toggleBookmark(bookmarkNumber, line);
		}
	}
}

void LatexEditorView::foldContextMenuRequested(int lineNumber, QPoint globalPos)
{
	Q_UNUSED(lineNumber);

	QMenu menu;
	QAction *act = new QAction(tr("Collapse All"), &menu);
	act->setData(-5);
	menu.addAction(act);
	for (int i = 1; i <= 4; i++) {
		act = new QAction(QString(tr("Collapse Level %1")).arg(i), &menu);
		act->setData(-i);
		menu.addAction(act);
	}
	menu.addSeparator();
	act = new QAction(tr("Expand All"), &menu);
	act->setData(5);
	menu.addAction(act);
	for (int i = 1; i <= 4; i++) {
		act = new QAction(QString(tr("Expand Level %1")).arg(i), &menu);
		act->setData(i);
		menu.addAction(act);
	}

	act = menu.exec(globalPos);
	if (act) {
		int level = act->data().toInt();
		if (qAbs(level) < 5) {
			foldLevel(level > 0, qAbs(level));
		} else {
			foldEverything(level > 0);
		}
	}
}

LinkOverlay::LinkOverlay(const LinkOverlay &o)
{
	type = o.type;
	if (o.isValid()) {
		docLine = o.docLine;
		formatRange = o.formatRange;
	}
}

LinkOverlay::LinkOverlay(const QDocumentCursor &cur, LinkOverlay::LinkOverlayType ltype) :
	type(ltype)
{
	if (type == Invalid) return;

	int from, to;

	if (type == UsepackageOverlay || type == BibFileOverlay || type == CiteOverlay) {
		// link one of the colon separated options
		QDocumentCursor c(cur);
		LatexEditorView::selectOptionInLatexArg(c);
		from = c.anchorColumnNumber();
		to = c.columnNumber() - 1;
		if (from < 0 || to < 0 || to <= from)
			return;
	} else {
		// link everything between {}
		QString text = cur.line().text();
		int col = cur.columnNumber();
		from = findOpeningBracket(text, col);
		to = findClosingBracket(text, col);
		if (from < 0 || to < 0)
			return;
		from += 1;
		to -= 1; // leave out brackets
	}

	REQUIRE(QDocument::defaultFormatScheme());
	formatRange = QFormatRange(from, to - from + 1, QDocument::defaultFormatScheme()->id("link"));
	docLine = cur.line();
}

QString LinkOverlay::text() const
{
	if (!isValid()) return QString();
	return docLine.text().mid(formatRange.offset, formatRange.length);
}

QString LatexEditorView::getSearchText()
{
	return searchReplacePanel->getSearchText();
}

QString LatexEditorView::getReplaceText()
{
	return searchReplacePanel->getReplaceText();
}

bool LatexEditorView::getSearchIsWords()
{
	return searchReplacePanel->getSearchIsWords();
}

bool LatexEditorView::getSearchIsCase()
{
	return searchReplacePanel->getSearchIsCase();
}

bool LatexEditorView::getSearchIsRegExp()
{
	return searchReplacePanel->getSearchIsRegExp();
}

bool LatexEditorView::isInMathHighlighting(const QDocumentCursor &cursor )
{
	const QDocumentLine &line = cursor.line();
	if (!line.handle()) return false;
	const QVector<int> &formats = line.handle()->getFormats();

	int col = cursor.columnNumber();

	bool atDelimiter = false;

	if (col >= 0 && col < formats.size()) {
		int f = formats[col];
		if (f == numbersFormat || f == math_KeywordFormat) return true;
		if (f == math_DelimiterFormat) atDelimiter = true;
	}
	if (col > 0 && col <= formats.size()) {
		int f = formats[col - 1];
		if (f == numbersFormat || f == math_KeywordFormat) return true;
		if (f == math_DelimiterFormat) atDelimiter = true;
	}

	if (!atDelimiter) return false;

	QDocumentCursor from, to;
	cursor.getMatchingPair(from, to, false);
	if (!from.isValid() || !to.isValid())
		return col > 0 && col <= formats.size() && formats.at(col - 1) == math_DelimiterFormat;
	if (cursor <= from.selectionStart()) return false;
	if (cursor >= to.selectionEnd()) return false;
	return true;
}

void LatexEditorView::checkRTLLTRLanguageSwitching()
{
#if defined( Q_OS_WIN ) || defined( Q_OS_LINUX ) || ( defined( Q_OS_UNIX ) && !defined( Q_OS_MAC ) )
#if QT_VERSION >= 0x040800
	QDocumentCursor cursor = editor->cursor();
	QDocumentLine line = cursor.line();
	InputLanguage language = IL_UNCERTAIN;
	if (line.firstChar() >= 0) { //whitespace lines have no language information
		if (config->switchLanguagesMath) {
			if (isInMathHighlighting(cursor)) language = IL_LTR;
			else language = IL_RTL;
		}

		if (config->switchLanguagesDirection && language != IL_LTR) {
			if (line.hasFlag(QDocumentLine::LayoutDirty))
				if (line.isRTLByLayout() || line.isRTLByText() ) {
					line.handle()->lockForWrite();
					line.handle()->layout(cursor.lineNumber());
					line.handle()->unlock();
				}
			if (!line.isRTLByLayout())
				language = IL_LTR;
			else {
				int c = cursor.columnNumber();
				int dir = line.rightCursorPosition(c) - c;
				if (dir < 0) language = IL_RTL;
				else if (dir > 0) language = IL_LTR;
			}
		}
	}
	setInputLanguage(language);
#endif
#endif
}
