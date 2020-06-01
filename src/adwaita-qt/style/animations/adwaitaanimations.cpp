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

#include "adwaitaanimations.h"

#include <QAbstractItemView>
#include <QComboBox>
#include <QCheckBox>
#include <QDial>
#include <QGroupBox>
#include <QHeaderView>
#include <QLineEdit>
#include <QProgressBar>
#include <QRadioButton>
#include <QScrollBar>
#include <QSpinBox>
#include <QTextEdit>
#include <QToolBox>
#include <QToolButton>

namespace Adwaita
{

    //____________________________________________________________
    Animations::Animations( QObject* parent ):
        QObject( parent )
    {
        _widgetEnabilityEngine = new WidgetStateEngine( this );
        _busyIndicatorEngine = new BusyIndicatorEngine( this );
        _comboBoxEngine = new WidgetStateEngine( this );
        _toolButtonEngine = new WidgetStateEngine( this );
        _spinBoxEngine = new SpinBoxEngine( this );
        _toolBoxEngine = new ToolBoxEngine( this );

        registerEngine( _headerViewEngine = new HeaderViewEngine( this ) );
        registerEngine( _widgetStateEngine = new WidgetStateEngine( this ) );
        registerEngine( _inputWidgetEngine = new WidgetStateEngine( this ) );
        registerEngine( _scrollBarEngine = new ScrollBarEngine( this ) );
        registerEngine( _stackedWidgetEngine = new StackedWidgetEngine( this ) );
        registerEngine( _tabBarEngine = new TabBarEngine( this ) );
        registerEngine( _dialEngine = new DialEngine( this ) );

    }

    //____________________________________________________________
    void Animations::setupEngines( void )
    {

        // animation steps
        AnimationData::setSteps( Adwaita::Config::AnimationSteps );

        bool animationsEnabled( Adwaita::Config::AnimationsEnabled );
        int animationsDuration( Adwaita::Config::AnimationsDuration );

        _widgetEnabilityEngine->setEnabled( animationsEnabled );
        _comboBoxEngine->setEnabled( animationsEnabled );
        _toolButtonEngine->setEnabled( animationsEnabled );
        _spinBoxEngine->setEnabled( animationsEnabled );
        _toolBoxEngine->setEnabled( animationsEnabled );

        _widgetEnabilityEngine->setDuration( animationsDuration );
        _comboBoxEngine->setDuration( animationsDuration );
        _toolButtonEngine->setDuration( animationsDuration );
        _spinBoxEngine->setDuration( animationsDuration );
        _stackedWidgetEngine->setDuration( animationsDuration );
        _toolBoxEngine->setDuration( animationsDuration );

        // registered engines
        foreach( const BaseEngine::Pointer& engine, _engines )
        {
            engine.data()->setEnabled( animationsEnabled );
            engine.data()->setDuration( animationsDuration );
        }

        // stacked widget transition has an extra flag for animations
        _stackedWidgetEngine->setEnabled( animationsEnabled && Adwaita::Config::StackedWidgetTransitionsEnabled );

        // busy indicator
        _busyIndicatorEngine->setEnabled( Adwaita::Config::ProgressBarAnimated );
        _busyIndicatorEngine->setDuration( Adwaita::Config::ProgressBarBusyStepDuration );

    }

