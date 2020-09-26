# ElieGouzien 2020-09-26 for interval v0.4

#include:pgfkeys

\interval{%<start%>}{%<end%>}#m
\interval[%<options%>]{%<start%>}{%<end%>}#m
\ointerval[%<options%>]{%<start%>}{%<end%>}#m*
\linterval[%<options%>]{%<start%>}{%<end%>}#m*
\rinterval[%<options%>]{%<start%>}{%<end%>}#m*
\intervalconfig{%<options%>}#*

#keyvals:\interval
open
open left
open right
#endkeyvals
#keyvals:\interval,\ointerval,\linterval,\rinterval
scaled
scaled=
#endkeyvals

#keyvals:\intervalconfig
separator symbol=
left open fence=
left closed fence=
right open fence=
right closed fence=
soft open fences
colorize=
#endkeyvals
