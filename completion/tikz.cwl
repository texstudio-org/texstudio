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
\tikzset{options%keyvals}
\tikzoption{key%plain}{value}#*
\tikzaddafternodepathoption{arg1}#S
\tikzparentanchor#*
\tikzchildanchor#*
\tikzparentnode#*
\tikzchildnode#*
\tikzstyle{style} = [definition]#s#%tikzstyle
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
\path
\path[options%keyvals]
\draw
\draw[options%keyvals]
\fill
\fill[options%keyvals]
\filldraw
\filldraw[options%keyvals]
\pattern
\pattern[options%keyvals]
\shade
\shade[options%keyvals]
\shadedraw
\shadedraw[options%keyvals]
\clip
\clip[options%keyvals]
\useasboundingbox#*
\node
\node[options%keyvals] (node name) {};#s#%node
\coordinate
\coordinate[options%keyvals]
\nodepart{part name}
\nodepart[options%keyvals]{part name}
\pic
\pic[options%keyvals]
\matrix
\matrix[options%keyvals]
\pgfextra{code}#*
\endpgfextra#*
\pgfstrokehook#*
\tikztostart#*
\tikztotarget#*
\tikztonodes#*
\tikzlastnode#*
\pgfplotlastpoint#*
\tikzerror{message%text}#*
\tikzleveldistance#*
\tikzsiblingdistance#*
\tikztreelevel#*
\tikznumberofchildren#*
\tikznumberofcurrentchild#*
\tikzpathuptonow#S
\tikzpictext#*
\tikzpictextoptions#*
\tikzdeclarepic{arg1}{arg2}#*
\p#S
\x#S
\y#S
\tikzgdeventcallback{arg1}{arg2}#S
\tikzgdeventgroupcallback{arg1}#S
\tikzgdlatenodeoptionacallback{arg1}#S

### < Libraries > ###
\usetikzlibrary{library list%keyvals}
#keyvals:\usetikzlibrary#c
3d
angles
animations
arrows
arrows.meta
arrows.spaced
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
circular
commutative-diagrams
curvilinear
datavisualization.3d
datavisualization.barcharts
datavisualization
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
er
external
fadings
fill.image
fill.hexagon
fill.rhombus
fit
fixedpointarithmetic
folding
fpu
graphdrawing
graphdrawing.evolving
graphs
graphs.standard
hobby
intersections
karnaugh
knots
layered
lindenmayersystems
math
matrix
matrix.skeleton
mindmap
misc
nef
optics
overlay-beamer-styles
paths.arcto
paths.ortho
paths.timer
patterns
patterns.images
patterns.meta
penrose
perspective
petri
phylogenetics
pie
plothandlers
plotmarks
positioning
profiler
quantikz
quotes
rdf
routing
rulercompass
scopes
shadings
shadows
shapes
shapes.arrows
shadows.blur
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
topaths.arcthrough
tqft
transformations.mirror
trees
turtle
views
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
every label quotes/.style={%<options%>}
every pin quotes/.style={%<options%>}
every edge/.style={%<options%>}
every edge quotes/.style={%<options%>}
every pic/.style={%<options%>}
every pic quotes/.style={%<options%>}
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
quotes mean label
quotes mean pin
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
# plothandlers library
bar width=##L
bar shift=##L
bar interval shift=%<factor%>
bar interval width=%<scale%>
matrix/inner style order={%<list%>}
#endkeyvals

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c,\path#c,\draw#c,\fill#c,\filldraw#c,\pattern#c,\shade#c,\shadedraw#c,\clip#c,\node#c,\coordinate#c,\nodepart#c,\pic#c,\matrix#c,\calendar#c,\chainin#c,\arrow#c,\arrowreversed#c
## coordinate systems
x=%<<dimen> or <coord>%>
y=%<<dimen> or <coord>%>
z=%<<dimen> or <coord>%>
## intersections library
name path=%<path%>
name path global=%<path%>
name intersections={%<options%>}
turn
current point is local#true,false
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
# positioning library
on grid#true,false
node distance=##L
base left=
base right=
mid left=
mid right=
above=of %<node%>
below=of %<node%>
right=of %<node%>
left=of %<node%>
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
# quotes library
node quotes mean=%<replacement%>
# referencing nodes
remember picture#true,false
overlay#true,false
# graphs library
every new ->
every new --
every new <->
every new <-
every new -!-
new set=%<set name%>
set=%<set name%>
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
# fadings library
path fading
path fading=%<name%>
fit fading#true,false
fading transform={%<options%>}
fading angle=%<degrees%>
scope fading=%<name%>
# decorations library
decoration={%<options%>}
decorate#true,false
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
# topaths library
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
\ifpgfmatrix#*
\pgfmatrixtrue#*
\pgfmatrixfalse#*
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

