# ot-tableau package
# Matthew Bertucci 1/4/2022

#include:xstring
#include:amssymb
#include:bbding
#include:suffix
#include:colortbl
#include:rotating
#include:arydshln

#ifOption:usehhline
#include:hhline
#endif

#keyvals:\usepackage/ot-tableau#c
notipa
circledviolations
shadedcells
fingerafter
usehhline
#endkeyvals

\begin{tableau}{preamble}
\end{tableau}

\inp{input%text}
\ips{text}
\const{constraint%text}
\const*{constraint%text}#*
\cand{candidate%text}
\cand[symbol]{candidate%text}
\cand*{candidate%text}#*
\cand*[symbol]{candidate%text}#*
\vio{violation%text}

\SetCellShading{factor}
\Optimal

\OptimalMarker#*
\ViolationMarker#*
\CircledViolationMarker#*

\TipaOn
\TipaOff
\CircledViolationsOn
\CircledViolationsOff
\ShadingOn
\ShadingOff
\FingerBeforeLetter
\LetterBeforeFinger

\CellShading#S
\ConstraintString#S
\DoubleLine#S
\ExclOff#S
\ExclOn#S
\OptimalOff#S
\OptimalOn#S
\ShadeTheCell#S
\TopOrBottomLine#S
\UnshadeTheCell#S
\ipa{text}#S
\ip{text}#S
\properlines#S
\rowletter#S
\thetableaurow#S