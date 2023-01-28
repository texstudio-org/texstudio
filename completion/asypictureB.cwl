# asypictureB package
# Matthew Bertucci 2/22/2022 for v0.3

#include:fancyvrb
#include:graphicx
#include:pgfkeys
#include:ifplatform

\begin{asypicture}{keyvals}
\end{asypicture}
\asyset{options%keyvals}

#keyvals:\begin{asypicture}#c,\asyset#c
name=%<name%>
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

\begin{asyheader}
\end{asyheader}

\getfontsize
\asylistingfile
\RequireAsyRecompile
\AsyCompileIfNecessary

\ASYPICcomparefiles{file1%file}{file2%file}#*
\copyfile{file1%file}{file2%file}#*
\deletefile{file%file}#*
\numlinesout#S
\oldnum#S
\unknownkey#S