## from shapes pgfmodule (loaded by matrix pgfmodule)
\pgfnodeparttextbox#*
\pgfmultipartnode{shape}{anchor}{name}{path usage cmd}#*
\pgfnode{shape}{anchor}{label text}{name}{path usage cmd}#*
\pgfpositionnodelater{macro}#*
\pgfpositionnodelatername#*
\pgfpositionnodelaterminx#*
\pgfpositionnodelatermaxx#*
\pgfpositionnodelaterminy#*
\pgfpositionnodelatermaxy#*
\ifpgflatenodepositioning#*
\pgflatenodepositioningtrue#*
\pgflatenodepositioningfalse#*
\pgfpositionnodelaterbox#*
\pgfpositionnodenow{coordinate}#*
\pgffakenode{node name}#*
\pgfnodepostsetupcode{node name}{code}#*
\pgfnodealias{new name}{existing name}#*
\pgfnoderename{new name}{existing name}#*
\pgfcoordinate{name}{coordinate}#*
\pgfdeclaregenericanchor{anchor}{code}#*
\pgfpointanchor{node}{anchor}#*
\pgfpointshapeborder{node}{point}#*
\pgfgetnodeparts{macro}{shape name}#*d
\pgfdeclareshape{shape name}{shape spec}#*
\centerpoint#S
\ifpgfshapeborderusesincircle#*
\pgfshapeborderusesincircletrue#*
\pgfshapeborderusesincirclefalse#*
\northeast#S
\southwest#S
\radius#S
\nodeparts{list of node parts}#*
\savedanchor{cmd}{code}#*d
\saveddimen{cmd}{code}#*d
\savedmacro{cmd}{code}#*d
\addtosavedmacro{macro}#*
\anchor{name}{code}#*
\deferredanchor{name}{code}#*
\anchorborder{code}#*
\backgroundpath{code}#*
\foregroundpath{code}#*
\behindbackgroundpath{code}#*
\beforebackgroundpath{code}#*
\behindforegroundpath{code}#*
\beforeforegroundpath{code}#*
\inheritsavedanchors#*
\inheritsavedanchors[from={%<shape name%>}]#*
\inheritbehindbackgroundpath#*
\inheritbehindbackgroundpath[from={%<shape name%>}]#*
\inheritbackgroundpath#*
\inheritbackgroundpath[from={%<shape name%>}]#*
\inheritbeforebackgroundpath#*
\inheritbeforebackgroundpath[from={%<shape name%>}]#*
\inheritbehindforegroundpath#*
\inheritbehindforegroundpath[from={%<shape name%>}]#*
\inheritforegroundpath#*
\inheritforegroundpath[from={%<shape name%>}]#*
\inheritbeforeforegroundpath#*
\inheritbeforeforegroundpath[from={%<shape name%>}]#*
\inheritanchor#*
\inheritanchor[from={%<shape name%>}]{name}#*
\inheritanchorborder#*
\inheritanchorborder[from={%<shape name%>}]#*

## from topaths tikzlibrary
# no new user commands

## Commands in those libraries shipped with tikz also listed here with #S
## tikz loads only topaths by default; rest must be loaded with \usetikzlibrary
## If another package loads a library the commands can be copied to that package's cwl with #S removed or replaced with #*

## 3d tikzlibrary
# no new user commands

## angles tikzlibrary
# no new user commands

## animations tikzlibrary
# loads animations pgfmodule
\tikzanimateset{options%keyvals}#S
\tikzanimationattributesset{options%keyvals}#S
\tikzanimationdefineattribute{attribute}{config}#S
\tikzanimationdefineattributelist{name}{list of attributes}#S
\tikzanimationattachto{name}{animation code}#S

## arrows tikzlibrary
# loads arrows pgf library
# no new user commands

## automata tikzlibrary
# loads shapes.multipart tikzlibrary
# no new user commands

## babel tikzlibrary
# no new user commands

## backgrounds tikzlibrary
# no new user commands

