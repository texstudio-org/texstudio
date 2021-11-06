# imakeidx package
# Matthew Bertucci 11/5/2021 for v1.3e

#include:xkeyval
#include:ifxetex
#include:ifluatex
#include:multicol

\makeindex[options%keyvals]
#keyvals:\makeindex
name=
title=
program=#makeindex,xindy,texindy,truexindy
options=
noautomatic#true,false
intoc#true,false
columns=%<number%>
columnsep=##L
columnseprule#true,false
#endkeyvals

\indexsetup
#keyvals:\indexsetup
level=%<section cmd%>
toclevel=%<section csname%>
noclearpage#true,false
firstpagestyle=
headers={%<left marks%>}{%<right marks%>}
othercode=
#endkeyvals

\splitindexoptions{split index options}

\index[name]{entry}

\indexprologue{text}
\indexprologue[spacing]{text}

\printindex
\printindex[name]