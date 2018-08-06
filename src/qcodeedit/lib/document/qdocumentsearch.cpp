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
 : m_option(opt), m_string(f),  m_editor(e), m_replaced(0), m_replaceDeltaLength(0)
{
	m_replace=r;
	connectToEditor();
}
void QDocumentSearch::connectToEditor(){
	if (m_editor && hasOption(HighlightAll)){ //connect if highlighting is on
		connect(m_editor->document(),SIGNAL(contentsChange(int, int)),this,SLOT(documentContentChanged(int, int)));
		connect(m_editor->document(),SIGNAL(lineDeleted(QDocumentLineHandle*)), SLOT(lineDeleted(QDocumentLineHandle*)));
		connect(m_editor->document(),SIGNAL(lineRemoved(QDocumentLineHandle*)), SLOT(lineDeleted(QDocumentLineHandle*)));
		connect(m_editor,SIGNAL(visibleLinesChanged()), SLOT(visibleLinesChanged()));
	}
}

QDocumentSearch::~QDocumentSearch()
{
        clearMatches();
}

QDocumentSearch::Options QDocumentSearch::options() const
{
	return m_option;
}


//equal to next but needs matches
void QDocumentSearch::searchMatches(const QDocumentCursor& subHighlightScope, bool clearAll, bool clearSelection){
	if ( !hasOption(HighlightAll) )
		return;
	
	if ( clearAll )
		clearMatches();

	QDocument* d= currentDocument();
	if ( !d || !d->lines()) return;

	int sid = d->getFormatId("search");
	
	if ( !sid ) {
		qWarning("Highlighting of search matches disabled due to unavailability of a format scheme.");
		return;
	}

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
	
	//limit search scope to visible lines
	hscope = hscope.intersect(currentDocument()->cursor(m_editor->getFirstVisibleLine(), 0, m_editor->getLastVisibleLine()));

	if (!hscope.hasSelection()) return;

	//remove already searched lines from scope
	QDocumentCursor hss = hscope.selectionStart();
	QDocumentCursor hse = hscope.selectionEnd();
	m_searchedScope.setColumnMemory(false);
	if (m_searchedScope.isValid() && m_searchedScope.hasSelection()){
		//invariant: m_searchedScope.anchorLineNumber() <= m_searchedScope.lineNumber()
		bool startInOld = m_searchedScope.isWithinSelection(hss);
		bool endInOld = m_searchedScope.isWithinSelection(hse);
		if (!clearSelection) {
			if (startInOld && endInOld) return; //no need to update
			if (startInOld) {
				hscope = QDocumentCursor(m_searchedScope.selectionEnd(), hse);
				m_searchedScope.setLineNumber(hse.lineNumber(), QDocumentCursor::KeepAnchor);
				m_searchedScope.setColumnNumber(hse.columnNumber(), QDocumentCursor::KeepAnchor);
			} else if (endInOld) {
				hscope = QDocumentCursor(hss, m_searchedScope.selectionStart());
				m_searchedScope.setAnchorLineNumber(hss.lineNumber());
				m_searchedScope.setAnchorColumnNumber(hss.columnNumber());
			} else m_searchedScope = QDocumentCursor(hss, hse);;
		} else if (!startInOld || !endInOld){
			if (startInOld) {
				m_searchedScope.setLineNumber(hse.lineNumber());
				m_searchedScope.setColumnNumber(hse.columnNumber());
			} else if (endInOld) {
				m_searchedScope.setAnchorLineNumber(hss.lineNumber());
				m_searchedScope.setAnchorColumnNumber(hss.columnNumber());
			} else m_searchedScope = QDocumentCursor(hss, hse);;
		}
	} else m_searchedScope = QDocumentCursor(hscope.selectionStart(), hscope.selectionEnd());

	//qDebug() << "shs: " << subHighlightScope.anchorLineNumber() << ":" << subHighlightScope.anchorColumnNumber() << "->" << subHighlightScope.lineNumber() << ":" << subHighlightScope.columnNumber();
	//qDebug() << "search scope: " << m_searchedScope.anchorLineNumber() << ":" << m_searchedScope.anchorColumnNumber() << "->" << m_searchedScope.lineNumber() << ":" << m_searchedScope.columnNumber();
	//qDebug() << "hscope: " << hscope.anchorLineNumber() << ":" << hscope.anchorColumnNumber() << "->" << hscope.lineNumber() << ":" << hscope.columnNumber();

	QDocumentCursor hc = hscope.selectionStart();
	QDocumentSelection boundaries=hscope.selection();
	recreateRegExp();
	
	if (!clearAll) {//otherwise it was already cleaned above
		int from = boundaries.startLine, to = boundaries.endLine;
		if (boundaries.start == d->line(boundaries.startLine).length()) from++;
		if (boundaries.end == 0) to--;
		for ( int i=from; i<=to;i++ )
			d->line(i).clearOverlays(sid);
	}

	hc.setColumnMemory(false);
	while ( !hc.atEnd() && hscope.isWithinSelection(hc))
	{
		int ln = hc.lineNumber();

		QDocumentLine l = hc.line();
		//TODO: Why is this needed ?????  It makes absolutely no sense, but if it isn't there, deleting a search text step by step and then adding the characters again, creates artifact overlays
		l.setFlag(QDocumentLine::FormatsApplied, false);

		const QString &s = boundaries.endLine != ln ? l.text() : l.text().left(boundaries.end);

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
											
				hc.line().addOverlay(QFormatRange(hc.anchorColumnNumber(), hc.columnNumber() - hc.anchorColumnNumber(), sid));
				m_highlights.insert(l.handle());
			}
		} else hc.movePosition(1, QDocumentCursor::NextBlock, QDocumentCursor::ThroughFolding);
	}
    int begLine=0;
    int endLine=d->lines();
    int offset=0;
    int endOffset=-1;
    if (m_scope.isValid() && m_scope.hasSelection()){
        QDocumentSelection boundaries=m_scope.selection();
        begLine=boundaries.startLine;
        endLine=boundaries.endLine+1;
        offset=boundaries.start;
        endOffset=boundaries.end;
    }
    if(clearSelection){
        // don't run again when only visibleLines is changed
        // remove old marks first
        m_editor->removeMark("search");
        bool needsUpdate=false;
        for(int i=begLine;i<endLine;i++){
            QString txt=d->line(i).text();
            if((endOffset>=0)&&(i+1==endLine)){
                txt=txt.left(endOffset);
            }
            if(m_regexp.indexIn(txt,offset)>-1){
                m_editor->addMarkDelayed(i,Qt::darkYellow,"search");
                needsUpdate=true;
            }
            offset=0;
        }
        if(needsUpdate)
            m_editor->paintMarks();
    }
	m_editor->viewport()->update();
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

	int sid = doc->getFormatId("search");

	foreach (QDocumentLineHandle* h, m_highlights)
		QDocumentLine(h).clearOverlays(sid);

    m_editor->removeMark("search");
    m_editor->removeMark("replace");
	m_highlights.clear();
    m_newReplacementOverlays.clear();
	m_searchedScope = QDocumentCursor();
	//qDebug("clearing matches");

	clearReplacements();
	m_editor->viewport()->update();
}

