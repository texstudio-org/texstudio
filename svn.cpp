#include "svn.h"
#include "smallUsefulFunctions.h"
#include "buildmanager.h"

namespace SVN {

/*!
 * Return a filename suitable to pass to an svn command line call. This does:
 *   1. enquote the filename in double qoutes.
 *   2. add '@' at the end if the filename contains an @. This prevents the interpretation
 *      of the contained @ as revision marker. See https://stackoverflow.com/a/757510/2726279
 */
QString quote(QString filename) {
	if (filename.contains('@')) {
		filename += '@';
	}
	return quotePath(filename);
}

QString cmd(QString action, QString args)
{
	return BuildManager::CMD_SVN + " " + action + " " + args;
}

}
