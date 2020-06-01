//////////////////////////////////////////////////////////////////////////////
// adwaitastackedwidgetdata.cpp
// data container for QStackedWidget transition
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

#include "adwaitastackedwidgetdata.h"

namespace Adwaita
{

    //______________________________________________________
    StackedWidgetData::StackedWidgetData( QObject* parent, QStackedWidget* target, int duration ):
        TransitionData( parent, target, duration ),
        _target( target ),
        _index( target->currentIndex() )
    {

        // configure transition
        connect( _target.data(), SIGNAL(destroyed()), SLOT(targetDestroyed()) );
        connect( _target.data(), SIGNAL(currentChanged(int)), SLOT(animate()) );

        // disable focus
        transition().data()->setAttribute(Qt::WA_NoMousePropagation, true);
        transition().data()->setFlag(TransitionWidget::PaintOnWidget, true);

        setMaxRenderTime( 50 );

    }

    //___________________________________________________________________
    bool StackedWidgetData::initializeAnimation( void )
    {

        // check enability
        if( !( _target && _target.data()->isVisible() ) )
        { return false; }

        // check index
        if( _target.data()->currentIndex() == _index )
        { return false; }

        // do not animate if either index or currentIndex is not valid
        // but update _index none the less
        if( _target.data()->currentIndex() < 0 || _index < 0 )
        {
            _index = _target.data()->currentIndex();
            return false;
        }

        // get old widget (matching _index) and initialize transition
        if( QWidget *widget = _target.data()->widget( _index ) )
        {

            transition().data()->setOpacity( 0 );
            startClock();
            transition().data()->setGeometry( widget->geometry() );
            transition().data()->setStartPixmap( transition().data()->grab( widget ) );

            _index = _target.data()->currentIndex();
            return !slow();

        } else {

            _index = _target.data()->currentIndex();
            return false;

        }

    }

    //___________________________________________________________________
    bool StackedWidgetData::animate( void )
    {

        // check enability
        if( !enabled() ) return false;

        // initialize animation
        if( !initializeAnimation() ) return false;

        // show transition widget
        transition().data()->show();
        transition().data()->raise();
        transition().data()->animate();
        return true;

    }

    //___________________________________________________________________
    void StackedWidgetData::finishAnimation( void )
    {
        // disable updates on currentWidget
        if( _target && _target.data()->currentWidget() )
        { _target.data()->currentWidget()->setUpdatesEnabled( false ); }

        // hide transition
        transition().data()->hide();

        // reenable updates and repaint
        if( _target && _target.data()->currentWidget() )
        {
            _target.data()->currentWidget()->setUpdatesEnabled( true );
            _target.data()->currentWidget()->repaint();
        }

        // invalidate start widget
        transition().data()->resetStartPixmap();

    }

    //___________________________________________________________________
    void StackedWidgetData::targetDestroyed( void )
    {
        setEnabled( false );
        _target.clear();
    }

}
