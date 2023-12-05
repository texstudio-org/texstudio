# fbox package
# Matthew Bertucci 2023/12/05 for v0.07

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
linewidth=##L
#keyvals
