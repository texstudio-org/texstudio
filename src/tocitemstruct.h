#ifndef TOCITEMSTRUCT_H
#define TOCITEMSTRUCT_H

#include <qstring.h>

struct TocItem
{
	QString title;
	QString file;
	int line;
	int level;
};

#endif // TOCITEMSTRUCT_H
