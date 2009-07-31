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

/*!
	\file qdocumentsearch.cpp
	\brief Implementation of QDocumentSearch
*/

#include "qdocumentsearch.h"

/*!
	\ingroup document
	@{
*/

#include "qeditor.h"
#include "qdocument.h"
#include "qdocument_p.h"
#include "qdocumentline.h"
#include "qformatscheme.h"

#include <QMessageBox>

/*!
	\class QDocumentSearch
	\brief An helper class to perform search in document
	
	QDocumentSearch offer means to perform complex search in documents.
*/

QDocumentSearch::QDocumentSearch(QEditor *e, const QString& f, Options opt, const QString& r)
 : m_group(-1), m_option(opt), m_string(f), m_replace(r), m_editor(e)
{
	
}

QDocumentSearch::~QDocumentSearch()
{
	clearMatches();
}

QDocumentSearch::Options QDocumentSearch::options() const
{
	return m_option;
}

/*!
	\brief Position of the current match among the indexed matches
*/
int QDocumentSearch::currentMatchIndex() const
{
	return m_highlight.count() ? m_index : -1;
}

/*!
	\brief Number of availables indexed matches
	
	Indexed matches are only available when the whole scope is searched,
	i.e when either the HighlightAll option is set to true or when next()
	is called with the all parameter set to true.
*/
int QDocumentSearch::indexedMatchCount() const
{
	return m_highlight.count();
}

/*!
	\return A cursor pointing to the n-th index match
	\param idx index of the match to lookup
	
	The cursor returned, if valid, delimits the match through its selection.
*/
QDocumentCursor QDocumentSearch::match(int idx) const
{
	return idx >= 0 && idx < m_highlight.count() ? m_highlight.at(idx) : QDocumentCursor();
}

/*!
	\brief Clear matches
	
	This function should be called anytime you perform a search with the HighlightAll option,
	once you're done iterating over the matches.
*/
void QDocumentSearch::clearMatches()
{
	if ( !m_editor || !m_editor->document() )
		return;
	
	//qDebug("clearing matches");
	m_cursor = QDocumentCursor();
	
	if ( m_group != -1 )
	{
		m_editor->document()->clearMatches(m_group);
		m_editor->document()->flushMatches(m_group);
		m_group = -1;
	}
	
	m_highlight.clear();
}

/*!
	\return The search pattern
*/
QString QDocumentSearch::searchText() const
{
	return m_string;
}

/*!
	\brief Set the search pattern
*/
void QDocumentSearch::setSearchText(const QString& f)
{
	m_string = f;
	
	clearMatches();
}

/*!
	\brief Test whether a given option is enabled
*/
bool QDocumentSearch::hasOption(Option opt) const
{
	return m_option & opt;
}

/*!
	\brief Set a search option
	\param opt option to set
	\param on whether to enable the option
*/
void QDocumentSearch::setOption(Option opt, bool on)
{
	if ( on )
		m_option |= opt;
	else
		m_option &= ~opt;
	
	if ( (opt & QDocumentSearch::HighlightAll) && m_highlight.count() )
	{
		QDocument *d = m_editor->document();
		
		if ( m_group != -1 && !on )
		{
			d->clearMatches(m_group);
			d->flushMatches(m_group);
			m_group = -1;
		} else if ( m_group == -1 && on ) {
			m_group = d->getNextGroupId();
			
			QFormatScheme *f = d->formatScheme();
			
			if ( !f )
				f = QDocument::formatFactory();
			
			if ( !f )
			{
				qWarning("No format scheme set to the document and no global default one available.\n"
						"-> highlighting of search matches disabled.");
				return;
			}
			
			int sid = f->id("search");
			
			foreach ( const QDocumentCursor& c, m_highlight )
			{
				//QFormatRange r(c.anchorColumnNumber(), c.columnNumber() - c.anchorColumnNumber(), sid);
				
				d->addMatch(m_group,
							c.lineNumber(),
							c.anchorColumnNumber(),
							c.columnNumber() - c.anchorColumnNumber(),
							sid);
			}
			
			//qDebug("%i matches in group %i", indexedMatchCount(), m_group);
			d->flushMatches(m_group);
		}
	} else if (
					(m_option & QDocumentSearch::HighlightAll)
				&&
					(
						(opt & QDocumentSearch::RegExp)
					||
						(opt & QDocumentSearch::WholeWords)
					||
						(opt & QDocumentSearch::CaseSensitive)
					)
			)
	{
		// matches may have become invalid : update them
		clearMatches();
		next(false);
	}
}


void QDocumentSearch::setOptions(Options options){
	for (int i=0;i<8;i++)
		setOption((Option)(1<<i), options & (1<<i));
}


