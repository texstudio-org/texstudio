# eolang package
# Matthew Bertucci 2022/11/13 for v0.5.0

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
# loads arrows, shapes, snakes, decorations, decorations.pathmorphing,
# positioning, backgrounds, and calc tikzlibraries
#include:trimclip

#keyvals:\usepackage/eolang#c
tmpdir=%<path%>
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
