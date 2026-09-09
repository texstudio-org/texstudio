# luadraw package
# Matthew Bertucci 2026/09/08 for v3.5

#include:ifluatex
#include:luacode
#include:verbatim
#include:xkeyval
#include:tikz
#include:tikzlibrarypatterns
#include:tikzlibrarypatterns.meta
#include:tikzlibraryplotmarks
#include:tikzlibrarybending
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

\luadrawLiteral{code}#*