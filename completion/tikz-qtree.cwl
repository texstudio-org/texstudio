# tikz-qtree package
# Matthew Bertucci 4/13/2022 for v1.2

# Dependency Tree:
# tikz-qtree.sty
# ├── tikz.sty
# ├── pgftree.sty
# │   ├── pgf.sty
# │   ├── pgffor.sty
# │   ├── pgfsubpic.sty
# │   │   ├── pgf.sty
# │   │   └── pgfsubpic.tex
# │   └── pgftree.tex
# └── tikz-qtree.tex

#include:tikz
#include:pgftree

# from tikz-qtree.tex
\Tree[qtree code]
\edge;
\edge[%<options%>];
\edge node [%<options%>] {%<label%>};
\edge[%<options%>] node {%<label%>};
\edge[%<options%>] node[%<options%>] {%<label%>};

#keyvals:\tikzset#c,\begin{tikzpicture}#c,\begin{scope}#c
level distance=##L
sibling distance=##L
grow=#up,down,left,right
grow'=#up,down,left,right
level %<n%>+/.style={%<options%>}
interior/.style={%<options%>}
frontier/.style={%<options%>}
#endkeyvals

#keyvals:\tikzset#c
every tree node/.style={%<options%>}
every internal node/.style={%<options%>}
every leaf node/.style={%<options%>}
every level %<n%> node/.style={%<options%>}
edge from parent/.append style={%<options%>}
#endkeyvals