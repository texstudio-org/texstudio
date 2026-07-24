# iexec package
# Matthew Bertucci 2026/07/24 for v0.16.1

#include:shellesc
#include:pdftexcmds
#include:pgfopts
#include:pgfkeys

#keyvals:\usepackage/iexec#c
trace
#endkeyvals

\iexec{shell command%definition}
\iexec[options%keyvals]{shell command%definition}

#keyvals:\iexec
quiet
stdout=%<file name%>
stderr=%<file name%>
exit=%<file name%>
trace
append
unskip
log
null
ignore
maybe
#endkeyvals
