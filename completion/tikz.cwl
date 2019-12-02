# tikz package
# muzimuzhi/12 Nov 2019

#include:pgfcore

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
\tikzstyle{style} = {definition}#s#%tikzstyle
\begin{tikzpicture}
\begin{tikzpicture}[options%keyvals]
\end{tikzpicture}
\tikz
\tikz[options%keyvals]
\tikzifinpicture{arg1}#*
\tikzaddtikzonlycommandshortcutlet{arg1}#*
\tikzaddtikzonlycommandshortcutdef{arg1}#*
\path#/tikzpicture
\path[options%keyvals]#/tikzpicture
\draw#/tikzpicture
\draw[options%keyvals]#/tikzpicture
\fill#/tikzpicture
\fill[options%keyvals]#/tikzpicture
\filldraw#/tikzpicture
\filldraw[options%keyvals]#/tikzpicture
\pattern#/tikzpicture
\pattern[options%keyvals]#/tikzpicture
\shade#/tikzpicture
\shade[options%keyvals]#/tikzpicture
\shadedraw#/tikzpicture
\shadedraw[options%keyvals]#/tikzpicture
\clip#*/tikzpicture
\clip[options%keyvals]#*/tikzpicture
\useasboundingbox#*
\node#/tikzpicture
\node[options%keyvals] (node name) {};#s/tikzpicture#(%node)
\nodepart[options%keyvals]{part name}#/tikzpicture
\coordinate#/tikzpicture
\coordinate[options%keyvals]#/tikzpicture
\pic/#tikzpicture
\pic/[options%keyvals]#tikzpicture
\graph#/tikzpicture
\graph[options%keyvals]#/tikzpicture
\matrix#/tikzpicture
\matrix[options%keyvals]#/tikzpicture
\calendar#*
\datavisualization#*
\pgfextra#*
\pgfstrokehook#*
\tikztotarget#*
\tikztonodes#*
\pgfplotlastpoint#*
\pgfmatrixbegincode#*
\pgfmatrixendcode#*
\pgfmatrixemptycode#*
\tikzdeclarecoordinatesystem{arg1}#*
\tikzaliascoordinatesystem{arg1}#*

\usetikzlibrary{keyvals}
#keyvals:\usetikzlibrary
3d
angles
animations
arrows
arrows.meta
arrows.spaced
automata
babel
backgrounds
bending
calc
calendar
chains
circuits
circuits.ee
circuits.ee.IEC
circuits.logic
circuits.logic.CDH
circuits.logic.IEC
circuits.logic.US
circular
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
layered
lindenmayersystems
math
matrix
mindmap
patterns
patterns.meta
perspective
petri
phylogenetics
plothandlers
plotmarks
positioning
profiler
quotes
rdf
routing
scopes
shadings
shadows
shapes.arrows
shapes.callouts
shapes.gates.ee
shapes.gates.ee.IEC
shapes.gates.logic
shapes.gates.logic.IEC
shapes.gates.logic.US
shapes.geometry
shapes.misc
shapes.multipart
shapes.symbols
spy
svg.path
through
topaths
trees
turtle
views
#endkeyvals

#keyvals:\node#c,\draw#c,\path#c,\begin{scope}#c,\begin{tikzpicture}#c,\tikz#c
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
## others
->
<-
name path=
color=#%color
sharp corners
rounded corners=
outline
%tikzstyle
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
