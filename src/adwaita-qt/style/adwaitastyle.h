/*************************************************************************
 * Copyright (C) 2014 by Hugo Pereira Da Costa <hugo.pereira@free.fr>    *
 * Copyright (C) 2014-2018 Martin Bříza <m@rtinbriza.cz>                 *
 * Copyright (C) 2019 Jan Grulich <jgrulich@redhat.com>                  *
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

#ifndef Header_Adwaita_Style
#define Header_Adwaita_Style

#include "adwaita.h"
#include "config-adwaita.h"

#if ADWAITA_USE_KDE4
#include "kstylekde4compat.h"
#endif

#include <QAbstractItemView>
#include <QAbstractScrollArea>

#include <QCommonStyle>
#include <QDockWidget>
#include <QHash>
#include <QIcon>
#include <QMdiSubWindow>
#include <QStyleOption>
#include <QWidget>

#if QT_VERSION >= 0x050000
#include <QCommandLinkButton>
#endif

namespace AdwaitaPrivate
{
class TabBarData;
}

namespace Adwaita
{
class Animations;
class Helper;
class Mnemonics;
class SplitterFactory;
class WidgetExplorer;
class WindowManager;

//* convenience typedef for base class
#if ADWAITA_USE_KDE4
using ParentStyleClass = KStyleKDE4Compat;
#else
using ParentStyleClass = QCommonStyle;
#endif

//* base class for adwaita style
/** it is responsible to draw all the primitives to be displayed on screen, on request from Qt paint engine */
class Style : public ParentStyleClass
{
    Q_OBJECT

    /* this tells kde applications that custom style elements are supported, using the kstyle mechanism */
    Q_CLASSINFO("X-KDE-CustomElements", "true")

public:
    //* constructor
    explicit Style(bool dark);

    //* destructor
    virtual ~Style(void);

    //* needed to avoid warnings at compilation time
    using ParentStyleClass::polish;
    using ParentStyleClass::unpolish;

    //* widget polishing
    virtual void polish(QWidget *widget);

    //* widget unpolishing
    virtual void unpolish(QWidget *widget);

    //* palette polishing
    virtual void polish(QPalette &palette);

    virtual QPalette standardPalette() const;

    //* polish scrollarea
    void polishScrollArea(QAbstractScrollArea *scrollArea);

    //* pixel metrics
    virtual int pixelMetric(PixelMetric metric, const QStyleOption *option = nullptr, const QWidget *widget = nullptr) const;

    //* style hints
    virtual int styleHint(StyleHint hint, const QStyleOption *option = nullptr, const QWidget *widget = nullptr, QStyleHintReturn *returnData = nullptr) const;

    //* returns rect corresponding to one widget's subelement
    virtual QRect subElementRect(SubElement element, const QStyleOption *option, const QWidget *widget) const;

    //* returns rect corresponding to one widget's subcontrol
    virtual QRect subControlRect(ComplexControl element, const QStyleOptionComplex *option, SubControl subControl, const QWidget *widget) const;

    //* returns size matching contents
    QSize sizeFromContents(ContentsType element, const QStyleOption *option, const QSize &size, const QWidget *widget) const;

    //* returns which subcontrol given QPoint corresponds to
    SubControl hitTestComplexControl(ComplexControl control, const QStyleOptionComplex *option , const QPoint &point, const QWidget *widget) const;

    //* primitives
    void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const;

    //* controls
    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const;

    //* complex controls
    void drawComplexControl(ComplexControl element, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget) const;

    //* generic text rendering
    virtual void drawItemText(QPainter *painter, const QRect &rect, int alignment, const QPalette &palette, bool enabled,
                              const QString &text, QPalette::ColorRole textRole = QPalette::NoRole) const;

    //*@name event filters
    //@{

