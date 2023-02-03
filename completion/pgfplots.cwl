# mode: pgfplots.sty
# denisbitouze, 26.03.2017
# muzimuzhi, 9 Aug 2019 and 17 Dec 2019
# Matthew Bertucci 12/21/2021 for v1.18.1

### Dependency Tree ###
# pgfplots.sty
# ├── graphicx.sty
# ├── tikz.sty
# ├── pgfplots.revision.tex
# ├── tikzlibraryplotmarks.code.tex
# └── pgfplots.code.tex
#     ├── pgfplotscore.code.tex
#     │   └── pgfplotssysgeneric.code.tex
#     ├── pgfplotslibrary.code.tex
#     ├── pgfplotsoldpgfsupp_loader.code.tex
#     ├── pgfplotsutil.code.tex
#     │   ├── pgfplotsliststructure.code.tex
#     │   ├── pgfplotsliststructureext.code.tex
#     │   ├── pgfplotsarray.code.tex
#     │   ├── pgfplotsmatrix.code.tex
#     │   ├── pgfplotstableshared.code.tex
#     │   ├── pgfplotsdeque.code.tex
#     │   ├── pgfplotsbinary.code.tex
#     │   │   └── pgfplotsbinary.data.code.tex
#     │   ├── pgfplotsutil.verb.code.tex
#     │   └── pgflibrarypgfplots.surfshading.code.tex
#     ├── pgfplotscolormap.code.tex
#     │   └── pgfplotscolor.code.tex
#     ├── pgfplotsstackedplots.code.tex
#     ├── pgfplotsplothandlers.code.tex
#     │   └── pgfplotsmeshplothandler.code.tex
#     │       └── pgfplotsmeshplotimage.code.tex
#     ├── pgfplots.scaling.code.tex
#     ├── pgfplotscoordprocessing.code.tex
#     ├── pgfplots.errorbars.code.tex
#     ├── pgfplots.markers.code.tex
#     ├── pgfplotsticks.code.tex
#     ├── pgfplots.paths.code.tex
#     ├── tikzlibrarydecorations.code.tex
#     ├── tikzlibrarydecorations.pathmorphing.code.tex
#     ├── tikzlibrarydecorations.pathreplacing.code.tex
#     └── tikzlibrarypgfplots.contourlua.code.tex

#include:graphicx
#include:tikz
#include:tikzlibraryplotmarks
#include:tikzlibrarydecorations
#include:tikzlibrarydecorations.pathmorphing
#include:tikzlibrarydecorations.pathreplacing

### Main commands ###
\begin{axis}#/tikzpicture
\begin{axis}[options%keyvals]#/tikzpicture
\end{axis}
\begin{loglogaxis}#/tikzpicture
\begin{loglogaxis}[options%keyvals]#/tikzpicture
\end{loglogaxis}
\begin{semilogxaxis}#/tikzpicture
\begin{semilogxaxis}[options%keyvals]#/tikzpicture
\end{semilogxaxis}
\begin{semilogyaxis}#/tikzpicture
\begin{semilogyaxis}[options%keyvals]#/tikzpicture
\end{semilogyaxis}

\addplot {%<input data%>};#/axis,semilogxaxis,semilogyaxis,loglogaxis,groupplot,polaraxis,smithchart,ternaryaxis
\addplot[%<options%>] {%<input data%>} %<<trailing path commands>%>;
\addplot3 {%<input data%>};#/axis,semilogxaxis,semilogyaxis,loglogaxis,groupplot,polaraxis,smithchart,ternaryaxis
\addplot3[%<options%>] {%<input data%>} %<<trailing path commands>%>;
\addplot+ {%<input data%>};#/axis,semilogxaxis,semilogyaxis,loglogaxis,groupplot,polaraxis,smithchart,ternaryaxis
\addplot+[%<options%>] {%<input data%>} %<<trailing path commands>%>;#/axis,semilogxaxis,semilogyaxis,loglogaxis,groupplot,polaraxis,smithchart,ternaryaxis

\pgfplotsset{options%keyvals}

