//////////////////////////////////////////////////////////////////////////////
// adwaitatransitionwidget.cpp
// stores event filters and maps widgets to transitions for transitions
// -------------------
//
// Copyright (c) 2009 Hugo Pereira Da Costa <hugo.pereira@free.fr>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//////////////////////////////////////////////////////////////////////////////

#include "adwaitatransitionwidget.h"

#include <QPainter>
#include <QPaintEvent>
#include <QStyleOption>
#include <QTextStream>

namespace Adwaita
{

    //________________________________________________
    bool TransitionWidget::_paintEnabled = true;
    bool TransitionWidget::paintEnabled( void )
    { return _paintEnabled; }

    int TransitionWidget::_steps = 0;

    //________________________________________________
    TransitionWidget::TransitionWidget( QWidget* parent, int duration ):
        QWidget( parent ),
        _animation( new Animation( duration, this ) )
    {

        // background flags
        setAttribute( Qt::WA_NoSystemBackground );
        setAutoFillBackground( false );

        // setup animation
        _animation.data()->setStartValue( 0 );
        _animation.data()->setEndValue( 1.0 );
        _animation.data()->setTargetObject( this );
        _animation.data()->setPropertyName( "opacity" );

        // hide when animation is finished
        connect( _animation.data(), SIGNAL(finished()), SLOT(hide()) );

    }

    //________________________________________________
    QPixmap TransitionWidget::grab( QWidget* widget, QRect rect )
    {

        // change rect
        if( !rect.isValid() ) rect = widget->rect();
        if( !rect.isValid() ) return QPixmap();

        // initialize pixmap
        QPixmap out( rect.size() );
        out.fill( Qt::transparent );
        _paintEnabled = false;

        if( testFlag( GrabFromWindow ) )
        {

            rect = rect.translated( widget->mapTo( widget->window(), widget->rect().topLeft() ) );
            widget = widget->window();
            #if QT_VERSION < 0x050000
            out = QPixmap::grabWidget( widget, rect );
            #else
            out = widget->grab( rect );
            #endif

        } else {

            if( !testFlag( Transparent ) ) { grabBackground( out, widget, rect ); }
            grabWidget( out, widget, rect );

        }

        _paintEnabled = true;

        return out;

    }

    //________________________________________________
    bool TransitionWidget::event( QEvent* event )
    {
        switch( event->type() )
        {
            case QEvent::MouseButtonPress:
            case QEvent::MouseButtonRelease:
            case QEvent::KeyPress:
            case QEvent::KeyRelease:
            endAnimation();
            hide();
            event->ignore();
            return false;

            default: return QWidget::event( event );
        }

    }

    //________________________________________________
    void TransitionWidget::paintEvent( QPaintEvent* event )
    {

        // fully transparent case
        if( opacity() >= 1.0 && endPixmap().isNull() ) return;
        if( !_paintEnabled ) return;

        // get rect
        QRect rect = event->rect();
        if( !rect.isValid() ) rect = this->rect();

        // local pixmap
        bool paintOnWidget( testFlag( PaintOnWidget ) && !testFlag( Transparent ) );
        if( !paintOnWidget )
        {

            if( _currentPixmap.isNull() || _currentPixmap.size() != size() )
            { _currentPixmap = QPixmap( size() ); }

        }

        // fill
        _currentPixmap.fill( Qt::transparent );

        // copy local pixmap to current
        {

            QPainter p;

            // draw end pixmap first, provided that opacity is small enough
            if( opacity() >= 0.004 && !_endPixmap.isNull() )
            {

                // faded endPixmap if parent target is transparent and opacity is
                if( opacity() <= 0.996 && testFlag( Transparent ) )
                {

                    fade( _endPixmap, _currentPixmap, opacity(), rect );
                    p.begin( &_currentPixmap );
                    p.setClipRect( event->rect() );

                } else {

                    if( paintOnWidget ) p.begin( this );
                    else p.begin( &_currentPixmap );
                    p.setClipRect( event->rect() );
                    p.drawPixmap( QPoint(), _endPixmap );

                }

            } else {

                if( paintOnWidget ) p.begin( this );
                else p.begin( &_currentPixmap );
                p.setClipRect( event->rect() );

            }

            // draw fading start pixmap
            if( opacity() <= 0.996 && !_startPixmap.isNull() )
            {
                if( opacity() >= 0.004 )
                {

                    fade( _startPixmap, _localStartPixmap, 1.0-opacity(), rect );
                    p.drawPixmap( QPoint(), _localStartPixmap );

                } else p.drawPixmap( QPoint(), _startPixmap );

            }

            p.end();
        }

        // copy current pixmap on widget
        if( !paintOnWidget )
        {
            QPainter p( this );
            p.setClipRect( event->rect() );
            p.drawPixmap( QPoint(0,0), _currentPixmap );
            p.end();
        }
    }

