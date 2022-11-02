/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact:  Qt Software Information (qt-info@nokia.com)
**
** Commercial Usage
**
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
**
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
**
**************************************************************************/

#ifndef Header_Animation
#define Header_Animation

#include <QtCore/QPointer>
#include <QtCore/QTime>
#include <QtCore/QBasicTimer>
#include <QStyle>
#include <QPainter>
#include <QWidget>

/* 
 * This is a set of helper classes to allow for widget animations in
 * the style. Its mostly taken from Vista style so it should be fully documented
 * there.
 *
 */
namespace Manhattan{
class Animation
{
public :
    Animation() : m_running(true) { }
    virtual ~Animation() { }
    QWidget * widget() const { return m_widget; }
    bool running() const { return m_running; }
    const QTime &startTime() const { return m_startTime; }
    void setRunning(bool val) { m_running = val; }
    void setWidget(QWidget *widget) { m_widget = widget; }
    void setStartTime(const QTime &startTime) { m_startTime = startTime; }
    virtual void paint(QPainter *painter, const QStyleOption *option);

protected:
    void drawBlendedImage(QPainter *painter, QRect rect, float value);
    QTime m_startTime;
    QPointer<QWidget> m_widget;
    QImage m_primaryImage;
    QImage m_secondaryImage;
    QImage m_tempImage;
    bool m_running;
};

// Handles state transition animations
class Transition : public Animation
{
public :
    Transition() : Animation(),m_duration(130) {}
    virtual ~Transition() {}
    void setDuration(int duration) { m_duration = duration; }
    void setStartImage(const QImage &image) { m_primaryImage = image; }
    void setEndImage(const QImage &image) { m_secondaryImage = image; }
    virtual void paint(QPainter *painter, const QStyleOption *option);
    int duration() const { return m_duration; }
    int m_duration; //set time in ms to complete a state transition
};

class StyleAnimator : public QObject
{
    Q_OBJECT

public:
    StyleAnimator(QObject *parent = nullptr) : QObject(parent) {}

    void timerEvent(QTimerEvent *);
    void startAnimation(Animation *);
    void stopAnimation(const QWidget *);
    Animation* widgetAnimation(const QWidget *) const;
    
private:
    QBasicTimer animationTimer;
    QList <Animation*> animations;
};
}
#endif // ANIMATION_H
