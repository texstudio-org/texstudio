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

#ifndef Header_QNFA_Definitions
#define Header_QNFA_Definitions

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

struct QParenthesis;

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
    virtual void setSingleLineComment(const QString text);

	virtual QString defaultLineMark() const;

	virtual int parenthesisWeight(int id) const;
	virtual const QStringList& openingParenthesis() const;
	virtual const QStringList closingParentheses() const;
	//virtual const QHash<int, QString> & closingParenthesis() const;
	virtual QString getClosingParenthesis(const QString& opening) const;
	virtual bool possibleEndingOfOpeningParenthesis(const QString& text) const;

	virtual void clearMatches(QDocument *d);
	virtual void match(QDocumentCursor& c);

	virtual QList<QList<QDocumentCursor> > getMatches(const QDocumentCursor& c) const;
	virtual QDocumentCursor getNextMismatch(const QDocumentCursor& scope) const;
	
	virtual QString indent(const QDocumentCursor& c, int* indentCount);
	virtual bool unindent (const QDocumentCursor& c, const QString& ktxt);

	virtual void expand(QDocument *d, int line);
	virtual void collapse(QDocument *d, int line);
	void fold(QDocument *d, int line, bool expand);
	virtual bool correctFolding(QDocument *d);

	static void load(QFile *f, QLanguageFactory::LangData *d, QFormatScheme *s);
	static void load(const QString& file, QLanguageFactory::LangData *d, QFormatScheme *s);
	static void load(const QDomDocument& doc, QLanguageFactory::LangData *d, QFormatScheme *s);

	static void addContext(const QString& id, QNFA *nfa);
	static void addEmbedRequest(const QString& lang, QNFA *dest);
	static void shareEmbedRequests(QNFA *src, QNFA *dest, int offset);

	static QString getContextName(QNFA* cxt){
		return m_contexts.key(cxt);
	}

private:
	bool m_indentFold;
	QString m_language,
	m_defaultMark,
	m_singleLineComment;

	QStringList m_extensions;

	QNFA *m_root;

	QHash<QPointer<QDocument>, int> m_matchGroups;

	static QHash<QString, int> m_paren;
	static QHash<int, int> m_parenWeight;
	static QHash<QString, QNFA*> m_contexts;
	static QHash<QString, int> m_openingParenthesis;
	static QHash<int, QString> m_closingParenthesis;
	QStringList m_openingParenthesisList;
	bool m_openingParenthesisEnd[256];

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

			weight[0] = weight[1] = 0;
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
		int weight[2];
	};
	virtual void getPMatches(const QDocumentCursor& c, QList<PMatch>& matches) const;

	void matchOpen(QDocument *d, PMatch& m) const;
	void matchClose(QDocument *d, PMatch& m) const;

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
