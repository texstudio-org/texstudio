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

#ifndef Header_Latex_Editor_View
#define Header_Latex_Editor_View

#include "mostQtHeaders.h"
#include "qdocument.h"
#include "syntaxcheck.h"
#include "grammarcheck.h"
#include "bibtexreader.h"
#include "cursorposition.h"
#include "latexcompleter.h"
#include "help.h"
#include "latexdocument.h"
//class QDocumentLineHandle;

//class LatexDocument;
class QCodeEdit;
class QEditor;
class QLineMarkPanel;
class QLineNumberPanel;
class QSearchReplacePanel;
class QGotoLinePanel;
class QStatusPanel;
class LatexCompleter;
class SpellerUtility;
class SpellerManager;
class DefaultInputBinding;
class LatexEditorViewConfig;
class Macro;
class MacroExecContext;
/*!
 * \brief represent link overlays
 * When pressing control, some structural elements in the text can be changed to links in order to jump to corresponding places
 *
 */
struct LinkOverlay {
	enum LinkOverlayType {Invalid, RefOverlay, FileOverlay, UrlOverlay, UsepackageOverlay, BibFileOverlay, CiteOverlay, CommandOverlay, EnvOverlay};
	// for simpler access everything is public - only access for reading
	LinkOverlayType type;
	QDocumentLine docLine;
	QFormatRange formatRange;
    QString m_link;

	LinkOverlay() : type(Invalid) {}
	LinkOverlay(const LinkOverlay &o);
	LinkOverlay(const Token &token, LinkOverlayType ltype);

	bool isValid() const
	{
		return type != Invalid;
	}
	LinkOverlay & operator= (const LinkOverlay &) = default;	// Avoid GCC9 -Wdeprecated-copy warning
	bool operator ==(const LinkOverlay &o) const
	{
		return (docLine == o.docLine) && (formatRange == o.formatRange);
	}
	QString text() const;
};
/*!
 * \brief actual editor widget
 */
class LatexEditorView : public QWidget
{
	Q_OBJECT

public:
    LatexEditorView(QWidget *parent, LatexEditorViewConfig *aconfig, LatexDocument *doc = nullptr);
	~LatexEditorView();

	QCodeEdit *codeeditor;
	QEditor *editor;

	LatexDocument *document;

	QDateTime lastUsageTime;

	QEditor *getEditor() const
	{
		return editor;
	}
	LatexDocument *getDocument() const { return document; }
    Q_PROPERTY(QEditor *editor READ getEditor);
    Q_PROPERTY(LatexDocument *document READ getDocument);    //<- semicolon necessary due to qt bug 22992

	LatexEditorViewConfig *getConfig() { return config; }

	Q_INVOKABLE	QString displayName() const;
	QString displayNameForUI() const;

	//  FindWidget *findwidget;
	//Functions affecting the editor

    Q_INVOKABLE void complete(int flags); ///< complete text
	bool gotoLineHandleAndSearchCommand(const QDocumentLineHandle *dlh, const QSet<QString> &searchFor, const QString &id);
	bool gotoLineHandleAndSearchString(const QDocumentLineHandle *dlh, const QString &str);
	bool gotoLineHandleAndSearchLabel(const QDocumentLineHandle *dlh, const QString &label);
	bool gotoLineHandleAndSearchBibItem(const QDocumentLineHandle *dlh, const QString &bibId);

	static QList<QAction *> getBaseActions();
	static void setBaseActions(QList<QAction *> baseActions);
    static int getLineRowforContexMenu();
    static int getLineColforContexMenu();
	void setSpellerManager(SpellerManager *manager);
    bool setSpeller(const QString &name,bool updateComment=false);
	Q_INVOKABLE QString getSpeller();

	static void setCompleter(LatexCompleter *newCompleter);
	static LatexCompleter *getCompleter();
	bool containsBibTeXId(QString id);

	void updateCitationFormats();
	void updatePackageFormats();

	void clearLogMarks();
	void addLogEntry(int logEntryNumber, int lineNumber, int markID);
	void setLogMarksVisible(bool visible);
	QMultiHash<QDocumentLineHandle *, int> lineToLogEntries;
	QHash<int, QDocumentLineHandle *> logEntryToLine;
	QHash<int, int> logEntryToMarkID;

	static int hideTooltipWhenLeavingLine;
	static int syntaxErrorFormat;

	void setLineMarkToolTip(const QString &tooltip);
	void updateSettings();
	static void updateFormatSettings();

	QPoint getHoverPosistion() { return m_point; }

	static int deleteFormat, insertFormat, replaceFormat;
	static int preEditFormat;

