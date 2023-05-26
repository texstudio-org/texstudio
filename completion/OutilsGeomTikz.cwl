# OutilsGeomTikz package
# Matthew Bertucci 2023/05/22 for v0.1.2

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
Couleur=#%color
Fond#true,false
CouleurFond=#%color
Opacite=%<factor%>
AfficheValeurs#true,false
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
AfficheAngles#true,false
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

\COMPAScouleur#S
\COMPAScouleurcrayon#S
\COMPASechelle#S
\COMPASechellecrayon#S
\COMPASLLB#S
\COMPASLLC#S
\COMPASunittikz#S
\EQangle#S
\EQcouleur#S
\EQcouleurfond#S
\EQechelle#S
\EQlargeur#S
\EQlongueur#S
\EQopac#S
\EQposOrigin#S
\MiniEQangle#S
\MiniEQcouleur#S
\MiniEQechelle#S
\MiniEQposOrigin#S
\MiniREGLangle#S
\MiniREGLcouleur#S
\MiniREGLechelle#S
\MiniREGLposOrigin#S
\NodeTmpAngle{arg1}{arg2}#S
\NodeTmpDist{arg1}{arg2}#S
\PENangle#S
\PENcouleur#S
\PENechelle#S
\PENlongueur#S
\PENposOrigin#S
\RAPPangle#S
\RAPPcouleur#S
\RAPPcouleurfond#S
\RAPPechangle#S
\RAPPechelle#S
\RAPPEQangle#S
\RAPPEQcouleur#S
\RAPPEQcouleurfond#S
\RAPPEQechangle#S
\RAPPEQechelle#S
\RAPPEQlargeur#S
\RAPPEQopac#S
\RAPPEQposOrigin#S
\RAPPopac#S
\RAPPposOrigin#S
\recupunitexencm#S
\REGLangle#S
\REGLcouleur#S
\REGLcouleurfond#S
\REGLechelle#S
\REGLlargeur#S
\REGLlongueur#S
\REGLopac#S
\REGLposOrigin#S
\REGLposval#S
\REQangle#S
\REQcouleur#S
\REQcouleurfond#S
\REQechelle#S
\REQlargeur#S
\REQlongueur#S
\REQopac#S
\REQposOrigin#S
\TmpUniteX#S
\REGLREPechelle#S
\REGLREPlongueur#S
\REGLREPlargeur#S
\REGLREPcouleur#S
\REGLREPcouleurfond#S
\REGLREPposOrigin#S
\REGLREPangle#S
\REGLREPopac#S
