# mode: pstricks.sty
# dani/2006-02-22
# Matthew Bertucci/2022-02-18 for v3.13

#include:iftex
#include:xcolor

#keyvals:\usepackage/pstricks#c
noxcolor
useCalc
gsfonts
psfonts
noEngineCheck
pdf
xetex
distiller
monochrome
grayscale
# options from xcolor
dvips
xdvi
dvipdf
dvipdfm
dvipdfmx
luatex
pdftex
dvipsone
dviwindo
emtex
dviwin
oztex
textures
pctexps
pctexwin
pctexhp
pctex32
truetex
tcidvi
vtex
dvisvgm
natural
rgb
cmy
cmyk
hsb
gray
RGB
HTML
HSB
Gray
monochrome
dvipsnames
dvipsnames*
svgnames
svgnames*
x11names
x11names*
table
fixpdftex
hyperref
prologue
kernelfbox
xcdraw
noxcdraw
fixinclude
showerrors
hideerrors
#endkeyvals

#ifOption:useCalc
#include:pst-calculate
#endif

#ifOption:luatex
#include:luatex
#endif

#ifOption:xetex
#include:xetex
#endif

\addtopsstyle{style}{keyvals}
\AltClipMode#*
\altcolormode#*
\arrows{arrows}
\begin{pspicture*}(x0,y0)(x1,y1)#\picture,pictureHighlight
\begin{pspicture*}[keyvals](x0,y0)(x1,y1)
\begin{pspicture}(x0,y0)(x1,y1)#\picture,pictureHighlight
\begin{pspicture}[keyvals](x0,y0)(x1,y1)
\black
\blue
\Cartesian#S
\Cartesian(x,y)#S
\clipbox[dim%l]{stuff}
\clipbox{stuff}
\closedshadow
\closedshadow[keyvals]
\closepath
\code{code}
\coor(%<x1,y1%>)(%<x2,y2%>)%<...(xN,yN)%>
\cput*[keyvals]{angle}(x,y){stuff}
\Cput*[keyvals]{angle}(x,y){stuff}#*
\cput*{angle}(x,y){stuff}
\Cput*{angle}(x,y){stuff}#*
\cput[keyvals]{angle}(x,y){stuff}
\Cput[keyvals]{angle}(x,y){stuff}#*
\cput{angle}(x,y){stuff}
\Cput{angle}(x,y){stuff}#*
\curveto(x1,y1)(x2,y2)(x3,y3)
\cyan
\darkgray
\degrees
\degrees[num]
\dim{dim}
\DontKillGlue
\end{pspicture*}
\end{pspicture}
\endoverlaybox
\endpsclip
\endpspicture#S
\everypsbox{commands}
\file{file}
\fill
\fill[keyvals]
\gray
\green
\grestore
\gsave
\ifpsmathbox#*
\ifPSTlualatex#*
\ifPSTricks#*
\ifpstUndefined#*
\ifshowgrid#*
\KillGlue
\lightgray
\lineto(coor)
\magenta
\movepath(coor)
\moveto(coor)
\mrestore
\msave
\multips(x0,y0)(x1,y1){int}{graphics}
\multips{angle}(x0,y0)(x1,y1){int}{graphics}
\multirput(x0,y0)(x1,y1){int}{stuff}
\multirput*(x0,y0)(x1,y1){int}{stuff}
\multirput*[refpoint](x0,y0)(x1,y1){int}{stuff}
\multirput*[refpoint]{angle}(x0,y0)(x1,y1){int}{stuff}
\multirput*{angle}(x0,y0)(x1,y1){int}{stuff}
\multirput[refpoint](x0,y0)(x1,y1){int}{stuff}
\multirput[refpoint]{angle}(x0,y0)(x1,y1){int}{stuff}
\multirput{angle}(x0,y0)(x1,y1){int}{stuff}
\newcmykcolor{color}{num1 num2 num3 num4}#s#%color
\newcmykcolorx#S
\newgray{color}{num}#s#%color
\newhsbcolor{color}{num1 num2 num3}#s#%color
\newhsbcolorx#S
\newpath
\newpsfontdot{arg1}[arg2]{arg3}{arg4}#*
\newpsfontdotH{arg1}[arg2]{arg3}{arg4}{arg5}#*
\newpsobject{name}{object}{keyvals}
\NewPsput#S
\newpsstyle[package]{name}{keyvals}
\newpsstyle{name}{keyvals}
\newrgbcolor{color}{num1 num2 num3}
\newrgbcolorx#S
\NormalCoor
\oldpsput#S
\OldPsput#S
\openshadow
\openshadow[keyvals]
\overlaybox
\parabola(x0,y0)(x1,y1)
\parabola*(x0,y0)(x1,y1)
\parabola*[keyvals](x0,y0)(x1,y1)
\parabola*[keyvals]{arrows}(x0,y0)(x1,y1)
\parabola*{arrows}(x0,y0)(x1,y1)
\parabola[keyvals](x0,y0)(x1,y1)
\parabola[keyvals]{arrows}(x0,y0)(x1,y1)
\parabola{arrows}(x0,y0)(x1,y1)
\pgfforeach#*
\pgfforeach{cmd}#Sd
\Polar#S
\psaddtolength{cmd}{dim}
\psarc(x,y){radius}{angleA}{angleB}
\psarc*(x,y){radius}{angleA}{angleB}
\psarc*[keyvals](x,y){radius}{angleA}{angleB}
\psarc*[keyvals]{arrows}(x,y){radius}{angleA}{angleB}
\psarc*{arrows}(x,y){radius}{angleA}{angleB}
\psarc[keyvals](x,y){radius}{angleA}{angleB}
\psarc[keyvals]{arrows}(x,y){radius}{angleA}{angleB}
\psarc{arrows}(x,y){radius}{angleA}{angleB}
\psarcAB(xC,yC)(xA,yA)(xB,yB)
\psarcAB[keyvals](xC,yC)(xA,yA)(xB,yB)
\psarcAB[keyvals]{arrows}(xC,yC)(xA,yA)(xB,yB)
\psarcAB{arrows}(xC,yC)(xA,yA)(xB,yB)
\psarcn(x,y){radius}{angleA}{angleB}
\psarcn*(x,y){radius}{angleA}{angleB}
\psarcn*[keyvals](x,y){radius}{angleA}{angleB}
\psarcn*[keyvals]{arrows}(x,y){radius}{angleA}{angleB}
\psarcn*{arrows}(x,y){radius}{angleA}{angleB}
\psarcn[keyvals](x,y){radius}{angleA}{angleB}
\psarcn[keyvals]{arrows}(x,y){radius}{angleA}{angleB}
\psarcn{arrows}(x,y){radius}{angleA}{angleB}
\psarcnAB(xC,yC)(xA,yA)(xB,yB)
\psarcnAB[keyvals](xC,yC)(xA,yA)(xB,yB)
\psarcnAB[keyvals]{arrows}(xC,yC)(xA,yA)(xB,yB)
\psarcnAB{arrows}(xC,yC)(xA,yA)(xB,yB)
\psbezier(x0,y0)(x1,y1)(x2,y2)(x3,y3)
\psBezier(x0,y0)(x1,y1)(x2,y2)(x3,y3)
\psbezier*(x0,y0)(x1,y1)(x2,y2)(x3,y3)
\psBezier*(x0,y0)(x1,y1)(x2,y2)(x3,y3)
\psbezier*[keyvals](x0,y0)(x1,y1)(x2,y2)(x3,y3)
\psBezier*[keyvals](x0,y0)(x1,y1)(x2,y2)(x3,y3)
\psbezier*[keyvals]{arrows}(x0,y0)(x1,y1)(x2,y2)(x3,y3)
\psBezier*[keyvals]{arrows}(x0,y0)(x1,y1)(x2,y2)(x3,y3)
\psbezier*{arrows}(x0,y0)(x1,y1)(x2,y2)(x3,y3)
\psBezier*{arrows}(x0,y0)(x1,y1)(x2,y2)(x3,y3)
\psbezier[keyvals](x0,y0)(x1,y1)(x2,y2)(x3,y3)
\psBezier[keyvals](x0,y0)(x1,y1)(x2,y2)(x3,y3)
\psbezier[keyvals]{arrows}(x0,y0)(x1,y1)(x2,y2)(x3,y3)
\psBezier[keyvals]{arrows}(x0,y0)(x1,y1)(x2,y2)(x3,y3)
\psbezier{arrows}(x0,y0)(x1,y1)(x2,y2)(x3,y3)
\psBezier{arrows}(x0,y0)(x1,y1)(x2,y2)(x3,y3)
\psbordercolor#*
\pscbezier(x0,y0)(x1,y1)(x2,y2)(x3,y3)
\pscbezier*(x0,y0)(x1,y1)(x2,y2)(x3,y3)
\pscbezier*[keyvals](x0,y0)(x1,y1)(x2,y2)(x3,y3)
\pscbezier*[keyvals]{arrows}(x0,y0)(x1,y1)(x2,y2)(x3,y3)
\pscbezier*{arrows}(x0,y0)(x1,y1)(x2,y2)(x3,y3)
\pscbezier[keyvals](x0,y0)(x1,y1)(x2,y2)(x3,y3)
\pscbezier[keyvals]{arrows}(x0,y0)(x1,y1)(x2,y2)(x3,y3)
\pscbezier{arrows}(x0,y0)(x1,y1)(x2,y2)(x3,y3)
\psccurve(x1,y1)(xn,yn)
\psccurve*(x1,y1)(xn,yn)
\psccurve*[keyvals](x1,y1)(xn,yn)
\psccurve*[keyvals]{arrows}(x1,y1)(xn,yn)
\psccurve*{arrows}(x1,y1)(xn,yn)
\psccurve[keyvals](x1,y1)(xn,yn)
\psccurve[keyvals]{arrows}(x1,y1)(xn,yn)
\psccurve{arrows}(x1,y1)(xn,yn)
\pscircle(x0,y0){radius}
\psCircle(x0,y0){radius}
\pscircle*(x0,y0){radius}
\psCircle*(x0,y0){radius}
\pscircle*[keyvals](x0,y0){radius}
\psCircle*[keyvals](x0,y0){radius}
\pscircle[keyvals](x0,y0){radius}
\psCircle[keyvals](x0,y0){radius}
\pscirclebox*[keyvals]{stuff}
\psCirclebox*[keyvals]{stuff}
\pscirclebox*{stuff}
\psCirclebox*{stuff}
\pscirclebox[keyvals]{stuff}
\psCirclebox[keyvals]{stuff}
\pscirclebox{stuff}
\psCirclebox{stuff}
\pscircleOA(xO,yO)(xA,yA)
\pscircleOA[keyvals](xO,yO)(xA,yA)
\psclip{graphics}
\pscoor#*
\pscspline(%<x0,y0%>)(%<x1,y1%>)%<...(xN,yN)%>
\pscspline[%<options%>](%<x0,y0%>)(%<x1,y1%>)%<...(xN,yN)%>
\pscurve(x1,y1)(xn,yn)
\pscurve*(x1,y1)(xn,yn)
\pscurve*[keyvals](x1,y1)(xn,yn)
\pscurve*[keyvals]{arrows}(x1,y1)(xn,yn)
\pscurve*{arrows}(x1,y1)(xn,yn)
\pscurve[keyvals](x1,y1)(xn,yn)
\pscurve[keyvals]{arrows}(x1,y1)(xn,yn)
\pscurve{arrows}(x1,y1)(xn,yn)
\pscustom*[keyvals]{commands}
\pscustom*{commands}
\pscustom[keyvals]{commands}
\pscustom{commands}
\psdashcolor#*
\psdblframebox*[keyvals]{stuff}
\psdblframebox*{stuff}
\psdblframebox[keyvals]{stuff}
\psdblframebox{stuff}
\psDEBUG[opt]{text}#*
\psDEBUG{text}#*
\psdiabox*[keyvals]{stuff}
\psdiabox*{stuff}
\psdiabox[keyvals]{stuff}
\psdiabox{stuff}
\psdiamond(x0,y0)(x1,y1)
\psdiamond*(x0,y0)(x1,y1)
\psdiamond*[keyvals](x0,y0)(x1,y1)
\psdiamond[keyvals](x0,y0)(x1,y1)
\psdot(x1,y1)
\psdot*(x1,y1)
\psdot*[keyvals](x1,y1)
\psdot[keyvals](x1,y1)
\psdots(x1,y1)(xn,yn)
\psdots*(x1,y1)(xn,yn)
\psdots*[keyvals](x1,y1)(xn,yn)
\psdots[keyvals](x1,y1)(xn,yn)
\psdoublecolor#*
\psdoublesep#*
\psecurve(x1,y1)(xn,yn)
\psecurve*(x1,y1)(xn,yn)
\psecurve*[keyvals](x1,y1)(xn,yn)
\psecurve*[keyvals]{arrows}(x1,y1)(xn,yn)
\psecurve*{arrows}(x1,y1)(xn,yn)
\psecurve[keyvals](x1,y1)(xn,yn)
\psecurve[keyvals]{arrows}(x1,y1)(xn,yn)
\psecurve{arrows}(x1,y1)(xn,yn)
\psellipse(x0,y0)(x1,y1)
\psellipse*(x0,y0)(x1,y1)
\psellipse*[keyvals](x0,y0)(x1,y1)
\psellipse[keyvals](x0,y0)(x1,y1)
\psellipseAB(x,y){half radius}
\psellipseAB*(x,y){half radius}
\psellipseAB*[keyvals](x,y){half radius}
\psellipseAB[keyvals](x,y){half radius}
\psellipticarc(x0,y0)(x1,y1){angle1}{angle2}
\psellipticarc*(x0,y0)(x1,y1){angle1}{angle2}
\psellipticarc*[keyvals](x0,y0)(x1,y1){angle1}{angle2}
\psellipticarc[keyvals](x0,y0)(x1,y1){angle1}{angle2}
\psellipticarcn(x0,y0)(x1,y1){angle1}{angle2}
\psellipticarcn*(x0,y0)(x1,y1){angle1}{angle2}
\psellipticarcn*[keyvals](x0,y0)(x1,y1){angle1}{angle2}
\psellipticarcn[keyvals](x0,y0)(x1,y1){angle1}{angle2}
\psellipticwedge(x0,y0)(x1,y1){angle1}{angle2}
\psellipticwedge*(x0,y0)(x1,y1){angle1}{angle2}
\psellipticwedge*[keyvals](x0,y0)(x1,y1){angle1}{angle2}
\psellipticwedge[keyvals](x0,y0)(x1,y1){angle1}{angle2}
\psfillcolor#*
\psforeach{variable%cmd}{value list}{action}#d
\psForeach{variable%cmd}{value list}{action}#d
\psframe(x0,y0)(x1,y1)
\psframe*(x0,y0)(x1,y1)
\psframe*[keyvals](x0,y0)(x1,y1)
\psframe[keyvals](x0,y0)(x1,y1)
\psframebox*[keyvals]{stuff}
\psframebox*{stuff}
\psframebox[keyvals]{stuff}
\psframebox{stuff}
\psframesep#*
\psgetCMYKColorValues{color macro}#*
\psgetColorValues{color macro}#*
\psgetRGBColorValues{color macro}#*
\psgrid(x0,y0)(x1,y1)(x2,y2)
\psgridcolor#*
\psgridlabelcolor#*
\pshatchcolor#*
\pshooklength#*
\pshookwidth#*
\pshskip{length}#*
\pslabelsep
\pslbrace
\psline(x0,y0)(x1,y1)
\psLine(x0,y0)(x1,y1)
\psLine(x1,y1)
\psline*(x0,y0)(x1,y1)
\psLine*(x0,y0)(x1,y1)
\psLine*(x1,y1)
\psline*[keyvals](x0,y0)(x1,y1)
\psLine*[keyvals](x0,y0)(x1,y1)
\psLine*[keyvals](x1,y1)
\psline*[keyvals]{arrows}(x0,y0)(x1,y1)
\psline*{arrows}(x0,y0)(x1,y1)
\psline[keyvals](x0,y0)(x1,y1)
\psLine[keyvals](x0,y0)(x1,y1)
\psLine[keyvals](x1,y1)
\psline[keyvals]{arrows}(x0,y0)(x1,y1)
\psline{arrows}(x0,y0)(x1,y1)
\pslinearc#*
\pslinecolor#*
\psLineSegments(%<x0,y0%>)(%<x1,y1%>)%<...(xN,yN)%>
\psLineSegments[%<options%>](%<x0,y0%>)(%<x1,y1%>)%<...(xN,yN)%>
\pslinestyle#*
\pslinewidth#*
\pslongbox{name}{cmd}
\psLoop{n}{argument}
\psLoopIndex#*
\psmathboxfalse
\psmathboxtrue
\psovalbox*[keyvals]{stuff}
\psovalbox*{stuff}
\psovalbox[keyvals]{stuff}
\psovalbox{stuff}
\psoverlay{string}
\psparabola(x0,y0)(x1,y1)#S
\psparabola*(x0,y0)(x1,y1)#S
\psparabola*[keyvals](x0,y0)(x1,y1)#S
\psparabola*[keyvals]{arrows}(x0,y0)(x1,y1)#S
\psparabola*{arrows}(x0,y0)(x1,y1)#S
\psparabola[keyvals](x0,y0)(x1,y1)#S
\psparabola[keyvals]{arrows}(x0,y0)(x1,y1)#S
\psparabola{arrows}(x0,y0)(x1,y1)#S
\pspicture[keyvals]#S
\psPline(x1,y1)(x2,y2)(x3,y3)
\psPline[keyvals](x1,y1)(x2,y2)(x3,y3)
\pspolygon(x0,y0)(x1,y1)(x2,y2)
\pspolygon*(x0,y0)(x1,y1)(x2,y2)
\pspolygon*[keyvals](x0,y0)(x1,y1)(x2,y2)
\pspolygon[keyvals](x0,y0)(x1,y1)(x2,y2)
\psrbrace
\psresetColor
\psRing(x,y)[start,end]{inner radius}{outer radius}
\psRing(x,y){inner radius}{outer radius}
\psRing*(x,y)[start,end]{inner radius}{outer radius}
\psRing*(x,y){inner radius}{outer radius}
\psRing*[keyvals](x,y)[start,end]{inner radius}{outer radius}
\psRing*[keyvals](x,y){inner radius}{outer radius}
\psRing[keyvals](x,y)[start,end]{inner radius}{outer radius}
\psRing[keyvals](x,y){inner radius}{outer radius}
\psrotatedown{stuff}#S
\psrotateleft{stuff}#S
\psrotateright{stuff}#S
\psrunit#*
\psscalebox{num1 num2}{stuff}
\psscaleboxto(x,y){stuff}
\pssetGrayscale
\pssetlength{cmd}{dim}
\pssetMonochrome
\pssetxlength{cmd}{dim}#*
\pssetylength{cmd}{dim}#*
\psshadowbox*[keyvals]{stuff}
\psshadowbox*{stuff}
\psshadowbox[keyvals]{stuff}
\psshadowbox{stuff}
\psshadowcolor#*
\pssubgridcolor#*
\PstAtCode#S
\pstCheckCoorType{arg}#*
\pstdriver#*
\psTextFrame(x1,y1)(x2,y2){text}
\psTextFrame*(x1,y1)(x2,y2){text}
\psTextFrame*[keyvals](x1,y1)(x2,y2){text}
\psTextFrame[keyvals](x1,y1)(x2,y2){text}
\pstheader{arg}#*
\PSTlualatexfalse#*
\PSTlualatextrue#*
\pstnodescale#*
\pstriangle(x0,y0)(x1,y1)
\pstriangle*(x0,y0)(x1,y1)
\pstriangle*[keyvals](x0,y0)(x1,y1)
\pstriangle[keyvals](x0,y0)(x1,y1)
\pstribox*[keyvals]{stuff}
\pstribox*{stuff}
\pstribox[keyvals]{stuff}
\pstribox{stuff}
\PSTricksfalse#*
\PSTricksLoaded#S
\PSTricksOff
\PSTrickstrue#*
\pstunit#*
\pstverb{commands}#*
\pstVerb{commands}#*
\pstverbscale#*
\psunit#*
\psverbboxfalse
\psverbboxtrue
\pswedge(x0,y0){radius}{angle1}{angle2}
\pswedge*(x0,y0){radius}{angle1}{angle2}
\pswedge*[keyvals](x0,y0){radius}{angle1}{angle2}
\pswedge[keyvals](x0,y0){radius}{angle1}{angle2}
\psxunit#*
\psyunit#*
\putoverlaybox{string}
\qdisk(coor){radius}
\qline(coor0)(coor1)
\radians
\rcoor(%<x1,y1%>)(%<x2,y2%>)%<...(xN,yN)%>
\rcurveto(x1,y1)(x2,y2)(x3,y3)
\red
\resetArrowOptions#*
\reversepath
\rlineto(coor)
\rotate{angle}
\rotatedown{stuff}
\rotateleft{stuff}
\rotateright{stuff}
\rput(x,y){stuff}
\rput(x,y){stuff}#*
\rput*(x,y){stuff}
\rput*(x,y){stuff}#*
\rput*[refpoint](x,y){stuff}
\rput*[refpoint](x,y){stuff}#*
\rput*[refpoint]{rotation}(x,y){stuff}
\rput*[refpoint]{rotation}(x,y){stuff}#*
\rput*{rotation}(x,y){stuff}
\rput*{rotation}(x,y){stuff}#*
\rput[refpoint](x,y){stuff}
\rput[refpoint](x,y){stuff}#*
\rput[refpoint]{rotation}(x,y){stuff}
\Rput[refpoint]{rotation}(x,y){stuff}#*
\rput{rotation}(x,y){stuff}
\rput{rotation}(x,y){stuff}#*
\scale{num}
\scale{num1 num2}
\setcolor{color}
\showgridfalse#*
\showgridtrue#*
\SpecialCoor
\stroke
\stroke[keyvals]
\swapaxes
\translate(coor)
\uput*[refangle](x,y){stuff}
\uput*[refangle]{rotation}(x,y){stuff}
\uput*{labelsep}[refangle](x,y){stuff}
\uput*{labelsep}[refangle]{rotation}(x,y){stuff}
\uput[refangle](x,y){stuff}
\uput[refangle]{rotation}(x,y){stuff}
\uput{labelsep}[refangle](x,y){stuff}
\uput{labelsep}[refangle]{rotation}(x,y){stuff}
\white
\yellow

