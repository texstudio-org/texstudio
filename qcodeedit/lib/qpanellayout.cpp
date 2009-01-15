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

#include "qpanellayout.h"

#include "qpanel.h"
#include "qeditor.h"

#include <QWidget>
#include <QScrollBar>

/*
	The layouting code is inspired from a Qt4 example : Border Layout
*/

QPanelLayout::QPanelLayout(QEditor *p)
 : QLayout(p), m_parent(p)
{
	setSpacing(0);
}

QPanelLayout::QPanelLayout(const QString& layout, QEditor *p)
 : QLayout(p), m_parent(p)
{
	setSpacing(0);
	addSerialized(layout);
}

QPanelLayout::~QPanelLayout()
{
	QLayoutItem *l;
	
	while ( (l = takeAt(0)) )
		delete l;
}

QString QPanelLayout::serialized() const
{
	/*
		Scheme :
		
		QPanelLayout::Position '{' comma-separated list of identifiers '}'
	*/
	
	QHash<int, QString> posMap;
	
	for ( int i = 0; i < m_list.size(); ++i )
	{
		PanelWrapper *wrapper = m_list.at(i);
		Position position = wrapper->position;
		
		QPanel *panel = qobject_cast<QPanel*>(wrapper->item->widget());
		
		if ( !panel )
			continue;
		
		if ( !posMap.contains(position) )
		{
			posMap[position] = QString::number(position) + "{" + panel->id() + "}";
		} else {
			QString& ref = posMap[position];
			
			ref.insert(ref.count() - 2, QString(",") + panel->id());
		}
	}
	
	return QStringList(posMap.values()).join("");
}

void QPanelLayout::addSerialized(const QString& layout)
{
	//qDebug("layout : %s", qPrintable(layout));
	
	int last = 0, i = 0;
	bool inList = false;
	Position position = West;
	
	while ( i < layout.length() )
	{
		if ( inList )
		{
			if ( layout.at(i) == '}' )
				inList = false;
			
			if ( !inList || (layout.at(i) == ',') )
			{
				QPanel *panel = QPanel::panel(layout.mid(last, i - last), m_parent);
				
				if ( panel )
				{
					panel->attach(m_parent);
					addWidget(panel, position);
					
					//qDebug("\tpanel : %s", qPrintable(layout.mid(last, i - last)));
				}
				
				last = i + 1;
			}
		} else if ( layout.at(i) == '{' ) {
			inList = true;
			position = Position(layout.mid(last, i - last).toInt());
			
			//qDebug("position : %i [%s]", position, qPrintable(layout.mid(last, i - last)));
			
			last = i + 1;
		}
		
		++i;
	}
	
	update();
}

QList<QPanel*> QPanelLayout::panels() const
{
	QList<QPanel*> l;
	
	foreach ( PanelWrapper *w, m_list )
	{
		QPanel *p = qobject_cast<QPanel*>(w->item->widget());
		
		if ( p )
			l << p;
	}
	
	return l;
}

int QPanelLayout::count() const
{
	return m_list.count();
}

bool QPanelLayout::hasHeightForWidth() const
{
	return false;
}

Qt::Orientations QPanelLayout::expandingDirections() const
{
	return Qt::Horizontal | Qt::Vertical;
}

QSize QPanelLayout::sizeHint() const
{
	return calculateSize(SizeHint);
}

QSize QPanelLayout::minimumSize() const
{
	return calculateSize(MinimumSize);
}

void QPanelLayout::addItem(QLayoutItem *item)
{
	add(item, West);
}

void QPanelLayout::addWidget(QWidget *widget, Position position)
{
	add(new QWidgetItem(widget), position);
}

QLayoutItem* QPanelLayout::itemAt(int idx) const
{
	PanelWrapper *wrapper = m_list.value(idx);
	
	if ( wrapper )
		return wrapper->item;
	else
		return 0;
	
}

QLayoutItem* QPanelLayout::takeAt(int idx)
{
	if ( (idx >= 0) && (idx < m_list.size()) )
	{
		PanelWrapper *layoutStruct = m_list.takeAt(idx);
		return layoutStruct->item;
	}
	
	return 0;
}

