# bnumexpr package
# Matthew Bertucci 11/17/2021 for v1.5

#include:xintbinhex
#include:xintcore

#keyvals:\usepackage/bnumexpr#c
custom
#endkeyvals

\thebnumexpr %<<expr>%> \relax
\thebnumexpr#S
\bnethe \bnumexpr %<<expr>%> \relax
\bnumexpr %<<expr>%> \relax#*
\bnumexpr#S
\bnumeval{integer-expr list}
\evaltohex{hex-expr list}

\bnumsetup{options%keyvals}
\bnumexprsetup{options%keyvals}#S

#keyvals:\bnumsetup,\bnumexprsetup
add=%<macro%>
sub=%<macro%>
mul=%<macro%>
divround=%<macro%>
div=%<macro%>
mod=%<macro%>
pow=%<macro%>
fac=%<macro%>
opp=%<macro%>
#endkeyvals

\bnumhextodec{hex integer}#*
\bnumprintone#*
\bnumprintonetohex#*
\bnumprintonesep#*

\bnumdefinfix{operator}{macro}{L-prec}{R-prec}#*
\bnumdefpostfix{operator}{macro}{L-prec}#*

\BNErestorecatcodes#*
\bnumexpro#*
\bnebareeval{expr}#*
\XINTfstop#*
