# chapterfolder package
# Matthew Bertucci 2/8/2022 for v2.0

#include:ifthen

\cfpart{title}{folder%file}{file%file}#L0
\cfpart[short title]{title}{folder%file}{file%file}#L0
\cfpart*{title}{folder%file}{file%file}#L0
\cfpart*[short title]{title}{folder%file}{file%file}#L0

\cfchapter{title}{folder%file}{file%file}#L1
\cfchapter[short title]{title}{folder%file}{file%file}#L1
\cfchapter*{title}{folder%file}{file%file}#L1
\cfchapter*[short title]{title}{folder%file}{file%file}#L1

\cfsection{title}{folder%file}{file%file}#L2
\cfsection[short title]{title}{folder%file}{file%file}#L2
\cfsection*{title}{folder%file}{file%file}#L2
\cfsection*[short title]{title}{folder%file}{file%file}#L2

\cfsubsection{title}{folder%file}{file%file}#L3
\cfsubsection[short title]{title}{folder%file}{file%file}#L3
\cfsubsection*{title}{folder%file}{file%file}#L3
\cfsubsection*[short title]{title}{folder%file}{file%file}#L3

\cfinput{file}#*i
\cfcurrentfolder#*
\cfinputfigure{file}#*i
\cfcurrentfolderfigure#*
\cfinputlistings{file}#*i
\cfcurrentfolderlistings#*
\cfinputalgorithms{file}#*i
\cfcurrentfolderalgorithms#*
\cffolderfigure{folder%file}{file%file}#*
\cfaddFolder{cmd ext}{folder%file}#*

\cfpartstar{title}{folder%file}{file%file}#*L0
\cfpartstar[short title]{title}{folder%file}{file%file}#*L0
\cfchapterstar{title}{folder%file}{file%file}#*L1
\cfchapterstar[short title]{title}{folder%file}{file%file}#*L1
\cfsectionstar{title}{folder%file}{file%file}#*L2
\cfsectionstar[short title]{title}{folder%file}{file%file}#*L2
\cfsubsectionstar{title}{folder%file}{file%file}#*L3
\cfsubsectionstar[short title]{title}{folder%file}{file%file}#*L3

\cfpartstd{title}{folder%file}{file%file}#*L0
\cfpartstd[short title]{title}{folder%file}{file%file}#*L0
\cfchapterstd{title}{folder%file}{file%file}#*L1
\cfchapterstd[short title]{title}{folder%file}{file%file}#*L1
\cfsectionstd{title}{folder%file}{file%file}#*L2
\cfsectionstd[short title]{title}{folder%file}{file%file}#*L2
\cfsubsectionstd{title}{folder%file}{file%file}#*L3
\cfsubsectionstd[short title]{title}{folder%file}{file%file}#*L3

\cffolderinput{folder%file}{file%file}#*

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
