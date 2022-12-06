# bclogo package
# Matthew Bertucci 2/23/2022 for v3.1

#include:xkeyval
#include:ifthen
#include:graphicx
#include:mdframed
#include:ifpdf
#include:etoolbox

#keyvals:\usepackage/bclogo#c
tikz
pstricks
blur
#endkeyvals

#ifOption:tikz
#include:tikz
#include:tikzlibraryshadows
#include:tikzlibrarydecorations.pathmorphing
#endif

#ifOption:pstricks
#include:pstricks
#include:pst-grad
#include:pst-coil
#endif

#ifOption:blur
#include:pst-blur
\pagecolorOLD{color}#S
#endif

\begin{bclogo}{titre%text}
\begin{bclogo}[options%keyvals]{titre%text}
\end{bclogo}

#keyvals:\begin{bclogo}
couleur=#%color
couleurTexte=#%color
couleurBord=#%color
couleurBarre=#%color
epBord=%<valeur%>
arrondi=%<valeur%>
noborder#true,false
marge=%<entier%>
margeG=%<valeur%>
margeD=%<valeur%>
cadreTitre#true,false
sousTitre=%<titre%>
logo=%<logo%>
epOmbre=%<valeur en cm%>
couleurOmbre=#%color
barre=#none,line,snake,motif,zigzag,imageExt,imageClip,wave
epBarre=%<valeur en pt%>
tailleOndu=%<valeur en pt%>
motifBarre=%<motif%>
imageBarre=%<imagefile%>
avecBarre#true,false
nobreak#true,false
blur#true,false
ombre#true,false
#endkeyvals

\bcStyleTitre{text}#*
\bcStyleSousTitre{text}#*
\bcfleur
\bcpanchant
\bcnote
\bcetoile
\bcours
\bcattention
\bccoeur
\bcorne
\bcdanger
\bcsmbh
\bcsmmh
\bctakecare
\bclampe
\bcbook
\bctrefle
\bcquestion
\bccrayon
\bcspadesuit
\bcinfo
\bcplume
\bcbombe
\bccube
\bcdodecaedre
\bcicosaedre
\bcoctaedre
\bctetraedre
\bcdallemagne
\bcdautriche
\bcdbelgique
\bcdbulgarie
\bcdfrance
\bcditalie
\bcdluxembourg
\bcdpaysbas
\bcsoleil
\bceclaircie
\bcpluie
\bcneige
\bcinterdit
\bcpoisson
\bchorloge
\bccalendrier
\bcrosevents
\bcyin
\bcdz
\bcvelo
\bcpeaceandlove
\bcoeil
\bcnucleaire
\bcfemme
\bchomme
\bcloupe
\bcrecyclage
\bcvaletcoeur
\bccle
\bcclefa
\bcclesol
\bcfeuvert
\bcfeujaune
\bcfeurouge
\bcfeutricolore
\bcoutil
\bctrombone
\bcstop
\logowidth#L
\listofbclogo
\titrebclogo#*
\bccaption{text}#*
\bclogotitre#*
\styleSousTitre{text}#S
\thebclogocompteur#*

\ifbclogotikz#*
\bclogotikztrue#*
\bclogotikzfalse#*
\ifbclogoblur#*
\bclogoblurtrue#*
\bclogoblurfalse#*
\PackageName#S
\filedate#S
\fileversion#S
