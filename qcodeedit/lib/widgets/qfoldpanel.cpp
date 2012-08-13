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

void QFoldPanel::contextMenuEvent(QContextMenuEvent *e)
{
	if (!editor() || !editor()->languageDefinition()) {
		QPanel::contextMenuEvent(e);
		return;
	}

	QMenu menu(this);
	menu.addAction(tr("Expand All"));
	if (menu.exec(e->globalPos())) {
		QDocument *doc = editor()->document();
		QLanguageDefinition *def = editor()->languageDefinition();

		for (int ln = 0; ln < doc->lineCount(); ln++) {
			QDocumentLine b = doc->line(ln);
			if ( b.hasFlag(QDocumentLine::CollapsedBlockStart) )
				def->expand(doc, ln);
		}
		editor()->setFocus();
	}
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

	int pos,
		max = doc->lines(),
		ls = doc->getLineSpacing(),
		pageBottom = e->viewport()->height(),
		contentsY = e->verticalOffset();
	
	pos = - contentsY;

	//qDebug("beg pos : %i", pos);

	QFoldedLineIterator fli = def->foldedLineIterator(doc);

	bool oldFolding=false;

	for (; fli.lineNr<max; ++fli)
	{
		if ( pos > pageBottom )
			break;

		const QDocumentLine &line=fli.line;

		if ( fli.lineFlagsInvalid() ){
			//correct folding when the folding of the current line is invalid
			//problems: slow (but O(n) like the paint method is anyways), doesn't work if panel is hidden
			//pro: simple, doesn't correct invalid, but invisible folding (e.g. like folding that is only temporary invalid, until the user writes a closing bracket; otherwise writing $$ would expand every folded $-block)
			doc->correctFolding(fli.lineNr, doc->lines()); //this will again call paint
			return true;
		}

		if ( line.isHidden() )
		{
			continue;
		}

		int len = ls * line.lineSpan();

//		bool oldFolding = !fli.openParentheses.empty() && fli.openParentheses.first().line!=fli.lineNr;

		bVisible = ((pos + len) >= 0);

		if ( fli.open )
		{
			if ( line.hasFlag(QDocumentLine::CollapsedBlockStart) )
			{
				// outermost block folded : none of the opening is actually opened
				int bound = (ls - 8) / 2;
				int mid = pos + len - ls / 6;

				if ( bVisible )
				{
					// draw icon

					if ( bound > 0 && oldFolding )
					{
						p->drawLine(7, pos, 7, pos + bound);
					}

					if ( fli.close )
					{
						p->drawLine(7, pos + 8 + bound, 7, mid);
						p->drawLine(7, mid, 12, mid);
					}

					m_lines << fli.lineNr;
					m_rects << drawIcon(p, e, 3, pos + bound, true);
				}

				int firstParenthesisPos = fli.openParentheses.size() - fli.open;
				const FoldedParenthesis firstParenthesis = fli.openParentheses[firstParenthesisPos];

				while (fli.lineNr<doc->lines() &&
				       firstParenthesisPos<fli.openParentheses.size() &&
				       fli.openParentheses[firstParenthesisPos] == firstParenthesis){
					if (fli.lineNr < doc->lines()-1 && !doc->line(fli.lineNr+1).isHidden()) {
						if ( bVisible )
							p->drawLine(7, pos + 8 + bound, 7, pos + len);
						break;
					}
					++fli;
				}

				if ( bVisible && !fli.openParentheses.empty() )
				{
					if ( fli.close )
						p->drawLine(7, mid, 7, pos + len);
					else
						p->drawLine(7, pos + 8 + bound, 7, pos + len);
				}
			} else {
				if ( bVisible )
				{
					int bound = (ls - 8) / 2;

					if ( oldFolding && bound > 0 )
						p->drawLine(7, pos, 7, pos + bound);

					m_lines << fli.lineNr;
					m_rects << drawIcon(p, e, 3, pos + bound, false);

					int mid = pos + len - ls / 6;

					if ( fli.close )
						p->drawLine(7, mid, 12, mid);

					if ( bound > 0 )
						p->drawLine(7, pos + 8 + bound, 7, pos + len);
				}
			}
		} else if ( (oldFolding) && bVisible ) {
			if ( fli.close )
			{
				int mid = pos + len - ls / 6;

				p->drawLine(7, pos, 7, mid);
				p->drawLine(7, mid, 12, mid);

				if ( !fli.openParentheses.empty() )
					p->drawLine(7, pos, 7, pos + len);
			} else  {
				p->drawLine(7, pos, 7, pos + len);
			}
		}

		pos += len;
		oldFolding=!fli.openParentheses.empty();
	}
	
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
			if (it.lineNr - line < 16)
				tooltip = doc->exportAsHtml(doc->cursor(line,0,it.lineNr),true,true);
			else {
				tooltip = doc->exportAsHtml(doc->cursor(line,0,line+7),true,true);
				tooltip.replace("</body></html>","");
				tooltip += "<br>...<br>";
				tooltip += doc->exportAsHtml(doc->cursor(it.lineNr-7,0,it.lineNr),false);
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
							int x, int y, bool toExpand)
{
	QRect symbolRect(x, y, 8, 8);

	//p->save();
	//p->setRenderHint(QPainter::Antialiasing);
	p->drawRect(symbolRect);
	//p->restore();

	if ( toExpand )
	{
		p->drawLine(x + 2, y + 4, x + 6, y + 4);
		p->drawLine(x + 4, y + 2, x + 4, y + 6);
	} else {
		p->drawLine(x + 2, y + 4, x + 6, y + 4);
	}

	return symbolRect;
}

/*! @} */
