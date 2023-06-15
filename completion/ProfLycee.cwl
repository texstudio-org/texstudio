# ProfLycee package
# Matthew Bertucci 2023/06/15 for v2.7.0

#include:mathtools
#include:amssymb
#include:xcolor
# xcolor loaded with table and svgnames options
#include:tikz
#include:tkz-tab
#include:pgf
#include:pgffor
#include:ifthen
#include:xkeyval
#include:xstring
#include:xintexpr
#include:xintbinhex
#include:xinttools
#include:xintgcd
#include:randomlist
#include:simplekv
#include:listofitems
#include:tabularray
#include:settobox
#include:hologo
#include:fancyvrb
#include:nicefrac
#include:siunitx
#include:fontawesome5
#include:tikzlibrarycalc
#include:tikzlibrarydecorations
#include:tikzlibrarydecorations.pathreplacing
#include:tikzlibrarydecorations.markings
#include:tikzlibrarybabel
#include:tikzlibraryshapes.geometric
#include:tikzlibrarydecorations.pathmorphing
#include:tcolorbox
#include:tcolorboxlibrarymost
#include:tcolorboxlibraryminted
#include:iftex
#include:piton
#include:nicematrix
#include:cancel

#keyvals:\usepackage/ProfLycee#c
build
nonamssymb
#endkeyvals

\useproflyclib{librairies%keyvals}

#keyvals:\useproflyclib#c
piton
minted
pythontex
#endkeyvals

## Résolution approchée d’une équation ##
\ResolutionApprochee{équation}
\ResolutionApprochee{équation}[macro]
\ResolutionApprochee[options%keyvals]{équation}
\ResolutionApprochee[options%keyvals]{équation}[macro]

#keyvals:\ResolutionApprochee
Precision=%<integer%>
Intervalle=%<min:max%>
Variable=%<variable%>
#endkeyvals

## Présentation d’une solution d’équation par balayage ##
\SolutionTVI{fonction}{valeur}
\SolutionTVI[options%keyvals]{fonction}{valeur}

#keyvals:\SolutionTVI
NomFct=%<nom%>
NomSol=%<nom%>
va=%<nombre%>
vb=%<nombre%>
Precision=%<nombre%>
Stretch=%<factor%>
Balayage#true,false
Calculatrice#true,false
Majuscule#true,false
#endkeyvals

## Suites récurrentes simples ##
\CalculTermeRecurrence{fonction associée}
\CalculTermeRecurrence[options%keyvals]{fonction associée}

#keyvals:\CalculTermeRecurrence
No=%<nombre%>
UNo=%<nombre%>
Precision=%<nombre%>
N=%<nombre%>
#endkeyvals

\SolutionSeuil{fonction associée}{seuil}
\SolutionSeuil[options%keyvals]{fonction associée}{seuil}

#keyvals:\SolutionSeuil
NomSuite=%<nom%>
No=%<nombre%>
UNo=%<nombre%>
SolN=%<nombre%>
Precision=%<nombre%>
Stretch=%<factor%>
Balayage#true,false
Calculatrice#true,false
Simple#true,false
Majuscule#true,false
Exact#true,false
Conclusion#true,false
Sens=%<< ou >%>
#endkeyvals

\CompteurSeuil#*

## Valeur approchée d’une intégrale ##
\IntegraleApprochee{fonction}{a}{b}
\IntegraleApprochee[options%keyvals]{fonction}{a}{b}

#keyvals:\IntegraleApprochee
ResultatBrut#true,false
Methode=#RectanglesGauche,RectanglesDroite,RectanglesMilieu,Trapezes,Simpson
NbSubDiv=%<nombre%>
AffFormule#true,false
Expr=%<expr%>
Signe=%<signe%>
Variables=%<variables%>
#endkeyvals

## Équation réduite d’une droite ##
\EquationReduite{A/xa/ya,B/xb/yb}
\EquationReduite[d]{%<A/xa/ya,B/xb/yb%>}

## L’outil « Calcul Formel » ##
\CalculFormelParametres
\CalculFormelParametres[options%keyvals]

#keyvals:\paramCF
Largeur=%<largeur%>
EspaceLg=##L
PremCol=%<largeur%>
HautPremCol=%<hauteur%>
Taille=%<fontsize cmd%>
Couleur=#%color
Titre#true,false
TailleTitre=%<fontsize cmd%>
PosCmd=#centre,gauche,right
PosRes=#centre,gauche,right
CouleurCmd=#%color
CouleurRes=#%color
Sep#true,false
Menu#true,false
LabelTitre={%<texte%>}
#endkeyvals

\CalculFormelLigne{commande%text}{résultat%text}
\CalculFormelLigne[options%keyvals]{commande%text}{résultat%text}

#keyvals:\CalculFormelLigne
HautCmd=%<hauteur%>
HautRes=%<hauteur%>
#endkeyvals

\CFchap#*
\CFpremcol#*
\CFhpremcol#*

## Code Python « simple » via le package listings ##
\begin{CodePythonLst}{tcolorbox options}#V
\begin{CodePythonLst}[largeur%l]{tcolorbox options}#V
\begin{CodePythonLst}*{tcolorbox options}#V
\begin{CodePythonLst}*[largeur%l]{tcolorbox options}#V
\end{CodePythonLst}
\begin{CodePythonLstAlt}{tcolorbox options}#V
\begin{CodePythonLstAlt}[largeur%l]{tcolorbox options}#V
\begin{CodePythonLstAlt}*{tcolorbox options}#V
\begin{CodePythonLstAlt}*[largeur%l]{tcolorbox options}#V
\end{CodePythonLstAlt}