### Keys ###
#keyvals:\begin{axis}#c,\begin{loglogaxis}#c,\begin{semilogxaxis}#c,\begin{semilogyaxis}#c,\addplot#c,\addplot3#c,\addplot+#c,\pgfplotsset#c,\begin{groupplot}#c,\nextgroupplot#c,\begin{smithchart}#c,\begin{polaraxis}#c,\begin{ternaryaxis}#c
## Main pgfplots and tikz keys ##
compat=#1.18,1.17,1.16,1.15,1.14,1.13,1.12,1.11,1.10,1.9,1.8,1.7,1.6,1.5.1,1.5,1.4,1.3,pre 1.3,default
empty line=#auto,none,scanline,jump
domain=%<x1:x2%>
y domain=%<y1:y2%>
domain y=%<y1:y2%>
samples=%<number%>
samples y=%<number%>
samples at={%<coord list%>}
variable=%<variable name%>
variable y=%<variable name%>
trig format plots=#default,deg,rad
trig format=#deg,rad
translate gnuplot#true,false
parametric#true,false
id=%<id%>
prefix=%<filename prefix%>
raw gnuplot
sharp plot
smooth
tension=%<tension%>
const plot
const plot mark left
const plot mark right
const plot mark mid
jump mark left
jump mark right
jump mark mid
xbar
bar shift auto
bar shift auto=%<shift for multiple plots%>
ybar
bar width=##L
bar shift=##L
bar direction=#auto,x,y
ybar interval
ybar interval=%<relative width%>
xbar interval
xbar interval=%<relative width%>
xcomb
ycomb
quiver={%<quiver options%>}
stack plots=#x,y,false
ybar stacked
ybar stacked=#plus,minus
xbar stacked
xbar stacked=#plus,minus
stack dir=#plus,minus
reverse stacked plots#true,false
stacked ignores zero#true,false
xbar interval stacked
xbar interval stacked=#plus,minus
ybar interval stacked
ybar interval stacked=#plus,minus
stack negative=#on previous,separate
area style
only marks
scatter
scatter src=#none,x,y,z,f(x),explicit,explicit symbolic,%<expression%>
scatter/use mapped color={%<options for each marker%>}
scatter/classes={%<styles for each class name%>}
nodes near coords
nodes near coords={%<content%>}
nodes near coords*
nodes near coords*={%<content%>}
nodes near coords style={%<options%>}
node near coords style={%<options%>}
node near coord style={%<options%>}
nodes near coords align=#auto,horizontal,vertical
coordinate style/.condition={%<expression%>}{%<options%>}
coordinate style/.from={%<options%>}
coordinate style/.clear
scatter/position=#absolute,relative
scatter/@pre marker code/.code={%<code%>}
scatter/@post marker code/.code={%<code%>}
mesh
unbounded coords=#discard,jump
mesh/rows=%<integer%>
mesh/cols=%<integer%>
mesh/scanline verbose#true,false
mesh/ordering=#x varies,y varies,rowwise,colwise
mesh/check=#false,warning,error
z buffer=#default,none,auto,sort,reverse x seq,reverse y seq,reverse xy seq
surf
shader=#flat,interp,faceted,flat corner,flat mean,faceted interp
faceted color=#%color
mesh/interior colormap={%<map name%>}{%<colormap spec%>}
mesh/interior colormap name=%<map name%>
mesh/interior colormap thresh=%<number%>
surf shading/precision=#pdf,postscript,ps
mesh/color input=#colormap,explicit,explicit mathparse
mesh/colorspace explicit color input=#rgb,rgb255,cmy,cmyk,cmyk255,gray,wave,hsb,Hsb,HTML
mesh/colorspace explicit color output=#rgb,cmyk,gray
contour lua={%<contour options%>}
contour gnuplot={%<contour options%>}
contour prepared={%<contour options%>}
contour prepared format=#standard,matlab
contour external={%<contour options%>}
contour filled={%<contour options%>}
matrix plot
matrix plot*
imagesc
imagesc*
patch
patch table={%<file or inline table%>}
patch table with point meta={%<file or inline table%>}
patch table with individual point meta={%<file or inline table%>}
mesh input=#lattice,patches,image
patch type=#default,rectangle,triangle,line
mark size=##L
mark=#*,x,+,-,|,o,asterisk,star,10-pointed star,oplus,oplus*,otimes,otimes*,square,square*,triangle,triangle*,diamond,diamond*,halfdiamond,halfdiamond*,halfsquare,halfsquare*,halfsquare right,halfsquare right*,halfsquare left,halfsquare left*,Mercedes star,Mercedes star flipped,halfcircle,halfcircle*,pentagon,pentagon*,ball,text,cube,cube*
cube/size x=##L
cube/size y=##L
cube/size z=##L
no markers
mark repeat=%<integer%>
mark phase=%<integer%>
mark indices={%<index list%>}
mark color=#%color
mark options={%<options%>}
solid
dotted
densely dotted
loosely dotted
dashed
densely dashed
loosely dashed
dashdotted
densely dashdotted
loosely dashdotted
dashdotdotted
densely dashdotdotted
loosely dashdotdotted
line cap=#round,rect,butt
line join=#round,bevel,miter
miter limit=%<factor%>
font={%<font commands%>}
line width=##L
thin
ultra thin
very thin
semithick
thick
very thick
ultra thick
%color
color=#%color
draw=#%color
fill=#%color
colormap name=%<map name%>
colormap={%<map name%>}{%<colormap spec%>}
colormap default colorspace=#auto,gray,rgb,cmyk
color of colormap=%<value%>
color of colormap=%<value%> of %<map name%>
index of colormap=%<index%>
index of colormap=%<index%> of %<map name%>
const color of colormap=%<value%>
const color of colormap=%<value%> of %<map name%>
cycle list={%<list%>}
cycle list name=%<name%>
mark list fill=#%color
cycle list shift=%<integer%>
cycle multi list={%<<list1> \nextlist <list2>...%>}
cycle multiindex list={%<<list1> \nextlist <list2>...%>}
cycle multiindex* list={%<<list1> \nextlist <list2>...%>}
point meta=#none,x,y,z,f(x),explicit,explicit symbolic,%<expression%>
set point meta if empty=#none,x,y,z,f(x),explicit,explicit symbolic,%<expression%>
point meta rel=#axis wide,per plot
point meta min=%<number%>
point meta max=%<number%>
colormap access=#map,direct,const,piecewise constant,piecewise const,piecewise linear
near ticklabel align=#inside,center,outside
near ticklabel at={%<coord%>}
sloped like x axis
sloped like y axis
sloped like z axis
sloped like x axis={%<options%>}
sloped like y axis={%<options%>}
sloped like z axis={%<options%>}
xlabel=%<text%>
ylabel=%<text%>
zlabel=%<text%>
xlabel shift=##L
ylabel shift=##L
zlabel shift=##L
label shift=##L
title=%<text%>
extra description/.code={%<code%>}
legend entries={%<list%>}
legend style={%<options%>}
legend pos=#south west,south east,north west,north east,outer north east
legend cell align=#left,right,center
legend columns
legend columns=%<number%>
legend plot pos=#left,right,none
legend image post style={%<options%>}
legend image code/.code={%<code%>}
line legend
empty legend
area legend
xbar legend
ybar legend
zbar legend
xbar interval legend
ybar interval legend
zbar interval legend
mesh legend
reverse legend#true,false
legend reversed#true,false
transpose legend#true,false
legend transposed#true,false
invoke before crossref tikzpicture={%<code%>}
invoke after crossref tikzpicture={%<code%>}
legend to name=##l
axis x line=#box,top,middle,center,bottom,none
axis x line*=#box,top,middle,center,bottom,none
axis y line=#box,left,middle,center,right,none
axis y line*=#box,left,middle,center,right,none
axis z line=#box,left,middle,center,right,none
axis z line*=#box,left,middle,center,right,none
axis lines=#box,left,middle,center,right,none
axis lines*=#box,left,middle,center,right,none
axis line style={%<options%>}
inner axis line style={%<options%>}
outer axis line style={%<options%>}
x axis line style={%<options%>}
y axis line style={%<options%>}
z axis line style={%<options%>}
separate axis lines#true,false
axis x line shift=##L
axis y line shift=##L
axis z line shift=##L
axis line shift=##L
axis x discontinuity=#crunch,parallel,none
axis y discontinuity=#crunch,parallel,none
axis z discontinuity=#crunch,parallel,none
xtickmin=%<coord%>
ytickmin=%<coord%>
ztickmin=%<coord%>
xtickmax=%<coord%>
ytickmax=%<coord%>
ztickmax=%<coord%>
hide x axis#true,false
hide y axis#true,false
hide z axis#true,false
hide axis#true,false
colorbar#true,false
colorbar right
colorbar left
colorbar horizontal
colorbar source#true,false
colorbar style={%<options%>}
colorbar/width=##L
colorbar/draw/.code={%<code%>}
colorbar sampled
colorbar sampled={%<options%>}
colorbar sampled line
colorbar sampled line={%<options%>}
colorbar as legend
colorbar to name=##l
width=##L
height=##L
scale only axis#true,false
x=##L
y=##L
z=##L
x={%<(x,y)%>}
y={%<(x,y)%>}
z={%<(x,y)%>}
xmode=#normal,linear,log
ymode=#normal,linear,log
zmode=#normal,linear,log
x dir=#normal,reverse
y dir=#normal,reverse
z dir=#normal,reverse
axis equal#true,false
axis equal image#true,false
unit vector ratio={%<rx ry rz%>}
unit vector ratio*={%<rx ry rz%>}
unit rescale keep size=#true,false,unless limits declared
x post scale=%<scale%>
y post scale=%<scale%>
z post scale=%<scale%>
scale=%<scale%>
max space between ticks=%<integer%>
try min ticks=%<integer%>
normalsize
small
footnotesize
tiny
scale mode=#auto,none,stretch to fill,scale uniformly
scale uniformly strategy=#auto,units only,change vertical limits,change horizontal limits
unit rescale keep size=#true,false,unless limits declared
view={%<azimuth%>}{%<elevation%>}
view/az=%<azimuth%>
view/h=%<azimuth%>
view/el=%<elevation%>
view/v=%<elevation%>
plot box ratio={%<xstretch ystretch zstretch%>}
3d box=#background,complete,complete*
error bars/x dir=#none,plus,minus,both
error bars/y dir=#none,plus,minus,both
error bars/z dir=#none,plus,minus,both
error bars/x fixed=%<value%>
error bars/y fixed=%<value%>
error bars/z fixed=%<value%>
error bars/x fixed relative=%<percent%>
error bars/y fixed relative=%<percent%>
error bars/z fixed relative=%<percent%>
error bars/x explicit
error bars/y explicit
error bars/z explicit
error bars/x explicit relative
error bars/y explicit relative
error bars/z explicit relative
error bars/error mark=#*,x,+,-,|,o,asterisk,star,10-pointed star,oplus,oplus*,otimes,otimes*,square,square*,triangle,triangle*,diamond,diamond*,halfdiamond,halfdiamond*,halfsquare,halfsquare*,halfsquare right,halfsquare right*,halfsquare left,halfsquare left*,Mercedes star,Mercedes star flipped,halfcircle,halfcircle*,pentagon,pentagon*,ball,text,cube,cube*
error bars/error mark options={%<options%>}
error bars/error bar style={%<options%>}
log ticks with fixed point
log plot exponent style={%<options%>}
log identify minor tick positions#true,false
log number format code/.code={%<code%>}
log base 10 number format code/.code={%<code%>}
log number format basis/.code={%<code%>}
xmin=%<coord%>
ymin=%<coord%>
zmin=%<coord%>
xmax=%<coord%>
ymax=%<coord%>
zmax=%<coord%>
min=%<coord%>
max=%<coord%>
clip xlimits#true,false
clip ylimits#true,false
clip zlimits#true,false
clip limits#true,false
enlarge x limits={%<enlarge options%>}
enlarge y limits={%<enlarge options%>}
enlarge z limits={%<enlarge options%>}
enlargelimits=%<value%>
enlargelimits respects figure size#true,false
log origin x=#0,infty
log origin y=#0,infty
log origin z=#0,infty
log origin=#0,infty
update limits#true,false
xtick distance=%<number%>
ytick distance=%<number%>
ztick distance=%<number%>
xtick=#data,{%<coord list%>}
ytick=#data,{%<coord list%>}
ztick=#data,{%<coord list%>}
minor x tick num=%<number%>
minor y tick num=%<number%>
minor z tick num=%<number%>
minor tick num=%<number%>
minor xtick=#data,{%<coord list%>}
minor ytick=#data,{%<coord list%>}
minor ztick=#data,{%<coord list%>}
minor tick=#data,{%<coord list%>}
extra x ticks={%<coord list%>}
extra y ticks={%<coord list%>}
extra z ticks={%<coord list%>}
xtickten={%<exponent base 10 list%>}
ytickten={%<exponent base 10 list%>}
ztickten={%<exponent base 10 list%>}
xticklabels={%<label list%>}
yticklabels={%<label list%>}
zticklabels={%<label list%>}
xticklabel=%<command%>
yticklabel=%<command%>
zticklabel=%<command%>
xticklabels from table={%<table or file%>}{%<col name%>}
yticklabels from table={%<table or file%>}{%<col name%>}
zticklabels from table={%<table or file%>}{%<col name%>}
extra x tick label={%<code%>}
extra y tick label={%<code%>}
extra z tick label={%<code%>}
extra x tick labels={%<label list%>}
extra y tick labels={%<label list%>}
extra z tick labels={%<label list%>}
x tick label as interval#true,false
y tick label as interval#true,false
z tick label as interval#true,false
xminorticks#true,false
yminorticks#true,false
zminorticks#true,false
xmajorticks#true,false
ymajorticks#true,false
zmajorticks#true,false
ticks=#minor,major,both,none
xtick pos=#lower,upper,bottom,top,left,right,both
ytick pos=#lower,upper,bottom,top,left,right,both
ztick pos=#lower,upper,bottom,top,left,right,both
tick pos=#lower,upper,bottom,top,left,right,both
xticklabel pos=#lower,upper,bottom,top,left,right,default
yticklabel pos=#lower,upper,bottom,top,left,right,default
zticklabel pos=#lower,upper,bottom,top,left,right,default
ticklabel pos=#lower,upper,bottom,top,left,right,default
xtick align=#inside,center,outside
ytick align=#inside,center,outside
ztick align=#inside,center,outside
tick align=#inside,center,outside
xticklabel shift=##L
yticklabel shift=##L
zticklabel shift=##L
ticklabel shift=##L
typeset ticklabels with strut
scaled ticks=#true,false,base 10:%<exp%>,real:%<num%>,manual:{%<label%>}{%<code%>}
scaled x ticks=#true,false,base 10:%<exp%>,real:%<num%>,manual:{%<label%>}{%<code%>}
scaled y ticks=#true,false,base 10:%<exp%>,real:%<num%>,manual:{%<label%>}{%<code%>}
scaled z ticks=#true,false,base 10:%<exp%>,real:%<num%>,manual:{%<label%>}{%<code%>}
xtick scale label code/.code={%<code%>}
ytick scale label code/.code={%<code%>}
ztick scale label code/.code={%<code%>}
tick scale label code/.code={%<code%>}
tick scale binop=%<TeX math operator%>
scale ticks below exponent=%<exponent%>
scale ticks above exponent=%<exponent%>
max space between ticks=%<number%>
try min ticks=%<number%>
try min ticks log=%<number%>
tickwidth=##L
major tick length=##L
subtickwidth=##L
minor tick length=##L
log basis x=%<number%>
log basis y=%<number%>
log basis z=%<number%>
hide obscured x ticks#true,false
hide obscured y ticks#true,false
hide obscured z ticks#true,false
xminorgrids#true,false
yminorgrids#true,false
zminorgrids#true,false
xmajorgrids#true,false
ymajorgrids#true,false
zmajorgrids#true,false
grid=#minor,major,both,none
allow reversal of rel axis cs#true,false
pos=%<fraction%>
sloped
allow upside down#true,false
pos segment=%<segment index%>
forget plot style={%<options%>}
label style={%<options%>}
x label style={%<options%>}
y label style={%<options%>}
z label style={%<options%>}
xlabel style={%<options%>}
ylabel style={%<options%>}
zlabel style={%<options%>}
title style={%<options%>}
3d box foreground style={%<options%>}
colorbar sampled line style={%<options%>}
tick style={%<options%>}
minor tick style={%<options%>}
major tick style={%<options%>}
tick label style={%<options%>}
ticklabel style={%<options%>}
x tick label style={%<options%>}
y tick label style={%<options%>}
z tick label style={%<options%>}
xticklabel style={%<options%>}
yticklabel style={%<options%>}
zticklabel style={%<options%>}
x tick scale label style={%<options%>}
y tick scale label style={%<options%>}
z tick scale label style={%<options%>}
xtick style={%<options%>}
ytick style={%<options%>}
ztick style={%<options%>}
minor x tick style={%<options%>}
minor y tick style={%<options%>}
minor z tick style={%<options%>}
major x tick style={%<options%>}
major y tick style={%<options%>}
major z tick style={%<options%>}
extra x tick style={%<options%>}
extra y tick style={%<options%>}
extra z tick style={%<options%>}
extra tick style={%<options%>}
grid style={%<options%>}
minor grid style={%<options%>}
major grid style={%<options%>}
x grid style={%<options%>}
y grid style={%<options%>}
z grid style={%<options%>}
minor x grid style={%<options%>}
minor y grid style={%<options%>}
minor z grid style={%<options%>}
major x grid style={%<options%>}
major y grid style={%<options%>}
major z grid style={%<options%>}
at={%<(x,y)%>}
anchor=%<name%>
clip#true,false
clip marker paths#true,false
clip bounding box=#default tikz,upper bound
clip mode=#global,individual
x coord trafo/.code={%<code%>}
y coord trafo/.code={%<code%>}
z coord trafo/.code={%<code%>}
x coord inv trafo/.code={%<code%>}
y coord inv trafo/.code={%<code%>}
z coord inv trafo/.code={%<code%>}
symbolic x coords={%<dictionary%>}
symbolic y coords={%<dictionary%>}
symbolic z coords={%<dictionary%>}
x filter/.expression={%<math expr%>}
y filter/.expression={%<math expr%>}
z filter/.expression={%<math expr%>}
x filter/.append expression={%<math expr%>}
y filter/.append expression={%<math expr%>}
z filter/.append expression={%<math expr%>}
x filter/.code={%<code%>}
y filter/.code={%<code%>}
z filter/.code={%<code%>}
filter point/.code={%<code%>}
pre filter/.code={%<code%>}
skip coords between index={%<begin%>}{%<end%>}
each nth point=%<integer%>
restrict x to domain=%<min:max%>
restrict y to domain=%<min:max%>
restrict z to domain=%<min:max%>
restrict x to domain*=%<min:max%>
restrict y to domain*=%<min:max%>
restrict z to domain*=%<min:max%>
restrict expr to domain={%<expr%>}{%<min:max%>}
restrict expr to domain*={%<expr%>}{%<min:max%>}
filter discard warning#true,false
data cs=#cart,polar,polarrad
disablelogfilter#true,false
disabledatascaling#true,false
execute at begin plot={%<commands%>}
execute at end plot={%<commands%>}
execute at begin axis={%<commands%>}
execute at end axis={%<commands%>}
execute at begin plot visualization={%<commands%>}
execute at end plot visualization={%<commands%>}
forget plot#true,false
before end axis/.code={%<code%>}
after end axis/.code={%<code%>}
axis on top#true,false
visualization depends on=%<\macro%>
visualization depends on=%<expression%> \as %<\macro%>
visualization depends on=value %<content%> \as %<\macro%>
set layers=#none,standard,axis on top
on layer=%<layer name%>
mark layer=#auto,like plot,%<layer name%>
cell picture=#true,false,if necessary
enable tick line clipping#true,false
#endkeyvals

