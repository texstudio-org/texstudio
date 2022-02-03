# mindflow package
# Matthew Bertucci 2/2/2022 for v1.2

#include:kvoptions
#include:linenoamsmath
#include:xcolor
#include:nowidow
#include:verbatim

#keyvals:\usepackage/mindflow#c
linenumber#true,false
mathlines#true,false
leftlinenumber#true,false
rightlinenumber#true,false
leftmarker#true,false
rightmarker#true,false
incolumn#true,false
off#true,false
on#true,false
nonbreakable#true,false
#endkeyvals

#ifOption:nonbreakable
#include:tcolorbox
# tcolorbox loaded with option many
#include:amsmath
#include:tikz
#include:xparse
#include:pdfcol
#keyvals:\mindflowset
backgroundcolor=#%color
#endkeyvals
mindflowBackground#B
#endif

\begin{mindflow}
\end{mindflow}

\mindflowset{options%keyvals}

#keyvals:\mindflowset
left=%<text%>
textcolor=#%color
numcolor=#%color
markercolor=#%color
linecolor=#%color
right=%<text%>
textfont=%<font commands%>
numfont=%<font commands%>
markerfont=%<font commands%>
lineheight=##L
linenumber#true,false
leftlinenumber#true,false
rightlinenumber#true,false
leftmarker#true,false
rightmarker#true,false
incolumn#true,false
off#true,false
on#true,false
#endkeyvals

\mindflowTextFont#*
\mindflowNumFont#*
\mindflowMarkerFont#*
\mindflowLeft#*
\mindflowRight#*
\mindflowLineHeight#*

mindflowLine#B
mindflowText#B
mindflowNum#B
mindflowMarker#B

\AutoIncolumn#*
\LocallyStopLineNumbers#*
\ResumeIncolumn#*
\ResumeLineNumbers#*
\endmindflow#S
\endmindflowOFF#S
\endmindflowON#S
\mfSepLine#*
\mindflow#S
\mindflowOFF#S
\mindflowON#S
\themfLN#*
\therecordLN#*
\ifLNturnsON#*
\LNturnsONtrue#*
\LNturnsONfalse#*
\ifICturnsON#*
\ICturnsONtrue#*
\ICturnsONfalse#*