# eolang package
# Matthew Bertucci 2022/11/16 for v0.6.0

#include:stmaryrd
#include:amsmath
#include:amssymb
#include:fancyvrb
#include:iexec
#include:pgfopts
#include:ifluatex
#include:ifxetex
#include:pdftexcmds
#include:tikz
# loads arrows, shapes, snakes, decorations, decorations.pathmorphing, decorations.pathreplacing,
# positioning, calc, math, and arrows.meta tikzlibraries
#include:hyperref
#include:trimclip

#keyvals:\usepackage/eolang#c
tmpdir=%<path%>
nocomments
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

\phiConst#m
\phiWave#m
\phiSlot{arg}#m
\phiMany{arg}{under}{over}#m
\phiDotted#m

# internal
\begin{phicture}#S
\end{phicture}#S