\nextlist#*
\pgfplotslegendfromname{label}#*r
\pgfplotscolorbarfromname{label}#*r
\begin{pgfplotsinterruptdatabb}
\end{pgfplotsinterruptdatabb}

### Shortcuts ###
\begin{tikzpicture}% function%\\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]%\\addplot {%|};%\\end{axis}%\\end{tikzpicture}#n
\begin{tikzpicture}% table%\\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]%\\addplot table[x=%<column header%>,y=%<column header%>] {%<file%>};%\\end{axis}%\\end{tikzpicture}#n
\begin{tikzpicture}% coordinates%\\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]%\\addplot coordinates {%|};%\\end{axis}%\\end{tikzpicture}#n
\begin{tikzpicture}% file%\\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]%\\addplot file {%<file%>};%\\end{axis}%\\end{tikzpicture}#*n
\begin{tikzpicture}% gnuplot%\\begin{axis}[xlabel=%<x axis label%>,ylabel=%<y axis label%>]%\\addplot gnuplot {%<gnuplot code%>};%\\end{axis}%\\end{tikzpicture}#*n

\begin{axis}[%<options%>]% function%\\addplot {%|};%\\end{axis}#/tikzpicture
\begin{axis}[%<options%>]% table%\\addplot table[x=%<column header%>,y=%<column header%>] {%<file%>};%\\end{axis}#/tikzpicture
\begin{axis}[%<options%>]% coordinates%\\addplot coordinates {%|};%\\end{axis}#/tikzpicture
\begin{axis}[%<options%>]% file%\\addplot file {%<file%>};%\\end{axis}#*/tikzpicture
\begin{axis}[%<options%>]% gnuplot%\\addplot gnuplot {%<gnuplot code%>};%\\end{axis}#*/tikzpicture

