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

#ifndef Header_QFormat_Scheme
#define Header_QFormat_Scheme

#include "mostQtHeaders.h"

/*!
	\file qformatscheme.h
	\brief Definition of the QFormatScheme class.
	
	\see QFormatScheme
*/

/*!
	\defgroup language Language framework
*/

#include "qce-config.h"

struct QFormat;
class QString;
class QSettings;
//class QStringList;
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
		virtual void save(QSettings& s,QFormatScheme *defaultFormats) const;
		
		int formatCount() const;
		QStringList formats() const;
		
		virtual QString id(int ifid) const;
		virtual int id(const QString& sfid) const;
		
		virtual bool exists(const QString& sfid) const;
		
		virtual QFormat& formatRef(int ifid);
		virtual QFormat& formatRef(const QString& sfid);
		
		virtual QFormat format(int ifid) const;
		virtual QFormat format(const QString& sfid) const;
		
		static void mergeFormats(int &oldFormat, int newFormat);
        void extractFormats(int mergedFormat, int* fmt, QFormat* formats, int &fontFormat) const;

		QString exportAsCSS(bool simplifyCSS);

		bool modified; //true if a format was changed by setFormat (qformatconfig)
	public slots:
		virtual void setFormat(const QString& fid, const QFormat& fmt);
		
	protected:
		QString m_settings;
		
		QVector<QString> m_formatKeys;
		QVector<QFormat> m_formatValues;
};

static const int FORMAT_SELECTION       = 0x80000000;
static const int FORMAT_SPACE           = 0x40000000;
static const int FORMAT_MASK_BASE       = 0x000000ff;
//static int FORMAT_MASK_SECOND     = 0x0000ff00;
//static int FORMAT_MASK_FIRST      = 0x00ff0000;
static const int FORMAT_SHIFT           = 8;
static const int FORMAT_MASK_FULL       = FORMAT_MASK_BASE | (FORMAT_MASK_BASE << FORMAT_SHIFT) | (FORMAT_MASK_BASE << (2*FORMAT_SHIFT));
static const int FORMAT_MAX_COUNT       = 3;
#endif // !_QFORMAT_SCHEME_H_
