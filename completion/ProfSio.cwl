# ProfSio package
# Matthew Bertucci 2023/06/26 for v0.1.1

#include:tikz
#include:pgffor
#include:tabularray
#include:simplekv
#include:xstring
#include:listofitems
#include:xintexpr
#include:tikzlibrarypositioning
#include:tikzlibrarydecorations.pathreplacing
#include:tikzlibrarydecorations.markings
#include:tikzlibrarycalc
#include:tikzlibrarybabel
#include:tikzlibraryshapes
#include:tikzlibraryshapes.geometric

\begin{GrapheMPM}
\begin{GrapheMPM}<options TikZ>
\begin{GrapheMPM}[clés%keyvals]
\begin{GrapheMPM}[clés%keyvals]<options TikZ>
\end{GrapheMPM}

#keyvals:\begin{GrapheMPM}
CouleurDurees=#%color
CouleurFleches=#%color
LargeurCases
Epaisseur
Police=%<font commands%>
CouleurDates=#%color
CouleurBords=#%color
NoirBlanc#true,false
Grille={%<xmax,ymax%>}
#endkeyvals

\MPMPlaceNotice(coordonnées)
\MPMPlaceNotice*(coordonnées)
\MPMPlaceTache(coordonnées)(Tâche)(Dates)
\MPMPlaceTaches{%<(coordA)(TâcheA)(DatesA) / (coordB)(TâcheB)(DatesB) / ...%>}
\MPMPlaceDuree{%<TâcheA>TâcheB,durée%>}
\MPMPlaceDuree{%<TâcheA>TâcheB,durée%>}<%<options tikz%>>
\MPMPlaceDuree[%<options%>]{%<TâcheA>TâcheB,durée%>}
\MPMPlaceDuree[%<options%>]{%<TâcheA>TâcheB,durée%>}<%<options tikz%>>
\MPMPlaceDurees{%<TâcheA>TâcheB,durée / TâcheC>TâcheD,durée%>}
\MPMPlaceDurees{%<TâcheA>TâcheB,durée / TâcheC>TâcheD,durée%>}<%<options tikz%>>
\MPMPlaceDurees[%<options%>]{%<TâcheA>TâcheB,durée / TâcheC>TâcheD,durée%>}
\MPMPlaceDurees[%<options%>]{%<TâcheA>TâcheB,durée / TâcheC>TâcheD,durée%>}<%<options tikz%>>

#keyvals:\MPMPlaceDuree,\MPMPlaceDurees
Coude#true,false
SensCoude=#HV,VH,VHV
HauteurCoude=##L
DecalHorizDeb=##L
DecalVertDeb=##L
DecalHorizFin=##L
DecalVertFin=##L
#endkeyvals

\begin{TableKarnaugh}
\begin{TableKarnaugh}<options TikZ>
\begin{TableKarnaugh}[clés%keyvals]
\begin{TableKarnaugh}[clés%keyvals]<options TikZ>
\end{TableKarnaugh}

#keyvals:\begin{TableKarnaugh}
Couleur=#%color
Unite=##L
Variables=%<Gauche/Haut/Bas%>
Swap#true,false
Aide#true,false
Epaisseur=##L
CouleurCases=#%color
CouleurLegende=#%color
PosVarLaterale=#Gauche,Droite
Legende#true,false
#endkeyvals

\KarnaughCasesResult{contenu binaire des cases}
\KarnaughCasesResult*{contenu binaire des cases}
\KarnaughBlocRegroup{coinA}{coinB}
\KarnaughBlocRegroup[clés%keyvals]{coinA}{coinB}

#keyvals:\KarnaughBlocRegroup
Couleur=#%color
Type=#Centre,Gauche,Droite
Decalage=##L
#endkeyvals

\begin{GrapheTikz}
\begin{GrapheTikz}<options TikZ>
\begin{GrapheTikz}[clés%keyvals]
\begin{GrapheTikz}[clés%keyvals]<options TikZ>
\end{GrapheTikz}