	Q_INVOKABLE void closeCompleter();
	Q_INVOKABLE void removeBookmark(int lineNr, int bookmarkNumber);
	void removeBookmark(QDocumentLineHandle *dlh, int bookmarkNumber);
	Q_INVOKABLE void addBookmark(int lineNr, int bookmarkNumber);
	Q_INVOKABLE bool hasBookmark(int lineNr, int bookmarkNumber);
	bool hasBookmark(QDocumentLineHandle *dlh, int bookmarkNumber);
    int hasBookmark(QDocumentLineHandle *dlh);

	QList<QDocumentCursor> autoPreviewCursor;

	static int bookMarkId(int bookmarkNumber);

	static void selectOptionInLatexArg(QDocumentCursor &cur);

	QDocumentCursor parenthizedTextSelection(const QDocumentCursor &cursor, bool includeParentheses = true);
	QDocumentCursor findFormatsBegin(const QDocumentCursor &cursor, QSet<int> allowedFormats, QSet<int> allowedLineEndFormats);
    void setLatexPackageList(std::set<QString> *lst) { latexPackageList = lst; }

	LatexParser lp;

	QString getSearchText();
	QString getReplaceText();
	bool getSearchIsCase();
	bool getSearchIsRegExp();
	bool getSearchIsWords();

	void updateReplamentList(const LatexParser &cmds, bool forceUpdate = false);
    QMap<QString,QString> getReplacementList(){
        return mReplacementList;
    }

    void updatePalette(const QPalette & pal);

    void setHelp(Help *obj){
        help=obj;
    };
    Help* getHelp(){
        return help;
    }

private:
	QAction *lineNumberPanelAction, *lineMarkPanelAction, *lineFoldPanelAction, *lineChangePanelAction,
	        *statusPanelAction, *searchReplacePanelAction, *gotoLinePanelAction;
	QLineMarkPanel *lineMarkPanel;
	QLineNumberPanel *lineNumberPanel;
	QSearchReplacePanel *searchReplacePanel;
	QGotoLinePanel *gotoLinePanel;
	QStatusPanel *statusPanel;

	QPoint m_point;

    QDocumentCursor wordSelection;

	static int environmentFormat, referencePresentFormat, referenceMissingFormat, referenceMultipleFormat, citationMissingFormat, citationPresentFormat, structureFormat, todoFormat,
	       packagePresentFormat, packageMissingFormat, packageUndefinedFormat,
	       wordRepetitionFormat, wordRepetitionLongRangeFormat, badWordFormat, grammarMistakeFormat, grammarMistakeSpecial1Format, grammarMistakeSpecial2Format, grammarMistakeSpecial3Format, grammarMistakeSpecial4Format,
	       numbersFormat, verbatimFormat, commentFormat, pictureFormat, pweaveDelimiterFormat, pweaveBlockFormat, sweaveDelimiterFormat, sweaveBlockFormat, math_DelimiterFormat, math_KeywordFormat,
	       asymptoteBlockFormat;
	static QList<int> grammarFormats;
	static QVector<bool> grammarFormatsDisabled;
	static QList<int> formatsList;

    std::set<QString> *latexPackageList;

	friend class DefaultInputBinding;
	friend class SyntaxCheckTest;

	SpellerManager *spellerManager;
	SpellerUtility *speller;
	bool useDefaultSpeller;
	static LatexCompleter *completer;
	QList<CursorPosition> changePositions; //line, index
	int curChangePos;

	LatexEditorViewConfig *config;

	bibtexReader *bibReader;
	QPoint lastPos;

	LinkOverlay linkOverlay;
	QCursor linkOverlayStoredCursor;

	QList<QPair<QDocumentLine, QFormatRange> > tempHighlightQueue;

	QMap<QString, QString> mReplacementList;

    Help *help;

private slots:
	void requestCitation(); //emits needCitation with selected text
	void openExternalFile();
	void openPackageDocumentation(QString package = QString());
	void emitChangeDiff();
	void emitGotoDefinitionFromAction();
	void emitFindLabelUsagesFromAction();
	void emitSyncPDFFromAction();
	void lineMarkClicked(int line);
	void lineMarkToolTip(int line, int mark);
	void triggeredThesaurus();
	void reloadSpeller();
	void changeSpellingDict(const QString &name);
	void copyImageFromAction();
	void saveImageFromAction();

public slots:
	void cleanBib();

	void jumpChangePositionBackward();
	void jumpChangePositionForward();

	void jumpToBookmark(int bookmarkNumber);
	bool toggleBookmark(int bookmarkNumber, QDocumentLine line = QDocumentLine());

	void foldEverything(bool unFold);
	void foldLevel(bool unFold, int level);
	void foldBlockAt(bool unFold, int line);

	Q_INVOKABLE void zoomIn();
	Q_INVOKABLE void zoomOut();
	Q_INVOKABLE void resetZoom();

