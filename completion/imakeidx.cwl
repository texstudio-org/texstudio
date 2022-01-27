# imakeidx package
# Matthew Bertucci 11/5/2021 for v1.3e

#include:xkeyval
#include:ifxetex
#include:ifluatex
#include:multicol

#keyvals:\usepackage/imakeidx#c
xindy
texindy
truexindy
makeindex
noautomatic
nonewpage
splitindex
original
quiet
#endkeyvals

\makeindex[options%keyvals]
#keyvals:\makeindex
name=%<name%>
title=%<text%>
program=#makeindex,xindy,texindy,truexindy
options=%<program options%>
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
othercode=%<code%>
#endkeyvals

\splitindexoptions{splitindex options}

\index[name]{entry}

\indexprologue{text}
\indexprologue[spacing]{text}

\printindex
\printindex[name]
