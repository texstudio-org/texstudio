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

#ifndef Header_QPanel_Layout
#define Header_QPanel_Layout

#include "mostQtHeaders.h"

#include "qce-config.h"

/*!
	\file qpanellayout.h
	\brief Definition of the QPanelLayout class
*/

class QPanel;
class QEditor;

class QCE_EXPORT QPanelLayout : public QLayout
{
	Q_OBJECT
	
	public:
		enum Position
		{
			West,
			North,
			South,
			East
		};
		
		QPanelLayout(QEditor *p);
		QPanelLayout(const QString& layout, QEditor *p);
		virtual ~QPanelLayout();
		
		virtual int count() const;
		virtual bool hasHeightForWidth() const;
		virtual Qt::Orientations expandingDirections() const;
		
		virtual QSize sizeHint() const;
		virtual QSize minimumSize() const;
		
		virtual QLayoutItem *itemAt(int idx) const;
		virtual QLayoutItem *takeAt(int idx);
		
		QString serialized() const;
		void addSerialized(const QString& layout);
		
		QList<QPanel*> panels() const;
		
	public slots:
		virtual void addItem(QLayoutItem *item);
		virtual void setGeometry(const QRect &rect);
		
		void add(QLayoutItem *item, Position position);
		void addWidget(QWidget *widget, Position position);
		
	private:
		QPointer<QEditor> m_parent;
		
		struct PanelWrapper
		{
			PanelWrapper(QLayoutItem *i, Position p)
			{
				item = i;
				position = p;
			}
			
			QLayoutItem *item;
			Position position;
		};
		
		enum SizeType { MinimumSize, SizeHint };
		QSize calculateSize(SizeType sizeType) const;
		
		QList<PanelWrapper*> m_list;
};

#endif // _QPANEL_LAYOUT_H_

