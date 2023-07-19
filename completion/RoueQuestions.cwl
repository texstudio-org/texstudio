# RoueQuestions package
# Matthew Bertucci 2023/07/19 for v0.0.3

#include:tikz
#include:tkz-euclide
#include:simplekv
#include:listofitems
#include:ifthen

\roueQuestions{liste}
\roueQuestions[options%keyvals]{liste}
\rouesQuestions{listeQuestions}{listeRéponses}
\rouesQuestions[options%keyvals]{listeQuestions}{listeRéponses}

#keyvals:\roueQuestions,\rouesQuestions
Titre={%<texte%>}
Consigne={%<texte%>}
LineWidth=##L
RayonCentral=%<nombre%>
RayonTotal=%<nombre%>
BordureCouleur=#%color
CasesCouleur=#%color
CentreCouleur=#%color
Image=%<imagefile%>
ImageOpacite=%<factor%>
Decoupe#true,false
DecoupeCouleur=#%color
Pliage#true,false
PliageCouleur=#%color
Solution#true,false
#endkeyvals

#keyvals:\rouesQuestions
Conseil={%<texte%>}
EspaceRoues=##L
#endkeyvals
