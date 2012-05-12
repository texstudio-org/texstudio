
#include "configmanager.h"

#include "configdialog.h"
#include "latexeditorview.h"
#include "latexcompleter_config.h"
#include "latexeditorview_config.h"
#include "webpublishdialog_config.h"
#include "insertgraphics_config.h"
#include "grammarcheck_config.h"
#include "PDFDocument_config.h"
#include "smallUsefulFunctions.h"
#include "codesnippet.h"

#include <QDomElement>

#include "qformatconfig.h"

#include "manhattanstyle.h"

const QString TXS_AUTO_REPLACE_QUOTE_OPEN = "TMX:Replace Quote Open";
const QString TXS_AUTO_REPLACE_QUOTE_CLOSE = "TMX:Replace Quote Close";

const char* PROPERTY_COMMAND_NAME = "commandName";
const char* PROPERTY_ASSOCIATED_INPUT = "associatedInput";

ManagedProperty::ManagedProperty():storage(0),type(PT_VOID),widgetOffset(0){
}

#define CONSTRUCTOR(TYPE, ID) \
	ManagedProperty::ManagedProperty(TYPE* storage, QVariant def, ptrdiff_t widgetOffset)\
	: storage(storage), type(ID), def(def), widgetOffset(widgetOffset){} \
	ManagedProperty ManagedProperty::fromValue(TYPE value) { \
		ManagedProperty res;    \
		res.storage = new TYPE; \
		*((TYPE*)(res.storage)) = value; \
		res.type = ID;          \
		res.def = value;        \
		res.widgetOffset = 0;   \
		return res;             \
	}                              
PROPERTY_TYPE_FOREACH_MACRO(CONSTRUCTOR)
#undef CONSTRUCTOR


void ManagedProperty::deallocate(){ 
	switch (type) {
#define CASE(TYPE, ID) case ID: delete ((TYPE*)(storage)); break;
PROPERTY_TYPE_FOREACH_MACRO(CASE)
#undef CASE
	default: Q_ASSERT(false);
	}
	storage = 0;
}


static ConfigManager* globalConfigManager = 0;
ConfigManagerInterface* ConfigManagerInterface::getInstance(){
	Q_ASSERT(globalConfigManager);
	return globalConfigManager;
}


Q_DECLARE_METATYPE(ManagedProperty*);

ManagedToolBar::ManagedToolBar(const QString &newName, const QStringList &defs): name(newName), defaults(defs), toolbar(0){}

QVariant ManagedProperty::valueToQVariant() const{
	Q_ASSERT(storage);
	if (!storage) return QVariant();
	switch (type){
#define CONVERT(TYPE, ID) case ID: return *((TYPE*)storage);
PROPERTY_TYPE_FOREACH_MACRO(CONVERT)
#undef CONVERT
	default:
		Q_ASSERT(false);
		return QVariant();
	}
}
void ManagedProperty::valueFromQVariant(const QVariant v){
	Q_ASSERT(storage);
	if (!storage) return;
	switch (type){
	case PT_VARIANT: *((QVariant*)storage) = v; break;
	case PT_INT: *((int*)storage) = v.toInt(); break;
	case PT_BOOL: *((bool*)storage) = v.toBool(); break;
	case PT_STRING: *((QString*)storage) = v.toString(); break;
	case PT_STRINGLIST: *((QStringList*)storage) = v.toStringList(); break;
	case PT_DATETIME: *((QDateTime*)storage) = v.toDateTime(); break;
	case PT_FLOAT: *((float*)storage) = v.toFloat(); break;
	case PT_DOUBLE: *((double*)storage) = v.toDouble(); break;
	case PT_BYTEARRAY: *((QByteArray*)storage) = v.toByteArray(); break;
	case PT_LIST: *((QList<QVariant>*)storage) = v.toList(); break;
	default:
		Q_ASSERT(false);
	}
}

void ManagedProperty::writeToObject(QObject* w) const{
	Q_ASSERT(storage && w);
	if (!storage || !w) return;
	
	QCheckBox* checkBox = qobject_cast<QCheckBox*>(w);
	if (checkBox) {
		Q_ASSERT(type == PT_BOOL);
		checkBox->setChecked(*((bool*)storage));
		return;
	}
	QLineEdit* edit = qobject_cast<QLineEdit*>(w);
	if (edit){
		Q_ASSERT(type == PT_STRING);
		edit->setText(*((QString*)storage));
		return;
	}
	/*QTextEdit* tedit = qobject_cast<QTextEdit*>(w);
 if (tedit){
  *((QString*)storage) = tedit->toPlainText();
  continue;
 }*/
	QSpinBox* spinBox = qobject_cast<QSpinBox*>(w);
	if (spinBox){
		Q_ASSERT(type == PT_INT);
		spinBox->setValue(*((int*)storage));
		return;
	}
	QComboBox* comboBox = qobject_cast<QComboBox*>(w);
	if (comboBox){
		switch (type) {
		case PT_BOOL:
			comboBox->setCurrentIndex(*((bool*)storage)?1:0);
			return;
		case PT_INT:
			comboBox->setCurrentIndex(*((int*)storage));
			return;
		case PT_STRING:{
			int index = comboBox->findText(*(QString*)storage);
			if (index > 0) comboBox->setCurrentIndex(index);
			if (comboBox->isEditable()) comboBox->setEditText(*(QString*)storage);
			return;
		}
		case PT_STRINGLIST:{
			QStringList& sl = *(QStringList*)storage;
		
			int cp=comboBox->lineEdit() ? comboBox->lineEdit()->cursorPosition() : -1000; 
			while (comboBox->count() > sl.size()) 
				comboBox->removeItem(comboBox->count()-1);
			for (int i=0;i<qMin(sl.size(),comboBox->count());i++)
				if (comboBox->itemText(i) != sl[i]) 
					comboBox->setItemText(i,sl[i]);
			for (int i=comboBox->count();i<sl.size();i++)
				comboBox->addItem(sl[i]);
			if (cp != -1000) {
				//combobox visible (i.e. as used in search panel)
				if (!sl.isEmpty() && comboBox->currentText()!=sl.last() && comboBox->currentIndex()!=sl.size()-1)
					comboBox->setCurrentIndex(sl.size()-1);
				comboBox->lineEdit()->setCursorPosition(cp); 
			} // else:  combobox invisible (i.e. as used in universal input dialog)
			return;
		}
		default:
			Q_ASSERT(false);
		}
	}
	QDoubleSpinBox* doubleSpinBox = qobject_cast<QDoubleSpinBox*>(w);
	if (doubleSpinBox){
		switch (type) {
		case PT_DOUBLE: doubleSpinBox->setValue(*((double*)storage)); break;
		case PT_FLOAT: doubleSpinBox->setValue(*((float*)storage)); break;
		default:
			Q_ASSERT(false);
		}
		return;
	}
	QAction* action = qobject_cast<QAction*>(w);
	if (action) {
		Q_ASSERT(type == PT_BOOL);
		action->setChecked(*((bool*)storage));
		return;
	}
	QTextEdit* textEdit = qobject_cast<QTextEdit*>(w);
	if (textEdit) {
		switch (type) {
		case PT_STRING: textEdit->setPlainText(*((QString*)storage)); break;
		case PT_STRINGLIST: textEdit->setPlainText(((QStringList*)storage)->join("\n")); break;
		default:
			Q_ASSERT(false);
		}
		return;
	}
	Q_ASSERT(false);
}
bool ManagedProperty::readFromObject(const QObject* w){
#define READ_FROM_OBJECT(TYPE, VALUE) {           \
	TYPE oldvalue = *((TYPE*)storage);         \
	*((TYPE*)storage) = VALUE;                 \
	return oldvalue != *((TYPE*)storage);      \
}	
	Q_ASSERT(storage);
	if (!storage) return false;
	const QCheckBox* checkBox = qobject_cast<const QCheckBox*>(w);
	if (checkBox) {
		Q_ASSERT(type == PT_BOOL);
		READ_FROM_OBJECT(bool, checkBox->isChecked())
	}
	const QLineEdit* edit = qobject_cast<const QLineEdit*>(w);
	if (edit){
		Q_ASSERT(type == PT_STRING);
		READ_FROM_OBJECT(QString, edit->text())
	}
	/*QTextEdit* tedit = qobject_cast<QTextEdit*>(w);
 if (tedit){
  *((QString*)storage) = tedit->toPlainText();
  continue;
 }*/
	const QSpinBox* spinBox = qobject_cast<const QSpinBox*>(w);
	if (spinBox){
		Q_ASSERT(type == PT_INT);
		READ_FROM_OBJECT(int, spinBox->value())
	}
	const QComboBox* comboBox = qobject_cast<const QComboBox*>(w);
	if (comboBox){
		switch (type) {
		case PT_BOOL:   READ_FROM_OBJECT(bool, comboBox->currentIndex()!=0)
		case PT_INT:    READ_FROM_OBJECT(int, comboBox->currentIndex())
		case PT_STRING: READ_FROM_OBJECT(QString, comboBox->currentText())
		case PT_STRINGLIST:{
			QString oldvalue = ((QStringList*)storage)->first();
			*((QStringList*)storage) = QStringList(comboBox->currentText());
			return oldvalue != ((QStringList*)storage)->first();
		}
		default:
			Q_ASSERT(false);
		}
	}
	const QDoubleSpinBox* doubleSpinBox = qobject_cast<const QDoubleSpinBox*>(w);
	if (doubleSpinBox){
		switch (type) {
		case PT_DOUBLE: READ_FROM_OBJECT(double, doubleSpinBox->value())
		case PT_FLOAT: READ_FROM_OBJECT(float, doubleSpinBox->value())
		default:
			Q_ASSERT(false);
		}
	}
	const QAction* action = qobject_cast<const QAction*>(w);
	if (action){
		Q_ASSERT(type == PT_BOOL);
		Q_ASSERT(action->isCheckable());
		READ_FROM_OBJECT(bool, action->isChecked());
	}
	
	const QTextEdit* textEdit = qobject_cast<const QTextEdit*>(w);
	if (textEdit){
		switch (type) {
		case PT_STRING:     READ_FROM_OBJECT(QString, textEdit->toPlainText())
		case PT_STRINGLIST: READ_FROM_OBJECT(QStringList, textEdit->toPlainText().split("\n"))
		default:
			Q_ASSERT(false);
		}
	}
	Q_ASSERT(false);
	return false;
}
#undef READ_FROM_OBJECT

QTextCodec* ConfigManager::newFileEncoding = 0;

QString getText(QWidget* w){
	if (qobject_cast<QLineEdit*>(w)) return qobject_cast<QLineEdit*>(w)->text();
	else if (qobject_cast<QComboBox*>(w)) return qobject_cast<QComboBox*>(w)->currentText();
	else REQUIRE_RET(false, "");
}
void setText(QWidget* w, const QString& t){
	if (qobject_cast<QLineEdit*>(w)) qobject_cast<QLineEdit*>(w)->setText(t);
	else if (qobject_cast<QComboBox*>(w)) qobject_cast<QComboBox*>(w)->setEditText(t);
	else REQUIRE(false);
}


