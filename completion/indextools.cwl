# indextools package
# Matthew Bertucci 2/5/2022 for v1.5.1

#include:xkeyval
#include:ifxetex
#include:ifluatex
#include:pdftexcmds
#include:xpatch
#include:multicol

#keyvals:\usepackage/indextools#c
makeindex
xindy
texindy
truexindy
noautomatic
nonewpage
quiet
original
afterindex
innote
notenumber
splitindex
#endkeyvals

\makeindex[options%keyvals]

#keyvals:\makeindex
name=%<name%>
title=%<text%>
program=#makeindex,xindy,texindy,truexindy
options=%<program options%>
noautomatic#true,false
intoc#true,false
columns=%<integer%>
columnsep=##L
columnseprule#true,false
#endkeyvals

\indexsetup{options%keyvals}

#keyvals:\indexsetup
level=%<section command%>
toclevel=%<section csname%>
noclearpage#true,false
firstpagestyle=%<page style%>
headers={%<left mark%>}{%<right mark%>}
othercode=%<code%>
#endkeyvals

\splitindexoptions{splitindex option}
\index[name]{entry}
\indexprologue{text}
\indexprologue[spacing]{text}
\printindex
\printindex[name

\alsoname#*
\innotenumber{arg1}{arg2}#*
\innote{text}#*
\seealso{text}{page}#*
\seename#*
\see{text}{page}#*

#ifOption:innote
\nindex[name]{entry}#*
\nindex{entry}#*
\nnumberindex[name]{entry}#*
\nnumberindex{entry}#*
#endif

#ifOption:notenumber
\nindex[name]{entry}#*
\nindex{entry}#*
\nnumberindex[name]{entry}#*
\nnumberindex{entry}#*
#endif