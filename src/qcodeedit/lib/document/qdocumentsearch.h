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

#ifndef Header_QDocument_Search
#define Header_QDocument_Search

#include "qce-config.h"

/*!
	\file qdocumentsearch.h
	\brief Definition of the QDocumentSearch class
*/

#include <QString>
#include <QRegExp>
#include <QRegularExpression>
#include <QPointer>
#include <QAbstractScrollArea>
#include <QWidget>
#include <QCoreApplication>

#include "qdocumentcursor.h"
#include "qdocumentline.h"

class QEditor;

class QCE_EXPORT QDocumentSearch: public QObject
{
	Q_OBJECT
	
	public:
		enum Option
		{
			WholeWords		= 1,
			CaseSensitive	= 2,
			RegExp			= 4,
			Replace			= 8,
			Prompt			= 16,
			Silent			= 32,
			HighlightAll	= 64,
			EscapeSeq		= 128,
            filterByFormat  = 256,
            NonGreedy = 512,
            HighlightReplacements	= 64
		};
		
        Q_DECLARE_FLAGS(Options, Option)
		
		QDocumentSearch(QEditor *e, const QString& f, Options opt, const QString& r = QString());
		~QDocumentSearch();

		QString searchText() const;
		void setSearchText(const QString& f);
		
		Options options() const;
		bool hasOption(Option opt) const;
		void setOption(Option opt, bool on);
		void setOptions(Options options);

		void setFilteredFormats(QList<int> ids, bool inverted = false);
		QList<int> getFilteredFormats() const;

		QString replaceText() const;
		void setReplaceText(const QString& r);
		QString replaceTextExpanded() const;
		
		QDocumentCursor lastReplacedPosition() const;
		
		QDocumentCursor cursor() const;
		void setCursor(const QDocumentCursor& c);
		
		QDocumentCursor scope() const;
		void setScope(const QDocumentCursor& c);
		
        int next(bool backward, bool all = false, bool again=false,  bool allowWrapAround=true, const QDocumentCursor* overrideScope = nullptr);

		void highlightSelection(const QDocumentCursor& subHighlightScope=QDocumentCursor());

		QDocument* currentDocument();

	private:
		void connectToEditor();

		void replaceCursorText(bool backward);
		QList<QPair<QDocumentSelection, QDocumentSelection> > m_newReplacementOverlays;
		void updateReplacementOverlays();
		
		void searchMatches(const QDocumentCursor& subHighlightScope=QDocumentCursor(), bool clearAll=true, bool clearSubScope=true);
		void clearMatches();
		void clearReplacements();

		bool isAcceptedFormat(int formatIds) const;
		
		void recreateRegExp();
		
//		int m_index;
		Options m_option;
		QString m_string;
        QRegularExpression m_regularExpression;
        QRegularExpressionMatch m_match;


		QString m_replace;
		QPointer<QEditor> m_editor;
		QDocumentCursor m_cursor, m_scope, m_highlightedScope, m_searchedScope, m_lastReplacedPosition;
		QSet<QDocumentLineHandle*> m_highlights, m_highlightedReplacements;

		int m_replaced,m_replaceDeltaLength,m_replaceDeltaLines;

		QList<int> m_filteredIds;
		bool m_filteredIdsInverted;
	private slots:
		void documentContentChanged(int line, int n);
		void visibleLinesChanged();
		void lineDeleted(QDocumentLineHandle* line);
};
Q_DECLARE_OPERATORS_FOR_FLAGS(QDocumentSearch::Options)
#endif // !_QDOCUMENT_SEARCH_H_
