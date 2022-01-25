# currfile package
# Matthew Bertucci 10/6/2021 for v0.7d

#include:kvoptions
#include:filehook

#keyvals:\usepackage/currfile#c
mainext=%<extension%>
maindir=%<directory%>
fink#true,false
abspath#true,false
realmainfile#true,false
#endkeyvals

#ifOption:abspath
#include:currfile-abspath
#endif
#ifOption:abspath=true
#include:currfile-abspath
#endif

#ifOption:realmainfile
#include:currfile-abspath
#endif
#ifOption:realmainfile=true
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
