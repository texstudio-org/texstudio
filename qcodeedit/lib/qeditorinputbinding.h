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

#ifndef _QEDITOR_INPUT_BINDING_H_
#define _QEDITOR_INPUT_BINDING_H_

#include "qeditorinputbindinginterface.h"

class QEditorInputBinding : public QEditorInputBindingInterface
{
	public:
		enum Motion
		{
			None,
			
			MoveLeft,
			MoveRight,
			MoveUp,
			MoveDown,
			
			PageUp,
			PageDown,
			
			MoveToStartOfDocument,
			MoveToEndOfDocument,
			
			MoveToStartOfLine,
			MoveToEndOfLine,
			
			MoveToEndOfWord,
			MoveToStartOfWord,
			
			MoveToMouseCursor
		};
		
		enum Operator
		{
			Move			= 0,
			Select			= 1,
			Delete			= 2,
			CreateMirror	= 4
		}
		
		QEditorInputBinding();
		
		virtual QString id();
		virtual QString name();
		
		virtual bool isExclusive() const;
		
		virtual bool keyPressEvent(QKeyEvent *event, QEditor *editor);
		virtual void postKeyPressEvent(QKeyEvent *event, QEditor *editor);
		
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
};

#endif // _QEDITOR_INPUT_BINDING_H_
