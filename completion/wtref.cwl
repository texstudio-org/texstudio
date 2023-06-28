# wtref package
# Matthew Bertucci 1/9/2021 for v0.4.0

#include:xkeyval

\newref{ref types}
\newref[options%keyvals]{ref types}

#keyvals:\newref
namespace=%<string%>
nonamespace
scope=%<counter%>
#endkeyvals

\setrefstyle{ref types}{options%keyvals}

#keyvals:\setrefstyle
refcmd=%<command%>
sep=%<command%>
last sep
last sep=%<command%>
prefix=%<command%>
suffix=%<command%>
#endkeyvals