\CodePythonLstFichier{tcolorbox options}{file}
\CodePythonLstFichier[largeur%l]{tcolorbox options}{file}
\CodePythonLstFichier*{tcolorbox options}{file}
\CodePythonLstFichier*[largeur%l]{tcolorbox options}{file}
\CodePythonLstFichierAlt{tcolorbox options}{file}
\CodePythonLstFichierAlt[largeur%l]{tcolorbox options}{file}
\CodePythonLstFichierAlt*{tcolorbox options}{file}
\CodePythonLstFichierAlt*[largeur%l]{tcolorbox options}{file}

## Code Python via le package piton ##
\begin{CodePiton}{tcolorbox options}#V
\begin{CodePiton}[options%keyvals]{tcolorbox options}#V
\end{CodePiton}

#keyvals:\begin{CodePiton}
Lignes#true,false
Gobble#true,false
Largeur=##L
TaillePolice=%<font commands%>
Alignement=#justify,left,flush left,right,flush right,center,flush center
Style=#Moderne,Classique
Filigrane#true,false
BarreTitre#true,false
Cadre#true,false
CouleurNombres=#%color
#endkeyvals

\begin{ConsolePiton}{tcolorbox options}#V
\begin{ConsolePiton}<options%keyvals>{tcolorbox options}#V
\begin{ConsolePiton}[piton options]{tcolorbox options}#V
\begin{ConsolePiton}[piton options]<options%keyvals>{tcolorbox options}#V
\end{ConsolePiton}

#keyvals:\begin{ConsolePiton}
Largeur=##L
Alignement=#justify,left,flush left,right,flush right,center,flush center
Logo#true,false
#endkeyvals

## Code & Console Python, via les packages Pythontex ou Minted ##
\begin{CodePythonMinted}{tcolorbox options}#V
\begin{CodePythonMinted}[largeur%l]{tcolorbox options}#V
\begin{CodePythonMinted}*{tcolorbox options}#V
\begin{CodePythonMinted}*[largeur%l]{tcolorbox options}#V
\end{CodePythonMinted}
\begin{CodePythonMintedAlt}{tcolorbox options}#V
\begin{CodePythonMintedAlt}[largeur%l]{tcolorbox options}#V
\begin{CodePythonMintedAlt}*{tcolorbox options}#V
\begin{CodePythonMintedAlt}*[largeur%l]{tcolorbox options}#V
\end{CodePythonMintedAlt}

## Pseudo-Code ##
\begin{PseudoCode}{tcolorbox options}#V
\begin{PseudoCode}[largeur%l]{tcolorbox options}#V
\begin{PseudoCode}*{tcolorbox options}#V
\begin{PseudoCode}*[largeur%l]{tcolorbox options}#V
\end{PseudoCode}
\begin{PseudoCodeAlt}{tcolorbox options}#V
\begin{PseudoCodeAlt}[largeur%l]{tcolorbox options}#V
\begin{PseudoCodeAlt}*{tcolorbox options}#V
\begin{PseudoCodeAlt}*[largeur%l]{tcolorbox options}#V
\end{PseudoCodeAlt}

## Terminal Windows/UNiX/OSX ##
\begin{TerminalWin}{Titre=%<texte%>}#V
\begin{TerminalWin}[%<largeur%>]{Titre=%<texte%>}[%<tcolorbox options%>]#V
\end{TerminalWin}

\begin{TerminalUnix}{Titre=%<texte%>}#V
\begin{TerminalUnix}[%<largeur%>]{Titre=%<texte%>}[%<tcolorbox options%>]#V
\end{TerminalUnix}

\begin{TerminalOSX}{Titre=%<texte%>}#V
\begin{TerminalOSX}[%<largeur%>]{Titre=%<texte%>}[%<tcolorbox options%>]#V
\end{TerminalOSX}

## Cartouche Capytale ##
\CartoucheCapytale{code capytale}
\CartoucheCapytale[prefix]{code capytale}
\CartoucheCapytale*{code capytale}
\CartoucheCapytale*[prefix]{code capytale}

## Présentation de code LaTeX ##
\begin{PresentationCode}{tcolorbox options}#V
\begin{PresentationCode}[color]{tcolorbox options}#V
\end{PresentationCode}

## Pavé droit « simple » ##
\PaveTikz
\PaveTikz[options%keyvals]

#keyvals:\PaveTikz
Largeur=%<num%>
Profondeur=%<num%>
Hauteur=%<num%>
Angle=%<degrees%>
Fuite=%<num%>
Sommets=%<A1§...§A8%>
Epaisseur=%<épaisseur%>
Aff#true,false
Plein#true,false
Cube#true,false
Math#true,false
#endkeyvals

## Tétraèdre « simple » ##
\TetraedreTikz
\TetraedreTikz[options%keyvals]

#keyvals:\TetraedreTikz
Largeur=%<num%>
Profondeur=%<num%>
Hauteur=%<num%>
Alpha=%<degrees%>
Beta=%<degrees%>
Sommets=%<A1§...§A8%>
Epaisseur=%<épaisseur%>
Aff#true,false
Plein#true,false
Math#true,false
#endkeyvals

## Cercle trigo ##
\CercleTrigo
\CercleTrigo[options%keyvals]

#keyvals:\CercleTrigo
Rayon=%<rayon%>
Epaisseur=%<épaisseur%>
Epaisseursol=%<épaisseur%>
Marge=%<marge%>
TailleValeurs=%<fontsize cmd%>
TailleAngles=%<fontsize cmd%>
CouleurFond=#%color
Decal=##L
MoinsPi#true,false
AffAngles#true,false
AffTraits#true,false
AffValeurs#true,false
Equationcos#true,false
Equationsin#true,false
cos=%<degrees%>
sin=%<degrees%>
AffTraitsEq#true,false
CouleurSol=#%color
#endkeyvals