ConfigManager::ConfigManager(QObject *parent): QObject (parent),
       buildManager(0),editorConfig(new LatexEditorViewConfig),
       completerConfig (new LatexCompleterConfig),
       webPublishDialogConfig (new WebPublishDialogConfig),
       pdfDocumentConfig(new PDFDocumentConfig),
       insertGraphicsConfig(new InsertGraphicsConfig),
       grammarCheckerConfig(new GrammarCheckerConfig),
       menuParent(0), menuParentsBar(0), modifyMenuContentsFirstCall(true), persistentConfig(0) {
	
	Q_ASSERT(!globalConfigManager);
	globalConfigManager = this;
	
	managedToolBars.append(ManagedToolBar("Custom", QStringList()));
	managedToolBars.append(ManagedToolBar("File", QStringList() << "main/file/new" << "main/file/open" << "main/file/save" << "main/file/close"));
	managedToolBars.append(ManagedToolBar("Edit", QStringList() << "main/edit/undo" << "main/edit/redo" << "main/edit/copy" << "main/edit/cut" << "main/edit/paste"));
	managedToolBars.append(ManagedToolBar("Tools", QStringList() << "main/tools/viewlog" << "main/edit2/goto/errorprev" << "main/edit2/goto/errornext"	<< "separator"
	                                      << "main/tools/quickbuild" << "main/tools/latex" << "main/tools/viewdvi" << "main/tools/dvi2ps" << "main/tools/viewps" << "main/tools/pdflatex" << "main/tools/viewpdf"));
	managedToolBars.append(ManagedToolBar("Math", QStringList() << "main/math/mathmode" << "main/math/subscript" << "main/math/superscript" << "main/math/frac" << "main/math/dfrac" << "main/math/sqrt" << "separator"
	                                      << "tags/brackets/left" << "separator" << "tags/brackets/right"));
	managedToolBars.append(ManagedToolBar("Format", QStringList() << "main/latex/sectioning" << "separator" << "main/latex/references" <<"separator" <<
	                                      "main/latex/fontsizes" << "separator" <<
	                                      "main/latex/fontstyles/textbf" << "main/latex/fontstyles/textit" << "main/latex/fontstyles/underline" << "main/latex/environment/flushleft" << "main/latex/environment/center" << "main/latex/environment/flushright"
	                                      << "separator" << "main/latex/spacing/newline"));
	managedToolBars.append(ManagedToolBar("Table", QStringList() << "main/latex/tabularmanipulation/addRow" << "main/latex/tabularmanipulation/addColumn" << "main/latex/tabularmanipulation/pasteColumn" << "main/latex/tabularmanipulation/removeRow" << "main/latex/tabularmanipulation/removeColumn" << "main/latex/tabularmanipulation/cutColumn" << "main/latex/tabularmanipulation/alignColumns"));
	managedToolBars.append(ManagedToolBar("Diff", QStringList() << "main/file/svn/prevdiff" << "main/file/svn/nextdiff"  ));
	managedToolBars.append(ManagedToolBar("Central", QStringList() << "main/latex/fontstyles/textbf" << "main/latex/fontstyles/textit" << "main/latex/fontstyles/underline" << "main/latex/environment/flushleft" << "main/latex/environment/center" << "main/latex/environment/flushright" << "separator" <<
	                                      "main/latex/spacing/newline" << "separator" <<
	                                      "main/math/mathmode" << "main/math/subscript" << "main/math/superscript" << "main/math/frac" << "main/math/dfrac" << "main/math/sqrt"));
	
	registerOption("ToolBar/CentralVisible", &centralVisible, true);
	registerOption("StructureView/ShowLinenumbers", &showLineNumbersInStructure, false);
	registerOption("StructureView/Indentation", &indentationInStructure, -1);
	
	enviromentModes << "verbatim" << "numbers";
	
	
	
	Ui::ConfigDialog *pseudoDialog = (Ui::ConfigDialog*) 0;
	
	
	//beginRegisterGroup("texmaker");
	//files
	registerOption("Files/New File Encoding", &newFileEncodingName, "utf-8", &pseudoDialog->comboBoxEncoding); //check
	registerOption("Files/Auto Detect Encoding Of Loaded Files", &autodetectLoadedFile, true, &pseudoDialog->checkBoxAutoDetectOnLoad);
	//recent files
	registerOption("Files/Max Recent Files", &maxRecentFiles, 5, &pseudoDialog->spinBoxMaxRecentFiles);
	registerOption("Files/Max Recent Projects", &maxRecentProjects, 3, &pseudoDialog->spinBoxMaxRecentProjects);
	registerOption("Files/Recent Files", &recentFilesList);
	registerOption("Files/Recent Project Files", &recentProjectList);
	registerOption("Files/RestoreSession", &sessionRestore);
	registerOption("Files/Session/Files", &sessionFilesToRestore);
	registerOption("Files/Session/curRows", &sessionCurRowsToRestore);
	registerOption("Files/Session/curCols", &sessionCurColsToRestore);
	registerOption("Files/Session/firstLines", &sessionFirstLinesToRestore);
	registerOption("Files/Session/CurrentFile", &sessionCurrent);
	registerOption("Files/Session/MasterFile", &sessionMaster);
	registerOption("Files/Bookmarks", &bookmarkList);
	registerOption("Files/Last Document", &lastDocument);
	registerOption("Files/Parse BibTeX", &parseBibTeX, true, &pseudoDialog->checkBoxParseBibTeX);
	registerOption("Files/Parse Master", &parseMaster, true, &pseudoDialog->checkBoxParseMaster);
	registerOption("Files/Autosave", &autosaveEveryMinutes, 0);
	
	registerOption("Spell/DictionaryDir", &spellDictDir, "", &pseudoDialog->leDictDir); //don't translate it
	registerOption("Spell/Language", &spellLanguage, "<none>", &pseudoDialog->comboBoxSpellcheckLang);
	registerOption("Spell/Dic", &spell_dic, "<dic not found>", 0);
	registerOption("Thesaurus/Database", &thesaurus_database, "<dic not found>", &pseudoDialog->comboBoxThesaurusFileName);
	
	//editor
	registerOption("Editor/WordWrapMode", &editorConfig->wordwrap, 1, &pseudoDialog->comboBoxLineWrap);
	registerOption("Editor/WrapLineWidth", &editorConfig->lineWidth, 80, &pseudoDialog->spinBoxWrapLineWidth);
	registerOption("Editor/Parentheses Matching", &editorConfig->parenmatch, true); //TODO: checkbox?
	registerOption("Editor/Parentheses Completion", &editorConfig->parenComplete, true, &pseudoDialog->checkBoxAutoCompleteParens);
	registerOption("Editor/Line Number Multiples", &editorConfig->showlinemultiples, -1);
	registerOption("Editor/Cursor Surrounding Lines", &editorConfig->cursorSurroundLines, 5);
	registerOption("Editor/Auto Indent", &editorConfig->autoindent, true);
	registerOption("Editor/Weak Indent", &editorConfig->weakindent, true);
	registerOption("Editor/Indent with Spaces", &editorConfig->indentWithSpaces, false);
	registerOption("Editor/Folding", &editorConfig->folding, true, &pseudoDialog->checkBoxFolding);
	registerOption("Editor/Show Line State", &editorConfig->showlinestate, true, &pseudoDialog->checkBoxLineState);
	registerOption("Editor/Show Cursor State", &editorConfig->showcursorstate, true, &pseudoDialog->checkBoxState);
	registerOption("Editor/Real-Time Spellchecking", &editorConfig->realtimeChecking, true, &pseudoDialog->checkBoxRealTimeCheck); //named for compatibility reasons with older txs versions
	registerOption("Editor/Check Spelling", &editorConfig->inlineSpellChecking, true, &pseudoDialog->checkBoxInlineSpellCheck);
	registerOption("Editor/Check Citations", &editorConfig->inlineCitationChecking, true, &pseudoDialog->checkBoxInlineCitationCheck);
	registerOption("Editor/Check References", &editorConfig->inlineReferenceChecking, true, &pseudoDialog->checkBoxInlineReferenceCheck);
	registerOption("Editor/Check Syntax", &editorConfig->inlineSyntaxChecking, true, &pseudoDialog->checkBoxInlineSyntaxCheck);
	registerOption("Editor/Check Grammar", &editorConfig->inlineGrammarChecking, true, &pseudoDialog->checkBoxInlineGrammarCheck);
	registerOption("Editor/Show Whitespace", &editorConfig->showWhitespace, true, &pseudoDialog->checkBoxShowWhitespace);
	registerOption("Editor/TabStop", &editorConfig->tabStop, 4 , &pseudoDialog->sbTabSpace);
	registerOption("Editor/ToolTip Help", &editorConfig->toolTipHelp, true , &pseudoDialog->checkBoxToolTipHelp2);
	registerOption("Editor/ToolTip Preview", &editorConfig->toolTipPreview, true , &pseudoDialog->checkBoxToolTipPreview);
	
	registerOption("Editor/Replace Quotes", &replaceQuotes, 0 , &pseudoDialog->comboBoxReplaceQuotes);
	
	registerOption("Editor/Display Modifytime", &editorConfig->displayModifyTime, true, &pseudoDialog->checkBoxDisplayModifyTime);
	registerOption("Editor/Close Search Replace Together", &editorConfig->closeSearchAndReplace, false, &pseudoDialog->checkBoxCloseSearchReplaceTogether);
	registerOption("Editor/Use Line For Search", &editorConfig->useLineForSearch, true, &pseudoDialog->checkBoxUseLineForSearch);	
	registerOption("Editor/Search Only In Selection", &editorConfig->searchOnlyInSelection, true, &pseudoDialog->checkBoxSearchOnlyInSelection);	
	registerOption("Editor/Auto Replace Commands", &CodeSnippet::autoReplaceCommands, true, &pseudoDialog->checkBoxAutoReplaceCommands);
	
	registerOption("Editor/Font Family", &editorConfig->fontFamily, "", &pseudoDialog->comboBoxFont);
	registerOption("Editor/Font Size", &editorConfig->fontSize, -1, &pseudoDialog->spinBoxSize);
    registerOption("Editor/Line Spacing Percent", &editorConfig->lineSpacingPercent, 100, &pseudoDialog->spinBoxLineSpacingPercent);
	registerOption("Editor/Esc for closing log", &useEscForClosingLog, false, &pseudoDialog->cb_CloseLogByEsc);
	
	registerOption("Editor/Mouse Wheel Zoom", &editorConfig->mouseWheelZoom, true, &pseudoDialog->checkBoxMouseWheelZoom);
	
	registerOption("Editor/Hack Auto Choose", &editorConfig->hackAutoChoose, true, &pseudoDialog->checkBoxHackAutoRendering);
	registerOption("Editor/Hack Disable Fixed Pitch", &editorConfig->hackDisableFixedPitch, false, &pseudoDialog->checkBoxHackDisableFixedPitch);
	registerOption("Editor/Hack Disable Width Cache", &editorConfig->hackDisableWidthCache, false, &pseudoDialog->checkBoxHackDisableWidthCache);
	registerOption("Editor/Hack Disable Line Cache", &editorConfig->hackDisableLineCache, false, &pseudoDialog->checkBoxHackDisableLineCache);
	registerOption("Editor/Hack Disable Accent Workaround", &editorConfig->hackDisableAccentWorkaround, false, &pseudoDialog->checkBoxHackDisableAccentWorkaround);
	registerOption("Editor/Hack Render Mode", &editorConfig->hackRenderingMode, 0, &pseudoDialog->comboBoxHackRenderMode);
	
	//completion
	registerOption("Editor/Completion", &completerConfig->enabled, true, &pseudoDialog->checkBoxCompletion);
	Q_ASSERT(sizeof(int)==sizeof(LatexCompleterConfig::CaseSensitive));
	registerOption("Editor/Completion Case Sensitive", (int*)&completerConfig->caseSensitive, 2);
	registerOption("Editor/Completion Complete Common Prefix", &completerConfig->completeCommonPrefix, true, &pseudoDialog->checkBoxCompletePrefix);
	registerOption("Editor/Completion EOW Completes", &completerConfig->eowCompletes, true, &pseudoDialog->checkBoxEOWCompletes);
	registerOption("Editor/Completion Enable Tooltip Help", &completerConfig->tooltipHelp, true, &pseudoDialog->checkBoxToolTipHelp);
	registerOption("Editor/Completion Use Placeholders", &completerConfig->usePlaceholders, true, &pseudoDialog->checkBoxUsePlaceholders);
	registerOption("Editor/Completion Prefered Tab", (int*)&completerConfig->preferedCompletionTab, 0,&pseudoDialog->comboBoxPreferedTab);
	registerOption("Editor/Completion Tab Relative Font Size Percent", &completerConfig->tabRelFontSizePercent, 100,&pseudoDialog->spinBoxTabRelFontSize);
	
	//grammar
	registerOption("Grammar/Long Repetition Check", &grammarCheckerConfig->longRangeRepetitionCheck, true, &pseudoDialog->checkBoxGrammarRepetitionCheck);
	registerOption("Grammar/Bad Word Check", &grammarCheckerConfig->badWordCheck, true, &pseudoDialog->checkBoxGrammarBadWordCheck);
	registerOption("Grammar/Long Repetition Check Distance", &grammarCheckerConfig->maxRepetitionDelta, 3, &pseudoDialog->spinBoxGrammarRepetitionDistance);
	registerOption("Grammar/Very Long Repetition Check Distance", &grammarCheckerConfig->maxRepetitionLongRangeDelta, 40, &pseudoDialog->spinBoxGrammarLongRangeRepetition);
	registerOption("Grammar/Very Long Repetition Check Min Length", &grammarCheckerConfig->maxRepetitionLongRangeMinWordLength, 6, &pseudoDialog->spinBoxGrammarLongRangeRepetitionMinLength);
	registerOption("Grammar/Word Lists Dir", &grammarCheckerConfig->wordlistsDir, "", &pseudoDialog->lineEditGrammarWordlists);
	registerOption("Grammar/Language Tool URL", &grammarCheckerConfig->languageToolURL, "http://localhost:8081/",&pseudoDialog->lineEditGrammarLTUrl);
	registerOption("Grammar/Language Tool Path", &grammarCheckerConfig->languageToolPath, "", &pseudoDialog->lineEditGrammarLTPath);
	registerOption("Grammar/Language Tool Java Path", &grammarCheckerConfig->languageToolJavaPath, "java", &pseudoDialog->lineEditGrammarLTJava);
	registerOption("Grammar/Language Tool Autorun", &grammarCheckerConfig->languageToolAutorun, true, &pseudoDialog->checkBoxGrammarLTAutorun);
	registerOption("Grammar/Language Tool Ignored Rules", &grammarCheckerConfig->languageToolIgnoredRules, "", &pseudoDialog->lineEditGrammarLTIgnoredRules);
#define TEMP(ID) registerOption("Grammar/Special Rules" #ID, &grammarCheckerConfig->specialIds##ID, "", &pseudoDialog->lineEditGrammarSpecialRules##ID)
	TEMP(1); TEMP(2); TEMP(3); TEMP(4); 
#undef TEMP
	//other dialogs
	registerOption("Dialogs/Last Hard Wrap Column", &lastHardWrapColumn, 80);
	registerOption("Dialogs/Last Hard Wrap Smart Scope Selection", &lastHardWrapSmartScopeSelection, false);
	registerOption("Dialogs/Last Hard Wrap Join Lines", &lastHardWrapJoinLines, false);
	
	//build commands
	registerOption("Tools/SingleViewerInstance", &singleViewerInstance, false, &pseudoDialog->checkBoxSingleInstanceViewer);
	registerOption("Tools/Show Log After Compiling", &showLogAfterCompiling, true, &pseudoDialog->checkBoxShowLog);
	registerOption("Tools/Show Stdout", &showStdoutOption, 1, &pseudoDialog->comboBoxShowStdout);
	registerOption("Tools/Automatic Rerun Times", &BuildManager::autoRerunLatex, 5, &pseudoDialog->spinBoxRerunLatex);
	registerOption("Tools/Automatic Rerun Commands", &BuildManager::autoRerunCommands, "compile|latex|pdflatex|luatex|xelatex", &pseudoDialog->lineEditCommandsWithRerun);
	
	//SVN
	registerOption("Tools/Auto Checkin after Save", &autoCheckinAfterSave, false, &pseudoDialog->cbAutoCheckin);
	registerOption("Tools/SVN Undo", &svnUndo, false, &pseudoDialog->cbSVNUndo);
	registerOption("Tools/SVN KeywordSubstitution", &svnKeywordSubstitution, false, &pseudoDialog->cbKeywordSubstitution);
	registerOption("Tools/SVN Search Path Depth", &svnSearchPathDepth, 2, &pseudoDialog->sbDirSearchDepth);
	
	//interfaces
	registerOption("GUI/Style", &modernStyle, false, &pseudoDialog->comboBoxInterfaceModernStyle);
#ifdef Q_WS_X11
	useTexmakerPalette = true;
	interfaceFontFamily = "<later>";
	interfaceStyle="<later>";
#else
	useTexmakerPalette = false;
	interfaceFontFamily=QApplication::font().family();
	interfaceStyle="";
#endif
	registerOption("GUI/Texmaker Palette", &useTexmakerPalette, useTexmakerPalette, &pseudoDialog->checkBoxUseTexmakerPalette);
	registerOption("GUI/Use System Theme", &useSystemTheme, true, &pseudoDialog->checkBoxUseSystemTheme);
	registerOption("X11/Font Family", &interfaceFontFamily, interfaceFontFamily, &pseudoDialog->comboBoxInterfaceFont); //named X11 for backward compatibility
	registerOption("X11/Font Size", &interfaceFontSize, QApplication::font().pointSize(), &pseudoDialog->spinBoxInterfaceFontSize);
	registerOption("X11/Style", &interfaceStyle, interfaceStyle, &pseudoDialog->comboBoxInterfaceStyle);
	
	registerOption("Interface/Config Show Advanced Options", &configShowAdvancedOptions, false, &pseudoDialog->checkBoxShowAdvancedOptions);
	registerOption("Interface/Config Riddled", &configRiddled, false);	
	registerOption("LogView/Tabbed", &tabbedLogView, true, &pseudoDialog->checkBoxTabbedLogView);
	registerOption("Interface/New Left Panel Layout", &newLeftPanelLayout, true);
	
	//language
	registerOption("Interface/Language", &language, "", &pseudoDialog->comboBoxLanguage);
	
	//preview
	registerOption("Preview/Mode", (int*)&previewMode, (int)PM_INLINE, &pseudoDialog->comboBoxPreviewMode);
	registerOption("Preview/Auto Preview", (int*)&autoPreview, 1, &pseudoDialog->comboBoxAutoPreview);
	registerOption("Preview/Auto Preview Delay", &autoPreviewDelay, 300, &pseudoDialog->spinBoxAutoPreviewDelay);
	
	//pdf preview
	QRect screen = QApplication::desktop()->screenGeometry();
	registerOption("Geometries/PdfViewerLeft", &pdfDocumentConfig->windowLeft, screen.width()/3);
	registerOption("Geometries/PdfViewerTop", &pdfDocumentConfig->windowTop, screen.height()/3);
	registerOption("Geometries/PdfViewerWidth", &pdfDocumentConfig->windowWidth, screen.width()/3);
	registerOption("Geometries/PdfViewerHeight", &pdfDocumentConfig->windowHeight, screen.height()/3);
	registerOption("Geometries/PdfViewerState", &pdfDocumentConfig->windowState, QByteArray());
	
	registerOption("Preview/DPI", &pdfDocumentConfig->dpi, QApplication::desktop()->logicalDpiX(), &pseudoDialog->spinBoxPreviewDPI);
	registerOption("Preview/Scale Option", &pdfDocumentConfig->scaleOption, 1, &pseudoDialog->comboBoxPreviewScale);
	registerOption("Preview/Scale", &pdfDocumentConfig->scale, 100, &pseudoDialog->spinBoxPreviewScale);
	registerOption("Preview/Magnifier Size", &pdfDocumentConfig->magnifierSize, 300, &pseudoDialog->spinBoxPreviewMagnifierSize);
	registerOption("Preview/Magnifier Shape", &pdfDocumentConfig->magnifierShape, 1, &pseudoDialog->comboBoxPreviewMagnifierShape);
	registerOption("Preview/Magnifier Border", &pdfDocumentConfig->magnifierBorder, false, &pseudoDialog->checkBoxPreviewMagnifierBorder);
	
	registerOption("Preview/Sync File Mask", &pdfDocumentConfig->syncFileMask, "*.tex", &pseudoDialog->lineEditPreviewSyncFileMask);
	
#ifndef QT_NO_DEBUG
	registerOption("Debug/Last Application Modification", &debugLastFileModification);
	registerOption("Debug/Last Full Test Run", &debugLastFullTestRun);
#endif
	
	
}

ConfigManager::~ConfigManager(){
	delete editorConfig;
	delete completerConfig;
	delete webPublishDialogConfig;
	delete insertGraphicsConfig;
	if (persistentConfig) delete persistentConfig;
}

