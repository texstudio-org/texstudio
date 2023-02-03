# mgltex package
# Matthew Bertucci 2022/05/07 for v4.2

#include:keyval
#include:graphicx
#include:ifpdf
#include:verbatim

#keyvals:\usepackage/mgltex#c
draft
final
on
off
nocomments
comments
gray
color
1x
2x
3x
4x
5x
6x
7x
8x
9x
0q
1q
2q
3q
4q
5q
6q
7q
8q
9q
0v
1v
2v
eps
epsz
epsgz
bps
bpsz
bpsgz
pdf
png
jpg
jpeg
gif
tex
#endkeyvals

\begin{mgl}
\begin{mgl}[options%keyvals]
\end{mgl}
\begin{mgladdon}
\end{mgladdon}
\begin{mglfunc}{function name}
\begin{mglfunc}[number of arguments]{function name}
\end{mglfunc}
\begin{mglcode}{script name%definition}
\begin{mglcode}[options%keyvals]{script name%definition}
\end{mglcode}
\begin{mglscript}{script name%definition}
\end{mglscript}
\begin{mglsetupscript}
\end{mglsetupscript}
\begin{mglsetup}{keyword}
\end{mglsetup}
\mglplot{MGL code}
\mglplot[options%keyvals]{MGL code}
\mglgraphics{file}
\mglgraphics[options%keyvals]{file}

#keyvals:\begin{mgl},\begin{mglcode},\mglplot,\mglgraphics
bb=%<llx lly urx ury%>
bbllx=
bblly=
bburx=
bbury=
natwidth=
natheight=
hiresbb#true,false
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
gray=#on,off,0,1
mglscale=%<factor%>
quality=%<integer%>
variant=%<variant%>
imgext=%<image extension%>
#endkeyvals

#keyvals:\begin{mgl},\mglplot
label=%<name%>
#endkeyvals

#keyvals:\mglplot
setup=%<keyword%>
separator=%<symbol%>
#endkeyvals

#keyvals:\mglgraphics
path=%<file path%>
#endkeyvals

\begin{mglblock}{script name}#V
\begin{mglblock}[options%keyvals]{script name}#V
\end{mglblock}
\begin{mglblock*}{script name}#V
\begin{mglblock*}[options%keyvals]{script name}#V
\end{mglblock*}

#keyvals:\begin{mglblock},\begin{mglblock*}
lineno#true,false
#endkeyvals

\begin{mglverbatim}#V
\begin{mglverbatim}[options%keyvals]#V
\end{mglverbatim}
\begin{mglverbatim*}#V
\begin{mglverbatim*}[options%keyvals]#V
\end{mglverbatim*}

#keyvals:\begin{mglverbatim},\begin{mglverbatim*}
lineno#true,false
label=%<name%>
#endkeyvals

\begin{mglcomment}
\end{mglcomment}

\mglinclude{file}
\mglinclude[options%keyvals]{file}
\mglinclude*{file}
\mglinclude*[options%keyvals]{file}

#keyvals:\mglinclude,\mglinclude*
lineno#true,false
path=%<file path%>
#endkeyvals

\listofmglscripts

\mglTeX
\mglTeX*
\mglswitch{off|on}
\mglcomments{off|on}
\mglgray{off|on}
\mglscale{factor}
\mglquality{integer}
\mglvariant{variant}
\mglimgext{image extension}
\mglname{script name}
\mgldir{directory%definition}
\mglscriptsdir{directory%definition}
\mglgraphicsdir{directory%definition}
\mglbackupsdir{directory%definition}
\mglpaths{directory list%definition}

\mglsettings{options%keyvals}

#keyvals:\mglsettings
dir=%<directory%>
scriptsdir=%<directory%>
graphicsdir=%<directory%>
backupsdir=%<directory%>
paths=%<directory list%>
switch=#off,on,0,1
comments=#off,on,0,1
gray=#off,on,0,1
mglscale=%<factor%>
quality=%<integer%>
variant=%<variant%>
imgext=%<image extension%>
#endkeyvals

\mglsetupscriptname#*
\mglcommentname#*
\listofmglscriptsname#*
\mglverbatimname#*
\mgllinenostyle#*
\mgldashwidth#*
\mgllinethickness#*
\mglbreakindent#*

# deprecated
\begin{mglcommon}#S
\end{mglcommon}#S
