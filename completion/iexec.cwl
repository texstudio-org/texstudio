# iexec package
# Matthew Bertucci 2023/10/15 for v0.12.0

#include:shellesc
#include:pgfkeys
#include:xkeyval

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
log
null
unskip
#endkeyvals