## Paramètres d’une régression linéaire par la méthode des moindres carrés ##
\CalculsRegLin{listeX}{listeY}
\CalculsRegLin[options%keyvals]{listeX}{listeY}

#keyvals:\CalculsRegLin
NomCoeffa=%<nom%>
NomCoeffb=%<nom%>
NomCoeffr=%<nom%>
NomCoeffrd=%<nom%>
NomXmin=%<nom%>
NomXmax=%<nom%>
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

\PointsRegLin{listeX}{listeY}
\PointsRegLin[options%keyvals]{listeX}{listeY}

#keyvals:\PointsRegLin
Couleur=#%color
Taille=##L
Ox=%<num%>
Oy=%<num%>
#endkeyvals

## Statistiques à deux variables ##
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

\GrilleTikz
\GrilleTikz[options%keyvals]
\GrilleTikz[options%keyvals][options grille ppale]#*
\GrilleTikz[options%keyvals][options grille ppale][options grille second]

#keyvals:\GrilleTikz
Affp#true,false
Affs#true,false
#endkeyvals

\AxesTikz
\AxesTikz[options%keyvals]

#keyvals:\AxesTikz
Epaisseur=##L
Police=%<font commands%>
ElargirOx=%<num%>
ElargirOy=%<num%>
Labelx=%<text%>
Labely=%<text%>
AffLabel=#x,y,xy
PosLabelx=%<TikZ pos%>
PosLabely=%<TikZ pos%>
EchelleFleche=%<num%>
TypeFleche=%<type%>
#endkeyvals

\AxexTikz{valeurs}
\AxexTikz[options%keyvals]{valeurs}
\AxeyTikz{valeurs}
\AxeyTikz[options%keyvals]{valeurs}

#keyvals:\AxexTikz,\AxeyTikz
Epaisseur=##L
Police=%<font commands%>
PosGrad=%<TikZ pos%>
HautGrad=##L
AffGrad#true,false
AffOrigine#true,false
Annee#true,false
Trigo#true,false
Dfrac#true,false
Frac#true,false
#endkeyvals

\AffAngleRadian{expr}
\AffAngleRadian*{expr}

\FenetreTikz
\FenetreSimpleTikz{liste valx}{liste valy}
\FenetreSimpleTikz<opt axe Ox>{liste valx}<opt axe Oy>{liste valy}
\FenetreSimpleTikz(opt axes)<opt axe Ox>{liste valx}<opt axe Oy>{liste valy}
\FenetreSimpleTikz[opt](opt axes)<opt axe Ox>{liste valx}<opt axe Oy>{liste valy}

\OrigineTikz#*
\OrigineTikz[options%keyvals]#*

#keyvals:\OrigineTikz
Police=%<font commands%>
Pos=%<TikZ pos%>
Decal=##L
Valeur=%<num%>
#endkeyvals

\NuagePointsTikz{listeX}{listeY}
\NuagePointsTikz[options%keyvals]{listeX}{listeY}

#keyvals:\NuagePointsTikz
Taille=##L
Style=#o,x,+
Couleur=#%color
#endkeyvals

\PointMoyenTikz
\PointMoyenTikz[options%keyvals]

#keyvals:\PointMoyenTikz
Police=%<font commands%>
Taille=##L
Couleur=#%color
Style=#o,x,+
xg=%<num%>
yg=%<num%>
Nom=%<text%>
Pos=%<TikZ pos%>
Decal=##L
AffNom#true,false
#endkeyvals

\CourbeTikz{formule}{domaine}
\CourbeTikz[TikZ clés]{formule}{domaine}

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

## L’outil « SplineTikz » ##
\SplineTikz{x1/y1/d1§x2/y2/d2§...}
\SplineTikz[options%keyvals]{x1/y1/d1§x2/y2/d2§...}

#keyvals:\SplineTikz
Couleur=#%color
Epaisseur=##L
Style={%<TikZ clés%>}
Coeffs=
CouleurPoints=#%color
AffPoints#true,false
TaillePoints=##L
#endkeyvals

## L’outil « TangenteTikz » ##
\TangenteTikz{x1/y1/d1§x2/y2/d2§...}
\TangenteTikz[options%keyvals]{x1/y1/d1§x2/y2/d2§...}

#keyvals:\TangenteTikz
Point=%<num%>
Epaisseur=##L
Couleur=#%color
Style={%<TikZ clés%>}
xl=%<num%>
xr=%<num%>
#endkeyvals

## Boîtes à moustaches ##
\BoiteMoustaches{a1/a2/...}
\BoiteMoustaches[options%keyvals]{a1/a2/...}

#keyvals:\BoiteMoustaches
Couleur=#%color
Elevation=%<nombre%>
Hauteur=%<nombre%>
Moyenne=%<nombre%>
Epaisseur=%<épaisseur%>
Remplir=#%color
AffMoyenne#true,false
Pointilles#true,false
Valeurs#true,false
#endkeyvals

\BoiteMoustachesAxe[options%keyvals]

#keyvals:\BoiteMoustachesAxe
Min=%<nombre%>
Max=%<nombre%>
Elargir=%<pourcentage%>
Epaisseur=%<épaisseur%>
Valeurs={%<liste%>}
AffValeurs#true,false
#endkeyvals

## Histogrammes ##
\Histogramme{données}
\Histogramme[options%keyvals]{données}
\Histogramme*{données}
\Histogramme*[options%keyvals]{données}