\addplot table [x=%<column header%>,y=%<column header%>] {%<file%>};#/axis,semilogxaxis,semilogyaxis,loglogaxis,groupplot,polaraxis,smithchart,ternaryaxis
\addplot coordinates {%<coord list%>};#/axis,semilogxaxis,semilogyaxis,loglogaxis,groupplot,polaraxis,smithchart,ternaryaxis
\addplot gnuplot {%<gnuplot code%>};#*n/axis,semilogxaxis,semilogyaxis,loglogaxis,groupplot,polaraxis,smithchart,ternaryaxis
\addplot file {%<file%>};#*n/axis,semilogxaxis,semilogyaxis,loglogaxis
\addplot expression {%<math expr%>};#*n/axis,semilogxaxis,semilogyaxis,loglogaxis,groupplot,polaraxis,smithchart,ternaryaxis
\addplot function {%<gnuplot code%>};#*n/axis,semilogxaxis,semilogyaxis,loglogaxis,groupplot,polaraxis,smithchart,ternaryaxis
\addplot shell {%<shell commands%>};#*n/axis,semilogxaxis,semilogyaxis,loglogaxis,groupplot,polaraxis,smithchart,ternaryaxis
\addplot graphics {%<file%>};#*n/axis,semilogxaxis,semilogyaxis,loglogaxis,groupplot,polaraxis,smithchart,ternaryaxis

## pgfplots.revision.tex
\pgfplotsrevision#*
\pgfplotsversion#*
\pgfplotsversiondatetime#*
\pgfplotsrevisiondatetime#*
\pgfplotsversiondate#*
\pgfplotsrevisiondate#*

## pgfplots.code.tex
\ifpgfplotsthreedim#*
\pgfplotsthreedimtrue#S
\pgfplotsthreedimfalse#S
\pgfnodepartimagebox#*
\axisdefaultwidth#*
\axisdefaultheight#*
\pgfplotsifaxisthreedim{true}{false}#*
\pgfplotsifcurplotthreedim{true}{false}#*
\pgfplotsifcyclelistexists{name}{true}{false}#*
\pgfplotscreateplotcyclelist{name}{list}#*
\pgfplotsmarklistfill#*
\pgfplotsdeprecatedstylecheck{options}#S#*
\pgfplotspointmeta#*
\pgfplotspointmetarange#*
\pgfplotspointmetatransformed#*
\pgfplotspointmetatransformedrange#*
\length#S
\disstart#S
\disend#S
\discontstyle#S
\pgfplotsretval#*
\pgfplotsextra{path code}#*
\curcolumnNum#S
\maxcolumnCount#S
\legendplotpos#S
\theHpgfplotslink#S
\pgfmathlogtologten{arg}#*
\upperrightcorner#S
\lowerleftinnercorner#S
\innerdiagonal#S
\origin#S
\xaxisvec#S
\yaxisvec#S
\pgfplotsdefineaxistype{type}{code}#*
\pgfplotssetaxistype{type}#*
\pgfplotssetlayers{layer config name}#*
\pgfplotsonlayer{layer name}#*
\endpgfplotsonlayer#*
\pgfplotsgetlayerforstyle{options}#*
\pgfplotspointorigininternal#*
\pgfplotspointupperrightcorner#*
\pgfplotspointaxisorigin#*
\pgfplotspointdescriptionbyanchor{anchor}#*
\pgfplotspointbblowerleft#*
\pgfplotspointbbupperright#*
\pgfplotspointbbdiagonal#*
\pgfplotspathaxisoutline#*
\pgfplotspointaxisxy{x}{y}#*
\pgfplotspointaxisxyz{x}{y}{z}#*
\pgfplotsqpointaxisxy{x}{y}#*
\pgfplotsqpointaxisxyz{x}{y}{z}#*
\pgfplotspointnormalizedaxisxy{x}{y}#*
\pgfplotspointnormalizedaxisxyz{x}{y}{z}#*
\pgfplotspointaxisdirectionxy{x}{y}#*
\pgfplotspointaxisdirectionxyz{x}{y}{z}#*
\pgfplotspointdescriptionxy{x-frac}{y-frac}#*
\pgfplotsqpointdescriptionxy{x-frac}{y-frac}#*
\pgfplotspointrelaxisxy{x}{y}#*
\pgfplotspointrelaxisxyz{x}{y}{z}#*
\pgfplotstransformcoordinatex{x}#*
\pgfplotstransformcoordinatey{y}#*
\pgfplotstransformcoordinatez{z}#*
\pgfplotstransformdirectionx{x}#*
\pgfplotstransformdirectiony{y}#*
\pgfplotstransformdirectionz{z}#*
\ifpgfplotscolorbarCMYKworkaround#*
\pgfplotscolorbarCMYKworkaroundtrue#*
\pgfplotscolorbarCMYKworkaroundfalse#*
\pgfplotscolorbardrawstandalone#*
\pgfplotscolorbardrawstandalone[options]#*
\pgfplotsifnodeexists{node}{true}{false}#*
\axispath#S
\pgfplotsinterruptdatabb#*
\endpgfplotsinterruptdatabb#*
\logten#*
\reciproclogten#*
\logi{arg}#S
\axisdefaultticklabel#*
\axisdefaultticklabellog#*
\legend{list}#/axis,semilogxaxis,semilogyaxis,loglogaxis,groupplot,polaraxis,smithchart,ternaryaxis
\addlegendimage{options}#*
\addlegendentry{name}
\addlegendentry[options]{name}
\addlegendentryexpanded{TeX text}
\addlegendentryexpanded[options]{TeX text}
\pgfplotssetlateoptions{options}#*
\pgfplotsifissurveyphase{true}{false}#*
\pgfplotsifisvisualizationphase{true}{false}#*
\pgfplotsifinaxis{true}{false}#*
\numplots#*
\numplotsofactualtype#*
\closedcycle
\pgfplotsaxisplotphase#*
\pgfplotsreplacepdfmark{picture id1}{picture id2}#*
\axis#S
\endaxis#S
\semilogxaxis#S
\endsemilogxaxis#S
\semilogyaxis#S
\endsemilogyaxis#S
\loglogaxis#S
\endloglogaxis#S

## pgfplotscore.code.tex
\pgfplotsloglevel#*
\pgfplotsglobalretval#*
\pgfplotsthrow{exception}{arguments}#*
\pgfplotswarning{exception}{arguments}#*
\pgfplotstry{arg}#*
\endpgfplotstry#*
\pgfplotsrethrow#*
\pgfplotsexceptionmsg#*
\pgfplotsiffileexists{file}{true}{false}#*

## └── pgfplotssysgeneric.code.tex
# no new user commands

## pgfplotslibrary.code.tex
\usepgfplotslibrary{library list%keyvals}#u
\pgfplotsiflibraryloaded{library%keyvals}{true}{false}#*
#keyvals:\usepgfplotslibrary#c,\pgfplotsiflibraryloaded#c
clickable
colorbrewer
colormaps
dateplot
decorations.softclip
external
fillbetween
groupplots
patchplots
polar
smithchart
statistics
ternary
units
#endkeyvals

## pgfplotsoldpgfsupp_loader.code.tex
\pgfplotsusecompatibilityfile{file}#S

