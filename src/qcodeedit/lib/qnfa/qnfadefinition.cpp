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

#include "qnfadefinition.h"

/*!
	\file qnfadefinition.cpp
	\brief Implementation of the QNFADefinition class.
*/

#include "qnfa.h"

#include "qformatscheme.h"

#include "qlinemarksinfocenter.h"

#include "xml2qnfa.h"

#include "qdocument.h"
#include "qdocument_p.h"
#include "qdocumentline.h"
#include "qdocumentcursor.h"

#include <QFile>
#include <QKeyEvent>

#include <QDomText>
#include <QDomElement>
#include <QDomDocument>

uint qHash(const QPointer<QDocument>& p) { return qHash((QDocument*)(p)); }

class QNFANotifier : public QNFAMatchHandler
{
	public:
		QNFANotifier(const QString& line)
		{
			m_formats.fill(0, line.length());
		}

		QNFANotifier(const QDocumentLine& line)
		 : m_line(line)
		{
			m_formats.fill(0, line.length());
		}

		~QNFANotifier()
		{
			if ( m_line.isValid() )
			{
				m_line.setFormats(m_formats);
				m_line.setParentheses(m_parens);
			}
		}

		const QVector<int>& formats() const
		{
			return m_formats;
		}

		const QVector<QParenthesis>& parentheses() const
		{
			return m_parens;
		}

		virtual void matched(int pos, int len, int action)
		{
			//qDebug("action 0x%x on [%s]", action, qPrintable(m_line.text().mid(pos, len)));

			if ( !len )
				return;

			//qDebug("matched \"%s\"", qPrintable(m_line.text().mid(pos, len)));

			if (
					!(action & QNFAAction::Content)
				&&
					(
						action
					&
						(
							QNFAAction::ParenOpen
						|
							QNFAAction::ParenClose
						|
							QNFAAction::Indent
						|
							QNFAAction::Fold
						)
					)
				)
			{
				//qDebug("matched paren : %s", qPrintable(m_line.text().mid(pos, len)));

				QParenthesis par(
									(action & QNFAAction::ParenMask) >> 8,
									0,
									pos,
									len
								);

				if ( action & QNFAAction::ParenOpen )
					par.role |= QParenthesis::Open;

				if ( action & QNFAAction::ParenClose )
					par.role |= QParenthesis::Close;

				if ( action & QNFAAction::MatchParen )
					par.role |= QParenthesis::Match;

				if ( action & QNFAAction::Indent )
					par.role |= QParenthesis::Indent;

				if ( action & QNFAAction::Fold )
					par.role |= QParenthesis::Fold;

				m_parens << par;
			}
			
			if ( action & QNFAAction::Highlight )
			{
				int i = qMax(pos, 0);
				int max = qMin(i + len, m_formats.count());
				
				while ( i < max )
					m_formats[i++] = action & QNFAAction::FormatMask;
			}
		}
		
	private:
		QDocumentLine m_line;
		QVector<int> m_formats;
		QVector<QParenthesis> m_parens;
};

void embed(QNFA *src, QNFA *dest, int index);

static inline bool match(const QParenthesis& open, const QParenthesis& close)
{
	return open.id == close.id;
}

extern bool stringToBool(const QString& s, bool previous);

QHash<QString, int> QNFADefinition::m_paren;
QHash<int, int> QNFADefinition::m_parenWeight;
QHash<QString, int> QNFADefinition::m_openingParenthesis;
QHash<int, QString> QNFADefinition::m_closingParenthesis;
QHash<QString, QNFA*> QNFADefinition::m_contexts;
//QHash<QString, QNFADefinition*> QNFADefinition::m_definitions;
QHash<QString, QNFADefinition::EmbedRequestList> QNFADefinition::m_pendingEmbeds;

void QNFADefinition::load(const QString& file, QLanguageFactory::LangData *d, QFormatScheme *s)
{
	QFile f(file);

	if ( !f.open(QFile::ReadOnly | QFile::Text) )
	{
		qWarning("QNFADefinition : failed to open file %s", qPrintable(file));
		return;
	}

	load(&f, d, s);
}

void QNFADefinition::load(QFile *f, QLanguageFactory::LangData *d, QFormatScheme *s)
{
	QDomDocument doc;
	doc.setContent(f);

	load(doc, d, s);
}

