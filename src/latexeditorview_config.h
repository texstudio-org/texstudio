#ifndef Header_Latex_Editor_View_Config
#define Header_Latex_Editor_View_Config

//having the configuration in a single file allows to change it,
//without having a relationship between completer and configmanager
//so modifying one doesn't lead to a recompilation of the other

class QString;

class LatexEditorViewConfig
{
public:
	bool parenmatch, parenComplete;
	bool autoindent, weakindent;
	bool replaceIndentTabs;
	bool replaceTextTabs;
	bool removeTrailingWsOnSave;
	bool showWhitespace;
	int tabStop;
	int showlinemultiples;
	int cursorSurroundLines;
	bool boldCursor;
	bool centerDocumentInEditor;
	bool folding, showlinestate, showcursorstate, realtimeChecking;
	bool inlineSpellChecking, inlineCitationChecking, inlineReferenceChecking, inlineSyntaxChecking, inlineGrammarChecking, inlinePackageChecking;
	bool inlineCheckNonTeXFiles;
	bool hideNonTextSpellingErrors, hideNonTextGrammarErrors;
	QString fontFamily;
	int fontSize;
	int lineSpacingPercent;
	int lineWidth;
	bool closeSearchAndReplace;
	bool useLineForSearch, searchOnlyInSelection;
	static QString translateEditOperation(int key);
	static QList<int> possibleEditOperations();
	bool allowDragAndDrop;
	bool mouseWheelZoom, smoothScrolling, verticalOverScroll;

	bool hackAutoChoose, hackDisableFixedPitch, hackDisableWidthCache, hackDisableLineCache, hackDisableAccentWorkaround, hackQImageCache;
	int hackRenderingMode; //0: normal, 1: qt (missing), 2: single letter
	bool showPlaceholders;
	int wordwrap; // 0 off, 1 soft wrap, 2 soft wrap fixed line width, 3 hard wrap fixed line width
	bool toolTipPreview;
	bool toolTipHelp;
	bool imageToolTip;
	int maxImageTooltipWidth;
	bool texdocHelpInInternalViewer;
	bool monitorFilesForExternalChanges;
	bool silentReload;
	bool useQSaveFile;

	bool autoInsertLRM, visualColumnMode, switchLanguagesDirection, switchLanguagesMath;

	bool overwriteOpeningBracketFollowedByPlaceholder;
	bool overwriteClosingBracketFollowingPlaceholder;
	bool doubleClickSelectionIncludeLeadingBackslash;
	int tripleClickSelectionIndex;
	int contextMenuSpellcheckingEntryLocation;
	int contextMenuKeyboardModifiers;  // actually this is a Qt::KeyboardModifiers flag (but we don't want to import the whole qt namespace here)

	bool fullCompilePreview;

    QString regExpTodoComment;

	void settingsChanged();

private:
	QString lastFontFamily;
	int lastFontSize;
};

#endif
