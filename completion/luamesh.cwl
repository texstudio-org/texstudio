# luamesh package
# Matthew Bertucci 2022/07/13 for v0.7

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
thickness=##L
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
thickness=##L
thicknessNew=##L
thicknessCircle=##L
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
thickness=##L
thicknessPolygon=##L
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
thickness=##L
thicknessVoronoi=##L
#endkeyvals

\luameshmpcolorVoronoi

\drawGmsh{file}
\drawGmsh[options%keyvals]{file}

\drawGmshinc{file}{code before}{code after}
\drawGmshinc[options%keyvals]{file}{code before}{code after}

#keyvals:\drawGmsh,\drawGmshinc
color=#%color
print=#none,points
meshpoint=%<letter(s)%>
tikz#true,false
scale=##L
thickness=##L
#endkeyvals

\gmshVoronoi{file}
\gmshVoronoi[options%keyvals]{file}

\gmshVoronoiinc{file}{code before}{code after}
\gmshVoronoiinc[options%keyvals]{file}{code before}{code after}

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
thickness=##L
thicknessVoronoi=##L
#endkeyvals

\CircumPoint#*
\MeshPoint#*
\NewPoint#*

TeXCluaMeshTikZ#B
TeXCluaMeshNewTikZ#B
TeXCluaMeshBackTikZ#B
TeXCluaMeshCircleTikZ#B

\PackageName#S
\filedate#S
\fileversion#S
