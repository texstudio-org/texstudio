# ProfLycee package
# Matthew Bertucci 2/19/2022 for v1.0.6

#include:xcolor
# xcolor loaded with table and svgnames options
#include:amssymb
#include:tikz
# loads calc, decorations.pathreplacing, decorations.markings, and arrows.meta tikzlibraries
#include:pgf
#include:pgffor
#include:ifthen
#include:environ
#include:xparse
#include:xkeyval
#include:xfp
#include:xstring
#include:simplekv
#include:listofitems
#include:xintexpr
#include:tabularray
#include:fontawesome5
#include:tcolorbox
# tcolorbox loaded with most option and minted library loaded by default
#include:ifluatex
#include:fancyvrb
#include:pythontex

#keyvals:\usepackage/ProfLycee#c
nominted
#endkeyvals

\splinetikz
\splinetikz[paramètres%keyvals]

#keyvals:\splinetikz
liste=%<x1/y1/d1§x2/y2/d2§...%>
width=##L
couleur=#%color
coeffs=
couleurpoints=#%color
taillepoints=##L
style={%<TikZ clés%>}
affpoints#true,false
#endkeyvals

\tangentetikz
\tangentetikz[paramètres%keyvals]

#keyvals:\tangentetikz
liste=%<x1/y1/d1§x2/y2/d2§...%>
width=##L
couleur=#%color
xl=%<num%>
xr=%<num%>
style={%<TikZ clés%>}
point=%<num%>
#endkeyvals

\paramCF
\paramCF[paramètres%keyvals]

#keyvals:\paramCF
larg=%<largeur%>
esplg=##L
premcol=%<largeur%>
hpremcol=%<hauteur%>
taille=%<fontsize cmd%>
couleur=#%color
titre#true,false
tailletitre=%<fontsize cmd%>
poscmd=#centre,gauche,right
posres=#centre,gauche,right
couleurcmd=#%color
couleurres=#%color
sep#true,false
menu#true,false
labeltitre
#endkeyvals

\ligneCF{commande de celui%text}{commande de sortie%text}
\ligneCF[paramètres%keyvals]{commande de celui%text}{commande de sortie%text}

#keyvals:\ligneCF
hc=%<hauteur%>
hr=%<hauteur%>
#endkeyvals

\begin{envcodepythontex}#V
\begin{envcodepythontex}[paramètres%keyvals]#V
\end{envcodepythontex}

#keyvals:\begin{envcodepythontex}
largeur=##L
centre#true,false
lignes#true,false
#endkeyvals

\begin{envcodepythonminted}#V
\begin{envcodepythonminted}[largeur%l][tcolorbox options]#V
\begin{envcodepythonminted}*#V
\begin{envcodepythonminted}*[largeur%l][tcolorbox options]#V
\end{envcodepythonminted}

\begin{envconsolepythontex}#V
\begin{envconsolepythontex}[paramètres%keyvals]#V
\end{envconsolepythontex}

#keyvals:\begin{envconsolepythontex}
largeur=##L
centre#true,false
label#true,false
#endkeyvals

\begin{envpseudocode}
\begin{envpseudocode}[largeur%l][tcolorbox options]
\begin{envpseudocode}*
\begin{envpseudocode}*[largeur%l][tcolorbox options]
\end{envpseudocode}

\begin{PLtermwin}{titre=%<texte%>}#V
\begin{PLtermwin}[%<largeur%>]{titre=%<texte%>}[%<tcolorbox options%>]#V
\end{PLtermwin}

\begin{PLtermunix}{titre=%<texte%>}#V
\begin{PLtermunix}[%<largeur%>]{titre=%<texte%>}[%<tcolorbox options%>]#V
\end{PLtermunix}

\begin{PLtermosx}{titre=%<texte%>}#V
\begin{PLtermosx}[%<largeur%>]{titre=%<texte%>}[%<tcolorbox options%>]#V
\end{PLtermosx}

# from table option of xcolor
#include:colortbl
\rowcolors[commands]{row}{even-row-color}{odd-row-color}
\rowcolors[commands]{row}{color}{color}#S
\rowcolors*[commands]{row}{even-row-color}{odd-row-color}
\rowcolors*[commands]{row}{color}{color}#S
\showrowcolors
\hiderowcolors
\rownum

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

# from most option of tcolorbox (repeats removed)
#include:amsmath
#include:incgraph
#include:listings
#include:listingsutf8
#include:shellesc
#include:pdfcol

# from minted tcolorbox library
#include:minted

