# tikz package
# muzimuzhi, 12 Nov 2019, 23 Feb 2020, 8 Aug 2020
# Matthew Bertucci 12/6/2021 for v3.1.9a

# Dependency Tree:
# tikz.sty
# ├── pgf.sty
# ├── pgffor.sty
# └── tikz.code.tex
#     ├── pgflibraryplothandlers.code.tex
#     ├── pgfmodulematrix.code.tex
#     │   └── pgfmoduleshapes.code.tex
#     └── tikzlibrarytopaths.code.tex

#include:pgf
#include:pgffor

### < Commands > ###
\begin{scope}
\begin{scope}[options%keyvals]
\end{scope}
\scoped
\scoped[options%keyvals]
\tikzset{options%keyvals}
\tikzoption{key%plain}{value}#*
\tikzaddafternodepathoption{arg}#S
\tikzparentanchor#*
\tikzchildanchor#*
\tikzparentnode#*
\tikzchildnode#*
\tikzstyle{style%specialDef} = [definition]#s#%tikzstyle
\begin{tikzpicture}#\pictureHighlight
\begin{tikzpicture}[options%keyvals]
\end{tikzpicture}
\tikzpicture#S
\endtikzpicture#S
\tikz
\tikz[options%keyvals]
\tikzdeclarecoordinatesystem{name}{code}#*
\tikzaliascoordinatesystem{new name}{old name}#*
\tikzifinpicture{in code}{out code}#*
\tikzaddtikzonlycommandshortcutlet{short cmd%cmd}{cmd}#*d
\tikzaddtikzonlycommandshortcutdef{short cmd%cmd}{def}#*d
\path %<〈path spec〉%>;
\path[%<options%>] %<〈path spec〉%>;
\draw %<〈path spec〉%>;
\draw[%<options%>] %<〈path spec〉%>;
\fill %<〈path spec〉%>;
\fill[%<options%>] %<〈path spec〉%>;
\filldraw %<〈path spec〉%>;
\filldraw[%<options%>] %<〈path spec〉%>;
\pattern %<〈path spec〉%>;
\pattern[%<options%>] %<〈path spec〉%>;
\shade %<〈path spec〉%>;
\shade[%<options%>] %<〈path spec〉%>;
\shadedraw %<〈path spec〉%>;
\shadedraw[%<options%>] %<〈path spec〉%>;
\clip %<〈path spec〉%>;
\clip[%<options%>] %<〈path spec〉%>;
\useasboundingbox %<〈path spec〉%>;#*
\node %<〈node spec〉%> {%<content%>};
\node[%<options%>] %<〈node spec〉%> {%<content%>};
\coordinate (%<name%>);
\coordinate[%<options%>] (%<name%>);
\nodepart{part name}
\nodepart[options%keyvals]{part name}
\pic %<〈node spec〉%> {%<pic type%>};
\pic[%<options%>] %<〈node spec〉%> {%<pic type%>};
\matrix %<〈node spec〉%> {%<content%>};
\matrix[%<options%>] %<〈node spec〉%> {%<content%>};
\pgfextra{code}#*
\endpgfextra#*
\pgfstrokehook#S
\tikztostart#*
\tikztotarget#*
\tikztonodes#*
\tikzlastnode#*
\pgfplotlastpoint#S
\tikzerror{message%text}#S
\tikzleveldistance#*
\tikzsiblingdistance#*
\tikztreelevel#*
\tikznumberofchildren#*
\tikznumberofcurrentchild#*
\tikzpathuptonow#S
\tikzpictext#*
\tikzpictextoptions#*
\tikzdeclarepic{arg1}{arg2}#S
\p#S
\x#S
\y#S
\tikzgdeventcallback{arg1}{arg2}#S
\tikzgdeventgroupcallback{arg1}#S
\tikzgdlatenodeoptionacallback{arg1}#S