    //____________________________________________________________
    void Animations::registerWidget( QWidget* widget ) const
    {

        if( !widget ) return;

        // check against noAnimations propery
        QVariant propertyValue( widget->property( PropertyNames::noAnimations ) );
        if( propertyValue.isValid() && propertyValue.toBool() ) return;

        // all widgets are registered to the enability engine.
        _widgetEnabilityEngine->registerWidget( widget, AnimationEnable );

        // install animation timers
        // for optimization, one should put with most used widgets here first

        // buttons
        if( qobject_cast<QToolButton*>(widget) )
        {

            _toolButtonEngine->registerWidget( widget, AnimationHover|AnimationPressed );
            _widgetStateEngine->registerWidget( widget, AnimationHover|AnimationPressed );

        } else if( qobject_cast<QCheckBox*>(widget) || qobject_cast<QRadioButton*>(widget) ) {

            _widgetStateEngine->registerWidget( widget, AnimationHover|AnimationFocus|AnimationPressed );

        } else if( qobject_cast<QAbstractButton*>(widget) ) {

            // register to toolbox engine if needed
            if( qobject_cast<QToolBox*>( widget->parent() ) )
            { _toolBoxEngine->registerWidget( widget ); }

            _widgetStateEngine->registerWidget( widget, AnimationHover|AnimationPressed );

        }

        // groupboxes
        else if( QGroupBox* groupBox = qobject_cast<QGroupBox*>( widget ) )
        {
            if( groupBox->isCheckable() )
            { _widgetStateEngine->registerWidget( widget, AnimationHover|AnimationFocus ); }
        }

        // sliders
        else if( qobject_cast<QScrollBar*>( widget ) ) { _scrollBarEngine->registerWidget( widget, AnimationHover|AnimationFocus ); }
        else if( qobject_cast<QSlider*>( widget ) ) { _widgetStateEngine->registerWidget( widget, AnimationHover|AnimationFocus ); }
        else if( qobject_cast<QDial*>( widget ) ) { _dialEngine->registerWidget( widget, AnimationHover|AnimationFocus ); }

        // progress bar
        else if( qobject_cast<QProgressBar*>( widget ) ) { _busyIndicatorEngine->registerWidget( widget ); }

        // combo box
        else if( qobject_cast<QComboBox*>( widget ) ) {
            _comboBoxEngine->registerWidget( widget, AnimationHover|AnimationPressed );
            _inputWidgetEngine->registerWidget( widget, AnimationHover|AnimationFocus|AnimationPressed );
        }

        // spinbox
        else if( qobject_cast<QAbstractSpinBox*>( widget ) ) {
            _spinBoxEngine->registerWidget( widget );
            _inputWidgetEngine->registerWidget( widget, AnimationHover|AnimationFocus|AnimationPressed );
        }

        // editors
        else if( qobject_cast<QLineEdit*>( widget ) ) { _inputWidgetEngine->registerWidget( widget, AnimationHover|AnimationFocus ); }
        else if( qobject_cast<QTextEdit*>( widget ) ) { _inputWidgetEngine->registerWidget( widget, AnimationHover|AnimationFocus ); }
        else if( widget->inherits( "KTextEditor::View" ) ) { _inputWidgetEngine->registerWidget( widget, AnimationHover|AnimationFocus ); }

        // header views
        // need to come before abstract item view, otherwise is skipped
        else if( qobject_cast<QHeaderView*>( widget ) ) { _headerViewEngine->registerWidget( widget ); }

        // lists
        else if( qobject_cast<QAbstractItemView*>( widget ) )
        { _inputWidgetEngine->registerWidget( widget, AnimationHover|AnimationFocus ); }

        // tabbar
        else if( qobject_cast<QTabBar*>( widget ) ) { _tabBarEngine->registerWidget( widget ); }

        // scrollarea
        else if( QAbstractScrollArea* scrollArea = qobject_cast<QAbstractScrollArea*>( widget ) ) {

            if( scrollArea->frameShadow() == QFrame::Sunken && (widget->focusPolicy()&Qt::StrongFocus) )
            { _inputWidgetEngine->registerWidget( widget, AnimationHover|AnimationFocus ); }

        }

        // stacked widgets
        if( QStackedWidget* stack = qobject_cast<QStackedWidget*>( widget ) )
        { _stackedWidgetEngine->registerWidget( stack ); }

        return;

    }

    //____________________________________________________________
    void Animations::unregisterWidget( QWidget* widget ) const
    {

        if( !widget ) return;

        _widgetEnabilityEngine->unregisterWidget( widget );
        _spinBoxEngine->unregisterWidget( widget );
        _comboBoxEngine->unregisterWidget( widget );
        _busyIndicatorEngine->registerWidget( widget );

        // the following allows some optimization of widget unregistration
        // it assumes that a widget can be registered atmost in one of the
        // engines stored in the list.
        foreach( const BaseEngine::Pointer& engine, _engines )
        { if( engine && engine.data()->unregisterWidget( widget ) ) break; }

    }

    //_______________________________________________________________
    void Animations::unregisterEngine( QObject* object )
    {
        int index( _engines.indexOf( qobject_cast<BaseEngine*>(object) ) );
        if( index >= 0 ) _engines.removeAt( index );
    }

    //_______________________________________________________________
    void Animations::registerEngine( BaseEngine* engine )
    {
        _engines.append( engine );
        connect( engine, SIGNAL(destroyed(QObject*)), this, SLOT(unregisterEngine(QObject*)) );
    }

}
