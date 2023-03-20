# JeuxCartes package
# Matthew Bertucci 2023/03/20 for v0.2.4

#include:graphicx
#include:tikz
#include:tikzlibrarycalc
#include:pgffor
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
StyleJeu=#v1,v2,v3,v4,v5,fr,bicycl
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
StyleJeu=#v1,v2,v3,v4,v5,fr,bicycl
#endkeyvals

\MainCartesJeu{liste de cartes}
\MainCartesJeu[options%keyvals]{liste de cartes}

#keyvals:\MainCartesJeu
Hauteur=%<nombre%>
TypeJeu=#Poker,Pokerv2,Pokerv3,Pokerv4,Pokerv5,Tarot,Uno
StyleJeu=#v1,v2,v3,v4,v5,fr,bicycl
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
StyleJeu=#v1,v2,v3,v4,v5,fr,bicycl
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
\AffCarteJeuStyle#S
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
\MainAleaAlignementV#S
\MainAleaDecalH#S
\MainAleaDecalV#S
\MainAleaHauteur#S
\MainAleaJeuStyle#S
\MainAleaJeuType#S
\MainAleaRotation#S
\MainAlignementV#S
\MainDecalH#S
\MainDecalV#S
\MainHauteur#S
\MainJeuStyle#S
\MainJeuType#S
\MainOffset#S
\MainRotation#S
\MainSimpleHauteur#S
\MainSimpleJeuStyle#S
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
