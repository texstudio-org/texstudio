# graphicxsp package
# Matthew Bertucci 2022/05/10 for v1.0.3

#include:graphicx
#include:eso-pic
#include:verbatim

#keyvals:\usepackage/graphicxsp#c
preview
dvipsone
dvips
showembeds
!showembeds
draft
!draft
final
shownonames
!shownonames
#endkeyvals

\embedEPS{name%specialDef}{path%definition}#s#%EPSname
\embedEPS[options%keyvals]{name%specialDef}{path%definition}#s#%EPSname

#keyvals:\embedEPS
hiresbb
transparencyGroup
#endkeyvals

\bboxOf{name%keyvals}
\llxOf{name%keyvals}
\llyOf{name%keyvals}
\urxOf{name%keyvals}
\uryOf{name%keyvals}
\heightOf{name%keyvals}
\widthOf{name%keyvals}
\csOf{name%keyvals}

#keyvals:\bboxOf#c,\llxOf#c,\llyOf#c,\urxOf#c,\uryOf#c,\heightOf#c,\widthOf#c,\csOf#c
%EPSname
#endkeyvals

\begin{createImage}{bbox}{name}
\begin{createImage}[options%keyvals]{bbox}{name}
\end{createImage}

#keyvals:\begin{createImage}
transparencyGroup
#endkeyvals

\insertEPS{name}
\insertEPS[options%keyvals]{name}

#keyvals:\insertEPS,\includegraphics
name=%<name%>
transparency={%<specs%>}
presp={%<PS code%>}
postsp={%<PS code%>}
#endkeyvals

#keyvals:\insertEPS
# \includegraphics keys
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

\previewOn
\previewOff
\ifpreview#*
\previewtrue#S
\previewfalse#S

\begin{verbatimwrite}#S
\end{verbatimwrite}#S
\AddToEmbeddedEPSs{code}#*
\DVIPSONE#S
\setSMask{options}#*
\setSMask[group]{options}#*