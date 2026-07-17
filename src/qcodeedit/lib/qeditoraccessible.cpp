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

#include "qeditoraccessible.h"
#include "qeditor.h"
#include "qdocument.h"
#include "qdocumentcursor.h"
#include "qdocumentline.h"

#include <QTextBoundaryFinder>

/*!
    \file qeditoraccessible.cpp
    \brief Accessibility interface for QEditor.

    Exposes the QEditor text widget to platform accessibility APIs so that
    Windows screen readers (NVDA, JAWS, Narrator) and other AT tools can
    read and interact with the editor content.

    Absolute character offsets are computed by treating the document as a
    plain string where each line is terminated by a single '\n' character
    (except the last line).  This is consistent with \c fullText() which
    joins the lines with '\n'.
*/

QEditorAccessible::QEditorAccessible(QEditor *editor)
    : QAccessibleWidget(editor, QAccessible::EditableText)
{
}

// ---------------------------------------------------------------------------
// Private helpers
// ---------------------------------------------------------------------------

QEditor *QEditorAccessible::editor() const
{
    return qobject_cast<QEditor *>(object());
}

/*!
    \brief Returns the full document text with '\n' line separators.

    This is the canonical text string used for all offset calculations.
*/
QString QEditorAccessible::fullText() const
{
    QEditor *ed = editor();
    if (!ed || !ed->document())
        return QString();

    const int count = ed->document()->lineCount();
    if (count == 0)
        return QString();

    QString result;
    // Reserve a rough estimate to avoid many reallocations.
    result.reserve(count * 40);
    for (int i = 0; i < count; ++i) {
        if (i > 0)
            result += QLatin1Char('\n');
        result += ed->document()->line(i).text();
    }
    return result;
}

/*!
    \brief Convert (line, column) to an absolute character offset.

    Offsets are 0-based.  Each line is separated by exactly one '\n'
    character in the canonical text representation.
*/
int QEditorAccessible::offsetFromLineColumn(int line, int column) const
{
    QEditor *ed = editor();
    if (!ed || !ed->document())
        return 0;

    int offset = 0;
    const int lineCount = ed->document()->lineCount();
    for (int i = 0; i < line && i < lineCount; ++i)
        offset += ed->document()->line(i).length() + 1; // +1 for '\n'

    return offset + qMax(0, column);
}

/*!
    \brief Convert an absolute character offset to (line, column).

    The result is written to \a line and \a column (both 0-based).
    If \a offset is out of range it is clamped to [0, characterCount()].
*/
void QEditorAccessible::lineColumnFromOffset(int offset, int *line, int *column) const
{
    *line = 0;
    *column = 0;

    QEditor *ed = editor();
    if (!ed || !ed->document())
        return;

    const int lineCount = ed->document()->lineCount();
    int remaining = qMax(0, offset);

    for (int i = 0; i < lineCount; ++i) {
        const int lineLen = ed->document()->line(i).length();
        if (remaining <= lineLen) {
            *line = i;
            *column = remaining;
            return;
        }
        remaining -= lineLen + 1; // +1 for '\n'
    }

    // Clamp to end of document.
    *line = qMax(0, lineCount - 1);
    *column = lineCount > 0 ? ed->document()->line(*line).length() : 0;
}

// ---------------------------------------------------------------------------
// QAccessibleInterface overrides
// ---------------------------------------------------------------------------

QAccessible::Role QEditorAccessible::role() const
{
    return QAccessible::EditableText;
}

QAccessible::State QEditorAccessible::state() const
{
    QAccessible::State s = QAccessibleWidget::state();
    QEditor *ed = editor();
    if (ed) {
        if (ed->isReadOnly())
            s.readOnly = true;
        else
            s.editable = true;

        if (ed->cursor().hasSelection())
            s.selected = true;
    }
    return s;
}

QString QEditorAccessible::text(QAccessible::Text t) const
{
    QEditor *ed = editor();
    if (!ed)
        return QString();

    switch (t) {
    case QAccessible::Name:
        // Return the file name as the accessible name, falling back to a
        // generic description so that screen readers have something to announce.
        if (!ed->fileName().isEmpty())
            return ed->fileName();
        return QLatin1String("Text editor");
    case QAccessible::Value:
        return fullText();
    case QAccessible::Description:
        return QLatin1String("LaTeX source editor");
    default:
        return QAccessibleWidget::text(t);
    }
}

void *QEditorAccessible::interface_cast(QAccessible::InterfaceType t)
{
    if (t == QAccessible::TextInterface)
        return static_cast<QAccessibleTextInterface *>(this);
    return QAccessibleWidget::interface_cast(t);
}

// ---------------------------------------------------------------------------
// QAccessibleTextInterface implementation
// ---------------------------------------------------------------------------

QString QEditorAccessible::text(int startOffset, int endOffset) const
{
    const QString full = fullText();
    const int len = full.length();
    startOffset = qBound(0, startOffset, len);
    endOffset   = qBound(0, endOffset,   len);
    if (startOffset > endOffset)
        qSwap(startOffset, endOffset);
    return full.mid(startOffset, endOffset - startOffset);
}