void QPanelLayout::setGeometry(const QRect &r)
{
	//qDebug("laying out %i panels", count());
	#if 0
	QScrollBar *vb = m_parent->verticalScrollBar(),
			*hb = m_parent->horizontalScrollBar();
	
	QRect rect(	r.x(), r.y(),
				r.width() - (vb->isVisible() ? vb->width() : 0),
				r.height() - (hb->isVisible() ? hb->height() : 0)
				);
	#else
	QRect rect(	r.x(), r.y(),
				r.width(),
				r.height()
				);
	#endif
	
	int i,
		eastWidth = 0,
		westWidth = 0,
		northHeight = 0,
		southHeight = 0,
		centerHeight = 0;
	
	QLayout::setGeometry(rect);
	
	for ( i = 0; i < m_list.size(); ++i )
	{
		PanelWrapper *wrapper = m_list.at(i);
		QLayoutItem *item = wrapper->item;
		Position position = wrapper->position;
		
		if ( item->isEmpty()  )
			continue;
		
		if ( position == North )
		{
			item->setGeometry(QRect(
									rect.x(),
									northHeight,
									rect.width(),
									item->sizeHint().height()
									)
							);
			
			northHeight += item->geometry().height() + spacing();
		} else if (position == South) {
			item->setGeometry(QRect(item->geometry().x(),
									item->geometry().y(),
									rect.width(),
									item->sizeHint().height()
									)
							);
			
			southHeight += item->geometry().height() + spacing();
			
			item->setGeometry(QRect(rect.x(),
									rect.y() + rect.height() - southHeight + spacing(),
									item->geometry().width(),
									item->geometry().height()
									)
							);
			
		}
	}
	
	centerHeight = rect.height() - northHeight - southHeight;
	
	for ( i = 0; i < m_list.size(); ++i )
	{
		PanelWrapper *wrapper = m_list.at(i);
		QLayoutItem *item = wrapper->item;
		Position position = wrapper->position;
		
		if ( item->isEmpty() )
			continue;
		
		if ( position == West )
		{
			item->setGeometry(QRect(rect.x() + westWidth,
									northHeight,
									item->sizeHint().width(),
									centerHeight
									)
							);
			
			westWidth += item->geometry().width() + spacing();
		} else if (position == East) {
			item->setGeometry(QRect(item->geometry().x(),
									item->geometry().y(),
									item->sizeHint().width(),
									centerHeight
									)
							);
			
			eastWidth += item->geometry().width() + spacing();
			
			item->setGeometry(QRect(rect.x() + rect.width() - eastWidth + spacing(),
									northHeight,
									item->geometry().width(),
									item->geometry().height()
									)
							);
			
		}
	}
	
	/*
	if ( center )
		center->item->setGeometry(QRect(westWidth, northHeight,
										rect.width() - eastWidth - westWidth,
										centerHeight));
	*/
	//qDebug("{%i, %i, %i, %i}", westWidth, northHeight, eastWidth, southHeight);
	m_parent->setPanelMargins(westWidth, northHeight, eastWidth, southHeight);
}

void QPanelLayout::add(QLayoutItem *item, Position position)
{
	QPanel *p;
	
	if ( (p = qobject_cast<QPanel*>(item->widget())) )
	{
		//p->setParent(m_parent);
		p->setVisible(p->defaultVisibility());
	}
	
	m_list.append(new PanelWrapper(item, position));
}

QSize QPanelLayout::calculateSize(SizeType sizeType) const
{
	QSize totalSize;
	
	for ( int i = 0; i < m_list.size(); ++i )
	{
		QSize itemSize;
		PanelWrapper *wrapper = m_list.at(i);
		Position position = wrapper->position;
		
		if ( sizeType == MinimumSize )
			itemSize = wrapper->item->minimumSize();
		else // ( sizeType == SizeHint )
			itemSize = wrapper->item->sizeHint();
		
		if ( (position == North) || (position == South) ) // || (position == Center) )
			totalSize.rheight() += itemSize.height();
		
		if ( (position == West) || (position == East) ) // || (position == Center) )
			totalSize.rwidth() += itemSize.width();
		
	}
	
	return totalSize;
}

