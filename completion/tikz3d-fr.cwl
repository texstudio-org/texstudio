# tikz3d-fr package
# Matthew Bertucci 2023/05/02 for v0.1.0

#include:tikz
#include:xstring
#include:simplekv
#include:xinttools
#include:xintexpr
#include:listofitems
#include:tikzlibrarycalc
#include:tikzlibrarybabel

\begin{EnvTikzEspace}#\pictureHighlight
\begin{EnvTikzEspace}<options TikZ>#\pictureHighlight
\begin{EnvTikzEspace}[clés%keyvals]#\pictureHighlight
\begin{EnvTikzEspace}[clés%keyvals]<options TikZ>#\pictureHighlight
\end{EnvTikzEspace}

#keyvals:\begin{EnvTikzEspace}
UniteX={%<angle%>:%<longueur%>}
UniteY={%<angle%>:%<longueur%>}
UniteZ={%<angle%>:%<longueur%>}
VueClassique#true,false
#endkeyvals

\PlacePointEspace{nœud}{coordonnées}
\PlacePointEspace{nœud}{coordonnées}<label>
\PlacePointEspace[clés%keyvals]{nœud}{coordonnées}
\PlacePointEspace[clés%keyvals]{nœud}{coordonnées}<label>
\PlacePointEspace*{nœud}{coordonnées}
\PlacePointEspace*{nœud}{coordonnées}<label>
\PlacePointEspace*[clés%keyvals]{nœud}{coordonnées}
\PlacePointEspace*[clés%keyvals]{nœud}{coordonnées}<label>
\PlacePointsEspace{liste}
\PlacePointsEspace[clés%keyvals]{liste}
\PlacePointsEspace*{liste}
\PlacePointsEspace*[clés%keyvals]{liste}
\MarquePointEspace{point}
\MarquePointEspace[clés%keyvals]{point}
\MarquePointsEspace{liste}
\MarquePointsEspace[clés%keyvals]{liste}

#keyvals:\PlacePointEspace,\PlacePointEspace*,\PlacePointsEspace,\PlacePointsEspace*,\MarquePointEspace,\MarquePointsEspace
PosLabel=%<pos%>
StyleMarque=#x,o
TailleMarque=##L
Couleur=#%color
#endkeyvals

\TraceSegmentEspace(point)(point)
\TraceSegmentEspace[options TikZ](point)(point)
\TraceSegmentsEspace{liste}
\TraceSegmentsEspace[options TikZ]{liste}

\PaveTikzTriDim
\PaveTikzTriDim[clés%keyvals]

#keyvals:\PaveTikzTriDim
Largeur=%<nombre%>
Profondeur=%<nombre%>
Hauteur=%<nombre%>
Sommets=%<liste%>
Math#true,false
Epaisseur=%<épaisseur%>
AffLabel#true,false
Plein#true,false
Cube#true,false
Couleur=#%color
CouleurSommets=#%color
#endkeyvals

\begin{EmpilementCubes}#\pictureHighlight
\begin{EmpilementCubes}<options TikZ>#\pictureHighlight
\begin{EmpilementCubes}[échelle]#\pictureHighlight
\begin{EmpilementCubes}[échelle]<options TikZ>#\pictureHighlight
\end{EmpilementCubes}

\PlaquePetitsCubes{empilement}
\PlaquePetitsCubes[color]{empilement}
\PlaqueVide
\PlaqueVide[nb]

\BlocPetitsCubes{grille des hauteurs}
\BlocPetitsCubes[color]{grille des hauteurs}
\BlocPetitsCubes*{grille des hauteurs}
\BlocPetitsCubes*[color]{grille des hauteurs}
\PetitCube{grille des hauteurs}
\PetitCube[color]{grille des hauteurs}

# not documented
\thelgblocs#S
\PLTriDimUx#S
\PLTriDimUy#S
\PLTriDimUz#S
\PFPaveLgDDD#S
\PFPavePfDDD#S
\PFPaveHtDDD#S
\PFPaveSommetsDDD#S
\PFPaveThickDDD#S
\PFPaveCouleurDDD#S
\PFPaveCouleurSommDDD#S
\PFListeSommets#S
\TransfPosTikz{arg}#S
\PosTmpLabel#S
\TrimDimLabel#S
\TrimDimDecalLabel#S
\TrimDimStylePt#S
\TrimDimtaillePt#S
\TrimDimCoul#S