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


Scanner::Scanner(QObject *parent) : QObject(parent), scanner(NULL)
{

}

Scanner::~Scanner()
{
	clear();
}

Scanner::Scanner(const QString &filename, QObject *parent) : QObject(parent), scanner(NULL)
{
	load(filename);
}

bool Scanner::load(const QString &filename)
{
	clear();
	scanner = synctex_scanner_new_with_output_file(QFile::encodeName(filename).data(), NULL, 1);
	return scanner != NULL;
}

bool Scanner::clear()
{
	if (scanner) {
		synctex_scanner_free(scanner);
	}
	scanner = NULL;
}

QString Scanner::synctexFilename() const
{
	return QFile::decodeName(synctex_scanner_get_synctex(scanner));
}

QFileInfo Scanner::getNameFileInfo(const QDir &curDir, const Node &node, const char **rawName)
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

NodeIterator Scanner::displayQuery(const char *name, int line, int column, int page_hint)
{
	return NodeIterator(synctex_iterator_new_display(scanner, name, line, column, page_hint));
}

NodeIterator Scanner::editQuery(int page, float h, float v)
{
	return NodeIterator(synctex_iterator_new_edit(scanner, page, h, v));
}

Node Scanner::inputNode()
{
	return Node(synctex_scanner_input(scanner));
}


}  // namespace QSynctex



