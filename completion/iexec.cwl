# iexec package
# Matthew Bertucci 2024/01/15 for v0.14.0

#include:shellesc
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
