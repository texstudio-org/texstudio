# scrjrnl class
# Matthew Bertucci 2025/04/22 for v0.2

#include:titlesec
#include:fancytabs
# default class is scrbook
#include:class-scrbook

#keyvals:\documentclass/scrjrnl#c
scrartcl
scrreprt
scrbook
monthpages
fancytabs
cleardaypages
#endkeyvals

\begin{journal}
\begin{journal}[options%keyvals]
\end{journal}

#keyvals:\begin{journal}
startmonth=%<month%>
startday=%<day%>
#endkeyvals

\jrnlmonth#L1
\jrnlmonth[options%keyvals]#L1

#keyvals:\jrnlmonth
month=%<month%>
startday=%<day%>
#endkeyvals

\jrnlday{title}#L2
\jrnlday[options%keyvals]{title}#L2

#keyvals:\jrnlday
day=%<day%>
ante=%<text%>
post=%<text%>
#endkeyvals

# not documented
\HTMLchapHook#S
\HTMLsecHook#S
\calcfancytabsGap#S
\calcfancytabsHeight#S
\calcfancytabsTop#S
\calcfancytabsWidth#S
\calcfancytabsWidthBleed#S
\dayheadfont#S
\formatdateny#S
\jrnldayafterskip#S
\jrnldaysepskip#S
\jrnlformatdate#S
\jrnlformatindexdate#S
\monthheadfont#S
\thejrnlday#S
\thejrnlmonth#S
\thejrnlmonthstartday#S
\thejrnlstartchapter#S
\thejrnlstartday#S
\thejrnlstartmonth#S
\thejrnltotalday#S
\thejrnlyear#S
