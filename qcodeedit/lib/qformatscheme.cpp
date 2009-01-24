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

#include "qformatscheme.h"

/*!
	\file qformatscheme.cpp
	\brief Implementation of QFormatScheme
	
	\see QFormatScheme
*/

/*!
	\ingroup language
	@{
	
	\class QFormatScheme
	\brief A storage/configuration class for shared highlighting formats
	
	It stores text formats used by highlighters interfaces and provides
	a default serializing format in QXF format (XML-based).
	
	\see QLanguageFactory
	\see QHighlighter
*/

#include "qformat.h"

#include <QFile>
#include <QDomText>
#include <QStringList>
#include <QDomElement>
#include <QDomDocument>

#define QFORMAT_VERSION "1.0"

/*!
	\brief Constructor
*/
QFormatScheme::QFormatScheme(QObject *p)
 : QObject(p)
{
	setFormat("normal", QFormat());
}

/*!
	\brief Constructor
	\param f Filename of a format settings file to load
*/
QFormatScheme::QFormatScheme(const QString& f, QObject *p)
 : QObject(p)
{
	load(f);
}

/*!
	\brief Destructor
*/
QFormatScheme::~QFormatScheme()
{
}

/*!
	\brief Load format settings from a file
	\param f file to load data from

	The default implementation loads data in QXF format (XML-based)

	\note Previous content is discarded
*/
void QFormatScheme::load(const QString& f)
{
	m_settings = f;
	m_formatKeys.clear();
	m_formatValues.clear();

	QFile settings(f);
	
	setFormat("normal", QFormat());
	
	if ( settings.open(QFile::ReadOnly | QFile::Text) )
	{
		QDomDocument doc;
		doc.setContent(&settings);
		
		if ( doc.documentElement().attribute("version") < QFORMAT_VERSION )
		{
			qWarning("Format encoding version mismatch : [found]%s != [expected]%s",
					qPrintable(doc.documentElement().attribute("version")),
					QFORMAT_VERSION);
			
			return;
		}
		
		QDomElement e, c;
		QDomNodeList l, f = doc.documentElement().elementsByTagName("format");
		
		for ( int i = 0; i < f.count(); i++ )
		{
			e = f.at(i).toElement();
			l = e.childNodes();
			
			QFormat fmt;
			
			for ( int i = 0; i < l.count(); i++ )
			{
				c = l.at(i).toElement();
				
				if ( c.isNull() )
					continue;
				
				QString field = c.tagName(),
						value = c.firstChild().toText().data();
				
				if ( field == "bold" )
					fmt.weight = ((value == "true") || (value.toUInt() == 1))
										? QFont::Bold : QFont::Normal;
				else if ( field == "italic" )
					fmt.italic = ((value == "true") || (value.toUInt() == 1));
				else if ( field == "overline" )
					fmt.overline = ((value == "true") || (value.toUInt() == 1));
				else if ( field == "underline" )
					fmt.underline = ((value == "true") || (value.toUInt() == 1));
				else if ( field == "strikeout" )
					fmt.strikeout = ((value == "true") || (value.toUInt() == 1));
				else if ( field == "waveUnderline" )
					fmt.waveUnderline = ((value == "true") || (value.toUInt() == 1));
				else if ( field == "color" || field == "foreground" )
					fmt.foreground = QColor(value);
				else if ( field == "background" )
					fmt.background = QColor(value);
				else if ( field == "linescolor" )
					fmt.linescolor = QColor(value);
				
			}
			
			setFormat(e.attribute("id"), fmt);
		}
	}
}

