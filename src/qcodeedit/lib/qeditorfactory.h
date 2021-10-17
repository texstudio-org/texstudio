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

#ifndef Header_QEditor_Factory
#define Header_QEditor_Factory

#include "mostQtHeaders.h"

#include "qce-config.h"

/*!
	\file qeditorfactory.h
	\brief Definition of the QEditorFactory class
*/

#ifdef _QSAFE_SHARED_SETTINGS_

#ifndef _QMDI_
	#define Q_EDITOR_FACTORY_BASE QObject
	#define Q_EDITOR_FACTORY_EMIT(client)
#else
	#include "qmdiclientfactory.h"
	
	#define Q_EDITOR_FACTORY_BASE qmdiClientFactory
	#define Q_EDITOR_FACTORY_EMIT(client) emit clientCreated(client);
#endif

#include "qsettingsclient.h"

class QEditor;
class QCodeEdit;
class QFormatScheme;
class QLanguageFactory;
class QCodeCompletionEngine;
class QLanguageDefinition;
class QEditorConfiguration;

class QCE_EXPORT QEditorFactory : public Q_EDITOR_FACTORY_BASE, public QSettingsClient
{
	Q_OBJECT
	
	public:
		QEditorFactory(QSettingsServer *s);
		virtual ~QEditorFactory();
		
		inline QFormatScheme* defaultFormatScheme() const
		{ return m_defaultScheme; }
		
		inline QLanguageFactory* languageFactory() const
		{ return m_languageFactory; }
		
		virtual qmdiClient* createClient(const QString& filename) const;
		
		QCodeEdit* editor(	const QString& file,
							const QString& layout = QString()) const;
		
		QCodeEdit* editor(	const QString& file,
							QLanguageDefinition *l,
							QFormatScheme *s = 0,
							QCodeCompletionEngine *e = 0,
							const QString& layout = QString()) const;
		
		QString defaultLayout() const;
		QString layout(const QString& alias) const;
		void registerLayout(const QString& alias, const QString& layout);
		
		QSettingsClient settings(const QString& alias);
		
	signals:
		void fileSaved(const QString& f);
		
	private slots:
		void saved(QEditor *e, const QString& f);
		void loaded(QEditor *e, const QString& f);
		
	private:
		QEditorConfiguration *m_config;
		
		QFormatScheme *m_defaultScheme;
		QLanguageFactory *m_languageFactory;
};

#endif // _QSAFE_SHARED_SETTINGS_

#endif // ! _QEDITOR_FACTORY_H_
