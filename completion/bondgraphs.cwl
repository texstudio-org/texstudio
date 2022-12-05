# bondgraphs package
# Matthew Bertucci 12/14/2021 for v1.0.1

#include:amsfonts
#include:bm
#include:kvoptions
#include:tikz
#include:tikzlibrarydecorations.pathreplacing
#include:tikzlibrarypositioning
#include:tikzlibraryshapes

#keyvals:\usepackage/bondgraphs#c
labelcolour=#%color
bondlabelcolour=#%color
grey#true,false
colour
curly#true,false
#endkeyvals

\bond
\bond[options%keyvals]

\begin{bondgraph}#\pictureHighlight
\begin{bondgraph}[options%keyvals]
\end{bondgraph}

# TikZ draw keys
#keyvals:\bond,\begin{bondgraph}
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
## path specific keys
use as bounding box
clip
preaction={%<options%>}
postaction={%<options%>}
late options={%<options%>}
pic actions
#endkeyvals

#keyvals:\begin{bondgraph}
baseline
baseline=%<<dimen> or <coord> or default%>
execute at begin picture=%<code%>
execute at end picture=%<code%>
every scope/.style={%<options%>}
execute at begin scope=%<code%>
execute at end scope=%<code%>
transparency group
transparency group=%<options%>
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
#endkeyvals

# bondgraphs keys
#keyvals:\bond,\begin{bondgraph},\draw#c,\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c
e_in
e_in={%<options%>}
f_out
f_out={%<options%>}
e_out
e_out={%<options%>}
f_in
f_in={%<options%>}
effort={%<label%>}
flow={%<label%>}
mbond
#endkeyvals

#keyvals:\draw#c,\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c
bond
bonds
#endkeyvals

#keyvals:\node#c,\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c
bgelement
multiport
#endkeyvals

\bgelement{element}
\bgelement[options%keyvals]{element}

#keyvals:\bgelement
multiport
n=%<integer%>
wordbg
#endkeyvals
