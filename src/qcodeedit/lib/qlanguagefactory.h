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

#ifndef Header_QLanguage_Factory
#define Header_QLanguage_Factory

#include "mostQtHeaders.h"

/*!
	\file qlanguagefactory.h
	\brief Definition of the QLanguageFactory class.
	
	\see QLanguageFactory
*/

/*!
	\defgroup language Language framework
*/

#include "qce-config.h"

class QEditor;
class QFormatScheme;
class QLanguageDefinition;
class QCodeCompletionEngine;

class QCE_EXPORT QLanguageFactory : public QObject
{
	Q_OBJECT
	
	public:
		struct LangData
		{
			QString lang, mime;
			QStringList extensions;
			
			QFormatScheme *s;
			
			QLanguageDefinition *d;
			QCodeCompletionEngine *e;
		};
		
		QLanguageFactory(QFormatScheme *fmt, QObject *p = 0);
		virtual ~QLanguageFactory();
		
		QStringList languages() const;
		QStringList fileFilters() const;
		
		const LangData& languageData(const QString& lang);
		
		void addDefinitionPath(const QString& path);
		
		inline QFormatScheme* defaultFormatScheme() const { return m_defaultFormatScheme; }
		
	public slots:
		void addLanguage(const LangData& d);
		void addLanguageDefinition(QLanguageDefinition *l);
		void addCompletionEngine(QCodeCompletionEngine *e);
		
		virtual bool setLanguage(QEditor *e, const QString& f);
		virtual bool setLanguageFromName(QEditor *e, const QString& lang);
		
	private:
		QStringList m_languages;
		QHash<QString, LangData> m_data;
		QList<QCodeCompletionEngine*> m_unusedEngines;
		
		QFormatScheme *m_defaultFormatScheme;
		void deleteLangData(const LangData& d);
};

#endif // _QLANGUAGE_FACTORY_H_
