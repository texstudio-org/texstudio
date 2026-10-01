# eolang package
# Matthew Bertucci 2026/09/30 for v0.26.1

#include:stmaryrd
#include:amsmath
#include:amssymb
#include:upgreek
#include:fancyvrb
#include:iexec
#include:pgfopts
#include:ifluatex
#include:ifxetex
#include:pdftexcmds
#include:xstring
#include:tikz
#include:tikzlibraryshapes
#include:tikzlibrarydecorations
#include:tikzlibrarydecorations.pathmorphing
#include:tikzlibrarydecorations.pathreplacing
#include:tikzlibrarypositioning
#include:tikzlibrarycalc
#include:tikzlibrarymath
#include:tikzlibraryarrows.meta
#include:hyperref
#include:trimclip
#include:shellesc

#keyvals:\usepackage/eolang#c
tmpdir=%<path%>
nocomments
nodollar
nocolor
anonymous
noshell
#endkeyvals

\begin{phiquation}#\math
\end{phiquation}
\begin{phiquation*}#\math
\end{phiquation*}

\phiq{expression%formula}

\begin{sodg}
\end{sodg}

\eolang
\phic
\xmir

\phiSlot{arg}#m
\phiTerminal{arg}
\phiWave#m
\phiDotted#m
\phiOset{over}{arg}#m
\phiUset{under}{arg}#m
\phiMany{arg}{under}{over}#m
\phiSaveTo{name}
\sodgSaveTo{name}
\eoAnon{content}
\eoAnon[substitution]{content}
\phiEOL#*
\phiNormalize#m
\phiNormalize[sub]#m
\phiEvaluate#m
\phiEvaluate[sub]#m
\phiDataize#m
\phiDataize[sub]#m
\phiMorph#m
\phiMorph[sub]#m
\phiContextualize#m
\phiContextualize[sub]#m

# internal
\begin{phicture}#S
\end{phicture}#S
