# iexec package
# Matthew Bertucci 2022/10/29 for v0.11.2

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
exit=%<file name%>
trace
append
log
null
#endkeyvals
