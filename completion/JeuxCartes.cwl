# JeuxCartes package
# Matthew Bertucci 2023/02/26 for v0.2.3

#include:graphicx
#include:xcolor
# loads table and svgnames options of xcolor
#include:tikz
#include:tikzlibrarycalc
#include:pgffor
#include:xfp
#include:listofitems
#include:xstring
#include:xparse
#include:simplekv
#include:xinttools
#include:randomlist
#include:pifont

\AffCarteJeu{carte}
\AffCarteJeu[options%keyvals]{carte}

#keyvals:\AffCarteJeu
Hauteur=%<nombre%>
TypeJeu=#Poker,Pokerv2,Pokerv3,Pokerv4,Pokerv5,Tarot,Uno
Rotation=%<degrees%>
AlignementV=%<factor%>
Tikz#true,false
DecalageX=%<nombre%>
DecalageY=%<nombre%>
TikzAutonome#true,false
#endkeyvals

\AffCartesJeu{liste de cartes}
\AffCartesJeu[options%keyvals]{liste de cartes}

#keyvals:\AffCartesJeu
Hauteur=%<nombre%>
TypeJeu=#Poker,Pokerv2,Pokerv3,Pokerv4,Pokerv5,Tarot,Uno
#endkeyvals

\MainCartesJeu{liste de cartes}
\MainCartesJeu[options%keyvals]{liste de cartes}

#keyvals:\MainCartesJeu
Hauteur=%<nombre%>
TypeJeu=#Poker,Pokerv2,Pokerv3,Pokerv4,Pokerv5,Tarot,Uno
EspH=%<coefficient%>
EspV=%<coefficient%>
Eventail#true,false
Rotation=%<degrees%>
AlignementV=%<factor%>
Inverse#true,false
#endkeyvals

\MainCartesJeuAleatoire{nombre de cartes}
\MainCartesJeuAleatoire[options%keyvals]{nombre de cartes}

#keyvals:\MainCartesJeuAleatoire
Hauteur=%<nombre%>
TypeJeu=#Poker,Pokerv2,Pokerv3,Pokerv4,Pokerv5,Tarot,Belote,Belotev2,Belotev3,Belotev4,Belotev5,Bataille,Bataillev2,Bataillev3,Bataillev4,Bataillev5,Rami,Ramiv2,Ramiv3,Ramiv4,Ramiv5,Uno
EspH=%<coefficient%>
EspV=%<coefficient%>
Eventail#true,false
Rotation=%<degrees%>
AlignementV=%<factor%>
Inverse#true,false
#endkeyvals

\AffMiniCarteJeu{carte}
\AffMiniCarteJeu[options%keyvals]{carte}
\MainMiniCartesJeu{liste de cartes}
\MainMiniCartesJeu[options%keyvals]{liste de cartes}

#keyvals:\AffMiniCarteJeu,\MainMiniCartesJeu
Largeur=##L
FondAtout=#%color
#endkeyvals

\MainMiniCartesJeuAleatoire{nombre de cartes}
\MainMiniCartesJeuAleatoire[options%keyvals]{nombre de cartes}

#keyvals:\MainMiniCartesJeuAleatoire
Largeur=##L
FondAtout=#%color
TypeJeu=#Poker,Tarot,Belote,Bataille,Rami
#endkeyvals

# not documented
\AffCarteJeuAlignementV#S
\AffCarteJeuDecalageX#S
\AffCarteJeuDecalageY#S
\AffCarteJeuHauteur#S
\AffCarteJeuRotation#S
\AffCarteJeuType#S
\CarteDebutRand#S
\CarteMain#S
\CarteMainChoisie#S
\CarteMainPrefixe#S
\CarteMainType#S
\CartePrefixe#S
\CartesJeuBataille#S
\CartesJeuBelote#S
\CartesJeuPoker#S
\CartesJeuRami#S
\CartesJeuTarot#S
\CartesJeuUno#S
\csCoul#S
\csCplt#S
\csFond#S
\csSymb#S
\csVal#S
\DecAngleMain#S
\EchelleCarteDecalage#S
\HauteurGenerique#S
\ListeCartesMain#S
\ListeCartesMainlen#S
\MainAlignementV#S
\MainDecalH#S
\MainDecalV#S
\MainHauteur#S
\MainJeuType#S
\MainOffset#S
\MainRotation#S
\MainSimpleHauteur#S
\MainSimpleJeuType#S
\MiniCarteFondAtout#S
\MiniCarteLargeur#S
\MiniCarteMainChoisie#S
\MiniCartesJeuBataille#S
\MiniCartesJeuBelote#S
\MiniCartesJeuPoker#S
\MiniCartesJeuRami#S
\MiniCartesJeuTarot#S
\MiniCartesMain#S
\MiniMainAleaFondAtout#S
\MiniMainAleaLargeur#S
\MiniMainAleaType#S
\MiniMainFondAtout#S
\MiniMainLargeur#S
\NbCartesMain#S
\OptionTikzCBB#S
\SecondOffset#S

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
