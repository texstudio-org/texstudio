#ifndef adwaitatransitiondata_h
#define adwaitatransitiondata_h

//////////////////////////////////////////////////////////////////////////////
// adwaitatransitiondata.h
// data container for generic transitions
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

#include <QObject>
#include <QTime>
#include <QWidget>

namespace Adwaita
{

    //* generic data
    class TransitionData: public QObject
    {

        Q_OBJECT

        public:

        //* constructor
        TransitionData( QObject* parent, QWidget* target, int );

        //* destructor
        virtual ~TransitionData( void );

        //* enability
        virtual void setEnabled( bool value )
        { _enabled = value; }

        //* enability
        virtual bool enabled( void ) const
        { return _enabled; }

        //* duration
        virtual void setDuration( int duration )
        {
            if( _transition )
            { _transition.data()->setDuration( duration ); }
        }

        //* max render time
        void setMaxRenderTime( int value )
        { _maxRenderTime = value; }

        //* max renderTime
        const int& maxRenderTime( void ) const
        { return _maxRenderTime; }

        //* start clock
        void startClock( void )
        {
            if( _clock.isNull() ) _clock.start();
            else _clock.restart();
        }

        //* check if rendering is two slow
        bool slow( void ) const
        { return !( _clock.isNull() || _clock.elapsed() <= maxRenderTime() ); }

        protected Q_SLOTS:

        //* initialize animation
        virtual bool initializeAnimation( void ) = 0;

        //* animate
        virtual bool animate( void ) = 0;

        protected:

        //* returns true if one parent matches given class name
        inline bool hasParent( const QWidget*, const char* ) const;

        //* transition widget
        virtual const TransitionWidget::Pointer& transition( void ) const
        { return _transition; }

        //* used to avoid recursion when grabbing widgets
        void setRecursiveCheck( bool value )
        { _recursiveCheck = value; }

        //* used to avoid recursion when grabbing widgets
        bool recursiveCheck( void ) const
        { return _recursiveCheck; }

        private:

        //* enability
        bool _enabled = true;

        //* used to avoid recursion when grabbing widgets
        bool _recursiveCheck = false;

        //* timer used to detect slow rendering
        QTime _clock;

        //* max render time
        /*! used to detect slow rendering */
        int _maxRenderTime = 200;

        //* animation handling
        TransitionWidget::Pointer _transition;

    };

    //_____________________________________________________________________________________
    bool TransitionData::hasParent( const QWidget* widget, const char* className ) const
    {
        if( !widget ) return false;
        for( QWidget* parent = widget->parentWidget(); parent; parent = parent->parentWidget() )
        { if( parent->inherits( className ) ) return true; }

        return false;
    }

}

#endif