gradbegin#B
gradend#B
randomgray#B
randomrgb#B
randomcmyk#B
randomhsb#B

# not sure about these
\psarcOA#S
\psSquare#S

# from pst-key.tex v1.11
\psset{keyvals}
\setkeys{family}{keyvals}#*

# from pst-fp.tex v0.06
\PSTFPloaded#S
\pstFPadd{cmd}{num1}{num2}#*d
\pstFPsub{cmd}{num1}{num2}#*d
\pstFPmul{cmd}{num1}{num2}#*d
\pstFPdiv{cmd}{num1}{num2}#*d
\pstFPMul{cmd}{num1}{num2}#*d
\pstFPDiv{cmd}{num1}{num2}#*d
\pstFPstripZeros{cmd}{num}#*d

# loads the following files from pgf: pgfutil-common.tex, pgfkeys.code.tex, and pgffor.code.tex
# from pgfutil-common.tex (inputs pgfutil-common-lists.tex)
\pgferror{error text%text}#*
\pgfwarning{warning text%text}#*
\pgfutilensuremath{formula}#*
\pgfutilpreparefilename{file name}#*
\pgfretvalquoted#*
\pgfutilifcontainsmacro{token list}{true}{false}#*
\pgfutilifstartswith{start with pattern}{token list}{true}{false}#*
\pgfutilstrreplace{search}{replacement}{string}#*
\pgfutilsolvetwotwoleq{2x2 matrix entries}{2x1 matrix entries}#*
\pgfutilsolvetwotwoleqfloat{2x2 matrix entries}{2x1 matrix entries}#*
# from pgfutil-common-lists.tex
\pgfapplistnewempty{applist name}#*
\pgfapplistpushback %<item to append%>\to %<applist name%>#*
\pgfapplistlet{cmd}=%<applist name%>#*
\pgfprependlistnewempty{prelist name}#*
\pgfprependlistpushfront %<item to prepend%>\to %<prelist name%>#*
\pgfprependlistlet{cmd}=%<prelist name%>#*
# from pgfkeys.code.tex
#include:pgfkeys
# from pgffor.code.tex (inputs pgfmath.code.tex)
\foreach
\foreach{cmd}#Sd
\breakforeach#*
# from pgfmath.code.tex
\pgfmathsetlength{length register}{math expression}#*
\pgfmathaddtolength{length register}{math expression}#*
\pgfmathsetcount{count register}{math expression}#*
\pgfmathaddtocount{count register}{math expression}#*
\pgfmathsetcounter{counter}{math expression}#*
\pgfmathaddtocounter{counter}{math expression}#*
\pgfmathsetmacro{cmd}{math expression}#*d
\pgfmathsetlengthmacro{cmd}{math expression}#*d
\pgfmathtruncatemacro{cmd}{math expression}#*d
\pgfmathnewcounter{counter}#*
\pgfmathmakecounterglobal{counter}#*
\pgfmathanglebetweenpoints{point 1}{point 2}#*
\pgfmathanglebetweenlines{line 1 start}{line 1 end}{line 2 start}{line 2 end}#*
\pgfmathrotatepointaround{point}{rotate center}{degree}#*
\pgfmathreflectpointalongaxis{point}{point on axis}{axis angle}#*
\pgfmathpointintersectionoflineandarc{point 1}{point 2}{arc center}{start angle}{end angle}{radii}#*
\pgfmathangleonellipse{point on ellipse}{radii}#*
# from pgfmathutil.code.tex
\pgfmathincluded#*
\ifpgfmathcontinueloop#*
\pgfmathcontinuelooptrue#*
\pgfmathcontinueloopfalse#*
\pgfmathloop %<loop body%>\repeatpgfmathloop#*
\pgfmathbreakloop#*
\pgfmathreturn#*
\pgfmathcounter#*
\pgfmathsmuggle%<marcro%>\endgroup#*
# from pgfmathparser.code.tex
\ifpgfmathfloat#*
\pgfmathfloattrue#*
\pgfmathfloatfalse#*
\ifpgfmathunitsdeclared#*
\pgfmathunitsdeclaredtrue#*
\pgfmathunitsdeclaredfalse#*
\ifpgfmathmathunitsdeclared#*
\pgfmathmathunitsdeclaredtrue#*
\pgfmathmathunitsdeclaredfalse#*
\ifpgfmathignoreunitscale#*
\pgfmathignoreunitscaletrue#*
\pgfmathignoreunitscalefalse#*
\pgfmathprint{real number}
\pgfmathparse{math expression}
\pgfmathqparse{math expression}#*
\pgfmathpostparse#*
\pgfmathscaleresult#*
\pgfmathsetresultunitscale{scale value}#*
\pgfmathresultunitscale#*
\pgfmathifexpression{math expression}{true}{false}#*
\pgfmathdeclareoperator{op}{op name}{arity}{type}{precedence}#*
# from pgfmathfunctions.code.tex
\pgfmathdeclarefunction{name}{num of args}{code}#*
\pgfmathdeclarefunction*{name}{num of args}{code}#*
\pgfmathredeclarefunction{name}{code}#*
\pgfmathnotifynewdeclarefunction{name}{num of args}{code}#*
\pgfmathdeclarepseudoconstant{name}{code}#*
\pgfmathredeclarepseudoconstant{name}{code}#*
# from pgfmathfunctions.basic.code.tex
\pgfmathadd{x}{y}#*
\pgfmathsubtract{x}{y}#*
\pgfmathneg{x}#*
\pgfmathmultiply{x}{y}#*
\pgfmathdivide{x}{y}#*
\pgfmathreciprocal{x}#*
\pgfmathdiv{x}#*
\pgfmathmod{x}{y}#*
\pgfmathMod{x}{y}#*
\pgfmathabs{x}#*
\pgfmathsign{x}#*
\pgfmathe#*
\pgfmathln{x}#*
\pgfmathlogten{x}#*
\pgfmathlogtwo{x}#*
\pgfmathexp{x}#*
\pgfmathsqrt{x}#*
\pgfmathpow{x}{power}#*
\pgfmathfactorial{x}#*
# from pgfmathfunctions.trigonometric.code.tex
\pgfmathpi#*
\pgfmathiftrigonometricusesdeg{true}{false}#*
\pgfmathradians{x in radians} # for compatibility with pgf 1.18 beta#*
\pgfmathdeg{x in radians}#*
\pgfmathrad{x in degrees}#*
\pgfmathsin{x in degrees}#*
\pgfmathcos{x in degrees}#*
\pgfmathsincos{num in degress}#*
\pgfmathtan{x in degrees}#*
\pgfmathcosec{x in degrees}#*
\pgfmathsec{x in degrees}#*
\pgfmathcot{x in degrees}#*
\pgfmathasin{x in degrees}#*
\pgfmathacos{x in degrees}#*
\pgfmathatan{x in degrees}#*
\pgfmathatantwo{y in degrees}{x in degrees}#*
# from pgfmathfunctions.random.code.tex
\pgfmathsetseed{integer}#*
\pgfmathgeneratepseudorandomnumber#*
\pgfmathrnd#*
\pgfmathrand#*
\pgfmathrandom{maximum int}#*
\pgfmathrandom{minimum int}{maximum int}#*
\pgfmathrandominteger{cmd}{minimum}{maximum}#*d
\pgfmathdeclarerandomlist{list name}{list of items}#*
\pgfmathrandomitem{cmd}{list name}#*d
# from pgfmathfunctions.comparison.code.tex
\pgfmathgreater{x}{y}#*
\pgfmathgreaterthan{x}{y}#*
\pgfmathless{x}{y}#*
\pgfmathlessthan{x}{y}#*
\pgfmathequal{x}{y}#*
\pgfmathequalto{x}{y}#*
\ifpgfmathcomparison#*
\pgfmathcomparisontrue#*
\pgfmathcomparisonfalse#*
\pgfmathapproxequalto{x}{y}#*
\pgfmathifthenelse{x}{true}{false}#*
\pgfmathnotequal{x}{y}#*
\pgfmathnotless{x}{y}#*
\pgfmathnotgreater{x}{y}#*
\pgfmathand{x}{y}#*
\pgfmathor{x}{y}#*
\pgfmathnot{x}#*
\pgfmathtrue#*
\pgfmathfalse#*
# from pgfmathfunctions.base.code.tex
\pgfmathbin{x in base 10}#*
\pgfmathhex{x in base 10}#*
\pgfmathHex{x in base 10}#*
\pgfmathoct{x in base 10}#*
\pgfmathbasetodec{cmd}{number}{base}#*d
\pgfmathdectobase{cmd}{number}{base}#*d
\pgfmathdectoBase{cmd}{number}{base}#*d
\pgfmathbasetobase{cmd}{number}{base1}{base2}#*d
\pgfmathbasetoBase{cmd}{number}{base1}{base2}#*d
\pgfmathsetbasenumberlength{integer}#*
\pgfmathtodigitlist{cmd}{number}#*d
# from pgfmathfunctions.round.code.tex
\pgfmathround{x}#*
\pgfmathfloor{x}#*
\pgfmathceil{x}#*
\pgfmathint{x}#*
\pgfmathfrac{x}#*
\pgfmathreal{x}#*
# from pgfmathfunctions.misc.code.tex
\pgfmathveclen{x coordinate}{y coordinate}#*
\pgfmathcosh{x in degree}#*
\pgfmathsinh{x in degree}#*
\pgfmathtanh{x in degree}#*
\pgfmathscientific{mantissa}{exponent}#*
\pgfmathwidth{"text"}#*
\pgfmathheight{"text"}#*
\pgfmathdepth{"text"}#*
\pgfmatharray{array}{index}#*
\pgfmathdim{array}#*
\pgfmathmax{num list}{num list}#*
\pgfmathmin{num list}{num list}#*
\pgfmathscalar{value}#*
# from pgfmathfunctions.integerarithmetics.code.tex
\pgfmathgcd{x}{y}#*
\pgfmathisprime{x}#*
\pgfmathisodd{x}#*
\pgfmathiseven{x}#*
# from pgfmathfloat.code.tex
\ifpgfmathfloatcomparison#*
\pgfmathfloatcomparisontrue#*
\pgfmathfloatcomparisonfalse#*
\ifpgfmathfloatroundhasperiod#*
\pgfmathfloatroundhasperiodtrue#*
\pgfmathfloatroundhasperiodfalse#*
\ifpgfmathprintnumberskipzeroperiod#*
\pgfmathprintnumberskipzeroperiodtrue#*
\pgfmathprintnumberskipzeroperiodfalse#*
\ifpgfmathfloatroundmayneedrenormalize#*
\pgfmathfloatroundmayneedrenormalizetrue#*
\pgfmathfloatroundmayneedrenormalizefalse#*
\pgfmathfloatparsenumber{number}#*
\pgfmathfloatqparsenumber{number}#*
\pgfmathfloattomacro{number}{flags macro%cmd}{mantissa macro%cmd}{exponent macro%cmd}#*d
\pgfmathfloattoregisters{number}{flags count}{mantissa dimen}{exponent count}#*
\pgfmathfloattoregisterstok{number}{flags count}{mantissa toks}{exponent count}#*
\pgfmathfloatgetflags{number}{flags count}#*
\pgfmathfloatgetflagstomacro{number}{flags macro%cmd}#*d
\pgfmathfloatgetmantissa{number}{mantissa dimen}#*
\pgfmathfloatgetmantisse{number}{mantissa dimen}#*
\pgfmathfloatgetmantissatok{number}{mantissa toks}#*
\pgfmathfloatgetmantissetok{number}{mantissa toks}#*
\pgfmathfloatgetexponent{number}{exponent count}#*
\pgfmathfloatcreate{flags}{mantissa}{exponent}#*
\pgfmathfloattofixed{float}#*
\pgfmathfloattoint{float}#*
\pgfmathfloattosci{float}#*
\pgfmathfloatvalueof{float}#*
\pgfmathroundto{fixed point number}#*
\pgfmathroundtozerofill{fixed point number}#*
\pgfmathfloatround{float}#*
\pgfmathfloatroundzerofill{float}#*
\pgfmathfloatrounddisplaystyle{flags}{mantissa}{exponent}#*
\pgfmathfloatgetfrac{number}#*
\pgfmathgreatestcommondivisor{int 1}{int 2}#*
\pgfmathifisint{number constant}{true}{false}#*
\pgfmathprintnumber{number}#*
\pgfmathprintnumberto{number}{cmd}#*d
\ifpgfmathfloatparsenumberpendingperiod#*
\pgfmathfloatparsenumberpendingperiodtrue#*
\pgfmathfloatparsenumberpendingperiodfalse#*
# variables
\pgfretval#*
\pgfmathresult
\pgfmathresulty#*
\pgfmathresultx#*
\pgfmathresultdenom#S
\pgfmathresultfractional#S
\pgfmathresultnumerator#S
\pgfmathresultX#S

