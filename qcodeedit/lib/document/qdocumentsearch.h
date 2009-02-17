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

#ifndef _QDOCUMENT_SEARCH_H_
#define _QDOCUMENT_SEARCH_H_

#include "qce-config.h"

/*!
	\file qdocumentsearch.h
	\brief Definition of the QDocumentSearch class
*/

#include <QString>
#include <QRegExp>
#include <QPointer>
#include <QCoreApplication>

#include "qdocumentcursor.h"

class QEditor;

class QCE_EXPORT QDocumentSearch
{
	Q_DECLARE_TR_FUNCTIONS(QDocumentSearch)
	
	public:
		enum Option
		{
			WholeWords		= 1,
			CaseSensitive	= 2,
			RegExp			= 4,
			Replace			= 8,
			Prompt			= 16,
			Silent			= 32,
			HighlightAll	= 64
		};
		
		Q_DECLARE_FLAGS(Options, Option);
		
		QDocumentSearch(QEditor *e, const QString& f, Options opt, const QString& r = QString());
		~QDocumentSearch();
		
		int indexedMatchCount() const;
		
		QString searchText() const;
		void setSearchText(const QString& f);
		
		bool hasOption(Option opt) const;
		void setOption(Option opt, bool on);
		Options options() const;
		
		QString replaceText() const;
		void setReplaceText(const QString& r);
		
		QDocumentCursor origin() const;
		void setOrigin(const QDocumentCursor& c);
		
		QDocumentCursor cursor() const;
		void setCursor(const QDocumentCursor& c);
		
		QDocumentCursor scope() const;
		void setScope(const QDocumentCursor& c);
		
		bool next(bool backward, bool all = false);
		
	private:
		bool end(bool backward) const;
		
		void clearMatches();
		
		int m_group;
		int m_index;
		Options m_option;
		QString m_string;
		QString m_replace;
		QPointer<QEditor> m_editor;
		QDocumentCursor m_cursor, m_scope, m_origin;
		QList<QDocumentCursor> m_highlight;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QDocumentSearch::Options)

#endif // !_QDOCUMENT_SEARCH_H_
