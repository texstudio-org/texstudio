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

#ifndef _QFORMAT_SCHEME_H_
#define _QFORMAT_SCHEME_H_

/*!
	\file qformatscheme.h
	\brief Definition of the QFormatScheme class.
	
	\see QFormatScheme
*/

/*!
	\defgroup language Language framework
*/

#include "qce-config.h"

#include <QVector>
#include <QObject>

struct QFormat;
class QString;
class QSettings;
class QStringList;
class QDomElement;

class QCE_EXPORT QFormatScheme : public QObject
{
	Q_OBJECT
	
	public:
		QFormatScheme(QObject *p = 0);
		QFormatScheme(const QString& f, QObject *p = 0);
		virtual ~QFormatScheme();
		
		void clear();
		
		virtual void load(const QString& filename);
		virtual void save(const QString& filename = QString()) const;
		
		virtual void load(const QDomElement& doc, bool ignoreNewIds = false);
		virtual void save(QDomElement& elem) const;
		
		virtual void load(QSettings& s, bool ignoreNewIds = false);
		virtual void save(QSettings& s) const;
		
		int formatCount() const;
		QStringList formats() const;
		
		virtual QString id(int ifid) const;
		virtual int id(const QString& sfid) const;
		
		virtual QFormat& formatRef(int ifid);
		virtual QFormat& formatRef(const QString& sfid);
		
		virtual QFormat format(int ifid) const;
		virtual QFormat format(const QString& sfid) const;
		
	public slots:
		virtual void setFormat(const QString& fid, const QFormat& fmt);
		
	protected:
		QString m_settings;
		
		QVector<QString> m_formatKeys;
		QVector<QFormat> m_formatValues;
};

#endif // !_QFORMAT_SCHEME_H_