    virtual bool eventFilter(QObject *object, QEvent *event);
    bool eventFilterScrollArea(QWidget *widget, QEvent *event);
    bool eventFilterComboBoxContainer(QWidget *widget, QEvent *event);
    bool eventFilterDockWidget(QDockWidget *dockWidget, QEvent *event);
    bool eventFilterMdiSubWindow(QMdiSubWindow *subWindow, QEvent *event);

#if QT_VERSION >= 0x050000
    bool eventFilterCommandLinkButton(QCommandLinkButton *button, QEvent *event);
#endif

    //* install event filter to object, in a unique way
    void addEventFilter(QObject *object)
    {
        object->removeEventFilter(this);
        object->installEventFilter(this);
    }

    //@}

protected Q_SLOTS:

    //* update configuration
    void configurationChanged(void);

    //* standard icons
    virtual QIcon standardIconImplementation(StandardPixmap standardPixmap, const QStyleOption *option, const QWidget *widget) const;

protected:

    //* standard icons
    virtual QIcon standardIcon(StandardPixmap pixmap, const QStyleOption *option = nullptr, const QWidget *widget = nullptr) const
    {
        return standardIconImplementation(pixmap, option, widget);
    }

    //* load configuration
    void loadConfiguration();

    //*@name subelementRect specialized functions
    //@{

    //* default implementation. Does not change anything
    QRect defaultSubElementRect(const QStyleOption *option, const QWidget *widget) const
    {
        Q_UNUSED(widget)
        return option->rect;
    }

    QRect pushButtonContentsRect(const QStyleOption *option, const QWidget *widget) const;
    QRect pushButtonFocusRect(const QStyleOption *option, const QWidget *widget) const;
    QRect checkBoxContentsRect(const QStyleOption *option, const QWidget *widget) const;
    QRect checkBoxIndicatorRect(const QStyleOption *option, const QWidget *widget) const;
    QRect checkBoxFocusRect(const QStyleOption *option, const QWidget *widget) const;
    QRect lineEditContentsRect(const QStyleOption *option, const QWidget *widget) const;
    QRect progressBarGrooveRect(const QStyleOption *option, const QWidget *widget) const;
    QRect progressBarContentsRect(const QStyleOption *option, const QWidget *widget) const;
    QRect progressBarLabelRect(const QStyleOption *option, const QWidget *widget) const;
    QRect headerArrowRect(const QStyleOption *option, const QWidget *widget) const;
    QRect headerLabelRect(const QStyleOption *option, const QWidget *widget) const;
    QRect sliderFocusRect(const QStyleOption *option, const QWidget *widget) const;
    QRect tabBarTabLeftButtonRect(const QStyleOption *option, const QWidget *widget) const;
    QRect tabBarTabRightButtonRect(const QStyleOption *option, const QWidget *widget) const;
    QRect tabWidgetTabBarRect(const QStyleOption *option, const QWidget *widget) const;
    QRect tabWidgetTabContentsRect(const QStyleOption *option, const QWidget *widget) const;
    QRect tabWidgetTabPaneRect(const QStyleOption *option, const QWidget *widget) const;
    QRect tabWidgetCornerRect(SubElement element, const QStyleOption *option, const QWidget *widget) const;
    QRect toolBoxTabContentsRect(const QStyleOption *option, const QWidget *widget) const;
    QRect genericLayoutItemRect(const QStyleOption *option, const QWidget *widget) const;

    //@}option

    //*@name subcontrol Rect specialized functions
    //@{

    QRect groupBoxSubControlRect(const QStyleOptionComplex *option, SubControl subControl, const QWidget *widget) const;
    QRect toolButtonSubControlRect(const QStyleOptionComplex *option, SubControl subControl, const QWidget *widget) const;
    QRect comboBoxSubControlRect(const QStyleOptionComplex *option, SubControl subControl, const QWidget *widget) const;
    QRect spinBoxSubControlRect(const QStyleOptionComplex *option, SubControl subControl, const QWidget *widget) const;
    QRect scrollBarInternalSubControlRect(const QStyleOptionComplex *option, SubControl subControl) const;
    QRect scrollBarSubControlRect(const QStyleOptionComplex *option, SubControl subControl, const QWidget *widget) const;
    QRect dialSubControlRect(const QStyleOptionComplex *option, SubControl subControl, const QWidget *widget) const;
    QRect sliderSubControlRect(const QStyleOptionComplex *option, SubControl subControl, const QWidget *widget) const;

