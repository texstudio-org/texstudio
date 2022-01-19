# sparklines package
# Matthew Bertucci 1/18/2022 for v1.7

#include:pgf

\begin{sparkline}{width%plain}
\end{sparkline}

\spark %<<x1> <y1> <x2> <y2> ... %> /
\sparkrectangle %<<y1> <y2>%>
\sparkdot %<<x> <y> <color>%>
\sparkspike %<<x> <height>%>
\sparkbottomline
\sparkbottomline[length%plain]
\sparkbottomlinex %<<x1> <x2>%>

sparkrectanglecolor#B
sparkspikecolor#B
sparklinecolor#B
sparkbottomlinecolor#B

\sparklinethickness#*
\sparkdotwidth#*
\sparkspikewidth#*
\sparkbottomlinethickness#*
\sparklineclipsep#*
\sparklineheight#*