## pgfplotsutil.code.tex
\pgfplotsqaftergroupeach{tokens}#*
\pgfplotsaftergroupcollectinto{cmd}{tokens}#*d
\pgfplotscommandtostring{cmd1}{cmd2%cmd}#*d
\pgfplotsmathmin{x}{y}#*
\pgfplotsmathmax{x}{y}#*
\pgfplotsmathlessthan{x}{y}#*
\pgfplotsmathfloatmax{x}{y}#*
\pgfplotsmathfloatmin{x}{y}#*
\pgfplotsscalarproductofvectors{point1}{point2}
\pgfplotsqpointxy{x}{y}#*
\pgfplotsqpointxyz{x}{y}{z}#*
\pgfplotsutilforeachcommasep{list}\as{macro%cmd}{code}#*d
\as{cmd}#Sd
\pgfplotsforeachentryinCSV{macro%cmd}{list}{code}#*d
\pgfplotsforeachentryinCSVisterminated{macro%cmd}{list}{code}#*d
\pgfplotsforeachungrouped %<\variable%> in {%<list%>}{%<code%>}#*
\pgfplotsforeachungrouped{macro%cmd}#Sd
\pgfplotsforeachtodomain{domain}#*
\ifpgfplotsforeachungroupedassumenumeric#S
\pgfplotsforeachungroupedassumenumerictrue#S
\pgfplotsforeachungroupedassumenumericfalse#S
\pgfplotsinvokeforeach{list}{code}#*
\pgfplotsforeachlogarithmicformatresultwith{code}#*
\pgfplotsforeachlogarithmicungrouped[samples]#*
\pgfplotsforeachlogarithmicmathid
\pgfplotsmathmodint{x}{y}#*
\ifpgfplotsloopcontinue#S
\pgfplotsloopcontinuetrue#S
\pgfplotsloopcontinuefalse#S
\pgfplotsloop{code}{body}#*
\pgfplotsutilstrcmp{string1}{string2}#*
\pgfplotsmathcarttopol{x}{y}{angle macro%cmd}{radius macro%cmd}#*d
\pgfplotsmathcarttopolbasic{x}{y}{angle macro%cmd}{radius macro%cmd}#*d
\pgfplotsmathpoltocart{angle}{radius}{x macro%cmd}{y macro%cmd}#*d
\pgfplotsmathpoltocartbasic{angle}{radius}{x macro%cmd}{y macro%cmd}#*d
\pgfplotsmathdeclarepseudoconstant{name}{code}#*
\pgfplotsmathredeclarepseudoconstant{name}{code}#*
\pgfplotsmathdefinemacrolnbase{macro%cmd}{number}#*d
\pgfplotsutilifstartswith{pattern}{string}{true}{false}#*
\pgfplotsutilstrreplace{token}{replacement}{string}#*
\pgfplotsutilifstringequal{string1}{string2}{true}{false}#*
\pgfplotsutilifcontainsmacro{tokens}{true}{false}#*
\pgfmathparsex{expr}#*
\pgfplotsutilifdatelessthan %<YYYY-MM-DD%> \cmp %<YYYY-MM-DD%> \relax{%<true%>}{%<false%>}#*
\cmp#S
\pgfplotsutilifdategreaterthan %<YYYY-MM-DD%> \cmp %<YYYY-MM-DD%> \relax{%<true%>}{%<false%>}#*
\pgfplotsutilsortthree{macro1}{macro2}{macro3}#*
\pgfplotsutilsortfour{macro1}{macro2}{macro3}{macro4}#*
\pgfplotsmathvectortostring{x,y,z}{arg}#*
\pgfplotsmathvectorfromstring{x,y,z}{arg}#*
\pgfplotsmathvectorsubtract{x1,y1,z1}{x2,y2,z2}{arg}#*
\pgfplotsmathvectoradd{x1,y1,z1}{x2,y2,z2}{arg}#*
\pgfplotsmathvectorcompwise{x1,y1,z1}{x2,y2,z2}{operation}{arg}#*
\pgfplotsmathvectorsum{x,y,z}{arg}#*
\pgfplotsmathvectorscalarproduct{x1,y1,z1}{x2,y2,z2}{arg}#*
\pgfplotsmathvectortocomponents{x,y,z}{string}{arg}#*
\pgfplotsmathvectorcrossprod{x1,y1,z1}{x2,y2,z2}{arg}#*
\pgfplotsmathvectorscaleindividually{x1,y1,z1}{x2,y2,z2}{arg}#*
\pgfplotspointfromcsvvector{x,y,z}{arg}#*
\pgfplotsmathvectorlength{x,y,z}{arg}#*
\pgfplotsmathvectorscale{x,y,z}{scale}{arg}#*
\pgfplotsmathvectordatascaletrafoinverse{x,y,z}{arg}#*
\pgfplotsDQ#S
\pgfplotsVERTBAR#S
\pgfplotsHASH#S
\pgfplotsPERCENT#S
\CATCODE#S
\LONG#S

## ├── pgfplotsliststructure.code.tex
\ifpgfplotslistempty#*
\pgfplotslistemptytrue#*
\pgfplotslistemptyfalse#*
\pgfplotslistnewempty{macro%cmd}#*d
\pgfplotslistnew{macro%cmd}{list}#*d
\pgfplotslistcopy %<\list%> \to %<\macro%>#*
\to{cmd}#Sd
\pgfplotslistpushfront %<item%> \to %<\list%>#*
\pgfplotslistpushfrontglobal %<item%> \to %<\list%>#*
\pgfplotslistpushback %<item%> \to %<\list%>#*
\pgfplotslistpushbackglobal %<item%> \to %<\list%>#*
\pgfplotslistconcat%\macro%>=%<\list1%>&%<\list2%>#*
\pgfplotslistconcat{cmd}#Sd
\pgfplotslistpopfront %<\list%> \to %<\macro%>#*
\pgfplotslistfront %<\list%> \to %<\macro%>#*
\pgfplotslistsize %<\list%> \to %<\macro%>#*
\pgfplotslistselect %<index%> \of %<\list%> \to %<\macro%>#*
\of#S
\pgfplotslistselectorempty %<index%> \of %<\list%> \to %<\macro%>#*
\pgfplotslistset %<index%> \of %<\list%> \to %<content%>#*
\pgfplotslistcheckempty%<\list%>#*
\pgfplotslistforeach %<\list%> \as %<\var%> {%<code%>}#*
\pgfplotslistforeachungrouped %<\list%> \as %<\var%> {%<code%>}#*

## ├── pgfplotsliststructureext.code.tex
\pgfplotsapplistnewempty{macro%cmd}#*d
\pgfplotsapplistpushback %<item%> \to %<\list%>#*
\pgfplotsapplistedefcontenttomacro %<\list%> \to %<\macro%>#*
\pgfplotsapplistxdefcontenttomacro %<\list%> \to %<\macro%>#*
\pgfplotsapplistexecute{code}#*
\pgfplotsapplistXnewempty{macro%cmd}#*d
\pgfplotsapplistXpushback %<item%> \to %<\list%>#*
\pgfplotsapplistXflushbuffers{list}#*
\pgfplotsapplistXedefcontenttomacro %<\list%> \to %<\macro%>#*
\pgfplotsapplistXxdefcontenttomacro %<\list%> \to %<\macro%>#*
\pgfplotsapplistXlet %<\macro%>=%<\list%>#*
\pgfplotsapplistXlet{cmd}#Sd
\pgfplotsapplistXexecute{code}#*
\pgfplotsprependlistXnewempty{list}#*
\pgfplotsprependlistXpushfront %<item%> \to %<\list%>#*
\pgfplotsprependlistXflushbuffers{list}#*
\pgfplotsprependlistXlet %<cs%>=%<list%>#*
\pgfplotsapplistXXnewempty{macro%cmd}#*d
\pgfplotsapplistXX#*
\pgfplotsapplistXXclear{list}#*
\pgfplotsapplistXXpushback{item}{list macro}#*
\pgfplotsapplistXXflushbuffers{list}#*
\pgfplotsapplistXXedefcontenttomacro{list}{macro%cmd}#*d
\pgfplotsapplistXXxdefcontenttomacro{list}{macro%cmd}#*d
\pgfplotsapplistXXlet{macro%cmd}#*d
\pgfplotsapplistXXexecute{code}#*
\pgfplotsapplistXXglobalnewempty{macro%cmd}#*d
\pgfplotsapplistXXglobal#*
\pgfplotsapplistXXglobalclear{list}#*
\pgfplotsapplistXXglobalpushback{item}{list macro}#*
\pgfplotsapplistXXglobalflushbuffers{list}#*
\pgfplotsapplistXXglobaledefcontenttomacro{list}{macro%cmd}#*d
\pgfplotsapplistXXglobalxdefcontenttomacro{list}{macro%cmd}#*d
\pgfplotsapplistXXgloballet{macro%cmd}#*d
\pgfplotsapplistXXglobalexecute{code}#*
\pgfplotsgloballet#*
\pgfplotsgloballet{cmd}#Sd
\pgfplotsapplistXglobalnewempty{macro%cmd}#*d
\pgfplotsapplistXglobalpushback %<item%> \to %<\list%>#*
\pgfplotsapplistXglobalflushbuffers{list}#*
\pgfplotsapplistXgloballet %<\macro%>=%<\list%>#*
\pgfplotsapplistXgloballet{cmd}#Sd

