#ifndef TOCITEMSTRUCT_H
#define TOCITEMSTRUCT_H

#include <qstring.h>

class TocItem
{
public:
	QString title;
	QString file;
	int line;
	int level;

	inline bool operator==(const TocItem& rh) { return title == rh.title && file == rh.file && line == rh.line && level == rh.level; }
};

#endif // TOCITEMSTRUCT_H
