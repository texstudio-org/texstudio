# dynkin-diagrams package
# Matthew Bertucci 2023/05/18 for 3.14159265358979323

#include:tikz
#include:xstring
#include:etoolbox
#include:pgfkeys
#include:pgfopts
#include:amsmath
#include:amssymb
#include:mathtools
#include:tikzlibrarybackgrounds
#include:tikzlibrarycalc
#include:tikzlibrarydecorations.markings
#include:tikzlibrarydecorations.pathreplacing
#include:tikzlibrarydecorations.pathmorphing
#include:tikzlibraryfit
#include:tikzlibrarypatterns
#include:tikzlibraryshadows

\dynkin{%<letter%>}{%<rank%>}
\dynkin{%<letter%>}[%<twisted rank%>]{%<rank%>}
\dynkin[%<options%>]{%<letter%>}{%<rank%>}
\dynkin[%<options%>]{%<letter%>}[%<twisted rank%>]{%<rank%>}
\begin{dynkinDiagram}{%<letter%>}{%<rank%>}#\pictureHighlight
\begin{dynkinDiagram}{%<letter%>}[%<twisted rank%>]{%<rank%>}#\pictureHighlight
\begin{dynkinDiagram}[%<options%>]{%<letter%>}{%<rank%>}#\pictureHighlight
\begin{dynkinDiagram}[%<options%>]{%<letter%>}[%<twisted rank%>]{%<rank%>}#\pictureHighlight
\end{dynkinDiagram}
\dynkinName{%<letter%>}{%<rank%>}#*
\dynkinName{%<letter%>}[%<twisted rank%>]{%<rank%>}#*
\dynkinName[%<options%>]{%<letter%>}{%<rank%>}#*
\dynkinName[%<options%>]{%<letter%>}[%<twisted rank%>]{%<rank%>}#*

#keyvals:\dynkin#c,\begin{dynkinDiagram}#c,\pgfkeys#c,\tikzset#c,\dynkinName#c
*/.style={%<style specs%>}
affine mark=#o,O,*,t,x,X
arrow shape/.style={%<style specs%>}
arrow style={%<style specs%>}
arrow width=##L
arrows#true,false
at=(%<node%>)
backwards
bird arrow
Bourbaki arrow
ceref
Coxeter
double edges
double fold
double fold left
double fold right
double left
double right
edge label/.style={%<style specs%>}
edge length=##L
edge/.style={%<style specs%>}
extended
fold
fold left
fold left style/.style={%<style specs%>}
fold radius=##L
fold right
fold right style/.style={%<style specs%>}
fold style/.style={%<style specs%>}
gonality=%<math%>
horizontal shift=##L
indefinite edge/.style={%<style specs%>}
indefinite edge=
indefinite edge ratio=%<number%>
involution/.style={%<style specs%>}
involutions={%<inv1;inv2;...%>}
Kac
Kac arrows
label
label depth=%<label text%>
label directions={%<dir1,dir2,...%>}
label height=%<label text%>
label macro*/.code={%<code%>}
label macro/.code={%<code%>}
label* directions={%<dir1,dir2,...%>}
labels*={%<label list%>}
labels={%<label list%>}
make indefinite edge/.list={%<i1-j1,i2-j2,...%>}
make indefinite edge={%<i-j%>}
mark=#o,O,*,t,x,X
name=%<name%>
o/.append style={%<style specs%>}
o/.style={%<style specs%>}
O/.style={%<style specs%>}
odd
ordering=#Kac,Dynkin,Adams,Bourbaki,Carter
parabolic=%<integer%>
ply=#0,1,2,3,4
reverse arrows
root radius=##L
separator length=##L
scale=%<factor%>
t/.style={%<style specs%>}
text style/.style={%<style specs%>}
text style={%<style specs%>}
upside down
vertical shift=##L
x/.style={%<style specs%>}
X/.style={%<style specs%>}
#endkeyvals

#keyvals:\pgfkeys#c,\tikzset#c
/Dynkin diagram
#endkeyvals

