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


#ifndef MARKEDSCROLLBAR_H
#define MARKEDSCROLLBAR_H

#include <QScrollBar>
#include <QPaintEvent>
#include <QList>

#include "qdocument.h"

class MarkedScrollBar : public QScrollBar
{
    Q_OBJECT

public:
    MarkedScrollBar(QWidget *parent = nullptr);

    void addMark(int position, const QColor &colour,
                 const QString &identifier = "");
    void addMark(QDocumentLineHandle *dlh, const QColor &colour,
                 const QString &identifier = "");
    void removeMark(int position);
    void removeMark(const QString &identifier);
    void removeMark(int position, const QString &type);
    void removeMark(QDocumentLineHandle *dlh,QString type);
    void removeAllMarks();
    void removeMarksLessThan(int position);
    void removeMarksGreaterThan(int position);
    void removeMarksBetween(int startPos, int endPos);

    void addShade(int startPos, int endPos, const QColor &colour,
                  const QString &identifier = "");
    void removeShade(const QString &identifier);
    void removeAllShades();
	
	bool isClipped() const;
	void enableClipping(bool clip);

    void setDocument(QDocument *newDoc){ ///< set document used in text editor in order to handle linehandles
        doc=newDoc;
    }
	
	Q_PROPERTY(bool clipped READ isClipped WRITE enableClipping)

protected:
    struct markData
    {
        /// Position of the mark (visualLine)
        int pos;

        /// real lineNumber
        int realLn;

        /// Position of the mark (realLine)
        QDocumentLineHandle *dlh;

        /// Colour of the mark
        QColor colour;

        /// Identifier
        QString identifier;
    };

    struct shadeData
    {
        /// Starting coord of the shaded region
        int start;

        /// Stopping coord of the shaded region
        int end;

        /// Colour of the shade
        QColor colour;

        /// Identifier
        QString identifier;
    };

    QList<markData> m_marks;
    QList<shadeData> m_shades;
	
	bool m_isClipped;

    QDocument *doc;

    virtual void paintEvent(QPaintEvent *event);
    virtual void sliderChange(SliderChange change);
};

#endif // MARKEDSCROLLBAR_H