    //@}

    //*@name sizeFromContents
    //@{
    QSize defaultSizeFromContents(const QStyleOption *option, const QSize &size, const QWidget *widget) const
    {
        Q_UNUSED(option)
        Q_UNUSED(widget)
        return size;
    }

    QSize checkBoxSizeFromContents(const QStyleOption *option, const QSize &size, const QWidget *widget) const;
    QSize lineEditSizeFromContents(const QStyleOption *option, const QSize &size, const QWidget *widget) const;
    QSize comboBoxSizeFromContents(const QStyleOption *option, const QSize &size, const QWidget *widget) const;
    QSize spinBoxSizeFromContents(const QStyleOption *option, const QSize &size, const QWidget *widget) const;
    QSize sliderSizeFromContents(const QStyleOption *option, const QSize &size, const QWidget *widget) const;
    QSize pushButtonSizeFromContents(const QStyleOption *option, const QSize &size, const QWidget *widget) const;
    QSize toolButtonSizeFromContents(const QStyleOption *option, const QSize &size, const QWidget *widget) const;
    QSize menuBarItemSizeFromContents(const QStyleOption *option, const QSize &size, const QWidget *widget) const;
    QSize menuItemSizeFromContents(const QStyleOption *option, const QSize &size, const QWidget *widget) const;
    QSize progressBarSizeFromContents(const QStyleOption *option, const QSize &size, const QWidget *widget) const;
    QSize tabWidgetSizeFromContents(const QStyleOption *option, const QSize &size, const QWidget *widget) const;
    QSize tabBarTabSizeFromContents(const QStyleOption *option, const QSize &size, const QWidget *widget) const;
    QSize headerSectionSizeFromContents(const QStyleOption *option, const QSize &size, const QWidget *widget) const;
    QSize itemViewItemSizeFromContents(const QStyleOption *option, const QSize &size, const QWidget *widget) const;

    //@}

    //*@name primitives specialized functions
    //@{

    bool emptyPrimitive(const QStyleOption *option, QPainter *painter, const QWidget *widget) const
    {
        Q_UNUSED(option)
        Q_UNUSED(painter)
        Q_UNUSED(widget)
        return true;
    }

