# tikz-dependency package
# Matthew Bertucci 12/26/2021 for v1.2

#include:environ
#include:tikz
#include:tikzlibrarymatrix
#include:tikzlibrarybackgrounds
#include:tikzlibrarycalc
#include:tikzlibrarypatterns
#include:tikzlibrarypositioning
#include:tikzlibraryfit
#include:tikzlibraryshapes

\begin{dependency}#\pictureHighlight
\begin{dependency}[options%keyvals]
\end{dependency}

\begin{deptext}
\begin{deptext}[options%keyvals]
\end{deptext}

## keys from TikZ
# matrix and tikzpicture keys
#keyvals:\begin{dependency}#c,\begin{deptext}#c
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
# matrix keys
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

# just tikzpicture keys
#keyvals:\begin{dependency}#c
baseline
baseline=%<<dimen> or <coord> or default%>
execute at begin picture=%<code%>
execute at end picture=%<code%>
every scope/.style={%<options%>}
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
# pic specific keys
pic type=%<type%>
pics/code=%<code%>
pics/foreground code=%<code%>
pics/background code=%<code%>
pic text=%<text%>
pic text options={%<options%>}
#endkeyvals

\depkeys{options%keyvals}
\depedge{from-word}{to-word}{label}
\depedge[options%keyvals]{from-word}{to-word}{label}
\deproot{root-offset}{label}
\deproot[options%keyvals]{root-offset}{label}
\wordgroup{row-offset}{word-offset-beg}{word-offset-end}{gid}
\wordgroup[options%keyvals]{row-offset}{word-offset-beg}{word-offset-end}{gid}
\groupedge{from-gid}{to-gid}{label}{height}
\groupedge[options%keyvals]{from-gid}{to-gid}{label}{height}
\depstyle{style name%specialDef}{options}#s#%depstyle

#keyvals:\begin{dependency}#c,\begin{deptext}#c,\depkeys#c,\depedge#c,\deproot#c,\wordgroup#c,\groupedge#c
edge unit distance=##L
edge height=##L
edge above#true,false
edge below#true,false
edge slant=##L
edge horizontal padding=##L
edge vertical padding=##L
arc edge#true,false
segmented edge#true,false
arc angle=%<decimal%>
text only label#true,false
edge start x offset=##L
edge end x offset=##L
theme=#default,simple,night,brazil,grassy,iron,copper
edge theme=#default,simple,night,brazil,grassy,iron,copper
label theme=#default,simple,night,brazil,grassy,iron,copper
text theme=#default,simple,night,brazil,grassy,iron,copper
hide label#true,false
show label#true,false
edge style={%<TikZ keys%>}
label style={%<TikZ keys%>}
group style={%<TikZ keys%>}
nodes={%<TikZ keys%>}
%depstyle
#endkeyvals

\matrixref
\wordref{row-offset}{word-offset}
\rootref
\storelabelnode{macro%cmd}#d
\storefirstcorner{macro%cmd}#d
\storesecondcorner{macro%cmd}#d

\settgtlayer#*
\anchorpoint#S
\distance#S
\source#S
\offa#S
\offb#S
\dest#S
\depname#S
\xca#*
\xcb#*
\yca#*
\ycb#*
