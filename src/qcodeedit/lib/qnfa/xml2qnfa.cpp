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

/*!
	\file xml2qnfa.cpp
	\brief Implementation of the QNFA builder (fetch syntax engine data from XML files)
*/

#include "qnfa.h"
#include "qnfadefinition.h"

#include "qformatscheme.h"

#include "xml2qnfa.h"

#include <QVariant>
#include <QDomText>
#include <QDomElement>
#include <QDomDocument>

/*
	<QNFA>
		<word></word>
		<sequence></sequence>
		
		<context>
			<start></start>
			<stop></stop>
			<escape></escape>
			
			...
			
		</context>
	</QNFA>
*/

QXml2NFAParser::QXml2NFAParser(QFormatScheme *formatScheme, QHash<QString, int>& parenthesisIds, QHash<int, int>& parenthesisWeights, QHash<QString, int>& openingParenthesis, QHash<int, QString>& closingParenthesis):
	f(formatScheme), pids(parenthesisIds), parenWeight(parenthesisWeights), parenOpening(openingParenthesis), parenClosing(closingParenthesis)
{
    singleLineCommentTarget = nullptr;
}

bool stringToBool(const QString& s, bool previous)
{
	if ( s.isEmpty() )
		return previous;
	
	return
			(
				(s == "true")
			||
				(s == "enabled")
			)
		||
			(
				(s != "false")
			&&
				(s != "disabled")
			&&
				QVariant(s).toBool()
			);
}

QString regexpUnescape(const QString& s){
	//regexp chars: \ $, (,), *, +, ., ?, [, ,], ^, {, | and }.
	//used by qce: ( ) * + . ? [ ] | not used: \ $ ^ { }
	QString result;
	result.reserve(s.length());
	for (int i=0;i<s.length(); i++){
		QChar cur = s.at(i);
		if (cur == '\\') {
			i++;
			cur = s[i];
			if (cur == '\\' || cur == '(' || cur == ')' || cur == '*' || cur == '+' || cur == '.' || cur == '?' || cur == '[' || cur == ']' || cur == '|' || cur == '{' || cur == '}' || cur == '$' || cur == '^')
				result += cur;
			else
				return "";
		} else if (!(cur == '(' || cur == ')' || cur == '*' || cur == '+' || cur == '.' || cur == '?' || cur == '[' || cur == ']' || cur == '|'))
			result += cur;
		else return "";
	}
	return result;
}

int QXml2NFAParser::pid(const QString& s)
{
	if ( pids.contains(s) )
		return pids.value(s);
	
	int id = (pids.count() + 1) << 12;
	
	pids[s] = id;

	return id;
}