## bending tikzlibrary
# loads bending pgfmodule
# no new user commands

## calc tikzlibrary
# no new user commands

## calendar tikzlibrary
# loads pgfcalendar package
\calendar#S
\calendar[options%keyvals]
#keyvals:\calendar#c
dates=%<start%> to %<end%>
day xshift=##L
day yshift=##L
month xshift=##L
month yshift=##L
day code={%<code%>}
day text=%<text%>
month code={%<code%>}
month text=%<text%>
year code={%<code%>}
year text=%<text%>
if=
execute before day scope={%<code%>}
execute at begin day scope={%<code%>}
execute at end day scope={%<code%>}
execute after day scope={%<code%>}
day list downward
day list upward
day list right
day list left
week list
month list
month label left
month label left vertical
month label right
month label right vertical
month label above left
month label above centered
month label above right
month label below left
month label below centered
#endkeyvals
\tikzdaycode#S
\tikzdaytext#S
\tikzmonthcode#S
\tikzmonthtext#S
\tikzyearcode#S
\tikzyeartext#S
# from pgfcalendar package
\pgfcalendardatetojulian{date}{counter}#S
\pgfcalendarjuliantodate{Julian day}{year cmd%cmd}{month cmd%cmd}{day cmd%cmd}#Sd
\pgfcalendarjuliantoweekday{Julian day}{week day cmd%cmd}#Sd
\pgfcalendareastersunday{year}{cmd}#Sd
\pgfcalendarifdate{date}{tests%keyvals}{code}{else code}#S
#keyvals:\pgfcalendarifdate#c,\ifdate#c
all
Monday
Tuesday
Wednesday
Thursday
Friday
Saturday
Sunday
workday
weekend
equals=%<reference%>
at least=%<reference%>
at most=%<reference%>
between=%<start%> and %<end%>
day of month=%<number%>
end of month=%<number%>
Easter=%<number%>
#endkeyvals
\pgfcalendarifdatejulian#S
\pgfcalendarifdateweekday#S
\pgfcalendarifdateyear#S
\pgfcalendarifdatemonth#S
\pgfcalendarifdateday#S
\pgfcalendarweekdayname{week day number}#S
\pgfcalendarweekdayshortname{week day number}#S
\pgfcalendarmonthname{month number}#S
\pgfcalendarmonthshortname{month number}#S
\pgfcalendar{prefix}{start date}{end date}{rendering code}#S
\pgfcalendarprefix#S
\pgfcalendarbeginiso#S
\pgfcalendarbeginjulian#S
\pgfcalendarendiso#S
\pgfcalendarendjulian#S
\pgfcalendarcurrentjulian#S
\pgfcalendarcurrentweekday#S
\pgfcalendarcurrentyear#S
\pgfcalendarcurrentmonth#S
\pgfcalendarcurrentday#S
\ifdate{test%keyvals}{code}{else code}#S
\pgfcalendarshorthand{kind}{representation}#S
\pgfcalendarsuggestedname#S
\ifpgfcalendarmatches#S
\pgfcalendarmatchestrue#S
\pgfcalendarmatchesfalse#S

## chains tikzlibrary
# loads positioning tikzlibrary
\chainin(node name)#S
\chainin(node name)[options%keyvals]#S
\tikzchaincount#S
\tikzchaincurrent#S
\tikzchainprevious#S

## circuits tikzlibrary
# loads calc and decorations.marking tikzlibraries
\tikzcircuitssizeunit#S

## circuits.ee tikzlibrary
# loads circuits tikzlibrary and shapes.gates.ee pgflibrary
# no new user commands

## circuits.ee.IEC tikzlibrary
# loads arrows and circuits.ee tikzlibraries and shapes.gates.ee.IEC pgflibrary
# no new user commands

## circuits.logic tikzlibrary
# loads circuits tikzlibrary
# no new user commands

## circuits.logic.CDH tikzlibrary
# loads circuits.logic.US
# no new user commands

## circuits.logic.IEC tikzlibrary
# loads circuits.logic tikzlibrary and shapes.gates.logic.IEC pgflibrary
# no new user commands

## circuits.logic.US tikzlibrary
# loads circuits.logic tikzlibrary and shapes.gates.logic.US pgflibrary
# no new user commands

## datavisualization.3d tikzlibrary
# loads datavisualization tikzlibrary
# no new user commands

