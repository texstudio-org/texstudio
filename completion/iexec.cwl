# iexec package
# Matthew Bertucci 2022/10/16 for v0.9.0

#include:shellesc
#include:pgfkeys
#include:expl3
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
trace
append
log
null
#endkeyvals
