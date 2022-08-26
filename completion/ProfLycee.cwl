# ProfLycee package
# Matthew Bertucci 2022/08/25 for v1.2.3

#include:xcolor
# xcolor loaded with table and svgnames options
#include:tikz
# loads calc, decorations, decorations.pathreplacing, decorations.markings, arrows, and arrows.meta tikzlibraries
#include:tkz-tab
#include:mathtools
#include:pgf
#include:pgffor
#include:ifthen
#include:xparse
#include:xkeyval
#include:xfp
#include:xstring
#include:xintexpr
#include:xintbinhex
#include:simplekv
#include:listofitems
#include:tabularray
#include:siunitx
#include:fontawesome5
#include:csvsimple-l3
#include:tcolorbox
# tcolorbox loaded with most option and minted library loaded by default
#include:ifluatex
#include:fancyvrb
#include:pythontex

#keyvals:\usepackage/ProfLycee#c
nominted
build
csvii
#endkeyvals

#ifOption:csvii
#include:csvsimple-legacy
#endif

\splinetikz
\splinetikz[options%keyvals]

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
\tangentetikz[options%keyvals]

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
\paramCF[options%keyvals]

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
\ligneCF[options%keyvals]{commande de celui%text}{commande de sortie%text}

#keyvals:\ligneCF
hc=%<hauteur%>
hr=%<hauteur%>
#endkeyvals

\begin{envcodepython}{tcolorbox options}#V
\begin{envcodepython}[largeur]{tcolorbox options}#V
\begin{envcodepython}*{tcolorbox options}#V
\begin{envcodepython}*[largeur]{tcolorbox options}#V
\end{envcodepython}

\envcodepythonfichier{tcolorbox options}{file}#i
\envcodepythonfichier[largeur]{tcolorbox options}{file}#i
\envcodepythonfichier*{tcolorbox options}{file}#i
\envcodepythonfichier*[largeur]{tcolorbox options}{file}#i

\begin{envcodepythontex}#V
\begin{envcodepythontex}[options%keyvals]#V
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
\begin{envconsolepythontex}[options%keyvals]#V
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

\liencapytale{code}
\liencapytale[prefix]{code}
\liencapytale*{code}
\liencapytale*[prefix]{code}

\pavePL
\pavePL[options%keyvals]

#keyvals:\pavePL
largeur=%<num%>
profondeur=%<num%>
hauteur=%<num%>
angle=%<degrees%>
fuite=%<num%>
sommets=%<A1§...§A8%>
epaisseur=%<épaisseur%>
aff#true,false
plein#true,false
cube#true,false
#endkeyvals

\tetraPL
\tetraPL[options%keyvals]

#keyvals:\tetraPL
largeur=%<num%>
profondeur=%<num%>
hauteur=%<num%>
alpha=%<degrees%>
beta=%<degrees%>
sommets=%<A1§...§A8%>
epaisseur=%<épaisseur%>
aff#true,false
plein#true,false
#endkeyvals

\convertfraction{fraction expr}
\convertfraction[d ou t]{fraction expr}

\ensPL{a1/a2/...}
\ensPL[options%keyvals]{a1/a2/...}

#keyvals:\ensPL
sep={%<separator%>}
option={%<code%>}
mathpunct#true,false
#endkeyvals

\recurrPL[options%keyvals]
\recurrPL[options%keyvals][options du tracé]
\recurrPL[options%keyvals][options du tracé][option supplémentaire des termes]

#keyvals:\recurrPL
fct=%<fonction%>
nom=%<nom%>
no=%<l’indice initial%>
uno=%<la valeur du terme initial%>
nb=%<nombre%>
poslabel=%<pos%>
decallabel=##L
taillelabel=%<fontsize cmd%>
afftermes#true,false
#endkeyvals

\cercletrigoPL
\cercletrigoPL[options%keyvals]

