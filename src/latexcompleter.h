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

#ifndef Header_Latex_Completer
#define Header_Latex_Completer

#include "mostQtHeaders.h"

#include "codesnippet.h"

#include "qcodeedit.h"
#include "qeditor.h"
#include "directoryreader.h"
#include "bibtexreader.h"
#include <set>

class CompletionListModel;
class LatexCompleterConfig;
class LatexReference;
class LatexParser;

/*!
 * \brief Implements the actual completer
 *
 * It uses codesnippet, also called completionwords for inserting into text.
 * \see Codesnippet
 */
class LatexCompleter : public QObject
{
	Q_OBJECT

public:
	enum CompletionFlag {CF_FORCE_VISIBLE_LIST = 1, ///< force visible of completer
						 CF_NORMAL_TEXT = 2, ///< complete normal text words
						 CF_FORCE_REF = 4, ///< completes labels in a reference, e.g. \ref{label}
						 CF_OVERRIDEN_BACKSLASH = 8,
						 CF_FORCE_GRAPHIC = 16, ///< complete a filename for an image
						 CF_FORCE_CITE = 32, ///< complete a citation
						 CF_FORCE_PACKAGE = 64, ///< complete a package name
						 CF_FORCE_KEYVAL = 128, ///< complete key/value pair
						 CF_FORCE_SPECIALOPTION = 256,
						 CF_FORCE_LENGTH = 512,
						 CF_FORCE_REFLIST = 1024};
	Q_DECLARE_FLAGS(CompletionFlags, CompletionFlag)

    LatexCompleter(const LatexParser &latexParser, QObject *p = nullptr); ///< constructor
	virtual ~LatexCompleter();

	void complete(QEditor *newEditor, const CompletionFlags &flags); ///< initiate completion with given flags
	void setAdditionalWords(const CodeSnippetList &newwords, CompletionType completionType = CT_COMMANDS);
	void setAdditionalWords(const QSet<QString> &newwords, CompletionType completionType);
    void setAdditionalWords(const std::set<QString> &newwords, CompletionType completionType);
	void setKeyValWords(const QString &name, const QSet<QString> &newwords);
	void setContextWords(const QSet<QString> &newwords, const QString &context);
	void updateAbbreviations();

	static void setLatexReference(LatexReference *ref) { latexReference = ref; } ///< set latexreference which is used for showing help per tooltip on selecetd completion commands
	static LatexReference *getLatexReference() { return latexReference; } ///< get used latexreference

	bool acceptTriggerString(const QString &trigger);

	void setConfig(LatexCompleterConfig *config);
	LatexCompleterConfig *getConfig() const;

    void setPackageList(std::set<QString> *lst); ///< set a list with available latex package names

	bool close(); ///< close completer (without insertion)
	bool isVisible() { return list->isVisible(); }
	bool existValues(); ///< are still completion ssuggestions available

	void setWorkPath(const QString cwd) { workingDir = cwd; }
	bool completingGraphic() { return forcedGraphic; }
	bool completingKey() { return forcedKeyval; }

	int countWords();
	void setTab(int index); ///< bring given 'tab' to front

	void insertText(QString txt); ///< insert 'txt'

	void showTooltip(QString text); ///< show tooltip

signals:
	void setDirectoryForCompletion(QString fn); ///< set the used directory for filename completion
	void searchBibtexSection(QString file, QString bibId);
	void showImagePreview(QString fn); ///< show preview of selected image
	void showPreview(QString text); ///< show preview of selected item, usually references or citations

public slots:

    void bibtexSectionFound(QString content);

private:
	friend class CompleterInputBinding;
	friend class CompletionListModel;
	static LatexCompleterConfig *config;
	const LatexParser &latexParser;
	int maxWordLen;
	QListView *list;
	CompletionListModel *listModel;
	directoryReader *dirReader;
	QEditor *editor;

    std::set<QString> *packageList;

	QWidget *widget;
	QTabBar *tbBelow, *tbAbove;

	bool editorAutoCloseChars;

	void filterList(QString word, int showMostUsed = -1);
	bool acceptChar(QChar c, int pos);
	void adjustWidget();

	static LatexReference *latexReference;

	bool forcedRef;
	bool forcedGraphic;
	bool forcedCite;
	bool forcedPackage;
	bool forcedKeyval;
	bool forcedSpecialOption;
	bool forcedLength;
	bool startedFromTriggerKey;
	QString workingDir;

	QPoint lastPos;
	bibtexReader *bibReader;

private slots:
	void cursorPositionChanged();
	void selectionChanged(const QModelIndex &index);
	void editorDestroyed();
	void changeView(int pos);
	void listClicked(QModelIndex index);
	void directoryLoaded(QString dn, QSet<QString> content);
};

#endif
