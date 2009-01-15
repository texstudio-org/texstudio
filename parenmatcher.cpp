/****************************************************************************
**
** Copyright (C) 1992-2006 Trolltech AS. All rights reserved.
**
** This file is part of the QSA of the Qt Toolkit.
**
** For QSA Commercial License Holders (non-open source):
** 
** Licensees holding a valid Qt Script for Applications (QSA) License Agreement
** may use this file in accordance with the rights, responsibilities and
** obligations contained therein.  Please consult your licensing agreement or
** contact sales@trolltech.com if any conditions of the Licensing Agreement are
** not clear to you.
** 
** Further information about QSA licensing is available at:
** http://www.trolltech.com/products/qsa/licensing.html or by contacting
** info@trolltech.com.
** 
** 
** For Open Source Edition:  
** 
** This file may be used under the terms of the GNU General Public License
** version 2 as published by the Free Software Foundation and appearing in the
** file LICENSE.GPL included in the packaging of this file.  Please review the
** following information to ensure GNU General Public Licensing requirements
** will be met:  http://www.trolltech.com/products/qt/opensource.html 
** 
** If you are unsure which license is appropriate for your use, please review
** the following information:
** http://www.trolltech.com/products/qsa/licensing.html or contact the 
** sales department at sales@trolltech.com.

**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#include "parenmatcher.h"
#include <QSyntaxHighlighter>
#include "blockdata.h"
#include "latexeditor.h"

#include <QTextEdit>
#include <QAbstractTextDocumentLayout>
#include <QDebug>

ParenMatcher::MatchType checkOpenParenthesis(QTextCursor *cursor, QChar c)
{
    BlockData *ud = BlockData::data(cursor->block());
    if (!ud)
        return ParenMatcher::NoMatch;

    QList<Parenthesis> parenList = ud->parentheses;
    Parenthesis openParen, closedParen;
    QTextBlock closedParenParag = cursor->block();

    const int cursorPos = cursor->position() - closedParenParag.position();
    int i = 0;
    int ignore = 0;
    bool foundOpen = false;
    for (;;) {
        if (!foundOpen) {
            if (i >= parenList.count())
                return ParenMatcher::NoMatch;
            openParen = parenList.at(i);
            if (openParen.pos != cursorPos) {
                ++i;
                continue;
            } else {
                foundOpen = true;
                ++i;
            }
        }

        if (i >= parenList.count()) {
            for (;;) {
                closedParenParag = closedParenParag.next();
                if (!closedParenParag.isValid())
                    return ParenMatcher::NoMatch;
                if (BlockData::data(closedParenParag) &&
                    !BlockData::data(closedParenParag)->parentheses.isEmpty()) {
                    parenList = BlockData::data(closedParenParag)->parentheses;
                    break;
                }
            }
            i = 0;
        }

        closedParen = parenList.at(i);
        if (closedParen.type == Parenthesis::Open) {
            ignore++;
            ++i;
            continue;
        } else {
            if (ignore > 0) {
                ignore--;
                ++i;
                continue;
            }

            cursor->clearSelection();
            cursor->setPosition(closedParenParag.position() + closedParen.pos + 1, QTextCursor::KeepAnchor);

            if (c == QLatin1Char('{') && closedParen.chr != QLatin1Char('}'))
                return ParenMatcher::Mismatch;

            return ParenMatcher::Match;
        }
    }
}

ParenMatcher::MatchType checkClosedParenthesis(QTextCursor *cursor, QChar c)
{
    if (!BlockData::data(cursor->block()))
        return ParenMatcher::NoMatch;
    QList<Parenthesis> parenList = BlockData::data(cursor->block())->parentheses;
    Parenthesis openParen, closedParen;
    QTextBlock openParenParag = cursor->block();

    const int cursorPos = cursor->position() - openParenParag.position();
    int i = parenList.count() - 1;
    int ignore = 0;
    bool foundClosed = false;
    for (;;) {
        if (!foundClosed) {
            if (i < 0)
                return ParenMatcher::NoMatch;
            closedParen = parenList.at(i);
            if (closedParen.pos != cursorPos - 1) {
                --i;
                continue;
            } else {
                foundClosed = true;
                --i;
            }
        }

        if (i < 0) {
            for (;;) {
                openParenParag = openParenParag.previous();
                if (!openParenParag.isValid())
                    return ParenMatcher::NoMatch;

                if (BlockData::data(openParenParag) &&
                    !BlockData::data(openParenParag)->parentheses.isEmpty()) {
                    parenList = BlockData::data(openParenParag)->parentheses;
                    break;
                }
            }
            i = parenList.count() - 1;
        }

        openParen = parenList.at(i);
        if (openParen.type == Parenthesis::Closed) {
            ignore++;
            --i;
            continue;
        } else {
            if (ignore > 0) {
                ignore--;
                --i;
                continue;
            }

            cursor->clearSelection();
            cursor->setPosition(openParenParag.position() + openParen.pos, QTextCursor::KeepAnchor);

            if ( c == '}' && openParen.chr != '{' )
                return ParenMatcher::Mismatch;

            return ParenMatcher::Match;
        }
    }
}

static QChar charFromCursor(QTextCursor cursor, QTextCursor::MoveOperation op)
{
    cursor.clearSelection();
    if (!cursor.movePosition(op, QTextCursor::KeepAnchor))
        return QChar();
    if (!cursor.hasSelection())
        return QChar();
    return cursor.selectedText().at(0);
}

ParenMatcher::MatchType ParenMatcher::match(QTextCursor *cursor)
{
    cursor->clearSelection();

    QChar leftChar = charFromCursor(*cursor, QTextCursor::PreviousCharacter);
    QChar rightChar = charFromCursor(*cursor, QTextCursor::NextCharacter);
    if (rightChar == QLatin1Char('{')) {
        return checkOpenParenthesis(cursor, rightChar);
    } else if (leftChar == QLatin1Char('}')) {
        return checkClosedParenthesis(cursor, leftChar);
    }
    return NoMatch;
}

ParenMatcher::ParenMatcher(QObject *parent)
    : QObject(parent)
{
    matchFormat.setBackground(QColor("#FFFF99"));
    matchFormat.setFontWeight(QFont::Bold);
    matchFormat.setProperty(ParenthesisMatcherPropertyId, true);
    mismatchFormat.setBackground(Qt::magenta);
    mismatchFormat.setProperty(ParenthesisMatcherPropertyId, true);
}

void ParenMatcher::matchFromSender()
{
    QTextEdit *edit = qobject_cast<QTextEdit *>(sender());
    if (!edit)
        return;

    int rehighlightStart = currentMatch.selectionStart();
    int rehighlightEnd = currentMatch.selectionEnd();
    if (rehighlightStart != rehighlightEnd) {
        QTextBlock block = edit->document()->findBlock(rehighlightStart);
        while (block.isValid() && block.position() < rehighlightEnd) {
            if (BlockData *d = BlockData::data(block)) {
                d->parenthesisMatchStart = -1;
                d->parenthesisMatchEnd = -1;
                d->parenthesisMatchingFormat = QTextCharFormat();

                LatexEditor::clearMarkerFormat(block, ParenthesisMatcherPropertyId);
            }
            block = block.next();
        }

    }

    currentMatch = edit->textCursor();
    MatchType matchType = match(&currentMatch);
    if (currentMatch.hasSelection()) {
        rehighlightStart = qMin(rehighlightStart, currentMatch.selectionStart());
        rehighlightEnd = qMax(rehighlightEnd, currentMatch.selectionEnd());

        const int startPos = currentMatch.selectionStart();
        const int endPos = currentMatch.selectionEnd();
        QTextBlock block = edit->document()->findBlock(startPos);
        while (block.isValid() && block.position() < endPos) {
            BlockData *d = BlockData::data(block);
            if (!d) {
                d = new BlockData;
                d->setToBlock(block);
            }
            d->parenthesisMatchStart = qMax(0, startPos - block.position());
            d->parenthesisMatchEnd = qMin(block.length(), endPos - block.position());
            if (matchType == Match)
                d->parenthesisMatchingFormat = matchFormat;
            else if (matchType == Mismatch)
                d->parenthesisMatchingFormat = mismatchFormat;

            QTextLayout *layout = block.layout();
            QList<QTextLayout::FormatRange> formats = layout->additionalFormats();
            QTextLayout::FormatRange r;
            r.start = d->parenthesisMatchStart;
            r.length = d->parenthesisMatchEnd;
            r.format = d->parenthesisMatchingFormat;
            formats.append(r);
            layout->setAdditionalFormats(formats);

            block = block.next();
        }
    }

    if (rehighlightStart != rehighlightEnd)
        edit->document()->markContentsDirty(rehighlightStart, rehighlightEnd-rehighlightStart);
}


