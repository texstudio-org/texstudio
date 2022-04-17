# sectionbox package
# Matthew Bertucci 4/14/2022 for v1.01

#include:ifthen
#include:calc
#include:fancybox
#include:color

\begin{sectionbox}{title}#L2
\begin{sectionbox}[width]{title}#L2
\end{sectionbox}
\begin{subsectionbox}{title}#L3
\begin{subsectionbox}[width]{title}#L3
\end{subsectionbox}
\begin{subsubsectionbox}{title}#L4
\begin{subsubsectionbox}[width]{title}#L4
\end{subsubsectionbox}

\framesectionbox
\doublesectionbox
\shadowsectionbox
\framesubsectionbox
\doublesubsectionbox
\shadowsubsectionbox
\framesubsubsectionbox
\doublesubsubsectionbox
\shadowsubsubsectionbox

sectboxrulecol#B
subsectboxrulecol#B
subsubsectboxrulecol#B
sectboxfillcol#B
subsectboxfillcol#B
subsubsectboxfillcol#B
sectboxtextcol#B
subsectboxtextcol#B
subsubsectboxtextcol#B

\colboxsep#*

# not documented
\makesectionbox{text}#*
\makesubsectionbox{text}#*
\makesubsubsectionbox{text}#*
\sectboxskip#*
\sectsavebox#*
\subsectboxskip#*
\subsectmargin#*
\subsectsavebox#*
\subsubsectboxskip#*
\subsubsectmargin#*
\subsubsectsavebox#*