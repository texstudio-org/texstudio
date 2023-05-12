# FenetreCas package
# Matthew Bertucci 2023/05/07 for v0.1.1

#include:tikz
#include:xstring
#include:xintexpr
#include:simplekv
#include:settobox
#include:tikzlibrarycalc
#include:tikzlibrarypositioning

\begin{CalculFormelGeogebra}#\pictureHighlight
\begin{CalculFormelGeogebra}<options tikz>
\begin{CalculFormelGeogebra}[clés%keyvals]
\begin{CalculFormelGeogebra}[clés%keyvals]<options tikz>
\end{CalculFormelGeogebra}

#keyvals:\begin{CalculFormelGeogebra}
Largeur=%<nombre%>
CouleurEntete=#%color
LargeurNumero=%<nombre%>
CouleurNumero=#%color
PoliceEntete=%<commandes%>
PoliceNumero=%<commandes%>
Titre=%<texte%>
Entete#true,false
#endkeyvals

\LigneCalculsGeogebra{commande}{résultat}
\LigneCalculsGeogebra[clés%keyvals]{commande}{résultat}

#keyvals:\LigneCalculsGeogebra
HauteurLigne=%<nombre%>
TailleCommande=%<commande%>
TailleResultat=%<commande%>
ElargirAuto=%<nombre%>
HauteurAuto#true,false
MargeV=##L
MargeH=%<nombre%>
Fond#true,false
CouleurFond=#%color
#endkeyvals

\begin{CalculFormelXcas}#\pictureHighlight
\begin{CalculFormelXcas}<options tikz>
\begin{CalculFormelXcas}[clés%keyvals]
\begin{CalculFormelXcas}[clés%keyvals]<options tikz>
\end{CalculFormelXcas}

#keyvals:\begin{CalculFormelXcas}
Largeur=%<nombre%>
EspaceLg=##L
Couleur=#%color
Menu#true,false
Entete#true,false
NoirBlanc#true,false
PoliceEntete=%<commande%>
Sep#true,false
TexteOptions=%<texte%>
#endkeyvals

\LigneCalculsXcas{commande}{résultat}
\LigneCalculsXcas[clés%keyvals]{commande}{résultat}

#keyvals:\LigneCalculsXcas
TailleCommande=%<commande%>
TailleResultat=%<commande%>
ElargirAuto=%<nombre%>
MargeV=##L
MargeH=%<nombre%>
CouleurCmd=#%color
CouleurRes=#%color
PosRes=#centre,gauche,droite
Fond#true,false
CouleurFond=#%color
#endkeyvals

# not documented
\GEOCFcoulentete#S
\GEOCFcoulnum#S
\GEOCFelargirauto#S
\GEOCFfontenete#S
\GEOCFhauteur#S
\GEOCFlarg#S
\GEOCFlargnum#S
\GEOCFoffset#S
\GEOCFoffseth#S
\GEOCFpolnum#S
\GEOCFtaillecmd#S
\GEOCFtailleres#S
\GEOCFtitre#S
\hauteurboitecmdxcas#S
\hauteurboiteggbcmd#S
\hauteurboiteggbres#S
\hauteurboiteggbtitre#S
\hauteurboiteresxcas#S
\maboitecmdxcas#S
\maboiteggbcmd#S
\maboiteggbres#S
\maboiteggbtitre#S
\maboiteresxcas#S
\offsetcfgeogebra#S
\offsetcfxcas#S
\thegeogebracfnum#S
\thexcascfnum#S
\XCCFcoulcmd#S
\XCCFcouleur#S
\XCCFcoulres#S
\XCCFelargirauto#S
\XCCFesplg#S
\XCCFfontenete#S
\XCCFlarg#S
\XCCFoffset#S
\XCCFoffseth#S
\XCCFposres#S
\XCCFtaillecmd#S
\XCCFtailleres#S
\XCCFtxtopts#S
\GEOCFcolfond#S
\XCCFcolfond#S
