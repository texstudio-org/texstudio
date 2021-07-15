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
/*!
 * \brief Creates an XML tag widget
 * This widget was copied from texmaker. It generates a text based sidebar which offers an overview of available commands.
 * The commands are stored in tags/ *.xml (file)
 * \param parent
 * \param file
 */
XmlTagsListWidget::XmlTagsListWidget(QWidget *parent, QString file): QListWidget(parent)
{
	mFile = file;
	mLoaded = false;
}
/*!
 * \brief populate the widget
 * population of the widget is deferred for faster start-up.
 */
void XmlTagsListWidget::populate()
{
	if (!mLoaded) {
		QFile tagsFile(mFile);
		if (tagsFile.open(QFile::ReadOnly)) {
			QDomDocument domDocument;
			if (domDocument.setContent(&tagsFile)) {
				QDomElement root = domDocument.documentElement();
				if (root.tagName() == "texmakertags") {
					xmlSections = getTags(root);
					for (int i = 0; i < xmlSections.children.size(); ++i)
						addListWidgetItems(xmlSections.children.at(i));
				}
			}
		}
		mLoaded = true;
	}
}
/*!
 * \brief showEvent is used as trigger to populate the widget (if that has not yet happened)
 */
void XmlTagsListWidget::showEvent(QShowEvent *)
{
	if (!mLoaded)
		populate();
}
/*!
 * \brief check if population has already taken place.
 * \return true if populated
 */
bool XmlTagsListWidget::isPopulated()
{
	return mLoaded;
}
/*!
 * \brief return all entries from a given category
 * \param category
 * \return list of entries
 */
QStringList XmlTagsListWidget::tagsTxtFromCategory(const QString &category)
{
	foreach  (const xmlTagList &tags, xmlSections.children)
		if (tags.id == category) {
			QStringList result;
			foreach (const xmlTag &tag, tags.tags)
				result.append(tag.txt);
			return result;
		}
	return QStringList();
}
/*!
 * \internal
 * \brief helper for parsing xml
 * \param tagList
 * \param tagTxt
 * \return
 */
QString tagsFromTagTxtRec(const xmlTagList &tagList, const QString &tagTxt)
{
	foreach (const xmlTag &tag, tagList.tags)
		if (tag.txt == tagTxt) return tag.tag;
	QString result;
	foreach (const xmlTagList &childTagList, tagList.children) {
		result = tagsFromTagTxtRec(childTagList, tagTxt);
		if (!result.isEmpty())
			return result;
	}
	return result;
}
/*!
 * \brief translate tag/gui text to actual tag/code
 * \param tagTxt
 * \return
 */
QString XmlTagsListWidget::tagsFromTagTxt(const QString &tagTxt)
{
	return tagsFromTagTxtRec(xmlSections, tagTxt);
}
/*!
 * \internal
 * \brief parse xml
 * \param element
 * \return
 */
xmlTagList XmlTagsListWidget::getTags(const QDomElement &element)
{
	xmlTag item;
	xmlTagList tagList;
	QList<xmlTag> tags;
	tagList.title = element.attribute("title");
	tagList.id = element.attribute("id");
	QDomElement child = element.firstChildElement("item");
    QString txt, code;
	while (!child.isNull()) {
		code = child.attribute("tag");
		code.replace("\\\\", "\\");
		code.replace("&lt;", "<");
		code.replace("&gt;", ">");
		item.tag = code;
		txt = child.attribute("txt");
		if (txt != "") {
			txt.replace("\\\\", "\\");
			txt.replace("&lt;", "<");
			txt.replace("&gt;", ">");
		} else txt = code;
        item.txt = txt.remove(QRegularExpression("%[<n>|]?"));
		item.type = child.attribute("type").toInt();
		tags << item;
		child = child.nextSiblingElement("item");
	}
	tagList.tags = tags;
	QDomElement section = element.firstChildElement("section");
	while (!section.isNull()) {
		tagList.children << getTags(section);
		section = section.nextSiblingElement("section");
	}
	return tagList;
}
/*!
 * \internal
 * \brief set-up the widget items
 * \param tagList
 */
void XmlTagsListWidget::addListWidgetItems(const xmlTagList &tagList)
{
	QFont titleFont = qApp->font();
	titleFont.setBold(true);
	QFont optionFont = qApp->font();
	optionFont.setItalic(true);
	QFont commandFont = qApp->font();
	QListWidgetItem *item = new QListWidgetItem(this);
	QString itemText = tr(qPrintable(tagList.title));
	item->setText(itemText);
    item->setBackground(QBrush(QColor(0x44,0x7B,0xCD)));
    item->setForeground(QBrush(QColor(0xff,0xff,0xff)));
	item->setFont(titleFont);
	for (int i = 0; i < tagList.tags.size(); ++i) {
		QListWidgetItem *item = new QListWidgetItem(this);
		QString itemText = tr(qPrintable(tagList.tags.at(i).txt));
		item->setText(itemText);
		item->setData(Qt::UserRole, tagList.tags.at(i).tag);
		if (tagList.tags.at(i).type == 0) item->setFont(commandFont);
		else item->setFont(optionFont);
	}
	//TODO: use QListView, and CompletionItemDelegate from latexcompleter to highlight temporary code completion
}