bool lengthLessThan(const QString &s1, const QString &s2)
{
	return s1.length() > s2.length();
}


void QNFADefinition::load(const QDomDocument& doc, QLanguageFactory::LangData *d, QFormatScheme *s)
{
	QDomElement root = doc.documentElement();

	QNFADefinition *nd = new QNFADefinition;

	nd->m_language = d->lang = root.attribute("language");
	nd->m_indentFold = stringToBool(root.attribute("indentationFold"), false);
	nd->m_extensions = d->extensions = root.attribute("extensions").split(";");
	nd->m_defaultMark = root.attribute("defaultLineMark", "bookmark");

	/*
	qDebug("Generating definition for %s language from XML file : %s",
			qPrintable(m_language),
			qPrintable(fn));
	*/

	// create root entity
	nd->m_root = lexer();

	QHash<QString, int> tempOpening;
	QHash<int, QString> tempClosing;

	QXml2NFAParser parser(s, m_paren, m_parenWeight, tempOpening, tempClosing);
	parser.singleLineCommentTarget = &(nd->m_singleLineComment);
	parser.fillContext(nd->m_root, root, true);

	memset(nd->m_openingParenthesisEnd, 0, sizeof(nd->m_openingParenthesisEnd));
	foreach (const QString& s, tempOpening.keys()) {
		Q_ASSERT(!s.isEmpty());
		if (!nd->m_openingParenthesisList.contains(s)){
			nd->m_openingParenthesisList.append(s);
			nd->m_openingParenthesisEnd[(int)(s.at(s.length()-1).toLatin1())] = true;
		}
	}
	qSort(nd->m_openingParenthesisList.begin(), nd->m_openingParenthesisList.end(), lengthLessThan);

	for (QHash<QString, int>::iterator i = tempOpening.begin(); i != tempOpening.end(); ++i)
		m_openingParenthesis.insert(i.key(),i.value());
	for (QHash<int, QString>::iterator i = tempClosing.begin(); i != tempClosing.end(); ++i)
		m_closingParenthesis.insert(i.key(),i.value());

	//squeeze(nd->m_root);

	//m_definitions[m_language] = this;
	m_contexts[nd->m_language] = nd->m_root;

	flushEmbedRequests(nd->m_language);

	d->d = nd;
    d->e = nullptr;
	d->s = s;
}

QNFADefinition::QNFADefinition()
 : m_indentFold(false), m_root(nullptr)
{
	for (unsigned int i=0;i < sizeof(m_openingParenthesisEnd)/sizeof(m_openingParenthesisEnd[0]); i++)
		m_openingParenthesisEnd[i] = false;
}

QNFADefinition::~QNFADefinition()
{
	delete m_root;
}

QString QNFADefinition::language() const
{
	return m_language;
}

QStringList QNFADefinition::extensions() const
{
	return m_extensions;
}

/*!
	\brief Entry point for syntax highlighting
*/
int QNFADefinition::tokenize(QDocument *d, int line, int count)
{
	int n = 0;
	bool diffCxt = false;

	QNFA *prevcxt;
	QDocumentLine l, prev = d->line(line - 1);

	//qDebug("reformating %i lines from %i...", count, line);

	while ( (n < count) || diffCxt )
	{
		l = d->line(line);

		if ( !l.isValid() )
			break;

		// get last context nest to check for noteworthy modifications needing further work
		prevcxt = l.matchContext()->context;
		//qDebug("\tline %i, cxt : %i", line, prevcxt);

		if ( prev.isValid() )
		{
			// go on using previous match context (NFA naming...)

			l.matchContext()->context = prev.matchContext()->context;
			l.matchContext()->parents = prev.matchContext()->parents;
			l.matchContext()->meaningless = prev.matchContext()->meaningless;
		} else {
			// first line : reset context....

			l.matchContext()->reset();

			/*
			qDebug("reset : popping down by %i contexts", line.matchContext()->parents.count());

			while ( line.matchContext()->parents.count() )
				line.matchContext()->context = line.matchContext()->parents.pop();
			*/
		}

		// call the implementation
		if ( !l.matchContext()->context )
			l.matchContext()->context = m_root;

		QNFANotifier notifier(l);
		QString txt = l.text() + "\n";
		::match(l.matchContext(), txt, &notifier);

		// update cont state, i.e. whether or not highlighting info of next block shall be updated
		diffCxt = (prevcxt != l.matchContext()->context);
		//qDebug("\t->%i (%i)", l.matchContext()->context, diffCxt);
		prev = l;
		++line;
		++n;
	}

	return n;
}

