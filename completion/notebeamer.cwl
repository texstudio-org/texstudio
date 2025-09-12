# notebeamer package
# Matthew Bertucci 2025/08/21 for v4.5A

#include:tikz
#include:tikzpagenodes

\includebeamer{file}
\includebeamer[keyvals]{file}
# alternative syntax
\includebeamer{file}[keyvals%plain]#S

#keyvals:\includebeamer
color=#%color
ratio=%<fp num%>
sep=##L
nup=%<integer%>
pages=%<comma list%>
lines=%<integer%>
lineno#true,false
lhead=%<text%>
rhead=%<text%>
#endkeyvals
