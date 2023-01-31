# WriteOnGrid package
# Matthew Bertucci 2023/01/31 for v0.1.2

#include:xcolor
# loads table and svgnames options of xcolor
#include:tikz
#include:simplekv
#include:xstring
#include:tikzlibrarycalc
#include:tikzlibrarypositioning

TyrianPurple#B
\ColSeyes
\ColRuled

\begin{EnvGrid}[keyvals]
\begin{EnvGrid}[keyvals]<color>
\end{EnvGrid}

#keyvals:\begin{EnvGrid}
NumSquares=%<<cols>x<rows>%>
Unit=%<number%>
Margin=%<number%>
Enlarge=%<L/R%>
Border#true,false
Grid=#5x5,Seyes,Ruled
Seyes#true,false
#endkeyvals

\WriteLine{text}
\WriteLine<alignment>{text}
\WriteLine[keyvals]{text}
\WriteLine[keyvals]<alignment>{text}

#keyvals:\WriteLine
OffsetH=%<num squares%>
OffsetV=##L
Scale=%<factor%>
#endkeyvals

\PassLine

# French versions of commands
\CoulSeyes
\CoulRuled

\begin{EnvQuadrillage}[clés%keyvals]
\begin{EnvQuadrillage}[clés%keyvals]<color>
\end{EnvQuadrillage}

#keyvals:\begin{EnvQuadrillage}
NbCarreaux=%<<nbCol>x<nbLig>%>
Unite=%<nombre%>
Marge=%<nombre%>
Elargir=%<L/R%>
Cadre#true,false
Grille=#5x5,Seyes,Ruled
CouleurBarreSeyes=#%color
#endkeyvals

\EcrireLigne{text}
\EcrireLigne<alignement>{text}
\EcrireLigne[clés%keyvals]{text}
\EcrireLigne[clés%keyvals]<alignement>{text}

#keyvals:\EcrireLigne
DecalH=%<nombre carreaux%>
DecalV=##L
Echelle=%<factor%>
#endkeyvals

\PasseLigne

\begin{PleinePageSeyes}
\begin{PleinePageSeyes}[options%keyvals]
\end{PleinePageSeyes}

#keyvals:\begin{PleinePageSeyes}
CouleurP=#%color
CouleurS=#%color
CouleurMarge=#%color
NumLignes#true,false
#endkeyvals

\LignePapierSeyes{text}
\LignePapierSeyes[options%keyvals]{text}
\LignePapierSeyes[options%keyvals]<alignement>(ajustement){text}

#keyvals:\LignePapierSeyes
Couleur=#%color
Ligne=%<numéro%>
Echelle=%<nombre%>
Largeur=%<nombre%>
#endkeyvals

\CadreNoteSeyes{numligne}
\CadreNoteSeyes[hauteur]{numligne}

\ParagraphePapierSeyes{text}
\ParagraphePapierSeyes[options%keyvals]{text}
\ParagraphePapierSeyes[options%keyvals]<alignement>(ajustement){text}

#keyvals:\ParagraphePapierSeyes
Couleur=#%color
Ligne=%<numéro%>
TaillePolice=%<nombre%>
Espacement=%<nombre%>
Largeur=%<nombre%>
#endkeyvals

\begin{PleinePageCinqCinq}
\begin{PleinePageCinqCinq}[options%keyvals]
\end{PleinePageCinqCinq}

#keyvals:\begin{PleinePageCinqCinq}
Couleur=#%color
CouleurMarge=#%color
NumLignes#true,false
#endkeyvals

\LignePapierCinqCinq{text}
\LignePapierCinqCinq[options%keyvals]{text}
\LignePapierCinqCinq[options%keyvals]<alignement>(ajustement){text}

#keyvals:\LignePapierCinqCinq
Couleur=#%color
Ligne=%<numéro%>
Echelle=%<nombre%>
Largeur=%<nombre%>
#endkeyvals

\CadreNoteCinqCinq{numligne}
\CadreNoteCinqCinq[hauteur]{numligne}

\ParagraphePapierCinqCinq{text}
\ParagraphePapierCinqCinq[options%keyvals]{text}
\ParagraphePapierCinqCinq[options%keyvals]<alignement>(ajustement){text}

#keyvals:\ParagraphePapierCinqCinq
Couleur=#%color
Ligne=%<numéro%>
TaillePolice=%<nombre%>
Espacement=%<nombre%>
Largeur=%<nombre%>
#endkeyvals

\begin{PleinePageRuled}
\begin{PleinePageRuled}[options%keyvals]
\end{PleinePageRuled}

#keyvals:\begin{PleinePageRuled}
Couleur=#%color
CouleurMarge=#%color
NumLignes#true,false
#endkeyvals

\LignePapierRuled{text}
\LignePapierRuled[options%keyvals]{text}
\LignePapierRuled[options%keyvals]<alignement>(ajustement){text}

#keyvals:\LignePapierRuled
Couleur=#%color
Ligne=%<numéro%>
Echelle=%<nombre%>
Largeur=%<nombre%>
#endkeyvals

\CadreNoteRuled{numligne}
\CadreNoteRuled[hauteur]{numligne}

