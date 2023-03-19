# schulma package
# Matthew Bertucci 2023/03/15 for v1.4

#include:mathtools
#include:autoaligne
#include:icomma
#include:pgfplots
#include:tikzlibraryshapes.misc

#keyvals:\usepackage/schulma#c
ohne-icomma
#endkeyvals

\begin{Kosy}#\pictureHighlight
\begin{Kosy}[pgfplots options%keyvals]
\end{Kosy}

\LGS{Gleichungen%formula}
\ehoch{Exponent}#m
\diff{Variable}#m
\Pkt{x%formula}{y%formula}
\Pkt[Name%formula]{x%formula}{y%formula}
\PktR{x%formula}{y%formula}{z%formula}
\Pkt[Name%formula]{x%formula}{y%formula}{z%formula}
\Vek{x%formula}{y%formula}{z%formula}
\VekBr{x%formula}{y%formula}{z%formula}
\GTRY{index}
\GTRY{index}[term%formula]

#keyvals:\node#c
Kreuz
#endkeyvals

#keyvals:\begin{Kosy}#c
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
