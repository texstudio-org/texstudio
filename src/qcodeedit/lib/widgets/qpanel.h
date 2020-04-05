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

#ifndef _QPANEL_H_
#define _QPANEL_H_

#include "mostQtHeaders.h"

/*!
	\file qpanel.h
	\brief Definition of the QPanel class
	
	\see QPanel
	
	\defgroup widgets
*/

#include "qce-config.h"

class QPainter;
class QPaintEvent;

class QEditor;
class QPanelCreator;

class QCE_EXPORT QPanel : public QWidget
{
	Q_OBJECT
	
	public:
        QPanel(QWidget *p = nullptr);
		virtual ~QPanel();
		
		virtual QString id() const = 0;
		virtual QString type() const = 0;
		
		QEditor* editor();
		void attach(QEditor *e);
		
		virtual bool shallShow() const;
		
		bool defaultVisibility() const;
		void setDefaultVisibility(bool on);
		
        static QPanel* panel(const QString& id, QWidget *p = nullptr);
		static void registerCreator(QPanelCreator *c);
		
	protected:
		virtual bool forward(QMouseEvent *e);
		
		virtual void editorChange(QEditor *e);
		
		virtual void mouseMoveEvent(QMouseEvent *e);
		virtual void mousePressEvent(QMouseEvent *e);
		virtual void mouseReleaseEvent(QMouseEvent *e);
		
		virtual void showEvent(QShowEvent *e);
		virtual void hideEvent(QHideEvent *e);
		virtual void paintEvent(QPaintEvent *e);
		virtual bool paint(QPainter *p, QEditor *e);
		
	private:
		QPointer<QEditor> m_editor;
		bool m_defaultVisibility, m_shownOnce;
		static QHash<QString, QPanelCreator*>& creators();
};

class QPanelCreator
{
	public:
		virtual ~QPanelCreator() {}
		virtual QString id() const = 0;
		virtual QPanel* panel(QWidget *p) = 0;
};

#define Q_PANEL(T, SID)									\
	public:												\
	class Creator : public QPanelCreator				\
	{ 													\
		public: 										\
			virtual QString id() const					\
			{											\
				return SID;								\
			}											\
														\
			virtual QPanel* panel(QWidget *p)			\
			{											\
				return new T(p);						\
			}											\
														\
			static QPanelCreator* instance()			\
			{											\
				static Creator global;					\
				return &global;							\
			}											\
														\
			Creator() {}								\
			virtual ~Creator() {}						\
	};													\
														\
	QString id() const { return SID; }					\
														\
	static void _register()								\
	{													\
		QPanel::registerCreator(Creator::instance());	\
	}													\
	

#define Q_PANEL_ID(T)									\
	T::Creator::instance()->id()						\
	

#define Q_CREATE_PANEL(T)								\
	QPanel::panel(Q_PANEL_ID(T))						\
	

#endif // _QPANEL_H_
