# currfile package
# Matthew Bertucci 10/6/2021 for v0.7d

#include:kvoptions
#include:filehook

#ifOption:abspath
#include:currfile-abspath
#endif

#ifOption:realmainfile
#include:currfile-abspath
#endif

\currfiledir#*
\currfilebase#*
\currfileext#*
\currfilename#*
\currfilepath#*
\ifcurrfiledir{text}{true}{false}#*
\ifcurrfilebase{text}{true}{false}#*
\ifcurrfileext{text}{true}{false}#*
\ifcurrfilename{text}{true}{false}#*
\ifcurrfilepath{text}{true}{false}#*
\ifcurrfile{macro or text}{text}{true}{false}#*

#ifOption:parent
\parentfiledir#*
\parentfilebase#*
\parentfileext#*
\parentfilename#*
\parentfilepath#*
\parentfileabsdir#*
\parentfileabspath#*
#endif

#ifOption:parents
\currfilegetparents#*
\parentfilediri#*
\parentfiledirii#*
\parentfilebasei#*
\parentfilebaseii#*
\parentfileexti#*
\parentfileextii#*
\parentfilenamei#*
\parentfilenameii#*
\parentfilepathi#*
\parentfilepathii#*
\parentfileabsdiri#*
\parentfileabsdirii#*
\parentfileabspathi#*
\parentfileabspathii#*
#endif