/*!
	\brief Return the string starting a single line comment, if any offered by the language
*/
QString QNFADefinition::singleLineComment() const
{
	return m_singleLineComment;
}

const QStringList& QNFADefinition::openingParenthesis() const
{
	return m_openingParenthesisList;
}

const QStringList QNFADefinition::closingParentheses() const
{
	// TODO: this may be precalculated once when m_openingParenthesisList is set up.
	QStringList closings;
	foreach (const QString &opening, openingParenthesis())
		closings << getClosingParenthesis(opening);
	return closings;
}

QString QNFADefinition::getClosingParenthesis(const QString& opening) const
{
	return m_closingParenthesis.value(m_openingParenthesis.value(opening, -1), "");
}

bool QNFADefinition::possibleEndingOfOpeningParenthesis(const QString& text) const{
	if (text.isEmpty()) return false;
	QChar last = text.at(text.length()-1);
	char l = last.toLatin1();
	if(l>0) {
	//Q_ASSERT(l >=0 && l <= 255); // leads to crashes here when special charcters are put in (ä = -28)
	return m_openingParenthesisEnd[(int)l];
	} else return false;
}

/*const QHash<int, QString>& QNFADefinition::closingParenthesis() const{
	return m_closingParenthesis;
}*/


QString QNFADefinition::defaultLineMark() const
{
	return m_defaultMark;
}

int QNFADefinition::parenthesisWeight(int id) const{
	return m_parenWeight.value(id, -1);
}

/*!
	\brief Brace matching entry point
*/
void QNFADefinition::clearMatches(QDocument *d)
{
	QHash<QPointer<QDocument>, int>::iterator it = m_matchGroups.find(d);

	if ( it != m_matchGroups.end() )
	{
		d->clearMatches(*it);
		d->flushMatches(*it);

		// erase?
		//m_matchGroups.erase(it);
	}
}

/*!
	\brief Brace matching entry point
*/
void QNFADefinition::match(QDocumentCursor& c)
{
	QDocumentLine b = c.line();
	QDocument *d = c.document();

	if ( !d || !b.isValid() )
	{
		qDebug("invalid cursor");
		return;
	}

	int gid = 0;
	QHash<QPointer<QDocument>, int>::iterator it = m_matchGroups.find(d);

	if ( it != m_matchGroups.end() )
	{
		d->clearMatches(*it);
		d->flushMatches(*it);
		*it = gid = d->getNextGroupId();
	} else {
		gid = d->getNextGroupId();
		m_matchGroups[d] = gid;
	}

	QFormatScheme *s = d->formatScheme();

	if ( !s )
	{
		qDebug("no fmt");
		d->releaseGroupId(gid);
		m_matchGroups.remove(d);
		return;
	}

	int matchFID = s->id("braceMatch"), mismatchFID = s->id("braceMismatch");


	QList<PMatch> matches;
	getPMatches(c, matches);

	if ( matches.isEmpty() )
	{
		// required to properly update display
		d->releaseGroupId(gid);
		m_matchGroups.remove(d);
		return;
	}


	foreach (const PMatch&  m, matches) {
		int mfid = m.type == PMatch::Match ? matchFID : mismatchFID;
		d->addMatch(gid, m.line[0], m.column[0], m.length[0], mfid);
		d->addMatch(gid, m.line[1], m.column[1], m.length[1], mfid);
	}

	d->flushMatches(gid);
}