## datavisualization.barcharts tikzlibrary
# loads datavisualization tikzlibrary and datavisualization.barcharts pgflibrary
# no new user commands

## datavisualization tikzlibrary
# loads datavisualization pgfmodule and backgrounds tikzlibrary
\datavisualization#S
\datavisualization[options%keyvals]#S
\tikzdatavisualizationset{options%keyvals}#S
#keyvals:\datavisualization#c,\tikzdatavisualizationset#c
data point={%<options%>}
before survey=%<code%>
at start survey=%<code%>
at end survey=%<code%>
after survey=%<code%>
before visualization=%<code%>
at start visualization=%<code%>
at end visualization=%<code%>
after visualization=%<code%>
new object={%<options%>}
class=%<class name%>
when=%<phase name%>
store=%<key name%>
before creation=%<code%>
after creation=%<code%>
arg1=%<value%>
arg2=%<value%>
arg3=%<value%>
arg4=%<value%>
arg5=%<value%>
arg6=%<value%>
arg7=%<value%>
arg8=%<value%>
arg1 from key=%<key%>
arg2 from key=%<key%>
arg3 from key=%<key%>
arg4 from key=%<key%>
arg5 from key=%<key%>
arg6 from key=%<key%>
arg7 from key=%<key%>
arg8 from key=%<key%>
arg1 handle from key=%<key%>
arg2 handle from key=%<key%>
arg3 handle from key=%<key%>
arg4 handle from key=%<key%>
arg5 handle from key=%<key%>
arg6 handle from key=%<key%>
arg7 handle from key=%<key%>
arg8 handle from key=%<key%>
new axis base=%<axis name%>
all axes={%<options%>}
new Cartesian axis=%<name%>
scientific axes
scientific axes={%<options%>}
school book axes
school book axes={%<options%>}
xy Cartesian
xy axes={%<options%>}
xyz Cartesian cabinet
xyz axes={%<options%>}
uv Cartesian 
uv axes={%<options%>}
uvw Cartesian cabinet
uvw axes={%<options%>}
step=%<value%>
minor steps between steps
minor steps between steps=%<number%>
phase=%<value%>
about=%<number%>
about strategy=%<list%>
standard about strategy
euro about strategy
half about strategy
decimal about strategy
quarter about strategy
int about strategy
many
some
few
none
major={%<options%>}
minor={%<options%>}
subminor={%<options%>}
common={%<options%>}
at=%<list%>
major at=%<list%>
minor at=%<list%>
subminor at=%<list%>
also at=%<list%>
major also at=%<list%>
minor also at=%<list%>
subminor also at=%<list%>
style={%<TikZ options%>}
styling
node style={%<TikZ options%>}
node styling
grid layer/.style={%<options%>}
every grid/.style={%<options%>}
every major grid/.style={%<options%>}
every minor grid/.style={%<options%>}
every subminor grid/.style={%<options%>}
every ticks={%<options%>}
every major ticks={%<options%>}
every minor ticks={%<options%>}
every subminor ticks={%<options%>}
tick layer={%<options%>}
tick node layer={%<options%>}
options at=%<value%> at [%<options%>]
no tick text at=%<value%>
tick prefix=%<text%>
tick suffix=%<text%>
tick unit=%<math text%>
tick typesetter=%<value%>
tick text low even padding=##L
tick text low odd padding=##L
tick text high even padding=##L
tick text high odd padding=##L
tick text odd padding=##L
tick text even padding=##L
tick text padding=##L
stack=##L
stack'=##L
compute step=%<code%>
low=#min,max,padded min,padded max
high=#min,max,padded min,padded max
padded
axis layer/.style={%<options%>}
every axis/.style={%<options%>}
direction axis=%<axis name%>
tick length=##L
tick text at low#true,false
tick text at high#true,false
no tick text
new axis system={%<name%>}{%<setup%>}{%<default opts%>}{%<application opts%>}
every visualizer/.style={%<options%>}
visualize as line
visualize as line=%<visualizer name%>
visualize as smooth line
visualize as smooth line=%<visualizer name%>
visualize as scatter
visualize as scatter=%<visualizer name%>
new visualizer={%<name%>}{%<options%>}{%<legend entry options%>}
style sheet=#vary thickness,vary dashing,vary thickness and dashing,cross marks,strong colors,vary hue,shades of blue,shades of red,gray scale,
every data set label/.style={%<options%>}
every label in data/.style={%<options%>}
new legend
new legend=%<legend name%>
legend={%<options%>}
every label in legend/.style={%<options%>}
new legend entry={%<options%>}
# datavisualization.polar library
scientific polar axes
scientific polar axes={%<options%>}
new polar axes={%<angle axis name%>}{%<radius axis name%>}
#endkeyvals
\tikzpointandanchordirection{code1}{code2}#S
\tikzdvvisualizercounter#S
\tikzdvdeclarestylesheetcolorseries{name}{color model}{init color}{step}#S

