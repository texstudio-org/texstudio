/***************************************************************************
 *   copyright       : (C) 2003-2007 by Pascal Brachet                     *
 *   http://www.xm1math.net/texmaker/                                      *
 *   inspired by the ktikz (GPL) program from Glad Deschrijver             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef Header_XMLTagsList_Widget
#define Header_XMLTagsList_Widget

#include <QListWidget>

class QDomElement;

struct xmlTag {
	QString txt;
	QString tag;
	int type;
};


struct xmlTagList {
	QString title, id;
	QList<xmlTag> tags;
	QList<xmlTagList> children;
};


class XmlTagsListWidget : public QListWidget
{
	Q_OBJECT

public:
	XmlTagsListWidget(QWidget *parent, QString file);
	QStringList tagsTxtFromCategory(const QString &category);
	QString tagsFromTagTxt(const QString &tagTxt);
	bool isPopulated();
	void populate();

protected:
	void showEvent ( QShowEvent *event );

private:
	xmlTagList getTags(const QDomElement &element);
	xmlTagList xmlSections;
	void addListWidgetItems(const xmlTagList &tagList);
	QString mFile;
	bool mLoaded;
};

#endif