    //________________________________________________
    void TransitionWidget::grabBackground( QPixmap& pixmap, QWidget* widget, QRect& rect ) const
    {
        if( !widget ) return;

        QWidgetList widgets;
        if( widget->autoFillBackground() )
        { widgets.append( widget ); }

        QWidget *parent(0);

        // get highest level parent
        for( parent = widget->parentWidget(); parent; parent = parent->parentWidget() )
        {

            if( !( parent->isVisible() && parent->rect().isValid() ) ) continue;

            // store in list
            widgets.append( parent );

            // stop at topLevel
            if( parent->isTopLevel() || parent->autoFillBackground() ) break;

        }

        if( !parent ) parent = widget;

        // painting
        QPainter p(&pixmap);
        p.setClipRect( rect );
        QBrush backgroundBrush = parent->palette().brush( parent->backgroundRole());
        if( backgroundBrush.style() == Qt::TexturePattern)
        {

            p.drawTiledPixmap( rect, backgroundBrush.texture(), widget->mapTo( parent, rect.topLeft() ) );

        } else {

            p.fillRect( pixmap.rect(), backgroundBrush );

        }

        if( parent->isTopLevel() && parent->testAttribute(Qt::WA_StyledBackground))
        {
            QStyleOption option;
            option.initFrom(parent);
            option.rect = rect;
            option.rect.translate( widget->mapTo( parent, rect.topLeft() ) );
            p.translate(-option.rect.topLeft());
            parent->style()->drawPrimitive ( QStyle::PE_Widget, &option, &p, parent );
            p.translate(option.rect.topLeft());
        }

        // draw all widgets in parent list
        // backward
        QPaintEvent event(rect);
        for( int i = widgets.size() - 1; i>=0; i-- )
        {
            QWidget* w = widgets.at(i);
            w->render( &p, -widget->mapTo( w, rect.topLeft() ), rect, 0 );
        }

        // end
        p.end();

    }

    //________________________________________________
    void TransitionWidget::grabWidget( QPixmap& pixmap, QWidget* widget, QRect& rect ) const
    { widget->render( &pixmap, pixmap.rect().topLeft(), rect, QWidget::DrawChildren ); }

    //________________________________________________
    void TransitionWidget::fade( const QPixmap& source, QPixmap& target, qreal opacity, const QRect& rect ) const
    {

        if( target.isNull() || target.size() != size() )
        { target = QPixmap( size() ); }

        // erase target
        target.fill( Qt::transparent );

        // check opacity
        if( opacity*255 < 1 ) return;

        QPainter p( &target );
        p.setClipRect( rect );

        // draw pixmap
        p.drawPixmap( QPoint(0,0), source );

        // opacity mask (0.996 corresponds to 254/255)
        if( opacity <= 0.996 )
        {
            p.setCompositionMode(QPainter::CompositionMode_DestinationIn);
            QColor color( Qt::black );
            color.setAlphaF( opacity );
            p.fillRect(rect, color );
        }

        p.end();
        return;
    }

}
