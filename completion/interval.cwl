# ElieGouzien 2020-09-26 for interval v0.4

#include:pgfkeys

\interval{%<start%>}{%<end%>}#m
\interval[%<options%>]{%<start%>}{%<end%>}#m
\ointerval[%<options%>]{%<start%>}{%<end%>}#m
\linterval[%<options%>]{%<start%>}{%<end%>}#m
\rinterval[%<options%>]{%<start%>}{%<end%>}#m
\intervalconfig{%<options%>}

#keyvals:\interval
open
open left
open right
#endkeyvals
#keyvals:\interval,\ointerval,\linterval,\rinterval
scaled
scaled=%<scale command%>
#endkeyvals

#keyvals:\intervalconfig
separator symbol=%<symbol%>
left open fence=%<symbol%>
left closed fence=%<symbol%>
right open fence=%<symbol%>
right closed fence=%<symbol%>
soft open fences
colorize=%<color commands%>
#endkeyvals

\INTVversion#S
