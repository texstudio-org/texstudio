# graphs tikzlibrary
# 2022/11/21 for v3.1.9a

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c
every new ->/.style={%<options%>}
every new --/.style={%<options%>}
every new <->/.style={%<options%>}
every new <-/.style={%<options%>}
every new -!-/.style={%<options%>}
new set=%<set name%>
#endkeyvals

#keyvals:\node#c,\coordinate#c,\nodepart#c,\pic#c
set=%<set name%>
#endkeyvals

\graph {%<graph spec%>};
\graph[%<options%>] {%<graph spec%>};
\tikzgraphsset{options%keyvals}

#keyvals:\tikzgraphsset#c
every graph/.style={%<options%>}
#endkeyvals

#keyvals:\graph#c,\tikzgraphsset#c
nodes={%<options%>}
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
placement/compute position/.append code=%<code%>
#endkeyvals

#keyvals:\graph#c
declare={%<name%>}{%<specification%>}
#endkeyvals

\tikzgraphnodetext#*
\tikzgraphnodename#*
\tikzgraphnodepath#*
\tikzgraphnodefullname#*
\tikzgraphforeachcolorednode{color}{macro}#*
\tikzgraphpreparecolor{color}{counter}{prefix}#*
\tikzgraphinvokeoperator{option}#S
\tikzlibgraphactivations#S
\tikzlibgraphscommercialat#S
\tikzlibgraphactivationsbrace#S
\tikzgraphnodeas#S
\iftikzgraphsautonumbernodes#S
\tikzgraphsautonumbernodestrue#S
\tikzgraphsautonumbernodesfalse#S
\tikzgraphpreparewrapafter#S
\tikzgraphV#*
\tikzgraphVnum#*
\tikzgraphW#*
\tikzgraphWnum#*