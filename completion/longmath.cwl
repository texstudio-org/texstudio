# longmath package
# Matthew Bertucci 2024/03/25 for v0.1

#include:luatexbase

\lleft#m
\mleft#m
\mmbin#m
\mmiddle#m
\mmop#m
\mmord#m
\mmpunct#m
\mmrel#m
\mright#m
\rright#m

\begin{longmath}{width}#m
\begin{longmath}[align%keyvals]{width}#m
\end{longmath}#m
\begin{longmath*}{width}#m
\begin{longmath*}[align%keyvals]{width}#m
\end{longmath*}#m

#keyvals:\begin{longmath},\begin{longmath*}
c
t
b
#endkeyvals

\delimiterprefix{prefix}
\delimiterscale
\ignorelimits
\includelimits
\longmathlinesep#L
\pulldelimiter
\pushdelimiter