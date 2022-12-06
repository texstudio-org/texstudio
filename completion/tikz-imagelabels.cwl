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
bb=
bbllx=
bblly=
bburx=
bbury=
natwidth=
natheight=
hiresbb#true,false
pagebox=#mediabox,cropbox,bleedbox,trimbox,artbox
viewport=
trim=
angle=
origin=
width=##L
height=##L
totalheight=##L
keepaspectratio#true,false
scale=
clip#true,false
draft#true,false
type=
ext=
read=
command=
quiet
page=
interpolate#true,false
decodearray=
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
