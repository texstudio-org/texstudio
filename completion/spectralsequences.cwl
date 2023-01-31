# spectralsequences package
# Matthew Bertucci 2023/01/29 for v1.3.3

#include:tikz
#include:etoolbox
#include:verbatim
#include:tikzlibraryquotes
#include:tikzlibraryfit
#include:tikzlibrarypositioning
#include:tikzlibraryintersections
#include:tikzlibrarybackgrounds
#include:tikzlibraryshapes

#ifOption:tooltip
#include:pdfcomment
\sseqtooltip{text}{tooltip text}#*
#endif

#keyvals:\usepackage/spectralsequences#c
draft
tooltips
#endkeyvals

\begin{sseqdata}#\pictureHighlight
\begin{sseqdata}[options%keyvals]
\end{sseqdata}

\begin{sseqpage}#\pictureHighlight
\begin{sseqpage}[options%keyvals]
\end{sseqpage}

\printpage
\printpage[options%keyvals]

\class(x,y)
\class[options%keyvals](x,y)

\replaceclass(x,y)
\replaceclass(x,y,n)
\replaceclass[options%keyvals](x,y)
\replaceclass[options%keyvals](x,y,n)
\replacesource
\replacesource[options%keyvals]
\replacetarget
\replacetarget[options%keyvals]

\replacestructlines
\replacestructlines(source coord)

\classoptions[options%keyvals](x,y)
\classoptions[options%keyvals](x,y,n)
\classoptions[options%keyvals](class name)#*
\classoptions[options%keyvals]

\d%<<page>%>(%<x,y%>)
\d[%<options%>]%<<page>%>(%<x,y%>)
\d%<<page>%>(%<x,y,source n,target n%>)#*
\d[%<options%>]%<<page>%>(%<x,y,source n,target n%>)#*
\d%<<page>%>(%<source coord%>)(%<target coord%>)
\d[%<options%>]%<<page>%>(%<source coord%>)(%<target coord%>)

\doptions%<<page>%>(%<x,y%>)
\doptions[%<options%>]%<<page>%>(%<x,y%>)
\doptions%<<page>%>(%<x,y,source n,target n%>)#*
\doptions[%<options%>]%<<page>%>(%<x,y,source n,target n%>)#*
\doptions%<<page>%>(%<source coord%>)(%<target coord%>)
\doptions[%<options%>]%<<page>%>(%<source coord%>)(%<target coord%>)

\kill%<<page>%>
\kill%<<page>%>[%<coord%>]

\structline
\structline[options%keyvals]
\structline(source coord)(target coord)
\structline[options%keyvals](source coord)(target coord)

\structlineoptions[options%keyvals]
\structlineoptions[options%keyvals](source coord)(target coord)

\extension
\extension[options%keyvals]
\extension(source coord)(target coord)
\extension[options%keyvals](source coord)(target coord)

\extensionoptions[options%keyvals]
\extensionoptions[options%keyvals](source coord)(target coord)

\circleclasses(source coord)(target coord)
\circleclasses[options%keyvals](source coord)(target coord)

#keyvals:\class#c,\d#c,\structline#c,\replaceclass#c,\classoptions#c,\doptions#c,\structlineoptions#c,\replacestructlines#c
xshift=%<integer%>
yshift=%<integer%>
%color
"%<text%>"
"%<text%>" %<TikZ options%>
"%<text%>"'
"%<text%>"' %<TikZ options%>
pin={%<TikZ options%>}
description
circlen=%<integer%>
newellipse
ellipse ratio=%<ratio%>
isosceles triangle
rectangle
diamond
semicircle
regular polygon
regular polygon sides=%<integer%>
minimum width=##L
minimum height=##L
minimum size=##L
inner sep=##L
outer sep=##L
name=%<node name%>
show name={%<label options%>}
tag=%<tag%>
insert=%<integer%>
offset={(%<x,y%>)}
tooltip=%<text%>
#endkeyvals

#keyvals:\classoptions#c
page=%<page%>
page=%<page%>--%<page max%>
generation=%<generation%>
generation=%<generation%>--%<generation max%>
fill
#endkeyvals

\xcoord
\ycoord

#keyvals:\d#c,\structline#c,\extension#c,\doptions#c,\structlineoptions#c,\replacestructlines#c
source anchor=%<anchor%>
target anchor=%<anchor%>
shorten >=##L
shorten <=##L
bend left=%<angle%>
bend right=%<angle%>
in=%<anchor%>
out=%<anchor%>
#endkeyvals

#keyvals:\structline#c,\structlineoptions#c
page=%<page%>
page=%<page%>--%<page max%>
dashed
#endkeyvals

