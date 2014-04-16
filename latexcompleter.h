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

#ifndef LATEXCOMPLETER_H
#define LATEXCOMPLETER_H

#include "mostQtHeaders.h"

#include "codesnippet.h"

#include "qcodeedit.h"
#include "qeditor.h"
#include "latexeditorview.h"
#include "directoryreader.h"
#include "bibtexreader.h"

//#include "qdocumentline_p.h"


class CompletionListModel;
class LatexCompleterConfig;
class LatexReference;
//class Reference;

class LatexCompleter : public QObject  {
	Q_OBJECT
public:
    enum CompletionFlag { CF_FORCE_VISIBLE_LIST = 1, CF_NORMAL_TEXT = 2, CF_FORCE_REF = 4, CF_OVERRIDEN_BACKSLASH=8,CF_FORCE_GRAPHIC = 16, CF_FORCE_CITE = 32, CF_FORCE_PACKAGE = 64};
	Q_DECLARE_FLAGS(CompletionFlags, CompletionFlag);
	
	LatexCompleter(const LatexParser& latexParser, QObject *p = 0);
	virtual ~LatexCompleter();
	
	void complete(QEditor *newEditor, const CompletionFlags &flags);
	void setAdditionalWords(const QSet<QString> &newwords, CompletionType completionType=CT_COMMANDS);
    void setKeyValWords(const QString &name,const QSet<QString> &newwords);
	void updateAbbreviations();
	
	static void setLatexReference(LatexReference *ref) {latexReference = ref;}
	static LatexReference * getLatexReference() {return latexReference;}
	
	bool acceptTriggerString(const QString& trigger);
	
	void setConfig(LatexCompleterConfig* config);
	LatexCompleterConfig* getConfig() const;

    void setPackageList(QSet<QString> *lst);
	
	bool close();
	bool isVisible(){
		return list->isVisible();
	}
	
	void setWorkPath(const QString cwd){
		workingDir=cwd;
	}
	bool completingGraphic(){
		return forcedGraphic;
	}
	
	int countWords();
	void setTab(int index);
	
	void insertText(QString txt);
signals:
	void setDirectoryForCompletion(QString fn);
	void searchBibtexSection(QString file,QString bibId);
    void showImagePreview(QString fn);
private:
	friend class CompleterInputBinding;
	friend class CompletionListModel;
	static LatexCompleterConfig* config;
	const LatexParser& latexParser;
	int maxWordLen;
	QListView * list;
	CompletionListModel* listModel;
	directoryReader *dirReader;
	QEditor *editor;

    QSet<QString> *packageList;

	QWidget *widget;
	QTabBar *tbBelow,*tbAbove;
	
	bool editorAutoCloseChars;
	
	void filterList(QString word,int showMostUsed=-1);
	bool acceptChar(QChar c,int pos);
	void adjustWidget();
	
	static LatexReference *latexReference;
	
	bool forcedRef;
	bool forcedGraphic;
	bool forcedCite;
    bool forcedPackage;
    bool startedFromTriggerKey;
	QString workingDir;
	
	QPoint lastPos;
	bibtexReader *bibReader;
	
	void showTooltip(QString topic);

private slots:
	void cursorPositionChanged();
	void selectionChanged(const QModelIndex & index);
	void editorDestroyed();
	void changeView(int pos);
	void listClicked(QModelIndex index);
	void directoryLoaded(QString dn,QSet<QString> content);
    void bibtexSectionFound(QString content);
};

#endif
