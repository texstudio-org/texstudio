# gastex package
# Matthew Bertucci 2022/06/29 for v3.0

#include:ifpdf
#include:xkeyval
#include:xifthen
#include:calc
#include:trig
#include:environ
#include:xcolor
#include:graphicx
#include:auto-pst-pdf

#keyvals:\usepackage/gastex#c
slide
paper
pdflatex#true,false
recompilepics=#auto,true,false
runs=%<number%>
crop=#on,off
#endkeyvals

\gasset{options%keyvals}

\begin{gpicture}#\picture,pictureHighlight
\begin{gpicture}(width,height)#\picture,pictureHighlight
\begin{gpicture}(width,height)(xoffset,yoffset)#\picture,pictureHighlight
\begin{gpicture}[options%keyvals]#\picture,pictureHighlight
\begin{gpicture}[options%keyvals](width,height)#\picture,pictureHighlight
\begin{gpicture}[options%keyvals](width,height)(xoffset,yoffset)#\picture,pictureHighlight
\end{gpicture}

\gsavepicture{name}
\gusepicture{name}
\gusepicture[options%keyvals]{name}

#keyvals:\gusepicture
# \usepicture specific options
frame#true,false
innerframe#true,false
ignore#true,false
showname#true,false
namefont=%<font commands%>
# \includegraphics options
alt={%<alt text%>}
bb=%<llx lly urx ury%>
bbllx=
bblly=
bburx=
bbury=
natwidth=
natheight=
hiresbb#true,false
pagebox=#mediabox,cropbox,bleedbox,trimbox,artbox
viewport=%<llx lly urx ury%>
trim=%<llx lly urx ury%>
angle=%<degrees%>
origin=
width=##L
height=##L
totalheight=##L
keepaspectratio#true,false
scale=%<factor%>
clip#true,false
draft#true,false
type=%<file type%>
ext=%<file extension%>
read=%<read-file extension%>
command=
quiet
page=%<page number%>
interpolate#true,false
decodearray={%<color array%>}
#endkeyvals

## Commands for nodes
\node(name)(x,y){label text}
\node[options%keyvals](name)(x,y){label text}
\rpnode(name)(x,y)(n,r){label text}
\rpnode[options%keyvals](name)(x,y)(n,r){label text}
\imark(node name)
\imark[options%keyvals](node name)
\fmark(node name)
\fmark[options%keyvals](node name)
\rmark(node name)
\rmark[options%keyvals](node name)
\nodelabel(node name){label text}
\nodelabel[options%keyvals](node name){label text}

## Commands for edges
\drawedge(startNode,endNode){label text}
\drawedge[options%keyvals](startNode,endNode){label text}
\drawloop(node name){label text}
\drawloop[options%keyvals](node name){label text}
\drawqbedge(startNode,x,y,endNode){label text}
\drawqbedge[options%keyvals](startNode,x,y,endNode){label text}
\drawqbpedge(startNode,sa,endNode,ea){label text}
\drawqbpedge[options%keyvals](startNode,sa,endNode,ea){label text}
\drawbcedge(startNode,xs,ys,endNode,xe,ye){label text}
\drawbcedge[options%keyvals](startNode,xs,ys,endNode,xe,ye){label text}
\drawbpedge(startNode,sa,sr,endNode,ea,er){label text}
\drawbpedge[options%keyvals](startNode,sa,sr,endNode,ea,er){label text}

## Lines and curves
\drawline(%<x1,y1%>)(%<x2,y2%>)%<...(xn,yn)%>
\drawline[%<options%>](%<x1,y1%>)(%<x2,y2%>)%<...(xn,yn)%>
\drawcurve(%<x1,y1%>)(%<x2,y2%>)%<...(xn,yn)%>
\drawcurve[%<options%>](%<x1,y1%>)(%<x2,y2%>)%<...(xn,yn)%>

## Polygons and closed curves
\drawpolygon(%<x1,y1%>)(%<x2,y2%>)%<...(xn,yn)%>
\drawpolygon[%<options%>](%<x1,y1%>)(%<x2,y2%>)%<...(xn,yn)%>
\drawccurve(%<x1,y1%>)(%<x2,y2%>)%<...(xn,yn)%>
\drawccurve[%<options%>](%<x1,y1%>)(%<x2,y2%>)%<...(xn,yn)%>

