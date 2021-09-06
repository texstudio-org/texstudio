# tikz package
# muzimuzhi, 12 Nov 2019, 23 Feb 2020, 8 Aug 2020

#include:pgf
#include:pgffor

\begin{scope}
\begin{scope}[options%keyvals]
\end{scope}
\tikzset{options%keyvals}#*
\tikzoption{arg1}#*
\tikzsetexternalprefix{prefix}#*
\tikzexternalize#*
\tikzsetnextfilename{name}#*
\tikzaddafternodepathoption{arg1}#*
\tikzparentanchor#*
\tikzchildanchor#*
\pgfmatrixcolumnsep#*
\pgfmatrixrowsep#*
\tikzstyle{style} = [definition]#s#%tikzstyle
\begin{tikzpicture}
\begin{tikzpicture}[options%keyvals]#\picture
\end{tikzpicture}
\tikz
\tikz[options%keyvals]
\tikzifinpicture{arg1}#*
\tikzaddtikzonlycommandshortcutlet{arg1}#*
\tikzaddtikzonlycommandshortcutdef{arg1}#*
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
\clip#*
\clip[options%keyvals]#*
\useasboundingbox#*
\node
\node[options%keyvals] (node name) {};#s#%node
\nodepart[options%keyvals]{part name}
\coordinate
\coordinate[options%keyvals]
\pic
\pic[options%keyvals]
\graph
\graph[options%keyvals]
\matrix
\matrix[options%keyvals]
\scoped#*
\calendar#*
\datavisualization#*
\pgfextra#*
\pgfstrokehook#*
\tikztostart#*
\tikztotarget#*
\tikztonodes#*
\pgfplotlastpoint#*
\pgfmatrixbegincode#*
\pgfmatrixendcode#*
\pgfmatrixemptycode#*
\tikzdeclarecoordinatesystem{arg1}#*
\tikzaliascoordinatesystem{arg1}#*

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
datavisualization
datavisualization.formats.functions
datavisualization.polar
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
examples
external
fadings
fit
fixedpointarithmetic
folding
force
fpu
graphdrawing
graphs
graphs.standard
intersections
karnaugh
knots
layered
lindenmayersystems
math
matrix
matrix.skeleton
mindmap
nef
optics
overlay-beamer-styles
patterns
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
tqft
trees
turtle
views
#endkeyvals

#keyvals:\begin{tikzpicture}#c,\tikz#c
baseline=%<dimen or coord or default%>
execute at begin picture=%<code%>
execute at end picture=%<code%>
#endkeyvals

#keyvals:\begin{scope}#c
execute at begin scope=%<code%>
execute at end scope=%<code%>
#endkeyvals

#keyvals:\node#c,\draw#c,\path#c,\begin{scope}#c,\begin{tikzpicture}#c,\tikz#c,\tikzset#c
## line
dash pattern=%<dash pattern%>
dash phase=%<dash phase%>
dash=%<dash pattern%> phase %<dash phase%>
solid
dotted
dashed
dash dot
line width=##L
very thin
thin
semithick
thick
very thick
line cap=#round,rect,butt
line join=#round,bevel,miter
miter limit=%<factor%>
help lines
## node: shape, text, and position
anchor=
inner sep=##L
inner xsep=##L
inner ysep=##L
outer sep=##L
outer xsep=##L
outer ysep=##L
minimum height=##L
minimum width=##L
minimum size=##L
shape aspect=
text=%color
node font=
font=
text width=##L
align=#left,flush left,right,flush right,center,flush center,justify
text height=##L
text depth=##L
anchor=#north west,north,north east,west,center,east,mid west,mid,mid east,base west,base,base east,south west,south,south east,text
above=
below=
right=
left=
above=of %<node%>
below=of %<node%>
right=of %<node%>
left=of %<node%>
above left
above right
below left
below right
centered
pos=
midway
near start
near end
very near start
very near end
at start
at end
label=%<angle%>:%<text%>
## transformation
shift=%<coordinate%>
xshift=##L
yshift=##L
scale=%<scale%>
xscale=%<scale%>
yscale=%<scale%>
xslant=%<factor%>
yslant=%<factor%>
rotate=%<degree%>
rotate around={%<degree%>:coordinate}
### every xxx
every picture
every scope
every node
## others
->
<-
name path=
name=
sharp corners
rounded corners=##L
outline
%tikzstyle
color=#%color
%color
#endkeyvals

\usegdlibrary{graph drawing libraries%keyvals}
#keyvals:\usegdlibrary
circular
examples
force
layered
phylogenetics
routing
trees
#endkeyvals
