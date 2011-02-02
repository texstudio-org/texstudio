
#include "configmanager.h"

#include "configdialog.h"
#include "latexeditorview.h"
#include "latexcompleter_config.h"
#include "latexeditorview_config.h"
#include "webpublishdialog_config.h"
#include "PDFDocument_config.h"
#include "smallUsefulFunctions.h"
#include "codesnippet.h"

#include <QDomElement>

#include "qformatconfig.h"

#include "manhattanstyle.h"
ManagedToolBar::ManagedToolBar(const QString &newName, const QStringList &defs): name(newName), defaults(defs), toolbar(0){}

ManagedProperty::ManagedProperty():storage(0),type(PT_VOID),widgetOffset(0){
}
QVariant ManagedProperty::valueToQVariant() const{
	Q_ASSERT(storage);
	if (!storage) return QVariant();
	switch (type){
		case PT_INT: return QVariant(*((int*)storage));
		case PT_BOOL: return QVariant(*((bool*)storage));
		case PT_STRING: return QVariant(*((QString*)storage));
		case PT_STRINGLIST: return QVariant(*((QStringList*)storage));
		case PT_DATETIME: return QVariant(*((QDateTime*)storage));
		case PT_DOUBLE: return QVariant(*((double*)storage));
		case PT_BYTEARRAY: return QVariant(*((QByteArray*)storage));
		case PT_LIST: return QVariant(*((QList<QVariant>*)storage));
		default:
			Q_ASSERT(false);
			return QVariant();
	}
}
void ManagedProperty::valueFromQVariant(const QVariant v){
	Q_ASSERT(storage);
	if (!storage) return;
	switch (type){
		case PT_INT: *((int*)storage) = v.toInt(); break;
		case PT_BOOL: *((bool*)storage) = v.toBool(); break;
		case PT_STRING: *((QString*)storage) = v.toString(); break;
		case PT_STRINGLIST: *((QStringList*)storage) = v.toStringList(); break;
		case PT_DATETIME: *((QDateTime*)storage) = v.toDateTime(); break;
		case PT_DOUBLE: *((double*)storage) = v.toDouble(); break;
		case PT_BYTEARRAY: *((QByteArray*)storage) = v.toByteArray(); break;
		case PT_LIST: *((QList<QVariant>*)storage) = v.toList(); break;
		default:
			Q_ASSERT(false);
	}
}

