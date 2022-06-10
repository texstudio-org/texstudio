# powerdot-BerlinFU package
# Matthew Bertucci 2022/06/03 for v0.02a

#include:pifont
#include:calc
#include:graphicx
#include:tabularx
#include:ragged2e
# loads newcommands option of ragged2e
#include:helvet

FUblue#B
FUgreen#B
FUred#B
FUorange#B
FUgray#B

\inst{text}
\framelogo{graphics code}
\insertframelogo#*
\titlelogo{graphics code}
\inserttitlelogo#*
\fachbereich{fachbereich}
\insertfachbereich#*
\subtitle{text}
\insertsubtitle#*
\institute{institute}
\insertinstitute#*
\titlegraphic{imagefile}#g
\titlegraphic[options%keyvals]{imagefile}#g
\inserttitlegraphic#*

#keyvals:\titlegraphic
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

\begin{titleslide}{title}
\begin{titleslide}[options%keyvals]{title}
\end{titleslide}
\begin{basic}{title}#*
\begin{basic}[options%keyvals]{title}#*
\end{basic}#*
\begin{wideslide}{title}
\begin{wideslide}[options%keyvals]{title}
\end{wideslide}
\begin{slide}{title}
\begin{slide}[options%keyvals]{title}
\end{slide}
\begin{sectionslide}{title}
\begin{sectionslide}[options%keyvals]{title}
\end{sectionslide}
\begin{sectionwideslide}{title}
\begin{sectionwideslide}[options%keyvals]{title}
\end{sectionwideslide}

# from newcommands option of ragged2e
\LaTeXcentering#*
\LaTeXraggedleft#*
\LaTeXraggedright#*
\begin{LaTeXflushleft}#*
\end{LaTeXflushleft}#*
\begin{LaTeXflushleft}#*
\end{LaTeXflushright}#*
\begin{LaTeXcenter}#*
\end{LaTeXcenter}#*