#keyvals:\cercletrigoPL
rayon=%<rayon%>
epaisseur=%<épaisseur%>
epaisseursol=%<épaisseur%>
marge=%<marge%>
taillevaleurs=%<fontsize cmd%>
tailleangles=%<fontsize cmd%>
couleurfond=#%color
decal=##L
moinspi#true,false
affangles#true,false
afftraits#true,false
affvaleurs#true,false
equationcos#true,false
equationsin#true,false
cos=%<degrees%>
sin=%<degrees%>
couleursol=#%color
#endkeyvals

\aidesignePL
\aidesignePL[options%keyvals]

\aidesignetkztabPL{numligne}
\aidesignetkztabPL{numligne}[echelle]
\aidesignetkztabPL{numligne}[echelle][décalage horizontal]
\aidesignetkztabPL[options%keyvals]{numligne}
\aidesignetkztabPL[options%keyvals]{numligne}[echelle]
\aidesignetkztabPL[options%keyvals]{numligne}[echelle][décalage horizontal]

#keyvals:\aidesignePL,\aidesignetkztabPL
code=
couleur=#%color
racines=%<racines%>
largeur=%<num%>
hauteur=%<num%>
cadre#true,false
#endkeyvals

\PLreglin{listeX}{listeY}
\PLreglin[options%keyvals]{listeX}{listeY}

#keyvals:\PLreglin
nomcoeffa=%<nom%>
nomcoeffb=%<nom%>
nomcoeffr=%<nom%>
nomcoeffrd=%<nom%>
nomxmin=%<nom%>
nomxmax=%<nom%>
#endkeyvals

\LX#*
\LY#*
\LNB#S
\LXSomme#*
\LYSomme#*
\LXmoy#*
\LYmoy#*
\LXvar#*
\LYvar#*
\LXYvar#*

\PLreglinpts{listeX}{listeY}
\PLreglinpts[options%keyvals]{listeX}{listeY}

#keyvals:\PLreglinpts
couleur=#%color
taille=##L
Ox=%<num%>
Oy=%<num%>
#endkeyvals

#keyvals:\tikz#c,\begin{tikzpicture}#c,\tikzset#c
Ox=%<num%>
Oy=%<num%>
xmin=%<num%>
xmax=%<num%>
ymin=%<num%>
ymax=%<num%>
xgrille=%<num%>
xgrilles=%<num%>
ygrille=%<num%>
ygrilles=%<num%>
xunit=%<num%>
yunit=%<num%>
#endkeyvals

\PLgrilletikz
\PLgrilletikz[options%keyvals]
\PLgrilletikz[options%keyvals][options grille ppale]#*
\PLgrilletikz[options%keyvals][options grille ppale][options grille second]

#keyvals:\PLgrilletikz
affp#true,false
affs#true,false
#endkeyvals

\PLaxestikz
\PLaxestikz[options%keyvals]

#keyvals:\PLaxestikz
epaisseur=##L
police=%<font commands%>
labelx=%<text%>
labely=%<text%>
afflabel=#x,y,xy
poslabelx=%<TikZ pos%>
poslabely=%<TikZ pos%>
echellefleche=%<num%>
typefleche=%<type%>
#endkeyvals

\PLaxextikz{valeurs}
\PLaxextikz[options%keyvals]{valeurs}
\PLaxeytikz{valeurs}
\PLaxeytikz[options%keyvals]{valeurs}

#keyvals:\PLaxextikz,\PLaxeytikz
epaisseur=##L
police=%<font commands%>
posgrad=%<TikZ pos%>
hautgrad=##L
affgrad=#true,false
afforigine=#true,false
annee=#true,false
#endkeyvals

\PLfenetre
\PLfenetresimple{liste abscisses}{liste ordonnées}
\PLfenetresimple{liste abscisses}<options axe Oy>{liste ordonnées}
\PLfenetresimple<options axe Ox>{liste abscisses}{liste ordonnées}
\PLfenetresimple<options axe Ox>{liste abscisses}<options axe Oy>{liste ordonnées}

\PLorigine
\PLorigine[options%keyvals]

