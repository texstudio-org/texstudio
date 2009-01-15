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

#include "QCodeEdit/qcodeedit.h"
#include "QCodeEdit/qeditor.h"
#include "QCodeEdit/qcodecompletionengine.h"

#include <QListView>
//#include "QCodeEdit/qpanel.h"

//class CompleterInputBinding;
class CompletionListModel : public QAbstractListModel
 {
     Q_OBJECT

 public:
    CompletionListModel(QObject *parent = 0): QAbstractListModel(parent){}

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

 private:
     friend class LatexCompleter;
     QStringList words;
     QString curWord;
     void setWords(QStringList baselist, QString word);
};


class LatexCompleter : public QCodeCompletionEngine  {
   Q_OBJECT
public:
	LatexCompleter(QObject *p = 0);
	//virtual ~LatexCompleter();
  
    void complete(const QDocumentCursor& c, const QString& trigger);
    void setWords(const QStringList &newwords);

	virtual QCodeCompletionEngine* clone();
	virtual QString language() const;
    virtual QStringList extensions() const;

//public:
  //friend class CompleterInputBinding;
    QStringList words;
    QListView * list;
    QAbstractListModel* listModel;
    void updateList(QString word);
    bool acceptChar(QChar c,int pos);
};

#endif
