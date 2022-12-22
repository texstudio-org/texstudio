# eolang package
# Matthew Bertucci 2022/12/16 for v0.9.1

#include:stmaryrd
#include:amsmath
#include:amssymb
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

#keyvals:\usepackage/eolang#c
tmpdir=%<path%>
nocomments
anonymous
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
\phiConst#m
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

# internal
\begin{phicture}#S
\end{phicture}#S