# not documented
\begin{pythont}#S
\end{pythont}#S
\extractcoeff{liste}{numero}#*
\lcoeffs#S
\COEFFA#S
\COEFFB#S
\COEFF#S
\SPLliste#S
\SPLepaisseur#S
\SPLcouleur#S
\SPLcoeffs#S
\SPLcouleurpoints#S
\SPLtaillepoints#S
\SPLstyle#S
\SPLlistepoints#S
\SPLnbsplines#S
\SPLlistepointslen#S
\xa#S
\ya#S
\fprimea#S
\xb#S
\yb#S
\fprimeb#S
\TGTliste#S
\TGTepaisseur#S
\TGTcouleur#S
\TGTXL#S
\TGTXR#S
\TGTstyle#S
\TGTnumpt#S
\TGTlistepoints#S
\TGTDEB#S
\TGTFIN#S
\CFchap#S
\theCFnum#S
\CFlarg#S
\CFesplg#S
\CFpremcol#S
\CFhpremcol#S
\CFtaille#S
\CFcouleur#S
\CFtailletitre#S
\CFcoulcmd#S
\CFcoulres#S
\CFposcmd#S
\CFposres#S
\CFlabeltitre#S
\CFhle#S
\CFhlr#S
\CFL#S
\CFLA#S
\CSPYlargeur#S
\hookcenterpre#S
\hookcenterpost#S
\CODPYlargeur#S
\verbcenterpre#S
\verbcenterpost#S
\begin{tcpythontexcode}#*
\begin{tcpythontexcode}[width]#*
\end{tcpythontexcode}#*
\begin{tcpythontexcodeno}#*
\begin{tcpythontexcodeno}[width]#*
\end{tcpythontexcodeno}#*
\algomathttPL{text%plain}#*
\PLcommandeswin#*
\termwintitre#*
\termwintitre[opt]#*
\PLUbuntuWhite#*
\PLUbuntuMin#*
\PLUbuntuClose#*
\PLUbuntuMax#*
\termnuxtitre#*
\termnuxtitre[opt]#*
\PLOSXRed#*
\PLOSXOrange#*
\PLOSXGreen#*
\PLOSXLG#*
\termosxtitre#*
\termosxtitre[opt]#*

PLmpurple#B
PLmgray#B
PLogray#B
PLoorange#B
PLterminal#B
PLlinux#B
PLwinblue#B
PLosxgray#B

#keyvals:\tcbset,\begin{tcolorbox},\tcbsetforeverylayer,\tcbox,\newtcolorbox,\renewtcolorbox,\newtcbox,\renewtcbox,\tcolorboxenvironment,\tcbsubtitle,\tcbsidebyside,\tcbsubskin,\tcbincludegraphics,\tcbincludepdf,\begin{tcbraster},\begin{tcbitemize},\tcbitem,\begin{tcboxedraster},\begin{tcboxeditemize},\begin{tcblisting},\tcbinputlisting,\newtcblisting,\renewtcblisting,\newtcbinputlisting,\renewtcbinputlisting,\newtcbtheorem,\renewtcbtheorem,\tcboxmath,\tcbhighmath,\usetcboxarray,\consumetcboxarray,\posterbox,\begin{posterboxenv},\tcboxfit,\newtcboxfit,\renewtcboxfit,\DeclareTColorBox,\NewTColorBox,\RenewTColorBox,\ProvideTColorBox,\DeclareTotalTColorBox,\NewTotalTColorBox,\RenewTotalTColorBox,\ProvideTotalTColorBox,\DeclareTCBox,\NewTCBox,\RenewTCBox,\ProvideTCBox,\DeclareTotalTCBox,\NewTotalTCBox,\RenewTotalTCBox,\ProvideTotalTCBox,\DeclareTCBListing,\NewTCBListing,\RenewTCBListing,\ProvideTCBListing,\DeclareTCBInputListing,\NewTCBInputListing,\RenewTCBInputListing,\ProvideTCBInputListing,\DeclareTCBoxFit,\NewTCBoxFit,\RenewTCBoxFit,\ProvideTCBoxFit,\DeclareTotalTCBoxFit,\NewTotalTCBoxFit,\RenewTotalTCBoxFit,\ProvideTotalTCBoxFit,\tcboxverb,\begin{docCommand},\begin{docCommand*},\begin{docCommands},\begin{docEnvironment},\begin{docEnvironment*},\begin{docEnvironments},\begin{docKey},\begin{docKey*},\begin{docKeys},\begin{docPathOperation},\begin{docPathOperation*},\begin{docPathOperations},\docValue,\docValue*,\docAuxCommand,\docAuxCommand*,\docAuxEnvironment,\docAuxEnvironment*,\docAuxKey,\docAuxKey*,\docCounter,\docCounter*,\docLength,\docLength*,\docColor,\docColor*,\begin{dispExample*},\begin{dispListing*},\tcbdocmarginnote
stylepythontex
stylepythonnolineos
stylepythonlineos
pytmintedno
pytminted
stylepseudocodePL
PLfaketermwin
PLtermlinux
PLfaketermosx
#endkeyvals