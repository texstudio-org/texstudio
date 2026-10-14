# babelbidi package
# Matthew Bertucci 2026/10/13 for v0.2.0

#include:iftex
#include:xkeyval
#include:babel

#keyvals:\usepackage/babelbidi#c
bidi=#basic,bidi-r,default
layout=
fontcache#true,false
#endkeyvals

\babelbidilangs{keyvals}

#keyvals:\babelbidilangs,\usepackage/babelbidi#c
code=%<language%>
latin=%<language%>
ltr=%<language%>
rtl=%<language%>
#endkeyvals

\begin{RTL}
\end{RTL}
\begin{LTR}
\end{LTR}
\begin{latin}
\end{latin}

\LRE{text}
\LR{text}#*
\RLE{text}
\RL{text}#*
\latintoday
\lr{text}
\rl{text}
\setparLTR#*
\setparRTL#*