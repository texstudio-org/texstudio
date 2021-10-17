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

#include "qeditorfactory.h"

#ifdef _QSAFE_SHARED_SETTINGS_

/*!
	\file qeditorfactory.cpp
	\brief Implementation of the QEditorFactory class.
*/

#include "qcodeedit.h"

#include "qformatscheme.h"
#include "qlanguagefactory.h"
#include "qcodecompletionengine.h"

#include "qfoldpanel.h"
#include "qlinemarkpanel.h"
#include "qlinenumberpanel.h"
#include "qlinechangepanel.h"
#include "qgotolinepanel.h"
#include "qstatuspanel.h"
#include "qsearchreplacepanel.h"

#include "qeditor.h"
#include "qlinemarksinfocenter.h"

#include "qsettingsserver.h"

/*!
	\ingroup editor
	@{
	
	\class QEditorFactory
	\brief Convenience class that manages editors.
	
	QCodeEdit widgets are created through QEditorFactory using a simple
	QString representing a panel id. Each panel id is associated to a
	serialized panel layout (\see QPanelLayout::serialized() ).
	
	\see QCodeEdit
	\see QLanguageFactory
	\see QFormatScheme
*/

/*!
	\brief Construct a working editor factory
*/
QEditorFactory::QEditorFactory(QSettingsServer *s)
 :
#ifdef _QMDI_
	qmdiClientFactory(s),
#else
	QObject(s),
#endif
	QSettingsClient(s, "editor")
{
	m_defaultScheme = new QFormatScheme(QCE::fetchDataFile("formats.qxf"), this);
	
	QDocument::setFormatFactory(m_defaultScheme);
	
	m_languageFactory = new QLanguageFactory(m_defaultScheme, this);
	
	foreach ( QString dp, QCE::dataPathes() )
	{
		m_languageFactory->addDefinitionPath(dp);
	}
	
	if ( value("version").toInt() != 3 )
	{
		setValue("version", 3);
		
		// setup default layouts...
		beginGroup("layouts");
		
		setValue("default", "default");
		
		beginGroup("availables");
		
		beginGroup("empty");
		setValue("struct", QString());
		setValue("name", "No panels");
		endGroup();
		
        #define panelIdOf(Class) \
            Class::Creator::instance() -> id()

		beginGroup("default");
		setValue("struct",
				QString::number(QCodeEdit::West)
				+ "{"
                + panelIdOf(QLineMarkPanel)
				+ ","
                + panelIdOf(QLineNumberPanel)
				+ ","
                + panelIdOf(QFoldPanel)
				+ ","
                + panelIdOf(QLineChangePanel)
				+ "}"
				
				+ QString::number(QCodeEdit::South)
				+ "{"
                + panelIdOf(QStatusPanel)
				+ ","
                + panelIdOf(QGotoLinePanel)
				+ ","
                + panelIdOf(QSearchReplacePanel)
				+ "}"
				);
		
		setValue("name", "Default panel layout");
		endGroup();
		
		beginGroup("simple");
		setValue("struct",
				QString::number(QCodeEdit::West)
				+ "{"
                + panelIdOf(QLineNumberPanel)
				+ ","
                + panelIdOf(QFoldPanel)
				+ "}"
				
				+ QString::number(QCodeEdit::South)
				+ "{"
                + panelIdOf(QStatusPanel)
				+ "}"
				);
        #undef panelIdOf
		
		setValue("name", "Trimmed-down panel layout");
		endGroup();
		
		endGroup();
		
		endGroup();
	}
	
}

/*!
	\brief dtor
*/
QEditorFactory::~QEditorFactory()
{
	
}

/*!
	\reimp
	\brief Creates an editor with default layout for the given file
	\param filename file to load in the editor
	\return a managed QEditor object
*/
qmdiClient* QEditorFactory::createClient(const QString& filename) const
{
	return editor(filename, defaultLayout())->editor();
}

