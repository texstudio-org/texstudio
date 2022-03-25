# updated 11/13/2021 for v1.3

#include:epic
#include:graphicx

#keyvals:\usepackage/overpic#c
abs
percent
permil
#endkeyvals

\begin{overpic}{file}#\picture,pictureHighlight
\begin{overpic}[options%keyvals]{file}#\picture
\begin{Overpic}{tex-code}#\picture,pictureHighlight
\begin{Overpic}[options%keyvals]{tex-code}#\picture
\end{Overpic}
\end{overpic}
\setOverpic{options%keyvals}

#keyvals:\begin{overpic},\begin{Overpic},\setOverpic
abs#true,false
percent#true,false
permil#true,false
rel=%<number%>
grid#true,false
tics=%<number%>
unit=##L
# options passed to \includegraphics
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
