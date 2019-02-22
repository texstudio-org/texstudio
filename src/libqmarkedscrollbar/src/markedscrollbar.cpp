/*
    This file is part of libqmarkedscrollbar
    Copyright (C) 2009  Freddie Witherden

    libqmarkedscrollbar is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    libqmarkedscrollbar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with libqmarkedscrollbar.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "markedscrollbar.h"

#include <QPainter>
#include <QStyle>
#include <QStyleOptionSlider>

/*!
    \class MarkedScrollBar
    \brief Provides a QScrollBar with support for marked regions.

    A MarkedScrollBar is a special type of scroll bar which supports \e marks.
    These are small lines that are rendered onto the track of the scroll bar
    that can be used to indicate the location of points of interest.

    An example usage of scroll bar marks would be to highlight the location of
    compiler warnings/errors (with different colours for each) in a piece of
    source code.

    Furthermore the class also provides support for \e shades. While marks
    indicate a specific point in a document/view shades indicate a range or
    block. An instance where a shade would be useful is in a collaborative text
    editor in order to show which parts of the document have been selected by
    different users.

    Marks and shades are provided in scroll bar coordinates, between minimim()
    and maximum() with the translation to device coordinates being performed
    behind the scenes by the class.
*/

MarkedScrollBar::MarkedScrollBar(QWidget *parent)
 : QScrollBar(parent), m_isClipped(true), doc(nullptr)
{
}

/*!
    Adds a new mark to the scroll bar. If no identifier is specified then this
    defaults to a blank string.

    \param position The position in the scroll bar to add the mark to.
    \param colour The colour of the mark.
    \param identifier A string which can later be used to identify the mark.
*/
void MarkedScrollBar::addMark(int position, const QColor& colour,
                              const QString& identifier)
{
    int ln=position;
    if(doc)
        ln=doc->visualLineNumber(position);
    markData mark = { ln, position, nullptr, colour, identifier };
    m_marks.append(mark);
}
/*!
    Adds a new mark to the scroll bar. If no identifier is specified then this
    defaults to a blank string.

    \param dlh The position in the scroll bar to add the mark to.
    \param colour The colour of the mark.
    \param identifier A string which can later be used to identify the mark.
*/
void MarkedScrollBar::addMark(QDocumentLineHandle *dlh, const QColor &colour,
             const QString &identifier){
    markData mark = { -1,-1, dlh, colour, identifier };
    m_marks.append(mark);
}

/*!
    Removes the mark at \a position.

    \param position The position of the mark to be removed.
*/
void MarkedScrollBar::removeMark(int position)
{
    QMutableListIterator<markData> i(m_marks);
    while (i.hasNext())
    {
        if (i.next().pos == position)
        {
            i.remove();
            break;
        }
    }
}
/*!
    Removes the mark at \a position if it has \a type.

    \param position The position of the mark to be removed if type is correct.
    \param type
*/
void MarkedScrollBar::removeMark(int position,const QString &type)
{
    QMutableListIterator<markData> i(m_marks);
    while (i.hasNext())
    {
        markData mark=i.next();
        if (mark.pos == position && (type.isEmpty() || mark.identifier == type) )
        {
            i.remove();
        }
    }
}
/*!
    Removes the mark at position \a dlh if it has \a type.

    \param dlh The position of the mark to be removed if type is correct.
    \param type
*/
void MarkedScrollBar::removeMark(QDocumentLineHandle *dlh,QString type)
{
    QMutableListIterator<markData> i(m_marks);
    while (i.hasNext())
    {
        markData mark=i.next();
        if (mark.dlh == dlh && (type.isEmpty() || mark.identifier == type) )
        {
            i.remove();
        }
    }
}

/*!
    Removes the mark identified by \a identifier.

    \param identifier The identifier of the mark to be removed.
*/
void MarkedScrollBar::removeMark(const QString& identifier)
{
    QMutableListIterator<markData> i(m_marks);
    while (i.hasNext())
    {
        if (i.next().identifier == identifier)
        {
            i.remove();
        }
    }
}

/*!
    Removes all marks from the scroll bar.
*/
void MarkedScrollBar::removeAllMarks()
{
    m_marks.clear();
}

/*!
    Removes all marks from the scroll bar which occur before \a position.

    \param position The position to remove all marks less than.
*/
void MarkedScrollBar::removeMarksLessThan(int position)
{
    QMutableListIterator<markData> i(m_marks);
    while (i.hasNext())
    {
        int pos = i.next().pos;
        if (pos < position)
        {
            i.remove();
        }
    }
}

/*!
    Removes all marks from the scroll bar which occur after \a position.

    \param position The position to remove all marks greater than.
*/
void MarkedScrollBar::removeMarksGreaterThan(int position)
{
    QMutableListIterator<markData> i(m_marks);
    while (i.hasNext())
    {
        int pos = i.next().pos;
        if (pos > position)
        {
            i.remove();
        }
    }
}

/*!
    Removes all marks with a position between \a start and \a end.

    \param start The starting position.
    \param end The ending position.
*/
void MarkedScrollBar::removeMarksBetween(int start, int end)
{
    if (start > end)
    {
        qWarning("MarkedScrollBar::removeMarksBetween: start > end");
    }

    QMutableListIterator<markData> i(m_marks);
    while (i.hasNext())
    {
        int pos = i.next().pos;
        if (pos > start && pos < end)
        {
            i.remove();
        }
    }
}