### < Libraries > ###
\usetikzlibrary{library list%keyvals}#u
#keyvals:\usetikzlibrary#c
3d
angles
animations
arrows.meta
automata
babel
backgrounds
bayesnet
bbox
bending
braids
calc
calendar
calligraphy
cd
celtic
chains
circuits
circuits.ee
circuits.ee.IEC
circuits.ee.IEC.relay
circuits.logic
circuits.logic.CDH
circuits.logic.IEC
circuits.logic.US
circuits.plc.ladder
circuits.plc.sfc
colorbrewer
commutative-diagrams
curvilinear
datavisualization
datavisualization.3d
datavisualization.barcharts
datavisualization.formats.functions
datavisualization.polar
datavisualization.sparklines
decorations
decorations.footprints
decorations.fractals
decorations.markings
decorations.pathmorphing
decorations.pathreplacing
decorations.shapes
decorations.text
dubins
ducks
er
ext.calendar-plus
ext.misc
ext.node-families
ext.node-families.shapes.geometric
ext.paths.arcto
ext.paths.ortho
ext.paths.timer
ext.patterns.images
ext.positioning-plus
ext.scalepicture
ext.shapes.circlearrow
ext.shapes.circlecrosssplit
ext.shapes.heatmark
ext.shapes.rectangleroundedcorners
ext.shapes.superellipse
ext.shapes.uncenteredrectangle
ext.topaths.arcthrough
ext.transformations.mirror
external
fadings
fill.hexagon
fill.image
fill.rhombus
fit
fixedpointarithmetic
folding
fpu
graphdrawing
graphs
graphs.standard
hobby
intersections
karnaugh
knots
lindenmayersystems
math
matrix
matrix.skeleton
mindmap
nef
ocgx
optics
overlay-beamer-styles
patterns
patterns.images
patterns.meta
penrose
perspective
petri
plothandlers
plotmarks
positioning
profiler
quantikz
quotes
rdf
rulercompass
scopes
shadings
shadows
shadows.blur
shapes
shapes.arrows
shapes.callouts
shapes.gates.ee
shapes.gates.ee.IEC
shapes.gates.logic
shapes.gates.logic.IEC
shapes.gates.logic.US
shapes.geometric
shapes.misc
shapes.multipart
shapes.symbols
spath3
spy
svg.path
swigs
switching-architectures
through
tikzmark
topaths
tqft
trees
turtle
views
zx-calculus
#endkeyvals

### < Keys > ###
# Note many keys are available to commands for which they don't make sense; some care was taken to exclude these cases
# Only some keys from the many libraries are listed below

#keyvals:\tikzset#c
every picture/.style={%<options%>}
#endkeyvals

#keyvals:\begin{tikzpicture}#c,\tikz#c,\tikzset#c
baseline
baseline=%<<dimen> or <coord> or default%>
execute at begin picture=%<code%>
execute at end picture=%<code%>
every scope/.style={%<options%>}
#endkeyvals

