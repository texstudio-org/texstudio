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
#include "qformatscheme.h"

#include <QMessageBox>

/*!
	\class QDocumentSearch
	\brief An helper class to perform search in document
	
	QDocumentSearch offer means to perform complex search in documents.
*/

QDocumentSearch::QDocumentSearch(QEditor *e, const QString& f, Options opt, const QString& r)
 : m_group(-1), m_option(opt), m_string(f), m_replace(r), m_editor(e), m_scopeGroup(-1), m_replaced(0), m_replaceDeltaLength(0)
{
	if (m_editor && hasOption(HighlightAll))
		connect(m_editor->document(),SIGNAL(contentsChange(int, int)),this,SLOT(documentContentChanged(int, int)));
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

//equal to next but needs matches
bool QDocumentSearch::nextMatch(bool backward, bool again,  bool allowWrapAround){
	if (!hasOption(HighlightAll)) 
		return false;
	if (!indexedMatchCount()) searchMatches();
	if (!indexedMatchCount()) {
		m_cursor = QDocumentCursor();
		return false;
	}
	if (m_cursor.isNull()){
		m_cursor = QDocumentCursor();
		return false; //need a starting point, m_cursor should have been set by next
	}
	//search the correct index	
	if (m_index >= 0 && m_index < m_highlight.count() && m_highlight.at(m_index).isWithinSelection(m_cursor)){
		//we have a cached match!
		if ( !backward ) ++m_index;
		else --m_index;
	} else if (backward){
		//todo: binary search
		m_index=-1;
		for (int i=m_highlight.count()-1; i>=0;--i)
			if (m_highlight[i].selectionEnd()<=m_cursor) {
				m_index=i;
				break;
			}
	} else {
		m_index=-1;
		for (int i=0;i<m_highlight.count(); ++i)
			if (m_highlight[i].selectionStart()>=m_cursor) {
				m_index=i;
				break;
			}
	}

	m_cursor = QDocumentCursor(); //don't need the old cursor anymore (and will set the new one later if found)
	//remove invalid cursors

	if ( m_index >= 0 && m_index < m_highlight.count() ) {
		//TODO: understand why the selectedText().isEmpty() check is necessary, perhaps a bug in qdocumentcommand? (in the test case xxxxxxxxxxxxxxxx replace the cursor is moved to a not existing column)
		if (backward) 
			while (m_index>=0 && (m_highlight[m_index].isNull() || m_highlight[m_index].selectedText().isEmpty()))
				m_highlight.removeAt(m_index--);
		if (!backward)
			while (m_index<m_highlight.count() && (m_highlight[m_index].isNull() || m_highlight[m_index].selectedText().isEmpty()))
				m_highlight.removeAt(m_index);
	}
	
	if ( (m_index < 0 || m_index >= m_highlight.count()) )
	{
		if (!allowWrapAround) 
			return false;
		
		int ret = QMessageBox::Yes ;
		if ( !hasOption(Silent) )
		{
			ret=QMessageBox::question(
							m_editor,
							tr("Failure"),
							tr(
								"End of matches reached.\n"
								"Restart from the begining ?"
							),
							QMessageBox::Yes | QMessageBox::No,
							QMessageBox::Yes
						);
		}
		
		if ( ret != QMessageBox::Yes ) 
			return false;
		
		if (backward)  {
			while (m_highlight.count() && (m_highlight.last().isNull() || m_highlight.last().selectedText().isEmpty()))
				m_highlight.removeLast();
			m_index=m_highlight.count()-1;
		} else {
			while (m_highlight.count() && (m_highlight.first().isNull() || m_highlight.first().selectedText().isEmpty()))
				m_highlight.removeFirst();
			m_index=0;
		}
		if (!m_highlight.count()) return false;
	} 	

	m_cursor = m_highlight.at(m_index);
	if (backward) { //invert cursor, previous line necessary to set cursor document
		m_cursor.moveTo(m_cursor.lineNumber(), m_cursor.columnNumber());
		m_cursor.setColumnNumber(m_highlight.at(m_index).anchorColumnNumber(),QDocumentCursor::KeepAnchor); //swap anchor and normals
		//TODO: match spanning across several lines
	} 
	if ( m_editor && !hasOption(Silent) )
			m_editor->setCursor(m_cursor);

	if (hasOption(Replace) && !again) //again replacement should already have been handled by next
	{
		QRegExp m_regexp=currentRegExp();
		if (!m_regexp.exactMatch(m_cursor.selectedText())) 
			return false; //wtf? anyway this check is necessary to access the submatch \1, \2 in the replace text
		int ret=QMessageBox::Yes;
		
		if ( hasOption(Prompt) )
			ret = QMessageBox::question(m_editor, tr("Replacement prompt"),
								tr("Shall it be replaced?"),
								QMessageBox::Yes | QMessageBox::No,
								QMessageBox::Yes);

		if (ret==QMessageBox::Yes)
			replaceCursorText(m_regexp,backward);
	}
	return true;
}
void QDocumentSearch::searchMatches(const QDocumentCursor& subHighlightScope, bool clearAll){
	if ( !hasOption(HighlightAll) )
		return;
	
	if ( clearAll )
		clearMatches();
	
	QDocument* d= currentDocument();
	if ( !d || !d->lines()) return;

	QFormatScheme *f = d->formatScheme() ? d->formatScheme() : QDocument::formatFactory();
	int sid = f ? f->id("search") : 0;
	
	if ( !sid )
		qWarning("Highlighting of search matches disabled due to unavailability of a format scheme.");

	QDocumentCursor hscope = subHighlightScope; 
	if (!hscope.isValid() || !hscope.hasSelection() || hscope.document()!=d){
		if (m_scope.isValid() && m_scope.hasSelection() && m_scope.document()==d) hscope=m_scope;
		else {
			if (hscope.document()!=d) hscope=d->cursor(0,0);
			else hscope.movePosition(0,QDocumentCursor::Start);
			hscope.movePosition(0,QDocumentCursor::End, QDocumentCursor::KeepAnchor);
		}
	} else if (m_scope.isValid() && m_scope.hasSelection() && m_scope.document()==d){
		hscope = m_scope.intersect(hscope);
		if (!hscope.isValid() || !hscope.hasSelection()) return;
	}
	
	QList<QDocumentCursor> saved;
	if (!clearAll && m_group!=-1) {
		//TODO: binary search
		d->clearMatches(m_group); //clear matches in the document, remember our copy
		//remove all matches witin the new scope
		QDocumentCursor ss=hscope.selectionStart();
		QDocumentCursor se=hscope.selectionEnd();
		for (int i=0; i<m_highlight.count();)
			if (m_highlight[i].selectionEnd()<ss) 
				i++;
			else if (m_highlight[i].selectionStart()>se){
				saved<<m_highlight.mid(i);
				m_highlight.erase(m_highlight.begin()+i,m_highlight.end());
				break;
			} else 
				m_highlight.removeAt(i);
	}
	
	QDocumentCursor hc = hscope.selectionStart();
	QDocumentSelection boundaries=hscope.selection();
	QRegExp m_regexp = currentRegExp();
	
	while ( !hc.atEnd() && hscope.isWithinSelection(hc))
	{
		int ln = hc.lineNumber();
		QDocumentLine l = hc.line();
		
		QString s = l.text();
		
		if ( boundaries.endLine == ln )
			s = s.left(boundaries.end);
		
		int column=m_regexp.indexIn(s, hc.columnNumber());
                /*
		qDebug("searching %s in %s => %i",
				qPrintable(m_regexp.pattern()),
				qPrintable(s),
				column);
		*/
		
		if ( column != -1 && (column >= hc.columnNumber() ) )
		{
			if (!m_regexp.matchedLength())
				hc.setColumnNumber(column+1); //empty (e.g. a* regexp)
			else {
				hc.setColumnNumber(column);
				hc.setColumnNumber(column + m_regexp.matchedLength(), QDocumentCursor::KeepAnchor);
											
				m_highlight << hc;
				m_highlight.last().setAutoUpdated(true);		
			}
		} else hc.movePosition(1, QDocumentCursor::NextBlock);
	}
	
	m_highlight<<saved;
	
	if ( m_highlight.count() )
	{
		if ( m_group == -1 )
			m_group = d->getNextGroupId();
		foreach (const QDocumentCursor& hc, m_highlight)
			d->addMatch(m_group,
						hc.lineNumber(),
						hc.anchorColumnNumber(),
						hc.columnNumber() - hc.anchorColumnNumber(),
						sid);
	
		//qDebug("%i matches in group %i", indexedMatchCount(), m_group);
		m_editor->document()->flushMatches(m_group);
	} else clearMatches();
	m_index = -1; //current index became invalid due to (partially) cleaning (TODO?: change to new index)
}

/*!
	\brief Clear matches
	
	This function should be called anytime you perform a search with the HighlightAll option,
	once you're done iterating over the matches.
*/
void QDocumentSearch::clearMatches()
{
	QDocument* doc= currentDocument();
	if ( !doc )
		return;
	
	//qDebug("clearing matches");
	//m_cursor = QDocumentCursor();
	m_index=-1;
	
	if ( m_group != -1 )
	{
		doc->clearMatches(m_group);
		doc->flushMatches(m_group);
		m_group = -1;
	}
	
	m_highlight.clear();
}

/*
  returns the document the search should be performed
  */
QDocument* QDocumentSearch::currentDocument(){
	return m_editor ? m_editor->document() : m_origin.document();
}

/*
  returns a regexp which fully describes the search text (including flags like casesensitivity, wholewords,...)
  */
QRegExp QDocumentSearch::currentRegExp(){
	Qt::CaseSensitivity cs = hasOption(CaseSensitive)
								?
									Qt::CaseSensitive
								:
									Qt::CaseInsensitive;
	
	QRegExp m_regexp;
	if ( hasOption(RegExp) )
	{
		m_regexp = QRegExp(m_string, cs, QRegExp::RegExp);
	} else if ( hasOption(WholeWords) ) {
		//todo: screw this? it prevents searching of "world!" and similar things
		//(qtextdocument just checks the surrounding character when searching for whole words, this would also allow wholewords|regexp search)
		m_regexp = QRegExp(
						QString("\\b%1\\b").arg(QRegExp::escape(m_string)),
						cs,
						QRegExp::RegExp
					);
	} else {
		m_regexp = QRegExp(m_string, cs, QRegExp::FixedString);
	}
	return m_regexp;
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
	
	if (hasOption(HighlightAll) && !m_string.isEmpty()) 
		searchMatches();
	else if (m_group !=-1 || m_highlight.count())
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
	
	if ( (opt & QDocumentSearch::HighlightAll)  )
	{
		//prevent multiple connections
		if (m_editor->document()) {
			disconnect(m_editor->document(),SIGNAL(contentsChange(int, int)),this,SLOT(documentContentChanged(int, int)));
			if (on) //connect if highlighting is on
				connect(m_editor->document(),SIGNAL(contentsChange(int, int)),this,SLOT(documentContentChanged(int, int)));
		}
		if ( (m_group != -1 || m_highlight.count()) && !on  ) 
			clearMatches();
		else if ( m_group == -1 && on ) 
			searchMatches();
			/*m_group = d->getNextGroupId();
			
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
			d->flushMatches(m_group);*/
		
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
		searchMatches();
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
	if (m_origin.hasSelection())
		m_origin = m_origin.selectionStart();
		
//	clearMatches();
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
	m_index = -1;
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
	
	if ( c.hasSelection() ){
		m_scope = c;
		//prevent multiple connections
		if (m_editor->document()) {
			disconnect(m_editor->document(),SIGNAL(contentsChange(int, int)),this,SLOT(documentContentChanged(int, int)));
			connect(m_editor->document(),SIGNAL(contentsChange(int, int)),this,SLOT(documentContentChanged(int, int)));
		}
		m_scope.setAutoUpdated(true);
	} else
		m_scope = QDocumentCursor();
	highlightSelection();
	searchMatches();
	//clearMatches();
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

	\note The search will start at the first character left/right from the selected text
*/
bool QDocumentSearch::next(bool backward, bool all, bool again, bool allowWrapAround)
{
	if ( m_string.isEmpty() )
		return true;
	
	
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


	if (all && !hasOption(Replace)) {
		all=false;
		qWarning("QDocumentSearch:next: all without replace is meaningless");
	}

	QRegExp m_regexp=currentRegExp();
	
	int replaceCount = 0;
	
	if (hasOption(Replace) && again && !all) 
		if (m_regexp.exactMatch(m_cursor.selectedText()))  {
			replaceCursorText(m_regexp,backward);
			replaceCount++;
			//foundCount++; we can't set this here, because it has to search the next match
			//and if (foundCount) is true, it thinks already found something and doesn't restart from scope
		}

	//ensure that the current selection isn't searched
	if ( m_cursor.hasSelection() ) 
		if (m_cursor.selectionStart() == m_scope.selectionStart() &&
			m_cursor.selectionEnd() == m_scope.selectionEnd()) {
			//search whole scope
			if (backward) m_cursor=m_scope.selectionEnd();
			else m_cursor=m_scope.selectionStart();
		} else if (backward ^ all) //let all search in the selection
			m_cursor=m_cursor.selectionStart();
		else 
			m_cursor=m_cursor.selectionEnd();
	
	QDocumentSelection boundaries;
	bool bounded = m_scope.isValid() && m_scope.hasSelection();
	
	// condition only to avoid debug messages...
	if ( bounded ) {
		boundaries = m_scope.selection();
	
		//moves the cursor in the search scope if it isn't there, but directly in front of the selection (only possible if there actually is a selection)
		if ( end(backward) ) 
			if ( !backward && m_cursor < m_scope.selectionStart() ) 
				m_cursor = m_scope.selectionStart();
			else if ( backward && m_cursor > m_scope.selectionEnd() ) 
				m_cursor = m_scope.selectionEnd();
	}

	if (hasOption(HighlightAll) && !all)  //special handling if highlighting is on, but all replace is still handled here
		return nextMatch(backward,again,allowWrapAround);
	
	/*qDebug(
		"searching %s from line %i (column %i)",
		backward ? "backward" : "forward",
		m_cursor.lineNumber(),
		m_cursor.columnNumber()
	);
	//*/
	
	m_index = 0;
	bool realReplace=hasOption(Replace) && (!again || all);
	
	QDocumentCursor::MoveOperation move;
//	QDocument *d = currentDocument();
	
	move = backward ? QDocumentCursor::PreviousBlock : QDocumentCursor::NextBlock;	
	
	int foundCount = 0;
	while ( !end(backward) )
	{
		if ( backward && !m_cursor.columnNumber() )
		{
			m_cursor.movePosition(1, QDocumentCursor::PreviousCharacter);
			continue;
		}
		
		int ln = m_cursor.lineNumber();
		const QDocumentLine& l = m_cursor.line();
		
		int coloffset = 0;
		QString s = l.text();
		
		if ( backward )
		{
			if ( bounded && (boundaries.startLine == ln) )
			{
				s = s.mid(boundaries.start);
				coloffset = boundaries.start;
			}
			
			s = s.left(m_cursor.columnNumber()-coloffset);
		} else {
			if ( bounded && (boundaries.endLine == ln) )
				s = s.left(boundaries.end);
			
		}
		
		int column;
		if (backward) column=m_regexp.lastIndexIn(s,m_cursor.columnNumber()-coloffset);
		else column=m_regexp.indexIn(s, m_cursor.columnNumber());
        /*
		qDebug("searching %s in %s from %i => %i",
				qPrintable(m_regexp.pattern()),
				qPrintable(s), m_cursor.columnNumber(), 
				column);
		//*/
		
		if ( column != -1 && (backward || column >= m_cursor.columnNumber() ) )
		{
			if (!m_regexp.matchedLength()){
				//empty (e.g. a* regexp)
				if (backward) m_cursor.setColumnNumber(column-1);
				else m_cursor.setColumnNumber(column+1);
			} else {
				column += coloffset;
				
				if ( backward )
				{
					m_cursor.setColumnNumber(column + m_regexp.matchedLength());
					m_cursor.setColumnNumber(column, QDocumentCursor::KeepAnchor);
				} else {
					m_cursor.setColumnNumber(column);
					m_cursor.setColumnNumber(column + m_regexp.matchedLength(), QDocumentCursor::KeepAnchor);
				}
				
				if ( m_editor && !hasOption(Silent))
					m_editor->setCursor(m_cursor);
				
				foundCount++;
				
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
						if (ret==QMessageBox::Cancel) {
							QMessageBox::information(m_editor,tr("Replacing Canceled"),tr("%1 (of %2 found so far) occurences have been replaced").arg(replaceCount).arg(foundCount),QMessageBox::Ok);
							//rep=all=false;//return false;
							return false;
						}
					}
					
					if ( rep ) {
						replaceCursorText(m_regexp,backward);
						replaceCount++;
					}
				} 
				
				
				if ( !all )
					break;
			}
		} else 
			m_cursor.movePosition(1, move);
	}
		
	if ( !foundCount && allowWrapAround)
	{
		m_cursor = QDocumentCursor();
			
		int ret = QMessageBox::Yes; //different to base qce2.2, where it defaults to ::no if silent
		if ( !hasOption(Silent) /*&& hasOption(Prompt), to ask or not to ask that is the question; if it doesn't ask it fails silently if no match exists*/){
			ret=QMessageBox::question(
							m_editor,
							tr("Failure"),
							tr(
								"End of scope reached with no match.\n"
								"Restart from the beginning ?"
							),
							QMessageBox::Yes
							| QMessageBox::No,
							QMessageBox::Yes
						);
		}
		if ( ret == QMessageBox::Yes )
		{
			m_origin = QDocumentCursor();
			return next(backward, all, again, false);
		}
	}
	
	if ( !foundCount )
		m_cursor = QDocumentCursor();
	
	if ( all && foundCount && !hasOption(Silent)) {
		if (allowWrapAround) {
			int ret=QMessageBox::question(
								m_editor,
								tr("Replacing Finished"),
								tr("%1 (of %2) occurences have been replaced").arg(replaceCount).arg(foundCount)+"\n\n"+
								tr("Do you want to continue replacing from the beginning?"),
								QMessageBox::Yes
								| QMessageBox::No,
								QMessageBox::Yes
							);
			if ( ret == QMessageBox::Yes )
			{
				m_cursor = QDocumentCursor();
				m_origin = QDocumentCursor();
				return next(backward, all, again, false);
			}
		} else QMessageBox::information(m_editor,tr("Replacing Finished"),tr("%1 (of %2) occurences have been replaced").arg(replaceCount).arg(foundCount),QMessageBox::Ok);
	}
	
	
	return false;
}
/*! @} */

static QString escapeCpp(const QString& s)
{
	QString es;
//TODO: numbers (e.g. \xA6)
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

void QDocumentSearch::replaceCursorText(QRegExp& m_regexp,bool backward){
	QString replacement = hasOption(EscapeSeq)?escapeCpp(m_replace):m_replace;
	
	if (hasOption(RegExp)) 
		for ( int i = m_regexp.numCaptures(); i >= 0; --i )
			replacement.replace(QString("\\") + QString::number(i),
								m_regexp.cap(i));
	
	/*m_replaced=2;
	int n=replacement.lastIndexOf("\n");
	QString replacement_lastLine=replacement.mid(n+1);
	m_replaceDeltaLength=replacement_lastLine.length()-m_cursor.selectedText().length();
	m_replaceDeltaLines=replacement.count("\n");*/
	m_cursor.replaceSelectedText(replacement);

	
	//make sure that the cursor if  the correct side of the selection is used
	//(otherwise the cursor could be moved out of the searched scope by a long 
	//replacement text)
	if (m_cursor.hasSelection())
		if (backward) m_cursor=m_cursor.selectionStart();
		else m_cursor=m_cursor.selectionEnd();
}

void QDocumentSearch::documentContentChanged(int line, int n){
	if (!m_editor || !m_editor->document()) return;
	if (m_scope.isValid() && m_scope.hasSelection() && m_scope.selectionStart()==m_scope.selectionEnd()) 
		setScope(QDocumentCursor());
	if(!hasOption(HighlightAll)) {
		highlightSelection();
		return;
	}
	int lineend = qMin(m_editor->document()->lines()-1,line+n);
	if (lineend < line) {
		highlightSelection();
		return;
	}
	QDocumentLine le = m_editor->document()->line(lineend);
	if (!le.isValid()) {
		highlightSelection();
		return;
	}
	QDocumentCursor c = m_editor->document()->cursor(line);
	c.setLineNumber(lineend, QDocumentCursor::KeepAnchor);
	c.setColumnNumber(le.length(), QDocumentCursor::KeepAnchor);
	highlightSelection();
	searchMatches(c,false);
	//searchMatches();
}

void QDocumentSearch::highlightSelection(bool on)
{
	if(m_scopeGroup>-1){
		m_editor->document()->clearMatches(m_scopeGroup);
		m_editor->document()->flushMatches(m_scopeGroup);
		m_scopeGroup = -1;
	}

	if(on && m_scope.isValid() && m_scope.hasSelection()){
		m_scopeGroup = m_editor->document()->getNextGroupId();
		QFormatScheme *f = m_editor->document()->formatScheme() ? m_editor->document()->formatScheme() : QDocument::formatFactory();
		int sid = f ? f->id("selection") : 0;
		if(m_scope.hasSelection()){
			int begLine, endLine, begCol, endCol;
			m_scope.boundaries(begLine, begCol, endLine, endCol);
			for(int i=begLine;i<=endLine;i++){
				int beg = i==begLine ? begCol : 0;
				int en = i==endLine ? endCol : m_editor->document()->line(i).length();
				m_editor->document()->addMatch(m_scopeGroup,
											   i,
											   qMin(beg,en),
											   abs(en-beg),
											   sid);
			}
			m_editor->document()->flushMatches(m_scopeGroup);
		}
		//if(!QApplication::mouseButtons()) editor()->selectNothing();
	}
}
