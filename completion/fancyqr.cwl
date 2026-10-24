# fancyqr package
# Matthew Bertucci 2026/10/23 for v2.5

#include:pict2e
#include:qrcode

\fancyqr{URL}#U
\fancyqr[options%keyvals]{URL}#U
\fancyqr*{URL}#U
\fancyqr*[options%keyvals]{URL}#U
\fancyqrset{options%keyvals}

#keyvals:\fancyqr,\fancyqrset,\fancyqr*
add={%<style names%>}
alignment color=#%color
alignment core color=#%color
alignment=#finder,inherit,hide
background margin=##L
background radius=
background=#%color
cache#true,false
classic#true,false
color=#%color
compensate=##L
content color=#%color
eci#true,false
externalize prefix=%<prefix%>
externalize#true,false
extras={%<names%>}
faint#true,false
figure chance=
figures={%<names%>}
finder color=#%color
finder core color=#%color
finder core=#auto,none,square,rounded,circle,star
finder radius=%<number%>
finder thickness=%<number%>
gradient angle=%<degrees%>
gradient#true,false
image padding=%<number%>
image x padding=%<number%>
image y padding=%<number%>
image=%<graphics code%>
inner rounding=%<number%>
l color=#%color
left color=#%color
no extras={%<names%>}
no figures={%<names%>}
overlap=%<number%>
persist#true,false
place=
r color=#%color
random color=%<colors%>
right color=#%color
rounding=%<number%>
seed=%<integer%>
size=##L
style=%<style name%>
timing color=#%color
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

\FancyQrAdd{style name%keyvals}
\FancyQrDoNotPrintRadius{factor}
\FancyQrDoNotPrintSquare{x}{y}
\FancyQrExtraGallery
\FancyQrExtraGallery[options%keyvals]
\FancyQrFigureGallery
\FancyQrFigureGallery[options%keyvals]
\FancyQrFigureModule#L
\FancyQrGlowColor{color}{color}#S
\FancyQrGlowColor{from color}{to color}
\FancyQrGlow{width}{strength}{falloff}
\FancyQrHardCut
\FancyQrListExtras
\FancyQrListFigures
\FancyQrLoadDefault
\FancyQrLoad{style name%keyvals}
\FancyQrNoInnerRoundings
\FancyQrRoundCut
\FancyQrSeed{integer}
\FancyQrShowFigure[options%keyvals]{name}
\FancyQrShowFigure{name}
\FancyQrShowPattern{name}
\FancyQrTileGallery
\FancyQrTileGallery[options%keyvals]
\FancyQrTileShapes#*

#keyvals:\FancyQrAdd,\FancyQrLoad
blobs
castle
christmas
default
dots
flat
frame
glitch
glows
goo
halloween
rounded
snow
#endkeyvals

\FancyQrColor{arg}#S
\FancyQrDiagonals#*
\FancyQrExtraNeedsFigures{arg}#S
\FancyQrExtras{arg}#S
\FancyQrExtra{arg1}{arg2}#S
\FancyQrFigure*{name}{chance}{pattern}{code}#*
\FancyQrFigureAt{row}{column}#*
\FancyQrFigureTile{tile}#*
\FancyQrFigure{name}{chance}{pattern}{code}#*
\FancyQrGalleryAnchor#S
\FancyQrIfExtra{arg}#S
\FancyQrIfTiming{true code}{false code}#*
\FancyQrInnerRoundings#*
\FancyQrLend{arg1}{arg2}#S
\FancyQrPasses{integer}#*
\FancyQrPatternCell#S
\FancyQrRoundedPatterns{macro}#*
\FancyQrSidePatterns{macro}#*
\FancyQrSince{arg}#S
\FancyQrStyleSet{options%keyvals}#*
\GetPattern#S
\gradient#S
\newpattern{up}{left}{right}{down}{code}#*
\qrm#S