QSettings* ConfigManager::readSettings() {
	//load config
	QSettings *config = persistentConfig;
	bool importTexmakerSettings = false;
	bool importTexMakerXSettings = false;
	if (!config){
		bool usbMode = isExistingFileRealWritable(QCoreApplication::applicationDirPath()+"/texstudio.ini");
		if (!usbMode)
			if (isExistingFileRealWritable(QCoreApplication::applicationDirPath()+"/texmakerx.ini")) {
				//import texmaker usb settings
				usbMode=(QFile(QCoreApplication::applicationDirPath()+"/texmakerx.ini")).copy(QCoreApplication::applicationDirPath()+"/texstudio.ini");
				importTexMakerXSettings = true;
			}
		if (!usbMode)
			if (isExistingFileRealWritable(QCoreApplication::applicationDirPath()+"/texmaker.ini")) {
				//import texmaker usb settings
				usbMode=(QFile(QCoreApplication::applicationDirPath()+"/texmaker.ini")).copy(QCoreApplication::applicationDirPath()+"/texstudio.ini");
				importTexmakerSettings = true;
			}
		if (usbMode) {
			config=new QSettings(QCoreApplication::applicationDirPath()+"/texstudio.ini",QSettings::IniFormat);
		} else {
			config=new QSettings(QSettings::IniFormat,QSettings::UserScope,"texstudio","texstudio");
			if (config->childGroups().empty()) {
				QSettings texmakerxsetting(QSettings::IniFormat,QSettings::UserScope,"benibela","texmakerx");				
				//import texmakerx global settings
				if (texmakerxsetting.childGroups().empty()) {
					//import texmaker global settings
					QSettings oldconfig(QSettings::IniFormat,QSettings::UserScope,"xm1","texmaker");
					QStringList keys=oldconfig.allKeys();
					foreach(const QString& key, keys) config->setValue(key,oldconfig.value(key,""));
					importTexmakerSettings = true;
				} else {
					QDir texmakerxdir = QFileInfo(texmakerxsetting.fileName()).dir();
					QDir texstudiodir = QFileInfo(config->fileName()).dir();
					if (!texstudiodir.exists()) {
						QDir txsparent = texstudiodir;
						txsparent.cdUp();
						txsparent.mkpath(texstudiodir.absolutePath());
					}
					QStringList additionalFiles = texmakerxdir.entryList(QStringList() << "*");
					foreach (const QString &f, additionalFiles)
						QFile::copy(texmakerxdir.absoluteFilePath(f),texstudiodir.absoluteFilePath(f));
					
					QStringList keys=texmakerxsetting.allKeys();
					foreach(const QString& key, keys) config->setValue(key,texmakerxsetting.value(key,""));
					importTexMakerXSettings = true;
				}
				
			}
		}
		configFileName=config->fileName();
		configFileNameBase=configFileName;
		configBaseDir=QFileInfo(configFileName).absolutePath();
		if (!configBaseDir.endsWith("/")) configBaseDir+="/";
		completerConfig->importedCwlBaseDir=configBaseDir;// set in LatexCompleterConfig to get access from LatexDocument
		if (configFileNameBase.endsWith(".ini")) configFileNameBase=configFileNameBase.replace(QString(".ini"),"");
		persistentConfig = config;
	}
	
	config->beginGroup("texmaker");
	
	if ((importTexmakerSettings || importTexMakerXSettings) && config->value("Tools/IntegratedPdfViewer", false).toBool())
		config->setValue("Tools/Pdf", "<default>");
	
	//----------managed properties--------------------
	for (int i=0;i<managedProperties.size();i++)
		managedProperties[i].valueFromQVariant(config->value(managedProperties[i].name, managedProperties[i].def));
	
	//------------------files--------------------
	newFileEncoding=QTextCodec::codecForName(newFileEncodingName.toAscii().data());
	
	//----------------------------dictionaries-------------------------
	
	if (spellDictDir.isEmpty() || ((importTexmakerSettings  || importTexMakerXSettings)  && !QFileInfo(QDir(spellDictDir), spellLanguage+".dic").exists())) {
		// non-exeistent or invalid settings for dictionary
		// try restore from old format where there was only one dictionary - spell_dic can be removed later when users have migrated to the new version
		QString dic = spell_dic;
		if (!QFileInfo(dic).exists()) {
			// fallback to defaults
			QStringList temp;
			QStringList fallBackPaths;
#ifndef Q_WS_WIN
#ifndef PREFIX
#define PREFIX
#endif
			fallBackPaths << PREFIX"/share/hunspell" << PREFIX"/share/myspell"
			              << "/usr/share/hunspell" << "/usr/share/myspell" ;
#endif
			dic=findResourceFile(QString(QLocale::system().name())+".dic", true, temp, fallBackPaths);
			if (dic=="") spell_dic=findResourceFile("en_US.dic", true, temp, fallBackPaths);
			if (dic=="") spell_dic=findResourceFile("en_GB.dic", true, temp, fallBackPaths);
			if (dic=="") spell_dic=findResourceFile("fr_FR.dic", true, temp, fallBackPaths);
			if (dic=="") spell_dic=findResourceFile("de_DE.dic", true, temp, fallBackPaths);
		}
		QFileInfo fi(dic);
		if (fi.exists()) {
			spellDictDir = fi.absolutePath();
			spellLanguage = fi.baseName();
		}
	}
	if (grammarCheckerConfig->wordlistsDir.isEmpty()) {
		QString sw = findResourceFile("de.stopWords", true, QStringList(), QStringList() << spellDictDir);
		if (sw=="") sw = findResourceFile("en.stopWords", true, QStringList(), QStringList() << spellDictDir);
		if (QFileInfo(sw).exists()) grammarCheckerConfig->wordlistsDir = QFileInfo(sw).absolutePath();
	}
	
	if (thesaurus_database=="<dic not found>"||thesaurus_database=="") {
		thesaurus_database=findResourceFile("th_"+QString(QLocale::system().name())+"_v2.dat");
		if (thesaurus_database=="") thesaurus_database=findResourceFile("th_en_US_v2.dat");
		if (thesaurus_database=="") thesaurus_database=findResourceFile("th_en_GB_v2.dat");
		if (thesaurus_database=="") thesaurus_database=findResourceFile("th_fr_FR_v2.dat");
		if (thesaurus_database=="") thesaurus_database=findResourceFile("th_de_DE_v2.dat");
	}
	
	
	//----------------------------editor--------------------
	if (editorConfig->showlinemultiples==-1) {
		if (config->value("Editor/Line Numbers",true).toBool()) editorConfig->showlinemultiples=1;  //texmaker import
		else editorConfig->showlinemultiples=0;
	}
	
	//completion
    QStringList cwlFiles=config->value("Editor/Completion Files",QStringList() << "tex.cwl" << "latex-document.cwl" << "latex-mathsymbols.cwl").toStringList();
	//completerConfig->words=loadCwlFiles(cwlFiles,ltxCommands,completerConfig);
	LatexParser &latexParser = LatexParser::getInstance();
	foreach(const QString& cwlFile,cwlFiles){
		LatexPackage pck=loadCwlFile(cwlFile,completerConfig);
		completerConfig->words.append(pck.completionWords);
		latexParser.optionCommands.unite(pck.optionCommands);
		latexParser.environmentAliases.unite(pck.environmentAliases);
		//ltxCommands->possibleCommands.unite(pck.possibleCommands); // qt error, does not work properly
		foreach(const QString& elem,pck.possibleCommands.keys()){
			QSet<QString> set2=pck.possibleCommands[elem];
			QSet<QString> set=latexParser.possibleCommands[elem];
			set.unite(set2);
			latexParser.possibleCommands[elem]=set;
		}
	}
	
	completerConfig->setFiles(cwlFiles);
	// remove old solution from .ini
	if(config->contains("Editor/Completion Usage"))
		config->remove("Editor/Completion Usage");
	//web publish dialog
	webPublishDialogConfig->readSettings(*config);
	//insert graphics dialog
	insertGraphicsConfig->readSettings(*config);
	
	//build commands
	if (!buildManager) {
		txsCritical("No build Manager created! => crash");
		return 0;
	}
	buildManager->readSettings(*config);
	runLaTeXBibTeXLaTeX=config->value("Tools/After BibTeX Change", "tmx://latex && tmx://bibtex && tmx://latex").toString()!="";
	
	//import old key replacements or set default
	QStringList keyReplace, keyReplaceAfterWord, keyReplaceBeforeWord;
	if (!config->value("User/New Key Replacements Created",false).toBool()) {
		int keyReplaceCount = config->value("User/KeyReplaceCount",-1).toInt();
		if (keyReplaceCount ==-1) {
			//default
			/* new system ...
   keyReplace.append("\"");
   QString loc=QString(QLocale::system().name()).left(2);
   if (loc=="de") {
    keyReplaceBeforeWord.append("\">");
    keyReplaceAfterWord.append("\"<");
   } else {
    keyReplaceAfterWord.append("''");
    keyReplaceBeforeWord.append("``");
   }
      */
			keyReplace.append("%");
			keyReplaceBeforeWord.append("%");
			keyReplaceAfterWord.append(" %");
		} else for (int i=0; i<keyReplaceCount; i++) {
			keyReplace.append(config->value("User/KeyReplace"+QVariant(i).toString(),i!=0?"'":"\"").toString());
			keyReplaceAfterWord.append(config->value("User/KeyReplaceAfterWord"+QVariant(i).toString(),i!=0?"":"").toString());
			keyReplaceBeforeWord.append(config->value("User/KeyReplaceBeforeWord"+QVariant(i).toString(),i!=0?"":"\">").toString());
		}
	}
	
	//user macros
	QStringList userTags = config->value("User/Tags").toStringList();
	QStringList userNames = config->value("User/TagNames").toStringList();
	QStringList userAbbrevs = config->value("User/TagAbbrevs").toStringList();
	QStringList userTriggers = config->value("User/TagTriggers").toStringList();
	while (userTriggers.size()<userTags.size()) userTriggers << "";
	
	for (int i=0; i < keyReplace.size(); i++) {
		userNames.append(tr("Key replacement: %1 %2").arg(keyReplace[i]).arg(tr("before word")));
		userTags.append(keyReplaceBeforeWord[i].replace("%", "%%"));
		userAbbrevs.append("");
		userTriggers.append("(?<=\\s|^)"+QRegExp::escape(keyReplace[i]));
		
		userNames.append(tr("Key replacement: %1 %2").arg(keyReplace[i]).arg(tr("after word")));
		userTags.append(keyReplaceAfterWord[i].replace("%", "%%"));
		userAbbrevs.append("");
		userTriggers.append("(?<=\\S)"+QRegExp::escape(keyReplace[i]));
	}
	
	for (int i=0;i<userTags.size();i++)
		completerConfig->userMacro.append(Macro(userNames.value(i,""),userTags[i], userAbbrevs.value(i,""),userTriggers.value(i,"")));
	
	
	
	//menu shortcuts
	QMap<QString, QString> aliases = QMap<QString, QString>();
	aliases.insert("main/user/commands/", "main/tools/user/");
	int size = config->beginReadArray("keysetting");
	for (int i = 0; i < size; ++i) {
		config->setArrayIndex(i);
		QString id = config->value("id").toString();
		for (QMap<QString, QString>::iterator it = aliases.begin(), end = aliases.end(); it != end; ++it)
			if (id.startsWith(it.key())) {
				id.replace(0, it.key().length(), it.value());
				break;
			}
			
		managedMenuNewShortcuts.append(QPair<QString, QString> (id, config->value("key").toString()));
	}
	config->endArray();
	
	//changed latex menus
	manipulatedMenus=config->value("changedLatexMenus").toMap();
	
	//custom toolbar
	for (int i=0; i<managedToolBars.size();i++){
		ManagedToolBar& mtb=managedToolBars[i];
		mtb.actualActions=config->value(mtb.name+"ToolBar").toStringList();
		if (mtb.actualActions.empty()) mtb.actualActions=mtb.defaults;
	}
	replacedIconsOnMenus=config->value("customIcons").toMap();
	
	//custom highlighting
	customEnvironments=config->value("customHighlighting").toMap();
	LatexParser::getInstance().customCommands = QSet<QString>::fromList(config->value("customCommands").toStringList());
	
	//--------------------appearance------------------------------------
	QFontDatabase fdb;
	QStringList xf = fdb.families();
	//editor
#ifdef Q_WS_WIN
	if (editorConfig->fontFamily.isEmpty()){
		if (xf.contains("Courier New",Qt::CaseInsensitive)) editorConfig->fontFamily="Courier New";
		else editorConfig->fontFamily=qApp->font().family();
	}
	if (editorConfig->fontSize==-1)
		editorConfig->fontSize=10;
#else
	if (editorConfig->fontFamily.isEmpty()){
		if (xf.contains("DejaVu Sans Mono",Qt::CaseInsensitive)) editorConfig->fontFamily="DejaVu Sans Mono";
		//else if (xf.contains("Lucida Sans Unicode",Qt::CaseInsensitive)) editorConfig->fontFamily="Lucida Sans Unicode";
		else if (xf.contains("Lucida Sans Typewriter",Qt::CaseInsensitive)) editorConfig->fontFamily="Lucida Sans Typewriter";
		else editorConfig->fontFamily=qApp->font().family();
	}
	if (editorConfig->fontSize==-1)
		editorConfig->fontSize=qApp->font().pointSize();
#endif
	
	//interface
	systemPalette = QApplication::palette();
	defaultStyleName=QApplication::style()->objectName();
	
#ifdef Q_WS_X11
	if (interfaceFontFamily=="<later>") {
		//use an interface like Texmaker
		if (xf.contains("DejaVu Sans",Qt::CaseInsensitive)) interfaceFontFamily="DejaVu Sans";
		else if (xf.contains("DejaVu Sans LGC",Qt::CaseInsensitive)) interfaceFontFamily="DejaVu Sans LGC";
		else if (xf.contains("Bitstream Vera Sans",Qt::CaseInsensitive)) interfaceFontFamily="Bitstream Vera Sans";
		else if (xf.contains("Luxi Sans",Qt::CaseInsensitive)) interfaceFontFamily="Luxi Sans";
		else interfaceFontFamily=QApplication::font().family();
	}
	if (interfaceStyle=="<later>") {
		if (x11desktop_env()==0) //no-kde
		{
			if (QStyleFactory::keys().contains("GTK+")) interfaceStyle="GTK+";//gtkstyle
			else interfaceStyle="Cleanlooks";
		} else if ((x11desktop_env() ==4) && (QStyleFactory::keys().contains("Oxygen"))) interfaceStyle="Oxygen"; //kde4+oxygen
		else interfaceStyle="Plastique"; //others
	}
#endif
	
	setInterfaceStyle();
	QApplication::setFont(QFont(interfaceFontFamily, interfaceFontSize));
	
	//language
	QString locale=language;
	appTranslator=new QTranslator(this);
	basicTranslator=new QTranslator(this);
	loadTranslations(language);
	QCoreApplication::installTranslator(appTranslator);
	QCoreApplication::installTranslator(basicTranslator);
	
	config->endGroup();
	
	return config;
}
QSettings* ConfigManager::saveSettings(const QString& saveName) {
	Q_ASSERT(persistentConfig);
	QSettings *config= saveName.isEmpty()?persistentConfig:(new QSettings(saveName, QSettings::IniFormat));
	config->setValue("IniMode",true);
	
	config->beginGroup("texmaker");

	buildManager->saveSettings(*config); //save first, so it can set managed properties
	
	//----------managed properties--------------------
	foreach (const ManagedProperty& mp, managedProperties)
		config->setValue(mp.name, mp.valueToQVariant());
	
	//completion
	if (!completerConfig->getLoadedFiles().isEmpty())
		config->setValue("Editor/Completion Files",completerConfig->getLoadedFiles());
	
	//web publish dialog
	webPublishDialogConfig->saveSettings(*config);
	insertGraphicsConfig->saveSettings(*config);
	
	
	//---------------------build commands----------------
	config->setValue("Tools/After BibTeX Change",runLaTeXBibTeXLaTeX?"tmx://latex && tmx://bibtex && tmx://latex":"");
	
	//-------------------key replacements-----------------
	config->setValue("User/New Key Replacements Created", true);
	
	//user macros
	QStringList userTags, userNames, userAbbrevs, userTriggers;
	foreach (const Macro&m, completerConfig->userMacro){
		if(m.name==TXS_AUTO_REPLACE_QUOTE_OPEN || m.name==TXS_AUTO_REPLACE_QUOTE_CLOSE)
			continue;
		userNames << m.name;
		userTags << m.tag;
		userAbbrevs << m.abbrev;
		userTriggers << m.trigger;
	}
	config->setValue("User/Tags", userTags);
	config->setValue("User/TagNames", userNames);
	config->setValue("User/TagAbbrevs", userAbbrevs);
	config->setValue("User/TagTriggers", userTriggers);
	
	//menu shortcuts
	config->beginWriteArray("keysetting");
	for (int i = 0; i < managedMenuNewShortcuts.size(); ++i) {
		config->setArrayIndex(i);
		config->setValue("id", managedMenuNewShortcuts[i].first);
		config->setValue("key", managedMenuNewShortcuts[i].second);
	}
	config->endArray();
	
	//changed latex menus
	config->setValue("changedLatexMenus",manipulatedMenus);
	//custom toolbar
	for (int i=0; i<managedToolBars.size();i++){
		ManagedToolBar& mtb=managedToolBars[i];
		if (mtb.actualActions == mtb.defaults) config->setValue(mtb.name+"ToolBar", QStringList());
		else config->setValue(mtb.name+"ToolBar", mtb.actualActions);
	}
	config->setValue("customIcons",replacedIconsOnMenus);
	// custom highlighting
	config->setValue("customHighlighting",customEnvironments);
	QStringList zw=LatexParser::getInstance().customCommands.toList();
	config->setValue("customCommands",zw);
	
	config->endGroup();
	
	config->sync();
	
	return config;
}

