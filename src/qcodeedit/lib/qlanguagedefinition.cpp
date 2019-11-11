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
#include "qdocumentcursor.h"
#include "qdocumentline.h"
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

int QLanguageDefinition::parenthesisWeight(int id) const{
	Q_UNUSED(id)
	return 0;
}

bool QLanguageDefinition::possibleEndingOfOpeningParenthesis(const QString& text) const{
	Q_UNUSED(text)
	return false;
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
QString QLanguageDefinition::indent(const QDocumentCursor& c, int* indentCount)
{
	Q_UNUSED(c)
	Q_UNUSED(indentCount)

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

bool QLanguageDefinition::correctFolding(QDocument *d){
	Q_UNUSED(d)

	return false;
}

QFoldedLineIterator QLanguageDefinition::foldedLineIterator(QDocument *d, int line) const{
	QFoldedLineIterator fli;
	fli.doc=d;
	fli.def=this;
	fli.hidden=false;
	fli.hiddenDepth=0;
	for (fli.lineNr=-1;fli.lineNr<line;++fli);
	return fli;
}

QFoldedLineIterator& QFoldedLineIterator::operator++(){
	open = 0;
	close = 0;
	lineNr++;
	line=doc->line(lineNr);
	if (!line.isValid())
		return *this;
	int oldHiddenDepth=hiddenDepth;
	int maxClosedParenthesisWeight=0, maxClosedHiddenParenthesisWeight=0;
	collapsedBlockStart=line.hasFlag(QDocumentLine::CollapsedBlockStart);
	foreach (const QParenthesis& par, line.parentheses()){
		if (!(par.role & QParenthesis::Fold))
			continue;
		if (par.role & QParenthesis::Close && !openParentheses.empty()) {
			if (openParentheses.last().id==par.id) {
				//Close last bracket
				if (openParentheses.last().line != lineNr) {
					close++;
					if (openParentheses.last().hiding) {
						hiddenDepth--;
						maxClosedHiddenParenthesisWeight=qMax(maxClosedHiddenParenthesisWeight, openParentheses.last().weight);
					} else
						maxClosedParenthesisWeight=qMax(maxClosedHiddenParenthesisWeight, openParentheses.last().weight);
				} else open--;
				openParentheses.removeLast();
			} else {
				//Close a matching bracket if there are only "lighter" brackets in-between
				int weight=def->parenthesisWeight(par.id);
				int removedHidingBrackets=0;
				int removedOwnBrackets=0;
				int removedMaxClosedPW = 0;
				int removedMaxClosedHiddenPW = 0;
				for (int i=openParentheses.size()-1;i>=0;i--){
					if (openParentheses[i].weight>weight) break;
					if (openParentheses[i].line == lineNr) removedOwnBrackets++;
					else if (openParentheses[i].hiding) {
						removedHidingBrackets++;
						removedMaxClosedHiddenPW=qMax(removedMaxClosedHiddenPW, openParentheses[i].weight);
					} else
						removedMaxClosedPW=qMax(removedMaxClosedPW, openParentheses[i].weight);
					if ( openParentheses[i].weight==weight ) {
						if ( openParentheses[i].id!=par.id ) break;
						open-=removedOwnBrackets;
						close+=(openParentheses.size()-i) - removedOwnBrackets;
						hiddenDepth-=removedHidingBrackets;
						openParentheses.erase(openParentheses.begin()+i,openParentheses.end());
						maxClosedParenthesisWeight=qMax(maxClosedParenthesisWeight, removedMaxClosedPW);
						maxClosedHiddenParenthesisWeight=qMax(maxClosedHiddenParenthesisWeight, removedMaxClosedHiddenPW);
						break;
					}
				}
			}
		}
		if (par.role & QParenthesis::Open){
			//Open new bracket
			openParentheses << FoldedParenthesis(lineNr, par.id, def->parenthesisWeight(par.id), collapsedBlockStart );
			open++;
		}
	}

	collapsedBlockStart = collapsedBlockStart  && open;
	collapsedBlockEnd = hiddenDepth!=oldHiddenDepth;
	hiddenCollapsedBlockEnd = oldHiddenDepth>0 && !open && maxClosedParenthesisWeight <= maxClosedHiddenParenthesisWeight;

	hidden = (hiddenDepth>0) || //line contained in a hidden block
		 (hiddenDepth==0 && hiddenCollapsedBlockEnd); //a closing bracket is hidden iff there is no new block to open

	if (collapsedBlockStart)
		hiddenDepth+=open;

	return *this;
}

bool QFoldedLineIterator::lineFlagsInvalid() const{
	return line.hasFlag(QDocumentLine::Hidden) != hidden ||
	       line.hasFlag(QDocumentLine::CollapsedBlockStart) != collapsedBlockStart ||
	       line.hasFlag(QDocumentLine::CollapsedBlockEnd) != collapsedBlockEnd;

}

void QFoldedLineIterator::incrementUntilBlockEnd(){
	int firstParenthesisPos = openParentheses.size() - open;
	const FoldedParenthesis firstParenthesis = openParentheses[firstParenthesisPos];

	while ( lineNr < doc->lines() &&
		firstParenthesisPos < openParentheses.size() &&
		openParentheses[firstParenthesisPos] == firstParenthesis ){
		++(*this);
	}
}

/*! @} */