#keyvals:\begin{scope}#c,\tikzset#c,\scoped#c
execute at begin scope=%<code%>
execute at end scope=%<code%>
transparency group
transparency group=%<options%>
#endkeyvals

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c
every path/.style={%<options%>}
every circle/.style={%<options%>}
every to/.style={%<options%>}
every node/.style={%<options%>}
every lower node part/.style={%<options%>}
every label/.style={%<options%>}
every pin/.style={%<options%>}
every pin edge/.style={%<options%>}
every edge/.style={%<options%>}
every pic/.style={%<options%>}
every new ->/.style={%<options%>}
every new --/.style={%<options%>}
every new <->/.style={%<options%>}
every new <-/.style={%<options%>}
every new -!-/.style={%<options%>}
every matrix/.style={%<options%>}
every outer matrix/.style={%<options%>}
every child/.style={%<options%>}
every child node/.style={%<options%>}
every plot/.style={%<options%>}
every mark/.style={%<options%>}
every loop/.style={%<options%>}
execute at begin to=%<code%>
execute at end to=%<code%>
execute at begin node=%<code%>
execute at end node=%<code%>
trim left
trim left=%<<dimen> or <coord> or default%>
trim right
trim right=%<<dimen> or <coord> or default%>
tri lowlevel#true,false
name prefix=%<text%>
name suffix=%<text%>
badness warnings for centered text#true,false
node halign header=%<macro%>
level/.style={%<options%>}
level %<n%>/.style={%<options%>}
level distance=##L
sibling distance=##L
edge from parent/.style={%<options%>}
# plots of functions
variable=%<macro%>
samples=%<number%>
domain=%<start%>:%<end%>
samples at=%<samples list%>
parametric#true,false
range=%<start%>:%<end%>
yrange=%<start%>:%<end%>
xrange=%<start%>:%<end%>
id=%<id%>
prefix
raw gnuplot
mark=%<mark%>
mark repeat=%<number%>
mark phase=%<number%>
mark indices=%<list%>
mark size=##L
mark options={%<options%>}
no marks
no markers
sharp plot
smooth
tension=%<value%>
smooth cycle
const plot
const plot mark left
const plot mark right
const plot mark mid
jump mark left
jump mark right
jump mark mid
ycomb
xcomb
polar comb
ybar
xbar
ybar interval
xbar interval
only marks
# blend modes
blend mode=#normal,multiply,screen,overlay,darken,lighten,color dodge,color burn,hard light,soft light,difference,exclusion,hue,saturation,color,luminosity
blend group=#normal,multiply,screen,overlay,darken,lighten,color dodge,color burn,hard light,soft light,difference,exclusion,hue,saturation,color,luminosity
matrix/inner style order={%<list%>}
# plothandlers pgflibrary (loaded by default)
bar width=##L
bar shift=##L
bar interval shift=%<factor%>
bar interval width=%<scale%>
gap around stream point=##L
#endkeyvals

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c,\path#c,\draw#c,\fill#c,\filldraw#c,\pattern#c,\shade#c,\shadedraw#c,\clip#c,\node#c,\coordinate#c,\nodepart#c,\pic#c,\matrix#c,\calendar#c,\chainin#c,\arrow#c,\arrowreversed#c
## coordinate systems
x=%<<dimen> or <coord>%>
y=%<<dimen> or <coord>%>
z=%<<dimen> or <coord>%>
## paths
name=%<name%>
append after command=%<path%>
prefix after command=%<path%>
rounded corners
rounded corners=##L
sharp corners
x radius=%<<num> or <dimen>%>
y radius=%<<num> or <dimen>%>
radius=##L
at=%<coord%>
start angle=%<degrees%>
end angle=%<degrees%>
delta angle=%<degrees%>
step=%<<num> or <dimen> or <coord>%>
xstep=%<<num> or <dimen>%>
ystep=%<<num> or <dimen>%>
help lines
bend=%<coord%>
bend pos=%<fraction%>
parabola height=##L
bend at start
bend at end
to path=%<path%>
save path=%<macro%>
use path=%<macro%>
## actions on paths
color=#%color
%color
draw
draw=#%color
line width=##L
ultra thin
very thin
thin
semithick
thick
very thick
ultra thick
line cap=#round,rect,butt
line join=#round,bevel,miter
miter limit=%<factor%>
dash pattern=%<dash pattern%>
dash phase=%<dash phase%>
dash=%<dash pattern%> phase %<dash phase%>
dash expand off
solid
dotted
densely dotted
loosely dotted
dashed
densely dashed
loosely dashed
dash dot
densely dash dot
loosely dash dot
dash dot dot
densely dash dot dot 
loosely dash dot dot
double
double=#%color
double distance=##L
double distance between line centers=##L
double equal sign distance
fill
fill=#%color
pattern
pattern=%<name%>
pattern color=#%color
nonzero rule
even odd rule
shade
shading=#axis,radial,ball
shading angle=%<degrees%>
## arrows
arrows=%<start spec%>-%<end spec%>
->
<-
<->
tips
tips=#true,proper,on draw,on proper draw,never,false
>=%<end arrow spec%>
shorten <=##L
shorten >=##L
## nodes: shape, text, and position
inner sep=##L
inner xsep=##L
inner ysep=##L
outer sep=%<<dimen> or auto%>
outer xsep=##L
outer ysep=##L
minimum height=##L
minimum width=##L
minimum size=##L
shape aspect=%<aspect ratio%>
shape border uses incircle#true,false
shape border rotate=%<degrees%>
text=#%color
node font=%<font commands%>
font=%<font commands%>
text width=##L
align=#left,flush left,right,flush right,center,flush center,justify
text height=##L
text depth=##L
anchor=#north west,north,north east,west,center,east,mid west,mid,mid east,base west,base,base east,south west,south,south east,text
above
above=##L
below
below=##L
right
right=##L
left
left=##L
above left
above right
below left
below right
centered
# transformations
transform shape
transform shape nonlinear#true,false
# placing nodes explicitly
pos=%<fraction%>
auto
auto=#left,right,false
swap
sloped
allow upside down#true,false
midway
near start
near end
very near start
very near end
at start
at end
label=%<angle%>:%<text%>
label=[%<options%>]%<angle%>:%<text%>
label position=%<degrees%>
absolute#true,false
label distance=##L
pin=%<angle%>:%<text%>
pin=[%<options%>]%<angle%>:%<text%>
pin distance=##L
pin edge={%<options%>}
# referencing nodes
remember picture#true,false
overlay#true,false
# making trees grow
growth parent anchor=#north west,north,north east,west,center,east,mid west,mid,mid east,base west,base,base east,south west,south,south east,text
growth function=%<macro%>
edge from parent path=%<path%>
# transparency
draw opacity=%<value%>
opacity=%<value%>
transparent
ultra nearly transparent
very nearly transparent 
nearly transparent
semitransparent
nearly opaque 
very nearly opaque
ultra nearly opaque
opaque
fill opacity=%<value%>
text opacity=%<value%>
## transformations
shift={%<coordinate%>}
shift only
xshift=##L
yshift=##L
scale=%<scale%>
xscale=%<scale%>
yscale=%<scale%>
xslant=%<factor%>
yslant=%<factor%>
rotate=%<degrees%>
rotate around={%<degree%>:%<coordinate%>}
rotate around x=%<degrees%>
rotate around y=%<degrees%>
rotate around z=%<degrees%>
cm={%<a,b,c,d,coord%>}
reset cm
transform canvas={%<options%>}
# topaths library (loaded by default)
out=%<degrees%>
in=%<degrees%>
relative#true,false
bend left
bend left=%<degrees%>
bend right
bend right=%<degrees%>
bend angle=%<degrees%>
looseness=%<number%>
out looseness=%<number%>
in looseness=%<number%>
min distance=##L
max distance=##L
out min distance=##L
out max distance=##L
in min distance=##L
in max distance=##L
distance=##L
out distance=##L
in distance=##L
out control=%<coord%>
in control=%<coord%>
controls=%<coord1%> and %<coord2%>
## others
%tikzstyle
#endkeyvals

