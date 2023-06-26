# RoueQuestions package
# Matthew Bertucci 2023/06/26 for v0.0.1

#include:tikz
#include:simplekv
#include:listofitems

\roueQuestions{liste}
\roueQuestions[options%keyvals]{liste}

#keyvals:\roueQuestions
LineWidth=##L
NbCases=%<nombre%>
RayonCentral=%<nombre%>
RayonTotal=%<nombre%>
Consigne={%<texte%>}
Titre={%<texte%>}
Decoupe#true,false
Pliage#true,false
Solution#true,false
#endkeyvals