#keyvals:\begin{GrapheTikz}
Police=%<font commands%>
Poids=%<font commands%>
CouleurSommets=#%color
CouleurFleches=#%color
TypeSommets=%<type%>
Epaisseur=%<épaisseur%>
Unite=##L
CouleurFT=#%color
Grille={%<xmax,ymax%>}
DimensionSommets=##L
PositionFleches=#Milieu,Fin
EchelleFleches=%<nombre%>
TypeFleche=%<type%>
#endkeyvals

\GrphPlaceSommets{liste coordonnées/sommet}
\GrphTraceAretes{liste arêtes}
\GrphTraceAretes<options tikz>{liste arêtes}
\GrphTraceAretes[type%keyvals]{liste arêtes}
\GrphTraceAretes[type%keyvals]<options tikz>{liste arêtes}
\GrphTraceAretes*{liste arêtes}
\GrphTraceAretes*<options tikz>{liste arêtes}
\GrphTraceAretes*[type%keyvals]{liste arêtes}
\GrphTraceAretes*[type%keyvals]<options tikz>{liste arêtes}

#keyvals:\GrphTraceAretes,\GrphTraceAretes*
Droit
AngleGauche
AngleDroite
Boucle
#endkeyvals

\DiagrammeSagittal{liaisons}
\DiagrammeSagittal<options TikZ>{liaisons}
\DiagrammeSagittal[clés%keyvals]{liaisons}
\DiagrammeSagittal[clés%keyvals]<options TikZ>{liaisons}
\DiagrammeSagittal*{liaisons}
\DiagrammeSagittal*<options TikZ>{liaisons}
\DiagrammeSagittal*[clés%keyvals]{liaisons}
\DiagrammeSagittal*[clés%keyvals]<options TikZ>{liaisons}

#keyvals:\DiagrammeSagittal,\DiagrammeSagittal*
DistElem=%<nombre%>
DistEns=%<nombre%>
LargEns=%<nombre%>
NomAppli=%<nom%>
CouleurE=#%color
CouleurAppli=#%color
CouleurF=#%color
CouleurFleches=#%color
TypeFleche=%<type%>
Epaisseur=##L
Police=%<font commands%>
NoirBlanc#true,false
Labels#true,false
Ensembles=%<nom%>
PosLabels=#haut,bas
#endkeyvals

# not documented
\begin{MPMtache}#S
\end{MPMtache}#S
\GrphCoulFleches#S
\GrphCoulFT#S
\GrphCoulSommets#S
\GrphDimSommet#S
\GrphGrille#S
\GrphPolicePoids#S
\GrphPoliceSommets#S
\GrphPosArrow#S
\GrphScaleArrow#S
\GrphTchick#S
\GrphTypeArrow#S
\GrphTypeSomm#S
\GrphUnit#S
\KarnaughBlocCoul[opt]{arg}#S
\KarnaughBlocCoul{arg}#S
\KGHcouleur#S
\KGHdecalage#S
\KGHTCoul#S
\KGHTCoulCases#S
\KGHTCoulLegende#S
\KGHTechelle#S
\KGHThick#S
\KGHTPosVarA#S
\KGHTvariables#S
\KGHtype#S
\MPMCoulDates#S
\MPMCoulDuree#S
\MPMCoulFleche#S
\MPMCoulTraits#S
\MPMFont#S
\MPMGrille#S
\MPMHautCoude#S
\MPMLargBoite#S
\MPMOffsetHFin#S
\MPMOffsetHInit#S
\MPMOffsetVFin#S
\MPMOffsetVInit#S
\MPMOrientation#S
\MPMThick#S
\DSListeEltE#S
\DSListeEltF#S
\DSEcartIN#S
\DSEcartIP#S
\DSLargPatates#S
\DSNomFctPatates#S
\DSCouleurE#S
\DSCouleurFct#S
\DSCouleurF#S
\DSCouleurArc#S
\DSTypeFleche#S
\DSThick#S
\DSPolicePatates#S
\DSPoliceLabels#S
\DSNomEns#S
\DSPosLabels#S