# fitr package
# Matthew Bertucci 2022/05/10 for v1.3.2

#include:xkeyval
#include:ifpdf
#include:ifxetex
#include:ifluatex
#include:xcolor
#include:eforms
#include:calc
#include:collectbox

#keyvals:\usepackage/fitr#c
pdftex
luatex
dvips
dvipsone
dvipdfm
dvipdfmx
xetex
preview
!preview
viewMagWin
!viewMagWin
gonative
blinkonjmp
!blinkonjmp
blinkonrestore
!blinkonrestore
blink
!blink
#endkeyvals

\jdRect
\jdRect[options%keyvals]
\jdRect*{content%text}
\jdRect*[options%keyvals]{content%text}

#keyvals:\jdRect,\jdRect*
lift=##L
shift=##L
width=##L
height=##L
ref=#t,c,b
adddestw=##L
adddesth=##L
button#true,false
link=#jmp,restore
nodest#true,false
dest=%<name%>
allowFX#true,false
#endkeyvals

\restoreOverlayPresets
\viewMagWinOff
\viewMagWinOn

\allowFXDefault#*
\overlayPresets#*

\allowFXcode#*
\FitRbboxB{width}{height}#*
\FRblinkonjmpfalse#*
\FRblinkonjmptrue#*
\FRblinkonrestorefalse#*
\FRblinkonrestoretrue#*
\FRusedljsfalse#*
\FRusedljstrue#*
\ifFRblinkonjmp#*
\ifFRblinkonrestore#*
\ifFRusedljs#*
\ifviewMagWin#*
\pbJmpLnkPresets#*
\setFitRDest{width}{height}{name}#*
\themagCnt#*
\viewMagWinfalse#*
\viewMagWintrue#*