int QEditorAccessible::characterCount() const
{
    return fullText().length();
}

int QEditorAccessible::cursorPosition() const
{
    QEditor *ed = editor();
    if (!ed)
        return 0;
    const QDocumentCursor c = ed->cursor();
    return offsetFromLineColumn(c.lineNumber(), c.columnNumber());
}

void QEditorAccessible::setCursorPosition(int position)
{
    QEditor *ed = editor();
    if (!ed)
        return;
    int line = 0, col = 0;
    lineColumnFromOffset(position, &line, &col);
    ed->setCursorPosition(line, col);
}

void QEditorAccessible::selection(int selectionIndex, int *startOffset, int *endOffset) const
{
    *startOffset = 0;
    *endOffset   = 0;

    if (selectionIndex != 0)
        return;

    QEditor *ed = editor();
    if (!ed)
        return;

    const QDocumentCursor c = ed->cursor();
    if (!c.hasSelection())
        return;

    const int anchor = offsetFromLineColumn(c.anchorLineNumber(), c.anchorColumnNumber());
    const int pos    = offsetFromLineColumn(c.lineNumber(),       c.columnNumber());

    *startOffset = qMin(anchor, pos);
    *endOffset   = qMax(anchor, pos);
}

int QEditorAccessible::selectionCount() const
{
    QEditor *ed = editor();
    if (!ed)
        return 0;
    return ed->cursor().hasSelection() ? 1 : 0;
}

void QEditorAccessible::addSelection(int startOffset, int endOffset)
{
    setSelection(0, startOffset, endOffset);
}

void QEditorAccessible::removeSelection(int selectionIndex)
{
    if (selectionIndex != 0)
        return;
    QEditor *ed = editor();
    if (!ed)
        return;
    const int pos = cursorPosition();
    int line = 0, col = 0;
    lineColumnFromOffset(pos, &line, &col);
    ed->setCursorPosition(line, col);
}

void QEditorAccessible::setSelection(int selectionIndex, int startOffset, int endOffset)
{
    if (selectionIndex != 0)
        return;
    QEditor *ed = editor();
    if (!ed)
        return;

    int startLine = 0, startCol = 0, endLine = 0, endCol = 0;
    lineColumnFromOffset(startOffset, &startLine, &startCol);
    lineColumnFromOffset(endOffset,   &endLine,   &endCol);

    QDocumentCursor c(ed->document(), startLine, startCol);
    c.setSelectionBoundary(QDocumentCursor(ed->document(), endLine, endCol));
    ed->setCursor(c);
}

QRect QEditorAccessible::characterRect(int offset) const
{
    QEditor *ed = editor();
    if (!ed)
        return QRect();

    int line = 0, col = 0;
    lineColumnFromOffset(offset, &line, &col);

    const QRectF docRect = ed->document()->lineRect(line);
    if (!docRect.isValid())
        return QRect();

    // Use the editor's cursor-to-screen conversion: approximate by using the
    // line rect translated by the horizontal scroll offset.
    const QDocumentLine docLine = ed->document()->line(line);
    const QPointF charPos = docLine.cursorToDocumentOffset(col);

    qreal panelLeft = 0, panelTop = 0, temp = 0;
    ed->getPanelMargins(&panelLeft, &panelTop, &temp, &temp);

    const qreal x = panelLeft + charPos.x() - ed->horizontalScrollBar()->value();
    const qreal y = panelTop  + docRect.top() - ed->verticalScrollBar()->value() * ed->document()->getLineSpacing();

    const QPoint globalOffset = ed->viewport()->mapToGlobal(QPoint(0, 0));
    return QRect(globalOffset.x() + qRound(x),
                 globalOffset.y() + qRound(y),
                 1,
                 qRound(ed->document()->getLineSpacing()));
}

int QEditorAccessible::offsetAtPoint(const QPoint &point) const
{
    QEditor *ed = editor();
    if (!ed)
        return -1;

    const QPoint viewportPoint = ed->viewport()->mapFromGlobal(point);
    const QDocumentCursor c = ed->cursorForPosition(viewportPoint);
    if (!c.isValid())
        return -1;
    return offsetFromLineColumn(c.lineNumber(), c.columnNumber());
}

void QEditorAccessible::scrollToSubstring(int startIndex, int endIndex)
{
    Q_UNUSED(endIndex)
    QEditor *ed = editor();
    if (!ed)
        return;

    int line = 0, col = 0;
    lineColumnFromOffset(startIndex, &line, &col);
    ed->ensureVisible(line);
}