int QXml2NFAParser::action(QDomElement c, int fid)
{
	QString paren, spid, spt, sfid;
	
	sfid = c.attribute("format");
	
	if ( sfid.count() )
	{
		fid |= QNFAAction::Highlight | QNFAAction::format(f->id(sfid));
	}
	
	paren = c.attribute("parenthesis");
	
	if ( paren.count() )
	{
		spid = paren.section(':', 0, -2);
		spt = paren.section(':', -1, -1);
		
		fid |= QNFAAction::MatchParen;
		bool autoComplete = true;

		int atsep = spt.lastIndexOf('@');
		if (atsep > 0) {
			QString options = spt.mid(atsep+1);
			if (options.contains("nomatch")) fid = fid & ~QNFAAction::MatchParen;
			if (options.contains("nocomplete")) autoComplete = false;
			spt.chop(spt.length() - atsep);
		}


		
		if ( spid.count() )
		{
			/*qDebug("paren : [%s|%s] => 0x%x",
					qPrintable(spid), qPrintable(spt),
					(spt == "open" ? QNFAAction::ParenOpen : QNFAAction::ParenClose) | pid(spid, pids));
			*/
			
			if ( spt == "open" )
				fid |= QNFAAction::ParenOpen;
			else if ( spt == "close" )
				fid |= QNFAAction::ParenClose;
			else if ( spt == "boundary" )
				fid |= QNFAAction::ParenOpen | QNFAAction::ParenClose;

			int cid=pid(spid);
			fid |= QNFAAction::parenthesis(cid);
			
			/*
			qDebug("paren : [%s|%s] => 0x%x",
					qPrintable(spid), qPrintable(spt),
					fid & QNFAAction::ParenMask);
			*/
			QString weight=c.attribute("parenthesisWeight");
			if (weight.count()){
				//qDebug(qPrintable(QString("%1 %2: %3").arg(cid).arg((cid & QNFAAction::ParenMask) >> 8).arg(weight)));
				parenWeight.insert((cid & QNFAAction::ParenMask) >> 8, weight.toInt());
			}

			if (autoComplete){
				QString paren;
				switch ( fid & (QNFAAction::ParenOpen | QNFAAction::ParenClose) ) {
					case QNFAAction::ParenOpen:
						paren = regexpUnescape(c.firstChild().isText() ? c.firstChild().nodeValue() : "");
						if ( paren != "" && !parenOpening.contains(paren) ) parenOpening.insert(paren, cid);
						break;
					case QNFAAction::ParenClose:
						if (!parenClosing.contains(cid) ) {
							paren = regexpUnescape(c.firstChild().isText() ? c.firstChild().nodeValue() : "");
							if ( paren != "" ) parenClosing.insert(cid, paren);
						}
				}
			}
		}

	}
	
	if ( stringToBool(c.attribute("indent"), false) )
		fid |= QNFAAction::Indent;
	
	if ( stringToBool(c.attribute("fold"), false) )
		fid |= QNFAAction::Fold;
	
	// TODO : determine ambiguity automatically
	if ( stringToBool(c.attribute("ambiguous"), false) )
		fid |= QNFAAction::Ambiguous;
	
	return fid;
}

void copy(const QCharTreeLevel& src, QCharTreeLevel& dest)
{
	QCharTreeLevel::const_iterator it = src.constBegin();
	
	while ( it != src.constEnd() )
	{
		//qDebug("copying char tree level %c", QChar(it.key()).toLatin1());
		
		if ( !dest.contains(it.key()) )
			dest[it.key()] = *it;
		else
			copy(it->next, dest[it.key()].next);
		
		++it;
	}
}

void embed(QNFA *src, QNFA *dest, int idx = 0)
{
	const int n = src->out.branch->count();
	
	//dest->out.branch->alloc(idx, n);
	
	//qDebug("\tembedding %i children", n);
	
	for ( int i = 0; i < n; ++i )
	{
		QNFA *nfa = src->out.branch->at(i);
		
		if ( nfa->type & Reserved )
			continue;
		
		//qDebug("\t\teffectively embedding 0x%x at %i", nfa, idx);
		dest->out.branch->insert(idx++, nfa);
	}
	
	copy(src->tree, dest->tree);
}


void replaceAll(QDomNode e, const QString& what, const QString& through) {
	QDomNodeList children = e.childNodes();
	for (int i=0;i<children.count();i++)
		replaceAll(children.at(i),what,through);
	if (e.nodeValue() != "")
		e.setNodeValue(e.nodeValue().replace(what,through));
	if (e.nodeType() == QDomNode::ElementNode){
		QDomNamedNodeMap atts = e.toElement().attributes();
		for (int i=0;i<atts.length();i++)
			replaceAll(atts.item(i), what, through);
	}
}


