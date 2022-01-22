# ytableau package
# Matthew Bertucci 1/20/2022 for v1.4

#include:pgfkeys
#include:pgfopts
#include:xcolor

\ytableausetup{options%keyvals}

#keyvals:\usepackage/ytableau#c,\ytableausetup
boxsize=##L
boxframe=##L
smalltableaux
nosmalltableaux
aligntableaux=#top,center,bottom
centertableaux
nocentertableaux
textmode
mathmode
baseline
nobaseline
centerboxes
tabloids
notabloids
#endkeyvals

\begin{ytableau}#\math,array
\begin{ytableau}[formatting%formula]#\math,array
\end{ytableau}
\ytableau#S
\endytableau#S

\none

\ytableaushort{line1,line2,...%formula}
\ytableaushort[formatting%formula]{line1,line2,...%formula}

#ifOption:textmode
\ytableaushort{line1,line2,...%plain}
\ytableaushort[formatting%plain]{line1,line2,...%plain}
#endif

\ydiagram{offset+num1,num2,...}