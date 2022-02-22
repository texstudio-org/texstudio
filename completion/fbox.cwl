# fbox package
# Matthew Bertucci 2/21/2022 for v0.06

#include:xkeyval
#include:xcolor

\fbox[options%keyvals]{text}
\fbox*{text}
\fbox*[options%keyvals]{text}
\fparbox{text}
\fparbox[options%keyvals]{text}
\fparbox*{text}
\fparbox*[options%keyvals]{text}

#keyvals:\fbox#c,\fbox*#c,\fparbox#c,\fparbox*#c
boxrule=##L
boxsep=##L
lcolor=#%color
tcolor=#%color
rcolor=#%color
bcolor=#%color
#keyvals