void QDocumentSearch::clearReplacements(){
	m_lastReplacedPosition = QDocumentCursor();
	
	QDocument* doc= currentDocument();
	if ( !doc )
		return;

	int sid = doc->getFormatId("replacement");

	foreach (QDocumentLineHandle* l, m_highlightedReplacements)
		QDocumentLine(l).clearOverlays(sid);
//	m_editor->viewport()->update();

	m_highlightedReplacements.clear();
}

/*
  returns the document the search should be performed
  */
QDocument* QDocumentSearch::currentDocument(){
	return m_editor ? m_editor->document() : m_cursor.document();
}

/*
  returns a regexp which fully describes the search text (including flags like casesensitivity, wholewords,...)
  */
void QDocumentSearch::recreateRegExp(){
	Qt::CaseSensitivity cs = hasOption(CaseSensitive)
								?
									Qt::CaseSensitive
								:
									Qt::CaseInsensitive;
	
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
	if (m_string == f) 
		return;
	
	m_string = f;
	
	if (hasOption(HighlightAll) && !m_string.isEmpty()) {
		searchMatches();
		clearReplacements();
	} else
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
	if ( ((m_option & opt) != 0) == on)
		return; //no change, option already set

	if (opt != QDocumentSearch::Replace) //don't clear replacement markers if toggling replace (important to jump back to last replacement if the panel is closed)
		clearReplacements();

	if ( on )
		m_option |= opt;
	else
		m_option &= ~opt;

	if ( (opt & QDocumentSearch::HighlightAll) )
	{
		//prevent multiple connections
		if (m_editor->document()) {
			disconnect(m_editor->document(),SIGNAL(contentsChange(int, int)),this,SLOT(documentContentChanged(int, int)));
			disconnect(m_editor->document(),SIGNAL(lineDeleted(QDocumentLineHandle*)), this, SLOT(lineDeleted(QDocumentLineHandle*)));
			disconnect(m_editor->document(),SIGNAL(lineRemoved(QDocumentLineHandle*)), this, SLOT(lineDeleted(QDocumentLineHandle*)));
			connectToEditor();
		}
		if ( !on  )
			clearMatches();
		else if ( on )
			searchMatches();
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
		visibleLinesChanged();
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
	m_lastReplacedPosition = QDocumentCursor();
}


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
			//else if ( c == '0' )
			//	es += '\0';
			else es += '\\', es += c;

		} else {
			es += s.at(i);
		}
	}

	//qDebug("\"%s\" => \"%s\"", qPrintable(s), qPrintable(es));

	return es;
}

