# ProfLabo package
# Matthew Bertucci 4/29/2022 for v1.0

#include:pgf
#include:tikz
#include:listofitems
#include:simplekv
#include:ifthen

\TubeAEssai{}
\TubeAEssai[clés%keyvals]{}

#keyvals:\TubeAEssai
Couleurs=#%color
Echelle=%<valeur%>
Legende=%<text%>
Hauteur=%<valeur%>
#endkeyvals

\EchelleTube{nombre}
\EchelleTube[clés%keyvals]{nombre}

#keyvals:\EchelleTube
Couleurs={%<color1,color2,...%>}
Echelle=%<valeur%>
Legendes={%<label1,label2,...%>}
#endkeyvals

\Becher{}
\Becher[clés%keyvals]{}

#keyvals:\Becher
Couleurs=#%color
Echelle=%<valeur%>
Legende=%<text%>
#endkeyvals

\FioleJaugee{}
\FioleJaugee[clés%keyvals]{}

#keyvals:\FioleJaugee
Couleurs=#%color
Echelle=%<valeur%>
Legende=%<text%>
Hauteur=%<valeur%>
#endkeyvals

\Erlen{}
\Erlen[clés%keyvals]{}

#keyvals:\Erlen
Couleurs=#%color
Echelle=%<valeur%>
Legende=%<text%>
LegendeDessous=%<text%>
Hauteur=%<valeur%>
#endkeyvals

\Dosage{}
\Dosage[clés%keyvals]{}

#keyvals:\Dosage
Titrant=%<titrant%>
Titre=%<titre%>
Echelle=%<valeur%>
CouleurTitrant=#%color
CouleurTitre=#%color
#endkeyvals

# not documented
\CouleurActuelle#*
\CouleurBecher#*
\CouleurBecherd#*
\CouleurErlen#*
\CouleurFiole#*
\CouleurTitrant#*
\CouleurTitre#*
\CouleurTube#*
\EchelleActuelle#*
\erlenpartielfalse#*
\erlenpartieltrue#*
\erlenpleinfalse#*
\erlenpleintrue#*
\erlenvidefalse#*
\erlenvidetrue#*
\fiolepleinefalse#*
\fiolepleinetrue#*
\fiolevidefalse#*
\fiolevidetrue#*
\gendeerlenfalsefalse#*
\gendeerlenfalsetrue#*
\hauteurerlen#*
\hauteurfiole#*
\hauteurmaxtube#*
\HauteurTube#*
\iferlenpartiel#*
\iferlenplein#*
\iferlenvide#*
\iffiolepleine#*
\iffiolevide#*
\iflegende#*
\iflegendeerlen#*
\iflegendefiole#*
\iflegendesouserlen#*
\iflegendetube#*
\iftrait#*
\iftraitnoirbecher#*
\iftraitnoirerlen#*
\LegendeActuelle#*
\LegendeActuelleB#*
\LegendeActuelleD#*
\LegendeActuelleF#*
\LegendeActuelleT#*
\legendeerlenfalse#*
\legendeerlenfalse#*
\legendeerlentrue#*
\legendefalse#*
\legendefiolefalse#*
\legendefioletrue#*
\legendesouserlenfalse#*
\legendesouserlentrue#*
\legendetrue#*
\legendetubefalse#*
\legendetubetrue#*
\ListeAvantCouleurs#*
\ListeAvantLegendes#*
\ListeCouleurs#*
\ListeLegendes#*
\nombretube#*
\traitfalse#*
\traitnoirbecherfalse#*
\traitnoirbechertrue#*
\traitnoirerlenfalse#*
\traitnoirerlentrue#*
\traittrue#*