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

#include "qfoldpanel.h"

/*!
	\file qfoldpanel.cpp
	\brief Implementation of the QFoldPanel class.

	\see QFoldPanel
*/

#include "qeditor.h"

#include "qdocument.h"
#include "qdocumentline.h"

#include "qlanguagedefinition.h"

/*!
	\ingroup widgets
	@{
*/

/*!
	\class QFoldPanel
	\brief A panel that draw fold indicators and provide fold/unfold actions to the user
*/

QCE_AUTO_REGISTER(QFoldPanel)

/*!
	\brief Constructor
*/
QFoldPanel::QFoldPanel(QWidget *p)
 :	QPanel(p)
{
	setFixedWidth(12);
	setObjectName("foldPanel");
	setMouseTracking(true);
	m_lastMouseLine = -1;
}

/*!
	\brief Empty destructor
*/
QFoldPanel::~QFoldPanel()
{

}

/*!

*/
QString QFoldPanel::type() const
{
	return "Fold indicators";
}

/*!

*/
void QFoldPanel::mousePressEvent(QMouseEvent *e)
{
	if ( !editor() || !editor()->languageDefinition() || (e->button() != Qt::LeftButton) )
	{
		QPanel::mousePressEvent(e);
		return;
	}


	QDocument *doc = editor()->document();
	QLanguageDefinition *def = editor()->languageDefinition();

	int ln = mapRectPosToLine(e->pos());
	if ( ln != -1 ){
		QDocumentLine b = doc->line(ln);

		if ( b.hasFlag(QDocumentLine::CollapsedBlockStart) )
			def->expand(doc, ln);
		else //if ( def->blockFlags(doc, ln, 0) & QLanguageDefinition::Collapsible ) collapse checks if it can collapse the line
			def->collapse(doc, ln);
		editor()->setFocus();
	} else
		QPanel::mousePressEvent(e);

}

void QFoldPanel::mouseMoveEvent(QMouseEvent *e)
{
	if ( !editor() || !editor()->languageDefinition() )
	{
		QPanel::mousePressEvent(e);
		return;
	}

	int ln = mapRectPosToLine(e->pos());
	if (ln != m_lastMouseLine){
		m_lastMouseLine = ln;
		repaint();
	} else
		QPanel::mousePressEvent(e);
	m_lastMouseLine = ln;
}

void QFoldPanel::leaveEvent(QEvent *)
{
	if (m_lastMouseLine > -1) {
		m_lastMouseLine = -1;
		repaint();
	}
}

/*!

*/
void QFoldPanel::contextMenuEvent(QContextMenuEvent *e)
{
	if (!editor() || !editor()->languageDefinition()) {
		QPanel::contextMenuEvent(e);
		return;
	}

	int line=editor()->document()->lineNumber(editor()->verticalOffset()+e->y());
	if (line>-1) emit contextMenuRequested(line, e->globalPos());
}


/*!

*/
bool QFoldPanel::paint(QPainter *p, QEditor *e)
{
	QDocument *doc = editor()->document();
	QLanguageDefinition *def = e->languageDefinition();

	if ( !def || !doc )
	{
		return true;
	}

	m_rects.clear();
	m_lines.clear();

	bool bVisible = false; //,
	//	inCursorBlock = false;

	int endHighlightLineNr = -1;

	int pos,
		max = doc->lines(),
		ls = doc->getLineSpacing(),
		pageBottom = e->viewport()->height(),
		contentsY = e->verticalOffset();

	int xMid = 6,
		iconSize = 9,
		yIconOffset = (ls - iconSize) / 2;
	
	pos = - contentsY;

	//qDebug("beg pos : %i", pos);

	p->save();
	QPen linePen(QColor(128,0,128));
	linePen.setWidth(3);
	linePen.setCapStyle(Qt::FlatCap);
	p->setPen(linePen);

	QFoldedLineIterator fli = def->foldedLineIterator(doc);

	for (; fli.lineNr<max; ++fli) {
		if ( pos > pageBottom )
			break;

		const QDocumentLine &line=fli.line;

		if ( fli.lineFlagsInvalid() ){
			//correct folding when the folding of the current line is invalid
			//problems: slow (but O(n) like the paint method is anyways), doesn't work if panel is hidden
			//pro: simple, doesn't correct invalid, but invisible folding (e.g. like folding that is only temporary invalid, until the user writes a closing bracket; otherwise writing $$ would expand every folded $-block)
			doc->correctFolding(fli.lineNr, doc->lines()); //this will again call paint
			break;
		}

		if ( line.isHidden() ) {
			continue;
		}

		int len = ls * line.lineSpan();

		bVisible = ((pos + len) >= 0);

		if (bVisible) {

			if ( fli.open ) {
				if ( line.hasFlag(QDocumentLine::CollapsedBlockStart) ) {

					 // line above icon
					int topLineEnd = yIconOffset-1;
					if (topLineEnd > 0 && fli.lineNr <= endHighlightLineNr)
						p->drawLine(xMid, pos, xMid, pos + topLineEnd);

					// draw icon
					m_lines << fli.lineNr;
					m_rects << drawIcon(p, e, 2, pos + yIconOffset, true, fli.lineNr == m_lastMouseLine);

					 // line below icon
					int bottomLineStart = yIconOffset + iconSize + 1;
					if (bottomLineStart < len && fli.lineNr < endHighlightLineNr)
						p->drawLine(xMid, pos + bottomLineStart, xMid, pos + len);
				} else {
					// line above icon
					int topLineEnd = yIconOffset;
					if (topLineEnd > 0 && fli.lineNr <= endHighlightLineNr)
						p->drawLine(xMid, pos, xMid, pos + topLineEnd);

					// draw icon
					m_lines << fli.lineNr;
					m_rects << drawIcon(p, e, 2, pos + yIconOffset, false, fli.lineNr == m_lastMouseLine);
					if (fli.lineNr == m_lastMouseLine) {
						QFoldedLineIterator findEnd = fli;
						findEnd.incrementUntilBlockEnd();
						endHighlightLineNr = findEnd.lineNr;
					}

					// line below icon
					int bottomLineStart = yIconOffset + iconSize;
					if ( bottomLineStart < len && fli.lineNr < endHighlightLineNr)
						p->drawLine(xMid, pos + bottomLineStart, xMid, pos + len);
				}
			} else if (fli.lineNr <= endHighlightLineNr) {
				if ( fli.lineNr == endHighlightLineNr ) {
					int mid = pos + len - ls / 6;
					p->drawLine(xMid, pos, xMid, mid); // line ending here
				} else {
					p->drawLine(xMid, pos, xMid, pos + len); // line continues
				}
			}
		}
		pos += len;
	}

	p->restore();
	return true;
}

