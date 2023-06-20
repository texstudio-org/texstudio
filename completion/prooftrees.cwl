# prooftrees package
# Matthew Bertucci 2023/06/18 for v0.8

#include:svn-prov
#include:etoolbox
#include:forest
#include:amssymb
#include:amstext

#keyvals:\usepackage/prooftrees#c
tableaux
# options passed to forest package
external
linguistics
debug
#endkeyvals

#ifOption:tableaux
\begin{tableau}{tree preamble%keyvals}#\math
\end{tableau}
#endif
#ifOption:tableau
\begin{tableau}{tree preamble%keyvals}#\math
\end{tableau}
#endif

#ifOption:external
#include:tikzlibraryexternal
#endif

#ifOption:linguistics
\standardnodestrut#*
\standardnodestrutbox#*
\text{text}
#endif

\begin{prooftree}{tree preamble%keyvals}#\math
\end{prooftree}
# tableau defined if prooftree already defined
\begin{tableau}{tree preamble%keyvals}#S#\math
\end{tableau}#S

#keyvals:\begin{prooftree}#c,\begin{tableau}#c,\forestset#c
auto move#true,false
not auto move
line numbering#true,false
not line numbering
justifications#true,false
not justifications
single branches#true,false
not single branches
line no width=##L
just sep=##L
line no sep=##L
close sep=##L
proof tree inner proof width=##L
proof tree inner proof midpoint=##L
line no shift=%<integer%>
zero start
to prove={%<wff%>}
check with=%<symbol%>
check right#true,false
not check right
check left
close with=%<symbol%>
close with format={%<TikZ keys%>}
close format={%<TikZ keys%>}
subs with=%<symbol%>
subs right#true,false
not subs right
subs left
just refs left#true,false
not just refs left
just refs right
just format={%<TikZ keys%>}
line no format={%<TikZ keys%>}
wff format={%<TikZ keys%>}
proof statement format={%<TikZ keys%>}
highlight format={%<TikZ keys%>}
merge delimiter=%<punctuation%>
#endkeyvals

\linenumberstyle{number}
