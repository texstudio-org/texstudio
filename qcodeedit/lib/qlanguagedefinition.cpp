/****************************************************************************
**
** Copyright (C) 2006-2009 fullmetalcoder <fullmetalcoder@hotmail.fr>
**
** This file is part of the Edyuk project <http://edyuk.org>
**
** This file may be used under the terms of the GNU General Public License
** version 3 as published by the Free Software Foundation and appearing in the
** file GPL.txt included in the packaging of this file.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#include "qlanguagedefinition.h"

/*!
	\file qlanguagedefinition.cpp
	\brief Implementation of QLanguageDefinition

	\see QLanguageDefinition
*/

/*!
	\ingroup language
	@{

	\class QLanguageDefinition
	\brief Interface for language definition.

	This class is meant to be subclassed, see \see QGenericDefinition for more
	informations, and added to a QLanguageFactory.

	A language definition is a wrapper that creates interfaces for a given file
	extension from internally handled data (XML files in the case of
	QGenericDefinition)

	\see QLanguageFactory
*/

#include "qdocument.h"
#include "qdocumentline.h"
#include "qdocumentcursor.h"

#include "qlanguagefactory.h"

/*!
	\brief Empty constructor
*/
QLanguageDefinition::QLanguageDefinition()
{
}

/*!
	\brief Empty destructor
*/
QLanguageDefinition::~QLanguageDefinition()
{
}

/*!
	\fn QLanguageDefinition::language()

	\return The language supported by this definition
*/

/*!
	\fn QLanguageDefinition::extensions()

	\return the file extensions corrseponding to the supported language

	\see language()
	\see QFileInfo::completeSuffix()
*/

/*!
	\brief Entry point for syntax highlighting
*/
int QLanguageDefinition::tokenize(QDocument *d, int line, int count)
{
	Q_UNUSED(d)
	Q_UNUSED(line)
	
	return count;
}

/*!
	\brief Return the string starting a single line comment, if any offered by the language
*/
QString QLanguageDefinition::singleLineComment() const
{
	return QString();
}

/*!
	\brief Let language specify which line mark should be toggled by left clicking a line mark panel
*/
QString QLanguageDefinition::defaultLineMark() const
{
	return QString();
}

/*!
	\brief Brace matching entry point
*/
void QLanguageDefinition::clearMatches(QDocument *d)
{
	Q_UNUSED(d)
}

/*!
	\brief Brace matching entry point
*/
void QLanguageDefinition::match(QDocumentCursor& c)
{
	Q_UNUSED(c)
}

/*!
	\brief Return the indent to use when inserting a line at a given cursor position
*/
QString QLanguageDefinition::indent(const QDocumentCursor& c)
{
	Q_UNUSED(c)

	return QString();
}

/*!
	\brief Determines whether the given key event at the given position should cause unindent to happen
*/
bool QLanguageDefinition::unindent (const QDocumentCursor& c, const QString& ktxt)
{
	Q_UNUSED(c)
	Q_UNUSED(ktxt)

	return false;
}

/*!
	\brief Expand a collapsed block at a given line
*/
void QLanguageDefinition::expand(QDocument *d, int line)
{
	Q_UNUSED(d)
	Q_UNUSED(line)
}

/*!
	\brief Collapse a text block at a given line
*/
void QLanguageDefinition::collapse(QDocument *d, int line)
{
	Q_UNUSED(d)
	Q_UNUSED(line)
}

/*!
	\brief Compute the collapse state of a line
*/
int QLanguageDefinition::blockFlags(QDocument *d, int line, int depth) const
{
	Q_UNUSED(d)
	Q_UNUSED(line)
	Q_UNUSED(depth)

	return 0;
}

/*! @} */
