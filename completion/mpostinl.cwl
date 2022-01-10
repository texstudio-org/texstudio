# mpostinl package
# Matthew Bertucci 1/10/2022 for v1.5

#include:graphicx
#include:keyval
#include:verbatim

\mpostsetup{options%keyvals}

#keyvals:\usepackage/mpostinl#c,\mpostsetup
draft#true,false
final
write#true,false
compile#true,false
twice#true,false
clean#true,false
checksum#true,false
fonts#true,false
prologues=%<value%>
lineno#true,false
labelnames#true,false
latex#true,false
compiler
compiler=%<compiler%>
format
format=%<tag%>
class=%<class%>
classopt={%<class options%>}
mem=%<mem%>
command=%<command%>
now#true,false
nowall#true,false
nowkeep#true,false
globaldef#true,false
template=%<template%>
extension=%<ext%>
numberwithin=%<counter%>
beamer#true,false
warnunused#true,false
#endkeyvals

\begin{mpostfig}
\begin{mpostfig}[options%keyvals]
\end{mpostfig}

#keyvals:\begin{mpostfig}
show#true,false
file=%<file name%>
label=%<label%>
opt={%<includegraphics options%>}
now#true,false
twice#true,false
#endkeyvals

\mpostuse{label}
\mpostuse[options%keyvals]{label}

#keyvals:\mpostuse
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

\mpostgetname{label}
\mpostfigurename

\begin{mpostdef}
\begin{mpostdef}[options%keyvals]
\end{mpostdef}

#keyvals:\begin{mpostdef}
global#true,false
tex#true,false
#endkeyvals

\begin{mposttex}
\begin{mposttex}[options%keyvals]
\end{mposttex}

#keyvals:\begin{mposttex}
global#true,false
dual#true,false
#endkeyvals

\mpostplaceholder{name}
\mpostplaceholder[type%keyvals]{name}

#keyvals:\mpostplaceholder
file
label
#endkeyvals

\mpostdisplaylabel{label}

\mpostfilename
\mpostfile{file}
\mpostfile[options%keyvals]{file}

#keyvals:\mpostfile
include#true,false
#endkeyvals

\mpostdone