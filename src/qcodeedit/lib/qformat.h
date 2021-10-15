/****************************************************************************
**
** Copyright (C) 2006-2009 fullmetalcoder <fullmetalcoder@hotmail.fr>
**
** This file is part of the Edyuk project <http://edyuk.org>
** 
** This file may be used under the terms of the GNU General Public License
** version 3 as published by the Free Software Foundation and appearing in the
** file GPL.txt included in the packaging of this file.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef Header_QFormat
#define Header_QFormat

#include "mostQtHeaders.h"

/*!
	\file qformat.h
	\brief Definition of the QFormat class
*/
#if (QT_VERSION>=QT_VERSION_CHECK(6,0,0))
//template <typename T>
//class QList;
#else
template <typename T>
class QVector;
#endif

struct QFormat
{
	inline QFormat()
     : priority(-1), realPriority(-1), weight(QFont::Normal), italic(false), overline(false), underline(false), strikeout(false), waveUnderline(false), pointSize(0),wrapAround(false)
	{}
	
	inline QFormat(const QColor& c)
     : priority(-1), realPriority(-1), weight(QFont::Normal), italic(false), overline(false), underline(false), strikeout(false), waveUnderline(false), foreground(c), pointSize(0),wrapAround(false)
	{}

#if (QT_VERSION>=QT_VERSION_CHECK(6,0,0))
    inline QFormat(QFont::Weight w, const QColor& c)
     : priority(-1), realPriority(-1), weight(w), italic(false), overline(false), underline(false), strikeout(false), waveUnderline(false), foreground(c), pointSize(0),wrapAround(false)
    {}

    inline QFormat(QFont::Weight w, bool i, bool u, bool s, const QColor& c)
     : priority(-1), realPriority(-1), weight(w), italic(i), overline(false), underline(u), strikeout(s), waveUnderline(false), foreground(c), pointSize(0),wrapAround(false)
    {}

    inline QFormat(QFont::Weight w, bool i, bool o, bool u, bool s, bool wu, const QColor& c)
     : priority(-1), realPriority(-1), weight(w), italic(i), overline(o), underline(u), strikeout(s), waveUnderline(wu), foreground(c), pointSize(0),wrapAround(false)
    {}

#else
	inline QFormat(int w, const QColor& c)
     : priority(-1), realPriority(-1), weight(w), italic(false), overline(false), underline(false), strikeout(false), waveUnderline(false), foreground(c), pointSize(0),wrapAround(false)
	{}

    inline QFormat(int w, bool i, bool u, bool s, const QColor& c)
     : priority(-1), realPriority(-1), weight(w), italic(i), overline(false), underline(u), strikeout(s), waveUnderline(false), foreground(c), pointSize(0),wrapAround(false)
    {}

    inline QFormat(int w, bool i, bool o, bool u, bool s, bool wu, const QColor& c)
     : priority(-1), realPriority(-1), weight(w), italic(i), overline(o), underline(u), strikeout(s), waveUnderline(wu), foreground(c), pointSize(0),wrapAround(false)
    {}

#endif
	
	
	inline QFormat(const QFormat& f)
	 : priority(f.priority), realPriority(f.realPriority), weight(f.weight), italic(f.italic),
	 	overline(f.overline), underline(f.underline), strikeout(f.strikeout), waveUnderline(f.waveUnderline),
        foreground(f.foreground), background(f.background), linescolor(f.linescolor), fontFamily(f.fontFamily), pointSize(f.pointSize),wrapAround(f.wrapAround)
	{}
	
	inline QFormat& operator = (const QFormat& f)
	{
		priority = f.priority;
		realPriority = f.realPriority;
		weight = f.weight;
		italic = f.italic;
		overline = f.overline;
		underline = f.underline;
		strikeout = f.strikeout;
		foreground = f.foreground;
		background = f.background;
		linescolor = f.linescolor;
		waveUnderline = f.waveUnderline;
		fontFamily = f.fontFamily;
		pointSize = f.pointSize;
        wrapAround = f.wrapAround;
		
		return *this;
	}
	
