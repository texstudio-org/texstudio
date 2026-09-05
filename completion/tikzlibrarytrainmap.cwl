# trainmap tikzlibrary
# Matthew Bertucci 2026/08/28 for v1.0.0
# adapted from cwl provided by the package

#include:tikzlibrarycalc
#include:tikzlibrarybending

# Environment
\begin{trainmap}
\begin{trainmap}[options%keyvals]
\end{trainmap}
#
# Trunk definition
\settrunk{y1/color1, y2/color2, ...}
#
# Stations
\addstation{name}
\addstation[options%keyvals]{name}
\addterminal{name}{line}
\addterminal[options%keyvals]{name}{line}
\addinterchange{name}
\addinterchange[options%keyvals]{name}
#
# Tracks, branches and forks
\track{from}{to}{color}
\track[options%keyvals]{from}{to}{color}
\branch{from}{to}{color}
\branch[options%keyvals]{from}{to}{color}
\forkup{from}{to}{color}
\forkup[options%keyvals]{from}{to}{color}
\forkline{from}{to}{color}
\forkline[options%keyvals]{from}{to}{color}
\forkdown{from}{to}{color}
\forkdown[options%keyvals]{from}{to}{color}
\joinline{from}{to}{color}
\joinline[options%keyvals]{from}{to}{color}
#
# Exposed macros (position of the last placed station)
\tmlastx
\tmlasty
#
# Configuration keys (used inside [ ... ])
#keyvals:\begin{trainmap},\addstation,\addterminal,\addinterchange
mode=#fgc,rodalies
line code=%<code%>
line color=#color
track width=##L
station color=#color
station width=##L
terminal size=##L
terminal border=##L
badge color=#color
capsule width=##L
capsule inner=##L
capsule color=#color
station step=%<num%>
track sep=%<num%>
max width=%<num%>
row sep=%<num%>
label angle=%<num%>
label position=#above,below
corr=%<CODE/color,...%>
name=%<id%>
#endkeyvals

tmR1#B
tmR2#B
tmR2N#B
tmR2S#B
tmR3#B
tmR4#B
tmR7#B
tmR8#B
tmR11#B
tmR12#B
tmR13#B
tmR14#B
tmR15#B
tmR16#B
tmR17#B
tmRL1#B
tmRL2#B
tmRG1#B
tmRT1#B
tmRT2#B
tmL6#B
tmL7#B
tmL12#B
tmS1#B
tmS2#B
tmL8#B
tmR5#B
tmR50#B
tmR6#B
tmR60#B