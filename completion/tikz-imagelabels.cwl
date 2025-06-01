# tikz-imagelabels package
# Matthew Bertucci 11/2/2021 for v0.2

#include:tikz
#include:xifthen
#include:tikzlibrarycalc
#include:tikzlibrarypositioning
#include:tikzlibrarydecorations
#include:tikzlibrarydecorations.markings
#include:tikzlibrarymath

\begin{annotationimage}{options%keyvals}{imagefile}#g\pictureHighlight
\end{annotationimage}

#keyvals:\begin{annotationimage}
actualtext={%<text%>}
alt={%<alt text%>}
artifact#true,false
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

\imagelabelset{options%keyvals}

#keyvals:\imagelabelset
coarse grid color=#%color
fine grid color=#%color
image label font=
image label distance=##L
image label back=#%color
image label text=#%color
coordinate label font=
coordinate label distance=##L
coordinate label back=#%color
coordinate label text=#%color
annotation font=
arrow distance=##L
border thickness=##L
arrow thickness=##L
tip size=##L
outer dist=##L
#endkeyvals