bool ConfigManager::execConfigDialog() {
	ConfigDialog *confDlg = new ConfigDialog(qobject_cast<QWidget*>(parent()));
	confDlg->riddled = configRiddled;
	//----------managed properties--------------------
	foreach (const ManagedProperty& mp, managedProperties)
		if (mp.widgetOffset)
			mp.writeToObject(*((QWidget**)((char*)&confDlg->ui + mp.widgetOffset))); //convert to char*, because the offset is in bytes
	
	//files
	//if (newfile_encoding)
	//	confDlg->ui.comboBoxEncoding->setCurrentIndex(confDlg->ui.comboBoxEncoding->findText(newfile_encoding->name(), Qt::MatchExactly));
	
	//-----------------------editor------------------------------
	switch (editorConfig->showlinemultiples) {
	case 0:
		confDlg->ui.comboboxLineNumbers->setCurrentIndex(0);
		break;
	case 10:
		confDlg->ui.comboboxLineNumbers->setCurrentIndex(2);
		break;
	default:
		confDlg->ui.comboboxLineNumbers->setCurrentIndex(1);
	}
	if (editorConfig->autoindent && editorConfig->weakindent) confDlg->ui.comboBoxAutoIndent->setCurrentIndex(1);
	else if (editorConfig->autoindent) confDlg->ui.comboBoxAutoIndent->setCurrentIndex(2);
	else confDlg->ui.comboBoxAutoIndent->setCurrentIndex(0);
	if(confDlg->ui.comboBoxAutoIndent->currentIndex()>0 && editorConfig->indentWithSpaces) confDlg->ui.comboBoxAutoIndent->setCurrentIndex(confDlg->ui.comboBoxAutoIndent->currentIndex()+2);
	
	//completion
	confDlg->ui.checkBoxCaseSensitive->setChecked(completerConfig->caseSensitive!=LatexCompleterConfig::CCS_CASE_INSENSITIVE);
	confDlg->ui.checkBoxCaseSensitiveInFirstCharacter->setChecked(completerConfig->caseSensitive==LatexCompleterConfig::CCS_FIRST_CHARACTER_CASE_SENSITIVE);
	
	
	lastLanguage = language;
	QStringList languageFiles=findResourceFiles("translations","texstudio_*.qm") << findResourceFiles("","texstudio_*.qm");
	languageFiles << findResourceFiles("translations","texmakerx_*.qm") << findResourceFiles("","texmakerx_*.qm");
	for (int i=languageFiles.count()-1;i>=0;i--){
		QString temp = languageFiles[i].mid(languageFiles[i].indexOf("_")+1);
		temp.truncate(temp.indexOf("."));
		if (languageFiles.contains(temp)) languageFiles.removeAt(i);
		else languageFiles[i] = temp;
	}
	if (!languageFiles.contains("en")) languageFiles.append("en");
	int langId=-1;
	for (int i=0;i<languageFiles.count();i++){
		confDlg->ui.comboBoxLanguage->addItem(languageFiles[i]);
		if (languageFiles[i] == language) langId=i;
	}
	confDlg->ui.comboBoxLanguage->addItem(tr("default"));
	if (language=="") confDlg->ui.comboBoxLanguage->setEditText(tr("default"));
	else confDlg->ui.comboBoxLanguage->setEditText(language);
	if (langId!=-1) confDlg->ui.comboBoxLanguage->setCurrentIndex(langId);
	else confDlg->ui.comboBoxLanguage->setCurrentIndex(confDlg->ui.comboBoxLanguage->count()-1);
	
	QStringList files=findResourceFiles("completion","*.cwl",QStringList(configBaseDir));
	QListWidgetItem *item;
	const QStringList& loadedFiles = completerConfig->getLoadedFiles();
	foreach(const QString& elem,files) {
		item=new QListWidgetItem(elem,confDlg->ui.completeListWidget);
		item->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
		if (loadedFiles.contains(elem)) item->setCheckState(Qt::Checked);
		else  item->setCheckState(Qt::Unchecked);
	}
	//preview
	confDlg->ui.comboBoxDvi2PngMode->setCurrentIndex(buildManager->dvi2pngMode);
	
	//Autosave
	if(autosaveEveryMinutes==0) confDlg->ui.comboBoxAutoSave->setCurrentIndex(0);
	if(0<autosaveEveryMinutes && autosaveEveryMinutes<6) confDlg->ui.comboBoxAutoSave->setCurrentIndex(1);
	if(5<autosaveEveryMinutes && autosaveEveryMinutes<11) confDlg->ui.comboBoxAutoSave->setCurrentIndex(2);
	if(10<autosaveEveryMinutes && autosaveEveryMinutes<21) confDlg->ui.comboBoxAutoSave->setCurrentIndex(3);
	if(20<autosaveEveryMinutes) confDlg->ui.comboBoxAutoSave->setCurrentIndex(4);
	//--build things
	//normal commands
	pdflatexEdit = 0;
    buildManager->updateCommandNames();
	tempCommands = buildManager->getAllCommands();
	QStringList tempOrder = buildManager->getCommandsOrder();
	commandInputs.clear(); userCommandInputs.clear(); userCommandNameInputs.clear();
	createCommandList(confDlg->ui.groupBoxCommands, tempOrder, false, false);
	createCommandList(confDlg->ui.groupBoxMetaCommands, tempOrder, false, true);
	createCommandList(confDlg->ui.groupBoxUserCommands, tempOrder, true, false);
    confDlg->setBuildManger(buildManager);
	
	//quickbuild/more page	
	confDlg->ui.checkBoxReplaceBeamer->setChecked(buildManager->previewRemoveBeamer);
	confDlg->ui.checkBoxPrecompilePreamble->setChecked(buildManager->previewPrecompilePreamble);
	
	confDlg->ui.checkBoxRunAfterBibTeXChange->setChecked(runLaTeXBibTeXLaTeX);
	
	QIcon fileOpenIcon = getRealIcon("fileopen");
	confDlg->ui.pushButtonDictDir->setIcon(fileOpenIcon);
	confDlg->ui.btSelectThesaurusFileName->setIcon(fileOpenIcon);

	// grammar
	confDlg->ui.pushButtonGrammarWordlists->setIcon(fileOpenIcon);
	confDlg->ui.pushButtonGrammarLTPath->setIcon(fileOpenIcon);
	confDlg->ui.pushButtonGrammarLTJava->setIcon(fileOpenIcon);
	
	//menu shortcuts
	QTreeWidgetItem * menuShortcuts=new QTreeWidgetItem((QTreeWidget*)0, QStringList() << QString(tr("Menus")));
	foreach(QMenu* menu, managedMenus)
		managedMenuToTreeWidget(menuShortcuts,menu);
	confDlg->ui.shortcutTree->addTopLevelItem(menuShortcuts);
	menuShortcuts->setExpanded(true);
	
	QTreeWidgetItem * editorItem=new QTreeWidgetItem((QTreeWidget*)0, QStringList() << ConfigDialog::tr("Editor"));
	QTreeWidgetItem * editorKeys = new QTreeWidgetItem(editorItem, QStringList() << ConfigDialog::tr("Basic Key Mapping"));
	
	Q_ASSERT((int)Qt::CTRL == (int)Qt::ControlModifier && (int)Qt::ALT == (int)Qt::AltModifier && (int)Qt::SHIFT == (int)Qt::ShiftModifier && (int)Qt::META == (int)Qt::MetaModifier);
	QMultiMap<int, int> keysReversed;
	QHash<int, int>::const_iterator it = this->editorKeys.constBegin();
	while (it != this->editorKeys.constEnd()) {
		keysReversed.insertMulti(it.value(), it.key());
		++it;
	}
	int ht=confDlg->ui.comboBoxLanguage->minimumSizeHint().height();
	foreach(const int elem, editorAvailableOperations){
		QList<int> keys=keysReversed.values(elem);
		bool listEmpty=false;
		if(keys.isEmpty()){
			keys<< 0;
			listEmpty=true;
		}
		foreach(const int key,keys){
			QTreeWidgetItem * twi=0;
			if(listEmpty){
				twi = new QTreeWidgetItem(editorKeys, QStringList() << LatexEditorViewConfig::translateEditOperation(elem) << "" << tr("<none>"));
			} else {
				twi = new QTreeWidgetItem(editorKeys, QStringList() << LatexEditorViewConfig::translateEditOperation(elem) << "" << QKeySequence(key).toString(QKeySequence::NativeText));
			}
			twi->setData(0, Qt::UserRole, elem);
			twi->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled);
#ifdef Q_WS_WIN
			QSize sz=twi->sizeHint(0);
			twi->setSizeHint(0,QSize(sz.width(),ht));
#endif
		}
	}
	QTreeWidgetItem * twi=new QTreeWidgetItem(editorKeys, QStringList() << ShortcutDelegate::addRowButton);
#ifdef Q_WS_WIN
	QSize sz=twi->sizeHint(0);
	twi->setSizeHint(0,QSize(sz.width(),ht));
#else
    Q_UNUSED(twi);
    Q_UNUSED(ht);
#endif

	
	confDlg->ui.shortcutTree->addTopLevelItem(editorItem);
	editorItem->setExpanded(true);
	
	ShortcutDelegate delegate;
	delegate.treeWidget=confDlg->ui.shortcutTree;
	confDlg->ui.shortcutTree->setItemDelegate(&delegate); //setting in the config dialog doesn't work
	delegate.connect(confDlg->ui.shortcutTree,SIGNAL(itemClicked(QTreeWidgetItem *, int)),&delegate,SLOT(treeWidgetItemClicked(QTreeWidgetItem * , int)));
	
	//custom menus
	confDlg->menuParent=menuParent;
	changedItemsList.clear();
	manipulatedMenuTree.clear();
	superAdvancedItems.clear();
	foreach(QMenu* menu, managedMenus){
		QTreeWidgetItem *menuLatex=managedLatexMenuToTreeWidget(0,menu);
		if(menuLatex) {
			confDlg->ui.latexTree->addTopLevelItem(menuLatex);
			menuLatex->setExpanded(true);
		}
	}
	connect(confDlg->ui.checkBoxShowAllMenus, SIGNAL(toggled(bool)), SLOT(toggleVisibleTreeItems(bool)));
	toggleVisibleTreeItems(false);
	connect(confDlg->ui.latexTree,SIGNAL(itemChanged(QTreeWidgetItem*,int)),this,SLOT(latexTreeItemChanged(QTreeWidgetItem*,int)));
	QAction* act = new QAction(tr("insert new menu item (before)"), confDlg->ui.latexTree);
	connect(act, SIGNAL(triggered()), SLOT(latexTreeNewItem()));
	confDlg->ui.latexTree->addAction(act);
	act = new QAction(tr("insert new sub menu (before)"), confDlg->ui.latexTree);
	connect(act, SIGNAL(triggered()), SLOT(latexTreeNewMenuItem()));
	confDlg->ui.latexTree->addAction(act);
	confDlg->ui.latexTree->setContextMenuPolicy(Qt::ActionsContextMenu);

	ComboBoxDelegate * cbd = new ComboBoxDelegate(confDlg->ui.latexTree);
	cbd->defaultItems = possibleMenuSlots;
	confDlg->ui.latexTree->setItemDelegate(cbd);
	
	// custom toolbars
	confDlg->customizableToolbars.clear();
	foreach (const ManagedToolBar &mtb, managedToolBars){
		Q_ASSERT(mtb.toolbar);
		confDlg->customizableToolbars.append(mtb.actualActions);
		confDlg->ui.comboBoxToolbars->addItem(qApp->translate("Texmaker",qPrintable(mtb.name)));
	}
	confDlg->allMenus=managedMenus;
	confDlg->standardToolbarMenus=QList<QMenu*>()<< getManagedMenu("main/latex") << getManagedMenu("main/math") << getManagedMenu("main/user");
	confDlg->ui.comboBoxActions->addItem(tr("Latex/Math menus"));
	confDlg->ui.comboBoxActions->addItem(tr("All menus"));
	confDlg->ui.comboBoxActions->addItem(tr("Special Tags"));
	confDlg->replacedIconsOnMenus=&replacedIconsOnMenus;
	
	
	//appearance
	QString displayedInterfaceStyle=interfaceStyle==""?tr("default"):interfaceStyle;
	confDlg->ui.comboBoxInterfaceStyle->clear();
	confDlg->ui.comboBoxInterfaceStyle->addItems(QStyleFactory::keys()<<tr("default"));
	confDlg->ui.comboBoxInterfaceStyle->setCurrentIndex(confDlg->ui.comboBoxInterfaceStyle->findText(displayedInterfaceStyle));
	confDlg->ui.comboBoxInterfaceStyle->setEditText(displayedInterfaceStyle);
	
	confDlg->ui.checkBoxTabbedLogView->setChecked(tabbedLogView);
	confDlg->ui.checkBoxTabbedStructureView->setChecked(!newLeftPanelLayout);
	
	confDlg->fmConfig->setBasePointSize( editorConfig->fontSize );
	confDlg->fmConfig->addScheme("",QDocument::formatFactory());
	
	// custom higlighting
	{
		confDlg->environModes=&enviromentModes;
		int l=0;
		confDlg->ui.twHighlighEnvirons->setRowCount(customEnvironments.size()+1);
		QMap<QString, QVariant>::const_iterator i;
		for (i = customEnvironments.constBegin(); i != customEnvironments.constEnd(); ++i){
			QString env=i.key();
			QTableWidgetItem *item=new QTableWidgetItem(env);
			confDlg->ui.twHighlighEnvirons->setItem(l,0,item);
			//item=new QTableWidgetItem(i.value());
			QComboBox *cb=new QComboBox(0);
			cb->insertItems(0,enviromentModes);
			cb->setCurrentIndex(i.value().toInt());
			confDlg->ui.twHighlighEnvirons->setCellWidget(l,1,cb);
			l++;
		}
		QTableWidgetItem *item=new QTableWidgetItem("");
		confDlg->ui.twHighlighEnvirons->setItem(l,0,item);
		//item=new QTableWidgetItem(i.value());
		QComboBox *cb=new QComboBox(0);
		cb->insertItems(0,enviromentModes);
		confDlg->ui.twHighlighEnvirons->setCellWidget(l,1,cb);
		
		confDlg->ui.twCustomSyntax->setRowCount(LatexParser::getInstance().customCommands.count()+1);
		l=0;
		foreach(const QString& cmd, LatexParser::getInstance().customCommands){
			QTableWidgetItem *item=new QTableWidgetItem(cmd);
			confDlg->ui.twCustomSyntax->setItem(l,0,item);
			l++;
		}
		item=new QTableWidgetItem("");
		confDlg->ui.twCustomSyntax->setItem(l,0,item);
	}
	
	
	//EXECUTE IT
	bool executed = confDlg->exec();
	configRiddled = confDlg->riddled;
	
	//handle changes
	if (executed) {
		QList<void*> changedProperties;
		//----------managed properties--------------------
		for (int i=0;i<managedProperties.size();i++)
			if (managedProperties[i].widgetOffset && managedProperties[i].readFromObject(*((QWidget**)((char*)&confDlg->ui + managedProperties[i].widgetOffset))))
				changedProperties << managedProperties[i].storage;
		
		//files
		newFileEncoding=QTextCodec::codecForName(newFileEncodingName.toAscii().data());
		
		if (changedProperties.contains(&maxRecentFiles) || changedProperties.contains(&maxRecentProjects))
			updateRecentFiles(true);
		
		//editor
		editorConfig->autoindent=confDlg->ui.comboBoxAutoIndent->currentIndex()!=0;
		editorConfig->weakindent=(confDlg->ui.comboBoxAutoIndent->currentIndex()&1)==1;
		editorConfig->indentWithSpaces=confDlg->ui.comboBoxAutoIndent->currentIndex()>2;
		switch (confDlg->ui.comboboxLineNumbers->currentIndex()) {
		case 0:
			editorConfig->showlinemultiples=0;
			break;
		case 2:
			editorConfig->showlinemultiples=10;
			break;
		default:
			editorConfig->showlinemultiples=1;
			break;
		}
		
		//autosave
		QList<int> times;
		times << 0 << 5 << 10 << 20 << 60;
		autosaveEveryMinutes=times.value(confDlg->ui.comboBoxAutoSave->currentIndex(),0);
		
		// update user tags menu to update quote replacement
		if (changedProperties.contains(&replaceQuotes)) {
			bool conflict = false;
			if (replaceQuotes)
				for(int i=0;i<completerConfig->userMacro.count();i++){
					const Macro& m=completerConfig->userMacro.at(i);
					if (m.name == TXS_AUTO_REPLACE_QUOTE_OPEN ||
					              m.name == TXS_AUTO_REPLACE_QUOTE_CLOSE) continue;
					if (m.trigger == "(?<=\\s|^)\"" || m.trigger == "(?<=^)\"" || m.trigger == "(?<=\\S)\"") {
						conflict = true;
						qDebug() << m.trigger;
						break;
					}
				}
			if (conflict) 
				if (txsConfirm(tr("You have enabled auto quote replacement. However, there are user tags with trigger string (?<=\\s|^) or (?<=\\S) which will override the new quote replacement.\nDo you want to remove them?"))){
					for(int i=completerConfig->userMacro.count()-1;i>=0;i--){
						const Macro& m=completerConfig->userMacro.at(i);
						if (m.trigger == "(?<=\\s|^)\"" || m.trigger == "(?<=^)\"" || m.trigger == "(?<=\\S)\"") 
							completerConfig->userMacro.removeAt(i);
					}
				}
			
			updateUserMacroMenu();
		}
		
		//completion
		completerConfig->enabled=confDlg->ui.checkBoxCompletion->isChecked();
		if (!confDlg->ui.checkBoxCaseSensitive->isChecked()) completerConfig->caseSensitive=LatexCompleterConfig::CCS_CASE_INSENSITIVE;
		else if (confDlg->ui.checkBoxCaseSensitiveInFirstCharacter->isChecked()) completerConfig->caseSensitive=LatexCompleterConfig::CCS_FIRST_CHARACTER_CASE_SENSITIVE;
		else completerConfig->caseSensitive=LatexCompleterConfig::CCS_CASE_SENSITIVE;
		completerConfig->completeCommonPrefix=confDlg->ui.checkBoxCompletePrefix->isChecked();
		completerConfig->eowCompletes=confDlg->ui.checkBoxEOWCompletes->isChecked();
		completerConfig->tooltipHelp=confDlg->ui.checkBoxToolTipHelp->isChecked();
		completerConfig->usePlaceholders=confDlg->ui.checkBoxUsePlaceholders->isChecked();
		QStringList newFiles;
		QListWidgetItem *elem;
		for (int i=0; i<confDlg->ui.completeListWidget->count(); i++) {
			elem=confDlg->ui.completeListWidget->item(i);
			if (elem->checkState()==Qt::Checked) newFiles.append(elem->text());
		}
		LatexParser& latexParser = LatexParser::getInstance();
		latexParser.clear();
		latexParser.init();
		//completerConfig->words=loadCwlFiles(newFiles,ltxCommands,completerConfig);
		foreach(const QString& cwlFile,newFiles){
			LatexPackage pck=loadCwlFile(cwlFile,completerConfig);
			completerConfig->words.append(pck.completionWords);
			latexParser.optionCommands.unite(pck.optionCommands);
			latexParser.environmentAliases.unite(pck.environmentAliases);
			
			//ltxCommands->possibleCommands.unite(pck.possibleCommands); qt bug
			foreach(const QString& elem,pck.possibleCommands.keys()){
				QSet<QString> set2=pck.possibleCommands[elem];
				QSet<QString> set=latexParser.possibleCommands[elem];
				set.unite(set2);
				latexParser.possibleCommands[elem]=set;
			}
		}
		completerConfig->setFiles(newFiles);
		
		//preview
		previewMode=(PreviewMode) confDlg->ui.comboBoxPreviewMode->currentIndex();
		buildManager->dvi2pngMode=(BuildManager::Dvi2PngMode) confDlg->ui.comboBoxDvi2PngMode->currentIndex();
		
		//build things
		QStringList userOrder;
		for (CommandMapping::iterator it = tempCommands.begin(), end = tempCommands.end(); it != end; )
			if (it.value().user) it = tempCommands.erase(it);
			else  ++it;
		for (int i=0;i<commandInputs.size();i++){
			CommandMapping::iterator it = tempCommands.find(commandInputs[i]->property(PROPERTY_COMMAND_NAME).toString());
            if (it != tempCommands.end()) {
                QString text = getText(commandInputs[i]);
                int i=it.value().simpleDescriptionList.indexOf(text);
                if(i>=0)
                    text=it.value().metaSuggestionList.value(i);
                it.value().commandLine =text;
            }
		}
		//read user commands (ugly lists, but we can't use maps because they screw up the ordering)
		for (int i=0;i<userCommandInputs.size();i++){
			CommandInfo ci;
			QString combinedName = getText(userCommandNameInputs[i]);
			int pos = combinedName.indexOf(":");
			ci.id = pos == -1?combinedName:combinedName.left(pos);
			ci.displayName = pos == -1?combinedName:combinedName.mid(pos+1);
			ci.commandLine = getText(userCommandInputs[i]);
			ci.user = true;
			tempCommands.insert(ci.id, ci);
			userOrder << ci.id;
		}
		buildManager->setAllCommands(tempCommands, userOrder);
		/*TODO for (BuildManager::LatexCommand cmd=BuildManager::CMD_LATEX; cmd < BuildManager::CMD_USER_QUICK; ++cmd){
			if (!commandsToEdits.value(cmd)) continue;
			buildManager->setLatexCommand(cmd,commandsToEdits.value(cmd)->text());;
		}
		
		for (BuildManager::LatexCommand cmd=BuildManager::CMD_SVN; cmd <= BuildManager::CMD_SVNADMIN; ++cmd){
			if (!commandsToEdits.value(cmd)) continue;
			buildManager->setLatexCommand(cmd,commandsToEdits.value(cmd)->text());;
		}*/
		
		
		/*Q_ASSERT(confDlg->checkboxInternalPDFViewer);
		QString curPdfViewer = buildManager->getLatexCommand(BuildManager::CMD_VIEWPDF);
		if (confDlg->checkboxInternalPDFViewer && confDlg->checkboxInternalPDFViewer->isChecked() != curPdfViewer.startsWith(BuildManager::TXS_INTERNAL_PDF_VIEWER)) {
			//prepend/remove tmx://internal-pdf-viewer
			if (confDlg->checkboxInternalPDFViewer->isChecked())
				buildManager->setLatexCommand(BuildManager::CMD_VIEWPDF , BuildManager::TXS_INTERNAL_PDF_VIEWER + "/" + curPdfViewer);
			else if (curPdfViewer.startsWith(BuildManager::TXS_INTERNAL_PDF_VIEWER+"/"))
				buildManager->setLatexCommand(BuildManager::CMD_VIEWPDF , curPdfViewer.mid(BuildManager::TXS_INTERNAL_PDF_VIEWER.length() + 1));
			else
				buildManager->setLatexCommand(BuildManager::CMD_VIEWPDF , curPdfViewer.mid(BuildManager::TXS_INTERNAL_PDF_VIEWER.length()));
		}
		
		buildManager->setLatexCommand(BuildManager::CMD_USER_PRECOMPILE,confDlg->ui.lineEditExecuteBeforeCompiling->text());
		buildManager->setLatexCommand(BuildManager::CMD_USER_QUICK,confDlg->ui.lineEditUserquick->text());
		*/
		/*for (int i=0;i < confDlg->ui.quickbuildLayout->count(); i++) {
			QRadioButton *rb = qobject_cast<QRadioButton*>(confDlg->ui.quickbuildLayout->itemAt(i)->widget());
			if (rb && rb->isChecked()){
				buildManager->quickmode=rb->property("quickBuildMode").toInt();
				break;
			}
		}
		*/
		buildManager->previewRemoveBeamer = confDlg->ui.checkBoxReplaceBeamer->isChecked();
		buildManager->previewPrecompilePreamble = confDlg->ui.checkBoxPrecompilePreamble->isChecked();
		
		runLaTeXBibTeXLaTeX=confDlg->ui.checkBoxRunAfterBibTeXChange->isChecked();
		
		
		//formats
		confDlg->fmConfig->apply();
		
		this->editorKeys.clear();
		for (int i=0;i<editorKeys->childCount();i++)
			if (editorKeys->child(i)->data(0, Qt::UserRole).toInt() != /*QEditor::None*/0)
				this->editorKeys.insert(QKeySequence::fromString(editorKeys->child(i)->text(2),QKeySequence::NativeText), editorKeys->child(i)->data(0, Qt::UserRole).toInt());
		
		//menus
		managedMenuNewShortcuts.clear();
		treeWidgetToManagedMenuTo(menuShortcuts);
		treeWidgetToManagedLatexMenuTo();
		
		// custom toolbar
		Q_ASSERT(confDlg->customizableToolbars.size() == managedToolBars.size());
		for (int i=0; i<managedToolBars.size();i++){
			ManagedToolBar& mtb=managedToolBars[i];
			mtb.actualActions=confDlg->customizableToolbars[i];
		}
		
		//  interface
		if (changedProperties.contains(&interfaceFontFamily) || changedProperties.contains(&interfaceFontSize))
			QApplication::setFont(QFont(interfaceFontFamily, interfaceFontSize));
		if (changedProperties.contains(&interfaceStyle) || changedProperties.contains(&modernStyle) || changedProperties.contains(&useTexmakerPalette)){
			if (interfaceStyle==tr("default")) interfaceStyle="";
			setInterfaceStyle();
		}
		
		// read checkbox and set logViewer accordingly
		if (changedProperties.contains(&tabbedLogView))
			emit tabbedLogViewChanged(tabbedLogView);
		if (newLeftPanelLayout != !confDlg->ui.checkBoxTabbedStructureView->isChecked()){
			newLeftPanelLayout = !confDlg->ui.checkBoxTabbedStructureView->isChecked();
			emit newLeftPanelLayoutChanged(newLeftPanelLayout);
		}
		//language
		if (language == tr("default")) language="";
		if (language!=lastLanguage) loadTranslations(language);
		
		// custom highlighting
		customEnvironments.clear();
		for(int i=0;i<confDlg->ui.twHighlighEnvirons->rowCount();i++){
			QString env=confDlg->ui.twHighlighEnvirons->item(i,0)->text();
			if(!env.isEmpty()){
				if (env.endsWith("*") && !env.endsWith("\\*"))
					env.replace(env.length()-1,1,"\\*");
				QComboBox *cb=qobject_cast<QComboBox*>(confDlg->ui.twHighlighEnvirons->cellWidget(i,1));
				customEnvironments.insert(env,cb->currentIndex());
			}
		}
		latexParser.customCommands.clear();
		for(int i=0;i<confDlg->ui.twCustomSyntax->rowCount();i++){
			QString cmd=confDlg->ui.twCustomSyntax->item(i,0)->text();
			if(!cmd.isEmpty())
				latexParser.customCommands.insert(cmd);
		}
		
	}
	delete confDlg;
	return executed;
}