#keyvals:\Histogramme,\Histogramme*
DebutOx=%<nombre%>
FinOx=%<nombre%>
Largeur=%<nombre%>
Hauteur=%<nombre%>
ListeCouleurs={%<couleur1,couleur2,...%>}
ElargirX=##L
ElargirY=##L
LabelX=%<texte%>
LabelY=%<texte%>
GradX={%<graduations%>}
GradY={%<graduations%>}
AffEffectifs#true,false
PosEffectifs=#bas,milieu,haut,dessus
Remplir#true,false
Opacite=%<factor%>
AffBornes#true,false
GrilleV#true,false
PoliceAxes=%<font commands%>
PoliceEffectifs=%<font commands%>
EpaisseurTraits=%<épaisseur%>
Grille=%<GradX%>/%<UniteAire%>
ExtraGrilleY=%<nombre%>
PosLegende=
#endkeyvals

## Calculs de probabilités ##
\CalcBinomP{n}{p}{k}
\CalcBinomC{n}{p}{a}{b}
\CalcPoissP{l}{k}
\CalcPoissC{l}{a}{b}
\CalcGeomP{p}{k}
\CalcGeomC{l}{a}{b}
\CalcHypergeomP{N}{n}{m}{k}
\CalcHypergeomC{N}{n}{m}{a}{b}
\CalcNormC{m}{s}{a}{b}
\CalcExpoC{l}{a}{b}

\BinomP{n}{p}{k}
\BinomP[prec]{n}{p}{k}
\BinomP*{n}{p}{k}
\BinomP*[prec]{n}{p}{k}
\BinomC{n}{p}{a}{b}
\BinomC[prec]{n}{p}{a}{b}
\BinomC*{n}{p}{a}{b}
\BinomC*[prec]{n}{p}{a}{b}
\PoissonP{l}{k}
\PoissonP[prec]{l}{k}
\PoissonP*{l}{k}
\PoissonP*[prec]{l}{k}
\PoissonC{l}{a}{b}
\PoissonC[prec]{l}{a}{b}
\PoissonC*{l}{a}{b}
\PoissonC*[prec]{l}{a}{b}
\GeomP{p}{k}
\GeomP[prec]{p}{k}
\GeomP*{p}{k}
\GeomP*[prec]{p}{k}
\GeomC{l}{a}{b}
\GeomC[prec]{l}{a}{b}
\GeomC*{l}{a}{b}
\GeomC*[prec]{l}{a}{b}
\HypergeomP{N}{n}{m}{k}
\HypergeomP[prec]{N}{n}{m}{k}
\HypergeomP*{N}{n}{m}{k}
\HypergeomP*[prec]{N}{n}{m}{k}
\HypergeomC{N}{n}{m}{a}{b}
\HypergeomC[prec]{N}{n}{m}{a}{b}
\HypergeomC*{N}{n}{m}{a}{b}
\HypergeomC*[prec]{N}{n}{m}{a}{b}
\NormaleC{m}{s}{a}{b}
\NormaleC[prec]{m}{s}{a}{b}
\NormaleC*{m}{s}{a}{b}
\NormaleC*[prec]{m}{s}{a}{b}
\ExpoC{l}{a}{b}
\ExpoC[prec]{l}{a}{b}
\ExpoC*{l}{a}{b}
\ExpoC*[prec]{l}{a}{b}

## Arbres de probabilités « classiques » ##
\ArbreProbasTikz{donnees}
\ArbreProbasTikz[options%keyvals]{donnees}
\begin{EnvArbreProbasTikz}{donnees}
\begin{EnvArbreProbasTikz}[options%keyvals]{donnees}
\end{EnvArbreProbasTikz}

#keyvals:\ArbreProbasTikz,\begin{EnvArbreProbasTikz}
Unite=##L
EspaceNiveau=%<nombre%>
EspaceFeuille=%<nombre%>
Type=#2x2,2x3,3x2,3x3
Police=%<font commands%>
PoliceProbas=%<font commands%>
InclineProbas#true,false
Fleche#true,false
StyleTrait={%<TikZ keys%>}
EpaisseurTrait=%<épaisseur%>
#endkeyvals

## Petits schémas pour des probabilités continues ##
\LoiNormaleGraphe{m}{s}{a}{b}
\LoiNormaleGraphe<TikZ options>{m}{s}{a}{b}
\LoiNormaleGraphe[options%keyvals]{m}{s}{a}{b}
\LoiNormaleGraphe[options%keyvals]<TikZ options>{m}{s}{a}{b}
\LoiExpoGraphe{l}{a}{b}
\LoiExpoGraphe<TikZ options>{l}{a}{b}
\LoiExpoGraphe[options%keyvals]{l}{a}{b}
\LoiExpoGraphe[options%keyvals]<TikZ options>{l}{a}{b}

#keyvals:\LoiNormaleGraphe,\LoiExpoGraphe
CouleurAire=#%color
CouleurCourbe=#%color
Largeur=%<nombre%>
Hauteur=%<nombre%>
AfficheM#true,false
AfficheCadre#true,false
#endkeyvals

## Nombres aléatoires ##
\NbAlea{a}{b}{macro%cmd}#d
\NbAlea[n]{a}{b}{macro%cmd}#d
\VarNbAlea{macro%cmd}{calculs}#d

\TirageAleatoireEntiers{macro%cmd}#d
\TirageAleatoireEntiers[options%keyvals]{macro%cmd}#d

