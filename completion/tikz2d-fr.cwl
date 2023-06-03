# tikz2d-fr package
# Matthew Bertucci 2023/05/29 for v0.1.1

#include:tikz
#include:pgffor
#include:xintexpr
#include:simplekv
#include:listofitems
#include:tikzlibrarycalc
#include:tikzlibrarydecorations
#include:tikzlibrarydecorations.pathmorphing

#keyvals:\draw#c
mainlevee
mainlevee=%<segment len%> et %<amplitude%>
#endkeyvals

\DefinirPoint{noeud}{coordonnées}
\DefinirPoint{noeud}{coordonnées}<label>
\DefinirPoint[clés%keyvals]{noeud}{coordonnées}
\DefinirPoint[clés%keyvals]{noeud}{coordonnées}<label>
\DefinirPoint*{noeud}{coordonnées}
\DefinirPoint*{noeud}{coordonnées}<label>
\DefinirPoint*[clés%keyvals]{noeud}{coordonnées}
\DefinirPoint*[clés%keyvals]{noeud}{coordonnées}<label>
\DefinirPoints{liste}
\DefinirPoints[clés%keyvals]{liste}
\DefinirPoints*{liste}
\DefinirPoints*[clés%keyvals]{liste}
\MarquerPoint{point}
\MarquerPoint[clés%keyvals]{point}
\MarquerPoints{liste}
\MarquerPoints[clés%keyvals]{liste}

\ImagePoint{formule}
\ImagePoint{formule}<label>
\ImagePoint[clés%keyvals]{formule}
\ImagePoint[clés%keyvals]{formule}<label>
\ImagePoint*{formule}
\ImagePoint*{formule}<label>
\ImagePoint*[clés%keyvals]{formule}
\ImagePoint*[clés%keyvals]{formule}<label>
\ImagesPoints{formule1 § formule2 § ...}
\ImagesPoints[clés%keyvals]{formule1 § formule2 § ...}
\ImagesPoints*{formule1 § formule2 § ...}
\ImagesPoints*[clés%keyvals]{formule1 § formule2 § ...}

#keyvals:\DefinirPoint,\DefinirPoint*,\DefinirPoints,\DefinirPoints*,\MarquerPoint,\MarquerPoints,\ImagePoint,\ImagePoint*,\ImagesPoints,\ImagesPoints*
PosLabel=%<position%>
TaillePolice=%<font commands%>
DecalLabel=##L
StyleMarque=#x,o,+
Math#true,false
TailleMarque=##L
Couleur=#%color
#endkeyvals

\TracerSegments{ptA/ptB ptC/ptD ...}
\TracerSegments<options TikZ>{ptA/ptB ptC/ptD ...}
\TracerSegments[clés%keyvals]{ptA/ptB ptC/ptD ...}
\TracerSegments[clés%keyvals]<options TikZ>{ptA/ptB ptC/ptD ...}

#keyvals:\TracerSegments
Cap=%<type%>
Join=%<type%>
Couleurs=%<liste de couleurs%>
Cycle#true,false
Suite#true,false
#endkeyvals

# not documented
\TransfPosTikzDD{arg}#S
\TwoDimLabel#S
\TwoDimDecalLabel#S
\TwoDimStylePt#S
\TwoDimtaillePt#S
\TwoDimCoul#S
\TwoDimFonte#S
\TracSegCap#S
\TracSegJoin#S
\TracSegCoul#S