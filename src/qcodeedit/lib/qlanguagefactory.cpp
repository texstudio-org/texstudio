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

#include "qlanguagefactory.h"

/*!
	\file qlanguagefactory.cpp
	\brief Implementation of QLanguageFactory

	\see QLanguageFactory
*/

/*!
	\ingroup language
	@{

	\class QLanguageFactory
	\brief A class managing language definitions.

	It stores language definitions, added programmatically or found in XML files,
	in specified locations and only if generic components are built-in. From
	these definitions, QLanguageFactory generates matchers, indenters and
	highlighters for a text editor, according to a file name.

	\see QLanguageDefinition
*/

#include "qeditor.h"
#include "qformatscheme.h"

#include "qlanguagedefinition.h"
#include "qcodecompletionengine.h"

#ifdef QNFA_BUILD
#include "qnfadefinition.h"
#endif

/*!
	\brief Empty constructor
*/
QLanguageFactory::QLanguageFactory(QFormatScheme *fmt, QObject *p)
 : QObject(p), m_defaultFormatScheme(fmt)
{

}

/*!
	\brief Empty destructor
*/
QLanguageFactory::~QLanguageFactory()
{
	foreach ( const LangData& d, m_data.values() )
		deleteLangData(d);
}

/*!
	\return a list of languages supported by this factory
*/
QStringList QLanguageFactory::languages() const
{
	return m_languages;
}

/*!
	\return a list of file filters supported by this factory

	\note This list is NEVER empty and the last item is always "All files (*)"
*/
QStringList QLanguageFactory::fileFilters() const
{
	QStringList l;

	foreach ( QString lng, m_languages )
		l << tr("%1 files (*.%2)").arg(lng).arg(m_data[lng].extensions.join(" *."));

	l << tr("All files (*)");

	return l;
}

/*!
	\param e target editor
	\param file filename displayed by the editor

	The \a file parameter may actuall be either a filename, an extension or the name of the language,
	checked in that order.

	If it is a filename, complete extension as higher priority than simple extension
	(see QFileInfo suffix() and completeSuffix()).

	Matches are first done case-sensitively.

	If no matching language definition is found for all three possible interpretations of the \a file
	parameter, the same search is done case-insensitively.

	If no matching language is found the previous language definition/completion engine of the editor
	are removed, leaving it blank, and the format scheme of the document is set to the defaultFormatScheme()
*/
bool QLanguageFactory::setLanguage(QEditor *e, const QString& file)
{
	QString lang;
	QFileInfo inf(file);
	const QString ext = inf.suffix(),
				cext = inf.completeSuffix();

	//qDebug("suff:%s; compSuff:%s", qPrintable(ext), qPrintable(cext));

	if ( file.count() )
	{
		QList<Qt::CaseSensitivity> lcs;
		lcs << Qt::CaseSensitive << Qt::CaseInsensitive;

		foreach ( Qt::CaseSensitivity cs, lcs )
		{
			int n = 0, idx = -1;
			QStringList ext_langs, cext_langs, fcext_langs;

			foreach ( QString lang, m_languages )
			{
				const QStringList& exts = m_data[lang].extensions;

				//qDebug("%s in (%s) ?", qPrintable(ext), qPrintable(exts.join(" ")));

				foreach ( QString x, exts )
				{
					if ( !x.compare(ext, cs) )
						ext_langs << lang;

					if ( !x.compare(cext, cs) )
						cext_langs << lang;

					if ( !x.compare(file, cs) )
						fcext_langs << lang;
				}

				if ( !lang.compare(file, cs) )
					idx = n;

				++n;
			}

			if ( cext_langs.count() )
			{
				// TODO : use MIME types to resolve ambiguity
				lang = cext_langs.first();
			} else if ( ext_langs.count() ) {
				// TODO : use MIME types to resolve ambiguity
				lang = ext_langs.first();
			} else if ( fcext_langs.count() ) {
				// TODO : use MIME types to resolve ambiguity
				lang = fcext_langs.first();
			} else if ( idx != -1 ) {
				lang = m_languages.at(idx);
			}

			if ( lang.count() )
				break;
		}
	}
	
	return setLanguageFromName(e, lang);
}

	
bool QLanguageFactory::setLanguageFromName(QEditor *e, const QString& lang){
	QLanguageDefinition *oldLang = e->languageDefinition();

	if ( lang.isEmpty() && !m_data.contains(lang))
	{
		//qDebug("no lang match for %s", qPrintable(file));
        e->setLanguageDefinition(nullptr);
        e->setCompletionEngine(nullptr);
		e->document()->setFormatScheme(m_defaultFormatScheme);

		if ( oldLang ) {
			e->highlight();
			return true;
		}

	} else {
		//qDebug("lang match for %s : %s", qPrintable(file), qPrintable(lang));
		const LangData& data = m_data[lang];

		e->setLanguageDefinition(data.d);
        e->setCompletionEngine(data.e ? data.e->clone() : nullptr);
		e->document()->setFormatScheme(data.s ? data.s : m_defaultFormatScheme);

		if ( oldLang != data.d ) {
			e->highlight();
			return true;
		}
	}
	return false;
}