#keyvals:\TirageAleatoireEntiers
ValMin=%<nombre%>
ValMax=%<nombre%>
NbVal=%<nombre%>
Sep=%<séparateur%>
Tri=#non,croissant,decroissant
Repetition#true,false
#endkeyvals

## Combinatoire ##
\Arrangement{p}{n}
\Arrangement[option%keyvals]{p}{n}
\Arrangement*{p}{n}
\Arrangement*[option%keyvals]{p}{n}
\Combinaison{p}{n}
\Combinaison[option%keyvals]{p}{n}
\Combinaison*{p}{n}
\Combinaison*[option%keyvals]{p}{n}
\CalculAnp{p}{n}
\CalculCnp{p}{n}

#keyvals:\Arrangement,\Arrangement*,\Combinaison,\Combinaison*
Notation#true,false
NotationAncien#true,false
Formule#true,false
#endkeyvals

## Fonction de répartition ##
\FonctionRepartTikz{liste des probas,borneinf,bornesup}
\FonctionRepartTikz[option%keyvals]{liste des probas,borneinf,bornesup}

#keyvals:\FonctionRepartTikz
Couleur=#%color
Epaisseur=%<épaisseur%>
Pointilles#true,false
Extremite=#crochet,point
#endkeyvals

## Conversions binaire/hexadécimal/décimal ##
\ConversionDecBin{nombre}
\ConversionDecBin[options%keyvals]{nombre}
\ConversionDecBin*{nombre}
\ConversionDecBin*[options%keyvals]{nombre}

#keyvals:\ConversionDecBin,\ConversionDecBin*
AffBase#true,false
#endkeyvals

\ConversionBinHex{nombre}
\ConversionBinHex[options%keyvals]{nombre}

#keyvals:\ConversionBinHex
AffBase#true,false
Details#true,false
#endkeyvals

\ConversionVersDec{nombre}
\ConversionVersDec[options%keyvals]{nombre}
\ConversionBaseDix{nombre}{base de départ}
\ConversionBaseDix[options%keyvals]{nombre}{base de départ}

#keyvals:\ConversionVersDec,\ConversionBaseDix
BaseDep=%<2 ou 16%>
AffBase#true,false
Details#true,false
Zeros#true,false
#endkeyvals

