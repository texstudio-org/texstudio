# ticket package
# Matthew Bertucci 2022/07/24 for v0.4d

#include:ifthen
#include:calc

#keyvals:\usepackage/ticket#c
%<.tdf file%>
boxed
crossmark
circlemark
emptycrossmark
cutmark
rowmode
#endkeyvals

\ticketdefault
\ticket{content%text}
\ticketreset
\backside
\ticketskip{number}
\ticketNumbers{x}{y}
\ticketWidth#L
\ticketHeight#L
\ticketSize{width}{height}
\ticketDistance{x}{y}
\ticketToUse#*

\filedate#S
\fileversion#S