## datavisualization.formats.functions tikzlibrary
# loads datavisualization tikzlibrary and datavisualization.formats.functions pgflibrary
# no new user commands

## datavisualization.polar tikzlibrary
# loads datavisualization tikzlibrary and datavisualization.polar pgflibrary
# no new user commands

## datavisualization.sparklines tikzlibrary
# loads datavisualization tikzlibrary
# no new user commands

## decorations tikzlibrary
# loads decorations pgfmodule
# no new user commands

## decorations.footprints tikzlibrary
# loads decorations tikzlibrary and decorations.footprints pgflibrary
# no new user commands

## decorations.fractals tikzlibrary
# loads decorations tikzlibrary and decorations.fractals pgflibrary
# no new user commands

## decorations.markings tikzlibrary
# loads decorations tikzlibrary and decorations.markings pgflibrary
\arrow{arrow end tip}#S
\arrow[options%keyvals]{arrow end tip}#S
\arrowreversed{arrow end tip}#S
\arrowreversed[options%keyvals]{arrow end tip}#S

## decorations.pathmorphing tikzlibrary
# loads decorations tikzlibrary and decorations.pathmorphing pgflibrary
# no new user commands

## decorations.pathreplacing tikzlibrary
# loads decorations tikzlibrary and decorations.pathreplacing pgflibrary
\tikzinputsegmentfirst#S
\tikzinputsegmentlast#S
\tikzinputsegmentsupporta#S
\tikzinputsegmentsupportb#S

## decorations.shapes tikzlibrary
# loads decorations tikzlibrary and decorations.shapes pgflibrary
# no new user commands

## decorations.text tikzlibrary
# loads decorations tikzlibrary and decorations.text pgflibrary
\tikzdecorationcharactercount#S
\tikzdecorationcharactertotal#S
\tikzdecorationlettercount#S
\tikzdecorationlettertotal#S
\tikzdecorationwordcount#S
\tikzdecorationwordtotal#S
\tikzdecorationcharacter#S

## er tikzlibrary
# loads shapes.geometric tikzlibrary
# no new user commands

## external tikzlibrary
# loads pdftexcmds and atveryend packages
\tikzexternalize#S
\tikzexternalize[options%keyvals]#S
#keyvals:\tikzexternalize#c
system call={%<template%>}
shell escape={%<command-line arg%>}
aux in dpth#true,false
prefix=%<file name prefix%>
figure name=%<name%>
disable dependency files
force remake#true,false
remake next#true,false
export next#true,false
export#true,false
up to date check=#simple,md5,diff
figure list#true,false
mode=#only graphics,no graphics,only pictures,graphics if exists,list only,list and make
verbose IO#true,false
verbose optimize#true,false
verbose#true,false
optimize#true,false
optimize command away={%<command%>}{%<arg count%>}
only named
#endkeyvals
\tikzexternalrealjob#S
\tikzexternalcheckshellescape#S
\tikzsetexternalprefix{prefix}#S
\tikzsetnextfilename{name}#S
\tikzsetfigurename{name}#S
\tikzappendtofigurename{suffix}#S
\tikzpicturedependsonfile{file}#S
\tikzexternalimgextension#S
\tikzexternalfiledependsonfile{external graphics}{file}#S
\tikzexternaldisable#S
\tikzexternalenable#S
\tikzifexternalizing{true code}{false code}#S
\tikzifexternalizingnext{true code}{false code}#S
\iftikzexternalremakenext#S
\tikzexternalremakenexttrue#S
\tikzexternalremakenextfalse#S
\iftikzexternalexportnext#S
\tikzexternalexportnexttrue#S
\tikzexternalexportnextfalse#S
\tikzifexternalizingcurrent{true code}{false code}#S
\tikzifexternaljobnamematches{jobname}{true code}{false code}#S
\tikzifexternalizehasbeencalled{true code}{false code}#S
\tikzexternallocked#S
\tikzexternalgetnextfilename{macro%cmd}#Sd
\tikzexternalgetcurrentfilename{macro%cmd}#Sd
\tikzexternaldepext#S
\tikzexternalmakefiledefaultdeprule#S
\tikzexternalifwritesmakefile{true code}{false code}#S
\tikzexternalwritetomakefile{code}#S

