# eolang package
# Matthew Bertucci 2022/10/30 for v0.3.0

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
# loads arrows, shapes, decorations, decorations.pathmorphing, intersections,
# positioning, backgrounds, calc, and shapes.arrows tikzlibraries
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
\phiDotted#m

# internal
\begin{phicture}#S
\end{phicture}#S