void QNFADefinition::getPMatches(const QDocumentCursor& c, QList<QNFADefinition::PMatch>& matches) const{
	QDocumentLine b = c.line();
	QDocument *d = c.document();

	matches.clear();

	if ( !d || !b.isValid() )
	{
		qDebug("invalid cursor");
		return;
	}

	int pos = c.columnNumber();
	const QVector<QParenthesis>& m_parens = b.parentheses();

	if ( m_parens.isEmpty() )
		return;

	QParenthesis p;

	//qDebug("matching on line %i (fid is %i)", c.lineNumber(), fid);

	foreach ( p, m_parens )
	{
		if ( (pos != p.offset) && (pos != (p.offset + p.length)) )
			continue;

		if ( !(p.role & QParenthesis::Match) )
			continue;

		PMatch m;
		m.line[0] = c.lineNumber();
		m.column[0] = p.offset;
		m.length[0] = p.length;
		m.weight[0] = parenthesisWeight(p.id);

		if ( (p.role & QParenthesis::Open) && (p.role & QParenthesis::Close) )
		{
			matchOpen(d, m);

			if ( m.type == PMatch::Match )
				matches << m;

			m.line[0] = c.lineNumber();
			m.column[0] = p.offset;
			m.length[0] = p.length;
			m.weight[0] = parenthesisWeight(p.id);

			matchClose(d, m);

			if ( m.type == PMatch::Match )
				matches << m;

			continue;
		} else if ( p.role & QParenthesis::Open ) {
			matchOpen(d, m);
		} else if ( p.role & QParenthesis::Close ) {
			matchClose(d, m);
		}

		if ( m.type != PMatch::Invalid )
			matches << m;
	}

}

QList<QList<QDocumentCursor> > QNFADefinition::getMatches(const QDocumentCursor& c) const{
	QList<QList<QDocumentCursor> > res;
	QDocument *d = c.document();
	if (!d) return res;
	QList<PMatch> matches;
	getPMatches(c, matches);
	if (matches.isEmpty())
		return res;
	foreach (const PMatch &m, matches)
		res << (QList<QDocumentCursor> ()
			 << d->cursor(m.line[0], m.column[0], m.line[0], m.column[0]+m.length[0])
			 << d->cursor(m.line[1], m.column[1], m.line[1], m.column[1]+m.length[1]));
	return res;
}

QDocumentCursor QNFADefinition::getNextMismatch(const QDocumentCursor& scope) const{
	QDocumentCursor rscope = scope;
	QDocument* doc = rscope.document();
	Q_ASSERT(doc);
	if (!doc) return QDocumentCursor();
	if (!rscope.hasSelection()) rscope.movePosition(1, QDocumentCursor::End, QDocumentCursor::KeepAnchor);
	int begline, begcol, endline, endcol;
	rscope.boundaries(begline, begcol, endline, endcol);
	for (int l = begline; l <= endline; l++) {
		const QVector<QParenthesis> & parens = doc->line(l).parentheses();
		foreach (const QParenthesis& p, parens) {
			if (l == begline && p.offset+p.length < begcol ) continue;
			if (l == endline && p.offset > endcol ) continue;
			QList<PMatch> pmatches;
			QDocumentCursor bracketCursor = doc->cursor(l,p.offset,l,p.offset+p.length);
			getPMatches(bracketCursor, pmatches);
			if (pmatches.isEmpty()) return bracketCursor;
			foreach (const PMatch & match,pmatches)
				if (match.type == PMatch::Invalid || match.type == PMatch::Mismatch)
					return bracketCursor;
		}
	}
	return QDocumentCursor();
}

void QNFADefinition::matchOpen(QDocument *d, PMatch& m) const
{
	int line = m.line[0];
	int pos = m.column[0];
	QVector<QParenthesis> m_parens = d->line(line).parentheses();

	bool bMatch = false;
	QParenthesis par;
	QStack<int> lines;
	QStack<QParenthesis> parens;

	forever
	{
		foreach ( par, m_parens )
		{
			if ( par.offset < pos )
				continue;
//qDebug("%i: %i vs. %i", par.id, m_parenWeight.value(par.id, -1), m.weight[0]);
			if ( parenthesisWeight(par.id) < m.weight[0] )
				continue;

			if ( (par.role & QParenthesis::Open) && (par.role & QParenthesis::Close) )
			{
				bool bInsert = true;
				
				if (  parens.count() )
				{
					if ( ::match(par, parens.top()) )
					{
						//qDebug("submatch at %i", line);
						parens.pop();
						lines.pop();

						if ( parens.isEmpty() )
						{
							bMatch = true;
							//qDebug("match at %i", line);
							m.type = PMatch::Match;

							break;
						}
					} else {
						bInsert = false;

						do
						{
							QParenthesis tp = parens.top();

							if ( (tp.role & QParenthesis::Open) && (tp.role & QParenthesis::Close) )
							{
								if ( par.id < tp.id )
								{
									parens.pop();
								} else {
									break;
								}
							} else {
								break;
							}

						} while ( parens.count() );

						if ( parens.isEmpty() )
						{
							bMatch = true;
							m.type = PMatch::Mismatch;
							break;
						}
					}
				}

				if ( bInsert )
				{
					parens.push(par);
					lines.push(line);
				}
			} else if ( par.role & QParenthesis::Open ) {
				lines.push(line);
				parens.push(par);
			} else if ( par.role & QParenthesis::Close ) {
				if ( (bMatch = ::match(parens.top(), par)) )
				{
					bMatch &= parens.count() == 1;

					if ( bMatch )
					{
						m.type = PMatch::Match;

						break;
					} else if ( parens.count() ) {
						parens.pop();
						lines.pop();
					} else
						qWarning("bad paren nesting...");
				} else {
					bMatch = true;

					QParenthesis p = parens.pop();

					m.line[0] = lines.pop();
					m.column[0] = p.offset;
					m.length[0] = p.length;

					m.type = PMatch::Mismatch;

					break;
				}
			}
		}

		if ( bMatch )
			break;

		pos = 0;
		++line;

		QDocumentLine b = d->line(line);

		if ( !b.isValid() )
		{
			m.type = PMatch::Invalid;
			return;
		}

		m_parens = b.parentheses();
	}

	m.line[1] = line;
	m.column[1] = par.offset;
	m.length[1] = par.length;
	//m.weight[1] = parenthesisWeight(.value(par.id, -1); would be more consistent, but weight[1] won't be used
}