## ├── pgfplotsarray.code.tex
\ifpgfplotsarrayempty#*
\pgfplotsarrayemptytrue#*
\pgfplotsarrayemptyfalse#*
\pgfplotsarraynewempty{macro%cmd}#*d
\pgfplotsarraynewemptyglobal{macro%cmd}#*d
\pgfplotsarrayresize{array macro}{size}#*
\pgfplotsarrayresizeglobal{array macro}{size}#*
\pgfplotsarrayifdefined{array macro}{true}{false}#*
\pgfplotsarraynew{macro%cmd}{array}#*
\pgfplotsarrayfrompgfplotslist{array macro}{list}#*
\pgfplotsarraycopy %<\array1%> \to %<\array2%>#*
\pgfplotsarraypushback %<item%> to $<\array%>#*
\pgfplotsarraypushbackglobal %<item%> to $<\array%>#*
\pgfplotsarraysize %<\array%> \to %<\macro%>#*
\pgfplotsarraysizetomacro %<\array%> \to %<\macro%>#*
\pgfplotsarraysizeof{array macro}#*
\pgfplotsarrayselect %<index%> \of %<\array%> \to %<\macro%>#*
\pgfplotsarrayvalueofelem %<index%> \of %<\array%>#*
\pgfplotsarrayset %<index%> \of %<\array%> \to %<content%>#*
\pgfplotsarraysetglobal %<index%> \of %<\array%> \to %<content%>#*
\pgfplotsarrayletentry %<index%> \of %<\array%>=%<content%>#*
\pgfplotsarrayletentryglobal %<index%> \of %<\array%>=%<content%>#*
\pgfplotsarraytotext{array}#*
\pgfplotsarraycheckempty{array}#*
\pgfplotsarrayforeach %<\array%> \as %<\var%> {%<code%>}#*
\pgfplotsarrayforeachindex#*
\pgfplotsarrayforeachungrouped %<\array%> \as %<\var%> {%<code%>}#*
\pgfplotsarrayforeachreversed %<\array%> \as %<\var%> {%<code%>}#*
\pgfplotsarrayforeachreversedungrouped %<\array%> \as %<\var%> {%<code%>}#*
\pgfplotsarraysort{array}#*
\pgfplotsarrayinsertionsort{array}#*
\pgfplotsarraybinarysearch{array}{value}{start index}{end index}#*

## ├── pgfplotsmatrix.code.tex
\pgfplotsmatrixnewempty{macro%cmd}#*d
\pgfplotsmatrixresize{matrix}{rows}{cols}#*
\pgfplotsmatrixifdefined{matrix}{true}{false}#*
\pgfplotsmatrixsize %<\matrix%> \to {%<rows%>}{%<cols%>}#*
\pgfplotsmatrixsizetomacro %<\matrix%> \to %<\rows%>%<\cols%>#*
\pgfplotsmatrixselect %<row,col%> \of %<\matrix%> \to %<\macro%>#*
\pgfplotsmatrixvalueofelem %<row,col%> \of %<\matrix%>#*
\pgfplotsmatrixset %<row,col%> \of %<\matrix%> \to %<content%>#*
\pgfplotsmatrixletentry %<row,col%> \of %<\matrix%>=%<content%>#*
\pgfplotsmatrixforeach %<\matrix%> \as %<\var%> {%<code%>}#*
\pgfplotsmatrixforeachrowindex#*
\pgfplotsmatrixforeachcolindex#*
\pgfplotsmatrixforeachrowend#*
\pgfplotsmatrixtotext{matrix}#*
\pgfplotsmatrixLUdecomp %<\matrix%> \perm %<\macro%> \sign %<\macro%>#*
\perm{cmd}#Sd
\sign{cmd}#Sd
\pgfplotsmatrixLUdecompwarnsingular#*
\pgfplotsmatrixLUbacksubst %<\matrix%> \perm %<\macro%> \inout %<\macro%>#*
\inout{cmd}#Sd
\pgfplotsmatrixsolveLEQS %<\matrix%>=%<\vector%>#*

## ├── pgfplotstableshared.code.tex
\pgfplotstableread{file}
\pgfnumtableread#S
\pgfplotstableifiscreateonuse{column}{true}{false}
\pgfplotstablegenerateuniquecolnamefor{table}
\pgfplotstablegetcolumnbyname{column}\of{table}\to{macro}#*
\pgfplotstableresolvecolname{column}\of{table}\to{macro}#*
\pgfplotstablegetcolumn{column}\of{table}\to{macro}#*
\pgfplotstablegetcolumnnamebyindex{column index}\of{table}\to{macro}#*
\pgfplotstablegetcolumnindexforname{column}\of{table}\to{macro}#*
\pgfplotstablegetcolumnbyindex{column}\of{table}\to{macro}#*
\pgfplotstablecopy{table1}\to{table2}#*
\pgfplotstablegetname{table}{macro%cmd}#*d
\pgfplotstablenameof{table}#*
\pgfplotstablegetscanlinelength{table}{macro%cmd}#*d
\pgfplotstablescanlinelengthof{table}#*
\pgfplotstablereadpreparecatcodes#*
\pgfplotstablecollectoneargwithpreparecatcodes{arg}#*
\pgfplotstablecollectoneargwithpreparecatcodesnorestore{arg}#*
\pgfplotstableinstallignorechars#*
\pgfplotstableuninstallignorechars#*
\pgfplotstablename#*
\pgfplotstablerow#*
\pgfplotstablelineno#*
\pgfplotstablereadgetcolindex{index}{content}#*
\pgfplotstablereadgetcolname{name}{content}#*
\pgfplotstablereadgetptrtocolname{name}{macro%cmd}#*d
\pgfplotstablereadgetptrtocolindex{index}{macro%cmd}#*d
\pgfplotstablereadevalptr{pointer}{content}#*
\pgfplotstablereadvalueofptr{pointer}#*
\pgfplotstableforeachcolumn{%<table%>} \as %<\macro%> {%<code%>}#*
\pgfplotstablereadvalueofcolname{name}#*
\pgfplotstablereadvalueofcolindex{index}#*
\getthisrow{name}{macro%cmd}#*d
\thisrow{col name}#*
\thisrowno{col index}#*
\lineno#*
\getthisrowno{name}{macro%cmd}#*d
\pgfplotstableset{options%keyvals}#*
\pgfplotstabletypeset{table}#*
\pgfplotstabletypeset[options%keyvals]{table}#*
\pgfplotstabletypesetfile{file}#*
\pgfplotstabletypesetfile[options%keyvals]{file}#*
\pgfplotstablecreatecol{name}{table}#*
\pgfplotstablecreatecol[options%keyvals]{name}{table}#*
\pgfplotstableforeachcolumn{table}\as{macro}{code}#*
\pgfplotstablecol#*
\pgfplotstableforeachcolumnelement{column}\of{table}\as{macro}{code}#*
\pgfplotstablerow#*
\pgfplotstablemodifyeachcolumnelement{column}\of{table}\as{macro}{code}#*
\pgfplotstablegetelem{row}{col}\of{table}#*
\pgfplotstablegetcolumnlist{name}\to{macro}#*
\pgfplotstablegetrowsof{table}#*
\pgfplotstablegetcolsof{table}#*

## ├── pgfplotsdeque.code.tex
\pgfplotsdequenewempty{deque name}{integer}#*
\pgfplotsdequecopy{deque1}\to{deque2}#*
\pgfplotsdequepushback{deque1}\to{deque2}#*
\pgfplotsdequepopfront{deque1}\to{deque2}#*
\pgfplotsdequecheckempty{deque}{true}{false}#*
\pgfplotsdequeforeach{%<deque%>}\as%<\macro%>{%<code%>}#*

## ├── pgfplotsbinary.code.tex
\pgfplotsbinaryatcode#*
\pgfplotscharno{number}#*
\pgfplotsbinarytoluabinary{number list}#*
\pgfplotsgetchar{char}#*
\pgfplotsbinarysetbytes{number}#*
\pgfplotsbinaryempty#*
\pgfplotsbinaryencodeunsigned{unsigned integer}#*
\pgfplotsbinaryencodesignedmaplinearly{signed integer}#*
\pgfplotsbinaryencodedimenmaplinearly{TeX dimen}#*

## │   └── pgfplotsbinary.data.code.tex
# no new user commands

## ├── pgfplotsutil.verb.code.tex
\beginpgfplotsverbatim#*
\endpgfplotsverbatim#*

## └── pgflibrarypgfplots.surfshading.code.tex
\pgfplotslibrarysurfprocesscoordinate{arg}#*
\pgfplotslibrarysurfusepath#*
\pgfplotslibrarysurfstreamstart#*
\pgfplotslibrarysurfstreamend#*
\pgfplotslibrarysurfdraw#*
\pgfplotslibrarysurfstreamcoord{pgf point}{color coord}#*
\pgfplotslibrarysurfusepath#*
\pgfplotslibrarysurfdrawinpicture#*
\pgflibrarysurfshadingifactive{true}{false}#*