## Circles and arcs
\drawcircle(x,y,d)
\drawcircle[options%keyvals](x,y,d)
\drawarc(x,y,r,a,b)
\drawarc[options%keyvals](x,y,r,a,b)

## Rectangles, ovals and regular polygons
\drawrect(x0,y0,x1,y1)
\drawrect[options%keyvals](x0,y0,x1,y1)
\drawoval(x,y,w,h,mr)
\drawoval[options%keyvals](x,y,w,h,mr)
\drawrpolygon(x,y)(n,r)
\drawrpolygon[options%keyvals](x,y)(n,r)

## Bézier curves and snake lines
\drawqbezier(x0,y0,x1,y1,x2,y2)
\drawqbezier[options%keyvals](x0,y0,x1,y1,x2,y2)
\drawcbezier(x0,y0,x1,y1,x2,y2,x3,y3)
\drawcbezier[options%keyvals](x0,y0,x1,y1,x2,y2,x3,y3)
\drawsnake(x1,y1)(x2,y2)
\drawsnake[options%keyvals](x1,y1)(x2,y2)

## parameters
#keyvals:\gasset,\begin{gpicture},\node,\rpnode,\imark,\fmark,\rmark,\nodelabel,\drawedge,\drawloop,\drawqbedge,\drawqbpedge,\drawbcedge,\drawbpedge,\drawline,\drawcurve,\drawpolygon,\drawccurve,\drawcircle,\drawarc,\drawrect,\drawoval,\drawrpolygon,\drawqbezier,\drawcbezier,\drawsnake
AHangle=%<degrees%>
AHdist=%<number%>
AHLength=%<number%>
AHlength=%<number%>
AHnb=%<integer%>
arcPie=#y,n
arcradius=%<number%>
ATangle=%<degrees%>
ATdist=%<number%>
ATLength=%<number%>
ATlength=%<number%>
ATnb=%<integer%>
curvedepth=%<number%>
dash={%<pattern%>}{%<offset%>}
ELdist=%<number%>
ELdistC=#y,n
ELpos=%<value 0-100%>
ELside=#l,r
exo=%<number%>
ExtNL=#y,n
eyo=%<number%>
fangle=%<degrees%>
fillcolor=#%color
fillgray=%<factor%>
flength=%<number%>
frame#true,false
iangle=%<degrees%>
ilength=%<number%>
linecolor=#%color
linegray=%<factor%>
linewidth=%<number%>
loopangle=%<degrees%>
loopCW=#y,n
loopdiam=%<number%>
loopheight=%<number%>
loopwidth=%<number%>
Nadjust=%<combination of w,h,n%>
Nadjustdist=%<number%>
Nfill=#y,n
Nframe=#y,n
Nh=%<number%>
NLangle=%<degrees%>
NLdist=%<number%>
Nmarks=%<combination of i,f,r,n%>
Nmr=%<number%>
Nw=%<number%>
polyangle=%<degrees%>
rdist=%<number%>
snakeh=%<number%>
snakew=%<number%>
sxo=%<number%>
syo=%<number%>
#endkeyvals

#keyvals:\begin{gpicture}
ignore
name=%<name%>
#endkeyvals

\ifgastexslide#S
\gastexslidetrue#S
\gastexslidefalse#S

## Compatibility
\cbezier#S
\cbeziervector#S
\compatiblegastexun#S
\compatiblepspictpg#S
\drawcbezieredge#S
\drawcbeziertrans#S
\drawcircledvertex#S
\drawcurvededge#S
\drawcurvedtrans#S
\drawdisk#S
\drawfinalstate#S
\drawinitialstate#S
\drawqbezieredge#S
\drawqbeziertrans#S
\drawrepeatedstate#S
\drawstate#S
\drawtrans#S
\drawundirectedcbezieredge#S
\drawundirectedcurvededge#S
\drawundirectededge#S
\drawundirectedloop#S
\drawundirectedqbezieredge#S
\drawvector#S
\drawvertex#S
\letstate#S
\letvertex#S
\pcolor#S
\pictcolor#S
\qbeziervector#S
\setedgedecal#S
\setedgelabelskip#S
\setloopdiam#S
\setmaxbezier#S
\setnbptbezier#S
\setprecision#S
\setprofcurve#S
\setpsdash#S
\setpsgray#S
\setrepeatedstatediam#S
\setstatediam#S
\settransdecal#S
\settranslabelskip#S
\setvertexdiam#S