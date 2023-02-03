# fmp package
# Matthew Bertucci 2/22/2022 for v1.1a

#include:graphicx
#include:verbatim

#keyvals:\usepackage/fmp#c
# options passed to graphicx
unknownkeysallowed
draft
final
hiresbb
demo
setpagesize
nosetpagesize
dvips
xdvi
dvipdf
dvipdfm
dvipdfmx
xetex
pdftex
luatex
dvisvgm
dvipsone
dviwindo
emtex
dviwin
oztex
textures
pctexps
pctexwin
pctexhp
pctex32
truetex
tcidvi
vtex
debugshow
hiderotate
hidescale
#endkeyvals

\fmpfigure{IDstring}
\fmpfigure[options%keyvals]{IDstring}

#keyvals:\fmpfigure
alt={%<alt text%>}
bb=%<llx lly urx ury%>
bbllx=
bblly=
bburx=
bbury=
natwidth=
natheight=
hiresbb#true,false
pagebox=#mediabox,cropbox,bleedbox,trimbox,artbox
viewport=%<llx lly urx ury%>
trim=%<llx lly urx ury%>
angle=%<degrees%>
origin=
width=##L
height=##L
totalheight=##L
keepaspectratio#true,false
scale=%<factor%>
clip#true,false
draft#true,false
type=%<file type%>
ext=%<file extension%>
read=%<read-file extension%>
command=
quiet
page=%<page number%>
interpolate#true,false
decodearray={%<color array%>}
#endkeyvals

\begin{fmp}
\end{fmp}

\fmpsourcefilename{filename%file}
\fmpscriptfilename{filename%file}
\fmpfigurebasename{filename%file}

\fmpsourcepreamble{preamble%definition}
\fmpaddtosourcepreamble{code%definition}
\fmpscriptpreamble{preamble%definition}
\fmpaddtoscriptpreamble{code%definition}
\fmpsourcepostamble{preamble%definition}
\fmpaddtosourcepostamble{code%definition}
\fmpscriptpostamble{preamble%definition}
\fmpaddtoscriptpostamble{code%definition}

\thefmpfigure#*

\fmp#S
\endfmp#S