	inline bool operator == (const QFormat& f) const
	{
		return 		(priority == f.priority)
				&&
					(realPriority == f.realPriority)
				&&
					(weight == f.weight)
				&&
					(italic == f.italic)
				&&
					(overline == f.overline)
				&&
					(underline == f.underline)
				&&
					(strikeout == f.strikeout)
				&&
					(foreground == f.foreground)
				&&
					(background == f.background)
				&&
					(linescolor == f.linescolor)
				&&
					(waveUnderline == f.waveUnderline)
				&&
					(fontFamily == f.fontFamily)
				&&
					(pointSize == f.pointSize)
                &&
                    (wrapAround == f.wrapAround)
				;
	}
	
	inline bool operator != (const QFormat& f) const
	{
		return 		(priority != f.priority)
				||
					(realPriority != f.realPriority)
				||
					(weight != f.weight)
				||
					(italic != f.italic)
				||
					(overline != f.overline)
				||
					(underline != f.underline)
				||
					(strikeout != f.strikeout)
				||
					(foreground != f.foreground)
				||
					(background != f.background)
				||
					(linescolor != f.linescolor)
				||
					(waveUnderline != f.waveUnderline)
				||
					(fontFamily != f.fontFamily)
				||
					(pointSize != f.pointSize)
                ||
                    (wrapAround != f.wrapAround)
				;
	}
	
	QTextCharFormat toTextCharFormat() const;
	QString toCSS(bool simplifyCSS) const;

	void setPriority(int p);



	int priority, realPriority;
#if (QT_VERSION>=QT_VERSION_CHECK(6,0,0))
    bool widthChanging() const {return (weight != QFont::Medium) || italic;}
    QFont::Weight weight;
#else
    bool widthChanging() const {return (weight != 50) || italic;}
	int weight; // 50: normal, 75: bold
#endif
	bool italic;
	bool overline;
	bool underline;
	bool strikeout;
	bool waveUnderline;
	QColor foreground;
	QColor background;
	QColor linescolor;
	QString fontFamily;
	int pointSize;
    bool wrapAround; // fill empty space with background like fullSelection
};

Q_DECLARE_TYPEINFO(QFormat, Q_MOVABLE_TYPE);

struct QFormatRange
{
	inline QFormatRange()
	 : offset(0), length(0), format(0)
	{}
	
	inline QFormatRange(int o, int l, int f)
	 : offset(o), length(l), format(f)
	{}
	
	inline bool operator == (const QFormatRange& o) const
	{ return (offset == o.offset) && (length == o.length) && (format == o.format); }
	
	inline bool operator != (const QFormatRange& o) const
	{ return (offset != o.offset) || (length != o.length) || (format != o.format); }
	
	inline bool isValid() const
	{ return offset != 0 || length != 0 || format != 0; }

	int offset;
	int length;
	int format;
};

Q_DECLARE_TYPEINFO(QFormatRange, Q_PRIMITIVE_TYPE);


class QLineFormatAnalyzer {
	/*!
	 * Utility class for fast checking if certain formats are contained in a line
	 */
public:
	QLineFormatAnalyzer(const QVector<int> &formats) : m_formats(formats) {
        for (int col=0; col<m_formats.size(); col++) {
			if (!firstColForFormat.contains(m_formats[col])) {
				firstColForFormat.insert(m_formats[col], col);
			}
		}
	}
	
	/*! returns the column in which a format occurs or -1 */
	inline int firstCol(int format) {return firstColForFormat.value(format, -1);}
	
	/*! returns the length of a format counting from startCol */
	int formatLength(int startCol) {
		int fmt = m_formats[startCol];
		int endCol = startCol+1;
        while (endCol < m_formats.size() && m_formats[endCol] == fmt) endCol++;
		return endCol - startCol;
		
	}
	
private:
	QVector<int> m_formats;
	QHash<int, int> firstColForFormat;
};

#endif
