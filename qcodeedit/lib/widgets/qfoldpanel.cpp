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

#include <QBitmap>
#include <QPainter>
#include <QScrollBar>
#include <QMouseEvent>

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
	
	bool act = false;
	QDocument *doc = editor()->document();
	QLanguageDefinition *def = editor()->languageDefinition();
	
	for ( int i = 0; i < m_rects.count(); ++i )
	{
		if ( !m_rects.at(i).contains(e->pos()) )
			continue;
		
		int ln = m_lines.at(i);
		
		QDocumentLine b = doc->line(ln);
		
		if ( b.hasFlag(QDocumentLine::CollapsedBlockStart) )
			def->expand(doc, ln);
		else if ( def->blockFlags(doc, ln, 0) & QLanguageDefinition::Collapsible )
			def->collapse(doc, ln);
		
		act = true;
	}
	
	if ( act )
		editor()->setFocus();
	else
		QPanel::mousePressEvent(e);
	
}

/*!

*/
void QFoldPanel::paint(QPainter *p, QEditor *e)
{
	QDocument *doc = editor()->document();
	QLanguageDefinition *def = e->languageDefinition();
	
	if ( !def || !doc )
	{
		return;
	}
	
	m_rects.clear();
	m_lines.clear();
	
	bool bVisible = false; //,
	//	inCursorBlock = false;
	
	QDocumentLine block;
	const QFontMetrics fm(doc->font());
	
	int n,
		pos,
		depth = 0,
		max = doc->lines(),
		h = fm.height(),
		ls = fm.lineSpacing(),
		pageBottom = e->viewport()->height(),
		contentsY = e->verticalScrollBar()->value();
	
	pos = - contentsY;
	
	//qDebug("beg pos : %i", pos);
	
	for ( n = 0; n < max; ++n )
	{
		if ( pos > pageBottom )
			break;
		
		block = doc->line(n);
		
		if ( block.isHidden() )
		{
			continue;
		}
		
		int len = ls * block.lineSpan();
		int flags = def->blockFlags(doc, n, depth);
		
		bVisible = ((pos + len) >= 0);
		
		int off = flags & QLanguageDefinition::DataMask;
		
		if ( flags & QLanguageDefinition::Closure )
		{
			int mid = pos + len - ls / 4;
			
			// in case of mixup be smart...
			if ( flags & QLanguageDefinition::Collapsible )
			{
				// special mixup handling...
				//if ( block.hasFlag(QDocumentLine::CollapsedBlockEnd) )
				//	--off;
				
				depth += off;
				
				if ( !bVisible )
				{
					pos += len;
					continue;
				}
				
				// draw icon
				int bound = (ls - 8) / 2;
				
				if ( depth > off && bound > 0 )
					p->drawLine(7, pos, 7, pos + bound);
				
				m_lines << n;
				m_rects << drawIcon(p, e, 3, pos + bound, false);
				
				if ( bound > 0 )
					p->drawLine(7, pos + 8 + bound, 7, pos + len);
				
			} else if ( flags & QLanguageDefinition::Collapsed ) {
				// special mixup handling...
				
				--depth;
				
				//depth += off - 1;
				
				int bound = (ls - 8) / 2;
				
				if ( bVisible )
				{
					// draw icon
					
					if ( bound > 0 )
					{
						if ( depth >= 0 )
						{
							p->drawLine(7, pos, 7, pos + bound);
							
							if ( depth > 0 )
								p->drawLine(7, pos + 8 + bound, 7, pos + len);
						} else if ( 0 ) { // off ) {
							p->drawLine(7, pos + 8 + bound, 7, pos + len);
						}
					}
					
					m_lines << n;
					m_rects << drawIcon(p, e, 3, pos + bound, true);
				}
				
				int sub = off - 1;
				
				while ( sub > 0 && ((n + 1) < max) )
				{
					++n;
					block = doc->line(n);
					
					if ( !block.isHidden() )
					{
						// special handling when mixed closure/opening on the same line
						++depth;
						
						if ( bVisible )
							p->drawLine(7, pos + 8 + bound, 7, pos + len);
						
						--n;
						break;
					}
					
					flags = def->blockFlags(doc, n, depth + 1);
					
					int soff = flags & QLanguageDefinition::DataMask;
					
					if ( flags & (QLanguageDefinition::Collapsible | QLanguageDefinition::Collapsed) )
						sub += soff;
					else if ( flags & (QLanguageDefinition::Closure) )
						sub -= soff;
					
				}
				
				if ( sub < 0 )
				{
					depth += sub;
					
					//p->drawLine(7, pos + 8 + bound, 7, pos + ls);
					if ( bVisible && (depth > 0) )
						p->drawLine(7, pos + len, 12, pos + len);
				}
			} else {
				if ( depth > 0 )
					depth -= off;
				
				if ( !bVisible )
				{
					pos += len;
					continue;
				}
				
				p->drawLine(7, pos, 7, mid);
				p->drawLine(7, mid, 12, mid);
				
				if ( depth > 0 )
					p->drawLine(7, pos, 7, pos + len);
				
			}
			
		} else if ( flags & QLanguageDefinition::Collapsed ) {
			//no depth change : always fold outermost block when several start on the same line
			//depth += off - 1;
			
			int bound = (ls - 8) / 2;
			
			if ( bVisible )
			{
				// draw icon
				
				if ( bound > 0 )
				{
					if ( depth > 0 )
					{
						p->drawLine(7, pos, 7, pos + bound);
						p->drawLine(7, pos + 8 + bound, 7, pos + len);
					} else if ( 0 ) { // off ) {
						p->drawLine(7, pos + 8 + bound, 7, pos + len);
					}
				}
				
				m_lines << n;
				m_rects << drawIcon(p, e, 3, pos + bound, true);
			}
			
			int sub = off;
			
			while ( sub > 0 && ((n + 1) < max) )
			{
				++n;
				block = doc->line(n);
				
				if ( !block.isHidden() )
				{
					// special handling when mixed closure/opening on the same line
					++depth;
					
					if ( bVisible )
						p->drawLine(7, pos + 8 + bound, 7, pos + len);
					
					--n;
					break;
				}
				
				flags = def->blockFlags(doc, n, depth + 1);
				
				int soff = flags & QLanguageDefinition::DataMask;
				
				if ( flags & (QLanguageDefinition::Collapsible | QLanguageDefinition::Collapsed) )
					sub += soff;
				else if ( flags & (QLanguageDefinition::Closure) )
					sub -= soff;
				
			}
			
			if ( sub < 0 )
			{
				depth += sub;
				
				//p->drawLine(7, pos + 8 + bound, 7, pos + ls);
				if ( bVisible && (depth > 0) )
					p->drawLine(7, pos + len, 12, pos + len);
			}
		} else if ( flags & QLanguageDefinition::Collapsible ) {
			depth += off;
			
			if ( !bVisible )
			{
				pos += len;
				continue;
			}
			
			// draw icon
			int bound = (ls - 8) / 2;
			
			if ( depth > off && bound > 0 )
				p->drawLine(7, pos, 7, pos + bound);
			
			m_lines << n;
			m_rects << drawIcon(p, e, 3, pos + bound, false);
			
			if ( bound > 0 )
				p->drawLine(7, pos + 8 + bound, 7, pos + len);
			
		} else if ( bVisible && (depth > 0) ) {
			p->drawLine(7, pos, 7, pos + len);
		}
		
		pos += len;
	}
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