bool ConfigManager::addRecentFile(const QString & fileName, bool asMaster){ 
	int p=recentFilesList.indexOf(fileName);
	bool changed=p!=0;
	if (p>0) recentFilesList.removeAt(p);
	if (changed) recentFilesList.prepend(fileName);
	if (recentFilesList.count()>maxRecentFiles) recentFilesList.removeLast();
	
	if (asMaster) {
		p=recentProjectList.indexOf(fileName);
		changed|=p!=0;
		if (p>0) recentProjectList.removeAt(p);
		if (p!=0) recentProjectList.prepend(fileName);
		if (recentProjectList.count()>maxRecentProjects) recentProjectList.removeLast();
	}
	
	if (changed) updateRecentFiles();
	
	return changed;
}

void ConfigManager::activateInternalViewer(bool activated){
	if(!activated) return;
	QLineEdit *le = pdflatexEdit;
	REQUIRE(le);
	if(le->text().contains("synctex")) return;
	if (!txsConfirm(tr("To fully utilize the internal pdf-viewer, synctex has to be activated. Shall TeXstudio do it now?")))
		return;
	QString zw=le->text();
	zw.replace("pdflatex ","pdflatex -synctex=1 ",Qt::CaseSensitive);
	le->setText(zw);
}

void ConfigManager::updateRecentFiles(bool alwaysRecreateMenuItems) {
	QMenu* recentMenu = getManagedMenu("main/file/openrecent");
	if (alwaysRecreateMenuItems || (recentMenu->actions().count()!=maxRecentFiles+maxRecentProjects+3)) {
		QList<QAction*> actions=recentMenu->actions(); //recentMenu->clear() doesn't seem to delete the actions (why?)
		for (int i = 0; i< actions.count(); i++)
			recentMenu->removeAction(actions[i]); //neccessary or it crashes
		for (int i = 0; i < maxRecentProjects; ++i)
			newOrLostOldManagedAction(recentMenu, "p"+QString::number(i), tr("Recent 'Master Document' %1").arg(i), SLOT(fileOpenRecentProject()))->setVisible(false);
		recentMenu->addSeparator();
		for (int i = 0; i < maxRecentFiles; ++i)
			newOrLostOldManagedAction(recentMenu, QString::number(i), tr("Recent File %1").arg(i), SLOT(fileOpenRecent()))->setVisible(false);
		newOrLostOldManagedAction(recentMenu, "firstFile", tr("Open first non-open file"), SLOT(fileOpenFirstNonOpen()));
		newOrLostOldManagedAction(recentMenu, "allFiles", tr("&* Open all files"), SLOT(fileOpenAllRecent()));
	}
	
	for (int i=0; i < maxRecentProjects; i++) {
		QAction* act = getManagedAction(QString("main/file/openrecent/p%1").arg(i));
		REQUIRE(act);
		if (i<recentProjectList.count()) {
			act->setVisible(true);
			QString temp = recentProjectList.at(i);
			temp.replace("&", "&&");
			act->setText(tr("Master Document: ")+(i<=13?QString("&%1 ").arg((char)('M'+i)):"")+ temp);
			act->setData(recentProjectList.at(i));
		} else act->setVisible(false);
	}
	for (int i=0; i < maxRecentFiles; i++) {
		QAction* act = getManagedAction(QString("main/file/openrecent/%1").arg(i));
		REQUIRE(act);
		if (i<recentFilesList.count()) {
			act->setVisible(true);
			char schar = '\0';
			if (i+1 <= 9) schar = i+1+'0';
			else if (i+1 <= 9+12) schar = i+1 + 'a' - 10;
			else if (i+1 <= 21+9) schar = i+1 + '!' - 22;
			else if (i+1 <= 30+5) schar = i+1 + '+' - 31;
			else if (i+1 <= 35+7) schar = i+1 + ':' - 36;
			else if (i+1 <= 42+5) schar = i+1 + '[' - 43;
			else if (i+1 <= 47+4) schar = i+1 + '{' - 48;
			QString temp = recentFilesList.at(i);
			temp.replace("&","&&");
			act->setText((schar?QString("&%1 ").arg(schar):"")+temp);
			act->setData(recentFilesList.at(i));
		} else act->setVisible(false);
	}
}

QMenu* ConfigManager::updateListMenu(const QString& menuName, const QStringList& items, const QString& namePrefix, bool prefixNumber, const char* slotName, const int baseShortCut, bool alwaysRecreateMenuItems, int additionalEntries){
	QMenu* menu = getManagedMenu(menuName);
	REQUIRE_RET(menu, 0);
	Q_ASSERT(menu->objectName() == menuName);
	QList<QAction*> actions = menu->actions();
	if (!alwaysRecreateMenuItems &&
	              actions.count() == items.size() + additionalEntries) {
		//set only title
		for (int i = 0; i< items.size(); i++) {
			Q_ASSERT(actions[i]->objectName() == menuName + "/" + namePrefix + QString::number(i));
			actions[i]->setText(prefixNumber?QString("%1: %2").arg(i+1).arg(items[i]) : items[i]);
		}
		if (watchedMenus.contains(menuName))
			emit watchedMenuChanged(menuName);
		return 0;
	}
	//recreate
	for (int i = 0; i< actions.count(); i++)
		menu->removeAction(actions[i]); //neccessary or it crashes
	for (int i = 0; i<items.size(); i++){
		QString id = namePrefix + QString::number(i);
		QString completeId = menu->objectName()+"/"+ id;
		Q_ASSERT(completeId == menuName + "/" + namePrefix + QString::number(i));
		newOrLostOldManagedAction(menu, id, prefixNumber?QString("%1: %2").arg(i+1).arg(items[i]) : items[i], slotName,  (baseShortCut && i<10)?(QList<QKeySequence>() << baseShortCut + i): QList<QKeySequence>())->setData(i);
	}
	if (watchedMenus.contains(menuName))
		emit watchedMenuChanged(menuName);
	return menu;
}

void ConfigManager::updateUserMacroMenu(bool alwaysRecreateMenuItems){
	QStringList macronames;
	// remove quote replacement from list
	for(int i=0;i<completerConfig->userMacro.count();i++){
		Macro m=completerConfig->userMacro.at(i);
		if(m.name==TXS_AUTO_REPLACE_QUOTE_OPEN || m.name==TXS_AUTO_REPLACE_QUOTE_CLOSE){
			completerConfig->userMacro.removeAt(i);
			i--;
		}
	}
	
	
	foreach (const Macro&m , completerConfig->userMacro){
		macronames<<m.name;
	}
	
	QMenu* recreatedMenu = updateListMenu("main/user/tags", macronames, "tag", true, SLOT(insertUserTag()), Qt::SHIFT+Qt::Key_F1, alwaysRecreateMenuItems);
	if (recreatedMenu) {
		recreatedMenu->addSeparator();
		newOrLostOldManagedAction(recreatedMenu, "manage",QCoreApplication::translate("Texmaker", "Edit User &Tags"), SLOT(EditUserMenu()));
	}
	// update quote replacement
	switch(replaceQuotes){
	case 0:
		break;
	case 1:
		completerConfig->userMacro.append(Macro(TXS_AUTO_REPLACE_QUOTE_OPEN,"``", "","(?<=\\s|^)\""));
		completerConfig->userMacro.append(Macro(TXS_AUTO_REPLACE_QUOTE_CLOSE,"''", "","(?<=\\S)\""));
		break;
	case 2:
		completerConfig->userMacro.append(Macro(TXS_AUTO_REPLACE_QUOTE_OPEN,"\"<", "","(?<=\\s|^)\""));
		completerConfig->userMacro.append(Macro(TXS_AUTO_REPLACE_QUOTE_CLOSE,"\">", "","(?<=\\S)\""));
		break;
	case 3:
		completerConfig->userMacro.append(Macro(TXS_AUTO_REPLACE_QUOTE_OPEN,"\"`", "","(?<=\\s|^)\""));
		completerConfig->userMacro.append(Macro(TXS_AUTO_REPLACE_QUOTE_CLOSE,"\"'", "","(?<=\\S)\""));
		break;
	case 4:
		completerConfig->userMacro.append(Macro(TXS_AUTO_REPLACE_QUOTE_OPEN,"\\og ", "","(?<=\\s|^)\""));
		completerConfig->userMacro.append(Macro(TXS_AUTO_REPLACE_QUOTE_CLOSE,"\\fg{}", "","(?<=\\S)\""));
		break;
	case 5:
		completerConfig->userMacro.append(Macro(TXS_AUTO_REPLACE_QUOTE_OPEN,"\">", "","(?<=\\s|^)\""));
		completerConfig->userMacro.append(Macro(TXS_AUTO_REPLACE_QUOTE_CLOSE,"\"<", "","(?<=\\S)\""));
		break;
	default:
		break;
		
	}
}

