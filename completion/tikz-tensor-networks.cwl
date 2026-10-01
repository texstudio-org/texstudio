# tikz-tensor-networks package
# Matthew Bertucci 2026/09/18 for v0.8.0

#include:tikz
#include:tikzlibrarycalc
#include:tikzlibrarybackgrounds
#include:tikzlibrarydecorations.pathreplacing
#include:tikzlibrarydecorations.markings
#include:tikzlibraryfit
#include:tikzlibraryshapes.geometric
#include:tikzlibraryhobby
#include:tikzlibraryspath3
#include:tikzlibraryintersections

\begin{tenkz}[options%keyvals]#\tabular
\end{tenkz}
\begin{tenkzeq}[options%keyvals]
\end{tenkzeq}

\tn{label%plain}
\tn[options%keyvals]{label%plain}
\tnbond[options%keyvals]{end}{end}
\tnbond{end}{end}
\tndeclareatom{command}{options%keyvals}#d
\tndeclare{class%plain}{name}{options%keyvals}
\tnfuse[options%keyvals]{label%plain}
\tnfuse{label%plain}
\tngroup[options%keyvals]{body}
\tngroup{body}
\tnmark[options%keyvals]{target}{label%plain}
\tnmark{target}{label%plain}
\tnprose{text}
\tnset{options%keyvals}
\tntree[options%keyvals]{word}
\tntree{word}
\tnwire[options%keyvals]{end}{end}
\tnwire{end}{end}