/*!
	\brief Adds a language to the factory

	\param d language data

	\note The language data will overwrite any existing one for the same language
*/
void QLanguageFactory::addLanguage(const QLanguageFactory::LangData& d)
{
//TODO: disable, it causes a memory leak, enabled it crashes when an embed definition is used
//	if (m_data.contains(d.lang))
//		deleteLangData(m_data.value(d.lang));

	m_data.insert(d.lang, d);

	if ( !d.e )
	{
		foreach ( QCodeCompletionEngine *e, m_unusedEngines )
		{
			if ( e->language() == d.lang )
			{
				m_data[d.lang].e = e;
				break;
			}
		}
	}

	if ( !m_languages.contains(d.lang) )
		m_languages << d.lang;
}

/*!
	\brief Lookup language data for a matching language

	The primary purpose of this function is to make it easy to create configuration dialogs (mainly for
	format schemes). Beware though : some language may use the default format scheme. It is recommended
	to check for that before modifying a format scheme or users might be surprised...

	\warning This function will lead to crashes if you pass it a language name not contained in languages().
*/
const QLanguageFactory::LangData& QLanguageFactory::languageData(const QString& lang)
{
	return m_data[lang];
}

/*!
	\brief Registers a new completion engine

	\note This engine will NOT be used if there are no language definition for the
	language it supports...
*/
void QLanguageFactory::addLanguageDefinition(QLanguageDefinition *l)
{
	Q_UNUSED(l)
	
	qWarning("New design does not allow this sorry...");
}

/*!
	\brief Registers a new completion engine

	\note This engine will NOT be used if there are no language definition for the
	language it supports...
*/
void QLanguageFactory::addCompletionEngine(QCodeCompletionEngine *e)
{
	foreach ( QString l, m_languages )
	{
		if ( l == e->language() )
		{
			m_data[l].e = e;
			return;
		}
	}

	m_unusedEngines << e;
}

/*!
	\brief Fetches syntax definitions from files in \a path
*/
void QLanguageFactory::addDefinitionPath(const QString& path)
{
	QDir d(path);

	foreach ( QString f, d.entryList(QDir::Files | QDir::Readable) )
	{
		#ifdef QNFA_BUILD
		if ( f.endsWith(".qnfa") )
		{
			//qDebug("loading file %s", qPrintable(f));
			QFileInfo info(d.filePath(f));
			QString specificFormatScheme = QDir(info.path()).filePath(info.baseName() + ".qxf");

			QFormatScheme *scheme = m_defaultFormatScheme;

			if ( QFile::exists(specificFormatScheme) )
			{
				scheme = new QFormatScheme(specificFormatScheme);
			}

			LangData data;
			QNFADefinition::load(d.filePath(f), &data, scheme);

			//qDebug() << "load: "<<data.d;

			//qDebug("%s : (%s | %s)", qPrintable(data.lang), qPrintable(data.mime), qPrintable(data.extensions.join(", ")));
			addLanguage(data);
			//addLanguageDefinition(new QNFADefinition(d.filePath(f), this));
		}
		#endif
	}
}

void QLanguageFactory::deleteLangData(const LangData& d){
{
	if ( d.s != m_defaultFormatScheme && d.s)
		delete d.s;

	//qDebug() << "delete: "<<d.d;

    delete d.d;
}
}

/*! @} */
