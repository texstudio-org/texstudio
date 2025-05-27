# JeuxCartes package
# Matthew Bertucci 2025/05/27 for v0.3.2

#include:graphicx
#include:tikz
#include:tikzlibrarycalc
#include:pgffor
#include:listofitems
#include:xstring
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
TypeJeu=#Poker,Tarot,Belote,Bataille,Rami,PokerEN,BeloteEN,BatailleEN,RamiEN
#endkeyvals

\JeuCompletBeloteTriHaut
\JeuCompletBeloteTriCoul
\JeuCompletPokerTriHaut
\JeuCompletPokerTriHautJok
\JeuCompletPokerTriCoul
\JeuCompletTarotTriHaut
\JeuCompletTarotTriCoul
\JeuCompletPokerTriCoulJok
