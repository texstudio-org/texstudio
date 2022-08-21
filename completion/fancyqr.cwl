# fancyqr package
# Matthew Bertucci 2022/08/20 for v1.1

#include:tikz
#include:qrcode

\fancyqr{URL}#U
\fancyqr[options%keyvals]{URL}#U
\fancyqr*{URL}#U
\fancyqr*[options%keyvals]{URL}#U
\fancyqrset{options%keyvals}

#keyvals:\fancyqr,\fancyqrset,\fancyqr*
image=%<graphics code%>
image padding=%<number%>
image x padding=%<number%>
image y padding=%<number%>
gradient#true,false
color=#%color
l color=#%color
left color=#%color
r color=#%color
right color=#%color
gradient angle=%<degrees%>
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
\FancyQrRoundCut
\FancyQrHardCut

\FancyQrLoad{style-name%keyvals}

#keyvals:\FancyQrLoad
flat
frame
blobs
glitch
swift
dots
default
#endkeyvals

\FancyLoadDefault

# not documented
\FancyQrColor{arg}#S
\filename#S
\GetPattern#S
\gradient#S
\newpattern#S
\qrm#S