void QXml2NFAParser::addToContext(	QNFA *cxt, QDomElement c, int fid,
					const QStringList& pref,
					const QStringList& suff,
					bool cs)
{
	QString tag = c.tagName();
	
	if ( !c.hasChildNodes() && tag != "embed" )
		return;
	
	cs = stringToBool(c.attribute("caseSensitive"), cs);
	
	if ( (tag == "start") || (tag == "stop") || (tag == "escape") )
	{
		return;
	} else if ( tag == "word" ) {
		//qDebug("adding word : %s", qPrintable(c.firstChild().toText().data()));
		const QString value = c.firstChild().toText().data();
		
		if ( pref.isEmpty() && suff.isEmpty() )
		{
			addWord(cxt, value, fid, cs);
		} else if ( pref.count() ) {
			foreach ( const QString& p, pref )
			{
				if ( suff.isEmpty() )
				{
					addWord(cxt, p + value, fid, cs);
				} else {
					foreach ( const QString& s, suff )
					{
						addWord(cxt, p + value + s, fid, cs);
					}
				}
			}
		} else {
			foreach ( const QString& s, suff )
			{
				addWord(cxt, value + s, fid, cs);
			}
		}
	} else if ( tag == "sequence" ) {
		const QString value = c.firstChild().toText().data();
		
		//qDebug("adding sequence : %s [0x%x]", qPrintable(value), cxt);
		if ( pref.isEmpty() && suff.isEmpty() )
		{
			addSequence(cxt, value, fid, cs);
		} else if ( pref.count() ) {
			foreach ( const QString& p, pref )
			{
				if ( suff.isEmpty() )
				{
					addSequence(cxt, p + value, fid, cs);
				} else {
					foreach ( const QString& s, suff )
					{
						addSequence(cxt, p + value + s, fid, cs);
					}
				}
			}
		} else {
			foreach ( const QString& s, suff )
			{
				addSequence(cxt, value + s, fid, cs);
			}
		}
	} else if ( tag == "list" ) {
		QDomNodeList children = c.childNodes();
		QStringList prefixes, suffixes;
		
		//qDebug("starting list");
		for ( int j = 0; j < children.count(); ++j )
		{
			QDomElement cc = children.at(j).toElement();
			
			if ( cc.isNull() )
				continue;
			
			const QString role = cc.tagName();
			const QString value = cc.firstChild().toText().data();
			
			if ( role == "prefix" )
				prefixes << value;
			else if ( role == "suffix" )
				suffixes << value;
			else
				addToContext(cxt, cc, action(cc, fid), prefixes, suffixes, cs);
		}
		//qDebug("ending list");
		
	} else if ( tag == "embed" ) {
		QNFADefinition::addEmbedRequest(c.attribute("target"), cxt);
	} else if ( tag == "context" ) {
		QNFA	*nfa,
                *start = nullptr,
                *hstart = nullptr,
                *cstart = nullptr,
                *stop = nullptr,
                *hstop = nullptr,
                *escape = nullptr,
                *hescape = nullptr;
		
		QList<QNFA*> lStart, lStop, lEscape;
		
		QString attr;
		int defact = action(c);
		QDomNodeList children = c.childNodes();
		
		QString _id = c.attribute("id");
		bool trans = stringToBool(c.attribute("transparency"), false);
		bool stay = stringToBool(c.attribute("stayOnLine"), false);
		
		for ( int j = 0; j < children.count(); ++j )
		{
			QDomElement child = children.at(j).toElement();
			
			if ( child.isNull() || !child.hasChildNodes() )
				continue;
			
			bool tcs = stringToBool(child.attribute("caseSensitive"), cs);
			
			int act = action(child);
			
			if ( !(act & QNFAAction::Highlight) )
				act |= QNFAAction::Highlight | QNFAAction::format(defact);
			
			const QString role = child.tagName();
			const QString value = child.firstChild().toText().data();
			
			if ( role == "start" )
			{
				start = sequence(value, &hstart, tcs);
				start->actionid = act;
				//start->type |= Reserved;
				lStart << start;
				
				if ( !cstart )
				{
					cstart = new QNFA;
					cstart->type = ContextBegin | (stay ? StayOnLine : 0);
					cstart->actionid = defact;
					cstart->out.branch = new QNFABranch;
					
					// only the first sequence comes
					if ( singleLineCommentTarget && (_id == "comment/single") )
						*singleLineCommentTarget = value;
					
				}
				
				hstart->out.next = cstart;
				hstart->actionid = act;
				//hstart = nfa;
				
				//qDebug("cxt start seq : %s [0x%x, 0x%x]", qPrintable(value), start, nfa);
				
			} else if ( role == "stop" ) {
				stop = sequence(value, &hstop, tcs);
				stop->actionid = act;
				stop->type |= Reserved;
				lStop << stop;
				
				nfa = new QNFA;
				nfa->type = ContextEnd;
				nfa->actionid = act;
				//nfa->out.branch = new QNFABranch;
				
				hstop->out.next = nfa;
				hstop->actionid = act;
				hstop = nfa;
				
				attr = child.attribute("exclusive");
				
				if ( attr.isEmpty() || (attr == "true") || attr.toUInt() )
					hstop->type |= Exclusive;
				
				//qDebug("cxt stop seq : %s [0x%x]", qPrintable(value), act);
				
			} else if ( role == "escape" ) {
				
				escape = sequence(value, &hescape, tcs);
				escape->type |= Reserved;
				lEscape << escape;
				
				nfa = new QNFA;
				nfa->type = EscapeSeq;
				nfa->actionid = action(child);
				//nfa->out.branch = new QNFABranch;
				
				hescape->out.next = nfa;
				//hescape = nfa;
			}
		}
		
		if ( hstart )
		{
			//qDebug("starting cxt %s:0x%x [0x%x]", qPrintable(c.attribute("id")), cstart, cxt);
			
			foreach ( escape, lEscape )
			{
				//cstart->type |= Escaped;
				addNFA(cstart, escape);
			}
			
			//qDebug("after esc : %i", cstart->out.branch->count());
			
			foreach ( stop, lStop )
				addNFA(cstart, stop);
			
			//qDebug("after stop : %i", cstart->out.branch->count());
		} else {
			cstart = new QNFA;
			cstart->type = ContextBegin | (stay ? StayOnLine : 0);
			cstart->actionid = defact;
			cstart->out.branch = new QNFABranch;
		}
		
		fillContext(cstart, c, cs);
		
		if ( c.hasAttribute("id") )
		{
			QNFADefinition::addContext(
					c.ownerDocument().documentElement().attribute("language")
					+ ":"
					+ _id,
					cstart
				);
			
		} else {
			//qDebug("unregistered context");
		}
		
		//qDebug("after sub : %i", cstart->out.branch->count());
		
		if ( trans )
		{
			QNFADefinition::shareEmbedRequests(cxt, cstart, cstart->out.branch->count());
			embed(cxt, cstart, cstart->out.branch->count());
		}
		
		if ( hstart )
		{
			foreach ( start, lStart )
				addNFA(cxt, start);
			
			//qDebug("ending cxt");
		} else {
			
		}
		
		//fillContext(subcxt, c, f, pids);
	} else if (tag == "foreach") {
		QString var = c.attribute("loopVar");
		Q_ASSERT(!var.isEmpty());
		QStringList values;
		QDomNodeList children = c.childNodes();
		QDomElement body;
		for (int i=0;i<children.count();i++)
			if (children.at(i).toElement().tagName() == "e")
				values << children.at(i).toElement().firstChild().toText().data();
			else if (children.at(i).toElement().tagName() == "body")
				body = children.at(i).toElement();
			else Q_ASSERT(false);
		foreach (const QString& v, values) {
			QDomElement cur = body.cloneNode().toElement();
			replaceAll(cur, var, v);
			children = cur.childNodes();
			for (int i=0;i<children.count();i++)
				addToContext(cxt,children.at(i).toElement(),fid,pref,suff,cs);
		}

	} else {
		//qDebug("unhandled tag : %s", qPrintable(tag));
	}
}

void QXml2NFAParser::fillContext(QNFA *cxt, QDomElement e, bool cs)
{
	cs = stringToBool(e.attribute("caseSensitive"), cs);
	
	fillContext(cxt, e.childNodes(), cs);
}

void QXml2NFAParser::fillContext(QNFA *cxt, QDomNodeList l, bool cs)
{
	//qDebug("filling context from %i nodes", l.count());
	
	for ( int i = 0; i < l.count(); i++ )
	{
		QDomElement c = l.at(i).toElement();
		
		if ( c.isNull() )
			continue;
		
		addToContext(cxt, c, action(c), QStringList(), QStringList(), cs);
	}
	
	//qDebug("context filled");
}