\ParagraphePapierRuled{text}
\ParagraphePapierRuled[options%keyvals]{text}
\ParagraphePapierRuled[options%keyvals]<alignement>(ajustement){text}

#keyvals:\ParagraphePapierRuled
Couleur=#%color
Ligne=%<numéro%>
TaillePolice=%<nombre%>
Espacement=%<nombre%>
Largeur=%<nombre%>
#endkeyvals

# not documented
\CCFullCoul#S
\CCFullCoulM#S
\CCLigne#S
\CCLigneCouleur#S
\CCLigneEchelle#S
\CCLigneLarg#S
\CCPar#S
\CCParBase#S
\CCParCouleur#S
\CCParEchelle#S
\CCParLarg#S
\QuadCoulA#S
\QuadCoulB#S
\QuadCoulSeyes#S
\QuadEchelle#S
\QuadElar#S
\QuadElarD#S
\QuadElarG#S
\QuadNbCar#S
\QuadNbLig#S
\QuadType#S
\RuledFullCoul#S
\RuledFullCoulMarge#S
\RuledLigne#S
\RuledLigneCouleur#S
\RuledLigneEchelle#S
\RuledLigneLarg#S
\RuledPar#S
\RuledParBase#S
\RuledParCouleur#S
\RuledParEchelle#S
\RuledParLarg#S
\SeyesFullCoulM#S
\SeyesFullCoulP#S
\SeyesFullCoulS#S
\SeyesLigne#S
\SeyesLigneCouleur#S
\SeyesLigneEchelle#S
\SeyesLigneLarg#S
\SeyesPar#S
\SeyesParBase#S
\SeyesParCouleur#S
\SeyesParEchelle#S
\SeyesParLarg#S
\thelgquadri#S
\ValeurCarreau#S

# from table option of xcolor
#include:colortbl

# from svgnames option of xcolor
AliceBlue#B
DarkKhaki#B
Green#B
LightSlateGrey#B
AntiqueWhite#B
DarkMagenta#B
GreenYellow#B
LightSteelBlue#B
Aqua#B
DarkOliveGreen#B
Grey#B
LightYellow#B
Aquamarine#B
DarkOrange#B
Honeydew#B
Lime#B
Azure#B
DarkOrchid#B
HotPink#B
LimeGreen#B
Beige#B
DarkRed#B
IndianRed#B
Linen#B
Bisque#B
DarkSalmon#B
Indigo#B
Magenta#B
Black#B
DarkSeaGreen#B
Ivory#B
Maroon#B
BlanchedAlmond#B
DarkSlateBlue#B
Khaki#B
MediumAquamarine#B
Blue#B
DarkSlateGray#B
Lavender#B
MediumBlue#B
BlueViolet#B
DarkSlateGrey#B
LavenderBlush#B
MediumOrchid#B
Brown#B
DarkTurquoise#B
LawnGreen#B
MediumPurple#B
BurlyWood#B
DarkViolet#B
LemonChiffon#B
MediumSeaGreen#B
CadetBlue#B
DeepPink#B
LightBlue#B
MediumSlateBlue#B
Chartreuse#B
DeepSkyBlue#B
LightCoral#B
MediumSpringGreen#B
Chocolate#B
DimGray#B
LightCyan#B
MediumTurquoise#B
Coral#B
DimGrey#B
LightGoldenrod#B
MediumVioletRed#B
CornflowerBlue#B
DodgerBlue#B
LightGoldenrodYellow#B
MidnightBlue#B
Cornsilk#B
FireBrick#B
LightGray#B
MintCream#B
Crimson#B
FloralWhite#B
LightGreen#B
MistyRose#B
Cyan#B
ForestGreen#B
LightGrey#B
Moccasin#B
DarkBlue#B
Fuchsia#B
LightPink#B
NavajoWhite#B
DarkCyan#B
Gainsboro#B
LightSalmon#B
Navy#B
DarkGoldenrod#B
GhostWhite#B
LightSeaGreen#B
NavyBlue#B
DarkGray#B
Gold#B
LightSkyBlue#B
OldLace#B
DarkGreen#B
Goldenrod#B
LightSlateBlue#B
Olive#B
DarkGrey#B
Gray#B
LightSlateGray#B
OliveDrab#B
Orange#B
Plum#B
Sienna#B
Thistle#B
OrangeRed#B
PowderBlue#B
Silver#B
Tomato#B
Orchid#B
Purple#B
SkyBlue#B
Turquoise#B
PaleGoldenrod#B
Red#B
SlateBlue#B
Violet#B
PaleGreen#B
RosyBrown#B
SlateGray#B
VioletRed#B
PaleTurquoise#B
RoyalBlue#B
SlateGrey#B
Wheat#B
PaleVioletRed#B
SaddleBrown#B
Snow#B
White#B
PapayaWhip#B
Salmon#B
SpringGreen#B
WhiteSmoke#B
PeachPuff#B
SandyBrown#B
SteelBlue#B
Yellow#B
Peru#B
SeaGreen#B
Tan#B
YellowGreen#B
Pink#B
Seashell#B
Teal#B