/*!
	\return the replacement text
*/
QString QDocumentSearch::replaceText() const
{
	return m_replace;
}

/*!
	\brief Set the replacement text
*/
void QDocumentSearch::setReplaceText(const QString& r)
{
	m_replace = r;
	//if (m_option & QDocumentSearch::HighlightAll)
	//	clearMatches();
}

/*!
	\return The current cursor position
	
	This is useful to examine matches after performing a search.
*/
QDocumentCursor QDocumentSearch::origin() const
{
	return m_origin;
}

/*!
	\brief Set the cursor
	
	If the related option is set, search will start from that cursor position
	
	This also changes the cursor()
*/
void QDocumentSearch::setOrigin(const QDocumentCursor& c)
{
	m_cursor = QDocumentCursor();
	
	if ( c == m_origin )
		return;
	
	m_origin = c;
	
	clearMatches();
}

/*!
	\return The current cursor position
	
	This is useful to examine matches after performing a search.
*/
QDocumentCursor QDocumentSearch::cursor() const
{
	return m_cursor;
}

/*!
	\brief Set the cursor
	
	If the related option is set, search will start from that cursor position
*/
void QDocumentSearch::setCursor(const QDocumentCursor& c)
{
	m_cursor = c;
}

/*!
	\return The scope of the search
	
	An invalid cursor indicate that the scope is the whole document, otherwise
	the scope is the selection of the returned cursor.
*/
QDocumentCursor QDocumentSearch::scope() const
{
	return m_scope;
}

/*!
	\brief Set the search scope
	
	If the given cursor has no selection (a fortiori if it is invalid) then
	the scope is the whole document.
*/
void QDocumentSearch::setScope(const QDocumentCursor& c)
{
	if ( c == m_scope )
		return;
	
	if ( c.hasSelection() )
		m_scope = c;
	else
		m_scope = QDocumentCursor();
	
	clearMatches();
}

/*!
	\brief Test whether the end of the search scope has been reached
*/
bool QDocumentSearch::end(bool backward) const
{
	bool absEnd = backward ? m_cursor.atStart() : m_cursor.atEnd();
	
	if ( m_scope.isValid() && m_scope.hasSelection() )
	{
		absEnd |= !m_scope.isWithinSelection(m_cursor);
		/*
		qDebug(
				"(%i, %i, %i) %s in {(%i, %i), (%i, %i)}",
				m_cursor.lineNumber(),
				m_cursor.anchorColumnNumber(),
				m_cursor.columnNumber(),
				absEnd ? "is not" : "is",
				m_scope.selectionStart().lineNumber(),
				m_scope.selectionStart().columnNumber(),
				m_scope.selectionEnd().lineNumber(),
				m_scope.selectionEnd().columnNumber()
			);
		*/
	}
	
	return absEnd;
}

