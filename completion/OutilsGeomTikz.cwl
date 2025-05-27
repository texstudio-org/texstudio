# OutilsGeomTikz package
# Matthew Bertucci 2025/05/27 for v0.1.6

#include:tikz
#include:pgffor
#include:simplekv
#include:xstring
#include:nicefrac
#include:tikzlibrarycalc
#include:tikzlibrarypositioning

\tkzCrayon
\tkzCrayon[clés%keyvals]

#keyvals:\tkzCrayon
Longueur=%<nombre%>
Origine={(%<x,y%>)}
Rotation=%<degrees%>
Echelle=%<nombre%>
Couleur=#%color
#endkeyvals

\tkzRegle
\tkzRegle[clés%keyvals]

#keyvals:\tkzRegle
Longueur=%<nombre%>
Largeur=%<nombre%>
Origine={(%<x,y%>)}
Rotation=%<degrees%>
Echelle=%<nombre%>
Couleur=#%color
Fond#true,false
CouleurFond=#%color
Opacite=%<factor%>
AfficheValeurs#true,false
EchelleValeurs=%<factor%>
PosVal=#h,m,b,hb
#endkeyvals

\tkzRegleRepere
\tkzRegleRepere[clés%keyvals]

#keyvals:\tkzRegleRepere
Longueur=%<nombre%>
Largeur=%<nombre%>
Origine={(%<x,y%>)}
Rotation=%<degrees%>
Echelle=%<nombre%>
Couleur=#%color
Fond#true,false
CouleurFond=#%color
Opacite=%<factor%>
AfficheValeurs#true,false
EchelleValeurs=%<factor%>
Retourne#true,false
#endkeyvals

\tkzEquerre
\tkzEquerre[clés%keyvals]

#keyvals:\tkzEquerre
Longueur=%<nombre%>
Largeur=%<nombre%>
Origine={(%<x,y%>)}
Rotation=%<degrees%>
Echelle=%<nombre%>
EchelleValeurs=%<factor%>
Couleur=#%color
Fond#true,false
CouleurFond=#%color
Opacite=%<factor%>
AfficheValeurs#true,false
PetitCote#true,false
#endkeyvals

\tkzRapporteur
\tkzRapporteur[clés%keyvals]

#keyvals:\tkzRapporteur
Complet#true,false
Origine={(%<x,y%>)}
Rotation=%<degrees%>
Echelle=%<nombre%>
Couleur=#%color
Fond#true,false
CouleurFond=#%color
Opacite=%<factor%>
GraduationsInt#true,false
AfficheAngles#true,false
#endkeyvals

\tkzPourcenteur
\tkzPourcenteur[clés%keyvals]

#keyvals:\tkzPourcenteur
Echelle=%<nombre%>
EchelleAngle=%<nombre%>
Couleur=#%color
CouleurFond=#%color
Origine={(%<x,y%>)}
Rotation=%<degrees%>
AfficheValeurs#true,false
Fond#true,false
Opacite=%<factor%>
Decoration#true,false
#endkeyvals

\tkzRequerre
\tkzRequerre[clés%keyvals]

#keyvals:\tkzRequerre
Longueur=%<nombre%>
Largeur=%<nombre%>
Origine={(%<x,y%>)}
Rotation=%<degrees%>
Echelle=%<nombre%>
Couleur=#%color
Fond#true,false
CouleurFond=#%color
Opacite=%<factor%>
AfficheValeurs#true,false
EchelleValeurs=%<factor%>
#endkeyvals

\tkzRappEquerre
\tkzRappEquerre[clés%keyvals]

#keyvals:\tkzRappEquerre
Largeur=%<nombre%>
Origine={(%<x,y%>)}
Rotation=%<degrees%>
Echelle=%<nombre%>
EchelleValeurs=%<nombre%>
Couleur=#%color
Fond#true,false
CouleurFond=#%color
Opacite=%<factor%>
AfficheAngles#true,false
AfficheValeurs#true,false
Ombre#true,false
#endkeyvals

\tkzCompas{pointe}{mine}
\tkzCompas[clés%keyvals]{pointe}{mine}

#keyvals:\tkzCompas
AfficheCrayon#true,false
EchelleCrayon=%<nombre%>
CouleurCrayon=#%color
LongueurCrayon=%<nombre%>
LongueurBranches=%<nombre%>
CouleurCompas=#%color
Retourne#true,false
Echelle=%<nombre%>
UniteTikz=%<unité%>
#endkeyvals

\tkzMiniEquerre#*
\tkzMiniEquerre[clés%keyvals]#*
\tkzMiniRegle#*
\tkzMiniRegle[clés%keyvals]#*

#keyvals:\tkzMiniEquerre,\tkzMiniRegle
Echelle=%<nombre%>
Couleur=#%color
Origine={(%<x,y%>)}
Rotation=%<degrees%>
Ombre#true,false
#endkeyvals