## fadings tikzlibrary
\begin{tikzfadingfrompicture}#S
\begin{tikzfadingfrompicture}[options%keyvals]#S
\end{tikzfadingfrompicture}#S
\tikzfadingfrompicture#S
\tikzfadingfrompicture[options%keyvals]#S
\endtikzfadingfrompicture#S
#keyvals:\begin{tikzfadingfrompicture}#c,\tikzfadingfrompicture#c
name=%<name%>
#endkeyvals
\tikzfading[options%keyvals]#S
#keyvals:\tikzfading#c
name=%<name%>
left color=#%color
right color=#%color
inner color=#%color
outer color=#%color
top color=#%color
bottom color=#%color
middle color=#%color
#endkeyvals

## fit tikzlibrary
# no new user commands

## fixedpointarithmetic tikzlibrary
# loads fixedpointarithmetic pgflibrary
# no new user commands

## folding tikzlibrary
\tikzfoldingdodecahedron#S
\tikzfoldingalternatedodecahedron#S
\tikzfoldingtetrahedron#S
\tikzfoldingcube#S
\tikzfoldingoctahedron#S
\tikzfoldingicosahedron#S
\tikzfoldingtruncatedtetrahedron#S
\tikzfoldingcuboctahedron#S
\tikzfoldingtruncatedcube#S
\tikzfoldingtruncatedoctahedron#S
\tikzfoldingrhombicuboctahedron#S
\tikzfoldingtruncatedcuboctahedron#S
\tikzfoldingsnubcube#S
\tikzfoldingicosidodecahedron#S

## fpu tikzlibrary
# loads fpu pgflibrary
# no new user commands

## graphdrawing tikzlibrary
# loads graphdrawing pgflibrary
#keyvals:\graph#c,\tikzgraphsset#c
node distance=##L
node pre sep=##L
node post sep=##L
node sep=##L
level distance=##L
layer distance=##L
level pre sep=##L
level post sep=##L
layer pre sep=##L
layer post sep=##L
level sep=##L
layer sep=##L
sibling distance=##L
sibling pre sep=##L
sibling post sep=##L
sibling sep=##L
part distance=##L
part pre sep=##L
part post sep=##L
part sep=##L
component sep=##L
component distance=##L
anchor node=%<string%>
anchor at={%<coord%>}
orient=%<direction%>
orient'=%<direction%>
orient tail=%<string%>
orient head=%<string%>
horizontal=%<tail%> to %<head%>
horizontal'=%<head%> to %<tail%>
vertical=%<tail%> to %<head%>
vertical'=%<head%> to %<tail%>
grow=%<direction%>
grow'=%<direction%>
componentwise#true,false
component order=#by first specified node,increasing node number,decreasing node number
small components first
large components first
component direction=%<direction%>
component align=#first node,center,counterclockwise,clockwise,counterclockwise bounding box,clockwise bounding box,
components go right top aligned
components go right absolute top aligned
components go right bottom aligned
components go right absolute bottom aligned
components go right center aligned
components go right
components go left top aligned
components go left absolute top aligned
components go left bottom aligned
components go left absolute bottom aligned
components go left center aligned
components go left
components go down right aligned
components go down absolute right aligned
components go down left aligned
components go down absolute left aligned
components go down center aligned
components go down
components go up right aligned
components go up absolute right aligned
components go up left aligned
components go up absolute left aligned
components go up center aligned
components go up
component packing=#rectangular,skyline
allow inside edges#true,false
nodes behind edges#true,false
edges behind nodes
random seed=%<number%>
variation=%<number%>
# trees gdlibrary
tree layout
missing nodes get space#true,false
significant sep=##L
binary tree layout
extended binary tree layout
minimum number of children=%<number%>
breadth first spanning tree
depth first spanning tree
root#true,false
span priority=%<number%>
span edge
no span edge
span priority ->=%<number%>
span priority reversed ->=%<number%>
span using directed
span using all
# layered gdlibrary
layered layout
depth first cycle removal
prioritized greedy cycle removal
greedy cycle removal
naive greedy cycle removal
random greedy cycle removal
linear optimization layer assignment
minimum height layer assignment
sweep crossing minimization
linear optimization node positioning
polyline layer edge routing
# force gdlibrary
iterations=%<number%>
initial step length=##L
cooling factor=%<number%>
convergence tolerance=%<number%>
spring constant=%<number%>
electric force order=%<number%>
approximate remote forces#true,false
coarsen#true,false
minimum coarsening size=%<number%>
downsize ratio=%<number%>
spring layout
spring Hu 2006 layout
spring electrical layout
spring electrical layout'
spring electrical Hu 2006 layout
spring electrical Walshaw 2000 layout
# circular gdlibrary
simple necklace layout
# phylogenetics gdlibrary
phylogenetic tree layout
phylogenetic tree by author
unweighted pair group method using arithmetic averages
upgma
balanced minimum evolution
balanced nearest neighbour interchange
no phylogenetic tree optimization
rooted rectangular phylogram
rectangular phylogram
rooted straight phylogram
straight phylogram
unrooted rectangular phylogram
unrooted straight phylogram
evolutionary unit length=##L
# routing gdlibrary
necklace routing
# examples gdlibrary
simple demo layout
simple edge demo layout
simple Huffman layout
probability=%<number%>
#endkeyvals
\pgfgdtikzedgecallback{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}{arg7}{arg8}#S

