# polyhedra package
# Matthew Bertucci 2023/11/08 for v0.3

#include:xcolor
#include:xcolor-solarized
#include:tikz
#include:tikz-3dplot
#include:xstring
#include:tikzlibraryshapes
#include:tikzlibrarypatterns

\begin{polyhedron}{keyvals}#\pictureHighlight
\end{polyhedron}

#keyvals:\begin{polyhedron}
dim=%<integer%>
phi=%<degrees%>
theta=%<degrees%>
#endkeyvals

\point{(%<x,y,z%>)}{%<name%>}

\axes{keyvals}

#keyvals:\axes
x={%<num1,num2%>}
y={%<num1,num2%>}
z={%<num1,num2%>}
xlabel=%<text%>
ylabel=%<text%>
zlabel=%<text%>
labels=#true,false
#endkeyvals

\vertex{keyvals}
\edge{keyvals}
\ray{keyvals}
\cone{keyvals}
\polygon{keyvals}
\halfspace{keyvals}
\hyperplane{keyvals}

#keyvals:\vertex,\edge,\ray,\cone,\polygon,\halfspace,\hyperplane
color=#%color
status=#normal,focus,alert,open
opacity=%<factor%>
thickness=%<number%>
pattern={%<pattern%>}
#endkeyvals

#keyvals:\vertex
point={%<point%>}
text=%<text%>
textcolor=#%color
anchora=#north,south,east,west
anchorb=#above,below,left,right
#endkeyvals

#keyvals:\edge,\ray
points={%<point1,point2%>}
#endkeyvals

#keyvals:\cone
vertex={%<point%>}
generators={%<list of point%>}
#endkeyvals

#keyvals:\polygon
points={%<list of point%>}
boundary=#true,false
#endkeyvals

#keyvals:\halfspace,\hyperplane
points={%<list of point%>}
patterncolor=#%color
#endkeyvals

# not documented
\PolyhedraDefaultHeight#S
\PolyhedraDefaultWidth#S
\PolyhedraDefaultScale#S
\VertexColor#S
\VertexTextColor#S
\EdgeColor#S
\RayColor#S
\PolygonColor#S
\HalfspaceColor#S
\AlertColor#S
\FocusColor#S
\intersectionColor#S
\OpenColor#S
\ShadeColor#S
\OpenPolygonPattern#S
\OpenHyperplanePattern#S
\VertexThickness#S
\RayThickness#S
\EdgeThickness#S
\splicelist{arg}#S