QMenu* ConfigManager::newManagedMenu(const QString &id,const QString &text) {
	if (!menuParentsBar) qFatal("No menu parent bar!");
	if (!menuParent) qFatal("No menu parent!");
	//check if an old menu with this id exists and update it (for retranslation)
	QMenu *old=menuParent->findChild<QMenu*>(id);
	if (old) {
		old->setTitle(text);
		return old;
	}
	//create new
	QMenu* menu = new QMenu(qobject_cast<QWidget*>(menuParent));
	menuParentsBar->addMenu(menu);
	menu->setTitle(text);
	menu->setObjectName(id);
	managedMenus.append(menu);
	return menu;
}
QMenu* ConfigManager::newManagedMenu(QMenu* menu, const QString &id,const QString &text) {
	if (!menu) return newManagedMenu(id,text);
	QString completeId=menu->objectName()+"/"+ id;
	//check if an old menu with this id exists and update it (for retranslation)
	QMenu *old=menuParent->findChild<QMenu*>(completeId);
	if (old) {
		old->setTitle(text);
		return old;
	}
	//create new
	QMenu* submenu=menu->addMenu(text);
	submenu->setObjectName(completeId);
	return submenu;
}
QAction* ConfigManager::newManagedAction(QWidget* menu, const QString &id,const QString &text, const char* slotName, const QList<QKeySequence> &shortCuts, const QString & iconFile) {
	if (!menuParent) qFatal("No menu parent!");
	REQUIRE_RET(menu, 0);
	QString menuId = menu->objectName();
	QString completeId = menu->objectName()+"/"+ id;
	
	QAction *old=menuParent->findChild<QAction*>(completeId);
	if (old) {
		old->setText(text);
		if (!iconFile.isEmpty()) old->setIcon(getRealIcon(iconFile));
		if (watchedMenus.contains(menuId))
			emit watchedMenuChanged(menuId);
		//don't set shortcut and slot!
		return old;
	}
	
	QAction *act;
	if (iconFile.isEmpty()) act=new QAction(text, menuParent);
	else act=new QAction(getRealIcon(iconFile), text, menuParent);
	
	act->setObjectName(completeId);
	act->setShortcuts(shortCuts);
	if (slotName) {
		connect(act, SIGNAL(triggered()), menuParent, slotName);
		act->setProperty("primarySlot", QString::fromLocal8Bit(slotName));
	}
	menu->addAction(act);
	for (int i=0; i<shortCuts.size(); i++)
		managedMenuShortcuts.insert(act->objectName()+QString::number(i),shortCuts[i]);
	if (watchedMenus.contains(menuId))
		emit watchedMenuChanged(menuId);
	return act;
}

//creates a new action or reuses an existing one (an existing one that is currently not in any menu, but has been in the given menu)
QAction* ConfigManager::newOrLostOldManagedAction(QWidget* menu, const QString &id,const QString &text, const char* slotName, const QList<QKeySequence> &shortCuts, const QString & iconFile){
	QAction* old = menuParent->findChild<QAction*>(menu->objectName() + "/" + id);
	if (!old)
		return newManagedAction(menu, id, text, slotName, shortCuts, iconFile);
	menu->addAction(old);
	old->setText(text);
	if (watchedMenus.contains(menu->objectName()))
		emit watchedMenuChanged(menu->objectName());
	return old;
}

QAction* ConfigManager::newManagedAction(QWidget* menu, const QString &id, QAction* act) {
	if (!menuParent) qFatal("No menu parent!");
	QString completeId = menu->objectName()+"/"+id;
	
	QAction *old=menuParent->findChild<QAction*>(completeId);
	if (old) 
		return old;
	
	
	act->setObjectName(completeId);
	menu->addAction(act);
	managedMenuShortcuts.insert(act->objectName()+"0",act->shortcut());
	return act;
}
QAction* ConfigManager::getManagedAction(const QString& id) {
	QAction* act=0;
	if (menuParent) act=menuParent->findChild<QAction*>(id);
	if (act==0) qWarning("Can't find internal action %s",id.toAscii().data());
	return act;
}
QMenu* ConfigManager::getManagedMenu(const QString& id) {
	QMenu* menu=0;
	if (menuParent) menu=menuParent->findChild<QMenu*>(id);
	if (menu==0) qWarning("Can't find internal menu %s",id.toAscii().data());
	return menu;
}
void ConfigManager::removeManagedMenus(){
	/*foreach (QMenu* menu, managedMenus){
  menu->clear();
  delete menu;
 }
 menuParentsBar->clear();*/
}
void ConfigManager::triggerManagedAction(const QString& id){
	QAction* act = getManagedAction(id);
	if (act) act->trigger();
}

QList<QVariant> parseCommandArguments (const QString& str) {
	QString s = str;
	QList<QVariant> result;
	if (str == "()") return result;
	s.remove(0,1);
	//                            1/-----2---\  /----3----\  /4-/5/6---------6\5\4--4\ 0
	static const QRegExp args("^ *((-? *[0-9]+)|(true|false)|(\"(([^\"]*|\\\\\")*)\")) *,?");
	while (args.indexIn(s) != -1) {
		if (!args.cap(2).isEmpty()) result << args.cap(2).toInt();
		else if (!args.cap(3).isEmpty()) result << (args.cap(3) == "true");
		else if (!args.cap(5).isEmpty()) result << (args.cap(5).replace("\\\"", "\"").replace("\\n", "\n").replace("\\t", "\t").replace("\\\\", "\\"));		
		s.remove(0, args.matchedLength());
	}
	return result;
}

void ConfigManager::connectExtendedSlot(QAction* act, const QString& slot){
	static const char * signal = SIGNAL(triggered());
	if (act->property("primarySlot").isValid()) 
		disconnect(act, signal, menuParent, act->property("primarySlot").toByteArray().data());
	
	if (slot.startsWith('1') || slot.startsWith('2')) {
		act->setProperty("primarySlot", slot);
		connect(act, signal, menuParent, slot.toLocal8Bit());
		return;
	}

	if (slot.endsWith("()") && !slot.contains(':')) {
		QString temp = "1" + slot;
		act->setProperty("primarySlot", temp);
		connect(act, signal, menuParent, temp.toLocal8Bit());
		return;
	}

	int argSeparator = slot.indexOf('(');
	REQUIRE(argSeparator >= 0);
	
	QString slotName = slot.mid(0, argSeparator);	
	QString args = slot.mid(argSeparator);
	if (slotName.contains(":")) {
		act->setProperty("editorSlot", QVariant());
		act->setProperty("editorViewSlot", QVariant());
		if (slotName.startsWith("editorView:")) 
			act->setProperty("editorViewSlot", slotName.mid(strlen("editorView:")));
		else if (slotName.startsWith("editor:")) 
			act->setProperty("editorSlot", slotName.mid(strlen("editor:")));
		else REQUIRE(false);
		slotName = SLOT(relayToEditorSlot());
	} else {
		act->setProperty("slot", slotName);
		slotName = SLOT(relayToOwnSlot());
	}
	act->setProperty("primarySlot", slotName);
	connect(act, signal, menuParent, slotName.toLocal8Bit());
	act->setProperty("args", parseCommandArguments(args));
}
	
QString prettySlotName(QAction* act) {
	QString primary = act->property("primarySlot").toString();
	if (primary.startsWith("1")) primary = primary.mid(1);
	if (primary == "relayToOwnSlot()" || primary == "relayToEditorSlot()") {
		if (primary == "relayToEditorSlot()") {
			if (act->property("editorViewSlot").isValid()) primary = "editorView:" + act->property("editorViewSlot").toString();
			else if (act->property("editorSlot").isValid()) primary = "editor:" + act->property("editorSlot").toString();
		} else primary = act->property("slot").toString();
		primary += "(";
		QList<QVariant> args = act->property("args").value<QList<QVariant> >();
		for (int i=0;i<args.size();i++) {
			if (i!=0) primary += ", ";
			if (args[i].type() == QVariant::String) primary += '"';
			primary += args[i].toString();
			if (args[i].type() == QVariant::String) primary += '"';
		}
		primary += ")";
	}
	return primary;
}


void ConfigManager::modifyMenuContents(){
	QStringList ids = manipulatedMenus.keys();
	while (!ids.isEmpty()) modifyMenuContent(ids, ids.first());
	modifyMenuContentsFirstCall = false;
}

void ConfigManager::modifyMenuContent(QStringList& ids, const QString& id){
	REQUIRE(menuParent);
	int index = ids.indexOf(id);
	if (index < 0) return;
	ids.removeAt(index);
	
	QMap<QString, QVariant>::const_iterator i = manipulatedMenus.find(id);
	if (i == manipulatedMenus.end()) return;
	
	
	QStringList m = i.value().toStringList();
	//qDebug() << id << ": ===> " << m.join(", ");
	QAction * act = menuParent->findChild<QAction*>(id);
	bool  newlyCreated = false;
	if (!act && m.value(3, "") != "") {
		newlyCreated = true;
		QString before = m.value(3);
		modifyMenuContent(ids, before);
		QAction * prevact = 0;
		if (!before.endsWith('/')) 
			prevact = menuParent->findChild<QAction*>(before);
		else {
			before.chop(1);
			QMenu* temp = menuParent->findChild<QMenu*>(before);
			if (temp) prevact = temp->menuAction();
		}
		QString menuName = before.left(before.lastIndexOf("/"));
		QMenu* menu = menuParent->findChild<QMenu*>(menuName);
		if (!menu) { modifyMenuContent(ids, menuName + "/"); menu = menuParent->findChild<QMenu*>(menuName); }
		if (!menu) return;
		
		Q_ASSERT(!prevact || menu->actions().contains(prevact));
		QStringList temp = id.split('/'); 
		if (temp.size() < 2) return;
		if (id.endsWith('/')) {
			QMenu* newMenu = newManagedMenu(menu, temp[temp.size()-2], m.first());
			act = newMenu->menuAction();
		} else {
			QString ownId = temp.takeLast();
			QByteArray defSlot = menu->property("defaultSlot").toByteArray(); 
			if (m.value(4).isEmpty()) {
				while (defSlot.isEmpty() && temp.size() >= 2) {
					temp.removeLast();
					QMenu* tempmenu = menuParent->findChild<QMenu*>(temp.join("/"));
					if (!tempmenu) continue;
					defSlot = tempmenu->property("defaultSlot").toByteArray();
				}
			}
			act = newManagedAction(menu, ownId, m.first(), defSlot.isEmpty()?0:defSlot.data());
		}
		if  (prevact) {
			menu->removeAction(act);
			menu->insertAction(prevact, act);
		}
	}
	if (!act) return;
	bool visible = !(m.value(2,"visible")=="hidden");
	if (modifyMenuContentsFirstCall && !newlyCreated && visible && act->text() == m.first() && act->data() == m.at(1))
		manipulatedMenus.remove(act->objectName());
	act->setText(m.first());
	act->setData(m.at(1));
	act->setVisible(visible);
	if (!m.value(4).isEmpty()) {
		if (!act->property("originalSlot").isValid())
			act->setProperty("originalSlot", prettySlotName(act));
		connectExtendedSlot(act, m.value(4));
	} else if (act->property("originalSlot").isValid())
		connectExtendedSlot(act, act->property("originalSlot").toString());
	
}

void ConfigManager::modifyManagedShortcuts(){
	//modify shortcuts
	for (int i=0; i< managedMenuNewShortcuts.size(); i++) {
		QString id=managedMenuNewShortcuts[i].first;
		int num=-1;
		if (managedMenuNewShortcuts[i].first.endsWith("~0")) num=0;
		else if (managedMenuNewShortcuts[i].first.endsWith("~1")) num=1;
		else { } //backward compatibility
		if (num!=-1) id.chop(2);
		QAction * act= getManagedAction(id);
		if (act) {
			if (num!=1 || act->shortcuts().empty()) act->setShortcut(QKeySequence(managedMenuNewShortcuts[i].second));
			else act->setShortcuts((QList<QKeySequence>()<<act->shortcut())<<managedMenuNewShortcuts[i].second);
		}
	}
}
void ConfigManager::loadManagedMenu(QMenu* parent,const QDomElement &f) {
	QMenu *menu = newManagedMenu(parent,f.attributes().namedItem("id").nodeValue(),tr(qPrintable(f.attributes().namedItem("text").nodeValue())));
	QDomNodeList children = f.childNodes();
	for (int i = 0; i < children.count(); i++) {
		QDomElement c = children.at(i).toElement();
		if (c.nodeName()=="menu") loadManagedMenu(menu,c);
		else if (c.nodeName()=="insert" || c.nodeName()=="action") {
			QDomNamedNodeMap  att=c.attributes();
			QByteArray ba;
			const char* slotfunc;
			if (c.nodeName()=="insert") slotfunc=SLOT(InsertFromAction());
			else {
				ba=att.namedItem("slot").nodeValue().toLocal8Bit();
				slotfunc=ba.data();
			}
			QAction * act=newManagedAction(menu,
			                               att.namedItem("id").nodeValue(),
			                               tr(qPrintable(att.namedItem("text").nodeValue())),slotfunc,
			                               QList<QKeySequence>()<<  QKeySequence(att.namedItem("shortcut").nodeValue()),
			                               att.namedItem("icon").nodeValue());
			act->setWhatsThis(att.namedItem("info").nodeValue());
			act->setData(att.namedItem("insert").nodeValue());
		} else if (c.nodeName()=="separator") menu->addSeparator();
	}
}
void ConfigManager::loadManagedMenus(const QString &f) {
	QFile settings(f);
	
	if (settings.open(QFile::ReadOnly | QFile::Text)) {
		QDomDocument doc;
		doc.setContent(&settings);
		
		QDomNodeList f = doc.documentElement().childNodes();
		
		for (int i = 0; i < f.count(); i++)
			if (f.at(i).nodeName()=="menu")
				loadManagedMenu(0,f.at(i).toElement());
	}
}

void ConfigManager::managedMenuToTreeWidget(QTreeWidgetItem* parent, QMenu* menu) {
	if (!menu) return;
	QTreeWidgetItem* menuitem= new QTreeWidgetItem(parent, QStringList(menu->title().replace("&","")));
	if (menu->objectName().count("/")<=2) menuitem->setExpanded(true);
	QList<QAction *> acts=menu->actions();
	for (int i=0; i<acts.size(); i++)
		if (acts[i]->menu()) managedMenuToTreeWidget(menuitem, acts[i]->menu());
		else {
			QTreeWidgetItem* twi=new QTreeWidgetItem(menuitem, QStringList() << acts[i]->text().replace("&","")
			                                         << managedMenuShortcuts.value(acts[i]->objectName()+"0", QKeySequence())
			                                         << acts[i]->shortcut().toString(QKeySequence::NativeText));
			twi->setIcon(0,acts[i]->icon());
			if (!acts[i]->isSeparator()) twi->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled);
			twi->setData(0,Qt::UserRole,acts[i]->objectName());
			if (acts[i]->shortcuts().size()>1) twi->setText(3,acts[i]->shortcuts()[1].toString(QKeySequence::NativeText));
		}
}
void ConfigManager::treeWidgetToManagedMenuTo(QTreeWidgetItem* item) {
	if (item->childCount() > 0) {
		for (int i=0; i< item->childCount(); i++)
			treeWidgetToManagedMenuTo(item->child(i));
	} else {
		QString id=item->data(0,Qt::UserRole).toString();
		if (id=="") return;
		QAction * act=getManagedAction(id);
		if (act) {
			QString mseq=item->text(2);
			if(mseq==tr("<none>")) mseq="";
			if(mseq==tr("<default>")) mseq=managedMenuShortcuts.value(act->objectName()+"0",QKeySequence()).toString(QKeySequence::NativeText);
			QKeySequence sc=QKeySequence(mseq);
			act->setShortcuts(QList<QKeySequence>()<<sc);
			if (sc!=managedMenuShortcuts.value(act->objectName()+"0",QKeySequence()))
				managedMenuNewShortcuts.append(QPair<QString, QString> (id+"~0", sc.toString(QKeySequence ::PortableText)));
			mseq=item->text(3);
			if(mseq==tr("<none>")) mseq="";
			if(mseq==tr("<default>")) mseq=managedMenuShortcuts.value(act->objectName()+"1",QKeySequence()).toString(QKeySequence::NativeText);
			sc=QKeySequence(mseq);
			if (mseq!="") {
				if (act->shortcuts().empty()) act->setShortcut(sc);
				else act->setShortcuts((QList<QKeySequence>()<<act->shortcut()) << sc);
			}
			if (sc!=managedMenuShortcuts.value(act->objectName()+"1",QKeySequence()))
				managedMenuNewShortcuts.append(QPair<QString, QString> (id+"~1", sc.toString(QKeySequence ::PortableText)));
			if(id=="main/view/outputview"){  // special handling for outputview because of "esc"-key
				if((item->text(2).toUpper()=="ESC"||item->text(2).isEmpty())) act->setShortcutContext(Qt::WidgetShortcut);
				else act->setShortcutContext(Qt::WindowShortcut);
			}
		}
	}
	
}
void ConfigManager::loadTranslations(QString locale){
	if (locale=="") {
		locale = QString(QLocale::system().name()).left(2);
		if (locale.length() < 2) locale = "en";
	}
	QString txsTranslationFile=findResourceFile("texstudio_"+locale+".qm");
	if (txsTranslationFile == "")
		txsTranslationFile=findResourceFile("texmakerx_"+locale+".qm");
	//if (txsTranslationFile!="") {
	appTranslator->load(txsTranslationFile);
	basicTranslator->load(findResourceFile("qt_"+locale+".qm"));
	//}
}

