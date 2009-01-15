/****************************************************************************
**
** Copyright (C) 2006-2008 fullmetalcoder <fullmetalcoder@hotmail.fr>
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

#ifndef _QLANGUAGE_DEFINITION_H_
#define _QLANGUAGE_DEFINITION_H_

#include "qce-config.h"

/*!
	\file qlanguagedefinition.h
	\brief Definition of the QLanguageDefinition class.
	
	\see QLanguageDefinition
*/

#include "qformat.h"

#include <QStringList>

class QKeyEvent;
class QDocument;
class QDocumentCursor;

class QCE_EXPORT QLanguageDefinition
{
	public:
		/// Collapse state of a line
		enum CollapseFlag
		{
			None		= 0x00000000,		///< The line cannot be collapsed nor expanded
			Collapsible	= 0x01000000,		///< The line is expanded and can thus be collapsed
			Collapsed	= 0x02000000,		///< The line is collapsed and can thus be expanded
			Closure		= 0x04000000,		///< The line is expanded and mark the end of a block
			
			DataSign	= 0x08000000,
			DataMask	= 0x00ffffff
		};
		
		Q_DECLARE_FLAGS(CollapseState, CollapseFlag);
		
		QLanguageDefinition();
		virtual ~QLanguageDefinition();
		
		virtual QString language() const = 0;
		virtual QStringList extensions() const = 0;
		
		virtual int tokenize(QDocument *d, int line, int count);
		
		virtual QString singleLineComment() const;
		
		virtual void match(QDocumentCursor& c);
		virtual void clearMatches(QDocument *d);
		
		virtual QString indent(const QDocumentCursor& c);
		virtual bool unindent (const QDocumentCursor& c, QKeyEvent *k);
		
		virtual void expand(QDocument *d, int line);
		virtual void collapse(QDocument *d, int line);
		virtual int blockFlags(QDocument *d, int line, int depth = 0) const;
};

#endif // _QLANGUAGE_DEFINITION_H_