## graphdrawing.evolving tikzlibrary
# loads graphdrawing pgflibrary and evolving gdlibrary
\mycount#S

## graphs tikzlibrary
\graph#S
\graph[options%keyvals]#S
\tikzgraphsset{options%keyvals}#S

#keyvals:\tikzgraphsset
every graph/.style={%<options%>}
#endkeyvals

#keyvals:\graph#c,\tikzgraphsset#c
node={%<options%>}
edges={%<options%>}
edge node={%<node spec%>}
edge label=%<text%>
edge label'=%<text%>
new ->={%<left node%>}{%<right node%>}{%<edge options%>}{%<edge nodes%>}
left anchor=%<anchor%>
right anchor=%<anchor%>
new --={%<left node%>}{%<right node%>}{%<edge options%>}{%<edge nodes%>}
new <->={%<left node%>}{%<right node%>}{%<edge options%>}{%<edge nodes%>}
new <-={%<left node%>}{%<right node%>}{%<edge options%>}{%<edge nodes%>}
new -!-={%<left node%>}{%<right node%>}{%<edge options%>}{%<edge nodes%>}
use existing nodes#true,false
fresh nodes#true,false
number nodes
number nodes=%<start number%>
number nodes sep=%<text%>
name=%<prefix%>
name separator=%<symbols%>
as=%<text%>
typeset=%<code%>
empty nodes
math nodes
trie#true,false
quick
multi
simple
edge quotes={%<options%>}
edge quotes center
edge quotes mid
put node text on incoming edges
put node text on incoming edges={%<options%>}
put node text on outgoing edges
put node text on outgoing edges={%<options%>}
operator=%<code%>
color class=%<name%>
default edge operator=%<key%>
no placement
x=##L
y=##L
Cartesian placement
chain shift=%<coord%>
group shift=%<coord%>
grow up
grow up=##L
grow down
grow down=##L
grow left
grow left=##L
grow right
grow right=##L
branch up
branch up=##L
branch down
branch down=##L
branch left
branch left=##L
branch right
branch right=##L
grid placement
grow right sep
grow right sep=##L
grow left sep
grow left sep
grow up sep
grow up sep
grow down sep
grow down sep=##L
branch up sep
branch up sep=##L
branch down sep
branch down sep=##L
branch left sep
branch left sep=##L
branch right sep
branch right sep=##L
circular placement
chain polar shift=(%<angle%>:%<radius%>)
group polar shift=(%<angle%>:%<radius%>)
radius=##L
phase=%<degrees%>
clockwise
clockwise=%<number%>
counterclockwise
counterclockwise=%<number%>
level=%<level%>
level %<n%>/.style={%<options%>}
placement/logical node width=%<node name%>
placement/logical node depth=%<node name%>
V={%<list of vertices%>}
n=%<number%>
name shore V/.style={%<options%>}
W={%<list of vertices%>}
m=%<number%>
clique
clique=#%color
induced independent set
induced independent set
cycle
cycle
induced cycle
induced cycle
path
path
induced path
induced path
#endkeyvals