void ConfigManager::setInterfaceStyle(){
	//style is controlled by the properties interfaceStyle, modernStyle and useTexmakerPalette
	//default values are read from systemPalette and defaultStyleName
	
	QString newStyle=interfaceStyle!=""?interfaceStyle:defaultStyleName;
#if QT_VERSION >= 0x040500
	if (modernStyle) {
		ManhattanStyle* style=new ManhattanStyle(newStyle);
		if (style->isValid()) QApplication::setStyle(style);
	} else 
#endif
		QApplication::setStyle(newStyle);
	QPalette pal = systemPalette;
	if (useTexmakerPalette){ //modify palette like texmaker does it
		pal.setColor(QPalette::Active, QPalette::Highlight, QColor("#4490d8"));
		pal.setColor(QPalette::Inactive, QPalette::Highlight, QColor("#4490d8"));
		pal.setColor(QPalette::Disabled, QPalette::Highlight, QColor("#4490d8"));
		
		pal.setColor(QPalette::Active, QPalette::HighlightedText, QColor("#ffffff"));
		pal.setColor(QPalette::Inactive, QPalette::HighlightedText, QColor("#ffffff"));
		pal.setColor(QPalette::Disabled, QPalette::HighlightedText, QColor("#ffffff"));
		
		pal.setColor(QPalette::Active, QPalette::Base, QColor("#ffffff"));
		pal.setColor(QPalette::Inactive, QPalette::Base, QColor("#ffffff"));
		pal.setColor(QPalette::Disabled, QPalette::Base, QColor("#ffffff"));
		
		pal.setColor(QPalette::Active, QPalette::WindowText, QColor("#000000"));
		pal.setColor(QPalette::Inactive, QPalette::WindowText, QColor("#000000"));
		pal.setColor(QPalette::Disabled, QPalette::WindowText, QColor("#000000"));
		
		pal.setColor( QPalette::Active, QPalette::Text, QColor("#000000") );
		pal.setColor( QPalette::Inactive, QPalette::Text, QColor("#000000") );
		pal.setColor( QPalette::Disabled, QPalette::Text, QColor("#000000") );
		
		pal.setColor(QPalette::Active, QPalette::ButtonText, QColor("#000000"));
		pal.setColor(QPalette::Inactive, QPalette::ButtonText, QColor("#000000"));
		pal.setColor(QPalette::Disabled, QPalette::ButtonText, QColor("#000000"));
		
		pal.setColor( QPalette::ToolTipText, QColor("#000000") );
		
		pal.setColor( QPalette::ToolTipBase, QColor("#FFFFDC") );
		
		if (x11desktop_env() ==4) {
			pal.setColor(QPalette::Active, QPalette::Window, QColor("#eae9e9"));
			pal.setColor(QPalette::Inactive, QPalette::Window, QColor("#eae9e9"));
			pal.setColor(QPalette::Disabled, QPalette::Window, QColor("#eae9e9"));
			
			pal.setColor(QPalette::Active, QPalette::Button, QColor("#eae9e9"));
			pal.setColor(QPalette::Inactive, QPalette::Button, QColor("#eae9e9"));
			pal.setColor(QPalette::Disabled, QPalette::Button, QColor("#eae9e9"));
		} else {
			/*pal.setColor(QPalette::Active, QPalette::Window, QColor("#fbf8f1"));
   pal.setColor(QPalette::Inactive, QPalette::Window, QColor("#fbf8f1"));
   pal.setColor(QPalette::Disabled, QPalette::Window, QColor("#fbf8f1"));
   
   pal.setColor(QPalette::Active, QPalette::Button, QColor("#fbf8f1"));
   pal.setColor(QPalette::Inactive, QPalette::Button, QColor("#fbf8f1"));
   pal.setColor(QPalette::Disabled, QPalette::Button, QColor("#fbf8f1"));*/
			pal.setColor( QPalette::Active, QPalette::Window, QColor("#f6f3eb") );
			pal.setColor( QPalette::Inactive, QPalette::Window, QColor("#f6f3eb") );
			pal.setColor( QPalette::Disabled, QPalette::Window, QColor("#f6f3eb") );
			
			pal.setColor( QPalette::Active, QPalette::Button, QColor("#f6f3eb") );
			pal.setColor( QPalette::Inactive, QPalette::Button, QColor("#f6f3eb") );
			pal.setColor( QPalette::Disabled, QPalette::Button, QColor("#f6f3eb") );
			
		}
	}
	QApplication::setPalette(pal);
}

void ConfigManager::addCommandRow(QGridLayout* gl, const CommandInfo& cmd, int row){
	static QStringList simpleMetaOptions = QStringList() << "quick" << "compile" << "view" << "view-pdf" << "bibliography";
	QWidget * parent = gl->parentWidget();
	QWidget *l;
	if (cmd.user) l = new QLineEdit(cmd.id+":"+cmd.displayName, parent);
	else {
		l = new QLabel(cmd.displayName, parent);
		l->setToolTip("ID: txs:///"+cmd.id);
	}
	QWidget* w;
	if (cmd.metaSuggestionList.isEmpty()) {
		w = new QLineEdit(cmd.getPrettyCommand(), parent);
		if (cmd.id == "pdflatex") pdflatexEdit = qobject_cast<QLineEdit*>(w);
	} else {
		w = new QComboBox(parent);
        w->setObjectName(cmd.id);
        if(!configShowAdvancedOptions && simpleMetaOptions.contains(cmd.id) && cmd.metaSuggestionList.contains(cmd.getPrettyCommand())){
            static_cast<QComboBox*>(w)->addItems(cmd.simpleDescriptionList);
            static_cast<QComboBox*>(w)->setEditable(false);
            int i=cmd.metaSuggestionList.indexOf(cmd.getPrettyCommand());
            Q_ASSERT(i>=0);
            static_cast<QComboBox*>(w)->setEditText(cmd.simpleDescriptionList.value(i,tr("<unknown>")));
        }else{
            static_cast<QComboBox*>(w)->addItems(cmd.metaSuggestionList);
            static_cast<QComboBox*>(w)->setEditable(true);
            static_cast<QComboBox*>(w)->setEditText(cmd.getPrettyCommand());
        }

		int index = cmd.metaSuggestionList.indexOf(cmd.commandLine);
		if (index > 0) static_cast<QComboBox*>(w)->setCurrentIndex(index);		
	}
	QList<QPushButton*> buttons;
    if (cmd.user || cmd.meta) {
		buttons << new QPushButton("...", parent);
		connect(buttons.last(),SIGNAL(clicked()),SLOT(editCommand()));
	}
	buttons << new QPushButton(getRealIcon("fileopen"), "", parent);
	connect(buttons.last(),SIGNAL(clicked()),SLOT(browseCommand()));
	if (!cmd.user && cmd.metaSuggestionList.isEmpty()) {
		buttons << new QPushButton(getRealIcon("undo"), "", parent);
		connect(buttons.last(),SIGNAL(clicked()),SLOT(undoCommand()));
	}
	if (cmd.user) {
		buttons << new QPushButton(getRealIcon("list-remove"), "", parent);
		connect(buttons.last(),SIGNAL(clicked()),SLOT(removeCommand()));
		buttons << new QPushButton(getRealIcon("up"), "", parent);
		connect(buttons.last(),SIGNAL(clicked()),SLOT(moveUpCommand()));
		if (row == 0) buttons.last()->setEnabled(false);
		buttons << new QPushButton(getRealIcon("down"), "", parent);
		connect(buttons.last(),SIGNAL(clicked()),SLOT(moveDownCommand()));
	}
    bool advanced = cmd.meta && !simpleMetaOptions.contains(cmd.id);
	QList<QWidget*> temp; temp << l << w; foreach (QWidget* w, buttons) temp << w;
	foreach (QWidget* x, temp) {
		x->setMinimumHeight(x->sizeHint().height());
		if (x != w) x->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
		advanced |= (cmd.user && buttons.indexOf(static_cast<QPushButton*>(x)) >= 3);
		x->setProperty("advancedOption", advanced);
		if (advanced && !configShowAdvancedOptions) x->setVisible(false);
	}
	w->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
	gl->setRowStretch(row, 1);
	gl->addWidget(l, row,0);
	int off =  0;
	/*if (cmd == BuildManager::CMD_VIEWPDF) {
		QButtonGroup *bgPDFViewer = new QButtonGroup(confDlg);
		confDlg->checkboxInternalPDFViewer = new QRadioButton(confDlg);
		confDlg->checkboxInternalPDFViewer->setObjectName("internal");
		confDlg->checkboxInternalPDFViewer->setText(tr("Internal"));
		confDlg->checkboxInternalPDFViewer->setChecked(buildManager->getLatexCommand(cmd).startsWith(BuildManager::TXS_INTERNAL_PDF_VIEWER));
		connect(confDlg->checkboxInternalPDFViewer,SIGNAL(toggled(bool)),this,SLOT(activateInternalViewer(bool)));
		QRadioButton *rbExternalPDFViewer = new QRadioButton("External:", confDlg);
		rbExternalPDFViewer->setChecked(!confDlg->checkboxInternalPDFViewer->isChecked());
		bgPDFViewer->addButton(confDlg->checkboxInternalPDFViewer);
		bgPDFViewer->addButton(rbExternalPDFViewer);
		gl->addWidget(confDlg->checkboxInternalPDFViewer, (int)cmd, 1);
		gl->addWidget(rbExternalPDFViewer, (int)cmd, 2);
		off+=2;
	}*/
	gl->addWidget(w,row,1+off,1,6-off-buttons.size());
	for (int i = 0; i < buttons.size(); i++){
		gl->addWidget(buttons[i],row,7-buttons.size()+i, 1, 1);
		buttons[i]->setProperty(PROPERTY_ASSOCIATED_INPUT, QVariant::fromValue<QWidget*>(w));
	}
	w->setProperty(PROPERTY_COMMAND_NAME, cmd.id);
	
	if (cmd.user) {
		userCommandInputs << w;
		userCommandNameInputs << l;
	} else commandInputs << w;
}

void ConfigManager::createCommandList(QGroupBox* box, const QStringList& order, bool user, bool meta){
	QVBoxLayout *verticalLayout = new QVBoxLayout(box);
	QScrollArea *scrollAreaCommands = new QScrollArea(box);
	scrollAreaCommands->setWidgetResizable(true);
	QWidget *scrollAreaWidgetContents = new QWidget();
	QGridLayout* gl=new QGridLayout(scrollAreaWidgetContents);
	int row = 0;
	foreach (const QString& id, order){
		const CommandInfo& cmd = tempCommands.value(id);
        //bool isMeta = !cmd.metaSuggestionList.isEmpty();
        bool isMeta = cmd.meta;
		if (user != cmd.user) continue;
		if (!user && (isMeta != meta)) continue;
		addCommandRow(gl, cmd, row);

		row++;
	}
	if (user){
		QPushButton* b = new QPushButton(getRealIcon("list-add"), tr("Add"), box);
		connect(b, SIGNAL(clicked()), SLOT(addCommand()));
		gl->addWidget(b, row, 0);
		userGridLayout = gl;
		setLastRowMoveDownEnable(false);
	}
	scrollAreaCommands->setWidget(scrollAreaWidgetContents);
	verticalLayout->addWidget(scrollAreaCommands);
}

void ConfigManager::setFirstRowMoveUpEnable(bool enable){
	REQUIRE(userGridLayout);
	int rows = userGridLayout->rowCount();
	for (int i=0; i < rows-1;i++) {
		QLayoutItem* li = userGridLayout->itemAtPosition(i, 5);
		if (li && li->widget()) { li->widget()->setEnabled(enable); break; }
	}
}

void ConfigManager::setLastRowMoveDownEnable(bool enable){
	REQUIRE(userGridLayout);
	int rows = userGridLayout->rowCount();
	for (int i=rows-2; i >= 0; i--) {
		QLayoutItem* li = userGridLayout->itemAtPosition(i, 6);
		if (li && li->widget()) { li->widget()->setEnabled(enable); break; }
	}
}

void ConfigManager::browseCommand(){
	QPushButton *pb = qobject_cast<QPushButton*> (sender());
	REQUIRE(pb);
	QWidget *w = pb->property(PROPERTY_ASSOCIATED_INPUT).value<QWidget*>();
	REQUIRE(w);
	QString cmd = w->property(PROPERTY_COMMAND_NAME).toString();
	QString old = getText(w);
	QString path = old;
	if (old.contains("|")) {
		path = old.split("|").last().trimmed();
		if (path.isEmpty()) path = old.split("|").first().trimmed();
	}
	path = path.trimmed();
	if (path.contains(' ')) path.truncate(path.indexOf(' '));
	if (!path.contains('/') && !path.contains('\\')) {//no absolute path
		path=BuildManager::findFileInPath(path);
		if (path=="") path=QDir::rootPath(); //command not found, where could it be?
	} else {
		//opendialog doesn't like quotation like "C:\program files\..."
		if (path.startsWith('"')) path=path.remove(0,1);
		if (path.endsWith('"')) path.chop(1);
	}
	QString location=QFileDialog::getOpenFileName(0,tr("Browse program"),path,"Program (*)",0,QFileDialog::DontResolveSymlinks);
	if (!location.isEmpty()) {
		location.replace(QString("\\"),QString("/"));
		location="\""+location+"\" "+ tempCommands.value(cmd).defaultArgs;
		if (old.contains("|")) setText(w, old + (old.trimmed().endsWith("|")?"":" | ") + location);
		else setText(w, location);
	}
}
void ConfigManager::undoCommand(){
	QPushButton *pb = qobject_cast<QPushButton*> (sender());
	REQUIRE(pb);
	QWidget *w = pb->property(PROPERTY_ASSOCIATED_INPUT).value<QWidget*>();
	REQUIRE(w);
	QString cmd = w->property(PROPERTY_COMMAND_NAME).toString();
	setText(w, tempCommands.value(cmd).guessCommandLine());
}

void ConfigManager::editCommand(){
	QPushButton *pb = qobject_cast<QPushButton*> (sender());
	REQUIRE(pb);
	QWidget *w = pb->property(PROPERTY_ASSOCIATED_INPUT).value<QWidget*>();
	REQUIRE(w);
	setText(w, buildManager->editCommandList(getText(w), w->property(PROPERTY_COMMAND_NAME).toString()));
}

void ConfigManager::addCommand(){
	QPushButton* self = qobject_cast<QPushButton*>(sender());
	REQUIRE(self); REQUIRE(userGridLayout);
	CommandInfo cmd;
	cmd.id = QString("user%1").arg(userCommandInputs.size());
	cmd.user = true;
	int row = userGridLayout->rowCount();
	setLastRowMoveDownEnable(true);
	userGridLayout->removeWidget(self);
	addCommandRow(userGridLayout, cmd, row-1);
	userGridLayout->addWidget(self, row+1, 0);
	setLastRowMoveDownEnable(false);
}

void ConfigManager::removeCommand(){
	QPushButton* self = qobject_cast<QPushButton*>(sender()); REQUIRE(self); REQUIRE(userGridLayout);
	QWidget* w = self->property(PROPERTY_ASSOCIATED_INPUT).value<QWidget*>(); REQUIRE(w);
	int pos = userCommandInputs.indexOf(w); REQUIRE(pos >= 0);
	int widgetId = userGridLayout->indexOf(self) - 2; 
	for (int i=0;i<5;i++) {
		QLayoutItem* li = userGridLayout->takeAt(widgetId);
		REQUIRE(li);
		delete li->widget();
	}
	delete userCommandInputs[pos]; //layout item memory leak??
	delete userCommandNameInputs[pos];
	userCommandInputs.removeAt(pos);
	userCommandNameInputs.removeAt(pos);
	setLastRowMoveDownEnable(false);
	setFirstRowMoveUpEnable(false);
}

