#ifndef adwaitatoolboxengine_h
#define adwaitatoolboxengine_h

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

#include "adwaitabaseengine.h"
#include "adwaitadatamap.h"
#include "adwaitawidgetstatedata.h"

namespace Adwaita
{

    //* QToolBox animation engine
    class ToolBoxEngine: public BaseEngine
    {

        Q_OBJECT

        public:

        //* constructor
        explicit ToolBoxEngine( QObject* parent ):
            BaseEngine( parent )
        {}

        //* destructor
        virtual ~ToolBoxEngine( void )
        {}

        //* enability
        virtual void setEnabled( bool value )
        {
            BaseEngine::setEnabled( value );
            _data.setEnabled( value );
        }

        //* duration
        virtual void setDuration( int value )
        {
            BaseEngine::setDuration( value );
            _data.setDuration( value );
        }

        //* register widget
        virtual bool registerWidget( QWidget* );

        //* true if widget hover state is changed
        virtual bool updateState( const QPaintDevice*, bool );

        //* true if widget is animated
        virtual bool isAnimated( const QPaintDevice* );

        //* animation opacity
        virtual qreal opacity( const QPaintDevice* object )
        { return isAnimated( object ) ? data( object ).data()->opacity(): AnimationData::OpacityInvalid; }

        public Q_SLOTS:

        //* remove widget from map
        virtual bool unregisterWidget( QObject* data )
        {

            if( !data ) return false;

            // reinterpret_cast is safe here since only the address is used to find
            // data in the map
            return _data.unregisterWidget( reinterpret_cast<QPaintDevice*>(data) );

        }

        protected:

        //* returns data associated to widget
        PaintDeviceDataMap<WidgetStateData>::Value data( const QPaintDevice* object )
        { return _data.find( object ).data(); }

        private:

        //* map
        PaintDeviceDataMap<WidgetStateData> _data;

    };

}

#endif