    bool drawFramePrimitive(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    bool drawFrameLineEditPrimitive(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    bool drawFrameFocusRectPrimitive(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    bool drawFrameMenuPrimitive(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    bool drawFrameGroupBoxPrimitive(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    bool drawFrameTabWidgetPrimitive(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    bool drawFrameTabBarBasePrimitive(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    bool drawFrameWindowPrimitive(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;

    bool drawIndicatorArrowUpPrimitive(const QStyleOption *option, QPainter *painter, const QWidget *widget) const
    {
        return drawIndicatorArrowPrimitive(ArrowUp, option, painter, widget);
    }

    bool drawIndicatorArrowDownPrimitive(const QStyleOption *option, QPainter *painter, const QWidget *widget) const
    {
        return drawIndicatorArrowPrimitive(ArrowDown, option, painter, widget);
    }

    bool drawIndicatorArrowLeftPrimitive(const QStyleOption *option, QPainter *painter, const QWidget *widget) const
    {
        return drawIndicatorArrowPrimitive(ArrowLeft, option, painter, widget);
    }

    bool drawIndicatorArrowRightPrimitive(const QStyleOption *option, QPainter *painter, const QWidget *widget) const
    {
        return drawIndicatorArrowPrimitive(ArrowRight, option, painter, widget);
    }

    bool drawIndicatorArrowPrimitive(ArrowOrientation orientation, const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    bool drawIndicatorHeaderArrowPrimitive(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    bool drawPanelButtonCommandPrimitive(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    bool drawPanelButtonToolPrimitive(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    bool drawTabBarPanelButtonToolPrimitive(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    bool drawPanelScrollAreaCornerPrimitive(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    bool drawPanelMenuPrimitive(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    bool drawPanelTipLabelPrimitive(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    bool drawPanelItemViewRowPrimitive(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    bool drawPanelItemViewItemPrimitive(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    bool drawIndicatorCheckBoxPrimitive(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    bool drawIndicatorRadioButtonPrimitive(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    bool drawIndicatorButtonDropDownPrimitive(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    bool drawIndicatorTabClosePrimitive(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    bool drawIndicatorTabTearPrimitive(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    bool drawIndicatorToolBarHandlePrimitive(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    bool drawIndicatorToolBarSeparatorPrimitive(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    bool drawIndicatorBranchPrimitive(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;

    //@}

    //*@name controls specialized functions
    //@{

    bool emptyControl(const QStyleOption *option, QPainter *painter, const QWidget *widget) const
    {
        Q_UNUSED(option)
        Q_UNUSED(painter)
        Q_UNUSED(widget)
        return true;
    }

    virtual bool drawPushButtonLabelControl(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    virtual bool drawToolButtonLabelControl(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    virtual bool drawCheckBoxLabelControl(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    virtual bool drawComboBoxLabelControl(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    virtual bool drawItemViewItemControl(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    virtual bool drawMenuBarEmptyArea(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    virtual bool drawMenuBarItemControl(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    virtual bool drawMenuItemControl(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    virtual bool drawProgressBarControl(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    virtual bool drawProgressBarContentsControl(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    virtual bool drawProgressBarGrooveControl(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    virtual bool drawProgressBarLabelControl(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    virtual bool drawScrollBarSliderControl(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    virtual bool drawScrollBarAddLineControl(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    virtual bool drawScrollBarSubLineControl(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    virtual bool drawShapedFrameControl(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    virtual bool drawRubberBandControl(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    virtual bool drawHeaderSectionControl(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    virtual bool drawHeaderLabelControl(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    virtual bool drawHeaderEmptyAreaControl(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    virtual bool drawTabBarTabLabelControl(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    virtual bool drawTabBarTabShapeControl(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    virtual bool drawToolBoxTabLabelControl(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    virtual bool drawToolBoxTabShapeControl(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    virtual bool drawDockWidgetTitleControl(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;

    //*@}

    //*@name complex ontrols specialized functions
    //@{
    bool drawGroupBoxComplexControl(const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget) const;
    bool drawToolButtonComplexControl(const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget) const;
    bool drawComboBoxComplexControl(const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget) const;
    bool drawSpinBoxComplexControl(const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget) const;
    bool drawSliderComplexControl(const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget) const;
    bool drawDialComplexControl(const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget) const;
    bool drawScrollBarComplexControl(const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget) const;
    bool drawTitleBarComplexControl(const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget) const;
    //@}

    //!*@name various utilty functions
    //@{

    //* spinbox arrows
    void renderSpinBoxArrow(const SubControl &subControl, const QStyleOptionSpinBox *option, QPainter *painter, const QWidget *widget) const;

    //* menu title
    void renderMenuTitle(const QStyleOptionToolButton *option, QPainter *painter, const QWidget *widget) const;

    //* return dial angle based on option and value
    qreal dialAngle(const QStyleOptionSlider *sliderOption, int value) const;

    //* returns relevant scrollbar parent
    /** needed to detect parent focus */
    const QWidget *scrollBarParent(const QWidget *widget) const;

    //* returns true if given scrollbar arrow is animated
    QColor scrollBarArrowColor(const QStyleOptionSlider *option, const SubControl &control, const QWidget *widget) const;

    //* scrollbar buttons
    enum ScrollBarButtonType {
        NoButton,
        SingleButton,
        DoubleButton
    };

    //* returns height for scrollbar buttons depending of button types
    int scrollBarButtonHeight(const ScrollBarButtonType &type) const
    {
        switch (type) {
        case NoButton:
            return Metrics::ScrollBar_NoButtonHeight;
        case SingleButton:
            return Metrics::ScrollBar_SingleButtonHeight;
        case DoubleButton:
            return Metrics::ScrollBar_DoubleButtonHeight;
        default:
            return 0;
        }
    }

    //@}

    //* translucent background
    void setTranslucentBackground(QWidget *widget) const;

    /**
    separator can have a title and an icon
    in that case they are rendered as sunken flat toolbuttons
    return toolbutton option that matches named separator menu items
    */
    QStyleOptionToolButton separatorMenuItemOption(const QStyleOptionMenuItem *menuItemOption, const QWidget *widget) const;

    //* create toolbar extension icon
    QIcon toolBarExtensionIcon(StandardPixmap, const QStyleOption *option, const QWidget *widget) const;

    //* create title bar button icon
    QIcon titleBarButtonIcon(StandardPixmap, const QStyleOption *option, const QWidget *widget) const;

    //* returns item view parent if any
    /** needed to have correct color on focused checkboxes and radiobuttons */
    const QAbstractItemView *itemViewParent(const QWidget *widget) const;

    //* returns true if a given widget is a selected item in a focused list
    /**
    This is necessary to have the correct colors used for e.g. checkboxes and radiobuttons in lists
    @param widget The widget to be checked
    @param position Used to find the relevant QModelIndex
    */
    bool isSelectedItem(const QWidget *widget, const QPoint &localPosition) const;

    //* return true if option corresponds to QtQuick control
    bool isQtQuickControl(const QStyleOption *option, const QWidget *widget) const;

    //@}

    //* adjust rect based on provided margins
    QRect insideMargin(const QRect &r, int margin) const
    {
        return insideMargin(r, margin, margin);
    }

    //* adjust rect based on provided margins
    QRect insideMargin(const QRect &r, int marginWidth, int marginHeight) const
    {
        return r.adjusted(marginWidth, marginHeight, -marginWidth, -marginHeight);
    }

    //* expand size based on margins
    QSize expandSize(const QSize &size, int margin) const
    {
        return expandSize(size, margin, margin);
    }

    //* expand size based on margins
    QSize expandSize(const QSize &size, int marginWidth, int marginHeight) const
    {
        return size + 2 * QSize(marginWidth, marginHeight);
    }

    //* returns true for vertical tabs
    bool isVerticalTab(const QStyleOptionTab *option) const
    {
        return isVerticalTab(option->shape);
    }

    bool isVerticalTab(const QTabBar::Shape &shape) const
    {
        return shape == QTabBar::RoundedEast
               || shape == QTabBar::RoundedWest
               || shape == QTabBar::TriangularEast
               || shape == QTabBar::TriangularWest;

    }

    //* right to left alignment handling
    using ParentStyleClass::visualRect;
    QRect visualRect(const QStyleOption *opt, const QRect &subRect) const
    {
        return ParentStyleClass::visualRect(opt->direction, opt->rect, subRect);
    }

    //* centering
    QRect centerRect(const QRect &rect, const QSize &size) const
    {
        return centerRect(rect, size.width(), size.height());
    }

    QRect centerRect(const QRect &rect, int width, int height) const
    {
        return QRect(rect.left() + (rect.width() - width) / 2, rect.top() + (rect.height() - height) / 2, width, height);
    }

    /*
    Checks whether the point is before the bound rect for bound of given orientation.
    This is needed to implement custom number of buttons in scrollbars,
    as well as proper mouse-hover
    */
    inline bool preceeds(const QPoint &point, const QRect &bound, const QStyleOption *option) const;

    //* return which arrow button is hit by point for scrollbar double buttons
    inline QStyle::SubControl scrollBarHitTest(const QRect &rect, const QPoint &point, const QStyleOption *option) const;

    //! return true if one of the widget's parent inherits requested type
    inline bool hasParent(const QWidget *widget, const char *className) const;

    //* return true if one of the widget's parent inherits requested type
    template<typename T> bool hasParent(const QWidget *widget) const;

    //* return true if icons should be shown in menus
    bool showIconsInMenuItems(void) const;

    //* return true if icons should be shown on buttons
    bool showIconsOnPushButtons(void) const;

    //* return true if passed widget is a menu title (KMenu::addTitle)
    bool isMenuTitle(const QWidget *widget) const;

    //* return true if passed widget is a menu title (KMenu::addTitle)
    bool hasAlteredBackground(const QWidget *widget) const;

private:

    //*@name scrollbar button types (for addLine and subLine )
    //@{
    ScrollBarButtonType _addLineButtons;
    ScrollBarButtonType _subLineButtons;
    //@}

    //* helper
    Helper *_helper;

    //* animations
    Animations *_animations;

    //* keyboard accelerators
    Mnemonics *_mnemonics;

    //* window manager
    WindowManager *_windowManager;

    //* splitter Factory, to extend splitters hit area
    SplitterFactory *_splitterFactory;

    //* widget explorer
    WidgetExplorer *_widgetExplorer;

    //* tabbar data
    AdwaitaPrivate::TabBarData *_tabBarData;

    //* icon hash
    using IconCache = QHash<StandardPixmap, QIcon>;
    IconCache _iconCache;

    //* pointer to primitive specialized function
    using StylePrimitive = bool(Style::*)(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
    StylePrimitive _frameFocusPrimitive = nullptr;

    //* pointer to control specialized function
    using StyleControl = bool (Style::*)(const QStyleOption *option, QPainter *painter, const QWidget *widget) const;

    //* pointer to control specialized function
    using StyleComplexControl = bool (Style::*)(const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget) const;

    //*@name custom elements
    //@{

    //* use Argb Drag and Drop Window
    QStyle::StyleHint SH_ArgbDndWindow;

    //! styled painting for KCapacityBar
    QStyle::ControlElement CE_CapacityBar;

    bool _dark { false };

    bool _isGNOME { false };
    bool _isKDE { false };

    //@}
};

//_________________________________________________________________________
bool Style::preceeds(const QPoint &point, const QRect &bound, const QStyleOption *option) const
{
    if (option->state & QStyle::State_Horizontal) {
        if (option->direction == Qt::LeftToRight)
            return point.x() < bound.right();
        else
            return point.x() > bound.x();

    } else
        return point.y() < bound.y();
}

//_________________________________________________________________________
QStyle::SubControl Style::scrollBarHitTest(const QRect &rect, const QPoint &point, const QStyleOption *option) const
{
    if (option->state & QStyle::State_Horizontal) {
        if (option->direction == Qt::LeftToRight)
            return point.x() < rect.center().x() ? QStyle::SC_ScrollBarSubLine : QStyle::SC_ScrollBarAddLine;
        else
            return point.x() > rect.center().x() ? QStyle::SC_ScrollBarSubLine : QStyle::SC_ScrollBarAddLine;

    } else
        return point.y() < rect.center().y() ? QStyle::SC_ScrollBarSubLine : QStyle::SC_ScrollBarAddLine;
}

//_________________________________________________________________________
bool Style::hasParent(const QWidget *widget, const char *className) const
{

    if (!widget)
        return false;

    while ((widget = widget->parentWidget())) {
        if (widget->inherits(className))
            return true;
    }

    return false;

}

//_________________________________________________________________________
template< typename T > bool Style::hasParent(const QWidget *widget) const
{

    if (!widget)
        return false;

    while ((widget = widget->parentWidget())) {
        if (qobject_cast<const T *>(widget))
            return true;
    }

    return false;
}

} // namespace Adwaita

#endif // ADWAITA_STYLE_H