/*!
	\return the replacement text after expanding escape characters
*/

QString QDocumentSearch::replaceTextExpanded() const
{
	QString replacement = hasOption(EscapeSeq)?escapeCpp(m_replace):m_replace;

	if (hasOption(RegExp))
#if QT_VERSION<0x040600
	   for ( int i = m_regexp.numCaptures(); i >= 0; --i )
#else
	   for ( int i = m_regexp.captureCount(); i >= 0; --i )
#endif
			replacement.replace(QString("\\") + QString::number(i),
								m_regexp.cap(i));
	return replacement;
}

QDocumentCursor QDocumentSearch::lastReplacedPosition() const{
	return m_lastReplacedPosition;
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
	m_lastReplacedPosition = QDocumentCursor();
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
	if ( c.selectionStart() == m_scope.selectionStart() && c.selectionEnd() == m_scope.selectionEnd() )
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
	if (hasOption(HighlightAll)) searchMatches();
	else m_editor->viewport()->update();
}

/*!
	\brief Perform a search
	\param backward whether to go backward or forward
	\param all if true, the whole document will be searched first, all matches recorded and available for further navigation
	\param again if a search match is selected it will be replaced, than a normal search (no replace) will be performed
	\return The number of found occurences

	\note The search will start at the first character left/right from the selected text
*/
int QDocumentSearch::next(bool backward, bool all, bool again, bool allowWrapAround, const QDocumentCursor* overrideScope)
{
	if ( m_string.isEmpty() )
		return 0;

    if ( overrideScope && !overrideScope->isValid() ) overrideScope = nullptr;
	
	const QDocumentCursor& scope = overrideScope ? *overrideScope : m_scope;
	
	if ( m_cursor.isNull() )
	{
		if ( scope.isValid() && scope.hasSelection() )
		{
			if ( backward )
				m_cursor = scope.selectionEnd();
			else
				m_cursor = scope.selectionStart();
		} else if ( m_editor ) {
			
			m_cursor = QDocumentCursor(m_editor->document());
			
			if ( backward )
				m_cursor.movePosition(1, QDocumentCursor::End);
			
		} else {
            QMessageBox::warning(nullptr, nullptr, "Unable to perform search operation");
		}
	}

	QDocumentCursor firstMatch;

	recreateRegExp();
	
	int replaceCount = 0;
	
	// replace
	if (hasOption(Replace) && again && !all) {
		bool replaceSelectedText = false;
		if (m_regexp.exactMatch(m_cursor.selectedText()))  {
			replaceSelectedText = true;
		} else if (m_regexp.pattern().contains("(?=") or m_regexp.pattern().contains("(?!")) {
			// special handling for lookahead: The selected text is not enough to match the regexp
			// because the lookahead context is missing. Therefore we have to find matches to the
			// whole line until we find the original selection. Only then, we know that the original
			// selection is match and should be replaced.
			int start = 0;
			while (true) {
				start = m_regexp.indexIn(m_cursor.line().text(), start);
				if (start < 0)
					break;
				int end = start + m_regexp.matchedLength();
				if ((start == m_cursor.startColumnNumber() && end == m_cursor.endColumnNumber()) ||
				    (end == m_cursor.startColumnNumber() && start == m_cursor.endColumnNumber())) {
					replaceSelectedText = true;
				}
				start = end;
			}
		}
		if (replaceSelectedText) {
			replaceCursorText(backward);
			updateReplacementOverlays();
			replaceCount++;
			//foundCount++; we can't set this here, because it has to search the next match
			//and if (foundCount) is true, it thinks already found something and doesn't restart from scope
		}

	}

	// search next
	//ensure that the current selection isn't searched
	if ( m_cursor.hasSelection() ) {
		if (m_cursor.selectionStart() == scope.selectionStart() &&
			m_cursor.selectionEnd() == scope.selectionEnd()) {
			//search whole scope
			if (backward) m_cursor=scope.selectionEnd();
			else m_cursor=scope.selectionStart();
		} else {
			if (backward ^ all) //let all search in the selection
				m_cursor=m_cursor.selectionStart();
			else
				m_cursor=m_cursor.selectionEnd();
		}
	}
	
	QDocumentSelection boundaries = {0,0,0,0};
	bool bounded = scope.isValid() && scope.hasSelection();
	
	// condition only to avoid debug messages...
	if ( bounded ) {
		boundaries = scope.selection();
	
		//moves the cursor in the search scope if it isn't there, but directly in front of the selection (only possible if there actually is a selection)
		if (   ( backward ? m_cursor.atStart() : m_cursor.atEnd() )                              //absEnd
		    || ( scope.isValid() && scope.hasSelection() && !scope.isWithinSelection(m_cursor) )
		   ) {
			if ( !backward && m_cursor < scope.selectionStart() ) {
				m_cursor = scope.selectionStart();
			} else {
				if ( backward && m_cursor > scope.selectionEnd() )
					m_cursor = scope.selectionEnd();
			}
		}
	}
	
	bool realReplace=hasOption(Replace) && (!again || all);
	
	QDocumentCursor::MoveOperation move;
	
	move = backward ? QDocumentCursor::PreviousBlock : QDocumentCursor::NextBlock;	
	
	int foundCount = 0;

	if (m_editor && hasOption(Replace) && all && !hasOption(Prompt)){
		m_editor->document()->beginMacro();
		m_editor->document()->beginDelayedUpdateBlock();
	}
	
	m_cursor.setColumnMemory(false);
	QDocumentCursor lastSelection;
	while ( !( 
	             ( backward ? m_cursor.atStart() : m_cursor.atEnd() )                              //absEnd
	          || ( scope.isValid() && scope.hasSelection() && !scope.isWithinSelection(m_cursor) )
	      ) )
	{
		if ( backward && !m_cursor.columnNumber() )
		{
			m_cursor.movePosition(1, QDocumentCursor::PreviousCharacter, QDocumentCursor::ThroughFolding);
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
				
				if ( m_editor && !hasOption(Silent)) {
					if (!all || hasOption(Prompt)) {
						m_editor->setCursor(m_cursor, false);
						m_editor->ensureCursorVisible(QEditor::Navigation);
					} else lastSelection = m_cursor;
				}
				
				foundCount++;
				if ( foundCount == 1 ) {
					firstMatch = m_cursor;
					firstMatch.setAutoUpdated(true);
				}
				
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
							return foundCount;
						}
					}
					
					if ( rep ) {
						replaceCursorText(backward);
						if (!all) updateReplacementOverlays();
						replaceCount++;
					}
				} 
				
				
				if ( !all )
					break;
			}
		} else 
			m_cursor.movePosition(1, move, QDocumentCursor::ThroughFolding);
	}
	if ( all && replaceCount )
		updateReplacementOverlays();
	if ( m_editor && hasOption(Replace) && all && !hasOption(Prompt)) {
		m_editor->document()->endDelayedUpdateBlock();
		m_editor->document()->endMacro();
		if (!hasOption(Silent)){
            //m_editor->setCursor(lastSelection, false);
			m_editor->ensureCursorVisible(QEditor::Navigation);
		}
	}
		
	if ( !foundCount && allowWrapAround)
	{
		m_cursor = QDocumentCursor();
			
		int ret = QMessageBox::Yes; //different to base qce2.2, where it defaults to ::no if silent
		if ( !hasOption(Silent) /*&& hasOption(Prompt), to ask or not to ask that is the question; if it doesn't ask it fails silently if no match exists*/){
			QString message;
			if (backward) {
				message = tr(
							  "Start of scope reached with no match.\n"
							  "Restart from the end?"
						  );
			} else {
				message = tr(
							  "End of scope reached with no match.\n"
							  "Restart from the beginning?"
						  );
			}
			ret=QMessageBox::question(
							m_editor,
							tr("Failure"),
							message,
							QMessageBox::Yes
							| QMessageBox::No,
							QMessageBox::Yes
						);
		}
		if ( ret == QMessageBox::Yes )
			return next(backward, all, again, false);
	}
	
	if ( !foundCount )
		m_cursor = QDocumentCursor();
	
	if ( all && foundCount ) {
		if ( allowWrapAround ) {
			int ret = QMessageBox::Yes; //different to qce, see above
			if ( !hasOption(Silent) )
				ret=QMessageBox::question(
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
				QDocumentCursor newScope(backward?firstMatch.selectionEnd():firstMatch.selectionStart());
				if ( !backward ) newScope.movePosition(0,QDocumentCursor::Start,QDocumentCursor::KeepAnchor);
				else newScope.movePosition(0,QDocumentCursor::End,QDocumentCursor::KeepAnchor);
				if (scope.isValid() && scope.hasSelection()) newScope = scope.intersect(newScope);			
				m_cursor = QDocumentCursor();

				int result = foundCount;
				if (newScope.isValid() && newScope.hasSelection() )
					result += next(backward, all, again, false, &newScope);

				return result;
			}
		} else if ( !hasOption(Silent) )
			QMessageBox::information(m_editor,tr("Replacing Finished"),tr("%1 (of %2) occurences have been replaced").arg(replaceCount).arg(foundCount),QMessageBox::Ok);
	}
	
	
	return foundCount;
}
/*! @} */



