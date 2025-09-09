# bnumexpr package
# Matthew Bertucci 2025/09/07 for v1.6

#include:xintkernel
#include:xintbinhex
#include:xintcore

#keyvals:\usepackage/bnumexpr#c
custom
customcore
custombinhex
#endkeyvals

\thebnumexpr %<<expr>%> \relax
\thebnumexpr#S
\bnethe \bnumexpr %<<expr>%> \relax
\bnumexpr %<<expr>%> \relax#*
\bnumexpr#S
\bnumeval{integer-expr list}

\bnumsetup{options%keyvals}

#keyvals:\bnumsetup
add=%<macro%>
sub=%<macro%>
mul=%<macro%>
divround=%<macro%>
div=%<macro%>
mod=%<macro%>
pow=%<macro%>
fac=%<macro%>
opp=%<macro%>
hextodec=%<macro%>
octtodec=%<macro%>
bintodec=%<macro%>
dectohex=%<macro%>
dectooct=%<macro%>
dectobin=%<macro%>
#endkeyvals

\bnumprintone#*
\bnumprintonehex#*
\bnumprintoneoct#*
\bnumprintonebin#*
\bnumprintonesep#*

\bnumdefinfix{operator}{macro}{L-prec}{R-prec}#*
\bnumdefpostfix{operator}{macro}{L-prec}#*

\BNErestorecatcodesendinput#S
\bnumexpro#S
\bnebareeval{expr}#S