/*!
    Adds a new shade between \a startPos and \a endPos.

    \param startPos The starting position of the shaded block.
    \param endPos The ending position of the shaded block.
    \param colour The colour of the shade.
    \param identifier The identifier to use for the shade.
*/
void MarkedScrollBar::addShade(int startPos, int endPos, const QColor& colour,
                               const QString& identifier)
{
    if (startPos > endPos)
    {
        qWarning("MarkedScrollBar::addShade: bad argument, startPos > endPos");
    }

    shadeData shade = { startPos, endPos, colour, identifier };
    m_shades.append(shade);
}

/*!
    Removes the shade with an identifier of \a identifier.

    \param identifier The identifier of the shade to remove.
*/
void MarkedScrollBar::removeShade(const QString &identifier)
{
    QMutableListIterator<shadeData> i(m_shades);
    while (i.hasNext())
    {
        if (i.next().identifier == identifier)
        {
            i.remove();
            break;
        }
    }
}

/*!
    Removes all shades from the scroll bar.
*/
void MarkedScrollBar::removeAllShades()
{
    m_shades.clear();
}

/*!
    Returns if the slider is used to clip the drawing of marks/shades.
    \return If the slider is used for clipping or not.
*/
bool MarkedScrollBar::isClipped() const
{
	return m_isClipped;
}

/*!
    Sets if the slider should be used to clip the drawing of marks/shades.
	\param clip If to clip or not.
*/
void MarkedScrollBar::enableClipping(bool clip)
{
	m_isClipped = clip;
}

void MarkedScrollBar::sliderChange(SliderChange change){
    if(change==QAbstractSlider::SliderRangeChange && doc){
        // recalculate positions
        for(QList<markData>::iterator mark=m_marks.begin();mark!=m_marks.end();++mark)
        {
            mark->pos=-1;
        }
    }
    QScrollBar::sliderChange(change);
}

void MarkedScrollBar::paintEvent(QPaintEvent *event)
{
    // Draw the scrollbar control
    QScrollBar::paintEvent(event);

    // Get the style options for the control
    QStyleOptionSlider styleOption;
    initStyleOption(&styleOption);

    // Get the bounding rectangles of the add/sub pages
    QRect addPage = style()->subControlRect(QStyle::CC_ScrollBar, &styleOption,
                                            QStyle::SC_ScrollBarAddPage, this);
    QRect subPage = style()->subControlRect(QStyle::CC_ScrollBar, &styleOption,
                                            QStyle::SC_ScrollBarSubPage, this);
    QRect slider = style()->subControlRect(QStyle::CC_ScrollBar, &styleOption,
                                           QStyle::SC_ScrollBarSlider, this);


    // Create a painter to do the actual drawing
    QPainter p(this);

    // Clip it so that we do not draw over the slider
	if (isClipped())
	{
		p.setClipRegion(QRegion(addPage) + QRegion(subPage));
	}

    // The scale factor to use
    qreal sf;

    // Scale and translate the painter appropriately
    if (orientation() == Qt::Horizontal)
    {
        p.translate(qMin(subPage.left(), addPage.left()), 0.0);

        sf = (addPage.width() + subPage.width() + slider.width())
           / ((qreal) pageStep() + maximum() - minimum());
    }
    else // if (orientation() == Qt::Vertical)
    {
        p.translate(0.0, qMin(subPage.top(), addPage.top()));

        sf = (addPage.height() + subPage.height() + slider.height())
           / ((qreal) pageStep() + maximum() - minimum());
    }

    for(QList<markData>::iterator mark=m_marks.begin();mark!=m_marks.end();++mark)
    {
        p.setPen(mark->colour);

        if (orientation() == Qt::Horizontal)
        {
            p.drawLine(QPoint(mark->pos * sf, 2),
                       QPoint(mark->pos * sf, slider.height() - 3));
        }
        else if (orientation() == Qt::Vertical)
        {
            if(doc){
                if(mark->pos<0){ // not cached
                    if(mark->dlh!=nullptr){
                        int ln=doc->indexOf(mark->dlh);
                        if(ln<0)
                            continue; // did not find line
                        mark->pos=doc->visualLineNumber(ln);
                    }
                    if(mark->realLn>=0){
                        mark->pos=doc->visualLineNumber(mark->realLn);
                    }
                }
            }
            p.drawLine(QPoint(2, mark->pos * sf),
                       QPoint(slider.width() - 3, mark->pos * sf));
        }
    }

    foreach (shadeData shade, m_shades)
    {
        QColor penColour = shade.colour;
        QColor brushColour = shade.colour;
        brushColour.setAlphaF(brushColour.alphaF() * 0.45);

        p.setPen(penColour);
        p.setBrush(brushColour);

        if (orientation() == Qt::Horizontal)
        {
            p.drawRect(QRect(QPoint(shade.start * sf, 2),
                             QPoint(shade.end * sf, slider.height() - 4)));

        }
        else if (orientation() == Qt::Vertical)
        {
            p.drawRect(QRect(QPoint(2, shade.start * sf),
                             QPoint(slider.width() - 4, shade.end * sf)));
        }
    }
}

