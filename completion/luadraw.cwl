# luadraw package
# Matthew Bertucci 2026/06/03 for v3.1

#include:ifluatex
#include:luacode
#include:verbatim
#include:xkeyval
#include:tikz
#include:tikzlibrarypatterns
#include:tikzlibraryplotmarks
#include:tikzlibrarydecorations.markings
#include:tikzlibrarybackgrounds

#keyvals:\usepackage/luadraw#c
noexec
3d
cachedir=%<folder%>
#endkeyvals

\begin{luadraw}{options%keyvals}#\pictureHighlight
\end{luadraw}
\begin{luadraw*}{options%keyvals}#\pictureHighlight
\end{luadraw*}

#keyvals:\begin{luadraw},\begin{luadraw*}
name=%<file name%>
exec#true,false
auto#true,false
#endkeyvals