#keyvals:\PLorigine
police=%<font commands%>
pos=%<TikZ pos%>
decal=##L
valeur=%<num%>
#endkeyvals

\PLnuagepts{listeX}{listeY}
\PLnuagepts[options%keyvals]{listeX}{listeY}

#keyvals:\PLnuagepts
taille=##L
couleur=#%color
style=#o,x,+
#endkeyvals

\PLnuageptmoy
\PLnuageptmoy[options%keyvals]

#keyvals:\PLnuageptmoy
police=%<font commands%>
taille=##L
couleur=#%color
style=#o,x,+
xg=%<num%>
yg=%<num%>
nom=%<text%>
pos=%<TikZ pos%>
decal=##L
affnom=#true,false
#endkeyvals

\PLcourbe{formule}{domaine}
\PLcourbe[TikZ clés]{formule}{domaine}

\axexOx#*
\axeyOy#*
\xmin#*
\xmax#*
\ymin#*
\ymax#*
\xgrille#*
\xgrilles#*
\ygrille#*
\ygrilles#*
\xunit#*
\yunit#*

\PLconvdecbin{nombre}
\PLconvdecbin[options%keyvals]{nombre}
\PLconvdecbin*{nombre}
\PLconvdecbin*[options%keyvals]{nombre}

#keyvals:\PLconvdecbin,\PLconvdecbin*
affbase#true,false
#endkeyvals

\PLconvbinhex{nombre}
\PLconvbinhex[options%keyvals]{nombre}

#keyvals:\PLconvbinhex
affbase#true,false
details#true,false
trait=##L
#endkeyvals

\PLconvtodec{nombre}
\PLconvtodec[options%keyvals]{nombre}

#keyvals:\PLconvtodec
basedep=%<2 ou 16%>
affbase#true,false
details#true,false
zeros#true,false
#endkeyvals

#keyvals:\draw#c
mainlevee
mainlevee=%<segment-length%> et %<amplitude%>
#endkeyvals

\PLpixelart{file}#i
\PLpixelart[options%keyvals]{file}#i

#keyvals:\PLpixelart
codes=%<chaîne%>
couleurs={%<couleur1,couleur2,...%>}
symboles={%<symbol1,symbol2,...%>}
correction#true,false
symb#true,false
style=%<font commands%>
#endkeyvals

