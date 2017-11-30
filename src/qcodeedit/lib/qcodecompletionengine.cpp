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

#include "qcodecompletionengine.h"

/*!
	\file qcompletionengine.cpp
	\brief Implementation of the QCodeCompletionEngine class.
*/

#include "qeditor.h"

#ifdef _QCODE_MODEL_
#include "qcodebuffer.h"
#endif

/*!

*/
QCodeCompletionEngine::QCodeCompletionEngine(QObject *p)
 : QObject(p), m_max(0)
{
	pForcedTrigger = new QAction(tr("&Trigger completion"), this);

	connect(pForcedTrigger	, SIGNAL( triggered() ),
			this			, SLOT  ( complete() ) );

}

/*!

*/
QCodeCompletionEngine::~QCodeCompletionEngine()
{

}

/*!
	\return
*/
QAction* QCodeCompletionEngine::triggerAction() const
{
	return pForcedTrigger;
}

/*!

*/
void QCodeCompletionEngine::retranslate()
{
	pForcedTrigger->setText(tr("&Trigger completion"));
}

/*!

*/
QStringList QCodeCompletionEngine::triggers() const
{
	return m_triggers;
}

/*!

*/
void QCodeCompletionEngine::addTrigger(const QString& s)
{
	if ( m_triggers.contains(s) )
		return;

	if ( s.count() > m_max )
		m_max = s.count();

	m_triggers << s;
}

/*!

*/
void QCodeCompletionEngine::removeTrigger(const QString& s)
{
	m_triggers.removeAll(s);
}

/*!

*/
void QCodeCompletionEngine::setCodeModel(QCodeModel *m)
{
	Q_UNUSED(m)
}

/*!

*/
QEditor* QCodeCompletionEngine::editor() const
{
	return pEdit;
}

/*!
	\brief Attach the completion engine instance to a new editor object
*/
void QCodeCompletionEngine::setEditor(QEditor *e)
{
	if ( pEdit )
	{
		pEdit->removeAction(pForcedTrigger, "&Edit");
		//pEdit->removeEventFilter(this);

		disconnect(	pEdit	, SIGNAL( textEdited(QKeyEvent*) ),
					this	, SLOT  ( textEdited(QKeyEvent*) ) );
	}

	pEdit = e;

	if ( pEdit )
	{
		//pEdit->installEventFilter(this);
		pEdit->addAction(pForcedTrigger, "&Edit");

		connect(pEdit	, SIGNAL( textEdited(QKeyEvent*) ),
				this	, SLOT  ( textEdited(QKeyEvent*) ) );
	}
}

/*!
	\internal
*/
void QCodeCompletionEngine::run()
{
	if ( m_cur.isNull() )
		return;

	//qDebug("complete!");

	complete(m_cur, m_trig);

	m_cur = QDocumentCursor();
	m_trig.clear();
}

/*!
	\brief Forced completion trigger
*/
void QCodeCompletionEngine::complete()
{
	complete(editor()->cursor(), QString());
}

/*!
	\brief Standard completion entry point for QEditor
	\param e QKeyEvent that caused a modification of the text

	\note This slot is only called when editing happens without
	any cursor mirrors
*/
void QCodeCompletionEngine::textEdited(QKeyEvent *k)
{
	QString s, txt = s = k->text();
	QDocumentCursor cur = editor()->cursor();

	int count = txt.count();

	if ( txt.isEmpty() || m_triggers.isEmpty() )
		return;

	//qDebug("should trigger completion? (bis)");

	if ( count > m_max )
	{
		txt = txt.right(m_max);

	} else if ( count < m_max ) {

		QDocumentCursor c(cur);
		c.movePosition(m_max, QDocumentCursor::Left, QDocumentCursor::KeepAnchor);

		//qDebug("prev text : %s", qPrintable(c.selectedText()));

		txt = c.selectedText();
	}

	//qDebug("text : %s", qPrintable(txt));

	foreach ( QString trig, m_triggers )
	{
		if ( txt.endsWith(trig) )
		{
			cur = editor()->cursor();
			cur.movePosition(trig.count(), QDocumentCursor::PreviousCharacter);

			// notify completion trigger
			emit completionTriggered(trig);

			//get rid of previous calltips/completions
			editor()->setFocus();

			// trigger completion
			complete(cur, trig);
		}
	}
}

/*!
	\internal
*/
bool QCodeCompletionEngine::eventFilter(QObject *o, QEvent *e)
{
	if ( !e || !o || (e->type() != QEvent::KeyPress) || (o != pEdit) )
		return false;

	//qDebug("should trigger completion?");

	QDocumentCursor cur = editor()->cursor();
	QKeyEvent *k = static_cast<QKeyEvent*>(e);

	QString s, txt = s = k->text();

	int count = txt.count();

	if ( txt.isEmpty() || m_triggers.isEmpty() )
		return false; // QThread::eventFilter(o, e);

	//qDebug("should trigger completion? (bis)");

	if ( count > m_max )
	{
		txt = txt.right(m_max);

	} else if ( count < m_max ) {

		QDocumentCursor c(cur);
		c.movePosition(m_max - count, QDocumentCursor::Left, QDocumentCursor::KeepAnchor);

		//qDebug("prev text : %s", qPrintable(c.selectedText()));

		txt.prepend(c.selectedText());
	}

	//qDebug("text : %s", qPrintable(txt));

	foreach ( QString trig, m_triggers )
	{
		if ( txt.endsWith(trig) )
		{
			editor()->write(s);

			cur = editor()->cursor();
			cur.movePosition(trig.count(), QDocumentCursor::PreviousCharacter);

			// notify completion trigger
			emit completionTriggered(trig);

			//get rid of previous calltips/completions
			editor()->setFocus();

			// trigger completion
			complete(cur, trig);

			return true;
		}
	}

	return false;
}

/*!
	\brief Completion callback
*/
void QCodeCompletionEngine::complete(const QDocumentCursor& c, const QString& trigger)
{
	#ifdef _QCODE_MODEL_
	// TODO :
	//	* use a more efficient design by avoiding deep copy of the data
	//	* only lex the requested part (stop at cursor or topmost frame required for proper class hierarchy)

	QDocumentCursor cc = c;
	cc.movePosition(1, QDocumentCursor::Start, QDocumentCursor::KeepAnchor);

	//qDebug("%s", qPrintable(cc.selectedText()));

	QCodeBuffer buffer(cc.selectedText());
	//QCodeBuffer buffer(c.document()->text());
	complete(&buffer, trigger);
	#else
	Q_UNUSED(c)
	Q_UNUSED(trigger)
	qWarning("From complete(QDocumentCursor, QString)");
	qWarning("QCodeCompletionEngine is not self-sufficient : subclasses should "
			"reimplement at least on of the complete() method...");
	#endif
}

/*!
	\overload
	\brief Overloaded completion callback
*/
void QCodeCompletionEngine::complete(QCodeStream *s, const QString& trigger)
{
	Q_UNUSED(s)
	Q_UNUSED(trigger)
	
	qWarning("From complete(QCodeStream*, QString)");
	qWarning("QCodeCompletionEngine is not self-sufficient : subclasses should"
			"reimplement at least on of the complete() method...");
}
