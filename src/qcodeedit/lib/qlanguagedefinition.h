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

#ifndef Header_QLanguage_Definition
#define Header_QLanguage_Definition

#include "mostQtHeaders.h"
#include "qdocumentline.h"

#include "qce-config.h"

/*!
	\file qlanguagedefinition.h
	\brief Definition of the QLanguageDefinition class.

	\see QLanguageDefinition
*/

#include "qformat.h"

class QKeyEvent;
class QDocument;
class QDocumentCursor;

#define QCE_FOLD_FLAGS(flags, open, close) ((flags) | (open & QLanguageDefinition::OpenMask) | ((close << 12) & QLanguageDefinition::CloseMask))
#define QCE_FOLD_OPEN_COUNT(flags) ((flags) & QLanguageDefinition::OpenMask)
#define QCE_FOLD_CLOSE_COUNT(flags) (((flags) & QLanguageDefinition::CloseMask) >> 12)

class QFoldedLineIterator;

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

		virtual int parenthesisWeight(int id) const;
		virtual const QStringList& openingParenthesis() const = 0;
		virtual const QStringList closingParentheses() const = 0;
		//virtual const QHash<int, QString>& closingParenthesis() const = 0;
		virtual QString getClosingParenthesis(const QString& opening) const = 0;
		virtual bool possibleEndingOfOpeningParenthesis(const QString& text) const;

		virtual void match(QDocumentCursor& c);
		virtual QList<QList<QDocumentCursor> > getMatches(const QDocumentCursor& c) const = 0;
		virtual QDocumentCursor getNextMismatch(const QDocumentCursor& scope) const = 0;
		virtual void clearMatches(QDocument *d);

		virtual QString indent(const QDocumentCursor& c, int* indentCount);
		virtual bool unindent (const QDocumentCursor& c, const QString& ktxt);

		virtual void expand(QDocument *d, int line);
		virtual void collapse(QDocument *d, int line);
		virtual bool correctFolding(QDocument *d);
		virtual QFoldedLineIterator foldedLineIterator(QDocument *d, int line=0) const;
};

struct QCE_EXPORT FoldedParenthesis{
	int line, id, weight;
	bool hiding;
	FoldedParenthesis(int l, int i, int w, bool h):line(l), id(i), weight(w), hiding(h){}
	FoldedParenthesis(const FoldedParenthesis& fp):line(fp.line), id(fp.id), weight(fp.weight), hiding(fp.hiding){}
	FoldedParenthesis& operator= (const FoldedParenthesis& fp) = default; // Silence -Wdeprecated-copy
	bool operator== (const FoldedParenthesis& other) const{
		return id==other.id && line==other.line;
	}
};

class QCE_EXPORT QFoldedLineIterator{
public:
	//All these values (except line.impl) are READ-ONLY
	//(no methods for simplicity and performance)

	//You can change the folding while the iterator exists, but
	//then hidden, hiddenDepth and collapsedBlockEnd can have
	//invalid values

	//current line
	QDocumentLine line;
	int lineNr;
	//all parentheses which are open (at the end of this line)
	QList<FoldedParenthesis> openParentheses;
	//Count of parentheses which are opened or closed in this line (excluding parentheses like {()} which are opened and closed on this line)
	int open, close;

	//if this line is hidden (actual value, independent from line flags)
	bool hidden;
	//if this line starts a collapsed block (actual value, but only true if the flag is also set)
	bool collapsedBlockStart;
	//if this line ends a collapsed block (actual value, independent from line flags)
	bool collapsedBlockEnd;
	//if the block ending at this line hides this line
	bool hiddenCollapsedBlockEnd;
	//count of parenthesis in openParentheses which hiding == true
	int hiddenDepth;

	//goto next line and update parentheses values
	QFoldedLineIterator& operator++();

	//calls ++ until the iterator reaches the line that ends the block which is opened on the current line
	void incrementUntilBlockEnd();

	bool lineFlagsInvalid() const;
private:
	friend class QLanguageDefinition;
	QDocument* doc;
	const QLanguageDefinition* def;
};

#endif // _QLANGUAGE_DEFINITION_H_
