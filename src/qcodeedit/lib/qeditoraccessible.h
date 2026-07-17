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

#ifndef QEDITORACCESSIBLE_H
#define QEDITORACCESSIBLE_H

#include <QAccessible>
#include <QAccessibleWidget>

class QEditor;

/*!
    \file qeditoraccessible.h
    \brief Accessibility interface for QEditor.

    Implements QAccessibleInterface and QAccessibleTextInterface so that
    Windows screen readers (NVDA, JAWS, Narrator) and other AT tools can
    interact with the editor widget via the platform accessibility APIs.
*/

class QEditorAccessible : public QAccessibleWidget, public QAccessibleTextInterface
{
public:
    explicit QEditorAccessible(QEditor *editor);

    // QAccessibleInterface
    QAccessible::Role role() const override;
    QAccessible::State state() const override;
    QString text(QAccessible::Text t) const override;
    void *interface_cast(QAccessible::InterfaceType t) override;

    // QAccessibleTextInterface
    QString text(int startOffset, int endOffset) const override;
    void selection(int selectionIndex, int *startOffset, int *endOffset) const override;
    int selectionCount() const override;
    void addSelection(int startOffset, int endOffset) override;
    void removeSelection(int selectionIndex) override;
    void setSelection(int selectionIndex, int startOffset, int endOffset) override;
    int cursorPosition() const override;
    void setCursorPosition(int position) override;
    int characterCount() const override;
    QRect characterRect(int offset) const override;
    int offsetAtPoint(const QPoint &point) const override;
    void scrollToSubstring(int startIndex, int endIndex) override;
    QString attributes(int offset, int *startOffset, int *endOffset) const override;
    QString textBeforeCursor(int offset, QAccessible::TextBoundaryType boundaryType,
                             int *startOffset, int *endOffset) const override;
    QString textAfterCursor(int offset, QAccessible::TextBoundaryType boundaryType,
                            int *startOffset, int *endOffset) const override;
    QString textAtOffset(int offset, QAccessible::TextBoundaryType boundaryType,
                         int *startOffset, int *endOffset) const override;

    // Accessibility factory
    static QAccessibleInterface *factory(const QString &classname, QObject *object);

private:
    QEditor *editor() const;
    QString fullText() const;
    int offsetFromLineColumn(int line, int column) const;
    void lineColumnFromOffset(int offset, int *line, int *column) const;
    void boundaryOffsets(const QString &text, int offset,
                         QAccessible::TextBoundaryType boundaryType,
                         int *startOffset, int *endOffset) const;
};

#endif // QEDITORACCESSIBLE_H