#keyvals:\circleclasses#c
fit=%<coords or nodes%>
rounded rectangle
ellipse ratio=%<ratio%>
class style
permanent cycle style
transient cycle style
this page class style
differential style
struct line style
page=%<page%>
page=%<page%>--%<page max%>
#endkeyvals

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c,\path#c,\draw#c,\fill#c,\filldraw#c,\pattern#c,\shade#c,\shadedraw#c,\clip#c,\node#c,\coordinate#c,\nodepart#c
background
page constraint={%<predicate%>}
page constraint or={%<predicate%>}
class style
permanent cycle style
transient cycle style
this page class style
differential style
struct line style
#endkeyvals

\isalive(coord)
\isalive{(coord1)...(coordN)}

\sseqset{options%keyvals}

\SseqErrorToWarning%<<error name>%>#*
\begin{quiet}#*
\end{quiet}#*

\Do{iterations}{loop body}
\DoUntilOutOfBounds{loop body}
\DoUntilOutOfBoundsThenNMore{extra iterations}{loop body}
\iteration

\NewSseqCommand{macro%cmd}{args}{definition}#d
\DeclareSseqCommand{macro%cmd}{args}{definition}#d
\NewSseqGroup{macro%cmd}{args}{definition}#d
\DeclareSseqGroup{macro%cmd}{args}{definition}#d
\SseqCopyPage{macro%cmd}{spectral sequence name}{page}#d

\SseqNewFamily{family name}
\sseqnewfamily{family name}#S

\SseqParseInt{macro%cmd}{integer expr}#d
\sseqparseint{macro%cmd}{integer expr}#Sd

\SseqIfEmptyTF{expression}{true}{false}#*
\SseqIfEmptyT{expression}{true}#*
\SseqIfEmptyF{expression}{false}#*
\IfExistsTF{page}(coord){true}{false}#*
\IfExistsT{page}(coord){true}#*
\IfExistsF{page}(coord){false}#*
\IfAliveTF{page}(coord){true}{false}#*
\IfAliveT{page}(coord){true}#*
\IfAliveF{page}(coord){false}#*
\IfOutOfBoundsTF(coord){true}{false}#*
\IfOutOfBoundsT(coord){true}#*
\IfOutOfBoundsF(coord){false}#*
\IfInBoundsTF(coord){true}{false}#*
\IfInBoundsT(coord){true}#*
\IfInBoundsF(coord){false}#*
\IfValidDifferentialTF{page}(coord){true}{false}#*
\IfValidDifferentialTF{page}(coord)(target coord){true}{false}#*
\IfValidDifferentialT{page}(coord){true}#*
\IfValidDifferentialT{page}(coord)(target coord){true}#*
\IfValidDifferentialF{page}(coord){false}#*
\IfValidDifferentialF{page}(coord)(target coord){false}#*
\DrawIfValidDifferentialTF{page}(coord){true}{false}#*
\DrawIfValidDifferentialTF{page}(coord)(target coord){true}{false}#*
\DrawIfValidDifferentialTF[options]{page}(coord)(target coord){true}{false}#*
\DrawIfValidDifferentialT{page}(coord){true}#*
\DrawIfValidDifferentialT{page}(coord)(target coord){true}#*
\DrawIfValidDifferentialT[options]{page}(coord)(target coord){true}#*
\DrawIfValidDifferentialF{page}(coord){false}#*
\DrawIfValidDifferentialF{page}(coord)(target coord){false}#*
\DrawIfValidDifferentialF[options]{page}(coord)(target coord){false}#*
\DrawIfValidDifferential{page}(coord){true}#*
\DrawIfValidDifferential{page}(coord)(target coord){true}#*
\DrawIfValidDifferential[options]{page}(coord)(target coord){true}#*

\SseqNormalizeMonomial{monomial}#*
\result#*
\SseqNormalizeMonomialSetVariables{monomial}#*
\SseqAHSSNameHandler#*

\parsecoordinate{macro%cmd}(coord)#d
\getdtarget{macro%cmd}{page}(source coord)#d
\parsedifferential{page}(differential coord)
\parsedifferential{page}(differential coord)(differential target)

\nameclass{name}(coord)
\tagclass{tag}(coord)
\gettag{macro%cmd}(coord)#d

\lastx%<<n>%>
\lasty%<<n>%>
\lastclass%<<n>%>

\pushstack(coord)
\savestack
\restorestack

