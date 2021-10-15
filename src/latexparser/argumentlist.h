#ifndef Header_ArgumentList
#define Header_ArgumentList

#include "mostQtHeaders.h"

/*!
 * \brief The ArgumentList class holds lists of LaTeX command arguments
 *
 * An argument is enclosed either in curly or square brackets (mandatory/optional argument).
 */
class ArgumentList : public QStringList
{
public:
	inline ArgumentList() {}
	enum ArgType {Optional, Mandatory, MandatoryWithBraces};
	QString argContent(int index) const;
	QString argContent(int index, ArgType type) const;
	ArgType argType(int index) const;
	int count(ArgType type) const;
};

#endif // ARGUMENTLIST_H
