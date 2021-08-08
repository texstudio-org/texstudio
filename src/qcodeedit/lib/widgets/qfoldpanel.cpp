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
 :	QPanel(p), m_width(0)
{
	setWidth(12);
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

void QFoldPanel::setWidth(int w)
{
	w = qMax(w, 5);
	if (w != m_width) {
		m_width = w;
		setFixedWidth(w);
	}
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
	if (editor()->document()->line(line).isValid())
		emit contextMenuRequested(line, e->globalPos());
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

    qreal pos,
        max = doc->lines(),
        ls = doc->getLineSpacing(),
		pageBottom = e->viewport()->height(),
		contentsY = e->verticalOffset();

    qreal xMid = m_width / 2;
    qreal iconSize = (m_width * 3)/ 4;
    qreal xIconOffset = (m_width - iconSize) / 2;
    qreal yIconOffset = (ls - iconSize) / 2;
	
	pos = - contentsY;

	//qDebug("beg pos : %i", pos);

	p->save();
	QPen linePen(QColor(128,0,128));
    qreal lineWidth = m_width / 5;

	linePen.setWidth(lineWidth);
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

        qreal len = ls * line.lineSpan();

		bVisible = ((pos + len) >= 0);

		if (bVisible) {

			if ( fli.open ) {
				bool isCollapsed = line.hasFlag(QDocumentLine::CollapsedBlockStart);
                qreal topLineEnd = yIconOffset;
                qreal bottomLineStart = yIconOffset + iconSize;
				if (isCollapsed) {  // a bit more space for collapsed icons
					topLineEnd -= 1;
					bottomLineStart += 1;
				}

				// line above icon
				if (topLineEnd > 0 && fli.lineNr <= endHighlightLineNr)
                    p->drawLine(QPointF(xMid, pos), QPointF(xMid, pos + topLineEnd));

				// draw icon
				m_lines << fli.lineNr;
                m_rects << QRectF(0, pos, m_width, ls);
				drawIcon(p, e, xIconOffset, pos + yIconOffset, iconSize, isCollapsed, fli.lineNr == m_lastMouseLine);

				if (!isCollapsed && fli.lineNr == m_lastMouseLine) {
					// found the line with the mouse -> determine end of highlighting
					QFoldedLineIterator findEnd = fli;
					findEnd.incrementUntilBlockEnd();
					endHighlightLineNr = findEnd.lineNr;
				}

				// line below icon
				if (bottomLineStart < len && fli.lineNr < endHighlightLineNr)
                    p->drawLine(QPointF(xMid, pos + bottomLineStart), QPointF(xMid, pos + len));
			} else if (fli.lineNr <= endHighlightLineNr) {
				if ( fli.lineNr == endHighlightLineNr ) {
                    qreal mid = pos + len - ls / 6;
                    p->drawLine(QPointF(xMid, pos), QPointF(xMid, mid)); // line ending here
				} else {
                    p->drawLine(QPointF(xMid, pos), QPointF(xMid, pos + len)); // line continues
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
		if (doc) {
			QLanguageDefinition *def = doc->languageDefinition();

			QHelpEvent* helpEvent = static_cast<QHelpEvent*>(e);
			int line = mapRectPosToLine(helpEvent->pos());
			if ( def && line != -1){
				QFoldedLineIterator it = def->foldedLineIterator(doc, line);
				it.incrementUntilBlockEnd();
				if (doc->line(line).hasFlag(QDocumentLine::CollapsedBlockStart) || (editor()->getLastVisibleLine() < it.lineNr)) {
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
		}
	}
	return QWidget::event(e);
}

int QFoldPanel::mapRectPosToLine(const QPointF& p){
	for ( int i = 0; i < m_rects.count(); ++i )
	{
		if ( !m_rects.at(i).contains(p) )
			continue;

		return m_lines.at(i);
	}
	return -1;
}


QRectF QFoldPanel::drawIcon(	QPainter *p, QEditor *,
                            qreal x, qreal y, int iconSize, bool toExpand, bool highlight)
{
	int tailSpacing = iconSize / 4;
    QRectF symbolRect(x, y, iconSize, iconSize);

	p->save();

	p->setRenderHint(QPainter::Antialiasing);

	if (toExpand) {
		// rightarrow
		p->translate(tailSpacing, 0);
		QPainterPath path;
		path.moveTo(x, y);
		path.lineTo(x, y+iconSize);
		path.lineTo(x+float(iconSize)/2, y+float(iconSize)/2);
		path.lineTo(x, y);

		p->fillPath(path,  highlight ? QColor(128,0,128) : QColor(96,96,96));
	} else {
		// downarrow
		p->translate(0, tailSpacing);
		QPainterPath path;
		path.moveTo(x, y);
		path.lineTo(x+iconSize, y);
		path.lineTo(x+float(iconSize)/2, y+float(iconSize)/2);
		path.lineTo(x, y);

		p->fillPath(path,  highlight ? QColor(128,0,128) : QColor(160,160,160));
	}

	p->restore();
	return symbolRect;
}

void QFoldPanel::setFont_slot(const QFont &font)
{
	setWidth(font.pointSize() + 2);
	setFont(font);
}

void QFoldPanel::editorChange(QEditor *e)
{
	if ( editor() )
	{
		disconnect( editor()->document(), SIGNAL( fontChanged(QFont) ),
					this	, SLOT  ( setFont_slot(QFont) ) );
	}

	if ( e )
	{
		connect(e->document(), SIGNAL( fontChanged(QFont) ),
				this, SLOT  ( setFont_slot(QFont) ) );
	}
}


/*! @} */