# from xcolor options
#ifOption:table
#include:colortbl
\rowcolors[commands]{row}{even-row-color}{odd-row-color}
\rowcolors[commands]{row}{color}{color}#S
\rowcolors*[commands]{row}{even-row-color}{odd-row-color}
\rowcolors*[commands]{row}{color}{color}#S
\showrowcolors
\hiderowcolors
\rownum
#endif

#ifOption:fixpdftex
#include:pdfcolmk
#endif

#ifOption:svgnames
AliceBlue#B
DarkKhaki#B
Green#B
LightSlateGrey#B
AntiqueWhite#B
DarkMagenta#B
GreenYellow#B
LightSteelBlue#B
Aqua#B
DarkOliveGreen#B
Grey#B
LightYellow#B
Aquamarine#B
DarkOrange#B
Honeydew#B
Lime#B
Azure#B
DarkOrchid#B
HotPink#B
LimeGreen#B
Beige#B
DarkRed#B
IndianRed#B
Linen#B
Bisque#B
DarkSalmon#B
Indigo#B
Magenta#B
Black#B
DarkSeaGreen#B
Ivory#B
Maroon#B
BlanchedAlmond#B
DarkSlateBlue#B
Khaki#B
MediumAquamarine#B
Blue#B
DarkSlateGray#B
Lavender#B
MediumBlue#B
BlueViolet#B
DarkSlateGrey#B
LavenderBlush#B
MediumOrchid#B
Brown#B
DarkTurquoise#B
LawnGreen#B
MediumPurple#B
BurlyWood#B
DarkViolet#B
LemonChiffon#B
MediumSeaGreen#B
CadetBlue#B
DeepPink#B
LightBlue#B
MediumSlateBlue#B
Chartreuse#B
DeepSkyBlue#B
LightCoral#B
MediumSpringGreen#B
Chocolate#B
DimGray#B
LightCyan#B
MediumTurquoise#B
Coral#B
DimGrey#B
LightGoldenrod#B
MediumVioletRed#B
CornflowerBlue#B
DodgerBlue#B
LightGoldenrodYellow#B
MidnightBlue#B
Cornsilk#B
FireBrick#B
LightGray#B
MintCream#B
Crimson#B
FloralWhite#B
LightGreen#B
MistyRose#B
Cyan#B
ForestGreen#B
LightGrey#B
Moccasin#B
DarkBlue#B
Fuchsia#B
LightPink#B
NavajoWhite#B
DarkCyan#B
Gainsboro#B
LightSalmon#B
Navy#B
DarkGoldenrod#B
GhostWhite#B
LightSeaGreen#B
NavyBlue#B
DarkGray#B
Gold#B
LightSkyBlue#B
OldLace#B
DarkGreen#B
Goldenrod#B
LightSlateBlue#B
Olive#B
DarkGrey#B
Gray#B
LightSlateGray#B
OliveDrab#B
Orange#B
Plum#B
Sienna#B
Thistle#B
OrangeRed#B
PowderBlue#B
Silver#B
Tomato#B
Orchid#B
Purple#B
SkyBlue#B
Turquoise#B
PaleGoldenrod#B
Red#B
SlateBlue#B
Violet#B
PaleGreen#B
RosyBrown#B
SlateGray#B
VioletRed#B
PaleTurquoise#B
RoyalBlue#B
SlateGrey#B
Wheat#B
PaleVioletRed#B
SaddleBrown#B
Snow#B
White#B
PapayaWhip#B
Salmon#B
SpringGreen#B
WhiteSmoke#B
PeachPuff#B
SandyBrown#B
SteelBlue#B
Yellow#B
Peru#B
SeaGreen#B
Tan#B
YellowGreen#B
Pink#B
Seashell#B
Teal#B
#endif