## pgfplotscolormap.code.tex
\pgfplotscreatecolormap{name}{color spec}#*
\pgfplotscolormapsetadditionalintervalwidth{colormap}{interval width}#*
\pgfplotscolormapifisuniform{colormap}{true}{false}#*
\pgfplotscolormaptodatafile{colormap}{data file%file}#*
\pgfplotscolormaptodatafile[options%keyvals]{colormap}{data file%file}#*
#keyvals:\pgfplotscolormaptodatafile
output each nth=%<integer%>
output format=#csv,native
#endkeyvals
\pgfplotscolormapgetmeshwidth{colormap}#*
\pgfplotscolormapserializecomponentstomacro{colormap}{macro%cmd}#*d
\pgfplotscolormapserializeXtomacro{colormap}{macro%cmd}#*d
\pgfplotscolormapserializetomacro{colormap}{macro%cmd}#*d
\pgfplotscolormapgetpositions[start:end]{colormap}#*
\pgfplotscolormappdfmax#*
\pgfplotscolormapsizeof{colormap}#*
\pgfplotscolormapgetcolor{colormap}{index}#*
\pgfplotscolormaplastindexof{colormap}#*
\pgfplotscolormapifrequiresextrainterval{colormap}{true}{false}#*
\pgfplotscolormapifdrawslastcolor{colormap}{true}{false}#*
\pgfplotscolormaptopdffunction{colormap}#*
\pgfplotscolormapifdefined{colormap}{true}{false}#*
\pgfplotscolormapassertexists{colormap}#*
\pgfplotscolormaptoshadingspec{colormap}{pgf size}{macro%cmd}#*d
\pgfplotscolormaptoshadingspectorgb#*
\pgfplotscolormapreversedtoshadingspec{colormap}{pgf size}{macro%cmd}#*d
\pgfplotscolormaprange#*
\pgfplotscolormapgetcolorspace{colormap}#*
\pgfplotscolormapgetcolorcomps{colormap}#*
\pgfplotscolormapcolorspaceof{colormap}#*
\pgfplotscolormapcolorcompsof{colormap}#*
\pgfplotscolormapfind[start:end]{number}{colormap}#*
\pgfplotscolormapfind[start:end][slope]{number}{colormap}#*
\pgfplotscolormapfindpiecewiseconst[start:end]{number}{colormap}#*
\pgfplotscolormapfindpiecewiseconst[start:end][slope]{number}{colormap}#*
\pgfplotscolormapgetindex{index}{colormap}#*
\pgfplotscolormapaccess[start:end]{number}{colormap}#*
\pgfplotscolormapaccess[start:end][slope]{number}{colormap}#*
\pgfplotspointmetatransformedrange#*
\pgfplotscolormapdefinemappedcolor{number}#*

## └── pgfplotscolor.code.tex
\pgfplotscolornormalizesequence[color seq options]#*
\endpgfplotscolornormalizesequence#*
\pgfplotscolornormalizesequencenextbycomponents{color space}{components}#*
\pgfplotsretvalb#*
\pgfplotscolorspacegetcomponents{color space}#*
\pgfplotscolornormalizesequencegetnumcomponents#*
\pgfplotscolornormalizesequencenext{color}#*
\pgfplotscolornormalizesequencezero#*
\pgfplotscolorzero{num of components}#*
\pgfplotscolornormalizesequenceaddweighted{color1}{scale factor}{color2}#*
\pgfplotscoloraddweighted{num of components}{color1}{scale factor}{color2}#*

## pgfplotsstackedplots.code.tex
\pgfplotspointgetzerolevelcoordinates#*
\pgfplotspointgetnormalizedzerolevelcoordinates#*

## pgfplotsplothandlers.code.tex
\pgfplotssurveyphaseinputclass#*
\pgfplotsresetplothandler#*
\pgfplotsplothandlerserializepointto{macro%cmd}#*d
\pgfplotsplothandlerdeserializepointfrom{macro}#*
\pgfplotsplothandlerpointtokeys{key prefix}#*
\pgfplotsplothandlerserializestateto{macro%cmd}#*d
\pgfplotsplothandlervisualizejump#*
\pgfplotsplothandlersurveypointattime{fraction}{point1}{point2}#*
\pgfplotsplothandlersurveydifflen{point1}{point2}#*
\pgfplotsplothandlertransformslopedattime{fraction}{point1}{point2}#*
\pgfplotsplothandlerifcurrentpointcanbefirstlast#*
\pgfplotsaxisupdatelimitsforcoordinatethreedim#*
\pgfplotsaxisparsecoordinatethreedim#*
\pgfplotsaxisupdatelimitsforcoordinatetwodim#*
\pgfplotsaxisparsecoordinatetwodim#*
\pgfplotsaxisupdatelimitsforcoordinate{x}{y}{z}#*
\pgfplotsaxisparsecoordinate#*
\pgfplotsplothandlerquiver#*
\pgfplotsplothandlerquivererror#*
\pgfplotsplothandlerhistogram#*
\pgfplotsplothandlerhistadvancebin{arg}#*
\pgfplotsplothandlerhistgetintervalstartfor{arg}#*
\pgfplotsplothandlerhistgetbinfor{arg}#*
\pgfplotsplothandlerhistsettol{arg}#*
\pgfplotsplothandlercontourprepared#*
\pgfplotsplothandlersurveybeforesetpointmeta#*
\pgfplotsplothandlersurveyaftersetpointmeta#*
\pgfplotsplothandlercontourexternal#*
\pgfplotscontourpopulateallkeys#*
\numcoords#S
\ordering#S
\infile#S
\outfile#S
\pgfplotsmetamin#*
\pgfplotsmetamax#*
\script#S
\scriptbase#S
\scriptext#S
\thecontourlevels#S
\thecontournumber#S
\pgfplotsplothandlertofile{file}#*
\pgfplotsplothandlertofilegeneratedscanlinemarks#*
\pgfplotsplothandlercontourfilled#*
\pgfplotscontourfilledcolormap#*

## └── pgfplotsmeshplothandler.code.tex
\pgfplotsplothandlermesh#*
\pgfplotsplothandlername#*
\pgfplotsplothandlersurveystart#*
\pgfplotsplothandlersurveypoint#*
\pgfplotsplothandlersurveyend#*
\pgfplotsplothandlersurveyaftersetpointmeta#*
\pgfplotsplothandlernotifyscanlinecomplete#*
\pgfplotsplothandlerLUAfactory#*
\pgfplotsplothandlerLUAvisualizerfactory#*
\pgfplotspreparemeshkeydefaults#*
\pgfplotsautocompletemeshkeys#*
\pgfplotspatchvertex{x}{y}{meta data}{depth}:{3d coords}\endvertex#*
\endvertex#S
\pgfplotspatchvertexstruct#*
\pgfplotspatchvertexx#*
\pgfplotspatchvertexy#*
\pgfplotspatchvertexmeta#*
\pgfplotspatchvertexdepth#*
\pgfplotspatchvertexcoords#*
\pgfplotspatchvertexcopymeta%<\vertex1%>\to%<\vertex2%>#*
\pgfplotspatchvertexcopymetaifbounded %<\vertex1%> \to %<\vertex2%>#*
\pgfplotspointpatchvertex{x}{y}{meta data}{depth}:{3d coords}\endvertex#*
\pgfplotspatchvertexaccumstart#*
\pgfplotspatchvertexadd%<\vertex%>\times{%<factor%>}#*
\times#S
\pgfplotspatchvertexfinish%<\macro%>#*
\pgfplotspatchvertexfinish{cmd}#Sd
\pgfplotspatchvertexaddXY%<\vertex%>\times{%<factor%>}#*
\pgfplotspatchvertexfinishXY%<\macro%>#*
\pgfplotspatchvertexfinishXY{cmd}#Sd
\pgfplotspatchclass{class name}{method}#*
\pgfplotspatchclassname#*
\pgfplotspatchclasserror{class name}{method}#*
\pgfplotsdeclarepatchclass{class name}{method}#*
\pgfplotspatchready#*
\pgfplotsrefinedpatchready#*
\pointlast#S
\diffA#S
\diffB#S
\crossAB#S
\normal#S
\pgfplotspatchclassx#*
\pgfplotspatchclassy#*
\PA#S
\PB#S
\PC#S
\PD#S
\toCHAR#S
\Pnext#S
\pgfplotsplothandlermeshusepathstroke#*
\pgfplotsplothandlermeshusepathfill#*
\pgfplotsplothandlermeshusepathfillstroke#*
\rangea#S
\rangeb#S
\factor#S
\simplecoordinate(x,y,z)#*
\curelem#S

##     └── pgfplotsmeshplotimage.code.tex
# no new user commands

## pgfplots.scaling.code.tex
\pgfplotssetaxesfromazel{azimuth}{elevation}{macro%cmd}#*d
\sinaz#S
\cosaz#S
\sinel#S
\cosel#S
\pgfplotsgetnormalforcurrentview#*
\pgfplotscoordmathnotifydatascalesetfor{arg}#*

