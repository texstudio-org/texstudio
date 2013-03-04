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

#ifndef _QFORMAT_H_
#define _QFORMAT_H_

#include "mostQtHeaders.h"

/*!
	\file qformat.h
	\brief Definition of the QFormat class
*/

template <typename T>
class QVector;

struct QFormat
{
	inline QFormat()
	 : priority(-1), realPriority(-1), weight(QFont::Normal), italic(false), overline(false), underline(false), strikeout(false), waveUnderline(false), pointSize(0)
	{}
	
	inline QFormat(const QColor& c)
	 : priority(-1), realPriority(-1), weight(QFont::Normal), italic(false), overline(false), underline(false), strikeout(false), waveUnderline(false), foreground(c), pointSize(0)
	{}
	
	inline QFormat(int w, const QColor& c)
	 : priority(-1), realPriority(-1), weight(w), italic(false), overline(false), underline(false), strikeout(false), waveUnderline(false), foreground(c), pointSize(0)
	{}
	
	inline QFormat(int w, bool i, bool u, bool s, const QColor& c)
	 : priority(-1), realPriority(-1), weight(w), italic(i), overline(false), underline(u), strikeout(s), waveUnderline(false), foreground(c), pointSize(0)
	{}
	
	inline QFormat(int w, bool i, bool o, bool u, bool s, bool wu, const QColor& c)
	 : priority(-1), realPriority(-1), weight(w), italic(i), overline(o), underline(u), strikeout(s), waveUnderline(wu), foreground(c), pointSize(0)
	{}
	
	inline QFormat(const QFormat& f)
	 : priority(f.priority), realPriority(f.realPriority), weight(f.weight), italic(f.italic),
	 	overline(f.overline), underline(f.underline), strikeout(f.strikeout), waveUnderline(f.waveUnderline),
		foreground(f.foreground), background(f.background), linescolor(f.linescolor), fontFamily(f.fontFamily), pointSize(f.pointSize)
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
				;
	}
	
	QTextCharFormat toTextCharFormat() const;
	QString toCSS(bool simplifyCSS) const;

	void setPriority(int p);

	bool widthChanging() const {return (weight != 50) || italic;}

	int priority, realPriority;
	int weight; // 50: normal, 75: bold
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
	
	int offset;
	int length;
	int format;
};

Q_DECLARE_TYPEINFO(QFormatRange, Q_PRIMITIVE_TYPE);

#endif
