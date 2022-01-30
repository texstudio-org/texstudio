# sympytex package
# Matthew Bertucci 1/30/2022 for v0.3

#include:verbatim
#include:graphicx
#include:makecmds
#include:ifpdf
#include:ifthen

#keyvals:\usepackage/sympytex#c
imagemagick
#endkeyvals

# use %definition to prevent things like ^ from being marked as incorrect
\sympy{Sympy code%definition}
\percent

\sympyplot{graphics obj, keyword args%definition}
\sympyplot[options%keyvals]{graphics obj, keyword args%definition}
\sympyplot[options%keyvals][fmt]{graphics obj, keyword args%definition}

#keyvals:\sympyplot
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

\begin{sympyblock}#V
\end{sympyblock}
\begin{sympysilent}
\end{sympysilent}
\begin{sympyverbatim}#V
\end{sympyverbatim}
\begin{comment}
\end{comment}
\sympytexindent#*