# from table option of xcolor
#include:colortbl
\rowcolors{row}{odd-row-color}{even-row-color}
\rowcolors[commands]{row}{odd-row-color}{even-row-color}
\rowcolors{row}{color}{color}#S
\rowcolors[commands]{row}{color}{color}#S
\rowcolors*{row}{odd-row-color}{even-row-color}
\rowcolors*[commands]{row}{odd-row-color}{even-row-color}
\rowcolors*{row}{color}{color}#S
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
\algomathttPL{text%plain}#*
\axesafflabel#S
\axesechellefleche#S
\axesfont#S
\axeslabelx#S
\axeslabely#S
\axesordecal#S
\axesorfont#S
\axesorpos#S
\axesorval#S
\axesposlabelx#S
\axesposlabely#S
\axestypefleche#S
\axeswidth#S
\axexfont#S
\axexposlabel#S
\axextickwidth#S
\axextickwidthA#S
\axextickwidthB#S
\axexwidth#S
\axeyfont#S
\axeyposlabel#S
\axeytickwidth#S
\axeytickwidthA#S
\axeytickwidthB#S
\axeywidth#S
\basedepart#S
\begin{PLstats}#S
\begin{PLstats}[opt]#S
\begin{pythont}#S
\begin{tcpythontexcode}#*
\begin{tcpythontexcode}[width]#*
\begin{tcpythontexcodeno}#*
\begin{tcpythontexcodeno}[width]#*
\calculargument#S
\CFchap#S
\CFcoulcmd#S
\CFcouleur#S
\CFcoulres#S
\CFesplg#S
\CFhle#S
\CFhlr#S
\CFhpremcol#S
\CFL#S
\CFLA#S
\CFlabeltitre#S
\CFlarg#S
\CFposcmd#S
\CFposres#S
\CFpremcol#S
\CFtaille#S
\CFtailletitre#S
\chbrut#S
\CODPYlargeur#S
\COEFF#S
\COEFFA#S
\COEFFB#S
\cpt#S
\CSPYlargeur#S
\denominateur#S
\end{PLstats}#S
\end{pythont}#S
\end{tcpythontexcode}#*
\end{tcpythontexcodeno}#*
\epcrochet#S
\extractcoeff{liste}{numero}#*
\fctdecx#S
\fprimea#S
\fprimeb#S
\hookcenterpost#S
\hookcenterpre#S
\ifinal#S
\iinit#S
\indice#S
\LCNA#S
\lcoeffs#S
\LCPA#S
\listepointsaffiches#S
\nbblocs#S
\nbchiffres#S
\nbdepart#S
\nbgrp#S
\numerateur#S
\PATchiffres#S
\PATcouleurs#S
\PATlettres#S
\PATtaille#S
\PaveA#S
\PaveB#S
\PaveC#S
\PaveD#S
\PaveE#S
\PaveF#S
\PaveG#S
\PaveH#S
\PFListeSommets#S
\PFPaveAngl#S
\PFPaveFuite#S
\PFPaveHt#S
\PFPaveLg#S
\PFPavePf#S
\PFPaveSommets#S
\PFPaveSommets#S
\PFPaveThick#S
\PFTetraAlpha#S
\PFTetraBeta#S
\PFTetraHt#S
\PFTetraLg#S
\PFTetraPf#S
\PFTetraSommets#S
\PFTetraThick#S
\pixchf#S
\pixcnt#S
\pixcol#S
\pixpos#S
\PLcercleangles#S
\PLcerclecoleq#S
\PLcercledecal#S
\PLcerclefond#S
\PLcerclemarge#S
\PLcerclerayon#S
\PLcerclesolthick#S
\PLcerclethick#S
\PLcerclevalcos#S
\PLcerclevaleurs#S
\PLcerclevalsin#S
\PLcommandeswin#*
\PLconvblocbinhex[rule thickness]{binary integer}#*
\PLconvblocbinhex{binary integer}#*
\PLDm#S
\PLDM#S
\PLdomaine#S
\PLensopt#S
\PLenssep#S
\PLnuagepoints[opt]{arg}#S
\PLnuagepoints{arg}#S
\PLOSXGreen#*
\PLOSXLG#*
\PLOSXOrange#*
\PLOSXRed#*
\PLRecurfct#S
\PLRecurlabelsize#S
\PLRecurnb#S
\PLRecurno#S
\PLRecurnom#S
\PLRecuroffset#S
\PLRecurposlab#S
\PLRecuruno#S
\PLstrzeros{nombre}#*
\PLUbuntuClose#*
\PLUbuntuMax#*
\PLUbuntuMin#*
\PLUbuntuWhite#*
\ptmoycouleur#S
\ptmoycouleurA#S
\ptmoycouleurB#S
\ptmoydecal#S
\ptmoyfont#S
\ptmoynom#S
\ptmoypos#S
\ptmoystyle#S
\ptmoytaille#S
\ptmoyx#S
\ptmoyy#S
\ptscouleur#S
\ptscouleurA#S
\ptscouleurB#S
\ptsstyle#S
\ptstaille#S
\puiss#S
\RegLinCoeffa#S
\RegLinCoeffb#S
\RegLinCoeffr#S
\RegLinCoeffrd#S
\RegLinCoeffXmax#S
\RegLinCoeffXmin#S
\RegLinNuageCouleur#S
\RegLinNuageOx#S
\RegLinNuageOy#S
\RegLinNuageTaille#S
\resbrut#S
\resinter#S
\schematdsaff*{arg1}{arg2}{arg3}{arg4}#*
\schematdsaff{arg1}{arg2}{arg3}{arg4}#*
\schematdsparab{arg1}{arg2}{arg3}{arg4}{arg5}#*
\schematdsparab{arg1}{arg2}{arg3}{arg4}{arg5}[opt]#*
\SPLcoeffs#S
\SPLcouleur#S
\SPLcouleurpoints#S
\SPLepaisseur#S
\SPLliste#S
\SPLlistepoints#S
\SPLlistepointslen#S
\SPLnbsplines#S
\SPLstyle#S
\SPLtaillepoints#S
\tdscouleur#S
\tdshaut#S
\tdslarg#S
\tdsparam#S
\tdsracine#S
\termnuxtitre#*
\termnuxtitre[opt]#*
\termosxtitre#*
\termosxtitre[opt]#*
\termwintitre#*
\termwintitre[opt]#*
\TetraA#S
\TetraB#S
\TetraC#S
\TetraD#S
\TGTcouleur#S
\TGTDEB#S
\TGTepaisseur#S
\TGTFIN#S
\TGTliste#S
\TGTlistepoints#S
\TGTnumpt#S
\TGTstyle#S
\TGTXL#S
\TGTXR#S
\theCFnum#S
\verbcenterpost#S
\verbcenterpre#S
\xa#S
\xb#S
\xliste#S
\XPT#S
\ya#S
\yb#S
\yliste#S
\YPT#S