#ifOption:dvipsnames
Apricot#B
Aquamarine#B
Bittersweet#B
Black#B
Blue#B
BlueGreen#B
BlueViolet#B
BrickRed#B
Brown#B
BurntOrange#B
CadetBlue#B
CarnationPink#B
Cerulean#B
CornflowerBlue#B
Cyan#B
Dandelion#B
DarkOrchid#B
Emerald#B
ForestGreen#B
Fuchsia#B
Goldenrod#B
Gray#B
Green#B
GreenYellow#B
JungleGreen#B
Lavender#B
LimeGreen#B
Magenta#B
Mahogany#B
Maroon#B
Melon#B
MidnightBlue#B
Mulberry#B
NavyBlue#B
OliveGreen#B
Orange#B
OrangeRed#B
Orchid#B
Peach#B
Periwinkle#B
PineGreen#B
Plum#B
ProcessBlue#B
Purple#B
RawSienna#B
Red#B
RedOrange#B
RedViolet#B
Rhodamine#B
RoyalBlue#B
RoyalPurple#B
RubineRed#B
Salmon#B
SeaGreen#B
Sepia#B
SkyBlue#B
SpringGreen#B
Tan#B
TealBlue#B
Thistle#B
Turquoise#B
Violet#B
VioletRed#B
White#B
WildStrawberry#B
Yellow#B
YellowGreen#B
YellowOrange#B
#endif