## Conversion « présentée » d’un nombre en décimal ##
\ConversionDepuisBaseDix{nombre en base 10}{base d'arrivée}
\ConversionDepuisBaseDix[options%keyvals]{nombre en base 10}{base d'arrivée}

#keyvals:\ConversionDepuisBaseDix
Couleur=#%color
DecalH=##L
DecalV=##L
Noeud=%<préfixe%>
Rect#true,false
CouleurRes#true,false
#endkeyvals

## Algorithme d’Euclide pour le PGCD ##
\PresentationPGCD{a}{b}
\PresentationPGCD[options%keyvals]{a}{b}

#keyvals:\PresentationPGCD
Couleur=#%color
DecalRect=##L
Rectangle#true,false
Noeud=%<nom du nœud%>
CouleurResultat#true,false
AfficheConclusion#true,false
AfficheDelimiteurs#true,false
#endkeyvals

## Résolution d’une équation diophantienne ##
\EquationDiophantienne{equation}
\EquationDiophantienne[options%keyvals]{equation}

#keyvals:\EquationDiophantienne
Lettre=%<nom%>
Inconnues=%<x/y%>
Entier=%<nom%>
Cadres#true,false
PresPGCD#true,false
#endkeyvals

## Fractions, ensembles ##
\ConversionFraction{calcul}
\ConversionFraction[option de formatage%keyvals]{calcul}
\ConversionFraction*{calcul}
\ConversionFraction*[option de formatage%keyvals]{calcul}

#keyvals:\ConversionFraction,\ConversionFraction*
t
d
n
dec
dec=%<k%>
#endkeyvals

\EcritureEnsemble{a1/a2/...}
\EcritureEnsemble[options%keyvals]{a1/a2/...}

#keyvals:\EcritureEnsemble
Sep={%<separator%>}
Option={%<code%>}
Mathpunct#true,false
#endkeyvals

## Petits schémas pour le signe d’une fonction affine ou d’un trinôme ##
\MiniSchemaSignes
\MiniSchemaSignes<TikZ options>#*
\MiniSchemaSignes[options%keyvals]#*
\MiniSchemaSignes[options%keyvals]<TikZ options>
\MiniSchemaSignes*
\MiniSchemaSignes*<TikZ options>#*
\MiniSchemaSignes*[options%keyvals]#*
\MiniSchemaSignes*[options%keyvals]<TikZ options>

\MiniSchemaSignesTkzTab{numligne}
\MiniSchemaSignesTkzTab{numligne}[echelle]
\MiniSchemaSignesTkzTab{numligne}[echelle][décalage horizontal]
\MiniSchemaSignesTkzTab[options%keyvals]{numligne}
\MiniSchemaSignesTkzTab[options%keyvals]{numligne}[echelle]
\MiniSchemaSignesTkzTab[options%keyvals]{numligne}[echelle][décalage horizontal]

#keyvals:\MiniSchemaSignes,\MiniSchemaSignes*,\MiniSchemaSignesTkzTab
Code=
Couleur=#%color
Racines=%<racines%>
Largeur=%<num%>
Hauteur=%<num%>
Cadre#true,false
#endkeyvals

## Suites récurrentes et « toile » ##
\ToileRecurrence[options%keyvals]
\ToileRecurrence[options%keyvals][options du tracé]
\ToileRecurrence[options%keyvals][options du tracé][option supplémentaire des termes]

#keyvals:\ToileRecurrence
Fct=%<fonction%>
Nom=%<nom%>
No=%<l’indice initial%>
Uno=%<la valeur du terme initial%>
Nb=%<nombre%>
PosLabel=%<pos%>
DecalLabel=##L
TailleLabel=%<fontsize cmd%>
AffTermes#true,false
#endkeyvals

## Méthodes graphiques et intégrales ##
\DeclareFonctionTikz{expr}
\DeclareFonctionTikz[nom]{expr}

\IntegraleApprocheeTikz{nom fonction}{a}{b}
\IntegraleApprocheeTikz[options%keyvals]{nom fonction}{a}{b}

#keyvals:\IntegraleApprocheeTikz
Epaisseur=%<épaisseur%>
Couleur=#%color
Remplir#true,false
Opacite=%<factor%>
CouleurRemplissage=#%color
Methode=#RectanglesGauche,RectanglesDroite,RectanglesMilieu,Trapezes
NbSubDiv=%<nombre%>
#endkeyvals

## Affichage de coordonnées ##
\AffPoint(liste de coordonnées)
\AffPoint[options](liste de coordonnées)
\AffVecteur(liste de coordonnées)
\AffVecteur<options nicematrix>(liste de coordonnées)
\AffVecteur[options](liste de coordonnées)
\AffVecteur[options]<options nicematrix>(liste de coordonnées)

## Équation cartésienne d’un plan de l’espace ##
\TrouveEqCartPlan(vecteur normal)(point)
\TrouveEqCartPlan(vecteur dir1)(vecteur dir2)(point)
\TrouveEqCartPlan[options%keyvals](vecteur normal)(point)
\TrouveEqCartPlan[options%keyvals](vecteur dir1)(vecteur dir2)(point)

#keyvals:\TrouveEqCartPlan
OptionCoeffs=%<option%>
SimplifCoeffs#true,false
Facteur=%<facteur%>
#endkeyvals

## Équation paramétrique d’une droite de l’espace ##
\TrouveEqParamDroite(vecteur directeur)(point)
\TrouveEqParamDroite[options%keyvals](vecteur directeur)(point)

#keyvals:\TrouveEqParamDroite
OptionCoeffs=%<option%>
Reel=%<symbole%>
Oppose#true,false
Rgras#true,false
#endkeyvals

## Équation cartésienne d’une droite du plan ##
\TrouveEqCartDroite(vecteur)(point)
\TrouveEqCartDroite[options%keyvals](vecteur)(point)

#keyvals:\TrouveEqCartDroite
OptionCoeffs=%<option%>
SimplifCoeffs#true,false
Facteur=%<facteur%>
VectDirecteur#true,false
#endkeyvals

## Norme d’un vecteur, distance entre deux points ##
\TrouveNorme(vecteur)
\TrouveNorme(point1)(point2)

## Distance d’un point à un plan ##
\TrouveDistancePtPlan(point)(vec normal du plan)(point du plan)
\TrouveDistancePtPlan(point)(équation cartésienne)

## Écriture d’un trinôme, trinôme aléatoire ##
\EcritureTrinome{a}{b}{c}
\EcritureTrinome[options%keyvals]{a}{b}{c}

#keyvals:\EcritureTrinome
Alea#true,false
Anegatif#true,false
#endkeyvals

## Simplification de racines ##
\SimplificationRacine{expression ou calcul}

## Mesure principale d’un angle ##
\MesurePrincipale{angle}
\MesurePrincipale[options%keyvals]{angle}

#keyvals:\MesurePrincipale
d#true,false
Crochets#true,false
Brut#true,false
#endkeyvals

## Lignes trigonométriques ##
\LigneTrigo{cos|sin|tan}(angle)
\LigneTrigo[options%keyvals]{cos|sin|tan}(angle)
\LigneTrigo*{cos|sin|tan}(angle)
\LigneTrigo*[options%keyvals]{cos|sin|tan}(angle)

#keyvals:\LigneTrigo,\LigneTrigo*
d#true,false
Etapes#true,false
#endkeyvals

## SudoMaths, en TikZ ##
\SudoMaths{liste}
\SudoMaths[options%keyvals]{liste}

\begin{EnvSudoMaths}{grille}
\begin{EnvSudoMaths}[options%keyvals]{grille}
\end{EnvSudoMaths}

#keyvals:\SudoMaths,\begin{EnvSudoMaths}
Epaisseurg=##L
Epaisseur=##L
Unite=##L
CouleurCase=#%color
CouleurTexte=#%color
NbCol=%<nombre%>
NbSubCol=%<nombre%>
NbLig=%<nombre%>
NbSubLig=%<nombre%>
Police=%<font commands%>
Legendes#true,false
PoliceLeg=%<font commands%>
ListeLegV=%<liste%>
ListeLegH=%<liste%>
DecalLegende=%<décalage%>
#endkeyvals

## pythontex library ##
# conditional loading not possible, just listed here
#include:pythontex
\begin{CodePythontex}{}#V
\begin{CodePythontex}[options%keyvals]{}#V
\end{CodePythontex}
\begin{CodePythontexAlt}{}#V
\begin{CodePythontexAlt}[options%keyvals]{}#V
\end{CodePythontexAlt}
#keyvals:\begin{CodePythontex},\begin{CodePythontexAlt}
Largeur=##L
Centre#true,false
TaillePolice=%<font commands%>
EspacementVertical=%<factor%>
Lignes#true,false
#endkeyvals
\begin{ConsolePythontex}{}#V
\begin{ConsolePythontex}[options%keyvals]{}#V
\end{ConsolePythontex}
#keyvals:\begin{ConsolePythontex}
Largeur=##L
Centre#true,false
TaillePolice=%<font commands%>
EspacementVertical=%<factor%>
Label#true,false
#endkeyvals
\begin{pythont}#S
\begin{tcpythontexcode}{arg}#S
\begin{tcpythontexcode}[width]{arg}#S
\begin{tcpythontexcodeno}{arg}#S
\begin{tcpythontexcodeno}[width]{arg}#S
\CODPYfonte#S
\CODPYlargeur#S
\CODPYstretch#S
\CSPYfonte#S
\CSPYlargeur#S
\CSPYstretch#S
\end{pythont}#S
\end{tcpythontexcode}#S
\end{tcpythontexcodeno}#S
\hookcenterpost#S
\hookcenterpre#S
\begin{tcpythontexcodealt}{arg}#S
\begin{tcpythontexcodealt}[width]{arg}#S
\end{tcpythontexcodealt}#S
\begin{tcpythontexcodenoalt}{arg}#S
\begin{tcpythontexcodenoalt}[width]{arg}#S
\end{tcpythontexcodenoalt}#S

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

PLlinux#B
PLmgray#B
PLmpurple#B
PLogray#B
PLoorange#B
PLosxgray#B
PLterminal#B
PLwinblue#B
vertcapyt#B

# not documented
\AleaSigneA#S
\algomathttPL{text%plain}#S
\axesafflabel#S
\axesechellefleche#S
\axeselargx#S
\axeselargy#S
\axesenlargxD#S
\axesenlargxG#S
\axesenlargyD#S
\axesenlargyG#S
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
\BaMAxeElarg#S
\BaMAxeEpaisseur#S
\BaMaxelargeur#S
\BaMAxeMax#S
\BaMAxeMin#S
\BaMAxeValeurs#S
\BaMaxexmax#S
\BaMaxexmin#S
\BaMCouleur#S
\BaMElevation#S
\BaMEpaisseur#S
\BaMHauteur#S
\BaMListeparams#S
\BaMmax#S
\BaMmed#S
\BaMmin#S
\BaMMoyenne#S
\BaMqt#S
\BaMqu#S
\BaMRemplissage#S
\basedepart#S
\BorneInf#S
\BorneSup#S
\calculargument#S
\CalculInterneTermeRecurrence{arg1}{arg2}{arg3}{arg4}#S
\CalculSeuil{arg1}{arg2}{arg3}{arg4}{arg5}#S
\CFcoulcmd#S
\CFcouleur#S
\CFcoulres#S
\CFesplg#S
\CFhle#S
\CFhlr#S
\CFL#S
\CFLA#S
\CFlabeltitre#S
\CFlarg#S
\CFposcmd#S
\CFposres#S
\CFtaille#S
\CFtailletitre#S
\chbrut#S
\chiffre#S
\CODPITalign#S
\CODPITcolnb#S
\CODPITespV#S
\CODPITfonte#S
\CODPITlargeur#S
\CODPITstyle#S
\CODPITtitre#S
\COEFF#S
\COEFFA#S
\Coeffa#S
\COEFFB#S
\Coeffc#S
\ConsPyluaAlign#S
\ConsPyluaLarg#S
\convertbasedixtobase{arg1}{arg2}#S
\convertbasetobasedix{arg1}{arg2}#S
\cpt#S
\denominateur#S
\densexpo{arg}#S
\densnorm{arg}#S
\DHTnomfct#S
\DHTnomsol#S
\DHTprec#S
\DHTstretch#S
\DHTva#S
\DHTvb#S
\DICHOTOinterv#S
\DICHOTOstep#S
\DICHOTOvar#S
\extractcoeff{liste}{numero}#S
\fctdecx#S
\fprimea#S
\fprimeb#S
\GRPHPROBcoulcbe#S
\GRPHPROBcoulsurf#S
\GRPHPROBhauteur#S
\GRPHPROBlarg#S
\ifinal#S
\iinit#S
\indice#S
\IntSimplifMesPpale{arg}#S
\larcolinter#S
\larliginter#S
\LCNA#S
\lcoeffs#S
\LCPA#S
\listepointsaffiches#S
\MOYENNE#S
\nbblocs#S
\nbchiffres#S
\nbdepart#S
\NBdepart#S
\nbgrp#S
\numerateur#S
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
\PLAPeptrait#S
\PLAPespfeuille#S
\PLAPespniv#S
\PLAPfont#S
\PLAPfontproba#S
\PLAPtype#S
\PLAPtypetrait#S
\PLAPunite#S
\PLARBREDONNES#S
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
\PLcommandeswin#S
\PLConvCouleur#S
\PLConvDecalH#S
\PLConvDecalV#S
\PLConvNoeud#S
\PLDm#S
\PLDM#S
\PLdomaine#S
\PLensopt#S
\PLenssep#S
\PLnoeud{arg1}{arg2}#S
\PLnuagepoints[opt]{arg}#S
\PLnuagepoints{arg}#S
\PLOSXGreen#S
\PLOSXLG#S
\PLOSXOrange#S
\PLOSXRed#S
\PLpgcd#S
\PLPGCDCouleur#S
\PLPGCDDecal#S
\PLPGCDNoeud#S
\PLRecurfct#S
\PLRecurlabelsize#S
\PLRecurnb#S
\PLRecurno#S
\PLRecurnom#S
\PLRecuroffset#S
\PLRecurposlab#S
\PLRecuruno#S
\PLSMcoulcase#S
\PLSMcoultexte#S
\PLSMdecalleg#S
\PLSMepf#S
\PLSMepg#S
\PLSMfonte#S
\PLSMfonteleg#S
\PLSMlistelegh#S
\PLSMlistelegv#S
\PLSMnbcol#S
\PLSMnblig#S
\PLSMnbsubcol#S
\PLSMnbsublig#S
\PLSMunite#S
\PLstrzeros{nombre}#S
\PLUbuntuClose#S
\PLUbuntuMax#S
\PLUbuntuMin#S
\PLUbuntuWhite#S
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
\respgcd#S
\schematdsaff*{arg1}{arg2}{arg3}{arg4}#S
\schematdsaff{arg1}{arg2}{arg3}{arg4}#S
\schematdsparab{arg1}{arg2}{arg3}{arg4}{arg5}#S
\schematdsparab{arg1}{arg2}{arg3}{arg4}{arg5}[opt]#S
\SensDeb#S
\SEUILindiceinit#S
\SEUILn#S
\SEUILnmu#S
\SEUILnomsuite#S
\SEUILprec#S
\SEUILsens#S
\SEUILstretch#S
\SEUILtermeinit#S
\SMcase#S
\SMcaseb#S
\SPGrilleSudoMaths#S
\SPLcoeffs#S
\SPLcouleur#S
\SPLcouleurpoints#S
\SPLepaisseur#S
\SPLlistepoints#S
\SPLlistepointslen#S
\SPLnbsplines#S
\SPLstyle#S
\SPLtaillepoints#S
\SRnfinal#S
\SRninit#S
\SRprec#S
\SRuninit#S
\TAEEmax#S
\TAEEmin#S
\TAEEnb#S
\TAEEsep#S
\TAEEtri#S
\tdscouleur#S
\tdshaut#S
\tdslarg#S
\tdsparam#S
\tdsracine#S
\termnuxtitre#S
\termnuxtitre[opt]#S
\termosxtitre#S
\termosxtitre[opt]#S
\termwintitre#S
\termwintitre[opt]#S
\TetraA#S
\TetraB#S
\TetraC#S
\TetraD#S
\TGTcouleur#S
\TGTDEB#S
\TGTepaisseur#S
\TGTFIN#S
\TGTlistepoints#S
\TGTnumpt#S
\TGTstyle#S
\TGTXL#S
\TGTXR#S
\theCFnum#S
\TriListeCroiss{arg}#S
\TriListeDecroiss{arg}#S
\TriPartieA#S
\TriPartieB#S
\TriPartieC#S
\TriSigneA#S
\UNITEX#S
\UNITEY#S
\ValA#S
\ValA#S
\ValB#S
\ValB#S
\ValMU#S
\ValQ#S
\ValQ#S
\ValR#S
\ValR#S
\ValRes#S
\ValTMP#S
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
\MethIntegrPrec#S
\MethIntegrNb#S
\MethIntegrType#S
\MethIntegrEqual#S
\MethIntegrFct#S
\MethIntegrVar#S
\MethIntegrTkzCol#S
\MethIntegrTkzColOpak#S
\MethIntegrTkzNb#S
\MethIntegrTkzType#S
\MethIntegrTkzOpak#S
\MethIntegrTkzThick#S
\AffCoeffFAm{arg}#S
\AffCoeffFAm[opt]{arg}#S
\AffCoeffFAp{arg}#S
\AffCoeffFAp[opt]{arg}#S
\AffCoeffFloatPa{arg}#S
\AffCoeffFloatPa[opt]{arg}#S
\AffCoeffFloat{arg}#S
\AffCoeffFloat[opt]{arg}#S
\AffCoeffPa{arg}#S
\AffCoeffPa[opt]{arg}#S
\AffCoeffSgn{arg1}{arg2}#S
\AffCoeffSgn[opt]{arg1}{arg2}#S
\AffCoeffSgn*{arg1}{arg2}#S
\AffCoeffSgn*[opt]{arg1}{arg2}#S
\AffCoeffSgnSimpl{arg}#S
\AffCoeffSgnSimpl[opt]{arg}#S
\AffCoeffSgnSimpl*{arg}#S
\AffCoeffSgnSimpl*[opt]{arg}#S
\eqcartplformat#S
\eqcartplfact#S
\eqcartdteformat#S
\eqcartdtefact#S
\eqparamdteformat#S
\eqparamdtereel#S
\AffVarDteParam{arg1}{arg2}#S
\AffVarDteParamAlign{arg1}{arg2}#S
\AffCoeffBezout{arg}#S
\EgaliteBezout{arg1}{arg2}#S
\EgaliteBezout[opt]{arg1}{arg2}#S
\AffCoeffDioph{arg}#S
\AffCoeffDiophSign{arg}#S
\LettreSolEDioph#S
\CouleurSolEDioph#S
\InconnuesSolEDioph#S
\TrouveEqCartPlanAux#S
\TrouveEqCartDroiteAux#S
\AffVecteurAux#S
\TrouveEqParamDroiteAux#S
\TrouveDistancePtPlanAux#S
\TrouveNormeAux#S
\HistoCouleurs#S
\HistoLargeur#S
\HistoHauteur#S
\HistoGradX#S
\HistoGradY#S
\HistoPosEff#S
\HistoLabelx#S
\HistoLabely#S
\HistoElargirx#S
\HistoElargiry#S
\HistoFonte#S
\HistoFonteEff#S
\HistoOpac#S
\HistoDebX#S
\HistoFinX#S
\HistoEptraits#S
\HistogrammeTikz{arg}#S
\HistogrammeTikz[opt]{arg}#S
\CrochetFctRepart{arg1}{arg2}#S
\FctRepartColor#S
\FctRepartThickness#S
\FctRepartExtremite#S
\HistoGrille#S
\HistoExtraGridY#S
\HistoPosLeg#S