/*!
	\brief Perform a search
	\param backward whether to go backward or forward
	\param all if true, the whole document will be searched first, all matches recorded and available for further navigation
	\param again if a search match is selected it will be replaced, than a normal search (no replace) will be performed

	\note Technically speaking the all parameter make search behave similarly to the HighlightAll option, except that the former
	option does not alter the formatting of the document

	\note The .search will start at the first character left/right from the selected text
*/
bool QDocumentSearch::next(bool backward, bool all, bool again, bool allowWrapAround)
{
	if ( m_string.isEmpty() )
		return true;
	
	if ( !hasOption(Replace) && (all || hasOption(HighlightAll)) /*&& m_highlight.count()*/ &&
	     m_index >= 0 && m_index < m_highlight.count()  && m_cursor == m_highlight.at(m_index))
	{		
                if ( !backward ) ++m_index;
		else --m_index;
		
		//m_index = m_index + (backward ? -1 : 1);
		
		if ( (m_index < 0 || m_index >= m_highlight.count()) )
		{
			if ( hasOption(Silent) )
			{
				m_cursor = QDocumentCursor();
				return false;
			}
			
			int ret = 
			QMessageBox::question(
							m_editor,
							tr("Failure"),
							tr(
								"End of matches reached.\n"
								"Restart from the begining ?"
							),
							QMessageBox::Yes
							| QMessageBox::No,
							QMessageBox::Yes
						);
			
			if ( ret == QMessageBox::Yes )
			{
				m_index = backward ? m_highlight.count() : 0;
				--m_index;
				return next(backward);
			}
			return false;
		} else {
			m_cursor = m_highlight.at(m_index);
			
			if ( m_editor && !hasOption(Silent) )
				m_editor->setCursor(m_cursor);
			return true;
		}
		
		
		return false;
	}
	
	if ( m_cursor.isNull() )
	{
		m_cursor = m_origin;
	}
	
	if ( m_cursor.isNull() )
	{
		if ( m_scope.isValid() && m_scope.hasSelection() )
		{
                        if ( backward )
				m_cursor = m_scope.selectionEnd();
			else
				m_cursor = m_scope.selectionStart();
		} else if ( m_editor ) {
			
			m_cursor = QDocumentCursor(m_editor->document());
			
			if ( backward )
				m_cursor.movePosition(1, QDocumentCursor::End);
			
		} else {
			QMessageBox::warning(0, 0, "Unable to perform search operation");
		}
	}
	
	/*
	qDebug(
		"searching %s from line %i (column %i)",
		backward ? "backward" : "forward",
		m_cursor.lineNumber(),
		m_cursor.columnNumber()
	);
	*/
	
	m_index = 0;
	QRegExp m_regexp;
	Qt::CaseSensitivity cs = hasOption(CaseSensitive)
								?
									Qt::CaseSensitive
								:
									Qt::CaseInsensitive;
	
	if ( hasOption(RegExp) )
	{
		m_regexp = QRegExp(m_string, cs, QRegExp::RegExp);
	} else if ( hasOption(WholeWords) ) {
		m_regexp = QRegExp(
						QString("\\b%1\\b").arg(QRegExp::escape(m_string)),
						cs,
						QRegExp::RegExp
					);
	} else {
		m_regexp = QRegExp(m_string, cs, QRegExp::FixedString);
	}
	
	bool realReplace=hasOption(Replace) && !again;
	if (hasOption(Replace) && again) 
		if (m_regexp.exactMatch(m_cursor.selectedText()))  
			replaceCursorText(m_regexp,backward);
	
        bool found = false;
	
	QDocumentCursor::MoveOperation move;
	QDocument *d = m_editor ? m_editor->document() : m_origin.document();
	QFormatScheme *f = d->formatScheme() ? d->formatScheme() : QDocument::formatFactory();
	int sid = f ? f->id("search") : 0;
	
	if ( !sid )
		qWarning("Highlighting of search matches disabled due to unavailability of a format scheme.");
	
	move = backward ? QDocumentCursor::PreviousBlock : QDocumentCursor::NextBlock;
	
	QDocumentSelection boundaries;
	bool bounded = m_scope.isValid() && m_scope.hasSelection();
	
	// condition only to avoid debug messages...
	if ( bounded )
		boundaries = m_scope.selection();
	
	if (hasOption(HighlightAll)) {
		if (backward) m_cursor = bounded? m_scope.selectionEnd() : d->cursor(d->lines()-1,d->line(d->lines()-1).length()-1) ;
		else m_cursor = bounded?m_scope.selectionStart():d->cursor(0);
	}
	
	//make sure current selection isn't searched
	if ( m_cursor.hasSelection() ) {
		int l; int c;
		if (backward) m_cursor.leftBoundaries(l,c);
		else m_cursor.rightBoundaries(l,c);
		m_cursor.moveTo(l,c);
	}
	
	while ( !end(backward) )
	{
		if ( backward && !m_cursor.columnNumber() )
		{
			m_cursor.movePosition(1, QDocumentCursor::PreviousCharacter);
			continue;
		}
		
		int ln = m_cursor.lineNumber();
		QDocumentLine l = m_cursor.line();
		
		int coloffset = 0;
		QString s = l.text();
		
		if ( backward )
		{
			if ( bounded && (boundaries.startLine == ln) )
			{
				s = s.mid(boundaries.start);
				coloffset = boundaries.start;
			}
			
			s = s.left(m_cursor.columnNumber());
		} else {
			if ( bounded && (boundaries.endLine == ln) )
				s = s.left(boundaries.end);
			
		}
		
		int column;
		if (backward) column=m_regexp.lastIndexIn(s,m_cursor.columnNumber());
		else column=m_regexp.indexIn(s, m_cursor.columnNumber());
                /*
		qDebug("searching %s in %s => %i",
				qPrintable(m_regexp.pattern()),
				qPrintable(s),
				column);
		*/
		
                if ( column != -1 && (backward || column >= m_cursor.columnNumber() ) )
		{
			column += coloffset;
			
			if ( backward )
			{
				m_cursor.setColumnNumber(column + m_regexp.matchedLength());
				m_cursor.setColumnNumber(column, QDocumentCursor::KeepAnchor);
				
				/*
				m_cursor.movePosition(m_regexp.matchedLength(),
									QDocumentCursor::PreviousCharacter,
									QDocumentCursor::KeepAnchor);
				*/
			} else {
				m_cursor.setColumnNumber(column);
				m_cursor.setColumnNumber(column + m_regexp.matchedLength(), QDocumentCursor::KeepAnchor);
				
				/*
				m_cursor.movePosition(m_regexp.matchedLength(),
									QDocumentCursor::NextCharacter,
									QDocumentCursor::KeepAnchor);
				*/
			}
			
			if ( m_editor && !hasOption(Silent) && !hasOption(HighlightAll) )
				m_editor->setCursor(m_cursor);
			
			if ( realReplace )
			{
				bool rep = true;
				
				if ( hasOption(Prompt) )
				{
					QMessageBox::StandardButtons buttons=QMessageBox::Yes | QMessageBox::No;
					if (all) buttons|=QMessageBox::Cancel;
                                        int ret = QMessageBox::question(m_editor, tr("Replacement prompt"),
										tr("Shall it be replaced?"),
										buttons,
										QMessageBox::Yes);
					rep=ret==QMessageBox::Yes;
					if (ret==QMessageBox::Cancel) 
						return false;
				}
				
				//
				if ( rep ) replaceCursorText(m_regexp, backward);
			} else if ( all || hasOption(HighlightAll) ) {
				
				if ( sid && hasOption(HighlightAll) )
				{
					if ( m_group == -1 )
						m_group = d->getNextGroupId();
					
					d->addMatch(m_group,
								m_cursor.lineNumber(),
								m_cursor.anchorColumnNumber(),
								m_cursor.columnNumber() - m_cursor.anchorColumnNumber(),
								sid);
					//QFormatRange r(
					//			m_cursor.anchorColumnNumber(),
					//			m_cursor.columnNumber() - m_cursor.anchorColumnNumber(),
					//			m_editor->document()->formatScheme()->id("search")
					//		);
					
					//qDebug("(%i, %i, %i)", r.offset, r.length, r.format);
					//m_cursor.line().addOverlay(r);
				}
				
				m_highlight << m_cursor;
				m_highlight.last().setAutoUpdated(true);
			}
			
			found = true;
			
			if ( !(all || hasOption(HighlightAll)) )
				break;
			
		} else {
			m_cursor.movePosition(1, move);
		}
	}
	
	if ( !hasOption(Replace) && hasOption(HighlightAll) && m_highlight.count() )
	{
		//matches has been updated (only reached if there were no matches when next was called)
		//qDebug("%i matches in group %i", indexedMatchCount(), m_group);
		if ( indexedMatchCount() )
		{
			m_editor->document()->flushMatches(m_group);
		} else {
			m_editor->document()->releaseGroupId(m_group);
			m_group = -1;
		}
		
		m_index = backward ? m_highlight.count()-1 : 0;
		m_cursor = m_origin;
		return next(backward, false, again, allowWrapAround);
	}
	
	if ( !found && allowWrapAround)
	{
		m_cursor = QDocumentCursor();
			
		int ret = QMessageBox::Yes; //different to base qce2.2, where it defaults to ::no if silent
		if ( !hasOption(Silent) )
			ret=QMessageBox::question(
							m_editor,
							tr("Failure"),
							tr(
								"End of scope reached with no match.\n"
								"Restart from the begining ?"
							),
							QMessageBox::Yes
							| QMessageBox::No,
							QMessageBox::Yes
						);
		
		if ( ret == QMessageBox::Yes )
		{
			m_origin = QDocumentCursor();
			return next(backward, false, again, false);
		}
	}
	if ( !found )
		m_cursor = QDocumentCursor();
	return false;
}
/*! @} */

static QString escapeCpp(const QString& s)
{
	QString es;

	for ( int i = 0; i < s.count(); ++i )
	{
		if ( (s.at(i) == '\\') && ((i + 1) < s.count()) )
		{
			QChar c = s.at(++i);

			if ( c == '\\' )
				es += '\\';
			else if ( c == 't' )
				es += '\t';
			else if ( c == 'n' )
				es += '\n';
			else if ( c == 'r' )
				es += '\r';
			else if ( c == '0' )
				es += '\0';

		} else {
			es += s.at(i);
		}
	}

	//qDebug("\"%s\" => \"%s\"", qPrintable(s), qPrintable(es));

	return es;
}

void QDocumentSearch::replaceCursorText(QRegExp& m_regexp, bool backward){
	QString replacement = hasOption(EscapeSeq)?escapeCpp(m_replace):m_replace;
	
	for ( int i = m_regexp.numCaptures(); i >= 0; --i )
		replacement.replace(QString("\\") + QString::number(i),
							m_regexp.cap(i));
	
	m_cursor.replaceSelectedText(replacement);
	
//	if ( backward )
//		m_cursor.movePosition(replacement.length(), QDocumentCursor::PreviousCharacter);
	
}