void QDocumentSearch::replaceCursorText(bool backward){
	QDocumentSelection old_boundaries = m_cursor.selection();
	m_cursor.replaceSelectedText(replaceTextExpanded());
	m_newReplacementOverlays << QPair<QDocumentSelection,QDocumentSelection>(old_boundaries, m_cursor.selection());

	m_lastReplacedPosition = m_cursor;
	
	//make sure that the cursor if  the correct side of the selection is used
	//(otherwise the cursor could be moved out of the searched scope by a long 
	//replacement text)
	if (m_cursor.hasSelection()) {
		if (backward) m_cursor=m_cursor.selectionStart();
		else m_cursor=m_cursor.selectionEnd();
	}
}

void QDocumentSearch::updateReplacementOverlays(){
	if (m_newReplacementOverlays.isEmpty()) return;
	QDocument* d = m_cursor.document();
	if (!d) {
		m_newReplacementOverlays.clear();
		return;
	}
	int rid = d->getFormatId("replacement");
    m_editor->removeMark("replace");
	if (!hasOption(HighlightReplacements) || !rid)  {
		m_newReplacementOverlays.clear();
		return;
	}
	for (int i=0;i<m_newReplacementOverlays.size();i++) {
		const QDocumentSelection& boundaries = m_newReplacementOverlays[i].second;
		QDocumentLine startLine = d->line(boundaries.startLine);
		QDocumentLine endLine = d->line(boundaries.endLine);
		m_highlightedReplacements.insert(startLine.handle());
        if (boundaries.startLine == boundaries.endLine){  //single line replacement
			startLine.addOverlay(QFormatRange(boundaries.start, boundaries.end - boundaries.start, rid));
            m_editor->addMark(boundaries.startLine,Qt::red,"replace");
		} else {
			//multi line replacement
			m_highlightedReplacements.insert(endLine.handle());
			startLine.addOverlay(QFormatRange(boundaries.start, startLine.length() - boundaries.start, rid));
			endLine.addOverlay(QFormatRange(0, boundaries.end, rid));
            m_editor->addMarkRange(boundaries.startLine,boundaries.endLine,Qt::red,"replace");
			for (int i=boundaries.startLine+1; i<boundaries.endLine; i++){
				QDocumentLine curLine = d->line(i);
				m_highlightedReplacements.insert(curLine.handle());
				curLine.addOverlay(QFormatRange(0,curLine.length(),rid));
			}
		}
	}
	/*
	//highlight replacement, save old overlays
	//old overlays
	QList<QFormatRange> oldOverlays;
	int firstLine = m_newReplacementOverlays.first().first.startLine;
	int endLine = qMin(m_newReplacementOverlays.last().first.endLine, d->lineCount()-1);
	for (int l = firstLine; l<=endLine; l++) {
		
	}

	QDocumentSelection boundaries = m_cursor.selection();
			shift = -boundaries.end;
	
	QDocumentLine startLine = d->line(boundaries.startLine);
	QDocumentLine endLine = d->line(boundaries.endLine);
			oldOverlaysBefore = startLine.getOverlays(rid);
			for (int i=oldOverlaysBefore.size()-1;i>=0;i--)
				if (oldOverlaysBefore[i].offset + oldOverlaysBefore[i].length > boundaries.start)
					oldOverlaysBefore.removeAt(i);
			oldOverlaysAfter = endLine.getOverlays(rid);
			for (int i=oldOverlaysAfter.size()-1;i>=0;i--)
				if (oldOverlaysAfter[i].offset < boundaries.end)
					oldOverlaysAfter.removeAt(i);
			startLine.clearOverlays(rid);
			endLine.clearOverlays(rid);
		}
	}

	//highlight replacement
	if (rid) {
		//restore old
		QDocumentSelection boundaries = m_cursor.selection();
		shift += boundaries.end;

		QDocumentLine startLine = d->line(boundaries.startLine);
		QDocumentLine endLine = d->line(boundaries.endLine);
		foreach (const QFormatRange& frb, oldOverlaysBefore)
			startLine.addOverlay(frb);
		foreach (const QFormatRange& fra, oldOverlaysAfter)
			endLine.addOverlay(QFormatRange(fra.offset+shift,fra.length,fra.format));

		//add new overlay
	}*/
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
	c.setColumnMemory(false);
	c.setLineNumber(lineend, QDocumentCursor::KeepAnchor);
	c.setColumnNumber(le.length(), QDocumentCursor::KeepAnchor);
	highlightSelection(c);
	searchMatches(c,false);
}

