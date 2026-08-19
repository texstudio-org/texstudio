# fancyqr package
# Matthew Bertucci 2026/08/18 for v2.4

#include:pict2e
#include:qrcode

\fancyqr{URL}#U
\fancyqr[options%keyvals]{URL}#U
\fancyqr*{URL}#U
\fancyqr*[options%keyvals]{URL}#U
\fancyqrset{options%keyvals}

#keyvals:\fancyqr,\fancyqrset,\fancyqr*
cache#true,false
classic#true,false
color=#%color
compensate=##L
content color=#%color
finder color=#%color
finder core=#auto,none,square,rounded,circle,star
finder radius=%<number%>
finder thickness=%<number%>
gradient#true,false
gradient angle=%<degrees%>
image=%<graphics code%>
image padding=%<number%>
image x padding=%<number%>
image y padding=%<number%>
inner rounding=%<number%>
overlap=%<number%>
l color=#%color
left color=#%color
r color=#%color
random color=%<colors%>
right color=#%color
rounding=%<number%>
seed=%<integer%>
size=##L
width=##L
# from qrcode
height=##L
level=#L,M,Q,H
version=
tight
padding
#endkeyvals

#keyvals:\fancyqr,\fancyqrset
link
nolink
#endkeyvals

\FancyQrDoNotPrintRadius{factor}
\FancyQrDoNotPrintSquare{x}{y}
\FancyQrGlowColor{from color}{to color}
\FancyQrGlowColor{color}{color}#S
\FancyQrGlow{width}{strength}{falloff}
\FancyQrHardCut
\FancyQrInnerRoundings
\FancyQrLoadDefault
\FancyQrLoad{style-name%keyvals}
\FancyQrNoInnerRoundings
\FancyQrPasses{integer}
\FancyQrRoundCut
\FancyQrSeed{integer}

#keyvals:\FancyQrLoad
blobs
default
dots
flat
frame
glitch
glows
goo
rounded
#endkeyvals

# not documented
\FancyQrColor{arg}#S
\FancyQrRoundedPatterns{arg}#S
\FancyQrSidePatterns{arg}#S
\filename#S
\GetPattern#S
\gradient#S
\newpattern#S
\qrm#S