/*!
	\brief Create a managed editor
	\param f file to load
	\param layout panel layout to use
*/
QCodeEdit* QEditorFactory::editor(const QString& f, const QString& layout) const
{
	QCodeEdit *e = new QCodeEdit(layout.isEmpty() ? defaultLayout() : layout);
	
	//m_config->hookEditor(def, e);
	
	connect(e->editor()	, SIGNAL( loaded(QEditor*, QString) ),
			this		, SLOT  ( loaded(QEditor*, QString) ) );
	
	connect(e->editor()	, SIGNAL( saved(QEditor*, QString) ),
			this		, SLOT  ( saved(QEditor*, QString) ) );
	
	// set syntax handlers
	m_languageFactory->setLanguage(e->editor(), f);
	
	if ( f.count() && QFile::exists(f) )
	{
		// load contents
		e->editor()->load(f);
		
		// set line marks back...
		QLineMarksInfoCenter::instance()->flush(f);
	} else {
		e->editor()->setTitle(tr("untitled"));
		e->editor()->setContentModified(true);
	}
	
	return e;
}

/*!
	\overload
	\param f file to load
	\param l language definition to use
	\param s format scheme to use
	\param en code completion engine to use
	\param layout panel layout to use
*/
QCodeEdit* QEditorFactory::editor(	const QString& f,
									QLanguageDefinition *l,
									QFormatScheme *s,
									QCodeCompletionEngine *en,
									const QString& layout) const
{
	QCodeEdit *e = new QCodeEdit(layout.isEmpty() ? defaultLayout() : layout);
	
	//m_config->hookEditor(def, e);
	
	connect(e->editor()	, SIGNAL( loaded(QEditor*, QString) ),
			this		, SLOT  ( loaded(QEditor*, QString) ) );
	
	connect(e->editor()	, SIGNAL( saved(QEditor*, QString) ),
			this		, SLOT  ( saved(QEditor*, QString) ) );
	
	// set syntax handlers
	//m_languageFactory->setLanguage(e->editor(), l, en);
	e->editor()->setLanguageDefinition(l);
	e->editor()->document()->setFormatScheme(s ? s : m_defaultScheme);
	e->editor()->setCompletionEngine(en ? en->clone() : 0);
	
	if ( f.count() && QFile::exists(f) )
	{
		// load contents
		e->editor()->load(f);
		
		// set line marks back...
		QLineMarksInfoCenter::instance()->flush(f);
	} else {
		e->editor()->setTitle(tr("untitled"));
		e->editor()->setContentModified(true);
	}
	
	return e;
}

/*!
	\brief Called whenever a managed editor save its content
	
	Update the language definition/code completion engine if needed
	and emits the fileSaved signal
*/
void QEditorFactory::saved(QEditor *e, const QString& f)
{
	if ( !e || !e->document() )
		return;
	
	m_languageFactory->setLanguage(e, f);
	emit fileSaved(f);
}

/*!
	\brief Placeholder
*/
void QEditorFactory::loaded(QEditor *e, const QString& f)
{
	Q_UNUSED(f)
	
	if ( !e || !e->document() )
		return;
	
}

/*!
	\return The default panel layout
*/
QString QEditorFactory::defaultLayout() const
{
	QSettingsClient c(*this);
	
	c.beginGroup("layouts");
	QString a = c.value("default").toString();
	
	if ( a.isEmpty() )
	{
		c.beginGroup("availables");
		
		a = childGroups().at(0);
		
		c.endGroup();
	}
	
	c.endGroup();
	
	return layout(a);
}

/*!
	\return The layout structure associated with a given layout alias
*/
QString QEditorFactory::layout(const QString& alias) const
{
	return value("layouts/availables/" + alias + "/struct").toString();
}

/*!
	\brief Register a layout
	\param a layout alias
	\param layout layout structure
*/
void QEditorFactory::registerLayout(const QString& a, const QString& layout)
{
	beginGroup("layouts");
	beginGroup("availables");
	beginGroup(a);
	setValue("struct", layout);
	setValue("name", a);
	endGroup();
	endGroup();
	endGroup();
}

/*!
	\return an accessor to the settings associated with a given layout alias
*/
QSettingsClient QEditorFactory::settings(const QString& alias)
{
	return QSettingsClient(*this, "layouts/availables/" + alias);
}

/*! @} */

#endif
