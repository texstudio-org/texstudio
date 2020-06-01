#ifndef adwaitaanimations_h
#define adwaitaanimations_h

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

#include "adwaitabusyindicatorengine.h"
#include "adwaitadialengine.h"
#include "adwaitaheaderviewengine.h"
#include "adwaitascrollbarengine.h"
#include "adwaitaspinboxengine.h"
#include "adwaitastackedwidgetengine.h"
#include "adwaitatabbarengine.h"
#include "adwaitatoolboxengine.h"
#include "adwaitawidgetstateengine.h"

#include <QObject>
#include <QList>

namespace Adwaita
{

    //* stores engines
    class Animations: public QObject
    {

        Q_OBJECT

        public:

        //* constructor
        explicit Animations( QObject* );

        //* destructor
        virtual ~Animations( void )
        {}

        //* register animations corresponding to given widget, depending on its type.
        void registerWidget( QWidget* widget ) const;

        /** unregister all animations associated to a widget */
        void unregisterWidget( QWidget* widget ) const;

        //* enability engine
        WidgetStateEngine& widgetEnabilityEngine( void ) const
        { return *_widgetEnabilityEngine; }

        //* abstractButton engine
        WidgetStateEngine& widgetStateEngine( void ) const
        { return *_widgetStateEngine; }

        //* editable combobox arrow hover engine
        WidgetStateEngine& comboBoxEngine( void ) const
        { return *_comboBoxEngine; }

        //! Tool buttons arrow hover engine
        WidgetStateEngine& toolButtonEngine( void ) const
        { return *_toolButtonEngine; }

        //! item view engine
        WidgetStateEngine& inputWidgetEngine( void ) const
        { return *_inputWidgetEngine; }

        //* busy indicator
        BusyIndicatorEngine& busyIndicatorEngine( void ) const
        { return *_busyIndicatorEngine; }

        //* header view engine
        HeaderViewEngine& headerViewEngine( void ) const
        { return *_headerViewEngine; }

        //* scrollbar engine
        ScrollBarEngine& scrollBarEngine( void ) const
        { return *_scrollBarEngine; }

        //* dial engine
        DialEngine& dialEngine( void ) const
        { return *_dialEngine; }

        //* spinbox engine
        SpinBoxEngine& spinBoxEngine( void ) const
        { return *_spinBoxEngine; }

        //* tabbar
        TabBarEngine& tabBarEngine( void ) const
        { return *_tabBarEngine; }

        //* toolbox
        ToolBoxEngine& toolBoxEngine( void ) const
        { return *_toolBoxEngine; }

        //* setup engines
        void setupEngines( void );

        protected Q_SLOTS:

        //* enregister engine
        void unregisterEngine( QObject* );
        private:

        //* register new engine
        void registerEngine( BaseEngine* engine );

        //* busy indicator
        BusyIndicatorEngine* _busyIndicatorEngine;

        //* headerview hover effect
        HeaderViewEngine* _headerViewEngine;

        //* widget enability engine
        WidgetStateEngine* _widgetEnabilityEngine;

        //* abstract button engine
        WidgetStateEngine* _widgetStateEngine;

        //* editable combobox arrow hover effect
        WidgetStateEngine* _comboBoxEngine;

        //! mennu toolbutton arrow hover effect
        WidgetStateEngine* _toolButtonEngine;

        //! item view engine
        WidgetStateEngine* _inputWidgetEngine;

        //* scrollbar engine
        ScrollBarEngine* _scrollBarEngine;

        //* dial engine
        DialEngine* _dialEngine;

        //* spinbox engine
        SpinBoxEngine* _spinBoxEngine;

        //* stacked widget engine
        StackedWidgetEngine* _stackedWidgetEngine;

        //* tabbar engine
        TabBarEngine* _tabBarEngine;

        //* toolbar engine
        ToolBoxEngine* _toolBoxEngine;

        //* keep list of existing engines
        QList< BaseEngine::Pointer > _engines;

    };

}

#endif
