/*
 * This file is part of the TeXstudio (http://texstudio.org).
 * Copyright (c) 2017 Tim Hoffmann.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef Header_QSync_Tex
#define Header_QSync_Tex

#include <QObject>
#include <QFile>
#include <QFileInfo>
#include <QRectF>
#include <QDebug>

#include <synctex_parser.h>
#include <synctex_parser_advanced.h>

namespace QSynctex {


///! Describes a location in a TeX source file
struct TeXSyncPoint {
	TeXSyncPoint() : line(0), column(0) {}
	TeXSyncPoint(QString f, int ln, int col) : filename(f), line(ln), column(col) {}
	QString filename;
	int line;    // 1-based like in synctex
	int column;  // 1-based like in synctex
};

///! Describes a location on a pdf page
struct PDFSyncPoint {
	QString filename;
	int page;
	QList<QRectF> rects;
};



class Node {
	friend class Scanner;

public:
	Node(synctex_node_p n) { node = n; }
	bool isValid() const { return node != NULL; }
	int tag() const { return synctex_node_tag(node); }
	int line() const { return synctex_node_line(node); }
	int meanLine() const { return synctex_node_mean_line(node); }
	int column() const { return synctex_node_column(node); }
	int page() const { return synctex_node_page(node); }
	QString sourceFileName() { return QFile::decodeName(synctex_node_get_name(node)); }
	QString typeName() { return QString(synctex_node_isa(node)); }

	Node parent() const { return synctex_node_parent(node); }
	Node parentSheet() const { return synctex_node_parent_sheet(node); }
	Node parentForm() const { return synctex_node_parent_form(node); }
	Node child() const { return synctex_node_child(node); }
	Node lastChild() const { return synctex_node_last_child(node); }
	Node sibling() const { return synctex_node_sibling(node); }
	Node lastSibling() const { return synctex_node_last_sibling(node); }
	Node argSibling() const { return synctex_node_arg_sibling(node); }
	Node next() const { return synctex_node_next(node); }

	/* Dimensions of the node in TeX small point coordinates, with origin at the top left corner. */
	int x() const { return synctex_node_h(node); }
	int y() const { return synctex_node_v(node); }
	int width() const { return synctex_node_width(node); }
	int height() const { return synctex_node_height(node); }

	/* Dimensions of the enclosing box in TeX small point coordinates, with origin at the top left corner. */
	int boxX() const { return synctex_node_box_h(node); }
	int boxY() const { return synctex_node_box_v(node); }
	int boxWidth() const { return synctex_node_box_width(node); }
	int boxHeight() const { return synctex_node_box_height(node); }

	/* Dimensions of the node in page coordinates, with origin at the top left corner. */
	float visibleX() const { return synctex_node_visible_h(node); }
	float visibleY() const { return synctex_node_visible_v(node); }
	float visibleWidth() const { return synctex_node_visible_width(node); }
	float visibleHeight() const { return synctex_node_visible_height(node); }

	/* Dimensions of the enclosing box in page coordinates, with origin at the top left corner. */
	float boxVisibleX() const { return synctex_node_box_visible_h(node); }
	float boxVisibleY() const { return synctex_node_box_visible_v(node); }
	float boxVisibleWidth() const { return synctex_node_box_visible_width(node); }
	float boxVisibleHeight() const { return synctex_node_box_visible_height(node); }
	QRectF boxVisibleRect() const;

	void log() { synctex_node_log(node); }
	void display() { synctex_node_display(node); }

private:
	synctex_node_p node;
};


class NodeIterator {

public:
	NodeIterator(synctex_iterator_p it) { iter = it; }
	~NodeIterator() { synctex_iterator_free(iter); }

	bool hasNext() { return synctex_iterator_has_next(iter); }
	Node next() { return Node(synctex_iterator_next_result(iter)); }
	int reset() { return synctex_iterator_reset(iter); }
	int remainingCount() { return synctex_iterator_count(iter); }

private:
	synctex_iterator_p iter;
};

class Scanner : public QObject
{
	Q_OBJECT
public:
	explicit Scanner(QObject *parent = Q_NULLPTR);
	~Scanner();
	Scanner(const QString &filename, QObject *parent = Q_NULLPTR);

	bool load(const QString &filename);
	void clear();
	bool isValid() const { return scanner != NULL; }

	QString synctexFilename() const;
	QFileInfo getNameFileInfo(const QDir &curDir, const Node &node, const char **rawName = 0) const;

	NodeIterator displayQuery(const char * name, int line, int column, int page_hint) const;
	NodeIterator editQuery(int page, float h, float v);
	Node inputNode() const;

	Node sheet(int page) const { return synctex_sheet(scanner, page); }
	Node sheetContent(int page) const { return synctex_sheet_content(scanner, page); }
	Node form(int tag) const { return synctex_form(scanner, tag); }
	Node formContent(int tag) const { return synctex_form_content(scanner, tag); }

	void display() { synctex_scanner_display(scanner); }
	QString fileName(int tag) { return QFile::decodeName(synctex_scanner_get_name(scanner, tag)); }

	PDFSyncPoint syncFromTeX(const TeXSyncPoint &src, const QString &pdfFilename) const;

signals:

public slots:

private:
	synctex_scanner_p scanner;
};

void debugNodeTree(QSynctex::Node node, int level=0);

}  // namespace QSynctex


QDebug operator<<(QDebug dbg, QSynctex::Node node);

#endif // QSYNCTEX_H