## pgfplotscoordprocessing.code.tex
\pgfplotspointdescriptionxy{x}{y}#*
\pgfplotsqpointdescriptionxy{x}{y}#*
\pgfplotspointmaxminmin#*
\pgfplotspointminmaxmin#*
\pgfplotspointminminmin#*
\pgfplotspointxaxis#*
\pgfplotspointxaxislength#*
\pgfplotspointyaxis#*
\pgfplotspointyaxislength#*
\pgfplotspointzaxis#*
\pgfplotspointzaxislength#*
\pgfplotspointcenter#*
\pgfplotspointunitx#*
\pgfplotspointunity#*
\pgfplotsunitxlength#*
\pgfplotsunitylength#*
\pgfplotsunitxinvlength#*
\pgfplotsunityinvlength#*
\pgfplotspointunitz#*
\pgfplotsunitzlength#*
\pgfplotsunitzinvlength#*
\pgfplotspointticklabelcs{axis}{coord}#*
\pgfplotspointticklabelcs[default shift]{axis}{coord}#*
\pgfplotspointticklabelnoshiftcs{axis}{coord}#*
\pgfplotsconvertunittocoordinate{axis}{dimen%l}#*
\pgfplotsqpointxyzabsolutesize{x}{y}{z}#*
\pgfplotspointonorientedsurfaceab{a}{b}#*
\pgfplotspointonorientedsurfaceabwithbshift{a}{b}{shift}#*
\pgfplotspointonorientedsurfacespec#*
\pgfplotspointonorientedsurfacespecunordered#*
\pgfplotspointonorientedsurfacespecsymbol#*
\pgfplotspointonorientedsurfaceabsetupfor %<surface string%>#*
\pgfplotspointonorientedsurfaceabsetupforsetx{x}{char}#*
\pgfplotspointonorientedsurfaceabsetupforsety{y}{char}#*
\pgfplotspointonorientedsurfaceabsetupforsetz{z}{char}#*
\pgfplotspointonorientedsurfaceA#*
\pgfplotspointonorientedsurfaceB#*
\pgfplotspointonorientedsurfaceN#*
\pgfplotspointonorientedsurfaceabtolinespec{value}{surface}#*
\pgfplotspointonorientedsurfaceabgetcontainedaxisline{value}{macro%cmd}#*d
\pgfplotsgetadjacentsurfsforaxisline{arg1}\to{arg2}{arg3}#*
\pgfplotsifaxissurfaceisforeground{surface}{true}{false}#*
\pgfplotsifaxislineisonconvexhull{surface}{true}{false}#*
\pgfplotspointonorientedsurfaceabmatchaxisline{surface}{macro%cmd}#*d
\pgfplotsmatchcubeparts{cube part}{surface}{macro%cmd}#*d
\pgfplotsqpointoutsideofaxis{axis}{coord}{dimen%l}#*
\pgfplotsqpointoutsideofaxisrel{axis}{coord}{dimen%l}#*
\pgfplotsqpointoutsideofaxistransformed{axis}{coord}{dimen%l}#*
\pgfplotspointouternormalvectorofaxis{axis}#*
\pgfplotspointouternormalvectorofaxissetv{axis}{value}#*
\pgfplotspointouternormalvectorofaxisgetv{axis}#*
\pgfplotstransformtoaxisdirection#*
\pgfplotsdeclareborderanchorforaxis{direction}{axis}{anchor name}#*
\pgfplotspointviewdir#*
\pgfplotsdeclarecoordmath{class name}{method}#*
\pgfplotscoordmathid#*
\pgfplotscoordmathparsemacro{coord math choice}{macro}#*
\pgfplotscoordmath{axis}{method}{arguments}#*
\pgfplotscoordmathclassfor{label}#*
\pgfplotscoordmathnotifydatascalesetfor{label}#*
\pgfplotssetcoordmathfor{label}{class name}#*
\pgfplotsgetcoordmathfor{label}#*
\pgfplotssetpointmetainput{input method}{arguments}#*
\pgfplotspointmetainputhandler#*
\pgfplotsaxisifhaspointmeta{true}{false}#*
\pgfplotsifpointmetaisbounded{point meta data}{true}{false}#*
\pgfplotsaxisifcontainspoint{true}{false}#*
\pgfplotsdeclarepointmetasource{name}{keyvals}#*
#keyvals:\pgfplotsdeclarepointmetasource
assign=
initfor=
activate=
LUA class=
tostring=
explicitinput=
issymbolic=
#endkeyvals
\pgfplotsscanlinelengthinitzero#*
\pgfplotsscanlinelength#*
\pgfplotsdetermineemptylinehandler#*
\pgfplotsscanlinedisablechanges#*
\pgfplotsscanlinecomplete#*
\pgfplotsscanlinelengthincrease#*
\pgfplotsscanlinelengthcleanup#*
\pgfplotsscanlinelengthinitzero#*
\pgfplotsscanlineendofinput#*
\pgfplotsplothandlerappendjumpmarker#*
\pgfplotsaxisfilteredcoordsaway#*
\pgfplotsaxisplothasjumps#*
\pgfplotsaxisplothasunboundedpointmeta#*
\ifpgfplotsaxisparsecoordinateok#*
\pgfplotsaxisparsecoordinateoktrue#*
\pgfplotsaxisparsecoordinateokfalse#*
\pgfplotsaxisplotphase#*
\pgfplotsifinplot{true}{false}#*
\pgfplotsaxispreparecoordinate#*
\pgfplotsaxisdatapointsurveyed#*
\pgfplotsaxissurveysetpointmeta#*
\pgfplotsaxisupdatelimitsforpointmeta{arg}#*
\pgfplotsaxistransformfromdatacs#*
\pgfplotsaxistransformcs{actual coordsys}{desired coordsys}#*
\pgfplotsdefinecstransform{source coordsys}{target coordsys}{code}#*
\pgfplotsaxisserializedatapointtostring#*
\pgfplotsaxisserializedatapoint#*
\pgfplotsaxisdeserializedatapointfrom{arg}#*
\pgfplotsaxisvisphasetransformpointmeta#*
\pgfplotsaxisvisphasetransformpointmetaifany#*
\pgfplotssurveyphaseaddoptionsbeforesurveybegins{options}#*
\pgfplotsplothandlersurveyaddoptions{options}#*
\pgfplotsifinaddplottablestruct{true}{false}#*
\coordindex#*
\columnerrorx#S
\columnerrory#S
\columnerrorz#S
\plotnum#S
\plotnumofactualtype#S
\pgfplotsaxisvisphasegetpoint#*
\pgfplotspointgetcoordinates#*
\pgfplotspointgetcoordinates{point}#*
\pgfplotspointgetnormalizedcoordinates#*
\pgfplotspointgetcoordinatesfromnormalized#*
\pgfplotsaxisvisphasetransformcoordinate{x-macro}{y-macro}{z-macro}#*
\pgfplotsaxisvisphasepreparedatapoint#*
\pgfplotsaxisvisphasetransformcoordinateentry{x, y, or z}{input}#*
\pgfplotstransformplotattime{fraction}#*
\pgfplotspointplotattimeclearcache#*
\pgfplotspointplotattimegetfromcache{arg}#*
\pgfplotspointplotattimeaddtocache{arg}#*
\pgfplotspointplotattime{fraction}#*
\pgfplotsplothandlergraphics#*
\pgfplotsplothandlergraphicspointmappoint(x,y,z)(a,b)#*
\pgfplotsplothandlergraphicspointmapcomputerequiredview#*
\pgfplotsE#*
\pgfplotsmathfloatviewdepthxyz{x}{y}{z}#S
\pgfplotsmathvectorviewdepth{x,y,z}#*
\pgfplotsmathviewdepthxyz{x}{y}{z}#S
\pgfshell{shell command}#*
\pgfshell[filename prefix]{shell command}#*

## pgfplots.errorbars.code.tex
# no new user commands

## pgfplots.markers.code.tex
# no new user commands

## pgfplotsticks.code.tex
\ticknum#*
\tick#*
\nexttick#*
\pgfplotsvalueoflargesttickdimen{x, y, or z}#*
\pgfplotsqpointoutsideofticklabelaxis{x, y, or z}{coord}{dimen%l}#*
\pgfplotsqpointoutsideofticklabelaxisrel{x, y, or z}{coord}{dimen%l}#*
\pgfplotsqpointoutsideofticklabelaxistransformed{x, y, or z}{coord}{dimen%l}#*
\pgfplotsticklabelaxisspec{x, y, or z}#*
\pgfplotspointouternormalvectorofticklabelaxis{x, y, or z}#*
\Hmacro#S
\Hmacrobaseten#S
\MIN#S
\MAX#S
\MINH#S
\desirednumticks#S
\Wr#S
\pgfplotsdeclareborderanchorforticklabelaxis{axis}{anchor name}#*

## pgfplots.paths.code.tex
# no new user commands

## tikzlibrarypgfplots.contourlua.code.tex
# no new user commands
