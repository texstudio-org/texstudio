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

#ifndef _QNFA_DEFINITION_H_
#define _QNFA_DEFINITION_H_

/*!
	\file qnfadefinition.h
	\brief Definition of the QNFADefinition class.
*/

#include "qlanguagefactory.h"
#include "qlanguagedefinition.h"

#include <QHash>
#include <QPointer>
#include <QStringList>

struct QNFA;

class QParenthesis;

class QFile;
class QDomDocument;

class QNFAAction
{
	public:
		enum
		{
			NoAction	= 0,
			
			FormatMask	= 0x00000fff,
			ParenMask	= 0x00fff000,
			
			Highlight	= 0x01000000,
			Indent		= 0x02000000,
			ParenOpen	= 0x04000000,
			ParenClose	= 0x08000000,
			MatchParen	= 0x10000000,
			Fold		= 0x20000000,

			Ambiguous	= 0x40000000,
			
			Content		= 0x80000000
		};
		
		inline static int format(int id)
		{ return id & FormatMask; }
		
		inline static int parenthesis(int id)
		{ return id & ParenMask; }
};

class QCE_EXPORT QNFADefinition : public QLanguageDefinition
{
	public:
		QNFADefinition();
		virtual ~QNFADefinition();
		
		virtual QString language() const;
		virtual QStringList extensions() const;
		
		virtual int tokenize(QDocument *d, int line, int count);
		
		virtual QString singleLineComment() const;
		
		virtual QString defaultLineMark() const;
		
		virtual void clearMatches(QDocument *d);
		virtual void match(QDocumentCursor& c);
		
		virtual QString indent(const QDocumentCursor& c);
		virtual bool unindent (const QDocumentCursor& c, const QString& ktxt);
		
		virtual void expand(QDocument *d, int line);
		virtual void collapse(QDocument *d, int line);
		virtual int blockFlags(QDocument *d, int line, int depth) const;
		
		static void load(QFile *f, QLanguageFactory::LangData *d, QFormatScheme *s);
		static void load(const QString& file, QLanguageFactory::LangData *d, QFormatScheme *s);
		static void load(const QDomDocument& doc, QLanguageFactory::LangData *d, QFormatScheme *s);
		
		static void addContext(const QString& id, QNFA *nfa);
		static void addEmbedRequest(const QString& lang, QNFA *dest);
		static void shareEmbedRequests(QNFA *src, QNFA *dest, int offset);
		
	private:
		bool m_indentFold;
		QString m_language,
				m_defaultMark,
				m_singleLineComment;
		
		QStringList m_extensions;
		
		QNFA *m_root;
		
		QHash<QPointer<QDocument>, int> m_matchGroups;
		
		static QHash<QString, int> m_paren;
		static QHash<QString, QNFA*> m_contexts;
		
		struct PMatch
		{
			PMatch() : type(Invalid)
			{
				line[0] = -1;
				line[1] = -1;
				
				column[0] = -1;
				column[1] = -1;
				
				length[0] = 0;
				length[1] = 0;
			}
			
			enum Type
			{
				Invalid,
				Match,
				Mismatch
			};
			
			char type;
			
			int line[2];
			int column[2];
			int length[2];
		};
		
		void matchOpen(QDocument *d, PMatch& m);
		void matchClose(QDocument *d, PMatch& m);
		
		int findBlockEnd(QDocument *d, int line, bool *open = 0);
		
		static void flushEmbedRequests(const QString& lang);
		
		struct EmbedRequest
		{
			inline EmbedRequest(QNFA *nfa, int idx) : index(idx), target(nfa) {}
			
			int index;
			QNFA *target;
		};
		
		typedef QList<EmbedRequest> EmbedRequestList;
		
		static QHash<QString, EmbedRequestList> m_pendingEmbeds;
};

#endif // !_QNFA_DEFINITION_H_
