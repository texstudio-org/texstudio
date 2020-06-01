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

#include "adwaitaspinboxdata.h"

namespace Adwaita
{

    //________________________________________________
    SpinBoxData::SpinBoxData( QObject* parent, QWidget* target, int duration ):
        AnimationData( parent, target )
    {
        _upArrowData._hoverAnimation = new Animation( duration, this );
        _downArrowData._hoverAnimation = new Animation( duration, this );
        _upArrowData._pressedAnimation = new Animation( duration, this );
        _downArrowData._pressedAnimation = new Animation( duration, this );
        setupAnimation( upArrowAnimation(), "upArrowOpacity" );
        setupAnimation( downArrowAnimation(), "downArrowOpacity" );
        setupAnimation( upArrowPressedAnimation(), "upArrowPressed" );
        setupAnimation( downArrowPressedAnimation(), "downArrowPressed" );
    }

    //______________________________________________
    bool SpinBoxData::Data::updateState(bool value, bool pressed)
    {
        bool change = false;
        if( _hoverState != value ) {

            _hoverState = value;
            _hoverAnimation.data()->setDirection( ( _hoverState ) ? Animation::Forward : Animation::Backward );
            if( !_hoverAnimation.data()->isRunning() ) _hoverAnimation.data()->start();
            change = true;

        }
        if( _pressedState != pressed ) {

            _pressedState = pressed;
            _pressedAnimation.data()->setDirection( ( _pressedState ) ? Animation::Forward : Animation::Backward );
            if( !_pressedAnimation.data()->isRunning() ) _pressedAnimation.data()->start();
            change = true;

        }
        return change;
    }

}
