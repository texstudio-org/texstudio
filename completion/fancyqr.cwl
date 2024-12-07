# fancyqr package
# Matthew Bertucci 2024/11/29 for v2.2

#include:pict2e
#include:qrcode

\fancyqr{URL}#U
\fancyqr[options%keyvals]{URL}#U
\fancyqr*{URL}#U
\fancyqr*[options%keyvals]{URL}#U
\fancyqrset{options%keyvals}

#keyvals:\fancyqr,\fancyqrset,\fancyqr*
classic#true,false
color=#%color
compensate=##L
gradient#true,false
gradient angle=%<degrees%>
image=%<graphics code%>
image padding=%<number%>
image x padding=%<number%>
image y padding=%<number%>
l color=#%color
left color=#%color
r color=#%color
random color=%<colors%>
right color=#%color
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

\FancyQrDoNotPrintSquare{x}{y}
\FancyQrDoNotPrintRadius{factor}
\FancyQrRoundCut
\FancyQrHardCut

\FancyQrLoad{style-name%keyvals}

#keyvals:\FancyQrLoad
flat
frame
blobs
glitch
dots
default
#endkeyvals

\FancyQrLoadDefault

# not documented
\FancyQrColor{arg}#S
\filename#S
\GetPattern#S
\gradient#S
\newpattern#S
\qrm#S