#keyvals:\begin{sseqdata}#c,\begin{sseqpage}#c,\sseqset#c
sseqs={%<keys%>}
change sseqs={%<keys%>}
sseq={%<keys%>}
change sseq={%<keys%>}
classes={%<keys%>}
cycles={%<keys%>}
change classes={%<keys%>}
change cycles={%<keys%>}
permanent classes={%<keys%>}
permanent cycles={%<keys%>}
change permanent classes={%<keys%>}
change permanent cycles={%<keys%>}
transient classes={%<keys%>}
transient cycles={%<keys%>}
change transient classes={%<keys%>}
change transient cycles={%<keys%>}
this page classes={%<keys%>}
this page cycles={%<keys%>}
change this page classes={%<keys%>}
change this page cycles={%<keys%>}
edges={%<keys%>}
differentials={%<keys%>}
struct lines={%<keys%>}
change edges={%<keys%>}
change differentials={%<keys%>}
change struct lines={%<keys%>}
this page struct lines={%<keys%>}
change this page struct lines={%<keys%>}
tikz primitives={%<keys%>}
change tikz primitives={%<keys%>}
labels={%<keys%>}
change labels={%<keys%>}
class labels={%<keys%>}
inner class labels={%<keys%>}
outer class labels={%<keys%>}
change class labels={%<keys%>}
change inner class labels={%<keys%>}
change outer class labels={%<keys%>}
edge labels={%<keys%>}
differential labels={%<keys%>}
struct line labels={%<keys%>}
change edge labels={%<keys%>}
change differential labels={%<keys%>}
change struct line labels={%<keys%>}
label distance=##L
above label distance=##L
below label distance=##L
left label distance=##L
right label distance=##L
above left label distance=##L
above right label distance=##L
below left label distance=##L
below right label distance=##L
run off=%<start tip%>-%<end tip%>
run off struct lines=%<start tip%>-%<end tip%>
run off differentials=%<start tip%>-%<end tip%>
class label handler=%<macro%>
class name handler=%<macro%>
class name prefix=%<prefix%>
class name postfix=%<postfix%>
name=%<sseq name%>
page=%<page%>
page=%<page%>--%<page max%>
degree={%<x degree%>}{%<y degree%>}
cohomological Serre grading
homological Serre grading
Adams grading
strict degree
lax degree
no differentials
draw differentials
no struct lines
draw struct lines
no orphan edges
draw orphan edges
class pattern=%<class pattern name%>
class placement transform={%<transform keys%>}
add class placement transform={%<transform keys%>}
math nodes#true,false
scale=%<factor%>
xscale=%<factor%>
yscale=%<factor%>
xmirror
ymirror
rotate=%<angle%>
x range={%<x min%>}{%<x max%>}
y range={%<y min%>}{%<y max%>}
range check standard
range check sideways
range check off
grid=%<grid type%>
grid color=#%color
grid step=%<integer%>
x grid step=%<integer%>
y grid step=%<integer%>
title=%<text%>
title style={%<keys%>}
x label=%<text%>
y label=%<text%>
x label style={%<keys%>}
y label style={%<keys%>}
label style={%<keys%>}
no title
draw title
no x label
no y label
no labels
draw x label
draw y label
draw labels
no x ticks
no y ticks
no ticks
draw x ticks
draw y ticks
draw ticks
x tick step=%<integer%>
y tick step=%<integer%>
tick step=%<integer%>
x tick offset=%<integer%>
y tick offset=%<integer%>
tick offset=%<integer%>
x major tick step=%<integer%>
y major tick step=%<integer%>
major tick step=%<integer%>
x minor tick step=%<integer%>
y minor tick step=%<integer%>
minor tick step=%<integer%>
x tick style={%<keys%>}
y tick style={%<keys%>}
tick style={%<keys%>}
x tick handler=%<macro%>
y tick handler=%<macro%>
tick handler=%<macro%>
x axis type=#border,center,frame,none
y axis type=#border,center,frame,none
axes type=#border,center,frame,none
no x axis
no y axis
no axes
x axis origin=%<x value%>
y axis origin=%<y value%>
x axis gap=##L
y axis gap=##L
axes gap=##L
x tick gap=##L
y tick gap=##L
x axis extend start=##L
y axis extend start=##L
x axis extend end=##L
y axis extend end=##L
x axis tail=##L
y axis tail=##L
x axis clip padding=##L
y axis clip padding=##L
right clip padding=##L
left clip padding=##L
top clip padding=##L
bottom clip padding=##L
custom clip=%<clip path%>
clip#true,false
rotate labels#true,false
#endkeyvals

#keyvals:\begin{sseqdata}#c
update existing
#endkeyvals

#keyvals:\begin{sseqpage}#c
keep changes#true,false
#endkeyvals

\SseqNewClassPattern{name}{offsets}
\sseqnewclasspattern{name}{offsets}#S
\SseqOrientationNormal
\SseqOrientationSideways
\SseqOrientationToggle

\source#S
\sourcecoord#S
\target#S
\targetcoord#S
\circleclassobjname#S
\classname#S
\coord#S
\coordnopar#S
\handledname#S
\next#S
\nodenum#S
\oldclassname#S
\page#S
\partialcoord#S
\rawindex#S
\sourcename#S
\sseqifempty#S
\sseqpower{arg1}{arg2}#S
\sseqpowerempty{arg1}{arg2}#S
\ymax#S
\ymin#S
\xmax#S
\xmin#S