    void mayNeedToOpenCompleter(bool fromSingleChar=false);
	void documentContentChanged(int linenr, int count);
    void reCheckSyntax(int linenr, int count=-1);

private slots:
    void lineDeleted(QDocumentLineHandle *l,int hint=-1);
	void textReplaceFromAction();
    void spellCheckingAddToDict();
    void spellCheckingIgnoreAll();
	void populateSpellingMenu();
	void addReplaceActions(QMenu *menu, const QStringList &replacements, bool italic);
	void addSpellingActions(QMenu *menu, QString word, bool dedicatedMenu);

public slots:
	void spellRemoveMarkers(const QString &newIgnoredWord);
	void mouseHovered(QPoint pos);
	bool closeElement();
	void insertHardLineBreaks(int newLength, bool smartScopeSelection, bool joinLines);
public:
	enum LineSorting {SortAscending = 0, SortDescending, SortNone, SortRandomShuffle};

    void checkForLinkOverlay(QDocumentCursor cursor);
    bool hasLinkOverlay() const { return linkOverlay.isValid(); }
    const LinkOverlay &getLinkOverlay() const { return linkOverlay; }

	void sortSelectedLines(LineSorting sorting, Qt::CaseSensitivity caseSensitivity, bool completeLines, bool removeDuplicates);
	void viewActivated();
	void clearOverlays();
	void paste();
	void insertSnippet(QString text);

	void deleteLines(bool toStart, bool toEnd);
    void cutLines();
	void moveLines(int delta);
	QList<QPair<int, int> > getSelectedLineBlocks();
	static QMultiMap<int, QDocumentCursor* > getSelectedLines(QList<QDocumentCursor>& cursors);
	void alignMirrors();

private:
	void setLinkOverlay(const LinkOverlay &overlay);
	void removeLinkOverlay();
	bool isNonTextFormat(int format);
	QString extractMath(QDocumentCursor cursor);
	bool moveToCommandStart (QDocumentCursor &cursor, QString commandPrefix);
	bool showMathEnvPreview(QDocumentCursor cursor, QString command, QString environment, QPoint pos);
    QString findEnclosedMathText(QDocumentCursor cursor, QString command);

public slots:
	void temporaryHighlight(QDocumentCursor cur);
	void removeTemporaryHighlight();

	void displayLineGrammarErrorsInternal(int lineNr, const QList<GrammarError> &errors);
    void lineGrammarChecked(LatexDocument *doc, QDocumentLineHandle *line, int lineNr, const QList<GrammarError> &errors);
	void updateGrammarOverlays();

	void bibtexSectionFound(QString content);

public:
	static void setGrammarOverlayDisabled(int type, bool show);

	bool isInMathHighlighting(const QDocumentCursor &cursor);
	void checkRTLLTRLanguageSwitching();

signals:
	void lineHandleDeleted(QDocumentLineHandle *l);
	void showMarkTooltipForLogMessage(QList<int> logMessages);
	void needCitation(const QString &id);//request a new citation
	void showPreview(const QString &text);
	void showPreview(const QDocumentCursor &c);
	void showImgPreview(const QString &fileName);
	void showFullPreview();
	void openFile(const QString &name);
	void openFile(const QString &baseName, const QString &defaultExtension);
	void openCompleter();
	void thesaurus(int line, int col);
	void changeDiff(QPoint pt);
	void spellerChanged(const QString &name);
	void gotoDefinition(QDocumentCursor c);
	void findLabelUsages(LatexDocument *contextDoc, const QString &labelText);
	void syncPDFRequested(QDocumentCursor c);
	void bookmarkRemoved(QDocumentLineHandle *dlh);
	void bookmarkAdded(QDocumentLineHandle *dlh, int nr);
	void saveCurrentCursorToHistoryRequested();
	void execMacro(const Macro &macro, const MacroExecContext &context);

	void mouseBackPressed();
	void mouseForwardPressed();
	void cursorChangeByMouse();
        void focusReceived();

    void linesChanged(QString language, LatexDocument *doc, const QList<LineInfo> &lines, int firstLineNr);
	void searchBibtexSection(QString file, QString bibId);
	void openInternalDocViewer(QString package, QString command = "");

	void showExtendedSearch();

private slots:
	void lineMarkContextMenuRequested(int lineNumber, QPoint globalPos);
	void foldContextMenuRequested(int lineNumber, QPoint globalPos);
};
//Q_DECLARE_METATYPE(LatexEditorView *)


class BracketInvertAffector: public PlaceHolder::Affector
{
public:
	virtual QString affect(const QKeyEvent *e, const QString &base, int ph, int mirror) const;
	static BracketInvertAffector *instance();
};
#endif
