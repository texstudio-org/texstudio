/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#include "minisplitter.h"

#include <stylehelper.h>

#include <QPaintEvent>
#include <QPainter>
#include <QSplitterHandle>


namespace Internal {

class MiniSplitterHandle : public QSplitterHandle
{
public:
    MiniSplitterHandle(Qt::Orientation orientation, QSplitter *parent)
            : QSplitterHandle(orientation, parent)
    {
        setMask(QRegion(contentsRect()));
        setAttribute(Qt::WA_MouseNoMask, true);
    }
    QSize sizeHint() const;
protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
};

} // namespace Internal

using namespace Internal;

QSize MiniSplitterHandle::sizeHint() const {
    // This is a workaround to force 1px wide splitter handles
    // Strictly, this is not needed with manhattanstyle and vertical splitters on any style,
    // but horizontal splitters on non-manhattanstyle yield large ~5px size hints resulting
    // in unwanted large splitters.
    return QSize(1, 1);
}

void MiniSplitterHandle::resizeEvent(QResizeEvent *event)
{
    if (orientation() == Qt::Horizontal)
        setContentsMargins(2, 0, 2, 0);
    else
        setContentsMargins(0, 2, 0, 2);
    setMask(QRegion(contentsRect()));
    QSplitterHandle::resizeEvent(event);
}

void MiniSplitterHandle::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(event->rect(), StyleHelper::borderColor());
}

QSplitterHandle *MiniSplitter::createHandle()
{
    return new MiniSplitterHandle(orientation(), this);
}

MiniSplitter::MiniSplitter(QWidget *parent)
    : QSplitter(parent)
{
    setHandleWidth(1);
    setChildrenCollapsible(false);
    setProperty("minisplitter", true);
}

MiniSplitter::MiniSplitter(Qt::Orientation orientation, QWidget *parent)
    : QSplitter(orientation, parent)
{
    setHandleWidth(1);
    setChildrenCollapsible(false);
    setProperty("minisplitter", true);
}