/*!
	\brief Save the format settings to a file
	\param f target file (if none specified, last value passed to load is used)

	The default implementation saves data in QXF format (XML-based)
*/
void QFormatScheme::save(const QString& f)
{
	QFile settings(f.count() ? f : m_settings);
	
	if ( settings.open(QFile::WriteOnly | QFile::Text) )
	{
		QDomDocument doc("QXF");
		
		QDomElement root = doc.createElement("QXF");
		root.setAttribute("version", QFORMAT_VERSION);
		
		for ( int i = 1; i < m_formatKeys.count(); i++ )
		{
			QDomText t;
			QDomElement f, c = doc.createElement("format");
			
			c.setAttribute("id", m_formatKeys.at(i));
			
			const QFormat& fmt = m_formatValues.at(i);
			
			f = doc.createElement("bold");
			t = doc.createTextNode((fmt.weight == QFont::Bold) ? "true" : "false");
			f.appendChild(t);
			c.appendChild(f);
			
			f = doc.createElement("italic");
			t = doc.createTextNode(fmt.italic ? "true" : "false");
			f.appendChild(t);
			c.appendChild(f);
			
			f = doc.createElement("overline");
			t = doc.createTextNode(fmt.overline ? "true" : "false");
			f.appendChild(t);
			c.appendChild(f);
			
			f = doc.createElement("underline");
			t = doc.createTextNode(fmt.underline ? "true" : "false");
			f.appendChild(t);
			c.appendChild(f);
			
			f = doc.createElement("strikeout");
			t = doc.createTextNode(fmt.strikeout ? "true" : "false");
			f.appendChild(t);
			c.appendChild(f);
			
			f = doc.createElement("waveUnderline");
			t = doc.createTextNode(fmt.waveUnderline ? "true" : "false");
			f.appendChild(t);
			c.appendChild(f);
			
			if ( fmt.foreground.isValid() )
			{
				f = doc.createElement("foreground");
				t = doc.createTextNode(fmt.foreground.name());
				f.appendChild(t);
				c.appendChild(f);
			}
			
			if ( fmt.background.isValid() )
			{
				f = doc.createElement("background");
				t = doc.createTextNode(fmt.background.name());
				f.appendChild(t);
				c.appendChild(f);
			}
			
			if ( fmt.linescolor.isValid() )
			{
				f = doc.createElement("linescolor");
				t = doc.createTextNode(fmt.linescolor.name());
				f.appendChild(t);
				c.appendChild(f);
			}
			
			root.appendChild(c);
		}
		
		doc.appendChild(root);
		
		settings.write(doc.toByteArray(4));
	}
}

/*!
	\return The number of available formats
*/
int QFormatScheme::formatCount() const
{
	return m_formatValues.count();
}

/*!
	\return A list of available format keys
*/
QStringList QFormatScheme::formats() const
{
	return m_formatKeys.toList();
}

/*!
	\return The format key associated to integer format id \a ifid
*/
QString QFormatScheme::id(int ifid) const
{
	return m_formatKeys.at(ifid);
}

/*!
	\return The integer format id associated to format key \a fid
*/
int QFormatScheme::id(const QString& sfid) const
{
	int idx = m_formatKeys.indexOf(sfid);
	
	return (idx == -1) ? 0 : idx;
}

/*!
	\return The text format associated with format key \a fid
	
	\warning Use at your own risks : if there are no format associated
	with the requested id this function will crash
*/
QFormat& QFormatScheme::formatRef(int ifid)
{
	return m_formatValues[ifid];
}

/*!
	\return The a reference to the text format associated with format key \a fid
	
	\warning Use at your own risks : if there are no format associated
	with the requested id this function will crash.
*/
QFormat& QFormatScheme::formatRef(const QString& sfid)
{
	return m_formatValues[id(sfid)];
}

/*!
	\return The text format associated with format key \a fid
*/
QFormat QFormatScheme::format(int ifid) const
{
	//qDebug("Querying format id %i within ]-1, %i[", ifid, m_formatValues.count());
	
	return (ifid < m_formatValues.count()) ? m_formatValues.at(ifid) : QFormat();
}

/*!
	\return The text format associated with format key \a fid
*/
QFormat QFormatScheme::format(const QString& sfid) const
{
	return format(id(sfid));
}

/*!
	\brief Set text format for key
	\param fid Format key
	\param fmt Format value
*/
void QFormatScheme::setFormat(const QString& fid, const QFormat& fmt)
{
	const int idx = m_formatKeys.indexOf(fid);
	
	if ( idx != -1 )
	{
		m_formatValues[idx] = fmt;
	} else {
		
		//qDebug("adding format %s [%i]", qPrintable(fid), m_formatKeys.count());
		
		m_formatKeys << fid;
		m_formatValues << fmt;
	}
}

/*! @} */

