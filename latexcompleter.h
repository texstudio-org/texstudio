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

#include <qwidget.h>
#include <qfont.h>
#include <qcolor.h>

#include "qcodeedit.h"
#include "qeditor.h"

#include <QListView>
//#include "qpanel.h"

class CompletionWord {
public:
	CompletionWord():cursorPos(-1),anchorPos(-1) {}
	CompletionWord(const CompletionWord &cw):word(cw.word),sortWord(cw.sortWord),shownWord(cw.shownWord),cursorPos(cw.cursorPos),anchorPos(cw.anchorPos),descriptiveParts(cw.descriptiveParts) {}
	CompletionWord(const QString &newWord);//see cpp
	bool operator< (const CompletionWord &cw) const {
		return cw.sortWord > sortWord;
	}
	bool operator== (const CompletionWord &cw) const {
		return cw.word == word;
	}

	QString word,sortWord,shownWord;
	int cursorPos; //-1 => not defined
	int anchorPos;
	QList<QPair<int, int> > descriptiveParts; //used to draw

	void insertAt(QEditor* editor, QDocumentCursor cursor);
};
Q_DECLARE_METATYPE(CompletionWord)
//class CompleterInputBinding;
class CompletionListModel : public QAbstractListModel {
	Q_OBJECT

public:
	CompletionListModel(QObject *parent = 0): QAbstractListModel(parent) {}

	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

private:
	friend class LatexCompleter;
	QList<CompletionWord> words;
	QString curWord;
	void setWords(const QList<CompletionWord> & baselist, const QString &word);
};


class LatexCompleter : public QObject  {
	Q_OBJECT
public:
	LatexCompleter(QObject *p = 0);
	virtual ~LatexCompleter();

	void complete(QEditor *newEditor, bool forceVisibleList, bool normalText=false);
	void setWords(const QStringList &newwords, bool normalTextList=false);
	QList<CompletionWord> getWords() const {
		return words;
	}

	static void parseHelpfile(QString text);
	static bool hasHelpfile();
private:
	friend class CompleterInputBinding;
	static int maxWordLen;
	static QList<CompletionWord> words;
	static QList<CompletionWord> wordsText, wordsCommands;
	static QSet<QChar> acceptedChars;
	QListView * list;
	CompletionListModel* listModel;
	QEditor *editor;

	void updateList(QString word);
	bool acceptChar(QChar c,int pos);

	static QString helpFile;
	static QHash<QString, QString> helpIndices;
	static QHash<QString, int> helpIndicesCache;
private slots:
	void cursorPositionChanged();
	void selectionChanged(const QModelIndex & index);
	void editorDestroyed();
};

#endif