void QNFADefinition::matchClose(QDocument *d, PMatch& m) const
{
	int line = m.line[0];
	int pos = m.column[0];
	QVector<QParenthesis> m_parens = d->line(line).parentheses();

	bool bMatch = false;
	QParenthesis par;
	QStack<int> lines;
	QStack<QParenthesis> parens;

	forever
	{
		for ( int i = m_parens.count() - 1; i >= 0; --i )
		{
			par = m_parens.at(i);

			if ( par.offset > pos )
				continue;

			if ( parenthesisWeight(par.id) < m.weight[0] )
				continue;

			if ( (par.role & QParenthesis::Open) && (par.role & QParenthesis::Close) )
			{
				bool bInsert = true;

				if (  parens.count() )
				{
					if ( ::match(par, parens.top()) )
					{
						//qDebug("submatch at %i", line);
						parens.pop();
						lines.pop();

						if ( parens.isEmpty() )
						{
							//qDebug("match at %i", line);
							bMatch = true;
							m.type = PMatch::Match;

							break;
						}
					} else {
						bInsert = false;
						do
						{
							QParenthesis tp = parens.top();

							if ( (tp.role & QParenthesis::Open) && (tp.role & QParenthesis::Close) )
							{
								if ( par.id < tp.id )
								{
									parens.pop();
								} else {
									break;
								}
							} else {
								break;
							}

						} while ( parens.count() );

						if ( parens.isEmpty() )
						{
							bMatch = true;
							m.type = PMatch::Mismatch;
							break;
						}
					}
				}

				if ( bInsert )
				{
					parens.push(par);
					lines.push(line);
				}
			} else if ( par.role & QParenthesis::Close ) {
				parens.push(par);
				lines.push(line);
			} else if ( par.role & QParenthesis::Open ) {
				if ( ::match(par, parens.top()) )
				{
					bMatch = parens.count() == 1;

					if ( bMatch )
					{
						m.type = PMatch::Match;

						break;
					} else if ( parens.count() ) {
						parens.pop();
						lines.pop();
					} else
						qWarning("bad paren nesting...");
				} else {
					bMatch = true;

					QParenthesis p = parens.pop();

					m.line[0] = lines.pop();
					m.column[0] = p.offset;
					m.length[0] = p.length;

					m.type = PMatch::Mismatch;

					break;
				}
			}
		}

		if ( bMatch )
			break;

		--line;

		QDocumentLine b = d->line(line);
		pos = b.length();

		if ( !b.isValid() )
		{
			m.type = PMatch::Invalid;
			return;
		}

		m_parens = b.parentheses();
	}

	m.line[1] = line;
	m.column[1] = par.offset;
	m.length[1] = par.length;
	//m.weight[1] = parenthesisWeight(.value(par.id, -1); would be more consistent, but weight[1] won't be used
}

/*!
 * \brief Returns the column number of the first non-space char (or the length of s, if s consists purely of spaces)
 */
