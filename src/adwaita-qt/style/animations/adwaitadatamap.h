#ifndef adwaitadatamap_h
#define adwaitadatamap_h

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

#include "adwaita.h"

#include <QObject>
#include <QMap>
#include <QPaintDevice>

namespace Adwaita
{

    //* data map
    /** it maps templatized data object to associated object */
    template< typename K, typename T > class BaseDataMap: public QMap< const K*, WeakPointer<T> >
    {

        public:

        using Key = const K*;
        using Value = WeakPointer<T>;

        //* constructor
        BaseDataMap( void ):
            QMap<Key, Value>(),
            _enabled( true ),
            _lastKey( NULL )
        {}

        //* destructor
        virtual ~BaseDataMap( void )
        {}

        //* insertion
        virtual typename QMap< Key, Value >::iterator insert( const Key& key, const Value& value, bool enabled = true )
        {
            if( value ) value.data()->setEnabled( enabled );
            return QMap< Key, Value >::insert( key, value );
        }

        //* find value
        Value find( Key key )
        {
            if( !( enabled() && key ) ) return Value();
            if( key == _lastKey ) return _lastValue;
            else {
                Value out;
                typename QMap<Key, Value>::iterator iter( QMap<Key, Value>::find( key ) );
                if( iter != QMap<Key, Value>::end() ) out = iter.value();
                _lastKey = key;
                _lastValue = out;
                return out;
            }
        }

        //* unregister widget
        bool unregisterWidget( Key key )
        {

            // check key
            if( !key ) return false;

            // clear last value if needed
            if( key == _lastKey )
            {

                if( _lastValue ) _lastValue.clear();
                _lastKey = NULL;

            }

            // find key in map
            typename QMap<Key, Value>::iterator iter( QMap<Key, Value>::find( key ) );
            if( iter == QMap<Key, Value>::end() ) return false;

            // delete value from map if found
            if( iter.value() ) iter.value().data()->deleteLater();
            QMap<Key, Value>::erase( iter );

            return true;

        }

        //* maxFrame
        void setEnabled( bool enabled )
        {
            _enabled = enabled;
            foreach( const Value& value, *this )
            { if( value ) value.data()->setEnabled( enabled ); }
        }

        //* enability
        bool enabled( void ) const
        { return _enabled; }

        //* duration
        void setDuration( int duration ) const
        {
            foreach( const Value& value, *this )
            { if( value ) value.data()->setDuration( duration ); }
        }

        private:

        //* enability
        bool _enabled;

        //* last key
        Key _lastKey;

        //* last value
        Value _lastValue;

    };

    //* standard data map, using QObject as a key
    template< typename T > class DataMap: public BaseDataMap< QObject, T >
    {

        public:

        //* constructor
        DataMap( void )
        {}

        //* destructor
        virtual ~DataMap( void )
        {}

    };

    //* QPaintDevice based dataMap
    template< typename T > class PaintDeviceDataMap: public BaseDataMap< QPaintDevice, T >
    {

        public:

        //* constructor
        PaintDeviceDataMap( void )
        {}

        //* destructor
        virtual ~PaintDeviceDataMap( void )
        {}

    };

}

#endif