# path specific keys
#keyvals:\path#c,\draw#c,\fill#c,\filldraw#c,\pattern#c,\shade#c,\shadedraw#c,\clip#c
use as bounding box
clip
preaction={%<options%>}
postaction={%<options%>}
late options={%<options%>}
pic actions
#endkeyvals

# node specific keys
#keyvals:\node#c,\coordinate#c,\nodepart#c,\pic#c
matrix#true,false
shape=%<shape%>
circle
rectangle
#endkeyvals

# pic specific keys
#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c,\pic#c
pic type=%<type%>
pics/code=%<code%>
pics/foreground code=%<code%>
pics/background code=%<code%>
pic text=%<text%>
pic text options={%<options%>}
#endkeyvals

#matrix specific keys
#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c,\matrix#c
column sep=##L
row sep=##L
every cell={%<row%>}{%<column%>}
cells={%<options%>}
nodes={%<options%>}
column %<n%>/.style={%<options%>}
every odd column/.style={%<options%>}
every even column/.style={%<options%>}
row %<m%>/.style={%<options%>}
every odd row/.style={%<options%>}
every even row/.style={%<options%>}
row %<m%> column %<n%>/.style={%<options%>}
execute at begin cell=%<code%>
execute at end cell=%<code%>
execute at empty cell=%<code%>
matrix anchor=%<anchor%>
ampersand replacement=%<macro%>
#endkeyvals

## from plothandlers pgflibrary
\pgfplothandlercurveto#*
\pgfsetplottension{tension}#*
\pgfplothandlerclosedcurve#*
\pgfplothandlerxcomb#*
\pgfplothandlerycomb#*
\pgfplotxzerolevelstreamstart#*
\pgfplotxzerolevelstreamend#*
\pgfplotxzerolevelstreamnext#*
\pgfplotyzerolevelstreamstart#*
\pgfplotyzerolevelstreamend#*
\pgfplotyzerolevelstreamnext#*
\pgfplotxzerolevelstreamconstant{dimen%l}#*
\pgfplotyzerolevelstreamconstant{dimen%l}#*
\pgfplotbarwidth#*
\pgfplotbarshift#*
\pgfplothandlerybar#*
\pgfplothandlerxbar#*
\pgfplothandlerybarinterval#*
\pgfplothandlerxbarinterval#*
\pgfplothandlerconstantlineto#*
\pgfplothandlerconstantlinetomarkright#*
\pgfplothandlerconstantlinetomarkmid#*
\pgfplothandlerjumpmarkright#*
\pgfplothandlerjumpmarkleft#*
\pgfplothandlerjumpmarkmid#*
\pgfplothandlerpolarcomb#*
\pgfplothandlermark{mark code}#*
\pgfsetplotmarkrepeat{repeat count}#*
\pgfsetplotmarkphase{index}#*
\pgfplothandlermarklisted{code}{positions}#*
\pgfdeclareplotmark{name}{code}#*
\pgfsetplotmarksize{size%l}#*
\pgfplotmarksize#*
\pgfuseplotmark{name}#*
\pgfplothandlergaplineto#*
\pgfplothandlergapcycle#*

## from matrix pgfmodule
\ifpgfmatrix#S
\pgfmatrixtrue#S
\pgfmatrixfalse#S
\pgfmatrixcurrentrow#*
\pgfmatrixcurrentcolumn#*
\pgfmatrixbeforeassemblenode{code}#*
\pgfsetmatrixrowsep{sep list}#*
\pgfsetmatrixcolumnsep{sep list}#*
\pgfmatrixrowsep#*
\pgfmatrixcolumnsep#*
\pgfmatrix{shape}{anchor}{name}{usage}{shift}{precode}{matrix cells}#*
\pgfmatrixnextcell#*
\pgfmatrixnextcell[additional sep list]#*
\pgfmatrixbegincode#*
\pgfmatrixendcode#*
\pgfmatrixemptycode#*
\pgfmatrixendrow#*
\pgfmatrixendrow[additional sep list]#*

## from topaths tikzlibrary (loaded by default)
# no new user commands