void QDocumentSearch::visibleLinesChanged(){
	if (!hasOption(HighlightAll)) return;
	searchMatches(QDocumentCursor(), false, false);
}

void QDocumentSearch::highlightSelection(const QDocumentCursor& subHighlightScope)
{
	if (hasOption(Silent))
		return;

	if (!m_editor || !m_editor->document()) return;

	int sid = m_editor->document()->getFormatId("selection");
	if (!sid) return;

	int begLine, endLine, begCol, endCol;
	if( m_highlightedScope.isValid() && m_highlightedScope.hasSelection() ){
		m_highlightedScope.boundaries(begLine, begCol, endLine, endCol);
		if (subHighlightScope.isValid() && subHighlightScope.hasSelection())
			subHighlightScope.intersectBoundaries(begLine, begCol, endLine, endCol);
		for(int i=begLine;i<=endLine;i++)
			m_editor->document()->line(i).clearOverlays(sid);
		m_highlightedScope = QDocumentCursor();
	}

	if( m_scope.isValid() && m_scope.hasSelection() ){
		m_scope.boundaries(begLine, begCol, endLine, endCol);
		if (subHighlightScope.isValid() && subHighlightScope.hasSelection())
			subHighlightScope.intersectBoundaries(begLine, begCol, endLine, endCol);
		for(int i=begLine;i<=endLine;i++){
			int beg = i==begLine ? begCol : 0;
			int en = i==endLine ? endCol : m_editor->document()->line(i).length();
			m_editor->document()->line(i).addOverlay(QFormatRange(beg, en-beg, sid));
		}

		m_highlightedScope = m_scope;
		m_highlightedScope.setAutoUpdated(true);
	}
}

void QDocumentSearch::lineDeleted(QDocumentLineHandle* line){
	m_highlightedReplacements.remove(line);
	m_highlights.remove(line);
}
//TODO:  disable seleciton hide
