# auto-pst-pdf-lua package
# Matthew Bertucci 1/29/2022 for v0.03

#include:luatex
#include:ifpdf
#include:xkeyval
#include:ifplatform
#include:ifluatex
#include:pst-pdf

#keyvals:\usepackage/auto-pst-pdf-lua#c
off
on
crop=#on,off
ext=%<extension%>
latex={%<latex options%>}
dvips={%<dvips options%>}
pspdf={%<pspdf options%>}
pdfcrop={%<pdfcrop options%>}
cleanup={%<extension list%>}
runs=%<number%>
# options from pst-pdf
active
inactive
pstricks
nopstricks
draft
final
tightpage
notightpage
displaymath
# options from pstricks
noxcolor
useCalc
gsfonts
psfonts
noEngineCheck
pdf
xetex
distiller
monochrome
grayscale
#endkeyvals

\OnlyIfFileExists{file}{code}#*
\NotIfFileExists{file}{code}#*

\matlabfig{file}#g
\matlabfig[options%keyvals]{file}#g
\mathfig{file}#g
\mathfig[options%keyvals]{file}#g
\psfragfig{file}#g
\psfragfig[options%keyvals]{file}#g

#keyvals:\matlabfig,\mathfig,\psfragfig
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