int firstNonSpaceCol(const QString &s) {
	int pos = 0;
	for ( pos = 0; pos < s.size(); ++pos )
		if ( !s.at(pos).isSpace() )
			break;
	return pos;
}

/*!
	\brief Return the indent to use when inserting a line at a given cursor position
*/
QString QNFADefinition::indent(const QDocumentCursor& c, int* indentCount)
{
	if ( c.isNull() || c.line().isNull() )
		return QString();

	QDocumentLine curLine = c.line();
	int insertCol = qMin(c.columnNumber(), curLine.text().size());

	QString s = curLine.text().left(insertCol);

	//qDebug("line %i, column %i : %s", b.lineNumber(), c.columnNumber(), qPrintable(s));

	int pos = qMin(firstNonSpaceCol(s), insertCol);
	
	int indent = 0;
	QString spaces = s.left(pos);
	
	int initialUnindent = 0; 
	int initialUnindentCharacters = spaces.size();
	
	foreach ( QParenthesis p, curLine.parentheses() )
	{
		if ( p.offset >= insertCol )
			break;

		if ( !(p.role & QParenthesis::Indent) )
			continue;

		if ( p.role & QParenthesis::Open )
		{
			++indent;
		} else if ( p.role & QParenthesis::Close ) {
			--indent;
			
			if (p.offset == initialUnindentCharacters) {
				initialUnindent++;
				initialUnindentCharacters += p.length;
				for (; initialUnindentCharacters < insertCol; initialUnindentCharacters++)
					if ( !s.at(initialUnindentCharacters).isSpace() ) 
						break;
			}
		}
	}

	//qDebug("indent : %i", indent);

	if ( indent > 0 )
		spaces += QString(indent, '\t');

	if ( indentCount ) 
		*indentCount = indent + initialUnindent;
	
	return spaces;
}

/*!
	\brief Determines whether the given key event at the given position should cause unindent to happen
*/
bool QNFADefinition::unindent (const QDocumentCursor& c, const QString& ktxt)
{
	if ( c.isNull() || c.line().isNull() || ktxt.isEmpty() )
		return false;

	QDocumentLine curLine = c.line();
	QDocumentLine prevLine = c.document()->line(c.lineNumber() - 1);
	
	if ( !prevLine.isValid() )
		return false;
	
	if ( (prevLine.indent() - curLine.indent()) >= c.document()->tabStop() )
		return false;

	int insertCol = qMin(c.columnNumber(), curLine.text().size());
	QString s = curLine.text();
	s.insert(insertCol, ktxt);

	//qDebug("outdenting %s", qPrintable(s));
	int pos = qMin(firstNonSpaceCol(s), insertCol);
	if ( !pos || pos >= c.columnNumber() + ktxt.length() )
		return false;

	QString text = s.mid(pos);

	QNFAMatchContext cxt;
	QNFANotifier notify(text);
	
	if ( prevLine.isValid() )
	{
		cxt = prevLine.matchContext();
	} else {
		// first line
		cxt = curLine.matchContext();
		cxt.reset();
	}

	::match(&cxt, text, &notify);

	const QVector<QParenthesis>& parens = notify.parentheses();

	if ( parens.isEmpty() )
		return false;

	//qDebug("%i parentheses", parens.count());
	QParenthesis p = parens.first();

	//qDebug("%i, %i, %i", p.offset, p.length, c.columnNumber());

	return (
				(p.role & QParenthesis::Close)
			&&
				(p.role & QParenthesis::Indent)
			&&
				(p.offset <= c.columnNumber() - pos)
			&&
				(p.offset + p.length > c.columnNumber() - pos)
			);

}

/*!
	\brief Expand a collapsed block at a given line
*/
void QNFADefinition::expand(QDocument *d, int line)
{
	fold(d, line, true);
}

/*!
	\brief Collapse a text block at a given line
*/
void QNFADefinition::collapse(QDocument *d, int line)
{
	fold(d, line, false);
}

