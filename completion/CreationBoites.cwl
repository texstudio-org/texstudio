# CreationBoites package
# Matthew Bertucci 2023/08/27 for v0.1.0

#include:tcolorbox
#include:tcolorboxlibraryfitting
#include:tcolorboxlibraryskins
#include:fontawesome5
#include:simplekv
#include:xstring

\CreationBoite{envname}{compteur}{icône}{libéllés}#N
\CreationBoite[color]{envname}{compteur}{icône}{libéllés}#N
\ParamBoites[clés%keyvals]

#keyvals:\tcbset
baseboite/.style={%<options%>}
#endkeyvals

\margeboite#*
\margeinttitreboite#*
\eptraitboite#*
\policetitreboite#*
\policesoustitreboite#*
\couleursoustitreboite#*
\tailleiconeboite#*
\TitreBoite#*
\SousTitreBoite#*
\LogoCoinDroit#*
\CreerCompteur{counter}#*