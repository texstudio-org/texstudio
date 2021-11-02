# getfiledate package
# Matthew Bertucci 11/1/2021 for v1.2

#include:etextools
#include:ltxnew
#include:xkeyval
#include:xcolor
#include:amssymb
#include:boxedminipage

\getfiledate{file}
\getfiledate[options%keyvals]{file}

#keyvals:\getfiledate
file=
prefix=
postfix=
width=##L
head=##L
foot=##L
marker=
markercolor=#%color
filenamecolor=#%color
datecolor=#%color
inlinespace=##L
separator=
sepcolor=#%color
framecolor=#%color
framesep=##L
framerule=##L
align=#center,left,right,justified
putprefix#true,false
notime#true,false
boxed#true,false
#endkeyvals