#keyvals:\graph#c
declare={%<name%>}{%<specification%>}
#endkeyvals

\tikzgraphnodetext#S
\tikzgraphnodename#S
\tikzgraphnodepath#S
\tikzgraphnodefullname#S
\tikzgraphforeachcolorednode{color}{macro}#S
\tikzgraphpreparecolor{color}{counter}{prefix}#S
\tikzgraphinvokeoperator{option}#S
\tikzlibgraphactivations#S
\tikzlibgraphscommercialat#S
\tikzlibgraphactivationsbrace#S
\tikzgraphnodeas#S
\iftikzgraphsautonumbernodes#S
\tikzgraphsautonumbernodestrue#S
\tikzgraphsautonumbernodesfalse#S
\tikzgraphpreparewrapafter#S
\tikzgraphV#S
\tikzgraphVnum#S
\tikzgraphW#S
\tikzgraphWnum#S

## graphs.standard tikzlibrary
# loads graphs tikzlibrary
# no new user commands

## intersections tikzlibrary
# loads intersections pgflibrary
# no new user commands

## lindenmayersystems tikzlibrary
# loads lindenmayersystems pgflibrary
# no new user commands

## math tikzlibrary
# loads fpu tikzlibrary
\tikzmath{statements}#S
\tikzmathfor#S

## matrix tikzlibrary
# no new user commands

## mindmap tikzlibrary
# loads trees and decorations tikzlibraries
# no new user commands

## patterns tikzlibrary
# loads patterns pgflibrary
# no new user commands

## patterns.meta tikzlibrary
# loads patterns.meta pgflibrary
\tikzdeclarepattern{config%keyvals}#S
#keyvals:\tikzdeclarepattern
name=%<name%>
type=#uncolored,colored,form only,inherently colored
x=##L
y=##L
parameters=
defaults=
bottom left=%<point%>
top right=%<point%>
tile size=%<point%>
tile transformation=%<transformation%>
code=%<code%>
set up code=%<code%>
bounding box=%<point1%> and %<point2%>
infer tile bounding box
infer tile bounding box=##L
#endkeyvals

## perspective tikzlibrary
\pgfpointperspectivexyz{x}{y}{z}#S

## petri tikzlibrary
# no new user commands

## plothandlers tikzlibrary
# loads plothandlers pgflibrary
# no new user commands

## plotmarks tikzlibrary
# loads plotmarks pgflibrary
# no new user commands

## positioning tikzlibrary
# no new user commands

## quotes tikzlibrary
# no new user commands

## rdf tikzlibrary
\tikzrdfhashmark#S
\tikzrdfcontext#S

## scopes tikzlibrary
\scoped#S
\scoped[options%keyvals]#S

## shadings tikzlibrary
# loads shadings pgflibrary
# no new user commands

## shadows tikzlibrary
# loads fadings tikzlibrary
# no new user commands

## shapes tikzlibrary
# loads shapes.geometric, shapes.misc, shapes.symbols, shapes.arrows, shapes.callouts, and shapes.multipart tikzlibraries
# no new user commands

## shapes.arrows tikzlibrary
# loads shapes.arrows pgflibrary
# no new user commands

## shapes.callouts tikzlibrary
# loads shapes.callouts pgflibrary
# no new user commands

## shapes.gates.logic.IEC tikzlibrary
# loads shapes.gates.logic.IEC pgflibrary
# no new user commands

## shapes.gates.logic.US tikzlibrary
# loads shapes.gates.logic.US pgflibrary
# no new user commands

## shapes.geometric tikzlibrary
# loads shapes.geometric pgflibrary
# no new user commands

## shapes.misc tikzlibrary
# loads shapes.misc pgflibrary
# no new user commands

## shapes.multipart tikzlibrary
# loads shapes.multipart pgflibrary
# no new user commands

## shapes.symbols tikzlibrary
# loads shapes.symbols pgflibrary
# no new user commands

## spy tikzlibrary
\spy#S
\spy[options%keyvals]#S

## svg.path tikzlibrary
# loads svg.path pgflibrary
# no new user commands

## through tikzlibrary
# no new user commands

## trees tikzlibrary
# no new user commands

## turtle tikzlibrary
# no new user commands

## views tikzlibrary
# no new user commands
