# longfigure package
# Matthew Bertucci 11/2/2021 for v1.0

#include:xkeyval

#keyvals:\usepackage/longfigure#c
figname=%<name%>
resetby=%<counter%>
set
final
errorshow
pausing
#endkeyvals

\begin{longfigure}{placement}
\end{longfigure}
\endLFfirsthead
\endLFhead
\endLFfoot
\endLFlastfoot

\LFcounter#*
\LFreset#*
\strcfstr{string1}{string2}#*
\LFupcase{text}#*
\LFleft#*
\LFright#*
\LFpre#*
\LFpost#*
\LFchunksize#*
\LFcapwidth#*
