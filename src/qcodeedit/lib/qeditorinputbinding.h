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

#ifndef Header_QEditor_InputBinding
#define Header_QEditor_InputBinding

#include "mostQtHeaders.h"

#include "qeditorinputbindinginterface.h"

#include "qdocumentcursor.h"

class QCE_EXPORT QEditorInputBinding : public QEditorInputBindingInterface
{
	public:
		class Command
		{
			public:
				virtual ~Command() {}
				
				virtual void exec(QEditor *e) = 0;
		};
		
		class MotionCommand : public Command
		{
			public:
				MotionCommand(QDocumentCursor::MoveOperation op, QDocumentCursor::MoveMode m, int n = 1);
				
				virtual void exec(QEditor *e);
				
			private:
				int count;
				QDocumentCursor::MoveMode mode;
				QDocumentCursor::MoveOperation operation;
		};
		
		class EditCommand : public Command
		{
			public:
				enum Operation
				{
					ClearSelection,
					SelectWord,
					SelectLine,
					SelectDocument,
					
					DeleteChar,
					DeletePreviousChar,
					DeleteSelection,
					DeleteLine,
					
					InsertLine,
					InsertClipBoard,
				};
				
				EditCommand(Operation op);
				
				virtual void exec(QEditor *e);
				
			private:
				Operation operation;
		};
		
		class WriteCommand : public Command
		{
			public:
				WriteCommand(const QString& t);
				
				virtual void exec(QEditor *e);
				
			private:
				QString text;
		};
		
		class GroupCommand : public Command
		{
			public:
				void addCommand(Command *c);
				
				virtual void exec(QEditor *e);
				
			private:
				QList<Command*> commands;
		};
		
		QEditorInputBinding();
		~QEditorInputBinding();
		
		void setMapping(const QKeySequence& ks, Command *cmd);
		
		virtual bool isExclusive() const;
		
		virtual bool keyPressEvent(QKeyEvent *event, QEditor *editor);
		virtual void postKeyPressEvent(QKeyEvent *event, QEditor *editor);
		
		virtual bool keyReleaseEvent(QKeyEvent *event, QEditor *editor);
		virtual void postKeyReleaseEvent(QKeyEvent *event, QEditor *editor);

		virtual bool inputMethodEvent(QInputMethodEvent* event, QEditor *editor);
		virtual void postInputMethodEvent(QInputMethodEvent *event, QEditor *editor);
		
		virtual bool mouseMoveEvent(QMouseEvent *event, QEditor *editor);
		virtual void postMouseMoveEvent(QMouseEvent *event, QEditor *editor);
		
		virtual bool mousePressEvent(QMouseEvent *event, QEditor *editor);
		virtual void postMousePressEvent(QMouseEvent *event, QEditor *editor);
		
		virtual bool mouseReleaseEvent(QMouseEvent *event, QEditor *editor);
		virtual void postMouseReleaseEvent(QMouseEvent *event, QEditor *editor);
		
		virtual bool mouseDoubleClickEvent(QMouseEvent *event, QEditor *editor);
		virtual void postMouseDoubleClickEvent(QMouseEvent *event, QEditor *editor);
		
		virtual bool contextMenuEvent(QContextMenuEvent *event, QEditor *editor);
		
	private:
		QVector<int> m_index;
		QVector<Command*> m_actions;
		QVector<QKeySequence> m_keys;
};

#endif // _QEDITOR_INPUT_BINDING_H_
