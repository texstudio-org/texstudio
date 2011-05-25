/***************************************************************************
 *   copyright       : (C) 2003-2009 by Pascal Brachet                     *
 *   http://www.xm1math.net/texmaker/                                      *
 *   inspired by the ktikz (GPL) program from Glad Deschrijver             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "xmltagslistwidget.h"

#include <QListWidget>
#include <QFont>
#include <QColor>
#include <QDomDocument>
#include <QFile>
#include <QApplication>
#include <QDebug>

XmlTagsListWidget::XmlTagsListWidget(QWidget *parent, QString file):QListWidget(parent){
	mFile=file;
	mLoaded=false;
}

void XmlTagsListWidget::populate(){
    if(!mLoaded){
	QFile tagsFile(mFile);
	if (tagsFile.open(QFile::ReadOnly)){
	    QDomDocument domDocument;
	    if (domDocument.setContent(&tagsFile)){
		QDomElement root = domDocument.documentElement();
		if (root.tagName() == "texmakertags"){
		    xmlSections=getTags(root);
		    for (int i = 0; i < xmlSections.children.size(); ++i)
			addListWidgetItems(xmlSections.children.at(i));
		}
	    }
	}
	mLoaded=true;
    }
}

void XmlTagsListWidget::showEvent(QShowEvent *){
    if(!mLoaded)
	populate();
}

bool XmlTagsListWidget::isPopulated(){
    return mLoaded;
}

QStringList XmlTagsListWidget::tagsTxtFromCategory(const QString & category){
	foreach  (const xmlTagList &tags, xmlSections.children)
		if (tags.id==category) {
			QStringList result;
			foreach (const xmlTag& tag, tags.tags)
				result.append(tag.txt);
			return result;
		}
	return QStringList();
}

QString tagsFromTagTxtRec(const xmlTagList& tagList, const QString& tagTxt){
	foreach (const xmlTag& tag, tagList.tags)
		if (tag.txt == tagTxt) return tag.tag;
	QString result;
	foreach (const xmlTagList& childTagList, tagList.children){
		result = tagsFromTagTxtRec(childTagList, tagTxt);
		if (!result.isEmpty())
			return result;
	}
	return result;
}

QString XmlTagsListWidget::tagsFromTagTxt(const QString& tagTxt){
	return tagsFromTagTxtRec(xmlSections, tagTxt);
}

xmlTagList XmlTagsListWidget::getTags(const QDomElement &element){
	xmlTag item;
	xmlTagList tagList;
	QList<xmlTag> tags;
	tagList.title = element.attribute("title");
	tagList.id = element.attribute("id");
	QDomElement child = element.firstChildElement("item");
	QString txt, code, type;
	while (!child.isNull()){
		code = child.attribute("tag");
		code.replace("\\\\", "\\");
		code.replace("&lt;", "<");
		code.replace("&gt;", ">");
		item.tag=code;
		txt = child.attribute("txt");
		if (txt!=""){
			txt.replace("\\\\", "\\");
			txt.replace("&lt;", "<");
			txt.replace("&gt;", ">");
		} else txt=code;
		item.txt=txt.remove(QRegExp("%[<n>|]?"));
		item.type=child.attribute("type").toInt();
		tags << item;
		child = child.nextSiblingElement("item");
	}
	tagList.tags=tags;
	QDomElement section = element.firstChildElement("section");
	while (!section.isNull()){
		tagList.children << getTags(section);
		section = section.nextSiblingElement("section");
	}
	return tagList;
}

void XmlTagsListWidget::addListWidgetItems(const xmlTagList &tagList)
{
	QFont titleFont = qApp->font();
	titleFont.setBold(true);
	QFont optionFont=qApp->font();
	optionFont.setItalic(true);
	QFont commandFont=qApp->font();
	//QColor titleBg(QApplication::style()->standardPalette().color(QPalette::Normal, QPalette::Highlight));
	//QColor titleFg(QApplication::style()->standardPalette().color(QPalette::Normal, QPalette::HighlightedText));
	QColor titleBg("#447BCD");
	QColor titleFg("#ffffff");
	QListWidgetItem *item = new QListWidgetItem(this);
	QString itemText = tagList.title;
	item->setText(itemText);
	item->setBackgroundColor(titleBg);
	item->setTextColor(titleFg);
	item->setFont(titleFont);
	for (int i = 0; i < tagList.tags.size(); ++i){
		QListWidgetItem *item = new QListWidgetItem(this);
		QString itemText = tagList.tags.at(i).txt;
		item->setText(itemText);
		item->setData(Qt::UserRole,tagList.tags.at(i).tag);
		if (tagList.tags.at(i).type==0) item->setFont(commandFont); 
		else item->setFont(optionFont);
	}
	//TODO: use QListView, and CompletionItemDelegate from latexcompleter to highlight temporary code completion
}
