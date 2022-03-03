# mode: pst-eps.sty
# dani/2006-02-22
# Matthew Bertucci 2022-02-20 for v1.0

#include:pstricks
#include:pst-xkey

\TeXtoEPS#*
\endTeXtoEPS#*
\begin{TeXtoEPS}
\end{TeXtoEPS}

\PSTtoEPS{file%definition}{graphics objects}
\PSTtoEPS[options%keyvals]{file%definition}{graphics objects}

#keyvals:\PSTtoEPS
bbllx=##L
bblly=##L
bburx=##L
bburx=##L
makeeps=#none,new,all,all*
checkfile#true,false
headerfile=%<file name%>
headers=#none,all,user
GraphicsRef={%<x,y%>}
Translation={%<x,y%>}
Rotation=%<angle%>
Scale=
#endkeyvals

\PSTfilesLoaded#S