void ManagedProperty::writeToWidget(QWidget* w) const{
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
			case PT_STRINGLIST:
				Q_ASSERT(false);//TODO
				return;
			default:
				Q_ASSERT(false);
		}
	}
	QDoubleSpinBox* doubleSpinBox = qobject_cast<QDoubleSpinBox*>(w);
	if (doubleSpinBox){
		Q_ASSERT(type == PT_DOUBLE);
		doubleSpinBox->setValue(*((double*)storage));
		return;
	}

	Q_ASSERT(false);
}
bool ManagedProperty::readFromWidget(const QWidget* w){
	Q_ASSERT(storage);
	if (!storage) return false;

	const QCheckBox* checkBox = qobject_cast<const QCheckBox*>(w);
	if (checkBox) {
		Q_ASSERT(type == PT_BOOL);
		bool oldvalue = *((bool*)storage);
		*((bool*)storage) = checkBox->isChecked();
		return oldvalue != *((bool*)storage);
	}
	const QLineEdit* edit = qobject_cast<const QLineEdit*>(w);
	if (edit){
		Q_ASSERT(type == PT_STRING);
		QString oldvalue = *((QString*)storage);
		*((QString*)storage) = edit->text();
		return oldvalue == *((QString*)storage);
	}
	/*QTextEdit* tedit = qobject_cast<QTextEdit*>(w);
	if (tedit){
		*((QString*)storage) = tedit->toPlainText();
		continue;
	}*/
	const QSpinBox* spinBox = qobject_cast<const QSpinBox*>(w);
	if (spinBox){
		Q_ASSERT(type == PT_INT);
		int oldvalue = *((int*)storage);
		*((int*)storage) = spinBox->value();
		return oldvalue != *((int*)storage);
	}
	const QComboBox* comboBox = qobject_cast<const QComboBox*>(w);
	if (comboBox){
		switch (type) {
			case PT_BOOL:{
				bool oldvalue = *((bool*)storage);
				*((bool*)storage) = comboBox->currentIndex()!=0;
				return oldvalue != *((bool*)storage);
			}
			case PT_INT:{
				int oldvalue = *((int*)storage);
				*((int*)storage) = comboBox->currentIndex();
				return oldvalue != *((int*)storage);
			}
			case PT_STRING:{
				QString oldvalue = *((QString*)storage);
				*((QString*)storage) = comboBox->currentText();
				return oldvalue != *((QString*)storage);
			}
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
		Q_ASSERT(type == PT_DOUBLE);
		double oldvalue = *((double*)storage);
		*((double*)storage) = doubleSpinBox->value();
		return oldvalue != *((double*)storage);
	}

	Q_ASSERT(false);
	return false;
}


QTextCodec* ConfigManager::newFileEncoding = 0;

ConfigManager::ConfigManager(QObject *parent): QObject (parent),
	buildManager(0),editorConfig(new LatexEditorViewConfig),
	completerConfig (new LatexCompleterConfig),
	webPublishDialogConfig (new WebPublishDialogConfig),
	pdfDocumentConfig(new PDFDocumentConfig),
	menuParent(0), menuParentsBar(0), ltxCommands(0) {

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
	managedToolBars.append(ManagedToolBar("Table", QStringList() << "main/latex/tabularmanipulation/addRow" << "main/latex/tabularmanipulation/addColumn" << "main/latex/tabularmanipulation/pasteColumn" << "main/latex/tabularmanipulation/removeRow" << "main/latex/tabularmanipulation/removeColumn" << "main/latex/tabularmanipulation/cutColumn" ));
	managedToolBars.append(ManagedToolBar("Central", QStringList() << "main/latex/fontstyles/textbf" << "main/latex/fontstyles/textit" << "main/latex/fontstyles/underline" << "main/latex/environment/flushleft" << "main/latex/environment/center" << "main/latex/environment/flushright" << "separator" <<
					      "main/latex/spacing/newline" << "separator" <<
					       "main/math/mathmode" << "main/math/subscript" << "main/math/superscript" << "main/math/frac" << "main/math/dfrac" << "main/math/sqrt"));

	registerOption("ToolBar/CentralVisible", &centralVisible, true);

	enviromentModes << "verbatim" << "numbers";



	Ui::ConfigDialog *pseudoDialog = (Ui::ConfigDialog*) 0;


	//beginRegisterGroup("texmaker");
	//files
	registerOption("Files/New File Encoding", &newFileEncodingName, "utf-8", &pseudoDialog->comboBoxEncoding); //check
	registerOption("Files/Auto Detect Encoding Of Loaded Files", &autodetectLoadedFile, true, &pseudoDialog->checkBoxAutoDetectOnLoad);
	registerOption("Files/Ignore Log File Names", &ignoreLogFileNames, 0, &pseudoDialog->comboBoxIgnoreLogFileNames);
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
	registerOption("Files/Last Document", &lastDocument);
	registerOption("Files/Parse BibTeX", &parseBibTeX, true, &pseudoDialog->checkBoxParseBibTeX);
	registerOption("Files/Parse Master", &parseMaster, true, &pseudoDialog->checkBoxParseMaster);
        registerOption("Files/Autosave", &autosaveEveryMinutes, 0);

	registerOption("Spell/Dic", &spell_dic, "<dic not found>", &pseudoDialog->comboBoxDictionaryFileName); //don't translate it
	registerOption("Thesaurus/Database", &thesaurus_database, "<dic not found>", &pseudoDialog->comboBoxThesaurusFileName);

	//user macros
	registerOption("User/TagNames", &userMacroMenuName, QStringList());
	registerOption("User/Tags", &userMacroTag, QStringList());
	registerOption("User/TagAbbrevs", &userMacroAbbrev, QStringList());
	registerOption("User/ToolNames", &userToolMenuName, QStringList());
	registerOption("User/Tools", &userToolCommand, QStringList());
	registerOption("User/TagAbbrevs", &userMacroAbbrev, QStringList());

	//editor
	registerOption("Editor/WordWrap", &editorConfig->wordwrap, true, &pseudoDialog->checkBoxWordwrap);
	registerOption("Editor/HardWordWrap", &editorConfig->hardwordwrap, false, &pseudoDialog->checkBoxHardWordWrap);
	registerOption("Editor/WrapLineWidth", &editorConfig->lineWidth, 80, &pseudoDialog->spinBoxWrapLineWidth);
	registerOption("Editor/Parentheses Matching", &editorConfig->parenmatch, true); //TODO: checkbox?
	registerOption("Editor/Parentheses Completion", &editorConfig->parenComplete, true, &pseudoDialog->checkBoxAutoCompleteParens);
	registerOption("Editor/Line Number Multiples", &editorConfig->showlinemultiples, -1);
	registerOption("Editor/Auto Indent", &editorConfig->autoindent, true);
	registerOption("Editor/Weak Indent", &editorConfig->weakindent, true);
	registerOption("Editor/Indent with Spaces", &editorConfig->indentWithSpaces, false);
	registerOption("Editor/Folding", &editorConfig->folding, true, &pseudoDialog->checkBoxFolding);
	registerOption("Editor/Show Line State", &editorConfig->showlinestate, true, &pseudoDialog->checkBoxLineState);
	registerOption("Editor/Show Cursor State", &editorConfig->showcursorstate, true, &pseudoDialog->checkBoxState);
	registerOption("Editor/Real-Time Spellchecking", &editorConfig->realtimeChecking, true, &pseudoDialog->checkBoxRealTimeCheck); //named for compatibility reasons with older tmx versions
	registerOption("Editor/Check Spelling", &editorConfig->inlineSpellChecking, true, &pseudoDialog->checkBoxInlineSpellCheck);
	registerOption("Editor/Check Citations", &editorConfig->inlineCitationChecking, true, &pseudoDialog->checkBoxInlineCitationCheck);
	registerOption("Editor/Check References", &editorConfig->inlineReferenceChecking, true, &pseudoDialog->checkBoxInlineReferenceCheck);
	registerOption("Editor/Check Syntax", &editorConfig->inlineSyntaxChecking, true, &pseudoDialog->checkBoxInlineSyntaxCheck);
	registerOption("Editor/Show Whitespace", &editorConfig->showWhitespace, true, &pseudoDialog->checkBoxShowWhitespace);
	registerOption("Editor/TabStop", &editorConfig->tabStop, 4 , &pseudoDialog->sbTabSpace);

	registerOption("Editor/Display Modifytime", &editorConfig->displayModifyTime, true, &pseudoDialog->checkBoxDisplayModifyTime);
	registerOption("Editor/Close Search Replace Together", &editorConfig->closeSearchAndReplace, false, &pseudoDialog->checkBoxCloseSearchReplaceTogether);
	registerOption("Editor/Use Line For Search", &editorConfig->useLineForSearch, true, &pseudoDialog->checkBoxUseLineForSearch);	
	registerOption("Editor/Auto Replace Commands", &CodeSnippet::autoReplaceCommands, true, &pseudoDialog->checkBoxAutoReplaceCommands);

	registerOption("Editor/Font Family", &editorConfig->fontFamily, "", &pseudoDialog->comboBoxFont);
	registerOption("Editor/Font Size", &editorConfig->fontSize, -1, &pseudoDialog->spinBoxSize);
	registerOption("Editor/Esc for closing log", &useEscForClosingLog, false, &pseudoDialog->cb_CloseLogByEsc);

	registerOption("Editor/Esc for closing log", &editorConfig->mouseWheelZoom, true, &pseudoDialog->checkBoxMouseWheelZoom);

	registerOption("Editor/Hack Disable Fixed Pitch", &editorConfig->hackDisableFixedPitch, false, &pseudoDialog->checkBoxHackDisableFixedPitch);
	registerOption("Editor/Hack Disable Width Cache", &editorConfig->hackDisableWidthCache, false, &pseudoDialog->checkBoxHackDisableWidthCache);
	registerOption("Editor/Hack Disable Width Cache", &editorConfig->hackDisableAccentWorkaround, false, &pseudoDialog->checkBoxHackDisableAccentWorkaround);

	//completion
	registerOption("Editor/Completion", &completerConfig->enabled, true, &pseudoDialog->checkBoxCompletion);
	Q_ASSERT(sizeof(int)==sizeof(LatexCompleterConfig::CaseSensitive));
	registerOption("Editor/Completion Case Sensitive", (int*)&completerConfig->caseSensitive, 2);
	registerOption("Editor/Completion Complete Common Prefix", &completerConfig->completeCommonPrefix, true, &pseudoDialog->checkBoxCompletePrefix);
	registerOption("Editor/Completion EOW Completes", &completerConfig->eowCompletes, true, &pseudoDialog->checkBoxEOWCompletes);
	registerOption("Editor/Completion Enable Tooltip Help", &completerConfig->tooltipHelp, true, &pseudoDialog->checkBoxToolTipHelp);
	registerOption("Editor/Completion Use Placeholders", &completerConfig->usePlaceholders, true, &pseudoDialog->checkBoxUsePlaceholders);

	//other dialogs
	registerOption("Dialogs/Last Hard Wrap Column", &lastHardWrapColumn, 80);
	registerOption("Dialogs/Last Hard Wrap Smart Scope Selection", &lastHardWrapSmartScopeSelection, false);
	registerOption("Dialogs/Last Hard Wrap Join Lines", &lastHardWrapJoinLines, false);


	//build commands
	registerOption("Tools/SingleViewerInstance", &singleViewerInstance, false, &pseudoDialog->checkBoxSingleInstanceViewer);
	registerOption("Tools/Show Log After Compiling", &showLogAfterCompiling, true, &pseudoDialog->checkBoxShowLog);

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
	registerOption("LogView/Tabbed", &tabbedLogView, true, &pseudoDialog->checkBoxTabbedLogView);
	registerOption("Interface/New Left Panel Layout", &newLeftPanelLayout, true);

	//language
	registerOption("Interface/Language", &language, "", &pseudoDialog->comboBoxLanguage);

	//preview
	registerOption("Preview/Mode", (int*)&previewMode, 0, &pseudoDialog->comboBoxPreviewMode);


	//pdf preview
	QRect screen = QApplication::desktop()->screenGeometry();
	registerOption("Geometries/PdfViewerLeft", &pdfDocumentConfig->windowLeft, screen.width()/3);
	registerOption("Geometries/PdfViewerTop", &pdfDocumentConfig->windowTop, screen.height()/3);
	registerOption("Geometries/PdfViewerWidth", &pdfDocumentConfig->windowWidth, screen.width()/3);
	registerOption("Geometries/PdfViewerHeight", &pdfDocumentConfig->windowHeight, screen.height()/3);
	registerOption("Geometries/PdfViewerState", &pdfDocumentConfig->windowState, QByteArray());

	registerOption("Preview/DPI", &pdfDocumentConfig->dpi, QApplication::desktop()->logicalDpiX(), &pseudoDialog->spinBoxPreviewDPI);
	registerOption("Preview/Scale Option", &pdfDocumentConfig->scale, 1, &pseudoDialog->comboBoxPreviewScale);
	registerOption("Preview/Scale", &pdfDocumentConfig->scaleOption, 100, &pseudoDialog->spinBoxPreviewScale);
	registerOption("Preview/Magnifier Size", &pdfDocumentConfig->magnifierSize, 300, &pseudoDialog->spinBoxPreviewMagnifierSize);
	registerOption("Preview/Magnifier Shape", &pdfDocumentConfig->magnifierShape, 1, &pseudoDialog->comboBoxPreviewMagnifierShape);
	registerOption("Preview/Magnifier Border", &pdfDocumentConfig->magnifierBorder, false, &pseudoDialog->checkBoxPreviewMagnifierBorder);

	registerOption("Preview/Scrolling Follows Cursor", &pdfDocumentConfig->followFromCursor, false);
	registerOption("Preview/Cursor Follows Scrolling", &pdfDocumentConfig->followFromScroll, false);
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
}

QSettings* ConfigManager::readProfile(QString fname) {

	QSettings *config;

	config=new QSettings(fname,QSettings::IniFormat);

	config->beginGroup("texmaker");

	//----------managed properties--------------------
	for (int i=0;i<managedProperties.size();i++){
	    if(managedProperties[i].name.startsWith("Editor")){
		if(config->contains(managedProperties[i].name)){
		    managedProperties[i].valueFromQVariant(config->value(managedProperties[i].name, managedProperties[i].def));
		}
	    }
	}


	//menu shortcuts
	if(config->contains("keysetting")){
	    int size = config->beginReadArray("keysetting");
	    for (int i = 0; i < size; ++i) {
		config->setArrayIndex(i);
		managedMenuNewShortcuts.append(QPair<QString, QString> (config->value("id").toString(), config->value("key").toString()));
	    }
	    config->endArray();
	}

	//changed latex menus
	if(config->contains("changedLatexMenus"))
	    manipulatedMenus=config->value("changedLatexMenus").toMap();

	//custom toolbar
	for (int i=0; i<managedToolBars.size();i++){
		ManagedToolBar& mtb=managedToolBars[i];
		if(config->contains(mtb.name+"ToolBar"))
		    mtb.actualActions=config->value(mtb.name+"ToolBar").toStringList();
	}

	//custom highlighting
	if(config->contains("customHighlighting"))
	    customEnvironments=config->value("customHighlighting").toMap();

	config->endGroup();

	return config;
}


QSettings* ConfigManager::readSettings() {
	//load config
	bool importTexmakerSettings = false;
	bool usbMode = isExistingFileRealWritable(QCoreApplication::applicationDirPath()+"/texmakerx.ini");
	if (!usbMode)
		if (isExistingFileRealWritable(QCoreApplication::applicationDirPath()+"/texmaker.ini")) {
			//import texmaker usb settings
			usbMode=(QFile(QCoreApplication::applicationDirPath()+"/texmaker.ini")).copy(QCoreApplication::applicationDirPath()+"/texmakerx.ini");
			importTexmakerSettings = true;
		}
	QSettings *config;
	if (usbMode) {
		config=new QSettings(QCoreApplication::applicationDirPath()+"/texmakerx.ini",QSettings::IniFormat);
	} else {
		config=new QSettings(QSettings::IniFormat,QSettings::UserScope,"benibela","texmakerx");
		if (config->childGroups().empty()) {
			//import texmaker global settings
			QSettings oldconfig(QSettings::IniFormat,QSettings::UserScope,"xm1","texmaker");
			QStringList keys=oldconfig.allKeys();
			foreach(QString key, keys) config->setValue(key,oldconfig.value(key,""));
			importTexmakerSettings = true;
		}
	}
	configFileName=config->fileName();
	configFileNameBase=configFileName;
	if (configFileNameBase.endsWith(".ini")) configFileNameBase=configFileNameBase.replace(QString(".ini"),"");

	config->beginGroup("texmaker");

	//----------managed properties--------------------
	for (int i=0;i<managedProperties.size();i++)
		managedProperties[i].valueFromQVariant(config->value(managedProperties[i].name, managedProperties[i].def));

	//------------------files--------------------
	newFileEncoding=QTextCodec::codecForName(newFileEncodingName.toAscii().data());

	//----------------------------dictionaries-------------------------
	if (spell_dic=="<dic not found>" || (importTexmakerSettings && !QFileInfo(spell_dic).exists())) {
		QStringList temp;
		QStringList fallBackPaths;
#ifndef Q_WS_WIN
		fallBackPaths << "/usr/share/hunspell";
#endif
		spell_dic=findResourceFile(QString(QLocale::system().name())+".dic", true, temp, fallBackPaths);
		if (spell_dic=="") spell_dic=findResourceFile("en_US.dic", true, temp, fallBackPaths);
		if (spell_dic=="") spell_dic=findResourceFile("en_GB.dic", true, temp, fallBackPaths);
		if (spell_dic=="") spell_dic=findResourceFile("fr_FR.dic", true, temp, fallBackPaths);
		if (spell_dic=="") spell_dic=findResourceFile("de_DE.dic", true, temp, fallBackPaths);
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
	QStringList cwlFiles=config->value("Editor/Completion Files",QStringList() << "texmakerx.cwl" << "tex.cwl" << "latex-document.cwl" << "latex-mathsymbols.cwl").toStringList();
	completerConfig->words=loadCwlFiles(cwlFiles,ltxCommands);
	completerConfig->setFiles(cwlFiles);
	// remove old solution aus .ini
	if(config->contains("Editor/Completion Usage"))
	    config->remove("Editor/Completion Usage");
	//web publish dialog
	webPublishDialogConfig->readSettings(*config);

	//build commands
	if (!buildManager) QMessageBox::critical(0,"TexMakerX","No build Manager created! => crash",QMessageBox::Ok);
	buildManager->readSettings(*config);
	runLaTeXBibTeXLaTeX=config->value("Tools/After BibTeX Change", "tmx://latex && tmx://bibtex && tmx://latex").toString()!="";
	
	//read user key replacements
	keyReplace.clear();
	keyReplaceAfterWord.clear();
	keyReplaceBeforeWord.clear();
	int keyReplaceCount = config->value("User/KeyReplaceCount",-1).toInt();
	if (keyReplaceCount ==-1) {
		//default
		keyReplace.append("\"");
		QString loc=QString(QLocale::system().name()).left(2);
		if (loc=="de") {
			keyReplaceBeforeWord.append("\">");
			keyReplaceAfterWord.append("\"<");
/*
			keyReplace.append("'");
			keyReplaceBeforeWord.append("''");
			keyReplaceAfterWord.append("``");*/
		} else {
			keyReplaceAfterWord.append("''");
			keyReplaceBeforeWord.append("``");
		}
		keyReplace.append("%");
		keyReplaceBeforeWord.append("%");
		keyReplaceAfterWord.append(" %");
	} else for (int i=0; i<keyReplaceCount; i++) {
			keyReplace.append(config->value("User/KeyReplace"+QVariant(i).toString(),i!=0?"'":"\"").toString());
			keyReplaceAfterWord.append(config->value("User/KeyReplaceAfterWord"+QVariant(i).toString(),i!=0?"":"").toString());
			keyReplaceBeforeWord.append(config->value("User/KeyReplaceBeforeWord"+QVariant(i).toString(),i!=0?"":"\">").toString());
		}
	LatexEditorView::setKeyReplacements(&keyReplace,&keyReplaceAfterWord,&keyReplaceBeforeWord);

	//menu shortcuts
	int size = config->beginReadArray("keysetting");
	for (int i = 0; i < size; ++i) {
		config->setArrayIndex(i);
		managedMenuNewShortcuts.append(QPair<QString, QString> (config->value("id").toString(), config->value("key").toString()));
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
QSettings* ConfigManager::saveSettings() {
	QSettings *config=new QSettings(configFileName, QSettings::IniFormat);
	config->setValue("IniMode",true);

	config->beginGroup("texmaker");

	//----------managed properties--------------------
	foreach (const ManagedProperty& mp, managedProperties)
		config->setValue(mp.name, mp.valueToQVariant());

	//completion
	if (!completerConfig->getLoadedFiles().isEmpty())
		config->setValue("Editor/Completion Files",completerConfig->getLoadedFiles());

	//web publish dialog
	webPublishDialogConfig->saveSettings(*config);
	
	//---------------------build commands----------------
	config->setValue("Tools/After BibTeX Change",runLaTeXBibTeXLaTeX?"tmx://latex && tmx://bibtex && tmx://latex":"");
	
	//-------------------key replacements-----------------
	int keyReplaceCount = keyReplace.count();
	config->setValue("User/KeyReplaceCount",keyReplaceCount);
	for (int i=0; i<keyReplaceCount; i++) {
		config->setValue("User/KeyReplace"+QVariant(i).toString(),keyReplace[i]);
		config->setValue("User/KeyReplaceAfterWord"+QVariant(i).toString(),keyReplaceAfterWord[i]);
		config->setValue("User/KeyReplaceBeforeWord"+QVariant(i).toString(),keyReplaceBeforeWord[i]);
	}

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

	config->endGroup();

	return config;
}

bool ConfigManager::execConfigDialog() {
	ConfigDialog *confDlg = new ConfigDialog(qobject_cast<QWidget*>(parent()));
	//----------managed properties--------------------
	foreach (const ManagedProperty& mp, managedProperties)
		if (mp.widgetOffset)
			mp.writeToWidget(*((QWidget**)((char*)&confDlg->ui + mp.widgetOffset))); //convert to char*, because the offset is in bytes

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
	QStringList languageFiles=findResourceFiles("translations","texmakerx_*.qm")
							<< findResourceFiles("","texmakerx_*.qm");
	int langId=-1;
	for (int i=0;i<languageFiles.count();i++){
		//_gettext. 
		QString cur=languageFiles[i].mid(languageFiles[i].indexOf("_")+1);
		cur.truncate(cur.indexOf("."));
		confDlg->ui.comboBoxLanguage->addItem(cur);
		if (cur == language) langId=i;
	}
	confDlg->ui.comboBoxLanguage->addItem("en");
	confDlg->ui.comboBoxLanguage->addItem(tr("default"));
	if (language=="") confDlg->ui.comboBoxLanguage->setEditText(tr("default"));
	else confDlg->ui.comboBoxLanguage->setEditText(language);
	if (langId!=-1) confDlg->ui.comboBoxLanguage->setCurrentIndex(langId);
	else if (language=="en") confDlg->ui.comboBoxLanguage->setCurrentIndex(confDlg->ui.comboBoxLanguage->count()-2);
	else confDlg->ui.comboBoxLanguage->setCurrentIndex(confDlg->ui.comboBoxLanguage->count()-1);
	
	QStringList files=findResourceFiles("completion","*.cwl");
	QListWidgetItem *item;
	const QStringList& loadedFiles = completerConfig->getLoadedFiles();
	foreach(QString elem,files) {
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
	QVBoxLayout *verticalLayout = new QVBoxLayout(confDlg->ui.groupBoxCommands);
	QScrollArea *scrollAreaCommands = new QScrollArea(confDlg->ui.groupBoxCommands);
	scrollAreaCommands->setWidgetResizable(true);
	QWidget *scrollAreaWidgetContents = new QWidget();
	QGridLayout* gl=new QGridLayout(scrollAreaWidgetContents);
	for (BuildManager::LatexCommand cmd=BuildManager::CMD_LATEX; cmd < BuildManager::CMD_USER_QUICK; ++cmd){
		QLabel *l = new QLabel(confDlg);
		l->setText(BuildManager::commandDisplayName(cmd));
		QLineEdit *e = new QLineEdit(confDlg);
		e->setText(buildManager->getLatexCommandForDisplay(cmd));
		QPushButton *b = new QPushButton(confDlg);
		b->setIcon(getRealIcon("fileopen"));
		connect(b,SIGNAL(clicked()),this,SLOT(browseCommand()));
		QPushButton *bdefault = new QPushButton(confDlg);
		bdefault->setIcon(getRealIcon("undo"));
		connect(bdefault,SIGNAL(clicked()),this,SLOT(undoCommand()));
		l->setMinimumHeight(l->sizeHint().height());
		b->setMinimumHeight(b->sizeHint().height());
		e->setMinimumHeight(e->sizeHint().height());
 		gl->addWidget(l,(int)cmd,0);
		int off =  0;
		if (cmd == BuildManager::CMD_VIEWPDF) {
			confDlg->checkboxInternalPDFViewer = new QCheckBox(confDlg);
			confDlg->checkboxInternalPDFViewer->setObjectName("internal");
			confDlg->checkboxInternalPDFViewer->setText(tr("Internal viewer"));
			confDlg->checkboxInternalPDFViewer->setChecked(buildManager->getLatexCommand(cmd).startsWith(BuildManager::TMX_INTERNAL_PDF_VIEWER));
			connect(confDlg->checkboxInternalPDFViewer,SIGNAL(toggled(bool)),this,SLOT(activateInternalViewer(bool)));
			gl->addWidget(confDlg->checkboxInternalPDFViewer, (int)cmd, 1);
			off++;
		}
		gl->addWidget(e,(int)cmd,1+off,1,2-off);
		gl->addWidget(b,(int)cmd,3);
		gl->addWidget(bdefault,(int)cmd,4);
		buttonsToCommands.insert(b,cmd);
		buttonsToCommands.insert(bdefault,cmd);
		commandsToEdits.insert(cmd,e);
	}
	scrollAreaCommands->setWidget(scrollAreaWidgetContents);
	verticalLayout->addWidget(scrollAreaCommands);


	//confDlg->ui.groupBoxCommands->setMinimumHeight(confDlg->ui.groupBoxCommands->sizeHint().height());
	// svn commands
	QGridLayout* glsvn=new QGridLayout(confDlg->ui.groupBoxSVN);
	confDlg->ui.groupBoxSVN->setLayout(glsvn);
	for (BuildManager::LatexCommand cmd=BuildManager::CMD_SVN; cmd <= BuildManager::CMD_SVNADMIN; ++cmd){
		QLabel *l = new QLabel(confDlg);
		l->setText(BuildManager::commandDisplayName(cmd));
		QLineEdit *e = new QLineEdit(confDlg);
		e->setText(buildManager->getLatexCommandForDisplay(cmd));
		QPushButton *b = new QPushButton(confDlg);
		b->setIcon(getRealIcon("fileopen"));
		connect(b,SIGNAL(clicked()),this,SLOT(browseCommand()));
		QPushButton *bdefault = new QPushButton(confDlg);
		bdefault->setIcon(getRealIcon("undo"));
		connect(bdefault,SIGNAL(clicked()),this,SLOT(undoCommand()));
		l->setMinimumHeight(l->sizeHint().height());
		b->setMinimumHeight(b->sizeHint().height());
		e->setMinimumHeight(e->sizeHint().height());
		glsvn->addWidget(l,(int)cmd,0);
		glsvn->addWidget(e,(int)cmd,1);
		glsvn->addWidget(b,(int)cmd,2);
		glsvn->addWidget(bdefault,(int)cmd,3);
		buttonsToCommands.insert(b,cmd);
		buttonsToCommands.insert(bdefault,cmd);
		commandsToEdits.insert(cmd,e);
	}
	//quickbuild/more page	
	confDlg->buildManager = buildManager;
	if (buildManager->quickmode==1) confDlg->ui.radioButton1->setChecked(true);
	else if (buildManager->quickmode==2) confDlg->ui.radioButton2->setChecked(true);
	else if (buildManager->quickmode==3) confDlg->ui.radioButton3->setChecked(true);
	else if (buildManager->quickmode==4) confDlg->ui.radioButton4->setChecked(true);
	else if (buildManager->quickmode==5) confDlg->ui.radioButton5->setChecked(true);
	else if (buildManager->quickmode==6) confDlg->ui.radioButton6_2->setChecked(true);
	else if (buildManager->quickmode==7) confDlg->ui.radioButton7->setChecked(true);
	else if (buildManager->quickmode==8) confDlg->ui.radioButton6->setChecked(true);
	confDlg->ui.lineEditExecuteBeforeCompiling->setText(buildManager->getLatexCommandForDisplay(BuildManager::CMD_USER_PRECOMPILE));
	confDlg->ui.lineEditUserquick->setText(buildManager->getLatexCommandForDisplay(BuildManager::CMD_USER_QUICK));
	
	confDlg->ui.checkBoxReplaceBeamer->setChecked(buildManager->previewRemoveBeamer);

	confDlg->ui.checkBoxRunAfterBibTeXChange->setChecked(runLaTeXBibTeXLaTeX);

	QIcon fileOpenIcon = getRealIcon("fileopen");
	confDlg->ui.pushButtonAspell->setIcon(fileOpenIcon);
	confDlg->ui.btSelectThesaurusFileName->setIcon(fileOpenIcon);
	confDlg->ui.pushButtonExecuteBeforeCompiling->setIcon(fileOpenIcon);

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
	foreach(int elem, editorAvailableOperations){
	    QList<int> keys=keysReversed.values(elem);
	    bool listEmpty=false;
	    if(keys.isEmpty()){
		keys<< 0;
		listEmpty=true;
	    }
	    foreach(int key,keys){
		QTreeWidgetItem * twi=0;
		if(listEmpty){
		    twi = new QTreeWidgetItem(editorKeys, QStringList() << LatexEditorViewConfig::translateEditOperation(elem) << "" << tr("<none>"));
		} else {
		    twi = new QTreeWidgetItem(editorKeys, QStringList() << LatexEditorViewConfig::translateEditOperation(elem) << "" << QKeySequence(key).toString(QKeySequence::NativeText));
		}
		twi->setData(0, Qt::UserRole, elem);
		twi->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled);
	    }
	}
	new QTreeWidgetItem(editorKeys, QStringList() << ShortcutDelegate::addRowButton);

	//add special key replacements
	QTreeWidgetItem * keyReplacements = new QTreeWidgetItem(editorItem, QStringList() << ConfigDialog::tr("Special Key Replacement"));
	QTreeWidgetItem * columnItem=new QTreeWidgetItem(keyReplacements, QStringList() << ConfigDialog::tr("New column meaning:") << ConfigDialog::tr("Key to replace") << ConfigDialog::tr("Text to insert before word") << ConfigDialog::tr("Text to insert after word"));
	QFont f;
	f.setUnderline(true);
	columnItem->setFont(0,f);
	f.setBold(true);
	columnItem->setFont(1,f);
	columnItem->setFont(2,f);
	columnItem->setFont(3,f);
	for (int i=0; i<keyReplace.size(); i++)
		(new QTreeWidgetItem(keyReplacements, QStringList() << ShortcutDelegate::deleteRowButton << keyReplace[i] << keyReplaceBeforeWord[i] << keyReplaceAfterWord[i]))
		->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled);
	new QTreeWidgetItem(keyReplacements, QStringList() << ShortcutDelegate::addRowButton);
	confDlg->ui.shortcutTree->addTopLevelItem(editorItem);
	editorItem->setExpanded(true);


	ShortcutDelegate delegate;
	delegate.treeWidget=confDlg->ui.shortcutTree;
	confDlg->ui.shortcutTree->setItemDelegate(&delegate); //setting in the config dialog doesn't work
	delegate.connect(confDlg->ui.shortcutTree,SIGNAL(itemClicked(QTreeWidgetItem *, int)),&delegate,SLOT(treeWidgetItemClicked(QTreeWidgetItem * , int)));

	//latex menus
	confDlg->menuParent=menuParent;
	changedItemsList.clear();
	foreach(QMenu* menu, managedMenus){
		QTreeWidgetItem *menuLatex=managedLatexMenuToTreeWidget(0,menu);
		if(menuLatex) {
			confDlg->ui.latexTree->addTopLevelItem(menuLatex);
			menuLatex->setExpanded(true);
		}
	}
	connect(confDlg->ui.latexTree,SIGNAL(itemChanged(QTreeWidgetItem*,int)),this,SLOT(latexTreeItemChanged(QTreeWidgetItem*,int)));

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
	}
	
	
	//EXECUTE IT
	bool executed = confDlg->exec();
	//handle changes
	if (executed) {
		QList<void*> changedProperties;
		//----------managed properties--------------------
		for (int i=0;i<managedProperties.size();i++)
			if (managedProperties[i].widgetOffset && managedProperties[i].readFromWidget(*((QWidget**)((char*)&confDlg->ui + managedProperties[i].widgetOffset))))
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
		ltxCommands->clear();
		completerConfig->words=loadCwlFiles(newFiles,ltxCommands);
		completerConfig->setFiles(newFiles);

		//preview
		previewMode=(PreviewMode) confDlg->ui.comboBoxPreviewMode->currentIndex();
		buildManager->dvi2pngMode=(BuildManager::Dvi2PngMode) confDlg->ui.comboBoxDvi2PngMode->currentIndex();
		
		//build things
		for (BuildManager::LatexCommand cmd=BuildManager::CMD_LATEX; cmd < BuildManager::CMD_USER_QUICK; ++cmd){
			if (!commandsToEdits.value(cmd)) continue;
			buildManager->setLatexCommand(cmd,commandsToEdits.value(cmd)->text());;
		}
		
		for (BuildManager::LatexCommand cmd=BuildManager::CMD_SVN; cmd <= BuildManager::CMD_SVNADMIN; ++cmd){
			if (!commandsToEdits.value(cmd)) continue;
			buildManager->setLatexCommand(cmd,commandsToEdits.value(cmd)->text());;
		}


		Q_ASSERT(confDlg->checkboxInternalPDFViewer);
		QString curPdfViewer = buildManager->getLatexCommand(BuildManager::CMD_VIEWPDF);
		if (confDlg->checkboxInternalPDFViewer && confDlg->checkboxInternalPDFViewer->isChecked() != curPdfViewer.startsWith(BuildManager::TMX_INTERNAL_PDF_VIEWER)) {
			//prepend/remove tmx://internal-pdf-viewer
			if (confDlg->checkboxInternalPDFViewer->isChecked())
				buildManager->setLatexCommand(BuildManager::CMD_VIEWPDF , BuildManager::TMX_INTERNAL_PDF_VIEWER + "/" + curPdfViewer);
			else if (curPdfViewer.startsWith(BuildManager::TMX_INTERNAL_PDF_VIEWER+"/"))
				buildManager->setLatexCommand(BuildManager::CMD_VIEWPDF , curPdfViewer.mid(BuildManager::TMX_INTERNAL_PDF_VIEWER.length() + 1));
			else
				buildManager->setLatexCommand(BuildManager::CMD_VIEWPDF , curPdfViewer.mid(BuildManager::TMX_INTERNAL_PDF_VIEWER.length()));
		}

		buildManager->setLatexCommand(BuildManager::CMD_USER_PRECOMPILE,confDlg->ui.lineEditExecuteBeforeCompiling->text());
		buildManager->setLatexCommand(BuildManager::CMD_USER_QUICK,confDlg->ui.lineEditUserquick->text());

		if (confDlg->ui.radioButton1->isChecked()) buildManager->quickmode=1;
		if (confDlg->ui.radioButton2->isChecked()) buildManager->quickmode=2;
		if (confDlg->ui.radioButton3->isChecked()) buildManager->quickmode=3;
		if (confDlg->ui.radioButton4->isChecked()) buildManager->quickmode=4;
		if (confDlg->ui.radioButton5->isChecked()) buildManager->quickmode=5;
		if (confDlg->ui.radioButton6_2->isChecked()) buildManager->quickmode=6;
		if (confDlg->ui.radioButton7->isChecked()) buildManager->quickmode=7;
		if (confDlg->ui.radioButton6->isChecked()) buildManager->quickmode=8;

		buildManager->previewRemoveBeamer = confDlg->ui.checkBoxReplaceBeamer->isChecked();

		runLaTeXBibTeXLaTeX=confDlg->ui.checkBoxRunAfterBibTeXChange->isChecked();

		
		//key replacements
		keyReplace.clear();
		keyReplaceBeforeWord.clear();
		keyReplaceAfterWord.clear();
		for (int i=1; i<keyReplacements->childCount()-1; i++) {
			keyReplace << keyReplacements->child(i)->text(1);
			keyReplaceBeforeWord << keyReplacements->child(i)->text(2);
			keyReplaceAfterWord << keyReplacements->child(i)->text(3);
		}
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
		if (changedProperties.contains(&displayedInterfaceStyle) || changedProperties.contains(&modernStyle) || changedProperties.contains(&useTexmakerPalette)){
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
    QLineEdit *le=commandsToEdits.value(BuildManager::CMD_PDFLATEX);
    if(le->text().contains("synctex")) return;
    QMessageBox msgBox;
     msgBox.setText("Internal Viewer");
     msgBox.setInformativeText(tr("To fully utilize the internal pdf-viewer, synctex has to be activated. Shall TexMakerX do it now?"));
     msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
     msgBox.setDefaultButton(QMessageBox::Yes);
     int ret = msgBox.exec();
     if(ret==QMessageBox::Yes){
	 QString zw=le->text();
	 zw.replace("pdflatex ","pdflatex -synctex=1 ",Qt::CaseSensitive);
	 le->setText(zw);
     }
}

void ConfigManager::updateRecentFiles(bool alwaysRecreateMenuItems) {
	QMenu* recentMenu = getManagedMenu("main/file/openrecent");
	if (alwaysRecreateMenuItems || (recentMenu->actions().count()!=maxRecentFiles+maxRecentProjects+2)) {
		QList<QAction*> actions=recentMenu->actions(); //recentMenu->clear() doesn't seem to delete the actions (why?)
		for (int i = 0; i< actions.count(); i++)
			recentMenu->removeAction(actions[i]); //neccessary or it crashes
		for (int i = 0; i < maxRecentProjects; ++i)
			newOrLostOldManagedAction(recentMenu, "p"+QString::number(i), tr("Recent 'Master Document' %1").arg(i), SLOT(fileOpenRecentProject()))->setVisible(false);
		recentMenu->addSeparator();
		for (int i = 0; i < maxRecentFiles; ++i)
			newOrLostOldManagedAction(recentMenu, QString::number(i), tr("Recent File %1").arg(i), SLOT(fileOpenRecent()))->setVisible(false);
		newManagedAction(recentMenu, "allFiles", tr("Open all files"), SLOT(fileOpenAllRecent()));
	}

	for (int i=0; i < maxRecentProjects; i++) {
		QAction* act = getManagedAction(QString("main/file/openrecent/p%1").arg(i));
		REQUIRE(act);
		if (i<recentProjectList.count()) {
			act->setVisible(true);
			act->setText(tr("Master Document: ")+recentProjectList.at(i));
			act->setData(recentProjectList.at(i));
		} else act->setVisible(false);
	}
	for (int i=0; i < maxRecentFiles; i++) {
		QAction* act = getManagedAction(QString("main/file/openrecent/%1").arg(i));
		REQUIRE(act);
		if (i<recentFilesList.count()) {
			act->setVisible(true);
			act->setText(recentFilesList.at(i));
			act->setData(recentFilesList.at(i));
		} else act->setVisible(false);
	}
}

QMenu* ConfigManager::updateListMenu(const QString& menuName, const QStringList& items, const QString& namePrefix, bool prefixNumber, const char* slotName, const int baseShortCut, bool alwaysRecreateMenuItems, int additionalEntries){
	QMenu* menu = getManagedMenu(menuName);
	Q_ASSERT(menu->objectName() == menuName);
	REQUIRE_RET(menu, 0);
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
	return menu;
}

void ConfigManager::updateUserMacroMenu(bool alwaysRecreateMenuItems){
	QMenu* recreatedMenu = updateListMenu("main/user/tags", userMacroMenuName, "tag", true, SLOT(InsertUserTag()), Qt::SHIFT+Qt::Key_F1, alwaysRecreateMenuItems);
	if (recreatedMenu) {
		recreatedMenu->addSeparator();
		newOrLostOldManagedAction(recreatedMenu, "manage",QCoreApplication::translate("Texmaker", "Edit User &Tags"), SLOT(EditUserMenu()));
	}
}

void ConfigManager::updateUserToolMenu(bool alwaysRecreateMenuItems){
	QMenu* recreatedMenu = updateListMenu("main/user/commands", userToolMenuName, "cmd", true, SLOT(UserTool()), Qt::SHIFT+Qt::ALT+Qt::Key_F1, alwaysRecreateMenuItems);
	if (recreatedMenu) {
		recreatedMenu->addSeparator();
		newOrLostOldManagedAction(recreatedMenu, "manage", QCoreApplication::translate("Texmaker", "Edit User &Commands"), SLOT(EditUserTool()));
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
	QString menuId = menu->objectName();
	QString completeId = menu->objectName()+"/"+ id;

	QAction *old=menuParent->findChild<QAction*>(completeId);
	if (old) {
		old->setText(text);
		old->setIcon(getRealIcon(iconFile));
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
	if (slotName) connect(act, SIGNAL(triggered()), menuParent, slotName);
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
QAction* ConfigManager::getManagedAction(QString id) {
	QAction* act=0;
	if (menuParent) act=menuParent->findChild<QAction*>(id);
	if (act==0) qWarning("Can't find internal action %s",id.toAscii().data());
	return act;
}
QMenu* ConfigManager::getManagedMenu(QString id) {
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
void ConfigManager::triggerManagedAction(QString id){
	QAction* act = getManagedAction(id);
	if (act) act->trigger();
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
	QMap<QString, QVariant>::const_iterator i = manipulatedMenus.constBegin();
	while (i != manipulatedMenus.constEnd()) {
		QString id=i.key();
		QVariant zw=i.value();
		QStringList m=zw.toStringList();
		QAction * act= getManagedAction(id);
		if (act) {
			act->setText(m.first());
			act->setData(m.at(1));
			act->setVisible(!(m.value(2,"visible")=="hidden"));
		}
		++i;
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
	QString tmxTranslationFile=findResourceFile("texmakerx_"+locale+".qm");
	//if (tmxTranslationFile!="") {
		appTranslator->load(tmxTranslationFile);
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

void ConfigManager::browseCommand(){
	QPushButton *pb = qobject_cast<QPushButton*> (sender());
	if (!buttonsToCommands.contains(pb)) return;
	BuildManager::LatexCommand cmd=buttonsToCommands.value(pb);
	QLineEdit* ed = commandsToEdits.value(cmd);
	if (!ed) return;
	QString path = ed->text();
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
		location="\""+location+"\" "+BuildManager::defaultCommandOptions(cmd);
		ed->setText(location);
	}
}
void ConfigManager::undoCommand(){
	QPushButton *pb = qobject_cast<QPushButton*> (sender());
	if (!buttonsToCommands.contains(pb)) return;
	BuildManager::LatexCommand cmd=buttonsToCommands.value(pb);
	QLineEdit* ed = commandsToEdits.value(cmd);
	if (!ed) return;
	ed->setText(BuildManager::guessCommandName(cmd));
}

// manipulate latex menus
QTreeWidgetItem* ConfigManager::managedLatexMenuToTreeWidget(QTreeWidgetItem* parent, QMenu* menu) {
        if (!menu) return 0;
        QStringList relevantMenus;
        relevantMenus << tr("Latex") << tr("Math");
        if(!parent && !relevantMenus.contains(menu->title().replace("&",""))) return 0;
        QTreeWidgetItem* menuitem= new QTreeWidgetItem(parent, QStringList(menu->title().replace("&","")));
        if (menu->objectName().count("/")<=2) menuitem->setExpanded(true);
        QList<QAction *> acts=menu->actions();
        for (int i=0; i<acts.size(); i++)
                if (acts[i]->menu()) managedLatexMenuToTreeWidget(menuitem, acts[i]->menu());
                else {
                    if(acts[i]->data().isValid()){
                        QTreeWidgetItem* twi=new QTreeWidgetItem(menuitem, QStringList() << acts[i]->text()
                                        << acts[i]->data().toString());
                        twi->setIcon(0,acts[i]->icon());
						if (!acts[i]->isSeparator()) {
							twi->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
							twi->setCheckState(0,acts[i]->isVisible() ? Qt::Checked : Qt::Unchecked);
						}
                        twi->setData(0,Qt::UserRole,acts[i]->objectName());

                    }
                }
        return menuitem;
}

void ConfigManager::latexTreeItemChanged(QTreeWidgetItem* item,int ){
    if(!changedItemsList.contains(item)) changedItemsList.append(item);
}

void ConfigManager::treeWidgetToManagedLatexMenuTo() {
	foreach(QTreeWidgetItem* item,changedItemsList){
		QString id=item->data(0,Qt::UserRole).toString();
		if (id=="") return;
		QAction * act=getManagedAction(id);
		if (act) {
			act->setText(item->text(0));
			act->setData(item->text(1));
			act->setVisible(item->checkState(0)==Qt::Checked);
			QString zw="hidden";
			if(item->checkState(0)==Qt::Checked) zw="visible";
			QStringList m;
			m << item->text(0) << item->text(1) << zw ;
			manipulatedMenus.insert(id,m);
		}
	}
}


void ConfigManager::registerOption(const QString& name, void* storage, PropertyType type, QVariant def, void* displayWidgetOffset){
	ManagedProperty temp;
	temp.name = name;
	temp.storage = storage;
	temp.type = type;
	temp.def = def;
	temp.widgetOffset = (ptrdiff_t)displayWidgetOffset;
	managedProperties << temp;
}

void ConfigManager::registerOption(const QString& name, bool* storage, QVariant def, void* displayWidgetOffset){
	registerOption(name, storage, PT_BOOL, def, displayWidgetOffset);
}
void ConfigManager::registerOption(const QString& name, int* storage, QVariant def, void* displayWidgetOffset){
	registerOption(name, storage, PT_INT, def, displayWidgetOffset);
}
void ConfigManager::registerOption(const QString& name, QString* storage, QVariant def, void* displayWidgetOffset){
	registerOption(name, storage, PT_STRING, def, displayWidgetOffset);
}
void ConfigManager::registerOption(const QString& name, QStringList* storage, QVariant def, void* displayWidgetOffset){
	registerOption(name, storage, PT_STRINGLIST, def, displayWidgetOffset);
}
void ConfigManager::registerOption(const QString& name, QDateTime *storage, QVariant def, void* displayWidgetOffset){
	registerOption(name, storage, PT_DATETIME, def, displayWidgetOffset);
}
void ConfigManager::registerOption(const QString& name, double *storage, QVariant def, void* displayWidgetOffset){
	registerOption(name, storage, PT_DOUBLE, def, displayWidgetOffset);
}
void ConfigManager::registerOption(const QString& name, QByteArray *storage, QVariant def, void* displayWidgetOffset){
	registerOption(name, storage, PT_BYTEARRAY, def, displayWidgetOffset);
}
void ConfigManager::registerOption(const QString& name, QList<QVariant> *storage, QVariant def, void* displayWidgetOffset){
	registerOption(name, storage, PT_LIST, def, displayWidgetOffset);
}

void ConfigManager::registerOption(const QString& name, void* storage, PropertyType type, QVariant def){
	registerOption(name, storage, type, def, 0);
}

void ConfigManager::registerOption(const QString& name, bool* storage, QVariant def){
	registerOption(name, storage, def, 0);
}
void ConfigManager::registerOption(const QString& name, int* storage, QVariant def){
	registerOption(name, storage, def, 0);
}
void ConfigManager::registerOption(const QString& name, QString* storage, QVariant def){
	registerOption(name, storage, def, 0);
}
void ConfigManager::registerOption(const QString& name, QStringList* storage, QVariant def){
	registerOption(name, storage, def, 0);
}
void ConfigManager::registerOption(const QString& name, QDateTime* storage, QVariant def){
	registerOption(name, storage, def, 0);
}
void ConfigManager::registerOption(const QString& name, double* storage, QVariant def){
	registerOption(name, storage, def, 0);
}
void ConfigManager::registerOption(const QString& name, QByteArray* storage, QVariant def){
	registerOption(name, storage, def, 0);
}
void ConfigManager::registerOption(const QString& name, QList<QVariant>* storage, QVariant def){
	registerOption(name, storage, def, 0);
}

void ConfigManager::linkOptionToWidget(const void* optionStorage, QWidget* widget){
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

	property->writeToWidget(widget);
	widget->setProperty("managedProperty", QVariant::fromValue<void*>(property->storage));
}
ManagedProperty* ConfigManager::getManagedProperty(const void* storage){
	for (int i=0;i<managedProperties.size();i++)
		if (managedProperties[i].storage == storage) return &managedProperties[i];
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
		prop->readFromWidget(widget);
	}
	managedOptionDialogs.remove(dialog);
}
