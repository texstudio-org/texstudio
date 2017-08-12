#ifndef SVN_H
#define SVN_H

#include "mostQtHeaders.h"

namespace SVN {

enum Status {Unknown, Unmanaged, Modified, Locked, CheckedIn, InConflict};

QString quote(QString filename);
QString cmd(QString action, QString args);

}

#endif // SVN_H
