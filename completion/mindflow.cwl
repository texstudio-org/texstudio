# mindflow package
# Matthew Bertucci 2022/12/10 for v2022/12/06

#include:kvoptions
#include:lineno
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
#include:tcolorboxlibrarymany
#keyvals:\mindflowset
backgroundcolor=#%color
#endkeyvals
mindflowBackground#B
#endif
#ifOption:nonbreakable=true
#include:tcolorbox
#include:tcolorboxlibrarymany
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