void ConfigManager::moveUpCommand(){ moveCommand(-1); }
void ConfigManager::moveDownCommand(){ moveCommand(+1); }
void ConfigManager::moveCommand(int dir){
	QPushButton* self = qobject_cast<QPushButton*>(sender()); REQUIRE(self); REQUIRE(userGridLayout);
	QWidget* w = self->property(PROPERTY_ASSOCIATED_INPUT).value<QWidget*>(); REQUIRE(w);
	int pos = userCommandInputs.indexOf(w); REQUIRE(pos >= 0);
	int rowpos, column, temp;
	userGridLayout->getItemPosition(userGridLayout->indexOf(self), &rowpos, &column, &temp, &temp ); REQUIRE(rowpos >= 0);
	int rows = userGridLayout->rowCount();
	QWidget* w2 = 0, *wsel = 0;
	for (rowpos+=dir; rowpos >= 0 && rowpos < rows; rowpos+=dir) {
		QLayoutItem* li = userGridLayout->itemAtPosition(rowpos, 1);
		QLayoutItem* lis = userGridLayout->itemAtPosition(rowpos, column);
		if (li && li->widget() && lis && lis->widget()) { 
			w2 = li->widget();
			wsel = lis->widget();
			break;
		}
	}
	if (!w2) return;
	int pos2 = userCommandInputs.indexOf(w2);  REQUIRE(pos2 >= 0); 
	REQUIRE(userCommandInputs.size() == userCommandNameInputs.size());
	QString mixedId = getText(userCommandNameInputs[pos]);
	setText(userCommandNameInputs[pos], getText(userCommandNameInputs[pos2]));
	setText(userCommandNameInputs[pos2], mixedId);
	QString cmd = getText(w);
	setText(w, getText(w2));
	setText(w2, cmd);
	QVariant id = w->property(PROPERTY_COMMAND_NAME);
	w->setProperty(PROPERTY_COMMAND_NAME, w2->property(PROPERTY_COMMAND_NAME));
	w2->setProperty(PROPERTY_COMMAND_NAME, id);
	wsel->setFocus();
}

// manipulate latex menus
QTreeWidgetItem* ConfigManager::managedLatexMenuToTreeWidget(QTreeWidgetItem* parent, QMenu* menu) {
	if (!menu) return 0;
	static QStringList relevantMenus = QStringList() << "main/tools" << "main/latex" << "main/math";
	bool advanced = false;
	if (parent) advanced = parent->data(0, Qt::UserRole+2).toBool();
	if (!parent && !relevantMenus.contains(menu->objectName())) advanced = true;
	QTreeWidgetItem* menuitem= new QTreeWidgetItem(parent, QStringList(menu->title()));
	if (advanced) { superAdvancedItems << menuitem; menuitem->setData(0,Qt::UserRole+2, true); }
	menuitem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
	menuitem->setCheckState(0, menu->menuAction() && menu->menuAction()->isVisible() ? Qt::Checked : Qt::Unchecked);
	if (menu->objectName().count("/")<=2) menuitem->setExpanded(true);
	QList<QAction *> acts=menu->actions();
	for (int i=0; i<acts.size(); i++){
		bool subAdvanced = advanced;
		QTreeWidgetItem* twi = 0;
		if (acts[i]->menu()) twi = managedLatexMenuToTreeWidget(menuitem, acts[i]->menu());
		else {
			subAdvanced |= !acts[i]->data().isValid();
			twi=new QTreeWidgetItem(menuitem, QStringList() << QString(acts[i]->text()) << acts[i]->data().toString() << prettySlotName(acts[i]));
			twi->setIcon(0,acts[i]->icon());
			if (!acts[i]->isSeparator()) {
				twi->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
				twi->setCheckState(0,acts[i]->isVisible() ? Qt::Checked : Qt::Unchecked);
			}
			twi->setData(2, Qt::UserRole, acts[i]->property("originalSlot").isValid()?acts[i]->property("originalSlot").toString():twi->text(2));
			if (manipulatedMenus.contains(acts[i]->objectName())) {
				QFont bold = twi->font(0);
				bold.setBold(true);
				for (int j=0;j<3;j++) twi->setFont(j, bold);
			}			
		}
		if (!twi) continue;
		QString id = acts[i]->menu()?(acts[i]->menu()->objectName() + "/"): acts[i]->objectName();
		twi->setData(0,Qt::UserRole,id);
		twi->setData(0,Qt::UserRole+2,subAdvanced);
		manipulatedMenuTree.insert(id, twi);
		if (subAdvanced) superAdvancedItems << twi;
		
		int j = i+1;
		for (; j < acts.size() && acts[j]->isSeparator(); j++) ;
		if (j < acts.size()) twi->setData(0,Qt::UserRole+1,acts[j]->menu() ? acts[j]->menu()->objectName(): acts[j]->objectName());
		else twi->setData(0,Qt::UserRole+1, menu->objectName() + "/");
	}
	if (acts.isEmpty()) {
		QTreeWidgetItem* filler=new QTreeWidgetItem(menuitem, QStringList() << QString("temporary menu end") << "");
		filler->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		filler->setData(0,Qt::UserRole, menu->objectName()+"/!!end");
	}
	return menuitem;
}

void ConfigManager::latexTreeItemChanged(QTreeWidgetItem* item,int ){
	if((item->flags() & Qt::ItemIsEditable) && !changedItemsList.contains(item)) {
		QFont f = item->font(0);
		f.setBold(true);
		for (int i=0;i<3;i++) item->setFont(i, f);
		changedItemsList.append(item);
	}
}
void ConfigManager::latexTreeNewItem(bool menu){
	QAction* a = qobject_cast<QAction*>(sender());
	REQUIRE(a);
	QTreeWidget* tw = qobject_cast<QTreeWidget*>(a->parentWidget());
	REQUIRE(tw);
	QTreeWidgetItem * old = tw->currentItem();
	//qDebug() << old->data(0, Qt::UserRole) << old->data(0, Qt::DisplayRole);
	REQUIRE(old);
	if (!old->parent()) return;
	QTreeWidgetItem* twi=new QTreeWidgetItem(QStringList() << QString("new item") << "");
	twi->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
	twi->setCheckState(0, Qt::Checked);
	static int ID = 0;
	QString oldID = old->data(0,Qt::UserRole).toString(), append = (menu?"/":"");
	if (oldID.endsWith("/")) oldID.chop(1);
	for (ID=0;ID<100000 && manipulatedMenuTree.contains(oldID+"_UII"+QString::number(ID)+append); ID++) ;
	QString newId = oldID + "_UII"+QString::number(ID)+append;
	twi->setData(0,Qt::UserRole, newId);
	twi->setData(0,Qt::UserRole+1, old->data(0,Qt::UserRole).toString());
	old->parent()->insertChild(old->parent()->indexOfChild(old), twi);
	manipulatedMenuTree.insert(newId, twi);
	latexTreeItemChanged(twi, 0);
	if (menu) {
		QTreeWidgetItem* filler=new QTreeWidgetItem(twi, QStringList() << QString("temporary menu end") << "");
		filler->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		filler->setData(0,Qt::UserRole, newId + "!!end");
	}
}
void ConfigManager::latexTreeNewMenuItem(){
	latexTreeNewItem(true);
}

void ConfigManager::toggleVisibleTreeItems(bool show){
	REQUIRE(!superAdvancedItems.isEmpty());
	foreach (QTreeWidgetItem* twi, superAdvancedItems)
		twi->setHidden(!show);
	QTreeWidget* tw = superAdvancedItems.first()->treeWidget();
	tw->setColumnHidden(2, !show);
	if (show && tw->columnWidth(0) + tw->columnWidth(1) + tw->columnWidth(2) > tw->width() + 50) 
		tw->setColumnWidth(1, tw->width() - tw->columnWidth(0) - tw->columnWidth(2));
}

void ConfigManager::treeWidgetToManagedLatexMenuTo() {
	foreach(QTreeWidgetItem* item,changedItemsList){
		QString id=item->data(0,Qt::UserRole).toString();
		if (id=="") continue;
		QStringList m;
		m << item->text(0) 
		  << item->text(1) 
		  << (item->checkState(0)==Qt::Checked?"visible":"hidden")
		  << item->data(0, Qt::UserRole+1).toString()
		  << ((item->text(2) != item->data(2, Qt::UserRole).toString())?item->text(2):"");
		manipulatedMenus.insert(id, m);
	}
	modifyMenuContents();	
}


void ConfigManager::registerOption(const QString& name, void* storage, PropertyType type, QVariant def, void* displayWidgetOffset){
	//#ifndef QT_NO_DEBUG
	//TODO: optimize
	for (int i=0;i<managedProperties.size();i++)
		if (managedProperties[i].name == name){
			if (managedProperties[i].storage == storage)
				return;
			qDebug() << "Duplicate option name" << name;
			Q_ASSERT(false);
		}
	//#endif
	ManagedProperty temp;
	temp.name = name;
	temp.storage = storage;
	temp.type = type;
	temp.def = def;
	temp.widgetOffset = (ptrdiff_t)displayWidgetOffset;
	managedProperties << temp;
	
	if (persistentConfig){
		persistentConfig->beginGroup("texmaker");
		temp.valueFromQVariant(persistentConfig->value(temp.name, temp.def));
		persistentConfig->endGroup();
	}
}

void ConfigManager::registerOption(const QString& name, void* storage, PropertyType type, QVariant def){
	registerOption(name, storage, type, def, 0);
}

#define REGISTER_OPTION(TYPE, ID) \
	void ConfigManager::registerOption(const QString& name, TYPE* storage, QVariant def,  void* displayWidgetOffset){ \
		registerOption(name, storage, ID, def, displayWidgetOffset); \
	} \
	void ConfigManager::registerOption(const QString& name, TYPE* storage, QVariant def){ \
		registerOption(name, storage, ID, def, 0); \
	}
PROPERTY_TYPE_FOREACH_MACRO(REGISTER_OPTION)
#undef REGISTER_OPTION


void ConfigManager::setOption(const QString& name, const QVariant& value){
	REQUIRE(persistentConfig);
	QString rname = name.startsWith("/") ? name.mid(1) : ("texmaker/"+name);
    ManagedProperty* option = 0;
	if (rname.startsWith("texmaker/") && ((option = getManagedProperty(rname.mid(9))))){
		option->valueFromQVariant(value);
		return;
	}
	persistentConfig->setValue(rname,value);
}
QVariant ConfigManager::getOption(const QString& name) const{
	REQUIRE_RET(persistentConfig,QVariant());
	QString rname = name.startsWith("/") ? name.mid(1) : ("texmaker/"+name);
    const ManagedProperty* option = 0;
	if (rname.startsWith("texmaker/") && (option = getManagedProperty(rname.mid(9))))
		return option->valueToQVariant();
	return persistentConfig->value(rname);
}

bool ConfigManager::existsOption(const QString& name) const{
	REQUIRE_RET(persistentConfig,false);
	QString rname = name.startsWith("/") ? name.mid(1) : ("texmaker/"+name);
	return persistentConfig->contains(rname);
}
void ConfigManager::linkOptionToDialogWidget(const void* optionStorage, QWidget* widget){
	ManagedProperty *property = getManagedProperty(optionStorage);
	REQUIRE(property);
	
	QWidget* parentWidget = widget->parentWidget();
	while (parentWidget && !qobject_cast<QDialog*>(parentWidget)) parentWidget = parentWidget->parentWidget();
	Q_ASSERT(parentWidget);
	QDialog* parentDialog = qobject_cast<QDialog*>(parentWidget);
	Q_ASSERT(parentDialog);
	
	if (managedOptionDialogs.contains(parentDialog)) {
		(*managedOptionDialogs.find(parentDialog)) << widget;
	} else {
		managedOptionDialogs.insert(parentDialog, QList<QWidget*>() << widget);
		connect(parentDialog, SIGNAL(accepted()), SLOT(managedOptionDialogAccepted()));
	}
	
	property->writeToObject(widget);
	widget->setProperty("managedProperty", QVariant::fromValue<void*>(property->storage));
}

void ConfigManager::linkOptionToObject(const void* optionStorage, QObject* object, LinkOptions options){
	ManagedProperty *property = getManagedProperty(optionStorage);
	REQUIRE(property);
	REQUIRE((options & LO_DIRECT_OVERRIDE) || property->type == PT_BOOL);
	if (managedOptionObjects.contains(property)) {
		Q_ASSERT(managedOptionObjects[property].first == options);
		managedOptionObjects[property].second << object;
	} else {
		managedOptionObjects.insert(property, QPair<LinkOptions, QList<QObject*> >(options, QList<QObject*>() << object));
	}
	property->writeToObject(object);
	object->setProperty("managedProperty", QVariant::fromValue<ManagedProperty*>(property));
	connect(object,SIGNAL(destroyed(QObject*)), SLOT(managedOptionObjectDestroyed(QObject*)));
	if (qobject_cast<QAction*>(object) || qobject_cast<QCheckBox*>(object))
		connect(object, SIGNAL(toggled(bool)), SLOT(managedOptionBoolToggled()));
}
void ConfigManager::updateAllLinkedObjects(const void* optionStorage){
	ManagedProperty *property = getManagedProperty(optionStorage);
	REQUIRE(property);
	updateManagedOptionObjects(property);
}

ManagedProperty* ConfigManager::getManagedProperty(const void* storage){
	for (int i=0;i<managedProperties.size();i++)
		if (managedProperties[i].storage == storage) return &managedProperties[i];
	return 0;
}
ManagedProperty* ConfigManager::getManagedProperty(const QString& name){
	for (int i=0;i<managedProperties.size();i++)
		if (managedProperties[i].name == name) return &managedProperties[i];
	return 0;
}
const ManagedProperty* ConfigManager::getManagedProperty(const QString& name) const{
	for (int i=0;i<managedProperties.size();i++)
		if (managedProperties[i].name == name) return &managedProperties[i];
	return 0;
}

void ConfigManager::getDefaultEncoding(const QByteArray&, QTextCodec*&guess, int &sure){
	if (sure >= 100) return;
	if (!newFileEncoding) return;
	//guess is utf-8 or latin1, no latex encoding definition detected
	if (guess && guess->mibEnum() == MIB_UTF8) return; //trust utf8 detection
	//guess is latin1, no latex encoding definition detected
	if (sure == 0) {
		//ascii file
		if (newFileEncoding->mibEnum() == MIB_UTF16BE || newFileEncoding->mibEnum() == MIB_UTF16LE) {
			guess = QTextCodec::codecForMib(MIB_UTF8);
			return;
		}
		guess = newFileEncoding;
		return;
	} else {
		//file containing invalid utf-8 characters
		if (newFileEncoding->mibEnum() == MIB_UTF16BE || newFileEncoding->mibEnum() == MIB_UTF16LE || newFileEncoding->mibEnum() == MIB_UTF8) {
			guess = QTextCodec::codecForMib(MIB_LATIN1);
			return;
		}
		guess = newFileEncoding;
		return;
	}
}

void ConfigManager::managedOptionDialogAccepted(){
	QDialog* dialog = qobject_cast<QDialog*>(sender());
	REQUIRE(dialog);
	foreach (const QWidget* widget, managedOptionDialogs.value(dialog, QList<QWidget*>())) {
		ManagedProperty* prop = getManagedProperty(widget->property("managedProperty").value<void*>());
		Q_ASSERT(prop);
		prop->readFromObject(widget);
	}
	managedOptionDialogs.remove(dialog);
}

void ConfigManager::managedOptionObjectDestroyed(QObject* obj){
	REQUIRE(obj);
	ManagedProperty* property = obj->property("managedProperty").value<ManagedProperty*>();
	REQUIRE(property);
	Q_ASSERT(managedOptionObjects.contains(property));
	Q_ASSERT(managedOptionObjects[property].second.contains(obj));
	managedOptionObjects[property].second.removeAll(obj);
	if (managedOptionObjects[property].second.isEmpty())
		managedOptionObjects.remove(property);
}

int isChecked(const QObject* obj){
	const QAction* act = qobject_cast<const QAction*>(obj);
	if (act) return (act->isChecked()?1:-1);
	const QCheckBox* cb = qobject_cast<const QCheckBox*>(obj);
	if (cb) return (cb->isChecked()?1:-1);
	return 0;
}

void ConfigManager::managedOptionBoolToggled(){
	int state = isChecked(sender());
	REQUIRE(state);
	ManagedProperty* property = sender()->property("managedProperty").value<ManagedProperty*>();
	REQUIRE(property);
	REQUIRE(property->type==PT_BOOL);
	if ((state > 0) == *(bool*)(property->storage)) return;
	if (managedOptionObjects[property].first & LO_DIRECT_OVERRIDE) {
		//full sync
		*(bool*)property->storage = (state > 0);
	} else {
		//voting
		int totalState=0;
		foreach (const QObject* o, managedOptionObjects[property].second)
			totalState += isChecked(o);
		if (totalState == 0) totalState = state;
		if ((totalState > 0) == *(bool*)(property->storage)) return;
		*(bool*)property->storage = (totalState > 0);
	}
	updateManagedOptionObjects(property);
}

void ConfigManager::updateManagedOptionObjects(ManagedProperty* property){
	if (!(managedOptionObjects[property].first & LO_UPDATE_ALL))
		return;
	foreach (QObject* o, managedOptionObjects[property].second)
		property->writeToObject(o);
}












