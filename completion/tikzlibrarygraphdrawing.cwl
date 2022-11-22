# graphdrawing tikzlibrary
# 2022/11/21 for v3.1.9a

#include:luatex
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

# from graphdrawing pgflibrary (only documented cmds listed here; all others in pgfcore.cwl)
\usegdlibrary{list of libraries%keyvals}
\pgfgdset{options%keyvals}#*
\pgfgdevent{name}{parameter}#*
\pgfgdbegineventgroup{parameter}#*
\pgfgdendeventgroup#*
\pgfgdeventgroup{name}#*
\pgfgdsetlatenodeoption{node name}#*
\pgfgdcallbackrendernode{node name}{xmin}{xmax}{ymin}{ymax}{xpos}{ypos}{boxnum}{code}#*
\pgfpositionnodelatername#*
\pgfpositionnodelaterminx#*
\pgfpositionnodelatermaxx#*
\pgfpositionnodelaterminy#*
\pgfpositionnodelatermaxy#*
\pgfgdedge{node1}{node2}{edge dir}{edge opts}{edge nodes}#*
\pgfgdsetedgecallback{macro}#*
\pgfgddefaultedgecallback{node1}{node2}{options}{auxtext}{alg options}{bend info}{animations}#*
\pgfgdcallbackbeginshipout#*
\pgfgdcallbackendshipout#*
\pgfgdbeginlayout#*
\pgfgdendlayout#*
\pgfgdsubgraphnode{node name}{node options}{node text}#*
\pgfgdsetrequestcallback{macro}#*
\ifpgfgdgraphdrawingscopeactive#*
\pgfgdbeginscope#*
\pgfgdendscope#*
\pgfgdaddspecificationhook{code}#*