PLlinux#B
PLmgray#B
PLmpurple#B
PLogray#B
PLoorange#B
PLosxgray#B
PLterminal#B
PLwinblue#B
vertcapyt#B

#keyvals:\tcbset,\begin{tcolorbox},\tcbsetforeverylayer,\tcbox,\newtcolorbox,\renewtcolorbox,\newtcbox,\renewtcbox,\tcolorboxenvironment,\tcbsubtitle,\tcbsidebyside,\tcbsubskin,\tcbincludegraphics,\tcbincludepdf,\begin{tcbraster},\begin{tcbitemize},\tcbitem,\begin{tcboxedraster},\begin{tcboxeditemize},\begin{tcblisting},\tcbinputlisting,\newtcblisting,\renewtcblisting,\newtcbinputlisting,\renewtcbinputlisting,\newtcbtheorem,\renewtcbtheorem,\tcboxmath,\tcbhighmath,\usetcboxarray,\consumetcboxarray,\posterbox,\begin{posterboxenv},\tcboxfit,\newtcboxfit,\renewtcboxfit,\DeclareTColorBox,\NewTColorBox,\RenewTColorBox,\ProvideTColorBox,\DeclareTotalTColorBox,\NewTotalTColorBox,\RenewTotalTColorBox,\ProvideTotalTColorBox,\DeclareTCBox,\NewTCBox,\RenewTCBox,\ProvideTCBox,\DeclareTotalTCBox,\NewTotalTCBox,\RenewTotalTCBox,\ProvideTotalTCBox,\DeclareTCBListing,\NewTCBListing,\RenewTCBListing,\ProvideTCBListing,\DeclareTCBInputListing,\NewTCBInputListing,\RenewTCBInputListing,\ProvideTCBInputListing,\DeclareTCBoxFit,\NewTCBoxFit,\RenewTCBoxFit,\ProvideTCBoxFit,\DeclareTotalTCBoxFit,\NewTotalTCBoxFit,\RenewTotalTCBoxFit,\ProvideTotalTCBoxFit,\tcboxverb,\begin{docCommand},\begin{docCommand*},\begin{docCommands},\begin{docEnvironment},\begin{docEnvironment*},\begin{docEnvironments},\begin{docKey},\begin{docKey*},\begin{docKeys},\begin{docPathOperation},\begin{docPathOperation*},\begin{docPathOperations},\docValue,\docValue*,\docAuxCommand,\docAuxCommand*,\docAuxEnvironment,\docAuxEnvironment*,\docAuxKey,\docAuxKey*,\docCounter,\docCounter*,\docLength,\docLength*,\docColor,\docColor*,\begin{dispExample*},\begin{dispListing*},\tcbdocmarginnote
stylepythonlst
stylepythonlstnolineos
stylepythonlstlineos
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