QString QEditorAccessible::attributes(int offset, int *startOffset, int *endOffset) const
{
    // Return the extent of the word/run at offset; no rich-text attributes.
    *startOffset = offset;
    *endOffset   = offset;

    const QString full = fullText();
    if (offset < 0 || offset >= full.length())
        return QString();

    // Expand to the current run of characters with the same category.
    // Whitespace, alphanumeric, and punctuation/symbol characters each form
    // separate runs.  Punctuation characters are each their own run of length 1
    // because both isSpace and isLetterOrNumber are false for them, meaning
    // no expansion is possible.
    int start = offset;
    int end   = offset + 1;

    const QChar ch = full.at(offset);
    const bool isSpace = ch.isSpace();
    const bool isAlNum = ch.isLetterOrNumber();

    // Only expand for whitespace or alphanumeric runs.
    if (isSpace || isAlNum) {
        while (start > 0) {
            const QChar c = full.at(start - 1);
            if ((isSpace && !c.isSpace()) || (isAlNum && !c.isLetterOrNumber()))
                break;
            --start;
        }
        while (end < full.length()) {
            const QChar c = full.at(end);
            if ((isSpace && !c.isSpace()) || (isAlNum && !c.isLetterOrNumber()))
                break;
            ++end;
        }
    }

    *startOffset = start;
    *endOffset   = end;
    return QString();
}

// ---------------------------------------------------------------------------
// Text boundary helpers
// ---------------------------------------------------------------------------

void QEditorAccessible::boundaryOffsets(const QString &text, int offset,
                                        QAccessible::TextBoundaryType boundaryType,
                                        int *startOffset, int *endOffset) const
{
    *startOffset = offset;
    *endOffset   = offset;

    if (text.isEmpty() || offset < 0 || offset > text.length())
        return;

    switch (boundaryType) {
    case QAccessible::CharBoundary:
        if (offset < text.length()) {
            *startOffset = offset;
            *endOffset   = offset + 1;
        } else {
            *startOffset = qMax(0, offset - 1);
            *endOffset   = offset;
        }
        break;

    case QAccessible::WordBoundary: {
        QTextBoundaryFinder finder(QTextBoundaryFinder::Word, text);
        finder.setPosition(offset);

        // Move to the start of the current word (or the preceding word boundary).
        int start = finder.toPreviousBoundary();
        if (start < 0)
            start = 0;

        // Move to the end of the current word.
        finder.setPosition(start);
        int end = finder.toNextBoundary();
        if (end < 0)
            end = text.length();

        // If start == end (degenerate boundary), advance end.
        if (start == end && end < text.length())
            ++end;

        *startOffset = start;
        *endOffset   = end;
        break;
    }

    case QAccessible::SentenceBoundary: {
        QTextBoundaryFinder finder(QTextBoundaryFinder::Sentence, text);
        finder.setPosition(offset);
        int start = finder.toPreviousBoundary();
        if (start < 0) start = 0;
        finder.setPosition(start);
        int end = finder.toNextBoundary();
        if (end < 0) end = text.length();
        *startOffset = start;
        *endOffset   = end;
        break;
    }

    case QAccessible::LineBoundary:
    case QAccessible::ParagraphBoundary: {
        // Find the enclosing line in the full text.
        int lineStart = offset;
        while (lineStart > 0 && text.at(lineStart - 1) != QLatin1Char('\n'))
            --lineStart;
        int lineEnd = offset;
        while (lineEnd < text.length() && text.at(lineEnd) != QLatin1Char('\n'))
            ++lineEnd;
        *startOffset = lineStart;
        *endOffset   = lineEnd;
        break;
    }

    case QAccessible::NoBoundary:
    default:
        *startOffset = 0;
        *endOffset   = text.length();
        break;
    }
}

QString QEditorAccessible::textBeforeCursor(int offset,
                                            QAccessible::TextBoundaryType boundaryType,
                                            int *startOffset, int *endOffset) const
{
    const QString full = fullText();
    int s = 0, e = 0;
    const int adjustedOffset = qBound(0, offset - 1, full.length());
    boundaryOffsets(full, adjustedOffset, boundaryType, &s, &e);

    // Clamp so the result ends at 'offset'.
    if (e > offset) e = offset;
    if (s > e) s = e;

    *startOffset = s;
    *endOffset   = e;
    return full.mid(s, e - s);
}

QString QEditorAccessible::textAfterCursor(int offset,
                                           QAccessible::TextBoundaryType boundaryType,
                                           int *startOffset, int *endOffset) const
{
    const QString full = fullText();
    const int adjustedOffset = qBound(0, offset + 1, full.length());
    int s = 0, e = 0;
    boundaryOffsets(full, adjustedOffset, boundaryType, &s, &e);

    // Clamp so the result starts at 'offset'.
    if (s < offset) s = offset;
    if (e < s) e = s;

    *startOffset = s;
    *endOffset   = e;
    return full.mid(s, e - s);
}

QString QEditorAccessible::textAtOffset(int offset,
                                        QAccessible::TextBoundaryType boundaryType,
                                        int *startOffset, int *endOffset) const
{
    const QString full = fullText();
    int s = 0, e = 0;
    boundaryOffsets(full, offset, boundaryType, &s, &e);
    *startOffset = s;
    *endOffset   = e;
    return full.mid(s, e - s);
}

// ---------------------------------------------------------------------------
// Factory
// ---------------------------------------------------------------------------

QAccessibleInterface *QEditorAccessible::factory(const QString &classname, QObject *object)
{
    if (classname == QLatin1String("QEditor") && object && object->isWidgetType())
        return new QEditorAccessible(static_cast<QEditor *>(object));
    return nullptr;
}