#ifOption:x11names
AntiqueWhite1#B
AntiqueWhite2#B
AntiqueWhite3#B
AntiqueWhite4#B
Aquamarine1#B
Aquamarine2#B
Aquamarine3#B
Aquamarine4#B
Azure1#B
Azure2#B
Azure3#B
Azure4#B
Bisque1#B
Bisque2#B
Bisque3#B
Bisque4#B
Blue1#B
Blue2#B
Blue3#B
Blue4#B
Brown1#B
Brown2#B
Brown3#B
Brown4#B
Burlywood1#B
Burlywood2#B
Burlywood3#B
Burlywood4#B
CadetBlue1#B
CadetBlue2#B
CadetBlue3#B
CadetBlue4#B
Chartreuse1#B
Chartreuse2#B
Chartreuse3#B
Chartreuse4#B
Chocolate1#B
Chocolate2#B
Chocolate3#B
Chocolate4#B
Coral1#B
Coral2#B
Coral3#B
Coral4#B
Cornsilk1#B
Cornsilk2#B
Cornsilk3#B
Cornsilk4#B
Cyan1#B
Cyan2#B
Cyan3#B
Cyan4#B
DarkGoldenrod1#B
DarkGoldenrod2#B
DarkGoldenrod3#B
DarkGoldenrod4#B
DarkOliveGreen1#B
DarkOliveGreen2#B
DarkOliveGreen3#B
DarkOliveGreen4#B
DarkOrange1#B
DarkOrange2#B
DarkOrange3#B
DarkOrange4#B
DarkOrchid1#B
DarkOrchid2#B
DarkOrchid3#B
DarkOrchid4#B
DarkSeaGreen1#B
DarkSeaGreen2#B
DarkSeaGreen3#B
DarkSeaGreen4#B
DarkSlateGray1#B
DarkSlateGray2#B
DarkSlateGray3#B
DarkSlateGray4#B
DeepPink1#B
DeepPink2#B
DeepPink3#B
DeepPink4#B
DeepSkyBlue1#B
DeepSkyBlue2#B
DeepSkyBlue3#B
DeepSkyBlue4#B
DodgerBlue1#B
DodgerBlue2#B
DodgerBlue3#B
DodgerBlue4#B
Firebrick1#B
Firebrick2#B
Firebrick3#B
Firebrick4#B
Gold1#B
Gold2#B
Gold3#B
Gold4#B
Goldenrod1#B
Goldenrod2#B
Goldenrod3#B
Goldenrod4#B
Green1#B
Green2#B
Green3#B
Green4#B
Honeydew1#B
Honeydew2#B
Honeydew3#B
Honeydew4#B
HotPink1#B
HotPink2#B
HotPink3#B
HotPink4#B
IndianRed1#B
IndianRed2#B
IndianRed3#B
IndianRed4#B
Ivory1#B
Ivory2#B
Ivory3#B
Ivory4#B
Khaki1#B
Khaki2#B
Khaki3#B
Khaki4#B
LavenderBlush1#B
LavenderBlush2#B
LavenderBlush3#B
LavenderBlush4#B
LemonChiffon1#B
LemonChiffon2#B
LemonChiffon3#B
LemonChiffon4#B
LightBlue1#B
LightBlue2#B
LightBlue3#B
LightBlue4#B
LightCyan1#B
LightCyan2#B
LightCyan3#B
LightCyan4#B
LightGoldenrod1#B
LightGoldenrod2#B
LightGoldenrod3#B
LightGoldenrod4#B
LightPink1#B
LightPink2#B
LightPink3#B
LightPink4#B
LightSalmon1#B
LightSalmon2#B
LightSalmon3#B
LightSalmon4#B
LightSkyBlue1#B
LightSkyBlue2#B
LightSkyBlue3#B
LightSkyBlue4#B
LightSteelBlue1#B
LightSteelBlue2#B
LightSteelBlue3#B
LightSteelBlue4#B
LightYellow1#B
LightYellow2#B
LightYellow3#B
LightYellow4#B
Magenta1#B
Magenta2#B
Magenta3#B
Magenta4#B
Maroon1#B
Maroon2#B
Maroon3#B
Maroon4#B
MediumOrchid1#B
MediumOrchid2#B
MediumOrchid3#B
MediumOrchid4#B
MediumPurple1#B
MediumPurple2#B
MediumPurple3#B
MediumPurple4#B
MistyRose1#B
MistyRose2#B
MistyRose3#B
MistyRose4#B
NavajoWhite1#B
NavajoWhite2#B
NavajoWhite3#B
NavajoWhite4#B
OliveDrab1#B
OliveDrab2#B
OliveDrab3#B
OliveDrab4#B
Orange1#B
Orange2#B
Orange3#B
Orange4#B
OrangeRed1#B
OrangeRed2#B
OrangeRed3#B
OrangeRed4#B
Orchid1#B
Orchid2#B
Orchid3#B
Orchid4#B
PaleGreen1#B
PaleGreen2#B
PaleGreen3#B
PaleGreen4#B
PaleTurquoise1#B
PaleTurquoise2#B
PaleTurquoise3#B
PaleTurquoise4#B
PaleVioletRed1#B
PaleVioletRed2#B
PaleVioletRed3#B
PaleVioletRed4#B
PeachPuff1#B
PeachPuff2#B
PeachPuff3#B
PeachPuff4#B
Pink1#B
Pink2#B
Pink3#B
Pink4#B
Plum1#B
Plum2#B
Plum3#B
Plum4#B
Purple1#B
Purple2#B
Purple3#B
Purple4#B
Red1#B
Red2#B
Red3#B
Red4#B
RosyBrown1#B
RosyBrown2#B
RosyBrown3#B
RosyBrown4#B
RoyalBlue1#B
RoyalBlue2#B
RoyalBlue3#B
RoyalBlue4#B
Salmon1#B
Salmon2#B
Salmon3#B
Salmon4#B
SeaGreen1#B
SeaGreen2#B
SeaGreen3#B
SeaGreen4#B
Seashell1#B
Seashell2#B
Seashell3#B
Seashell4#B
Sienna1#B
Sienna2#B
Sienna3#B
Sienna4#B
SkyBlue1#B
SkyBlue2#B
SkyBlue3#B
SkyBlue4#B
SlateBlue1#B
SlateBlue2#B
SlateBlue3#B
SlateBlue4#B
SlateGray1#B
SlateGray2#B
SlateGray3#B
SlateGray4#B
Snow1#B
Snow2#B
Snow3#B
Snow4#B
SpringGreen1#B
SpringGreen2#B
SpringGreen3#B
SpringGreen4#B
SteelBlue1#B
SteelBlue2#B
SteelBlue3#B
SteelBlue4#B
Tan1#B
Tan2#B
Tan3#B
Tan4#B
Thistle1#B
Thistle2#B
Thistle3#B
Thistle4#B
Tomato1#B
Tomato2#B
Tomato3#B
Tomato4#B
Turquoise1#B
Turquoise2#B
Turquoise3#B
Turquoise4#B
VioletRed1#B
VioletRed2#B
VioletRed3#B
VioletRed4#B
Wheat1#B
Wheat2#B
Wheat3#B
Wheat4#B
Yellow1#B
Yellow2#B
Yellow3#B
Yellow4#B
Gray0#B
Green0#B
Grey0#B
Maroon0#B
Purple0#B
#endif
