# pst-pdf package
# Matthew Bertucci 1/12/2022 for v1.2f

#include:ifpdf
#include:ifxetex
#include:ifvtex
#include:luatex85
#include:graphicx
#include:pstricks
#include:preview
#include:environ

#keyvals:\usepackage/pst-pdf#c
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

#ifOption:useCalc
#include:pst-calculate
#endif

\PDFcontainer

\begin{postscript}
\begin{postscript}[options%keyvals]
\end{postscript}

\savepicture{name}
\usepicture{name}
\usepicture[options%keyvals]{name}

\begin{pst-pdf-defs}
\end{pst-pdf-defs}

#keyvals:\includegraphics,\usepicture,\begin{postscript}
frame#true,false
innerframe#true,false
ignore#true,false
showname#true,false
namefont=%<font commands%>
#endkeyvals

#keyvals:\usepicture,\begin{postscript}
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

\thepspicture#*
