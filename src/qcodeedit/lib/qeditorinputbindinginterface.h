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

#ifndef Header_QEditor_InputBinding_Interface
#define Header_QEditor_InputBinding_Interface

#include "qce-config.h"

class QEditor;

class QString;
class QKeyEvent;
class QMouseEvent;
class QInputMethodEvent;
class QContextMenuEvent;

class QEditorInputBindingInterface
{
	public:
		virtual ~QEditorInputBindingInterface() {}
		
		virtual QString id() const = 0;
		virtual QString name() const = 0;
		
		virtual bool isExclusive() const = 0;
		
		virtual bool keyPressEvent(QKeyEvent *event, QEditor *editor) = 0;
		virtual void postKeyPressEvent(QKeyEvent *event, QEditor *editor) = 0;

		virtual bool keyReleaseEvent(QKeyEvent *event, QEditor *editor) = 0;
		virtual void postKeyReleaseEvent(QKeyEvent *event, QEditor *editor) = 0;
		
		virtual bool inputMethodEvent(QInputMethodEvent* event, QEditor *editor) = 0;
		virtual void postInputMethodEvent(QInputMethodEvent *event, QEditor *editor) = 0;
		
		virtual bool mouseMoveEvent(QMouseEvent *event, QEditor *editor) = 0;
		virtual void postMouseMoveEvent(QMouseEvent *event, QEditor *editor) = 0;
		
		virtual bool mousePressEvent(QMouseEvent *event, QEditor *editor) = 0;
		virtual void postMousePressEvent(QMouseEvent *event, QEditor *editor) = 0;
		
		virtual bool mouseReleaseEvent(QMouseEvent *event, QEditor *editor) = 0;
		virtual void postMouseReleaseEvent(QMouseEvent *event, QEditor *editor) = 0;
		
		virtual bool mouseDoubleClickEvent(QMouseEvent *event, QEditor *editor) = 0;
		virtual void postMouseDoubleClickEvent(QMouseEvent *event, QEditor *editor) = 0;
		
		virtual bool contextMenuEvent(QContextMenuEvent *event, QEditor *editor) = 0;
};

#endif // _QEDITOR_INPUT_BINDING_INTERFACE_H_