\dynkins{spec}
\begin{DynkinDiagrams}{spec}
\end{DynkinDiagrams}

\dynkinFold{start}{end}
\dynkinFold[TikZ keys]{start}{end}
\drlap{arg}
\dynkinBrace{start}{end}
\dynkinBrace[label%formula]{start}{end}
\dynkinBrace*{start}{end}
\dynkinBrace*[label%formula]{start}{end}
\dynkinTripleEdge{root1}{root2}
\dynkinTripleEdge[TikZ keys]{root1}{root2}
\dynkinTripleEdge*{root1}{root2}
\dynkinTripleEdge*[TikZ keys]{root1}{root2}
\dynkinQuadrupleEdge{root1}{root2}
\dynkinQuadrupleEdge[TikZ keys]{root1}{root2}
\dynkinQuadrupleEdge*{root1}{root2}
\dynkinQuadrupleEdge*[TikZ keys]{root1}{root2}
\dynkinDefiniteDoubleEdge{root1}{root2}
\dynkinDefiniteDoubleEdge[TikZ keys]{root1}{root2}
\dynkinDefiniteDoubleEdge*{root1}{root2}
\dynkinDefiniteDoubleEdge*[TikZ keys]{root1}{root2}

# not documented
\Adynkin#*
\Bdynkin#*
\braceYshift#S
\Cdynkin#*
\centerarc[TikZ keys](center)(initangle:finalangle:radius)#*
\convertRootNumber{n}#*
\convertRootPair{root1}{root2}#*
\currentDynkinOrdering#*
\Ddynkin#*
\defaultpgflinewidth#*
\DfourPly#*
\Dir#S
\distance#S
\DOneFourFourPly#*
\DthreePly#*
\dynkinCrossRootMark*[TikZ keys]{root}#*
\dynkinCrossRootMark*{root}#*
\dynkinCrossRootMark[TikZ keys]{root}#*
\dynkinCrossRootMark{root}#*
\dynkinDefiniteDoubleDownLeftArc*[TikZ keys]{root1}{root2}#*
\dynkinDefiniteDoubleDownLeftArc*{root1}{root2}#*
\dynkinDefiniteDoubleDownLeftArc[TikZ keys]{root1}{root2}#*
\dynkinDefiniteDoubleDownLeftArc{root1}{root2}#*
\dynkinDefiniteDoubleDownRightArc*[TikZ keys]{root1}{root2}#*
\dynkinDefiniteDoubleDownRightArc*{root1}{root2}#*
\dynkinDefiniteDoubleDownRightArc[TikZ keys]{root1}{root2}#*
\dynkinDefiniteDoubleDownRightArc{root1}{root2}#*
\dynkinDefiniteDoubleDownRightSemiCircle*[TikZ keys]{root1}{root2}#*
\dynkinDefiniteDoubleDownRightSemiCircle*{root1}{root2}#*
\dynkinDefiniteDoubleDownRightSemiCircle[TikZ keys]{root1}{root2}#*
\dynkinDefiniteDoubleDownRightSemiCircle{root1}{root2}#*
\dynkinDefiniteDoubleLeftDownArc*[TikZ keys]{root1}{root2}#*
\dynkinDefiniteDoubleLeftDownArc*{root1}{root2}#*
\dynkinDefiniteDoubleLeftDownArc[TikZ keys]{root1}{root2}#*
\dynkinDefiniteDoubleLeftDownArc{root1}{root2}#*
\dynkinDefiniteDoubleLeftUpArc*[TikZ keys]{root1}{root2}#*
\dynkinDefiniteDoubleLeftUpArc*{root1}{root2}#*
\dynkinDefiniteDoubleLeftUpArc[TikZ keys]{root1}{root2}#*
\dynkinDefiniteDoubleLeftUpArc{root1}{root2}#*
\dynkinDefiniteDoubleRightDownArc*[TikZ keys]{root1}{root2}#*
\dynkinDefiniteDoubleRightDownArc*{root1}{root2}#*
\dynkinDefiniteDoubleRightDownArc[TikZ keys]{root1}{root2}#*
\dynkinDefiniteDoubleRightDownArc{root1}{root2}#*
\dynkinDefiniteDoubleRightUpArc*[TikZ keys]{root1}{root2}#*
\dynkinDefiniteDoubleRightUpArc*{root1}{root2}#*
\dynkinDefiniteDoubleRightUpArc[TikZ keys]{root1}{root2}#*
\dynkinDefiniteDoubleRightUpArc{root1}{root2}#*
\dynkinDefiniteDoubleUpLeftArc*[TikZ keys]{root1}{root2}#*
\dynkinDefiniteDoubleUpLeftArc*{root1}{root2}#*
\dynkinDefiniteDoubleUpLeftArc[TikZ keys]{root1}{root2}#*
\dynkinDefiniteDoubleUpLeftArc{root1}{root2}#*
\dynkinDefiniteDoubleUpRightArc*[TikZ keys]{root1}{root2}#*
\dynkinDefiniteDoubleUpRightArc*{root1}{root2}#*
\dynkinDefiniteDoubleUpRightArc[TikZ keys]{root1}{root2}#*
\dynkinDefiniteDoubleUpRightArc{root1}{root2}#*
\dynkinDefiniteDoubleUpRightSemiCircle*[TikZ keys]{root1}{root2}#*
\dynkinDefiniteDoubleUpRightSemiCircle*{root1}{root2}#*
\dynkinDefiniteDoubleUpRightSemiCircle[TikZ keys]{root1}{root2}#*
\dynkinDefiniteDoubleUpRightSemiCircle{root1}{root2}#*
\dynkinDefiniteLeftDownArc*[TikZ keys]{root1}{root2}#*
\dynkinDefiniteLeftDownArc*{root1}{root2}#*
\dynkinDefiniteLeftDownArc[TikZ keys]{root1}{root2}#*
\dynkinDefiniteLeftDownArc{root1}{root2}#*
\dynkinDefiniteLeftUpArc*[TikZ keys]{root1}{root2}#*
\dynkinDefiniteLeftUpArc*{root1}{root2}#*
\dynkinDefiniteLeftUpArc[TikZ keys]{root1}{root2}#*
\dynkinDefiniteLeftUpArc{root1}{root2}#*
\dynkinDefiniteRightDownArc*[TikZ keys]{root1}{root2}#*
\dynkinDefiniteRightDownArc*{root1}{root2}#*
\dynkinDefiniteRightDownArc[TikZ keys]{root1}{root2}#*
\dynkinDefiniteRightDownArc{root1}{root2}#*
\dynkinDefiniteRightUpArc*[TikZ keys]{root1}{root2}#*
\dynkinDefiniteRightUpArc*{root1}{root2}#*
\dynkinDefiniteRightUpArc[TikZ keys]{root1}{root2}#*
\dynkinDefiniteRightUpArc{root1}{root2}#*
\dynkinDefiniteSemiCircle*[TikZ keys]{root1}{root2}#*
\dynkinDefiniteSemiCircle*{root1}{root2}#*
\dynkinDefiniteSemiCircle[TikZ keys]{root1}{root2}#*
\dynkinDefiniteSemiCircle{root1}{root2}#*
\dynkinDefiniteSingleEdge*[TikZ keys]{root1}{root2}#*
\dynkinDefiniteSingleEdge*{root1}{root2}#*
\dynkinDefiniteSingleEdge[TikZ keys]{root1}{root2}#*
\dynkinDefiniteSingleEdge{root1}{root2}#*
\dynkinDefiniteTripleDownRightSemiCircle*[TikZ keys]{root1}{root2}#*
\dynkinDefiniteTripleDownRightSemiCircle*{root1}{root2}#*
\dynkinDefiniteTripleDownRightSemiCircle[TikZ keys]{root1}{root2}#*
\dynkinDefiniteTripleDownRightSemiCircle{root1}{root2}#*
\dynkinDoubleHollowRootMark*[TikZ keys]{root}#*
\dynkinDoubleHollowRootMark*{root}#*
\dynkinDoubleHollowRootMark[TikZ keys]{root}#*
\dynkinDoubleHollowRootMark{root}#*
\dynkinDrawCrossRootMark[TikZ keys]{name}#*
\dynkinDrawCrossRootMark{name}#*
\dynkinDrawSolidRootMark[TikZ keys]{root}#*
\dynkinDrawSolidRootMark{root}#*
\dynkinEast#*
\dynkinEast*#*
\dynkinEdge*[TikZ keys]{type}{root1}{root2}#*
\dynkinEdge*{type}{root1}{root2}#*
\dynkinEdge[TikZ keys]{type}{root1}{root2}#*
\dynkinEdge{type}{root1}{root2}#*
\dynkinEdgeArrow*[TikZ keys]{root1}{root2}#*
\dynkinEdgeArrow*{root1}{root2}#*
\dynkinEdgeArrow[TikZ keys]{root1}{root2}#*
\dynkinEdgeArrow{root1}{root2}#*
\dynkinEdgeLabel{root1}{root2}{label text%formula}#*
\dynkinHeavyCrossRootMark*[TikZ keys]{root}#*
\dynkinHeavyCrossRootMark*{root}#*
\dynkinHeavyCrossRootMark[TikZ keys]{root}#*
\dynkinHeavyCrossRootMark{root}#*
\dynkinHollowRootMark*[TikZ keys]{root}#*
\dynkinHollowRootMark*{root}#*
\dynkinHollowRootMark[TikZ keys]{root}#*
\dynkinHollowRootMark{root}#*
\dynkinIndefiniteLeftDownArc*[TikZ keys]{root1}{root2}#*
\dynkinIndefiniteLeftDownArc*{root1}{root2}#*
\dynkinIndefiniteLeftDownArc[TikZ keys]{root1}{root2}#*
\dynkinIndefiniteLeftDownArc{root1}{root2}#*
\dynkinIndefiniteLeftUpArc*[TikZ keys]{root1}{root2}#*
\dynkinIndefiniteLeftUpArc*{root1}{root2}#*
\dynkinIndefiniteLeftUpArc[TikZ keys]{root1}{root2}#*
\dynkinIndefiniteLeftUpArc{root1}{root2}#*
\dynkinIndefiniteRightDownArc*[TikZ keys]{root1}{root2}#*
\dynkinIndefiniteRightDownArc*{root1}{root2}#*
\dynkinIndefiniteRightDownArc[TikZ keys]{root1}{root2}#*
\dynkinIndefiniteRightDownArc{root1}{root2}#*
\dynkinIndefiniteRightUpArc*[TikZ keys]{root1}{root2}#*
\dynkinIndefiniteRightUpArc*{root1}{root2}#*
\dynkinIndefiniteRightUpArc[TikZ keys]{root1}{root2}#*
\dynkinIndefiniteRightUpArc{root1}{root2}#*
\dynkinIndefiniteSemiCircle*[TikZ keys]{root1}{root2}#*
\dynkinIndefiniteSemiCircle*{root1}{root2}#*
\dynkinIndefiniteSemiCircle[TikZ keys]{root1}{root2}#*
\dynkinIndefiniteSemiCircle{root1}{root2}#*
\dynkinIndefiniteSingleEdge*[TikZ keys]{root1}{root2}#*
\dynkinIndefiniteSingleEdge*{root1}{root2}#*
\dynkinIndefiniteSingleEdge[TikZ keys]{root1}{root2}#*
\dynkinIndefiniteSingleEdge{root1}{root2}#*
\dynkinIndefiniteSymbol{symbol}#*
\dynkinKacDoubleArrow[TikZ keys]{root1}{root2}#*
\dynkinKacDoubleArrow{root1}{root2}#*
\dynkinKacQuadrupleArrow[TikZ keys]{root1}{root2}#*
\dynkinKacQuadrupleArrow{root1}{root2}#*
\dynkinKacTripleArrow[TikZ keys]{root1}{root2}#*
\dynkinKacTripleArrow{root1}{root2}#*
\dynkinLabelRoot*{root}{label}#*
\dynkinLabelRoot{root}{label}#*
\dynkinLeftFold*[TikZ keys]{root1}{root2}#*
\dynkinLeftFold*{root1}{root2}#*
\dynkinLeftFold[TikZ keys]{root1}{root2}#*
\dynkinLeftFold{root1}{root2}#*
\dynkinMoveToRoot*{n}#*
\dynkinMoveToRoot{n}#*
\dynkinNorth#*
\dynkinNorth*#*
\dynkinNorthEast#*
\dynkinNorthEast*#*
\dynkinNorthWest#*
\dynkinNorthWest*#*
\dynkinOrder#*
\dynkinOrderFromBourbaki{series}{rank}{root}{to order}{count}#*
\dynkinOrderToBourbaki{series}{rank}{from order}{root}{count}#*
\dynkinOverrideRoot#*
\dynkinPlaceRootHere*{n}{L}{L*}#*
\dynkinPlaceRootHere{n}{L}{L*}#*
\dynkinPlaceRootRelativeTo*{root1}{root2}{dir}{L}{L*}#*
\dynkinPlaceRootRelativeTo{root1}{root2}{dir}{L}{L*}#*
\dynkinPrintLabels#*
\dynkinPrintLabelsStar#*
\dynkinPutLabelInDirection*{root}{val 0-7}#*
\dynkinPutLabelInDirection{root}{val 0-7}#*
\dynkinRefreshRoots#*
\dynkinRightFold*[TikZ keys]{root1}{root2}#*
\dynkinRightFold*{root1}{root2}#*
\dynkinRightFold[TikZ keys]{root1}{root2}#*
\dynkinRightFold{root1}{root2}#*
\dynkinRootMark*{mark style}{root}#*
\dynkinRootMark{mark style}{root}#*
\dynkinSkip#*
\dynkinSolidRootMark*[TikZ keys]{root}#*
\dynkinSolidRootMark*{root}#*
\dynkinSolidRootMark[TikZ keys]{root}#*
\dynkinSolidRootMark{root}#*
\dynkinSouth#*
\dynkinSouth*#*
\dynkinSouthEast#*
\dynkinSouthEast*#*
\dynkinSouthEastFold#*
\dynkinSouthFold#*
\dynkinSouthWest#*
\dynkinSouthWest*#*
\dynkinSouthWestFold#*
\dynkinTensorRootMark*[TikZ keys]{root}#*
\dynkinTensorRootMark*{root}#*
\dynkinTensorRootMark[TikZ keys]{root}#*
\dynkinTensorRootMark{root}#*
\dynkinWest#*
\dynkinWest*#*
\Edynkin#*
\ESixThreePly#*
\ESixTwoPly#*
\extendedAdynkin#*
\extendedBdynkin#*
\extendedBthreePly#*
\extendedCdynkin#*
\extendedDdynkin#*
\extendedDthreePly#*
\extendedEdynkin#*
\extendedESevenFolded#*
\extendedFdynkin#*
\extendedGdynkin#*
\extendedHdynkin#*
\extendedIdynkin#*
\Fdynkin#*
\forDynkinSemicolonsvlist{macro}{item1;item2;...}#*
\Gdynkin#*
\Hdynkin#*
\Idynkin#*
\LL#S
\pipebmo#*
\pipefpo#*
\regurgitate{arg}#*
\repeatCharacter{n}{string}#*
\replacementLeftString#*
\replacementN#*
\replacementRightString#*
\replaceNthChar{string}{N}{char}#*
\replaceNthCounter#*
\series#S
\stringCharacterInPosition{string}{n}#*
\swapRootIfInLastTwoRoots{root}#*
\tempDynkinReorder#S
\testbit{n}{b}#*
\thedynkinRootNo#*
\twistedAdynkin#*
\twistedDdynkin#*
\twistedDTwo#*
\twistedEdynkin#*
\typeDynkinOrder#*
\xd#S
\yd#S
\yfp#S
\yj#S
\yjj#S
\yyyy#S
