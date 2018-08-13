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

#ifndef _QFORMAT_CONFIG_H_
#define _QFORMAT_CONFIG_H_

#include "mostQtHeaders.h"

#include "qce-config.h"

/*!
	\file qformatconfig.h
	\brief Definition of the QFormatConfig widget
	
	\see QFormatConfig
*/

#include "ui_formatconfig.h"

class QFormatScheme;

class QCE_EXPORT QFormatConfig : public QWidget, private Ui::FormatConfig
{
	Q_OBJECT
	
	public:
		QFormatConfig(QWidget *w = 0, bool adaptStyle = true);
		
		bool isAutonomous() const;
		
		bool hasUnsavedChanges() const;
		
		QList<QFormatScheme*> schemes() const;
		
		QList<QString>& addCategory(const QString& name);

	public slots:
		void retranslate();
		
		void apply();
		void cancel();
		void restore();
		
		void setAutonomous(bool y);
		
		void addScheme(const QString& name, QFormatScheme *scheme);
		void removeScheme(QFormatScheme *scheme);
		
		void setCurrentScheme(QFormatScheme *scheme);
		
		void setBasePointSize(int basePointSize);
	protected:
		virtual void hideEvent(QHideEvent *e);
		virtual void showEvent(QShowEvent *e);
		
	private slots:
		void on_m_selector_currentIndexChanged(int idx);
		
	private:
		QList<int> modifiedFormats() const;
		QList<QList<QString> > m_categories;
		
		bool m_autonomous;
		QFormatScheme *m_currentScheme;
		QList<QFormatScheme*> m_schemes;

		int basePointSize;
};

#endif // _QFORMAT_CONFIG_H_
