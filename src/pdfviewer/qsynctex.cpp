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

#include "qsynctex.h"

#include <QDir>

#include <synctex_parser_c-auto.h>
#include "synctex_parser_utils.h"


namespace QSynctex {


QRectF Node::boxVisibleRect() const
{
	return QRectF(synctex_node_box_visible_h(node),
	              synctex_node_box_visible_v(node) - synctex_node_box_visible_height(node),
	              synctex_node_box_visible_width(node),
	              synctex_node_box_visible_height(node) + synctex_node_box_visible_depth(node));
}


Scanner::Scanner(QObject *parent) : QObject(parent), scanner(nullptr)
{

}

Scanner::~Scanner()
{
	clear();
}

Scanner::Scanner(const QString &filename, QObject *parent) : QObject(parent), scanner(nullptr)
{
	load(filename);
}

bool Scanner::load(const QString &filename)
{
	clear();
    scanner = synctex_scanner_new_with_output_file(QFile::encodeName(filename).data(), nullptr, 1);
    return scanner != nullptr;
}

void Scanner::clear()
{
	if (scanner) {
		synctex_scanner_free(scanner);
	}
    scanner = nullptr;
}

QString Scanner::synctexFilename() const
{
	return QFile::decodeName(synctex_scanner_get_synctex(scanner));
}

QFileInfo Scanner::getNameFileInfo(const QDir &curDir, const Node &node, const char **rawName) const
{
	QFileInfo fileinfo;

	const char *synctex_name = synctex_scanner_get_name(scanner, synctex_node_tag(node.node));
	if (rawName) *rawName = synctex_name;
	if (!synctex_name) return QFileInfo();

	fileinfo = QFileInfo(curDir, QFile::decodeName(synctex_name)); //old synctex
	if (fileinfo.exists()) return fileinfo;

	fileinfo = QFileInfo(curDir, QString::fromUtf8(synctex_name)); //new synctex
	if (fileinfo.exists()) return fileinfo;

	fileinfo = QFileInfo(curDir, QString::fromLatin1(synctex_name)); //for safety (not used afaik)
	if (fileinfo.exists()) return fileinfo;

	return QFileInfo();
}

NodeIterator Scanner::displayQuery(const char *name, int line, int column, int page_hint) const
{
	return NodeIterator(synctex_iterator_new_display(scanner, name, line, column, page_hint));
}

NodeIterator Scanner::editQuery(int page, float h, float v)
{
	return NodeIterator(synctex_iterator_new_edit(scanner, page, h, v));
}

Node Scanner::inputNode() const
{
	return Node(synctex_scanner_input(scanner));
}


//virtual
PDFSyncPoint Scanner::syncFromTeX(const TeXSyncPoint &src, const QString &pdfFilename) const
{
	PDFSyncPoint pdfPoint;
	pdfPoint.page = -1;

	// Find the name SyncTeX is using for this source file...
	const QFileInfo sourceFileInfo(src.filename);
	QDir curDir(QFileInfo(pdfFilename).canonicalPath());
	QSynctex::Node node = inputNode();
	const char *name;
	bool found = false;
	while (node.isValid()) {
		QFileInfo fi = getNameFileInfo(curDir, node, &name);
		if (fi == sourceFileInfo) {
			found = true;
			break;
		}

		node = node.sibling();
	}
	if (!found)
		return pdfPoint;

	pdfPoint.filename = pdfFilename;

	QSynctex::NodeIterator iter = displayQuery(name, src.line, src.column, 0);  // TODO: page_hint set to 0 , please fix/optimize
	while (iter.hasNext()) {
		QSynctex::Node node = iter.next();
		if (pdfPoint.page < 0)
			pdfPoint.page = node.page();
		if (node.page() != pdfPoint.page)
			continue;
		pdfPoint.rects.append(node.boxVisibleRect());
	}

	return pdfPoint;
}


void debugNodeTree(QSynctex::Node node, int level)
{
	if (!node.isValid())
		return;
	qDebug() << QString(2*level, ' ') << node;
	debugNodeTree(node.child(), level + 1);
	debugNodeTree(node.sibling(), level);
}

}  // namespace QSynctex


QDebug operator<<(QDebug dbg, QSynctex::Node node)
{
	QString s = QString("Node(%1:t%2,l%3:p%4 (%5, %6 : %7, %8))").arg(node.typeName()).arg(node.tag()).arg(node.line()).arg(node.page())\
				.arg(node.visibleX()/72.).arg(node.visibleY()/72.).arg(node.visibleWidth()/72.).arg(node.visibleHeight()/72.);
	s += QString(" (%1, %2)").arg(node.x()).arg(node.y());
	dbg << qPrintable(s);
	return dbg;
}