bool QFoldPanel::event(QEvent *e) {
	if (e->type() == QEvent::ToolTip) {		
		QDocument *doc = editor()->document();
		QLanguageDefinition *def = doc->languageDefinition();

		QHelpEvent* helpEvent = static_cast<QHelpEvent*>(e);
		int line = mapRectPosToLine(helpEvent->pos());
		if ( def && doc && line != -1 && doc->line(line).hasFlag(QDocumentLine::CollapsedBlockStart) ){
			QFoldedLineIterator it = def->foldedLineIterator(doc, line);
			it.incrementUntilBlockEnd();
			QString tooltip;


			int lineWidth = 80;
			int maxShownLines = 9;
			int wrapCount = 2;
			if (editor()->flag(QEditor::HardLineWrap)) {
				lineWidth = -1; // rely on wrapping of editor
				maxShownLines = 15;
				wrapCount = 0;
			}

			if (it.lineNr - line < maxShownLines)
				tooltip = doc->exportAsHtml(doc->cursor(line,0,it.lineNr),true,true,lineWidth,wrapCount);
			else {
				tooltip = doc->exportAsHtml(doc->cursor(line,0,line+maxShownLines/2),true,true,lineWidth,wrapCount);
				tooltip.replace("</body></html>","");
				tooltip += "<br>...<br>";
				tooltip += doc->exportAsHtml(doc->cursor(it.lineNr-maxShownLines/2,0,it.lineNr),false,true,lineWidth,wrapCount);
				tooltip +=  "</body></html>";
			}
			if (tooltip.isEmpty()) QToolTip::hideText();
			else QToolTip::showText(helpEvent->globalPos(), tooltip);
			e->setAccepted(true);
		}
	}
	return QWidget::event(e);
}

int QFoldPanel::mapRectPosToLine(const QPoint& p){
	for ( int i = 0; i < m_rects.count(); ++i )
	{
		if ( !m_rects.at(i).contains(p) )
			continue;

		return m_lines.at(i);
	}
	return -1;
}


QRect QFoldPanel::drawIcon(	QPainter *p, QEditor *,
							int x, int y, bool toExpand, bool highlight)
{
	QRect symbolRect(x, y, 9, 9);

	p->save();

	p->setRenderHint(QPainter::Antialiasing);

	if (toExpand) {
		// rightarrow
		QPainterPath path;
		path.moveTo(x+2,y);
		path.lineTo(x+2,y+9);
		path.lineTo(x+7,y+4.5);
		path.lineTo(x+2,y);

		p->fillPath(path,  highlight ? QColor(128,0,128) : QColor(96,96,96));
	} else {
		// downarrow
		QPainterPath path;
		path.moveTo(x,y+2);
		path.lineTo(x+9,y+2);
		path.lineTo(x+4.5,y+7);
		path.lineTo(x,y+2);

		p->fillPath(path,  highlight ? QColor(128,0,128) : QColor(160,160,160));
	}
	/*

	p->fillRect(symbolRect, highlight ? QColor(128,0,128) : QColor(160,160,160));

	p->setPen(Qt::white);
	if ( toExpand )
	{
		p->drawLine(x + 2, y + 4, x + 6, y + 4);
		p->drawLine(x + 4, y + 2, x + 4, y + 6);
	} else {
		p->drawLine(x + 2, y + 4, x + 6, y + 4);
	}*/

	p->restore();
	return symbolRect;
}

/*! @} */
