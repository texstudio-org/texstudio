# chapterfolder package
# Matthew Bertucci 2/8/2022 for v2.0

#include:ifthen

\cfpart{title}{folder%URL}{file%URL}#L0
\cfpart[short title]{title}{folder%URL}{file%URL}#L0
\cfpart*{title}{folder%URL}{file%URL}#L0
\cfpart*[short title]{title}{folder%URL}{file%URL}#L0

\cfchapter{title}{folder%URL}{file%URL}#L1
\cfchapter[short title]{title}{folder%URL}{file%URL}#L1
\cfchapter*{title}{folder%URL}{file%URL}#L1
\cfchapter*[short title]{title}{folder%URL}{file%URL}#L1

\cfsection{title}{folder%URL}{file%URL}#L2
\cfsection[short title]{title}{folder%URL}{file%URL}#L2
\cfsection*{title}{folder%URL}{file%URL}#L2
\cfsection*[short title]{title}{folder%URL}{file%URL}#L2

\cfsubsection{title}{folder%URL}{file%URL}#L3
\cfsubsection[short title]{title}{folder%URL}{file%URL}#L3
\cfsubsection*{title}{folder%URL}{file%URL}#L3
\cfsubsection*[short title]{title}{folder%URL}{file%URL}#L3

\cfinput{file}#*i
\cfcurrentfolder#*
\cfinputfigure{file}#*i
\cfcurrentfolderfigure#*
\cfinputlistings{file}#*i
\cfcurrentfolderlistings#*
\cfinputalgorithms{file}#*i
\cfcurrentfolderalgorithms#*
\cffolderfigure{folder%URL}{file%URL}#*
\cfaddFolder{cmd ext}{folder%URL}#*

\cfpartstar{title}{folder%URL}{file%URL}#*L0
\cfpartstar[short title]{title}{folder%URL}{file%URL}#*L0
\cfchapterstar{title}{folder%URL}{file%URL}#*L1
\cfchapterstar[short title]{title}{folder%URL}{file%URL}#*L1
\cfsectionstar{title}{folder%URL}{file%URL}#*L2
\cfsectionstar[short title]{title}{folder%URL}{file%URL}#*L2
\cfsubsectionstar{title}{folder%URL}{file%URL}#*L3
\cfsubsectionstar[short title]{title}{folder%URL}{file%URL}#*L3

\cfpartstd{title}{folder%URL}{file%URL}#*L0
\cfpartstd[short title]{title}{folder%URL}{file%URL}#*L0
\cfchapterstd{title}{folder%URL}{file%URL}#*L1
\cfchapterstd[short title]{title}{folder%URL}{file%URL}#*L1
\cfsectionstd{title}{folder%URL}{file%URL}#*L2
\cfsectionstd[short title]{title}{folder%URL}{file%URL}#*L2
\cfsubsectionstd{title}{folder%URL}{file%URL}#*L3
\cfsubsectionstd[short title]{title}{folder%URL}{file%URL}#*L3

\cffolderinput{folder%URL}{file%URL}#*

\cfincludegraphics{imagefile}#*g
\cfincludegraphics[options%keyvals]{imagefile}#*g

#keyvals:\cfincludegraphics
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