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

#ifndef LATEXEDITORVIEW_H
#define LATEXEDITORVIEW_H

#include "mostQtHeaders.h"

#include "spellerutility.h"

#include "qcodeedit.h"
#include "qeditor.h"
#include "qeditorinputbinding.h"
#include "qlinemarkpanel.h"
#include "qlinenumberpanel.h"

class References {
public:
	References() {}
	References(QString pattern) : mPattern(pattern) {}
	void insert(QString key,QDocumentLineHandle* handle) {mReferences.insert(key,handle);}
	QList<QDocumentLineHandle*> values(QString key) {return mReferences.values(key);}
	bool contains(QString key) {return mReferences.contains(key);}
	int count(QString key) {return mReferences.count(key);}
	QStringList removeByHandle(QDocumentLineHandle* handle);
	void removeUpdateByHandle(QDocumentLineHandle* handle,References* altRefs=0);
	void updateByKeys(QStringList refs,References* altRefs=0);
	void setPattern(QString pattern) {mPattern=pattern;}
	QString pattern() {return mPattern;}
	void setFormats(int multiple,int single,int none) {
		referenceMultipleFormat=multiple;
		referencePresentFormat=single;
		referenceMissingFormat=none;
	}
protected:
	QMultiHash<QString,QDocumentLineHandle*> mReferences;
	int referenceMultipleFormat,referencePresentFormat,referenceMissingFormat;
	QString mPattern;
};

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

class LatexCompleter;
class LatexEditorView : public QWidget  {
	Q_OBJECT
public:

	LatexEditorView(QWidget *parent);
	~LatexEditorView();

	QCodeEdit *codeeditor;
	QEditor *editor;


//  FindWidget *findwidget;
	//Functions affecting the editor

	void complete(bool forceVisibleList, bool normalText=false, bool forceRef=false);
	void jumpChangePositionBackward();
	void jumpChangePositionForward();
	void jumpToBookmark(int bookmarkNumber);
	void toggleBookmark(int bookmarkNumber);

	void foldEverything(bool unFold);
	void foldLevel(bool unFold, int level);
	void foldBlockAt(bool unFold, int line);

	void cleanBib();
	static void setKeyReplacements(QStringList *UserKeyReplace, QStringList *UserKeyReplaceAfterWord, QStringList *UserKeyReplaceBeforeWord);
	static QList<QAction *> getBaseActions();
	static void setBaseActions(QList<QAction *> baseActions);
	static void setSpeller(SpellerUtility* mainSpeller);
	static void setCompleter(LatexCompleter* newCompleter);
	
	QAction *lineNumberPanelAction, *lineMarkPanelAction, *lineFoldPanel, *lineChangePanel, 
	*statusPanel, *searchReplacePanel, *gotoLinePanelAction;
	QLineMarkPanel* lineMarkPanel;
	QLineNumberPanel* lineNumberPanel;

	QMultiHash<QDocumentLineHandle*, int> lineToLogEntries;
	QHash<int, QDocumentLineHandle*> logEntryToLine;

	
	
	static int hideTooltipWhenLeavingLine;

	void setFormats(int multiple,int single,int none) {
		referenceMultipleFormat=multiple;
		referencePresentFormat=single;
		referenceMissingFormat=none;
		containedLabels.setFormats(multiple,single,none);
		containedReferences.setFormats(multiple,single,none);
	}

	int environmentFormat,referencePresentFormat,referenceMissingFormat,referenceMultipleFormat;
private:
	friend class DefaultInputBinding;
	static int bookMarkId(int bookmarkNumber);

	static SpellerUtility* speller;
	static LatexCompleter* completer;
	QList<QPair<QDocumentLine, int> > changePositions; //line, index
	int curChangePos;
	int lastSetBookmark; //only looks at 1..3 (mouse range)

	References containedLabels,containedReferences;
public slots:
	void lineMarkClicked(int line);
	void documentContentChanged(int linenr, int count);
	void lineDeleted(QDocumentLineHandle* l);
	void lineRemoved(QDocumentLineHandle* l);
	void spellCheckingReplace();
	void spellCheckingAlwaysIgnore();
	void spellCheckingListSuggestions();
	void dictionaryReloaded();
	void mouseHovered(QPoint pos);
signals:
	void lineHandleDeleted(QDocumentLineHandle* l);
};

#endif
