/*************************************************************************
 * Copyright (C) 2014 by Hugo Pereira Da Costa <hugo.pereira@free.fr>    *
 *                                                                       *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the GNU General Public License as published by  *
 * the Free Software Foundation; either version 2 of the License, or     *
 * (at your option) any later version.                                   *
 *                                                                       *
 * This program is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 * GNU General Public License for more details.                          *
 *                                                                       *
 * You should have received a copy of the GNU General Public License     *
 * along with this program; if not, write to the                         *
 * Free Software Foundation, Inc.,                                       *
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .        *
 *************************************************************************/

//////////////////////////////////////////////////////////////////////////////
// adwaitatabbardata.cpp
// data container for QTabBar animations
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

#include "adwaitatabbardata.h"

#include <QHoverEvent>
#include <QTabBar>

namespace Adwaita
{

    //______________________________________________
    TabBarData::TabBarData( QObject* parent, QWidget* target, int duration ):
        AnimationData( parent, target )
    {

        _current._animation = new Animation( duration, this );
        setupAnimation( currentIndexAnimation(), "currentOpacity" );
        currentIndexAnimation().data()->setDirection( Animation::Forward );

        _previous._animation = new Animation( duration, this );
        setupAnimation( previousIndexAnimation(), "previousOpacity" );
        previousIndexAnimation().data()->setDirection( Animation::Backward );

    }

    //______________________________________________
    Animation::Pointer TabBarData::animation( const QPoint& position ) const
    {

        if( !enabled() ) return Animation::Pointer();

        const QTabBar* local( qobject_cast<const QTabBar*>( target().data() ) );
        if( !local ) return Animation::Pointer();

        int index( local->tabAt( position ) );
        if( index < 0 ) return Animation::Pointer();
        else if( index == currentIndex() ) return currentIndexAnimation();
        else if( index == previousIndex() ) return previousIndexAnimation();
        else return Animation::Pointer();

    }

    //______________________________________________
    bool TabBarData::updateState( const QPoint& position , bool hovered )
    {

        if( !enabled() ) return false;

        const QTabBar* local( qobject_cast<const QTabBar*>( target().data() ) );
        if( !local ) return false;

        int index( local->tabAt( position ) );
        if( index < 0 ) return false;

        if( hovered )
        {


            if( index != currentIndex() )
            {

                if( currentIndex() >= 0 )
                {
                    setPreviousIndex( currentIndex() );
                    setCurrentIndex( -1 );
                    previousIndexAnimation().data()->restart();
                }

                setCurrentIndex( index );
                currentIndexAnimation().data()->restart();
                return true;

            } else return false;

        } else if( index == currentIndex() ) {

            setPreviousIndex( currentIndex() );
            setCurrentIndex( -1 );
            previousIndexAnimation().data()->restart();
            return true;

        } else return false;

    }

    //______________________________________________
    qreal TabBarData::opacity( const QPoint& position ) const
    {

        if( !enabled() ) return OpacityInvalid;

        const QTabBar* local( qobject_cast<const QTabBar*>( target().data() ) );
        if( !local ) return OpacityInvalid;

        int index( local->tabAt( position ) );
        if( index < 0 ) return OpacityInvalid;
        else if( index == currentIndex() ) return currentOpacity();
        else if( index == previousIndex() ) return previousOpacity();
        else return OpacityInvalid;

    }


}
