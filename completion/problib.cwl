# problib package
# Matthew Bertucci 2026/10/05 for v1.0

#include:xcolor
#include:tabularx

\problibsetup{keyvals}

#keyvals:\usepackage/problib#c,\problibsetup
library=%<directory%>
roots={%<list of directories%>}
problemspace=
partspace=
subpartspace=
spacestyle=#blank,lines,dottedlines,box,grid
showdata#true,false
keyspace#true,false
warnreuse=%<days%>
#endkeyvals

#keyvals:\usepackage/problib#c
catalog#true,false
#endkeyvals

\begin{problem}
\begin{problem}[metadata]
\end{problem}

\problemmeta{key%plain}
\problemspace[style]{length}
\problemspace{length}
\problibassignment{keyvals}
\problibcatalog
\problibcatalog[filters]
\useproblem[options%keyvals]{path%file}
\useproblem{path%file}

#keyvals:\problibassignment
name=
course=
term=
type=
date=
record#true,false
#endkeyvals

#keyvals:\problibcatalog
folders=
tags=
topics=
difficulty=
unusedsince=%<date%>
sort=#path,difficulty,lastused
show=
#endkeyvals

#keyvals:\useproblem
space=
partspace=
subpartspace=
spacestyle=#blank,lines,dottedlines,box,grid
points=%<number%>
newpage#true,false
#endkeyvals

\problibentry{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}#S
\problibrecord#S
\problibusage{arg1}{arg2}#S