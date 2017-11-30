#include "argumentlist.h"
#include "latexparser.h"

/*!
 * returns the content (i.e. String without brackets) of the index-th argument
 */
QString ArgumentList::argContent(int index) const
{
	return LatexParser::removeOptionBrackets(this->at(index));
}

/*!
 * returns the content (i.e. String without brackets) index-th argument of the
 * specified type
 */
QString ArgumentList::argContent(int index, ArgumentList::ArgType type) const
{
	for (int i = 0; i < size(); i++) {
		if (argType(i) == type) {
			if (index == 0)
				return argContent(i);
			else
				index--;
		}
	}
	return QString();
}

/*!
 * returns the type of the index-th argument
 */
ArgumentList::ArgType ArgumentList::argType(int index) const
{
	return (this->at(index)[0] == '[') ? Optional : Mandatory;
}

/*!
 * returns the number of arguments of the specified type
 */
int ArgumentList::count(ArgumentList::ArgType type) const
{
	int count = 0;
	for (int i = 0; i < size(); i++) {
		if (argType(i) == type) {
			count++;
		}
	}
	return count;
}


