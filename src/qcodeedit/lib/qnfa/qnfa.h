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

#ifndef Header_QNFA
#define Header_QNFA

/*!
	\file qnfa.h
	\brief Definition of the core QNFA syntax engine
*/

#include <QChar>
#include <QList>
#include <QHash>
#include <QStack>
#include <QString>

#include "light_vector.h"

struct QNFA;

typedef light_vector<quint16> QNFASet;

class QNFABranch : public light_vector<QNFA*>
{
	public:
		~QNFABranch();
};

enum NFAType
{
	Char			= 0,

	Match			= 1,

	CxtBeg			= 2,
	CxtEnd			= 4,
	CxtEsc			= 8,

	ContextBegin	= Match | CxtBeg,
	ContextEnd		= Match | CxtEnd,
	EscapeSeq		= Match | CxtEsc,

	Escaped			= 16,
	Exclusive		= 32,
	StayOnLine		= 64,

	Reserved		= 128
};

enum NFAAssertion
{
	NoAssertion		= 0,

	One				= 0,		// default standard
	ZeroOrOne		= 1,		// ?
	ZeroOrMore		= 2,		// *
	OneOrMore		= 4,		// +

	WordStart		= 8,
	WordEnd			= 16,

	Word			= 32,
	NonWord			= 64,

	Digit			= 128,
	NonDigit		= 256,

	Space			= 512,
	NonSpace		= 1024,

	CaseSensitive	= 2048,

	LineStart = 4096
};

struct QCharTreeNode;

typedef QHash<quint16, QCharTreeNode> QCharTreeLevel;

struct QCharTreeNode
{
	inline QCharTreeNode(quint16 v = 0) { value.unicode = v; }
	inline QCharTreeNode(const QCharTreeNode& o) { value = o.value; next = o.next; }
	QCharTreeNode& operator= (const QCharTreeNode& o) = default; // Silence -Wdeprecated-copy

	union
	{
		int action;
		quint16 unicode;
	} value;

	QCharTreeLevel next;
};

Q_DECLARE_TYPEINFO(QCharTreeNode, Q_MOVABLE_TYPE);

typedef QCharTreeLevel QCharTree;

struct QNFA
{
	QNFA();
	~QNFA();

	QNFASet c;
	QCharTree tree;

	union
	{
		QNFA *next;
		QNFABranch *branch;
	} out;

	quint8 type;
	quint16 assertion;

	int actionid;

	static quint32 _count;
};

struct QNFAMatchContext
{
	inline QNFAMatchContext(QNFA *root = 0) : context(root) {}

	inline QNFAMatchContext& operator = (QNFAMatchContext *c)
	{
		if ( c )
		{
			context = c->context;
			parents = c->parents;
			meaningless = c->meaningless;
		} else {
			reset();
		}

		return *this;
	}

	inline QNFAMatchContext& operator = (const QNFAMatchContext& c)
	{
		context = c.context;
		parents = c.parents;
		meaningless = c.meaningless;

		return *this;
	}

	inline void reset()
	{
		context = 0;

		while ( parents.count() )
			context = parents.pop();
	}

	QNFA *context;
	QNFASet meaningless;
	QStack<QNFA*> parents;
};

class QNFAMatchHandler
{
	public:
		virtual ~QNFAMatchHandler() {}

		virtual void matched(int pos, int len, int action) = 0;
};

class QNFAMatchNotifier
{
	private:
		struct Command
		{
			inline Command(int p, int len, int act)
			 : pos(p), length(len), action(act) {}

			int pos;
			int length;
			int action;
		};

		typedef QList<Command> CommandList;

	public:
		inline QNFAMatchNotifier(const QNFAMatchNotifier&) = default;	// Avoid GCC9 -Wdeprecated-copy warning

		inline QNFAMatchNotifier(QNFAMatchHandler *h)
		 : handler(h) {}

		inline QNFAMatchNotifier& operator = (const QNFAMatchNotifier& n)
		{
			handler = n.handler;

			return *this;
		}

		inline void operator () (int pos, int len, int action)
		{
			if ( handler && (m_buffers.isEmpty() || m_pending.count()) )
				handler->matched(pos, len, action);
			else
				m_buffers.top() << Command(pos, len, action);
		}

		inline int bufferLevel() const
		{
			return m_buffers.count();
		}

		inline void startBuffering()
		{
			m_buffers.push(CommandList());
		}

		inline void stopBuffering()
		{
			m_pending = m_buffers.pop();
		}

		inline void flush()
		{
			foreach ( Command c, m_pending )
				handler->matched(c.pos, c.length, c.action);

			m_pending.clear();
		}

		inline void clear()
		{
			m_pending.clear();
			m_buffers.clear();
		}

	private:
		QNFAMatchHandler *handler;

		CommandList m_pending;
		QStack<CommandList> m_buffers;
};

void match(			QNFAMatchContext *lexer,
					const QChar *d,
					int length,
					QNFAMatchNotifier notify);

inline void match(	QNFAMatchContext *lexer,
					const QString& s,
					QNFAMatchNotifier notify)
{ match(lexer, s.constData(), s.length(), notify); }

QNFA* lexer();

void squeeze(QNFA *nfa);
void squeeze(QCharTreeLevel& lvl);

QNFA* sharedContext(const QString& start,
					QNFA *other,
					bool cs);

QNFA* context(		const QString& start,
					const QString& stop,
					const QString& escape,
					int action,
					QNFA **handler = 0,
					bool cs = true);

inline void addNFA(QNFA *context, QNFA *nfa)
{ context->out.branch->append(nfa); }

bool plain(const QString& word, QString *dest);

void addWord(		QCharTree& tree,
					const QString& w,
					int action,
					bool cs);

void addWord(		QNFA *lexer,
					const QString& w,
					int action,
					bool cs);

void addSequence(	QNFA *lexer,
					const QString& w,
					int action,
					bool cs);

QNFA* sequence(		const QChar *d,
					int length,
					QNFA **end,
					bool cs);

inline QNFA* sequence(
					const QString& s,
					QNFA **end,
					bool cs)
{ return sequence(s.constData(), s.length(), end, cs); }

#endif //!_Q_NFA_H_