void QNFADefinition::fold(QDocument *d, int line, bool expand){
	QDocumentLine b = d->line(line);

	if ( !b.isValid() || (b.hasFlag(QDocumentLine::CollapsedBlockStart) != expand) )
		return;


	QFoldedLineIterator fli = foldedLineIterator(d, line-1);

	//check if folding is actually possible
	QFoldedLineIterator fli_check = fli; //copy iterator because it can't go back
	++fli_check;
	if (expand){
		Q_ASSERT(fli_check.collapsedBlockStart);
		if (!fli_check.collapsedBlockStart) return;
	} else {
		Q_ASSERT(fli_check.open && !fli_check.collapsedBlockStart);
		if (!fli_check.open  || fli_check.collapsedBlockStart) return;
	}

	//set flag to tell the iterator that the line should be folded
	b.setFlag(QDocumentLine::CollapsedBlockStart, !expand);

	//goto line to fold
	++fli;

	int firstParenthesisPos = fli.openParentheses.size() - fli.open;
	const FoldedParenthesis firstParenthesis = fli.openParentheses[firstParenthesisPos];

	while (fli.lineNr<d->lines() &&
	       firstParenthesisPos<fli.openParentheses.size() &&
	       fli.openParentheses[firstParenthesisPos] == firstParenthesis){
		++fli;
		d->line(fli.lineNr).setFlag(QDocumentLine::Hidden, fli.hidden);
	}
	d->line(fli.lineNr).setFlag(QDocumentLine::CollapsedBlockEnd, fli.collapsedBlockEnd);


	if (expand)
		d->impl()->showEvent(line, -1); //expand all blocks starting on this line (count can't reliably determined because the expanding could have the hidden parenthesis weights)
	else {
		int count = fli.lineNr - line;
		if (!fli.hiddenCollapsedBlockEnd || fli.lineNr==d->lines())
			--count;
		d->impl()->hideEvent(line, count);
	}
}


/*! Corrects the folding of a document
    i.e., it ensures that no line is hidden which is not in an collapsable block
    (useful if the blocks have changed)
*/
bool QNFADefinition::correctFolding(QDocument *d){
	bool changed=false;
	for (QFoldedLineIterator fli = foldedLineIterator(d);
	     fli.lineNr<d->lines();
	     ++fli){
		changed |= fli.lineFlagsInvalid();
		if (changed) {
			QDocumentLine &l = fli.line;
			l.setFlag(QDocumentLine::Hidden, fli.hidden);
			l.setFlag(QDocumentLine::CollapsedBlockStart, fli.collapsedBlockStart);
			l.setFlag(QDocumentLine::CollapsedBlockEnd, fli.collapsedBlockEnd);
		}
	}
	return changed;
}

void QNFADefinition::addContext(const QString& id, QNFA *nfa)
{
	//qDebug("registering context : %s", qPrintable(id));
	m_contexts[id] = nfa;
}

void QNFADefinition::flushEmbedRequests(const QString& lang)
{
	//qDebug("flushing requests for : %s", qPrintable(lang));
	QHash<QString, EmbedRequestList>::iterator it;
	
	it = m_pendingEmbeds.begin();

	while ( it != m_pendingEmbeds.end() )
	{
		QString r = it.key();

		if (
				r.startsWith(lang)
			&&
				(
					(r.count() == lang.count())
				||
					(r.at(lang.count()) == ':')
				)
			)
		{
			QNFA *src = m_contexts.value(r);

			if ( !src )
			{
				++it;
				continue;
			}

			foreach( const EmbedRequest& request, *it )
			{
				//qDebug("embedding %s in 0x%x at index %i",
				//		qPrintable(r), request.target, request.index);

				embed(src, request.target, request.index);
			}

			it = m_pendingEmbeds.erase(it);
		} else {
			++it;
		}
	}
}

void QNFADefinition::addEmbedRequest(const QString& cxt, QNFA *dest)
{
	//qDebug("Adding request : %s", qPrintable(cxt));

	if ( m_contexts.contains(cxt) )
	{
		//qDebug("dealing with request : %s", qPrintable(cxt));
		embed(m_contexts[cxt], dest, dest->out.branch->count());
	} else {
		m_pendingEmbeds[cxt] << EmbedRequest(dest, dest->out.branch->count());
	}
}

void QNFADefinition::shareEmbedRequests(QNFA *src, QNFA *dest, int offset)
{
	QHash<QString, EmbedRequestList>::iterator it = m_pendingEmbeds.begin();

	while ( it != m_pendingEmbeds.end() )
	{
		foreach ( const EmbedRequest& request, *it )
		{
			if ( request.target == src )
			{
				//qDebug("sharing one embed request between 0x%x and 0x%x at %i + %i", src, dest, offset, request.index);
				it->append(EmbedRequest(dest, request.index + offset));
			}
		}

		++it;
	}
}
