# CreationBoites package
# Matthew Bertucci 2025/05/25 for v0.1.2

#include:tcolorbox
#include:tcolorboxlibraryfitting
#include:tcolorboxlibraryskins
#include:fontawesome5
#include:simplekv
#include:xstring

#keyvals:\usepackage/CreationBoites#c
breakable
fa6
#endkeyvals

#ifOption:breakable
#include:tcolorboxlibrarybreakable
#endif

#ifOption:fa6
#include:fontawesome6
#endif

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
\IconeCoinDroit#*
\CreerCompteur{counter}#*
