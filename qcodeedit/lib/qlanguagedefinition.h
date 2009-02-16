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

#define QCE_FOLD_FLAGS(flags, open, close) ((flags) | (open & QLanguageDefinition::OpenMask) | ((close << 12) & QLanguageDefinition::CloseMask))
#define QCE_FOLD_OPEN_COUNT(flags) ((flags) & QLanguageDefinition::OpenMask)
#define QCE_FOLD_CLOSE_COUNT(flags) (((flags) & QLanguageDefinition::CloseMask) >> 12)

class QCE_EXPORT QLanguageDefinition
{
	public:
		/// Collapse state of a line
		enum CollapseFlag
		{
			None		= 0x00000000,		///< The line cannot be collapsed nor expanded
			Collapsible	= 0x10000000,		///< The line is expanded and can thus be collapsed
			Collapsed	= 0x20000000,		///< The line is collapsed and can thus be expanded
			Closure		= 0x40000000,		///< The line is expanded and mark the end of a block
			
			CloseMask	= 0x00fff000,		///< Number of actual closing fold mark
			OpenMask	= 0x00000fff		///< Number of actual open fold mark
		};
		
		Q_DECLARE_FLAGS(CollapseState, CollapseFlag);
		
		QLanguageDefinition();
		virtual ~QLanguageDefinition();
		
		virtual QString language() const = 0;
		virtual QStringList extensions() const = 0;
		
		virtual int tokenize(QDocument *d, int line, int count);
		
		virtual QString singleLineComment() const;
		
		virtual QString defaultLineMark() const;
		
		virtual void match(QDocumentCursor& c);
		virtual void clearMatches(QDocument *d);
		
		virtual QString indent(const QDocumentCursor& c);
		virtual bool unindent (const QDocumentCursor& c, const QString& ktxt);
		
		virtual void expand(QDocument *d, int line);
		virtual void collapse(QDocument *d, int line);
		virtual int blockFlags(QDocument *d, int line, int depth = 0) const;
};

#endif // _QLANGUAGE_DEFINITION_H_
