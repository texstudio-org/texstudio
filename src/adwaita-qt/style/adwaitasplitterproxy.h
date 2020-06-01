#ifndef adwaitasplitterproxy_h
#define adwaitasplitterproxy_h

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
#include "adwaitaaddeventfilter.h"

#include <QEvent>
#include <QHoverEvent>
#include <QMainWindow>
#include <QMap>
#include <QMouseEvent>
#include <QSplitterHandle>
#include <QWidget>

namespace Adwaita
{

    class SplitterProxy;

    //* factory
    class SplitterFactory: public QObject
    {

        Q_OBJECT

        public:

        //* constructor
        explicit SplitterFactory( QObject* parent ):
            QObject( parent ),
            _enabled( false )
            {}

        //* destructor
        virtual ~SplitterFactory( void )
        {}

        //* enabled state
        void setEnabled( bool );

        //* register widget
        bool registerWidget( QWidget* );

        //* unregister widget
        void unregisterWidget( QWidget* );

        private:

        //* enabled state
        bool _enabled;

        //* needed to block ChildAdded events when creating proxy
        AddEventFilter _addEventFilter;

        //* pointer to SplitterProxy
        using SplitterProxyPointer = WeakPointer<SplitterProxy>;

        //* registered widgets
        using WidgetMap = QMap<QWidget*, SplitterProxyPointer >;
        WidgetMap _widgets;

    };

    //* splitter 'proxy' widget, with extended hit area
    class SplitterProxy : public QWidget
    {

        Q_OBJECT

        public:

        //* constructor
        explicit SplitterProxy( QWidget*, bool = false );

        //* destructor
        virtual ~SplitterProxy( void );

        //* event filter
        virtual bool eventFilter( QObject*, QEvent* );

        //* enable state
        void setEnabled( bool );

        //* enable state
        bool enabled( void ) const
        { return _enabled; }

        protected:

        //* event handler
        virtual bool event( QEvent* );

        protected:

        //* reset 'true' splitter widget
        void clearSplitter( void );

        //* keep track of 'true' splitter widget
        void setSplitter( QWidget* );

        private:

        //* enabled state
        bool _enabled;

        //* splitter object
        WeakPointer<QWidget> _splitter;

        //* hook
        QPoint _hook;

        //* timer id
        int _timerId;

    };

}

#endif
