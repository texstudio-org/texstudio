# iexec package
# Matthew Bertucci 1/9/2021 for v0.5.1

#include:shellesc
#include:pgfkeys
#include:xkeyval

#keyvals:\usepackage/iexec#c
trace
#endkeyvals

\iexec{shell command%definition}
\iexec[options%keyvals]{shell command%definition}

#keyvals:\iexec
trace
stdout=%<file name%>
quiet
#endkeyvals