# sagetex package
# Matthew Bertucci 1/31/2022 for v3.5

#include:verbatim
#include:fancyvrb
#include:listings
#include:color
#include:graphicx
#include:makecmds
#include:ifpdf
#include:ifthen

#keyvals:\usepackage/sagetex#c
final
imagemagick
epstopdf
noversioncheck
#endkeyvals

dbluecolor#B
dgreencolor#B
dgraycolor#B

\sage{Sage code%definition}
\sagestr{Sage code%definition}
\percent

\sageplot{graphics obj, keyword args}
\sageplot[options%keyvals]{graphics obj, keyword args}
\sageplot[options%keyvals][fmt]{graphics obj, keyword args}

#keyvals:\sageplot
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

\begin{sageblock}#V
\end{sageblock}
\begin{sagesilent}#V
\end{sagesilent}
\begin{sageverbatim}#V
\end{sageverbatim}

\sagetexindent

\begin{sageexample}#V
\end{sageexample}

\begin{sagecommandline}#V
\end{sagecommandline}

\sagetexpause
\sagetexunpause

\sageexampleincludetextoutput#*
\sagecommandlinetextoutput#*
\sagecommandlineskip#*

\begin{NoHyper}#S
\end{NoHyper}#S