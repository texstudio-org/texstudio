# bnumexpr package
# Matthew Bertucci 2025/09/14 for v1.7

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
\bnumeval[type%keyvals]{integer-expr list}
#keyvals:\bnumeval
b
o
h
ha
#endkeyvals

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
\bnumprintonelowerhex#*
\bnumprintoneoct#*
\bnumprintonebin#*
\bnumprintonesep#*

\bnumdefinfix{operator}{macro}{L-prec}{R-prec}#*
\bnumdefpostfix{operator}{macro}{L-prec}#*

\BNErestorecatcodesendinput#S
\bnumexpro#S
\bnebareeval{expr}#S
