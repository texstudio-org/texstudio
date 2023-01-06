# curve2e package
# Matthew Bertucci 2023/01/05 for v2.2.22

#include:graphicx
#include:color
#include:pict2e

# all options passed to pict2e
#keyvals:\usepackage/curve2e#c
dvips
xdvi
dvipdf
dvipdfm
dvipdfmx
pdftex
luatex
xetex
dvipsone
dviwindo
oztex
textures
pctexps
pctex32
vtex
original
ltxarrows
pstarrows
debug
hide
#endkeyvals

\AddVect%<〈vector1〉%> and %<〈vector2〉%> to %<〈vector macro〉%>
\Arc(x1,y1)(x2,y2){angle}#/picture
\ArgOfVect%<〈vector〉%> to %<〈angle macro〉%>
\AutoGrid#/picture
\AutoGrid(coordinates)#/picture
\CbezierBetween%<〈x1,y1〉%> And %<〈x2,y2〉%> WithDirs %<〈x3,y3〉%> And %<〈x4,y4〉%> UsingDists%<dist1%> And {%<dist2%>}#/picture
\CbezierTo%<〈x1,y1〉%> WithDirs %<〈x2,y2〉%> AndDists %<〈dist1〉%> And {%<dist2%>}#*/picture
\ChangeDir<cmd>#*
\ConjVect%<〈vector〉%> to %<〈vector macro〉%>
\CopyVect%<〈vector〉%> to %<〈vector macro〉%>
\CosOf%<〈angle〉%> to %<〈control sequence〉%>
\Curve(%<x1,y1%>)(%<x2,y2%>)%<...(xN,yN)%>#/picture
\Curve(%<x1,y1%>)<%<vx1,vy1%>>(%<x2,y2%>)%<<vx2,vy2>,...(xN,yN)<vxN,vyN>%>#/picture
\Curve*(%<x1,y1%>)(%<x2,y2%>)%<...(xN,yN)%>#/picture
\Curve*(%<x1,y1%>)<%<vx1,vy1%>>(%<x2,y2%>)%<<vx2,vy2>,...(xN,yN)<vxN,vyN>%>#/picture
\CurveBetween%<〈x1,y1〉%> and %<〈x2,y2〉%> WithDirs %<〈x3,y3〉%> and {%<x4,y4%>}#/picture
\CurveEnd#*/picture
\CurveFinish#*/picture
\CurveTo%<〈x1,y1〉%> WithDir %<〈x2,y2〉%>#*/picture
\Dashline(x1,y1)(x2,y2){dash length}#/picture
\defaultlinethickness{dimension%l}
\defaultlinewidth#*
\Diam#S
\DirFromAngle%<〈angle〉%> to %<〈vector macro〉%>
\DirOfVect%<〈vector〉%> to %<〈vector macro〉%>
\DistanceAndDirOfVect%<〈vector1〉%> minus %<〈vector2〉%> to %<〈distance macro〉%> and %<〈vector macro〉%>
\DividE%<〈num1〉%> by %<〈num2〉%> to %<\macro%>#*
\Divvect{vector1}{vector2}{vector macro}
\Dotline(x1,y1)(x2,y2){dot gap}#/picture
\Dotline(x1,y1)(x2,y2){dot gap}[dot diameter]#/picture
\FillCurve#*/picture
\fillstroke#*/picture
\fpdowhile{test}{code}
\fptest{test}{true}{false}
\fpwhiledo{test}{code}
\GetCoord(cmd){x}{y}#d
\GraphGrid(coordinates)#/picture
\Integer{number}#*
\IsPolar{arg1}#*
\legenda(coordinates){formula}#/picture
\legendbox#S
\LIne(cmd)#*/picture
\MakeVectorFrom%<〈numeric macro1〉〈numeric macro2〉%> to %<〈vector macro1〉%>
\ModAndAngleOfVect%<〈vector〉%> to %<〈modulus macro〉%> and %<〈angle macro〉%>
\ModAndDirOfVect%<〈vector〉%> to %<〈modulus macro〉%> and %<〈vector macro〉%>
\ModDirDot#*
\ModOfVect%<〈vector〉%> to %<〈modulus macro〉%>
\MultiplY%<〈num1〉%> by %<〈num2〉%> to %<\macro%>#*
\Multvect{vector1}*{vector2}*{vector macro}
\Multvect{vector1}*{vector2}{vector macro}
\Multvect{vector1}{vector2}*{vector macro}
\Multvect{vector1}{vector2}{vector macro}
\NumA#S
\Numero{cmd}{dimen}#*d
\PbDim#*
\Pbox(coordinates)[position]{formula}#*/picture
\Pbox(coordinates)[position]{formula}*#*/picture
\Pbox(coordinates)[position]{formula}*<angle>#*/picture
\Pbox(coordinates)[position]{formula}[dot diameter]#/picture
\Pbox(coordinates)[position]{formula}[dot diameter]*#/picture
\Pbox(coordinates)[position]{formula}[dot diameter]*<angle>#/picture
\Pbox(coordinates)[position]{formula}[dot diameter]<angle>#/picture
\Pbox(coordinates)[position]{formula}<angle>#*/picture
\Pbox(coordinates){formula}#/picture
\Pbox(coordinates){formula}*#/picture
\Pbox(coordinates){formula}*<angle>#/picture
\Pbox(coordinates){formula}[dot diameter]#*/picture
\Pbox(coordinates){formula}[dot diameter]*#*/picture
\Pbox(coordinates){formula}[dot diameter]*<angle>#*/picture
\Pbox(coordinates){formula}[dot diameter]<angle>#*/picture
\Pbox(coordinates){formula}<angle>#/picture
\Qurve(%<x1,y1%>)(%<x2,y2%>)%<...(xN,yN)%>#/picture
\Qurve(%<x1,y1%>)<%<vx1,vy1%>>(%<x2,y2%>)%<<vx2,vy2>,...(xN,yN)<vxN,vyN>%>#/picture
\Qurve*(%<x1,y1%>)(%<x2,y2%>)%<...(xN,yN)%>#/picture
\Qurve*(%<x1,y1%>)<%<vx1,vy1%>>(%<x2,y2%>)%<<vx2,vy2>,...(xN,yN)<vxN,vyN>%>#/picture
\QurveTo%<〈x1,y1〉%> WithDir %<〈x2,y2〉%>#*/picture
\Rapp#S
\RoundUp%<〈num1〉%> modulo %<〈num2〉%> to %<\macro%>#*
\ScaleVect%<〈vector〉%> by %<〈scaling factor〉%> to %<〈angle macro〉%>
\segment(x1,y1)(x2,y2)#/picture
\Segno#S
\SinOf%<〈angle〉%> to %<〈control sequence〉%>
\SplitCartesian(x,y){xmacro%cmd}{ymacro%cmd}#*d
\SplitPolar(angle:radius){anglemacro%cmd}{radiusmacro%cmd}#*d
\StartCurveAt%<〈x1,y1〉%> WithDir %<〈x2,y2〉%>#*/picture
\SubVect%<〈vector1〉%> from %<〈vector2〉%> to %<〈vector macro〉%>
\TROF#*
\TRON#*
\VECTOR(x1,y1)(x2,y2)#/picture
\VectorArc(x1,y1)(x2,y2){angle}#/picture
\VectorARC(x1,y1)(x2,y2){angle}#/picture
\VVECTOR(x1,y1)(x2,y2)#/picture
\VVectorArc(x1,y1)(x2,y2){angle}#*/picture
\xmultiput(x,y)(Δx,Δy){copies}{object}#/picture
\xmultiput[center](x,y)(Δx,Δy){copies}{object}#/picture
\XpartOfVect%<〈vector〉%> to %<〈macro〉%>
\YpartOfVect%<〈vector〉%> to %<〈macro〉%>
\Zbox(coordinates)[position]{formula}#/picture
\Zbox(coordinates)[position]{formula}[dot diameter]#/picture
\Zbox(coordinates){formula}#/picture
\Zbox(coordinates){formula}[dot diameter]#/picture

# deprecated
\DivideFN#S
\DivVect#S
\Dline(x1,y1)(x2,y2){dash length}#S
\MultiplyFN#S
\MultVect#S
\originalcurveto#S
\originallineto#S
\originalmoveto#S
\originalput#S
