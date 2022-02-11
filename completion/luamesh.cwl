# luamesh package
# Matthew Bertucci 2/9/2022 for v0.6

#include:xkeyval
#include:xcolor
#include:ifthen
#include:luamplib
#include:tikz

\buildMeshBW{%<<list of points> or <file>%>}
\buildMeshBW[%<options%>]{%<<list of points> or <file>%>}

\buildMeshBWinc{%<<list of points> or <file>%>}{%<code before%>}{%<code after%>}
\buildMeshBWinc[%<options%>]{%<<list of points> or <file>%>}{%<code before%>}{%<code after%>}

#keyvals:\buildMeshBW,\buildMeshBWinc
mode=#int,ext
bbox=#none,show
color=#%color
colorBbox=#%color
print=#none,points,dotpoints
meshpoint=%<letter(s)%>
tikz#true,false
scale=##L
#endkeyvals

\drawPointsMesh{%<<list of points> or <file>%>}
\drawPointsMesh[%<options%>]{%<<list of points> or <file>%>}

\drawPointsMeshinc{%<<list of points> or <file>%>}{%<code before%>}{%<code after%>}
\drawPointsMeshinc[%<options%>]{%<<list of points> or <file>%>}{%<code before%>}{%<code after%>}

#keyvals:\drawPointsMesh,\drawPointsMeshinc
mode=#int,ext
bbox=#none,show
color=#%color
colorBbox=#%color
print=#none,points
meshpoint=%<letter(s)%>
tikz#true,false
scale=##L
#endkeyvals

\meshAddPointBW{%<<list of points> or <file>%>}{%<<point> or <number of line>%>}
\meshAddPointBW[%<options%>]{%<<list of points> or <file>%>}{%<<point> or <number of line>%>}

\meshAddPointBWinc{%<<list of points> or <file>%>}{%<<point> or <number of line>%>}{%<code before%>}{%<code after%>}
\meshAddPointBWinc[%<options%>]{%<<list of points> or <file>%>}{%<<point> or <number of line>%>}{%<code before%>}{%<code after%>}

#keyvals:\meshAddPointBW,\meshAddPointBWinc
mode=#int,ext
bbox=#none,show
color=#%color
colorBbox=#%color
colorNew=#%color
colorBack=#%color
colorCircle=#%color
meshpoint=%<letter(s)%>
step=#badtriangles,cavity,newtriangles
newpoint=%<letter(s)%>
tikz#true,false
scale=##L
#endkeyvals

\meshPolygon{%<<list of points> or <file>%>}
\meshPolygon[%<options%>]{%<<list of points> or <file>%>}

\meshPolygonInc{%<<list of points> or <file>%>}{%<code before%>}{%<code after%>}
\meshPolygonInc[%<options%>]{%<<list of points> or <file>%>}{%<code before%>}{%<code after%>}

#keyvals:\meshPolygon,\meshPolygonInc
mode=#int,ext
h=%<number%>
color=#%color
colorPolygon=#%color
print=#none,points,dotpoints
meshpoint=%<letter(s)%>
step=#polygon,grid,points,mesh
tikz#true,false
scale=##L
gridpoints=#rect,perturb
#endkeyvals

\luameshmpcolor
\luameshmpcolorBack
\luameshmpcolorBbox
\luameshmpcolorCircle
\luameshmpcolorNew
\luameshmpcolorPoly

\buildVoronoiBW{%<<list of points> or <file>%>}
\buildVoronoiBW[%<options%>]{%<<list of points> or <file>%>}

\buildVoronoiBWinc{%<<list of points> or <file>%>}{%<code before%>}{%<code after%>}
\buildVoronoiBWinc[%<options%>]{%<<list of points> or <file>%>}{%<code before%>}{%<code after%>}

#keyvals:\buildVoronoiBW,\buildVoronoiBWinc
mode=#int,ext
bbox=#none,show
color=#%color
colorBbox=#%color
colorVoronoi=#%color
print=#none,points
meshpoint=%<letter(s)%>
circumpoint=%<letter(s)%>
tikz#true,false
scale=##L
delaunay=#none,show
styleDelaunay=#none,dashed
styleVoronoi=#none,dashed
#endkeyvals

\luameshmpcolorVoronoi

\drawGmsh{file}#i
\drawGmsh[options%keyvals]{file}#i

\drawGmshinc{file}{code before}{code after}#i
\drawGmshinc[options%keyvals]{file}{code before}{code after}#i

#keyvals:\drawGmsh,\drawGmshinc
color=#%color
print=#none,points
meshpoint=%<letter(s)%>
tikz#true,false
scale=##L
#endkeyvals

\gmshVoronoi{file}#i
\gmshVoronoi[options%keyvals]{file}#i

\gmshVoronoiinc{file}{code before}{code after}#i
\gmshVoronoiinc[options%keyvals]{file}{code before}{code after}#i

#keyvals:\gmshVoronoi,\gmshVoronoiinc
color=#%color
colorVoronoi=#%color
print=#none,points
meshpoint=%<letter(s)%>
circumpoint=%<letter(s)%>
tikz#true,false
scale=##L
delaunay=#none,show
styleDelaunay=#none,dashed
styleVoronoi=#none,dashed
#endkeyvals

\CircumPoint#*
\MeshPoint#*
\NewPoint#*

\PackageName#S
\filedate#S
\fileversion#S