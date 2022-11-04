# ProfCollege package
# Matthew Bertucci 2022/11/04 for v0.99-z-b

#include:verbatim
#include:mathtools
#include:amssymb
#include:siunitx
#include:xcolor
# xcolor loaded with table and svgnames options
#include:xstring
#include:simplekv
#include:ifthen
#include:modulus
#include:xinttools
#include:iftex
#include:luamplib
#include:gmp
#include:xintexpr
#include:listofitems
#include:datatool
#include:multido
#include:xlop
#include:xfp
#include:tcolorbox
# tcolorbox loaded with most option
#include:tikz
# loads calc, shapes, arrows, tikzmark, chains, positioning, shapes.symbols, babel, and fit tikzlibraries
#include:suffix
#include:multicol
#include:hhline
#include:stackengine
#include:cancel
#include:fontawesome5
#include:pifont
#include:nicematrix
#include:fmtcount
#include:environ
#include:longtable
#include:printlen
#include:ifoddpage

#keyvals:\usepackage/ProfCollege#c
nonshellescape
#endkeyvals

## L'écriture de grandeurs ##
\Lg{nombre}
\Lg[unité]{nombre}
\Aire{nombre}
\Aire[unité]{nombre}
\Vol{nombre}
\Vol[unité]{nombre}
\Masse{nombre}
\Masse[unité]{nombre}
\Capa{nombre}
\Capa[unité]{nombre}
\Temps{nombre}
\Temps[unité]{nombre}
\MasseVol{nombre}
\MasseVol[unité]{nombre}
\Vitesse{nombre}
\Vitesse[unité]{nombre}
\Octet{nombre}
\Octet[unité]{nombre}
\Conso{nombre}
\Conso[unité]{nombre}
\Prix{nombre}
\Prix[unité]{nombre}
\Temp{nombre}
\Temp[unité]{nombre}

## Représenter graphiquement un nombre entier ##
\RepresenterEntier{nombre}
\RepresenterEntier[clés%keyvals]{nombre}

#keyvals:\RepresenterEntier
Echelle=%<factor%>
ListeCouleurs={%<color1,color2,...%>}
Impression#true,false
Compact#true,false
Unite#true,false
#endkeyvals

## Écrire les nombres en lettres ##
\Ecriture{nombre}
\Ecriture[clés%keyvals]{nombre}

#keyvals:\Ecriture
Majuscule#true,false
Tradition#true,false
Math#true,false
E#true,false
Zero#true,false
#endkeyvals

## La frise temporelle ##
\Frise{1/A/a,2/B/b,3/C/c,...}
\Frise[clés%keyvals]{1/A/a,2/B/b,3/C/c,...}

#keyvals:\Frise
Longueur=##L
Fleches#true,false
Ecart=##L
Sup#true,false
#endkeyvals

## Les tables de multiplication et d'addition ##
\Tables{nombre}
\Tables[clés%keyvals]{nombre}

#keyvals:\Tables
Couleur=#%color
Debut=%<nombre%>
Fin=%<nombre%>
Seul#true,false
Addition#true,false
#endkeyvals

## Différents types de papiers ##
\Papiers
\Papiers[clés%keyvals]

#keyvals:\Papiers
Largeur=%<integer%>
Hauteur=%<integer%>
Couleur=#%color
Seyes#true,false
Millimetre#true,false
Isometrique#true,false
IsometriquePointe#true,false
Triangle#true,false
Grille=%<nombre%>
GrillePointe=%<nombre%>
PageEntiere#true,false
ZoneTexte#true,false
#endkeyvals

## Les tableaux de conversion et tableaux de numération ##
\Tableau{liste de nombres}
\Tableau[clés%keyvals]{liste de nombres}

#keyvals:\Tableau
Metre#true,false
FlechesH#true,false
FlechesB#true,false
Fleches#true,false
NbLignes=%<integer%>
Carre#true,false
Colonnes#true,false
Are#true,false
Cube#true,false
Capacite#true,false
Gramme#true,false
Litre#true,false
Escalier#true,false
Entiers#true,false
Millions#true,false
Milliards#true,false
Classes#true,false
CouleurG=#%color
CouleurM=#%color
Couleurm=#%color
Couleuru=#%color
Nombres#true,false
Puissances#true,false
FlechesB#true,false
FlechesH#true,false
Decimaux#true,false
Partie#true,false
Virgule#true,false
Prefixes#true,false
Micro#true,false
Nano#true,false
Incline#true,false
Couleurd=#%color
PuissancesSeules#true,false
Colonne=%<integer%>
Taille=%<nombre%>
Largeur=##L
Nom=%<nom%>
CodeAfter=%<code%>
#endkeyvals

## Questions - réponses à relier ##
\Relie{Liste des éléments par ligne}
\Relie[clés%keyvals]{Liste des éléments par ligne}

#keyvals:\Relie
Solution#true,false
LargeurG=##L
LargeurD=##L
Ecart=##L
Stretch=%<factor%>
Couleur=#%color
#endkeyvals

## Les questionnaires à choix multiples ##
\QCM{questions%text}
\QCM[clés%keyvals]{questions%text}

#keyvals:\QCM
Stretch=%<factor%>
Reponses#true,false
Largeur=##L
Titre#true,false
Nom=%<nom%>
AlphT#true,false
Alph#true,false
Alterne#true,false
Depart=%<nombre%>
Solution#true,false
Couleur=#%color
VF#true,false
NomV=%<nom%>
NomF=%<nom%>
Multiple
Noms=%<nom1/nom2/...%>
#endkeyvals

## Les questions « flash » ##
\QFlash{question/param1/param2/...%text}
\QFlash[clés%keyvals]{question/param1/param2/...%text}

#keyvals:\QFlash
Simple#true,false
Kahout#true,false
Pause#true,false
Hauteur=##L
Couleur1=#%color
Couleur2=#%color
Couleur3=#%color
Couleur4=#%color
Intrus#true,false
Numeration#true,false
Decimal#true,false
Operation=#Multiplie,Divide
Mental#true,false
Expression#true,false
Mesure#true,false
Heure#true,false
Numerique#true,false
Daily#true,false
Seul#true,false
Evaluation#true,false
#endkeyvals

\BoiteFlash{contenu%text}
\BoiteFlash[length]{contenu%text}

## Rapido ##
\Rapido{q1/r1§q2/r2§...%text}
\Rapido[clés%keyvals]{q1/r1§q2/r2§...%text}

#keyvals:\Rapido
Largeur=##L
Numero=%<numero%>
#endkeyvals

\BoiteRapido{texte%text}

## Mentalo ##
\Mentalo{o1,o2,...}
\Mentalo[clés%keyvals]{o1,o2,...}

#keyvals:\Mentalo
Questions=%<nombre%>
ValeurMin=%<nombre%>
ValeurMax=%<nombre%>
#endkeyvals

## Le calcul mental ##
\CourseNombre{file}#i
\CourseNombre[clés%keyvals]{file}#i

#keyvals:\CourseNombre
CoefQ=%<nombre%>
CoefR=%<nombre%>
CoefJ=%<nombre%>
Dossier=%<dossier%>
Liste={%<liste de répertoires%>}
Maitre#true,false
Debut=%<nombre%>
NbQ=%<nombre%>
Exercice#true,false
Ordre#true,false
Nom#true,false
CAN#true,false
#endkeyvals

\ChoixAlea{a}{b}{cmd}#d
\ChoixAlea[p]{a}{b}{cmd}#d
\VariableAlea{cmd}{fp expression}#d
\MathAlea{file}#*i
\MathAlea[clés%keyvals]{file}#*i
\CourseNombreTotalQuestions{nombre}#*

## Une aide à l’autonomie ##
\Autonomie{q1/r1§q2/r2§...§q8/r8%text}{Q1/I1§Q2/I2§...§Q8/I8%text}
\Autonomie[clés%keyvals]{q1/r1§q2/r2§...§q8/r8%text}{Q1/I1§Q2/I2§...§Q8/I8%text}

#keyvals:\Autonomie
AfficheMarge#true,false
TitreAtoi=%<texte%>
TexteCorrection=%<texte%>
#endkeyvals

## Fiche de mémorisation active ##
\FicheMemo{l1/q1/r1§l2/q2/r2§...%text}{L1/Q1/R1§L2/Q2/I2§...%text}
\FicheMemo[clés%keyvals]{l1/q1/r1§l2/q2/r2§...%text}{L1/Q1/R1§L2/Q2/I2§...%text}

#keyvals:\FicheMemo
TexteReponses=%<texte%>
TexteQuestions=%<texte%>
Solution#true,false
Largeur=##L
#endkeyvals

## « Bon de sortie » ##
\BonSortie{énoncé1%text}{énoncé2%text}{énoncé3%text}{énoncé4%text}
\BonSortie[clés%keyvals]{énoncé1%text}{énoncé2%text}{énoncé3%text}{énoncé4%text}

#keyvals:\BonSortie
MemeEnonce#true,false
#endkeyvals

## La géométrie ##
\begin{Geometrie}
\begin{Geometrie}[clés%keyvals]
\end{Geometrie}

#keyvals:\begin{Geometrie}
CoinBG={%<(x,y)%>}
CoinHD={%<(x,y)%>}
TypeTrace="%<type%>"
#endkeyvals

## Les positions relatives de deux droites ##
\ProprieteDroites{a%formula}{b%formula}{c%formula}
\ProprieteDroites[clés%keyvals]{a%formula}{b%formula}{c%formula}

#keyvals:\ProprieteDroites
Num=#1,2,3
CitePropriete#true,false
Brouillon#true,false
Figure#true,false
Remediation#true,false
#endkeyvals

## Le repérage ##
\Reperage{Liste des éléments}
\Reperage[clés%keyvals]{Liste des éléments}
\ReperageMulti{Liste des éléments}#*
\ReperageMulti[clés%keyvals]{Liste des éléments}#*

#keyvals:\Reperage,\ReperageMulti
Unitex=%<nombre%>
AffichageGrad#true,false
AffichageNom#true,false
AffichageAbs=#1,2,3
AffichageCoord#true,false
Pasx=%<nombre%>
DemiDroite#true,false
ValeurOrigine=%<valeur%>
ValeurUnitex=%<valeur%>
Thermometre#true,false
Kelvin#true,false
Farenheit#true,false
Mercure#true,false
CouleurMercure=#%color
Plan#true,false
Unitey=%<nombre%>
Pasy=%<nombre%>
ValeurUnitey=%<valeur%>
LectureCoord#true,false
Trace#true,false
ListeSegment={%<liste de segments%>}
Espace#true,false
Unitez=%<nombre%>
Pasz=%<nombre%>
EchelleEspace=%<nombre%>
Sphere#true,false
AnglePhi=%<degrees%>
EchelleEspace=%<nombre%>
ValeurMin=%<nombre%>
ValeurMax=%<nombre%>
Etages=%<nombre%>
#endkeyvals

## La somme des angles d’un triangle ##
\SommeAngles{Nom du triangle}{a}{b}
\SommeAngles[clés%keyvals]{Nom du triangle}{a}{b}

#keyvals:\SommeAngles
Detail#true,false
Perso#true,false
Figure#true,false
Echelle=##L
Angle=%<degrees%>
FigureSeule#true,false
Isocele#true,false
Rectangle#true,false
#endkeyvals

\ResultatAngle

## Le théorème de Pythagore ##
\Pythagore{Nom du triangle}{a}{b}{c}
\Pythagore[clés%keyvals]{Nom du triangle}{a}{b}{c}

#keyvals:\Pythagore
Soustraction#true,false
Egalite#true,false
Exact#true,false
Entier#true,false
Racine#true,false
Precision=%<integer%>
Unite=%<unité%>
Reciproque#true,false
ReciColonnes#true,false
Faible#true,false
Figure#true,false
Angle=%<degrees%>
Echelle=##L
FigureSeule#true,false
EnchaineA#true,false
EnchaineB#true,false
EnchaineC#true,false
ValeurA=%<valeur%>
ValeurB=%<valeur%>
ValeurC=%<valeur%>
AvantRacine#true,false
SansMots#true,false
Perso#true,false
AllPerso#true,false
#endkeyvals

\ResultatPytha

## Le théorème de Thalès ##
\Thales{Nom des points considérés}{a}{b}{c}{d}{e}{f}
\Thales[clés%keyvals]{Nom des points considérés}{a}{b}{c}{d}{e}{f}

#keyvals:\Thales
Droites#true,false
Segment#true,false
Propor#true,false
Perso#true,false
Precision=%<integer%>
IntroCalculs#true,false
Unite=%<unité%>
Entier#true,false
Figure#true,false
Echelle=##L
Angle=%<degrees%>
CouleurNum=#%color
CouleurDen=#%color
FigureSeule#true,false
Figurecroisee#true,false
FigurecroiseeSeule#true,false
ChoixCalcul=#0,1,2,3
Redaction#true,false
Remediation#true,false
Reciproque#true,false
Produit#true,false
Simplification#true,false
#endkeyvals

\ResultatThalesx
\ResultatThalesy
\ResultatThalesz

## La trigonométrie ##
\Trigo{Nom du triangle}{a}{b}{c}
\Trigo[clés%keyvals]{Nom du triangle}{a}{b}{c}

#keyvals:\Trigo
Cosinus#true,false
Propor#true,false
Precision=%<integer%>
Unite=%<unité%>
Sinus#true,false
Tangente#true,false
Perso#true,false
Figure#true,false
Angle=%<degrees%>
Echelle=##L
FigureSeule#true,false
#endkeyvals

\ResultatTrigo

## Cartographie ##
\Cartographie{longitude}{latitude}
\Cartographie[clés%keyvals]{longitude}{latitude}

#keyvals:\Cartographie
Arborescence="%<path%>"
Carte#true,false
Fleuves#true,false
Capitales#true,false
CouleurFond=#%color
Impression#true,false
Echelle=%<nombre%>
EchelleCarte=%<nombre%>
AfficheEchelle#true,false
Largeur=%<nombre%>
Hauteur=%<nombre%>
All#true,false
Europe#true,false
Asie#true,false
Amsud#true,false
Amnord#true,false
Amcentre#true,false
Afrique#true,false
Caraibes#true,false
Pays="%<pays%>"
Villes="%<.dat file%>"
Projection#true,false
TypeProjection="%<type%>"
CouleurPays=#%color
#endkeyvals

## Les formules de périmètre, d’aire, de volume ##
\Formule
\Formule[clés%keyvals]

#keyvals:\Formule
Perimetre#true,false
Surface=#polygone,triangle,parallelogramme,losange,rectangle,carre,cercle,disque,sphere
Ancre={%<(x,y)%>}
Angle=%<degrees%>
Largeur=##L
Couleur=#%color
Echelle=##L
Aire#true,false
Volume#true,false
Solide=#pave,cube,cylindre,prisme,cone,pyramide,boule
#endkeyvals

## Empilements de cubes ##
\VueCubes{liste de hauteurs}
\VueCubes[clés%keyvals]{liste de hauteurs}

#keyvals:\VueCubes
Largeur=%<nombre%>
Profondeur=%<nombre%>
Hauteur=%<nombre%>
Echelle=%<nombre%>
CouleurCube=#%color
Angle=%<degres%>
Trou#true,false
Creation#true,false
Grilles#true,false
Face#true,false
CouleurFleche=#%color
Solution#true,false
Nom=%<nom%>
#endkeyvals

## Opérations posées ##
\Addition{n1}{n2}
\Addition[clés%keyvals]{n1}{n2}
\Soustraction{n1}{n2}
\Soustraction[clés%keyvals]{n1}{n2}
\Multiplication{n1}{n2}
\Multiplication[clés%keyvals]{n1}{n2}
\Division{n1}{n2}
\Division[clés%keyvals]{n1}{n2}
\DivisionD{n1}{n2}
\DivisionD[clés%keyvals]{n1}{n2}

#keyvals:\Addition,\Soustraction,\Multiplication,\Division,\DivisionD
CouleurCadre=#%color
CouleurFond=#%color
CouleurVirgule=#%color
Solution#true,false
CouleurSolution=#%color
#endkeyvals

## Pyramide de nombre ##
\PyramideNombre{c1,c2,...}
\PyramideNombre[clés%keyvals]{c1,c2,...}

#keyvals:\PyramideNombre
Etages=%<integer%>
Largeur=##L
Hauteur=##L
Inverse#true,false
Couleur=#%color
CouleurNombre=#%color
#endkeyvals

## Programme de calcul ##
\ProgCalcul{i1,i2,...%formula}
\ProgCalcul[clés%keyvals]{i1,i2,...%formula}

#keyvals:\ProgCalcul
Direct#true,false
Ecart=##L
SansCalcul#true,false
Enonce#true,false
Nom=%<nom%>
CouleurCadre=#%color
CouleurFond=#%color
Largeur=##L
Epaisseur=##L
Pointilles=##L
ThemePerso#true,false
Application#true,false
Details#true,false
#endkeyvals

## Les nombres premiers ##
\Decomposition{integer}
\Decomposition[clés%keyvals]{integer}

#keyvals:\Decomposition
Tableau#true,false
TableauVide#true,false
TableauVertical#true,false
TableauVerticalVide#true,false
Dot=%<dot code%>
Potence#true,false
Exposant#true,false
Longue#true,false
All#true,false
Nombre=%<nombre%>
AllNombre=%<nombre%>
Arbre#true,false
ArbreComplet#true,false
Entoure#true,false
ArbreVide#true,false
ArbreDessine#true,false
Impression#true,false
ArbreDessineVide#true,false
Diviseurs#true,false
DiviseursT#true,false
#endkeyvals

## Des engrenages ##
\Engrenages{m1/z1,m2/z2,...}
\Engrenages[clés%keyvals]{m1/z1,m2/z2,...}

#keyvals:\Engrenages
Unite=##L
Couleur=#%color
#endkeyvals

## La représentation graphique de fractions ##
\Fraction{a/b}
\Fraction[clés%keyvals]{a/b}

#keyvals:\Fraction
Disque#true,false
Rayon=##L
Regulier#true,false
Cotes=%<integer%>
Segment#true,false
Longueur=##L
Triangle#true,false
Parts=%<integer%>
Rectangle#true,false
Largeur=##L
Multiple=%<integer%>
Reponse#true,false
Couleur=#%color
Hachures#true,false
Epaisseur=%<factor%>
#endkeyvals

## Décomposer une fraction décimale ##
\FractionDecimale{a/b}
\FractionDecimale[clés%keyvals]{a/b}

#keyvals:\FractionDecimale
Complete#true,false
SansZero#true,false
Remediation#true,false
#endkeyvals

## La simplification d’écritures fractionnaires ##
\Simplification{a}{b}
\Simplification[clés%keyvals]{a}{b}

#keyvals:\Simplification
Details#true,false
All#true,false
Longue#true,false
Contraire=%<integer%>
Fleches#true,false
#endkeyvals

## Ranger des nombres rationnels relatifs ##
\Rangement{Liste de nombres}
\Rangement[clés%keyvals]{Liste de nombres}

#keyvals:\Rangement
Decroissant#true,false
Strict#true,false
Fraction#true,false
Details#true,false
#endkeyvals

## Les puissances ##
\Puissances{expr%formula}{integer}

## La proportionnalité ##
\Propor{Liste des éléments par colonne}
\Propor[clés%keyvals]{Liste des éléments par colonne}

#keyvals:\Propor
Vertical#true,false
GrandeurA=%<texte%>
GrandeurB=%<texte%>
Math#true,false
Stretch=%<factor%>
Largeur=##L
CouleurTab=#%color
#endkeyvals

\FlechesPH{a}{b}{texte}
\FlechesPB{a}{b}{texte}
\FlechesPG{a}{b}{texte}
\FlechesPD{a}{b}{texte}
\FlecheCoef{texte}
\FlecheCoefDebut{texte}
\FlecheLineaireH{a}{b}{c}{opération}
\FlecheLineaireB{a}{b}{c}{opération}
\FlecheLineaireG{a}{b}{c}{opération}
\FlecheLineaireD{a}{b}{c}{opération}
\FlecheRatio{texte%plain}
\FlecheInvRatio{texte%plain}

## Les pourcentages ##
\Pourcentage{t}{q}
\Pourcentage[clés%keyvals]{t}{q}

#keyvals:\Pourcentage
Appliquer#true,false
Fractionnaire#true,false
Concret#true,false
Unite=%<unité%>
Augmenter#true,false
AideTableau#true,false
GrandeurA=%<texte%>
GrandeurB=%<texte%>
CouleurTab=#%color
Formule#true,false
Reduire#true,false
MotReduction=%<mot%>
Calculer#true,false
#endkeyvals

\ResultatPourcentage

## Les ratios ##
\Ratio{Liste des éléments du ratio}
\Ratio[clés%keyvals]{Liste des éléments du ratio}

#keyvals:\Ratio
Figure#true,false
Longueur=##L
TexteTotal=%<texte%>
TextePart=%<texte%>
CouleurUn=#%color
CouleurDeux=#%color
CouleurTrois=#%color
FigureCours#true,false
Tableau#true,false
GrandeurA=%<texte%>
GrandeurB=%<texte%>
Largeur=##L
Stretch=%<factor%>
CouleurTab=#%color
Nom#true,false
#endkeyvals

## Les statistiques ##
\Stat{Données}
\Stat[clés%keyvals]{Données}

#keyvals:\Stat
Qualitatif#true,false
Liste#true,false
Sondage#true,false
Tableau#true,false
Stretch=%<factor%>
CouleurTab=#%color
Largeur=##L
TableauVide#true,false
Donnee=%<texte%>
Effectif=%<texte%>
EffVide#true,false
Frequence#true,false
FreqVide#true,false
Angle#true,false
SemiAngle#true,false
AngVide#true,false
ECC#true,false
ECCVide#true,false
Total#true,false
ColVide=%<integer%>
CasesVides={%<cases%>}
Graphique#true,false
Batons#true,false
Unitex=%<nombre%>
Unitey=%<nombre%>
Grille#true,false
Pasx=%<nombre%>
Pasy=%<nombre%>
EpaisseurBatons=%<nombre%>
Origine=%<nombre%>
AngleRotationAbscisse=%<degrees%>
Lecture#true,false
LectureFine#true,false
AideLecture#true,false
Tiret#true,false
Depart=%<nombre%>
Reponses#true,false
DonneesSup#true,false
CouleurDefaut=#%color
ListeCouleursB={%<liste des coleurs%>}
Angle#true,false
SemiAngle#true,false
Rayon=##L
AffichageAngle#true,false
AffichageDonnees#true,false
LectureInverse#true,false
Legende#true,false
LegendesVides={%<liste de numéros%>}
Hachures#true,false
EcartHachures=%<nombre%>
EpaisseurHachures=%<nombre%>
ListeCouleurs={%<liste des coleurs%>}
Barre#true,false
Longueur=##L
Hauteur=##L
EcartBarre=##L
Bicolore#true,false
Representation#true,false
Xmin=%<nombre%>
Xmax=%<nombre%>
Ymin=%<nombre%>
Ymax=%<nombre%>
Xstep=%<nombre%>
Ystep=%<nombre%>
LabelX=%<texte%>
LabelY=%<texte%>
PasGrilleX=%<nombre%>
PasGrilleY=%<nombre%>
Graduations#true,false
CouleurTrace=#%color
Relie#true,false
RelieSegment#true,false
Invisible#true,false
CouleurPoint=#%color
Marque=#dot,croix
EffectifTotal#true,false
Etendue#true,false
Concret#true,false
Unite=%<unité%>
Mediane#true,false
Coupure=%<integer%>
Moyenne#true,false
Precision=%<integer%>
SET#true,false
ValeurExacte#true,false
ACompleter#true,false
#endkeyvals

\EffectifTotal
\Etendue
\Moyenne
\Mediane
\QuartileUn
\QuartileTrois

## Les probabilités ##
\Proba{Liste des évènements et probabilités}
\Proba[clés%keyvals]{Liste des évènements et probabilités}

#keyvals:\Proba
Echelle#true,false
LongueurEchelle=%<nombre%>
Grille=%<nombre%>
Affichage=#0,1,2,3,4
Arbre#true,false
Branche=%<nombre%>
Angle=%<degrees%>
Rayon=%<nombre%>
Incline#true,false
#endkeyvals

## Les fonctions affines ##
\FonctionAffine{Noms des points considérés}{a}{b}{c}{d}
\FonctionAffine[clés%keyvals]{Noms des points considérés}{a}{b}{c}{d}

#keyvals:\FonctionAffine
Definition#true,false
Nom=%<nom%>
Variable=%<variable%>
Ecriture#true,false
Image#true,false
Ligne#true,false
ProgCalcul#true,false
Antecedent#true,false
Retrouve#true,false
Redaction#true,false
Graphique#true,false
Unitex=%<nombre%>
Unitey=%<nombre%>
VoirCoef#true,false
ACoef=%<nombre%>
#endkeyvals

## Les fonctions ##
\Fonction{Liste des valeurs}
\Fonction[clés%keyvals]{Liste des valeurs}

#keyvals:\Fonction
Calcul=%<fonction%>
Tableau#true,false
Largeur=##L
Nom=%<nom%>
Variable=%<variable%>
Definition#true,false
Ecriture#true,false
Points#true,false
Tangentes#true,false
PasX=%<nombre%>
PasY=%<nombre%>
UniteX=%<nombre%>
UniteY=%<nombre%>
Prolonge#true,false
Trace#true,false
Xmin=%<nombre%>
Xmax=%<nombre%>
Ymin=%<nombre%>
Ymax=%<nombre%>
Xstep=%<nombre%>
Ystep=%<nombre%>
LabelX=%<texte%>
LabelY=%<texte%>
Origine={%<(x,y)%>}
Grille#true,false
PasGrilleX=%<nombre%>
PasGrilleY=%<nombre%>
Graduations#true,false
PasGradX=%<nombre%>
PasGradY=%<nombre%>
Bornea=%<nombre%>
Borneb=%<nombre%>
CouleurTrace=#%color
NomCourbe=%<nom%>
LabelC=%<nombre%>
#endkeyvals

## La distributivité ##
\Distri{a}{b}{c}{d}
\Distri[clés%keyvals]{a}{b}{c}{d}

#keyvals:\Distri
Numerique#true,false
Etape=#-1,0,1,2,3,4
All#true,false
NomExpression=%<nom%>
Fin=%<valeur%>
Lettre=%<lettre%>
Fleches#true,false
CouleurFH=#%color
CouleurFB=#%color
AideMul#true,false
Reduction#true,false
CouleurReduction=#%color
AideAdda#true,false
AideAddb#true,false
CouleurAide=#%color
Cours#true,false
Tuile#true,false
Vide#true,false
Impression#true,false
RAZ#true,false
Somme#true,false
Difference#true,false
Oppose#true,false
Remarquable#true,false
Echange=#0,1,2,3
Tableau#true,false
#endkeyvals

\Resultat

## Un modèle en barre ##
\ModeleBarre{C1 N1 "T1" C2 N2 "T2"...}{c1 n1 "t1" c2 n2 "t2"...}
\ModeleBarre[clés%keyvals]{C1 N1 "T1" C2 N2 "T2"...}{c1 n1 "t1" c2 n2 "t2"...}

#keyvals:\ModeleBarre
Largeur=##L
Separation=%<nombre%>
#endkeyvals

## La résolution d’équations du premier degré ##
\ResolEquation{a}{b}{c}{d}
\ResolEquation[clés%keyvals]{a}{b}{c}{d}

#keyvals:\ResolEquation
Lettre=%<lettre%>
Solution#true,false
LettreSol#true,false
Entier#true,false
Simplification#true,false
Decimal#true,false
Verification#true,false
Nombre=%<nombre%>
Egalite#true,false
Decomposition#true,false
CouleurSous=#%color
Fleches#true,false
Ecart=%<nombre%>
FlecheDiv#true,false
Pose#true,false
Laurent#true,false
Terme#true,false
CouleurTerme=#%color
Composition#true,false
CouleurCompo=#%color
Symbole#true,false
CouleurSymbole=#%color
Bloc#true,false
Produit#true,false
Facteurs#true,false
Equivalence#true,false
Carre#true,false
Exact#true,false
#endkeyvals

\leftcomment{A-8}{B-8}{A-8}{\dots}
\rightcomment{E-8}{F-8}{E-8}{\dots}

## Calculatrice ##
\Calculatrice{val1/val2/...}
\Calculatrice[clés%keyvals]{val1/val2/...}

#keyvals:\Calculatrice
Ecran#true,false
NbLignes=%<integer%>
#endkeyvals

## Le tableur ##
\begin{Tableur}#\tabular
\begin{Tableur}[clés%keyvals]#\tabular
\end{Tableur}

#keyvals:\begin{Tableur}
Bandeau#true,false
Colonnes=%<integer%>
Largeur=##L
LargeurUn=##L
Formule=%<formule%>
Cellule=%<cellule%>
Ligne=%<integer%>
PasL=%<integer%>
Colonne=%<integer%>
PasC=%<integer%>
Couleur=#%color
#endkeyvals

## Le codage RLE
\CodageRLE{liste}
\CodageRLE[clés%keyvals]{liste}

#keyvals:\CodageRLE
Enonce#true,false
Solution#true,false
Unite=##L
Taille=%<nombre%>
#endkeyvals

## Une tortue ##
\Tortue{liste des commandes}
\Tortue[clés%keyvals]{liste des commandes}

#keyvals:\Tortue
Pas=##L
Epaisseur=%<nombre%>
TortueD#true,false
TortueF#true,false
Angle=%<degrés%>
Etape=%<nombre%>
Grille#true,false
LargeurG=%<nombre%>
HauteurG=%<nombre%>
Axes#true,false
Origine={(%<x,y%>)}
Cases#true,false
Depart={(%<x,y%>)}
## not documented
# Etapes#true,false
# Nom=%<fichier%>
# Debut#true,false
#endkeyvals

## Les briques Scratch ##
\begin{Scratch}
\begin{Scratch}[clés%keyvals]
\end{Scratch}

#keyvals:\begin{Scratch}
Echelle=%<factor%>
Impression#true,false
Numerotation#true,false
Naturel#true,false
#endkeyvals

## La « rose » des multiplications ##
\RoseMul
\RoseMul[clés%keyvals]

#keyvals:\RoseMul
Nom=%<nom%>
FacteurMin=%<integer%>
FacteurMax=%<integer%>
Rayon=##L
Petales=%<integer%>
Solution#true,false
Produits#true,false
Aide#true,false
Vide#true,false
Polygone#true,false
CaseVide#true,false
ProduitVide#true,false
Couleur=#%color
#endkeyvals

## Le défi « Table » ##
\DefiTable{contenu}
\DefiTableTexte{liste}{phrase}
\DefiTableTexte[clés%keyvals]{liste}{phrase}

#keyvals:\DefiTableTexte
LargeurT=##L
Creation#true,false
Solution#true,false
Graine=%<nombre%>
#endkeyvals

## Billards ##
\Billard{"mot"}
\Billard[clés%keyvals]{"mot"}

#keyvals:\Billard
Longueur=##L
Largeur=##L
Solution#true,false
Vrai#true,false
Angle=%<degrees%>
Depart=%<nombre%>
#endkeyvals

## Labyrinthe ##
\Labyrinthe{Contenu1/Couleur1,Contenu2/Couleur2,...}{P1/P2/...}
\Labyrinthe[clés%keyvals]{Contenu1/Couleur1,Contenu2/Couleur2,...}{P1/P2/...}

#keyvals:\Labyrinthe
Colonnes=%<integer%>
Lignes=%<integer%>
Hauteur=%<nombre%>
Longueur=%<nombre%>
EcartH=%<nombre%>
EcartV=%<nombre%>
CouleurF=#%color
Texte=#%color
Passages#true,false
SensImpose#true,false
#endkeyvals

## Labyrinthe de nombres ##
\LabyNombre
\LabyNombre[clés%keyvals]

#keyvals:\LabyNombre
Nom=%<nom%>
Multiple=%<integer%>
Angle=%<degrees%>
Echelle=%<factor%>
Couleur=#%color
Longueur=%<nombre%>
Largeur=%<nombre%>
XDepart=%<integer%>
YDepart=%<integer%>
XArrivee=%<integer%>
YArrivee=%<integer%>
Solution#true,false
CouleurChemin=#%color
Murs#true,false
EntreeSortie#true,false
Entree="%<trouve%>"
Sortie="%<trouve%>"
#endkeyvals

## Triominos ##
\Triomino{v1§v2§v3...}
\Triomino[clés%keyvals]{v1§v2§v3...}

#keyvals:\Triomino
Longueur=##L
Etages=%<integer%>
Piece=%<integer%>
Hexagone#true,false
#endkeyvals

## Dessin gradué ##
\DessinGradue{a1/a2/a3,...}{b1/b2/b3,...}{c1§c2§...}
\DessinGradue[clés%keyvals]{a1/a2/a3,...}{b1/b2/b3,...}{c1§c2§...}

#keyvals:\DessinGradue
Lignes=%<integer%>
Longueur=%<nombre%>
Pas=%<integer%>
Debut=%<integer%>
Fin=%<integer%>
EcartVertical=%<nombre%>
Echelle=%<factor%>
Solution#true,false
LignesIdentiques#true,false
#endkeyvals

## Colorilude ##
\Colorilude{a11 b11 a12 b12\\a21 b21...%formula}
\Colorilude[clés%keyvals]{a11 b11 a12 b12\\a21 b21...%formula}

#keyvals:\Colorilude
Lignes=%<integer%>
Largeur=%<integer%>
Coef=%<nombre%>
Solution#true,false
CartonReponse#true,false
Resultats#true,false
#endkeyvals

\ColoriludeEnonce
\ColoriludeListeCouleur{abbrev1 couleur1 abbrev2 couleur2...}

## Pixel Art ##
\PixelArt{file}#i
\PixelArt[clés%keyvals]{file}#i

#keyvals:\PixelArt
Largeur=%<integer%>
Hauteur=%<integer%>
Unite=##L
Lettres=%<lettres%>
ListeCouleurs={%<color1,color2,...%>}
Solution#true,false
ListeNombres{%<nombre1,nombre2,...%>}
#endkeyvals

## Qui suis je? ##
\Quisuisje{c1§c2§...}{m o t à t r o u v e r}
\Quisuisje[clés%keyvals]{c1§c2§...}{m o t à t r o u v e r}

#keyvals:\Quisuisje
Colonnes=%<integer%>
Solution#true,false
CodePerso#true,false
#endkeyvals

\QuisuisjeEnonce
\QuisuisjeTableau{l1/v1§l2/v2§...}
\QuisuisjeTableau[Largeur=%|]{%<l1/v1§l2/v2§...%>}
\QuisuisjeCodePerso{n1 n2...}{l1 l2...}
\QuisuisjeCodePerso[Solution]{%<n1 n2...%>}{%<l1 l2...%>}

## Mots empilés ##
\MotsEmpiles{c1/mot1,c2/mot2,...}
\MotsEmpiles[clés%keyvals]{c1/mot1,c2/mot2,...}

#keyvals:\MotsEmpiles
Colonne=%<integer%>
Solution#true,false
Couleur=#%color
#endkeyvals

## Mots croisés ##
\MotsCroises{m11/q11,m12/q12...§m21/q21,m22/q22...}
\MotsCroises[clés%keyvals]{m11/q11,m12/q12...§m21/q21,m22/q22...}

#keyvals:\MotsCroises
Colonnes=%<integer%>
Lignes=%<integer%>
Largeur=##L
Croises#true,false
Couleur=#%color
Solution#true,false
#endkeyvals

## Mots codés ##
\MotsCodes{énoncé1/lettre1§énoncé2/lettre2§...}
\MotsCodes[clés%keyvals]{énoncé1/lettre1§énoncé2/lettre2§...}

#keyvals:\MotsCodes
Colonnes=%<integer%>
Largeur=##L
#endkeyvals

\MotsCodesTableau{r11/r12...,r21/r22...}{texte à trouver}
\MotsCodesTableau[clés%keyvals]{r11/r12...,r21/r22...}{texte à trouver}

#keyvals:\MotsCodesTableau
Math#true,false
LargeurT=##L
Solution#true,false
#endkeyvals

## Mosaïque ##
\Mosaique{mosa1/rep1,mosa2/rep2,...}
\Mosaique[clés%keyvals]{mosa1/rep1,mosa2/rep2,...}

#keyvals:\Mosaique
Solution#true,false
Type=%<nombre%>
Label=
Largeur=%<integer%>
Hauteur=%<integer%>
Echelle=##L
#endkeyvals

\DessineMosaique{type}
\DessineMosaique[clés%keyvals]{type}

#keyvals:\DessineMosaique
Type=%<nombre%>
Echelle=##L
#endkeyvals

## Des cartes à jouer ##
\Cartes{contenus du jeu%text}
\Cartes[clés%keyvals]{contenus du jeu%text}

#keyvals:\Cartes
Loop#true,false
Landscape#true,false
Largeur=%<nombre%>
Hauteur=%<nombre%>
Marge=%<nombre%>
Couleur=#%color
Theme=%<texte%>
HauteurTheme=%<nombre%>
Titre#true,false
NomTitre=%<nom%>
Trame#true,false
JaiQuia#true,false
BackgroundAv#true,false
ImageAv=%<imagefile%>
BackgroundAr#true,false
ImageAr=%<imagefile%>
ThemeSol=%<texte%>
Trivial#true,false
Symboles={%<symbole1,symbole2,...%>}
#endkeyvals

\SolutionCarte{solution}{commentaires%text}

## Des dominos à jouer ##
\Dominos{e q1/r1§q2/r2§...}
\Dominos[clés%keyvals]{e q1/r1§q2/r2§...}

#keyvals:\Dominos
Trame#true,false
Lignes=%<integer%>
Colonnes=%<integer%>
Logo#true,false
Image=%<imagefile%>
Couleur=#%color
Ratio=%<ratio%>
Superieur#true,false
#endkeyvals

## Des Enquêtes ##
\Enquete[clés%keyvals]

#keyvals:\Enquete
Largeur=##L
Perso=%<nom%>
Objet=%<nom%>
Lieu=%<nom%>
#endkeyvals

\ListePersonnages{p1§p2§...}
\ListeObjets{o1§o2§...}
\ListeLieux{l1§l2§...}
\ListeQuestions{e1/r1§e2/r2§...}
\AffichageQuestions
\AffichageTableau

## Puissance Quatre ##
\PQuatre{éléments du tableau}
\PQuatre[clés%keyvals]{éléments du tableau}

#keyvals:\PQuatre
Relatif#true,false
Puissance#true,false
Autre#true,false
Consignes="%<texte%>"
LargeurUn=##L
Echelle=%<nombre%>
Addition#true,false
Couleur=#%color
#endkeyvals

## Le Yohaku ##
\Yohaku{a/b/c/d...,1/2/3/4...}
\Yohaku[clés%keyvals]{a/b/c/d...,1/2/3/4...}

#keyvals:\Yohaku
Taille=%<nombre%>
Largeur=##L
Hauteur=##L
Bordure#true,false
CouleurResultat=#%color
Multiplication#true,false
Limite=%<nombre%>
Pair#true,false
Impair#true,false
Premier#true,false
Perso#true,false
Case=%<integer%>
Ligne=%<integer%>
PasL=%<integer%>
Colonne=%<integer%>
PasC=%<integer%>
Solution#true,false
Addition
CouleurZone=#%color
Relatif#true,false
Negatif#true,false
#endkeyvals

\PfCYHKpremier#*

## Le KenKen ##
\KenKen{description du jeu}
\KenKen[clés%keyvals]{description du jeu}

#keyvals:\KenKen
Taille=%<nombre%>
Largeur=##L
Nombre=%<nombre%>
Solution#true,false
#endkeyvals

## Le Kakuro ##
\Kakuro{description du jeu}
\Kakuro[clés%keyvals]{description du jeu}

#keyvals:\Kakuro
TLargeur=%<nombre%>
THauteur=%<nombre%>
Taille=%<nombre%>
Largeur=##L
CouleurCase=#%color
ListeNombres={%<nombre1,nombre2,...%>}
Solution#true,false
CouleurSolution=#%color
#endkeyvals

## Le Shikaku ##
\Shikaku{description du jeu}
\Shikaku[clés%keyvals]{description du jeu}

#keyvals:\Shikaku
Taille=%<nombre%>
Largeur=##L
Solution#true,false
Couleur=#%color
CodeAfter={%<code%>}
Creation#true,false
TailleHor=%<nombre%>
TailleVer=%<nombre%>
TailleHorMax=%<nombre%>
TailleVerMax=%<nombre%>
Nom=%<nom%>
#endkeyvals

## Calculs Croisés ##
\CalculsCroises{description du jeu}
\CalculsCroises[clés%keyvals]{description du jeu}

#keyvals:\CalculsCroises
Largeur=##L
Couleur=#%color
Solution#true,false
ListeNombres={%<liste%>}
Inverse#true,false
Vide#true,false
Creation#true,false
Negatifs#true,false
Graines#true,false
#endkeyvals

## Nombre astral ##
\NombreAstral
\NombreAstral[clés%keyvals]

#keyvals:\NombreAstral
Echelle=%<échelle%>
Solution#true,false
Graine=%<integer%>
#endkeyvals

## Le compte est bon ##
\CompteBon
\CompteBon[clés%keyvals]

#keyvals:\CompteBon
NombreCalculs=%<nombre%>
Solution#true,false
Graine=%<integer%>
Relatifs#true,false
Original#true,false
Plaques=%<nombre%>
#endkeyvals

## Bulles et cartes mentales ##
\begin{Mind}#\pictureHighlight
\end{Mind}

\begin{Bulle}
\begin{Bulle}[clés%keyvals]
\end{Bulle}

#keyvals:\begin{Bulle}
Nom=%<nom%>
Largeur=##L
Pointilles#true,false
CTrace=#%color
Epaisseur=##L
Rayon=%<nombre%>
CFond=#%color
Ancre={%<x,y%>}
#endkeyvals

## Des réseaux sociaux? ##
\begin{Twitter}
\begin{Twitter}[clés%keyvals]
\end{Twitter}

#keyvals:\begin{Twitter}
Largeur=##L
Auteur=%<auteur%>
Date=%<date%>
Url=%<URL%>
Logo=%<imagefile%>
EchelleLogo=%<factor%>
Publie#true,false
#endkeyvals

\begin{Facebook}
\begin{Facebook}[clés%keyvals]
\end{Facebook}

#keyvals:\begin{Facebook}
Largeur=##L
Auteur=%<auteur%>
Date=%<date%>
Logo=%<imagefile%>
EchelleLogo=%<factor%>
Publie#true,false
Heure=%<heure%>
#endkeyvals

\begin{Snapchat}
\begin{Snapchat}[clés%keyvals]
\end{Snapchat}

#keyvals:\begin{Snapchat}
Largeur=##L
Auteur=%<auteur%>
Date=%<date%>
Logo=%<imagefile%>
EchelleLogo=%<factor%>
Temps=%<temps%>
Texte=%<texte%>
#endkeyvals

\begin{Instagram}
\begin{Instagram}[clés%keyvals]
\end{Instagram}

#keyvals:\begin{Instagram}
Largeur=##L
Auteur=%<auteur%>
Date=%<date%>
Logo=%<imagefile%>
EchelleLogo=%<factor%>
Temps=%<temps%>
Expediteur=%<expéditeur%>
LogoEx=%<imagefile%>
Texte=%<texte%>
#endkeyvals

## Professeur principal ##
\Radar{Liste des éléments du diagramme en radar}
\Radar[clés%keyvals]{Liste des éléments du diagramme en radar}

#keyvals:\Radar
Rayon=##L
Pas=%<integer%>
Reference=%<integer%>
MoyenneClasse#true,false
Disciplines#true,false
#endkeyvals

\Jauge{Niveau atteint en pourcentage}
\Jauge[clés%keyvals]{Niveau atteint en pourcentage}

#keyvals:\Jauge
TexteOrigine=%<texte%>
TexteReference=%<texte%>
Nom=%<nom%>
CouleurBarre=#%color
CouleurFond=#%color
Graduation#true,false
CouleurGraduation=#%color
Niveau#true,false
LimiteI=%<pourcentage%>
LimiteF=%<pourcentage%>
LimiteS=%<pourcentage%>
CouleurI=#%color
CouleurF=#%color
CouleurS=#%color
CouleurM=#%color
#endkeyvals

## Quelques éléments pratiques... ##
\Demain
\pointilles
\pointilles[length]
\Lignespointilles{n}
\MultiCol{l1/l2/...}{contenu1§contenu2§...%text}

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

# from most option of tcolorbox (repeats removed)
#include:incgraph
#include:listings
#include:listingsutf8
#include:shellesc
#include:pdfcol

# from tikzmark library v1.10
\tikzmark{name}
\tikzmark[drawing command]{name}
\tikzmark{name}{coordinate}
\pgfmark{name}
\iftikzmark{name}{true}{false}
\iftikzmarkexists{name}
\iftikzmarkoncurrentpage{name}
\iftikzmarkonpage{name}{page}
\tikzmarknode{name}{contents}
\tikzmarknode[options]{name}{contents}
\subnode{name}{contents}
\subnode[options]{name}{contents}
\usetikzmarklibrary{library}#*

# not documented
\addtotok{arg1}{arg2}#S
\Affichage{arg1}{arg2}{arg3}{arg4}#S
\AffichageCoord#S
\AffichageEchange{arg1}{arg2}{arg3}{arg4}#S
\AffichageEqua{arg1}{arg2}{arg3}{arg4}#S
\AffichageGrad#S
\AffichageNom#S
\AfficheCoord#S
\AfficheGrad#S
\AfficheNom#S
\AjoutListEEaa{arg1}#S
\AjoutListEEab{arg1}#S
\AjoutListEEb{arg1}#S
\AjoutListEEx{arg1}#S
\AjoutListEEy{arg1}#S
\Alea#S
\annee#*
\anp#S
\anpdc#S
\anpl#S
\anpmv#S
\anpT#S
\anpv#S
\anpv#S
\anpvv#S
\are#*
\barre#S
\barrewidth#S
\begin{CadreNombre}#S
\begin{calc}#S
\begin{Mybox}{arg1}{arg2}{arg3}#S
\begin{MyboxJQ}{arg1}{arg2}#S
\begin{MyboxSimpleAr}{arg}#S
\begin{MyboxSimpleAv}{arg}#S
\begin{MyboxTrivial}#S
\begin{MyboxTrivial}[options]#S
\begin{MyDominoLogo}#S
\begin{MyDominoMini}#S
\begin{QuestionBox}#S
\begin{QuestionReponse}#S
\begin{RapidoBox}#S
\begin{Sortie}#S
\begin{Trame}#S
\begin{TrameDomino}#S
\bla#S
\bnp#S
\bnpdc#S
\bnpl#S
\bnpmv#S
\bnpT#S
\bnpv#S
\bnpv#S
\bnpvv#S
\BonSortieBandeau#S
\BonSortieSmiley#*
\Brouillon{arg1}{arg2}{arg3}{arg4}#S
\buildarbreproba#S
\builddemidroitenew#S
\buildechelleproba#S
\BuildEngrenages{arg}#S
\buildespace#S
\buildgraph{arg1}#S
\buildgraphbarhor#S
\buildgraphcq{arg1}#S
\buildgraphq{arg1}#S
\BuildNombreAstral{arg}{arg}#S
\BuildPixelArt{arg1}{arg2}{arg3}{arg4}#S
\buildreperenew#S
\BuildRLE{arg}#S
\buildtabfonction#S
\buildtabpropor#S
\Buildtabpropor#S
\buildtabratio#S
\buildtabrelie#S
\buildtabrelieold#S
\BuildtabStat#S
\buildtabt#S
\BuildVueCubes{arg1}{arg2}#S
\BuildVueCubesSolution#S
\CalculAngle{arg1}#S
\CalculECC{arg1}#S
\CalculFrequence{arg1}#S
\CalculNombreComposants#S
\CalculSemiAngle{arg1}#S
\CANNew#S
\CANSGFoo#S
\ChiffreAAjouter#S
\ChiffrePartieDecimale#S
\cmptEE#S
\cmxa#S
\cmya#S
\cmza#S
\CNfoo#S
\CNFOO#S
\CNfooListe#S
\CNFOOListePerso#S
\CNFOOSSDossiers#S
\cnp#S
\cnpdc#S
\cnpl#S
\cnpmv#S
\cnpT#S
\cnpv#S
\cnpv#S
\cnpvv#S
\CNReponse#S
\cntcol#S
\CNTheme{arg}#S
\cntlin#S
\Coeffa#S
\Coeffb#S
\Coeffc#S
\Coeffd#S
\ColonneDomino#S
\ColorFill#S
\colorfill#S
\Compteur#S
\CompteurCalcul#S
\compteurcnt#S
\CompteurECC#S
\CompteurECCTotal#S
\CouleurBarre#S
\CouleurDomino#S
\CouleurF#S
\CouleurFond#S
\CouleurGrad#S
\CouleurI#S
\CouleurM#S
\CouleurS#S
\CouleurTrace#S
\CountcolDeux#S
\CountcolUn#S
\dashblank#S
\DecalageLigne#S
\DecompositionFracDeciComplete#S
\DefinirListeFichiers#S
\DefiTableNombreLettreduCode{arg}#S
\demibarre#S
\denominateur#S
\DenominateurDiv#S
\DenomSimp#S
\DenomSimpa#S
\DenomSimpaa#S
\DessineMosaiqueComplet{arg1}#S
\DessinePyramideNombre{arg1}#S
\DessinePyramideNombreMul{arg}#S
\DessineRoseMul#S
\DessineRoseMulSol#S
\dispogpfc{arg1}{arg2}{arg3}#S
\DistriEchange{arg1}{arg2}{arg3}{arg4}{arg5}#S
\DistriTableau[opt]{arg1}{arg2}{arg3}{arg4}{arg5}#S
\DistriTableau{arg1}{arg2}{arg3}{arg4}{arg5}#S
\DivCom#S
\DiviseurCommun{arg1}{arg2}#S
\DiviseurNumero{arg1}{arg2}#S
\DivMax#S
\dnp#S
\dnpdc#S
\dnpmv#S
\dnpT#S
\dnpvv#S
\DonneeMax#S
\DonneeMin#S
\Dotfill#S
\DrawArrow#S
\DrawArrowSimple{arg1}#S
\DrawArrowSimpleRenverse{arg1}#S
\EcartLargeur#S
\EchelleLogo#S
\EcrireSolutionEquation{arg1}{arg2}{arg3}{arg4}#S
\EcritureCalculs#S
\EcritureDecimale#S
\EcriturePluriel{arg1}#S
\EcritureQuotients#S
\EffectifMax#S
\ElementsMelanges#S
\emoticon[TikZ keys]{draw code}#*
\emoticon{draw code}#*
\end{CadreNombre}#S
\end{calc}#S
\end{Mybox}#S
\end{MyboxJQ}#S
\end{MyboxSimpleAr}#S
\end{MyboxSimpleAv}#S
\end{MyboxTrivial}#S
\end{MyDominoLogo}#S
\end{MyDominoMini}#S
\end{QuestionBox}#S
\end{QuestionReponse}#S
\end{RapidoBox}#S
\end{Sortie}#S
\end{Trame}#S
\end{TrameDomino}#S
\EpaisseurLigne#S
\Eqalign{arg1}#S
\EquaBase{arg1}{arg2}{arg3}{arg4}{arg5}#S
\EquaBaseL{arg1}{arg2}{arg3}{arg4}{arg5}#S
\EquaBaseLaurent{arg1}{arg2}{arg3}{arg4}{arg5}#S
\EquaBaseSymbole{arg1}{arg2}{arg3}{arg4}{arg5}#S
\EquaDeuxComposition{arg1}{arg2}{arg3}{arg4}{arg5}#S
\EquaDeuxL{arg1}{arg2}{arg3}{arg4}{arg5}#S
\EquaDeuxLaurent{arg1}{arg2}{arg3}{arg4}{arg5}#S
\EquaDeuxSoustraction{arg1}{arg2}{arg3}{arg4}{arg5}#S
\EquaDeuxSymbole{arg1}{arg2}{arg3}{arg4}{arg5}#S
\EquaDeuxTerme{arg1}{arg2}{arg3}{arg4}{arg5}#S
\EquaTroisComposition{arg1}{arg2}{arg3}{arg4}{arg5}#S
\EquaTroisL{arg1}{arg2}{arg3}{arg4}{arg5}#S
\EquaTroisLaurent{arg1}{arg2}{arg3}{arg4}{arg5}#S
\EquaTroisSoustraction{arg1}{arg2}{arg3}{arg4}{arg5}#S
\EquaTroisSymbole{arg1}{arg2}{arg3}{arg4}{arg5}#S
\EquaTroisTerme{arg1}{arg2}{arg3}{arg4}{arg5}#S
\Etape#S
\EuRo#*
\exposant#S
\ExposantDivMax#S
\ExtraitElements{arg}#S
\ExtraitFruit{arg}#S
\ExtraitNom{arg}#S
\ExtraitObjets{arg}#S
\ExtraitSommet{arg}#S
\ExtraitSymboles{arg}#S
\faa#S
\fahrenheit#*
\FaireFigure{arg1}{arg2}{arg3}{arg4}#S
\Fdash{arg1}#S
\fdash{arg1}#S
\fdashlength#S
\fdashsep#S
\fdashwidth#S
\fii#S
\FlecheCoefInv[opt]{arg1}#S
\FlecheCoefInv{arg1}#S
\foo#S
\FooListeEntier#S
\FooStat#S
\FooStatCases#S
\FractionDeciDeno#S
\FractionDeciNum#S
\FruitsMelanges#S
\fuu#S
\fuuu#S
\getstrut{arg}#S
\GrandCote#S
\hauteurcards#S
\hauteurcarte#S
\HauteurFlash
\hauteurtitre#S
\hdash#S
\Intermed#S
\jour#*
\k#S
\kmh#*
\KN#S
\KY#S
\KYm#S
\LabyHaut#S
\LabyLong#S
\LabySlop#S
\largeurcards#S
\largeurcarte#S
\LargeurQCM#S
\largeurtitre#S
\leftcomment{arg1}{arg2}{arg3}{arg4}#*
\Leftcomment{arg1}{arg2}{arg3}{arg4}#S
\LETTRE#S
\LigneDomino#S
\Liste#S
\Listea#S
\ListeAutoEn#S
\ListeAutoQ#S
\ListeAvantCouleurs#S
\ListeAvantNombres#S
\Listeb#S
\ListeCalc#S
\ListeCalculs#S
\ListeCalculslen#S
\ListeCaracteresUniques#S
\ListeCards#S
\ListeCasesAVider#S
\ListeCasesCroises#S
\ListeCasesKK#S
\ListeCasesSKK#S
\ListeCNQuestions#S
\ListeColonnesAVider#S
\ListeColorilude#S
\ListeColoriludeCouleurs#S
\ListeColoriludelen#S
\ListeColoriludeMax#S
\ListeComplete#S
\ListeCompleteDiagHor#S
\ListeCompletelen#S
\ListeComposantStatCAN#S
\ListeContenuCol#S
\ListeCouleur#S
\ListeCouleurEntier#S
\ListeDefDroites#S
\ListeDefiTableCode#S
\ListeDefiTableMax#S
\ListeDefiTablePhrase#S
\ListeDefiTableTableau#S
\ListeDefLigne#S
\ListeDesCaracteresAUtiliser#S
\ListeDesCaracteresFoo#S
\ListeDesChiffres#S
\ListeDesLettres#S
\ListeDesLettresUniques#S
\ListeDesLettresUniqueslen#S
\ListeDesProduits#S
\ListeDesProduitsFoo#S
\ListeDesSSDossiersPerso#S
\Listedesvaleursaplacersurlademidroite#S
\ListeDiviseur{arg1}#S
\ListeDiviseurT{arg1}#S
\ListeDominos#S
\listEE#S
\listEEa#S
\listEEb#S
\ListeEcriture#S
\ListeEcriturelen#S
\ListeEtapes#S
\ListeFichiers#S
\ListeFichierslen#S
\ListeFinaleDesCaracteres#S
\ListeFlash#S
\ListeFlashlen#S
\ListeFonction#S
\ListeFonctionlen#S
\ListeFraction#S
\ListeFractionDecimale#S
\ListeFruitsCAN#S
\ListefuuLieux#S
\ListefuuObjets#S
\ListefuuPerso#S
\ListeInitiale#S
\ListeInter#S
\ListeInterlen#S
\ListeKakuroNombres#S
\ListeKakuroNombreslen#S
\ListeLaby#S
\ListeLabylen#S
\ListeLabySol#S
\ListeLegendesAEffacer#S
\Listelen#S
\ListeLettres#S
\ListeLettreslen#S
\ListeLieuxObjetsCAN#S
\ListeMelangeeLieux#S
\ListeMelangeeObjets#S
\ListeMelangeePersonnages#S
\ListeMelangeeQuestions#S
\ListeModelBarreInf#S
\ListeModelBarreSup#S
\ListeMosaique#S
\ListeMotsCAN#S
\ListeMotsCodes#S
\ListeMotsCodesMax#S
\ListeMotsCodesPas#S
\ListeMotsCodesPhrase#S
\ListeMotsCodesTableau#S
\ListeMotsEmpiles#S
\ListeMotsEmpilesMax#S
\ListeMulAstucieuxCAN#S
\ListeNom#S
\ListeNombreAPlacer#S
\ListeNombreAPlacerlen#S
\ListeNombreCol#S
\ListeNombreCollen#S
\ListeNomsCAN#S
\ListeNomsMul#S
\ListeObjetsCAN#S
\ListeObjetsSymbolesCAN#S
\ListePANombre#S
\ListePfCEngrenages#S
\ListePG#S
\ListePointDroite#S
\ListePointEspace#S
\ListePointRepere#S
\ListePoints#S
\ListePointsPlaces#S
\ListeProba#S
\ListeProg#S
\ListePyramide#S
\ListePyramidelen#S
\ListeQCM#S
\ListeQCMlen#S
\ListeQuestionColonneDeux#S
\ListeQuestionColonneDeuxlen#S
\ListeQuestionColonneUn#S
\ListeQuestionColonneUnlen#S
\ListeQuisuisje#S
\ListeQuisuisjeCode#S
\ListeQuisuisjelen#S
\ListeQuisuisjeLettres#S
\ListeQuisuisjeLettreslen#S
\ListeRadar#S
\ListeRapido#S
\ListeRapidolen#S
\ListeRatio#S
\ListeRatiolen#S
\ListeRelie#S
\ListeRelielen#S
\ListeRestante#S
\ListeRgt#S
\ListeSansDoublonsEE#S
\ListeSommetsCAN#S
\ListeSSDossiers#S
\ListeTempo#S
\ListeTotale#S
\ListeTotaleDesCaracteres#S
\ListeTraces#S
\ListeTriominos#S
\ListeValeur#S
\ListeValeurlen#S
\Logo{scale}{imagefile}#*g
\logobox#S
\LogoTW{scale}{imagefile}#*g
\longbarre#S
\longbarredepth#S
\longbarreheight#S
\LongListe#S
\LongueSimplification{arg1}{arg2}#S
\LongueurDecimale#S
\LongueurFracDeciDeno#S
\LongueurFracDeciNum#S
\LongueurMot#S
\LongueurNombreEntier#S
\LongueurPartieDecimale#S
\LongueurPartieEntiere#S
\margeh#S
\margev#S
\mathunderline{color}{arg}#S
\med#S
\meda#S
\MelangeListe{arg1}{arg2}#S
\MelangeListeNew{arg1}{arg2}#S
\mois#*
\MotifTexte#S
\MotsCodesMaLettre#S
\MoyenCote#S
\MPAfficheur{arg1}{arg2}{arg3}#S
\MPArbre{arg1}#S
\MPArbreComplet{arg1}#S
\MPArbreDessine{arg1}{arg2}#S
\MPArbreProba{arg1}{arg2}{arg3}{arg4}#S
\MPArbreVide{arg1}#S
\MPBillard{arg1}{arg2}{arg3}#S
\MPBillardSolution{arg1}{arg2}{arg3}#S
\MPCalculatrice{arg1}{arg2}{arg3}#S
\MPCinq{arg1}{arg2}{arg3}#S
\MPCourbe{arg1}{arg2}{arg3}{arg4}{arg5}#S
\MPCourbePoints{arg1}{arg2}{arg3}{arg4}{arg5}#S
\MPDessineFrise{arg}#S
\MPEchelleProbaUn{arg1}{arg2}{arg3}{arg4}#S
\MPEspacePave{arg1}{arg2}{arg3}{arg4}{arg5}#S
\MPEspaceSphere{arg1}{arg2}#S
\MPFigReciThales{arg1}{arg2}{arg3}{arg4}{arg5}#S
\MPFigReciThalesCroisee{arg1}{arg2}{arg3}{arg4}{arg5}#S
\MPFigThales{arg1}{arg2}{arg3}{arg4}{arg5}#S
\MPFigThalesCroisee{arg1}{arg2}{arg3}{arg4}{arg5}#S
\MPFigTrigo{arg1}{arg2}{arg3}{arg4}{arg5}#S
\MPFigTrigoAngle{arg1}{arg2}{arg3}{arg4}{arg5}#S
\MPFigureCarre#S
\MPFigureCercle#S
\MPFigureCone#S
\MPFigureCube#S
\MPFigureCylindre#S
\MPFigureDisque#S
\MPFigureDroite{arg1}{arg2}#S
\MPFigureLosange#S
\MPFigureLosangeAire#S
\MPFigureParallelogramme#S
\MPFigureParallelogrammeAire#S
\MPFigurePave#S
\MPFigurePolygone#S
\MPFigurePrisme#S
\MPFigurePyramide#S
\MPFigurePytha{arg1}{arg2}{arg3}{arg4}{arg5}#S
\MPFigurePythaSansMots{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}#S
\MPFigureReciPytha{arg1}{arg2}{arg3}{arg4}{arg5}#S
\MPFigureRectangle#S
\MPFigureSommeAngle{arg1}{arg2}{arg3}{arg4}{arg5}#S
\MPFigureSphere#S
\MPFigureTriangle#S
\MPFigureTriangleAire#S
\MPFonctionAffine{arg1}{arg2}{arg3}{arg4}{arg5}#S
\MPFractionDisque{arg1}{arg2}{arg3}{arg4}#S
\MPFractionDisqueH{arg1}{arg2}{arg3}{arg4}{arg5}#S
\MPFractionRectangle{arg1}{arg2}{arg3}{arg4}{arg5}#S
\MPFractionRectangleH{arg1}{arg2}{arg3}{arg4}{arg5}#S
\MPFractionRegulier{arg1}{arg2}{arg3}{arg4}{arg5}#S
\MPFractionRegulierH{arg1}{arg2}{arg3}{arg4}{arg5}#S
\MPFractionSegment{arg1}{arg2}{arg3}{arg4}#S
\MPFractionSegmentH{arg1}{arg2}{arg3}{arg4}{arg5}#S
\MPFractionTriangle{arg1}{arg2}{arg3}{arg4}{arg5}#S
\MPFractionTriangleH{arg1}{arg2}{arg3}{arg4}{arg5}#S
\MPGrille{arg1}{arg2}{arg3}{arg4}#S
\MPGrillePointe{arg1}{arg2}{arg3}{arg4}#S
\MPHorloge{arg1}{arg2}{arg3}#S
\MPIsometrique{arg1}{arg2}{arg3}#S
\MPIsometriquePointe{arg1}{arg2}{arg3}#S
\MPMillimetre{arg1}{arg2}{arg3}#S
\MPNewDEMIGraduee{arg1}{arg2}#S
\MPNewDROITEGraduee{arg1}{arg2}#S
\MPNewDROITEGradueeMulti{arg1}{arg2}#S
\MPPlacePoint{arg1}{arg2}#S
\MPPlannew{arg1}{arg2}{arg3}{arg4}{arg5}#S
\MPPlanTrace{arg1}{arg2}{arg3}{arg4}{arg5}#S
\MPRadar{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}#S
\MPSeyes{arg1}{arg2}{arg3}#S
\MPStat{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}{arg7}{arg8}#S
\MPStatCirculaireQ{arg1}{arg2}{arg3}{arg4}{arg5}#S
\MPStatNew{arg1}{arg2}#S
\MPStatQ{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}{arg7}{arg8}#S
\MPTest{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}{arg7}{arg8}{arg9}#S
\MPTestCours{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}{arg7}{arg8}{arg9}#S
\MPThermo{arg1}{arg2}#S
\MPTraceFonction{arg1}{arg2}#S
\MPTriangulaire{arg1}{arg2}{arg3}#S
\Multi#S
\Multij#S
\Multijo#S
\Multik#S
\Multiko#S
\Multil#S
\Multilo#S
\Multim#S
\Multimo#S
\Multio#S
\myoldmulticolumn#S
\NBcases#S
\NbColTabMul#S
\NbDepart#S
\NbDonnees#S
\nbdonnees#S
\NbHeures#S
\NbMinutes#S
\NbSecondes#S
\NbTrois#S
\NewMPDiagBarreHor{arg1}{arg2}{arg3}{arg4}#S
\NewMPStatCirculaireQ{arg1}{arg2}{arg3}{arg4}#S
\nil#S
\NomA#S
\NomAngleDroit#S
\NomB#S
\NombreCentaines#S
\NombreDizaines#S
\NombreMilliers#S
\NombrePremier{arg1}#S
\NombrePremierExposant{arg1}#S
\NombrePremierImpose{arg1}{arg2}{arg3}#S
\NombrePremierPotence{arg1}#S
\NombrePremierVertical{arg1}#S
\NombrePremierVerticalVide{arg1}#S
\NombreUnites#S
\NomC#S
\NomComp#S
\NomCouleurTab#S
\NomFin#S
\NomFonction#S
\NomFonctionA#S
\NomLargeurTab#S
\NomLettre#S
\NomM#S
\NomN#S
\NomNode#S
\NomPointA#S
\NomPointB#S
\NomPointC#S
\NomPointM#S
\NomPointN#S
\NomsMelanges#S
\NomSommetA#S
\NomSommetB#S
\NomSommetC#S
\NomStyle#S
\NomTriangle#S
\NomVariable#S
\Nomx#S
\Nomy#S
\Nomz#S
\NumA#S
\NumB#S
\NumC#S
\NumD#S
\numerateur#S
\NumerateurDiv#S
\Numerodelaquestionaposer#S
\numeroDonnee#S
\NumeroReponse#S
\NumSimp#S
\NumSimpa#S
\ObjetsMelanges#S
\octet#*
\OrdOrigine#S
\PapierBottom#S
\PapierCouleur#S
\PapierGrille#S
\PapierGrillePointe#S
\PapierHauteur#S
\PapierLargeur#S
\PapierLeft#S
\PapierLeftCurrent#S
\PartieDecimaleFractionDeci#S
\PartieEntiereFractionDeci#S
\PasNumEE#S
\PetitCote#S
\PfCAutreMoitieCase#S
\PfCBstrut#S
\PfCCalculsCroises#S
\PfCCBAffiche#S
\PfCCBAlea#S
\PfCCBDecompositionEtapes#S
\PfCCBListeCartes#S
\PfCCBListeEntiers#S
\PfCCBListeEntiersChoisis#S
\PfCCBListeFinaleCartes#S
\PfCCBListeMultiples#S
\PfCCBListeMultiplesChoisis#S
\PfCCBListeRappels#S
\PfCCBListeTirage#S
\PfCCBListeTirageAffiche#S
\PfCCBListeTirageIntermediaire#S
\PfCCBListeToutesCartes#S
\PfCCBNbPlaqueEntiers#S
\PfCCBNbPlaqueMultiples#S
\PfCCBResultat#S
\PfCCBResultatFinal#S
\PfCCBTest#S
\PfCCCFoo#S
\PfCCCfoo#S
\PfCchiffre{arg1}{arg2}#S
\PfCCoefConversion#S
\PfCCompteBonOriginal#S
\PfCCompteBonOriginal[opt]#S
\PfCCompteurMelange#S
\PfCCountCutDeux#S
\PfCCountCutUn#S
\PfCDerniereColonne#S
\PfCDerniereColonneEntiere#S
\PfCdotover#S
\PfCentoure{arg1}{arg2}#S
\PfCfiledate#S
\PfCfileversion#S
\PfCFooArrivee#S
\PfCFooDepart#S
\PfCFooRelatifYohaku#S
\PfCfooStat#S
\PfCfrac{arg1}{arg2}#S
\PfCGraineAlea#S
\PfCKakuro#S
\PfCKenKen#S
\PfCLargeurJury#S
\PfCLargeurQCM#S
\PfCLargeurQuestion#S
\PfCLargeurReponse#S
\PfCListeATrier#S
\PfCListeCCAide#S
\PfCListeCCAidelen#S
\PfCListeCCNb#S
\PfCListeCCOp#S
\PfCListeCmdTortue#S
\PfCListeHauteursCubes#S
\PfCListeRLE#S
\PfCListeSymbolTrivial#S
\PfCLongInter#S
\PfCMentaloDeuxiemeTerme#S
\PfCMentaloEtages#S
\PfCMentaloListeOperations#S
\PfCMentaloListeOperationslen#S
\PfCMentaloPremierTerme#S
\PfCMoitieCase#S
\PfCMPDessineModelBarre{arg1}{arg2}#S
\PfCMPDessineModelBarreNonHomogene{arg1}{arg2}#S
\PfCNACible#S
\PfCNAListeAEffacer#S
\PfCNAListeMelange#S
\PfCNAListeNombres#S
\PfCNAListeNombresBase#S
\PfCNbRep#S
\PfCNomLabyrinthe#S
\PfCNomRose#S
\PfCNomShikaku#S
\PfCNum{arg}#S
\PfCPCfaa#S
\PfCPCfoo#S
\PfCPremiereColonneDecimale#S
\PfCPythaUnit#S
\PfCQtroisk#S
\PfCQuartileTrois#S
\PfCQuartileUn#S
\PfCQunk#S
\PfCRappelImposeAll#S
\PfCShikakuh#S
\PfCShikakuv#S
\PfCTabCouleur#S
\PfCTableauDepart#S
\PfCTableauIncline#S
\PfCTableauPuissances#S
\PfCTableauUnite#S
\PfCTableurLargeur#S
\PfCTableurLargeurUn#S
\PfCTBstrut#S
\PfCTestBlack#S
\PfCTestEtoile#S
\PfCTestMP#S
\PfCThalesUnit#S
\PfCTotal#S
\PfCTrigoUnit#S
\PfCTstrut#S
\PfCVueCubeNom#S
\PfCYHKimpair#S
\PfCYHKlast#S
\PfCYHKListe#S
\PfCYHKListeFoo#S
\PfCYHKListeNA#S
\PfCYHKListeP#S
\PfCYHKListeProduit#S
\PfCYHKnegatif#S
\PfCYHKnombre#S
\PfCYHKpair#S
\PfCYHKTampon#S
\PfCYohaku#S
\PfCYohakuAlea#S
\PfCYohakuInter#S
\pgcd#S
\PGCD{arg1}{arg2}#S
\pileb#S
\Pointilles#S
\PointillesClesProg#S
\PotenceCases#S
\ppcm#S
\PPCM{arg1}{arg2}#S
\PQuatreGrille{arg1}{arg2}#S
\PQuatreListe#S
\PQuatreListeH#S
\PQuatreListes#S
\PQuatreListeV#S
\premier#S
\premierdeux#S
\PremierDiviseurVide{arg1}{arg2}#S
\PremierEtape{arg1}{arg2}#S
\PremierExposant{arg1}#S
\PremierLong{arg1}#S
\PremierMultipleVide{arg1}{arg2}#S
\premierun#S
\PtAlea#S
\pupils#*
\QCMPfC{arg1}{arg2}#S
\QFDaily#S
\QFDecimal#S
\QFExpression#S
\QFHeure#S
\QFMental#S
\QFMesure#S
\QFNumeration#S
\QFVide#S
\quintal#*
\ratiodomino#S
\RayonCoin#S
\Recapk#S
\Recapmed#S
\Recapmeda#S
\ReciproqueThales{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}{arg7}{arg8}#S
\ReciThales{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}#S
\ReciThalesCalculs{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}{arg7}{arg8}#S
\RecupererFichierTeXAllDossier{arg}#S
\RecupererFichierTeXAllSSDossier{arg}#S
\RecupererFichierTeXComplet{arg}#S
\RecupererFichierTeXDossier{arg}#S
\RecupererFichierTeXSSDossier{arg1}{arg2}#S
\RecupererFichierTeXSSDossierPerso{arg}#S
\RecupererSousDossiers{arg}#S
\Recupk#S
\Recupmed#S
\Recupmeda#S
\RecupNbFichiers#S
\RecupSSDossiers#S
\Redaction{arg1}{arg2}{arg3}{arg4}#S
\RedactionCalculsPythagore#S
\RedactionCalculsReciPythagore#S
\RedactionConclusionReciPythagore#S
\RedactionPythagore#S
\RedactionReciPythagore#S
\RedactionSom{arg1}{arg2}{arg3}{arg4}#S
\RedactionSomme#S
\RedactionThales#S
\RedactionTrigo#S
\ResolEquationCarre{arg1}{arg2}#S
\ResolEquationComposition{arg1}{arg2}{arg3}{arg4}{arg5}#S
\ResolEquationL{arg1}{arg2}{arg3}{arg4}{arg5}#S
\ResolEquationLaurent{arg1}{arg2}{arg3}{arg4}{arg5}#S
\ResolEquationProduit{arg1}{arg2}{arg3}{arg4}{arg5}#S
\ResolEquationSoustraction{arg1}{arg2}{arg3}{arg4}{arg5}#S
\ResolEquationSymbole{arg1}{arg2}{arg3}{arg4}{arg5}#S
\ResolEquationTerme{arg1}{arg2}{arg3}{arg4}{arg5}#S
\RetiensListeLieux#S
\RetiensListeLieuxlen#S
\RetiensListeObjets#S
\RetiensListeObjetslen#S
\RetiensListePersonnages#S
\RetiensListePersonnageslen#S
\RetiensListeQuestions#S
\RetiensListeQuestionslen#S
\rightcomment{arg1}{arg2}{arg3}{arg4}#*
\Rightcomment{arg1}{arg2}{arg3}{arg4}#S
\RKalmostcrying#*
\RKangry#*
\RKbigsmile#*
\RKblush#*
\RKconfused#*
\RKdevilish#*
\RKlookdown#*
\RKlookleft#*
\RKlookright#*
\RKlookup#*
\RKmartian#*
\RKneutral#*
\RKsad#*
\RKsexy#*
\RKsmallsmile#*
\RKsmile#*
\RoundedBoxWidth#S
\ShikakuCreation#S
\ShikakuCreationSolution#S
\SommeA#S
\sommeangle#S
\SommeB#S
\SommeC#S
\SommeDonnees#S
\SommetsMelanges#S
\Speed{nombre}#*
\speed{nombre}#*
\SSimpli{arg1}{arg2}#S
\SSimplifie{arg1}{arg2}#S
\SSimpliTest{arg1}{arg2}#S
\SymbolesMelanges#S
\TableAdditionComplete#S
\TableAdditionSeule{arg1}#S
\TableMultiplicationComplete#S
\TableMultiplicationCompleteColore#S
\TableMultiplicationSeule{arg1}#S
\TabLongueurNombre#S
\tabtoksa{arg}#S
\tabtoksb{arg}#S
\tabtoksc{arg}#S
\tabtoksEE{arg}#S
\tabtoksEEa{arg}#S
\tabtoksEEb{arg}#S
\TailleFonte#S
\Test#S
\Testa#S
\Testb#S
\TexteOrigine#S
\TexteReference#S
\theaddxlop#S
\theCNNumQ#S
\theCompteurMotEmpile#S
\thedivxlop#S
\themulxlop#S
\theNbCalculDistri#S
\theNbDistri#S
\theNbequa#S
\theNbFrac#S
\theNBprog#S
\theNbPropor#S
\theNbProporD#S
\theNbProporG#S
\theNbRelie#S
\thePfCCompteLignes#S
\thePfCnexo#S
\thePfCShikakuNom#S
\thePfCTortue#S
\theQuestionQCM#S
\thesubxlop#S
\theTitreQCM#S
\Tikzmark{arg1}#S
\TikzPB#S
\TikzPBD#S
\TikzPD#S
\TikzPG#S
\TikzPH#S
\TikzPHD#S
\TikzRB#S
\TikzRH#S
\toklisteaffhor{arg}#S
\toklistecaseM{arg}#S
\toklistecaseP{arg}#S
\toklistecouleur#S
\toklistedefdroites{arg}#S
\toklistedefligne{arg}#S
\toklistedonhor{arg}#S
\toklistefrise{arg}#S
\toklistelegende#S
\toklistemodelbarreinf#S
\toklistemodelbarresup#S
\toklisteNAMelange#S
\toklisteNANombres#S
\toklistenomhor{arg}#S
\toklistenompointdemidroite{arg}#S
\toklistePANombre#S
\toklistepoint{arg}#S
\toklistepointdemidroite{arg}#S
\toklistepointdroite{arg}#S
\toklistepointespace{arg}#S
\toklistepointproba{arg}#S
\toklistepointq{arg}#S
\toklistepointrepere{arg}#S
\toklistePQuatreh#S
\toklistePQuatrev#S
\toklistePtsFn{arg}#S
\toklisteptsgrad{arg}#S
\toklisteradara{arg}#S
\toklisteradarb{arg}#S
\toklisteradarc{arg}#S
\toklisteratio{arg}#S
\toklisteremplissage{arg}#S
\toklisterle#S
\toklistetracesgrad{arg}#S
\toklisteTriomino{arg}#S
\toklisteVueCube#S
\tokPfCCBRappels#S
\tokPfCEngrenages#S
\TortueCreationFichier[opt]{arg}#S
\TortueCreationFichier{arg}#S
\TortueDessinFinal#S
\totalangle#S
\TotalECC#S
\TotalLaby#S
\TotalP#S
\toto#S
\TraceDessinGradue{arg1}{arg2}{arg3}{arg4}#S
\TraceDessinGradueMul{arg1}#S
\TraceDessinGradueMulSolution{arg1}{arg2}{arg3}#S
\TraceDessinGradueSolution{arg1}{arg2}{arg3}{arg4}{arg5}#S
\TraceDoubleSolution{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}#S
\TraceEchiquierColoreColorilude#S
\TraceEchiquierColorilude#S
\TraceGraphique[opt]{arg}#S
\TraceGraphique{arg}#S
\TraceLabyFacto{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}#S
\TraceLabyFactoSolution{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}#S
\TraceLabyNombreDouble{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}#S
\TraceTriomino{arg1}#S
\TraceTriominoHexa{arg1}#S
\TrigoCalculs{arg1}{arg2}{arg3}{arg4}{arg5}#S
\TSimp#S
\TThales{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}{arg7}{arg8}#S
\TThalesCalculsD{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}{arg7}{arg8}#S
\TThalesCalculsE{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}{arg7}{arg8}#S
\TTThales{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}#S
\Tuile{arg1}{arg2}{arg3}{arg4}#S
\untest#S
\UpdateCoul{arg1}#S
\UpdateDefDroites{arg1}#S
\UpdateDefLignes{arg1}#S
\UpdateLegende{arg}#S
\UpdateLignes{arg1}#S
\UpdateListeModelBarreInf{arg}#S
\UpdateListeModelBarreSup{arg}#S
\UpdatePtsFN{arg1}#S
\UpdatePtsFn{arg1}#S
\UpdateRadara{arg1}#S
\UpdateRadarb{arg1}#S
\UpdateRadarc{arg1}#S
\UpdateRatio{arg1}#S
\updateratiotoks{arg1}#S
\UpdateRemplissage{arg1}#S
\Updatetoks{arg1}#S
\updatetoks{arg1}#S
\UpdatetoksCB{arg}#S
\Updatetoksdemidroite{arg1}#S
\Updatetoksdroite{arg1}#S
\UpdatetoksEngrenages#S
\Updatetoksespace{arg1}#S
\UpdatetoksFrise#S
\UpdatetoksHor#S
\Updatetoksmath{arg1}#S
\UpdatetoksMosaique{arg1}#S
\UpdatetoksNAMelange{arg}#S
\UpdatetoksNANombres{arg}#S
\UpdatetoksPANombre{arg}#S
\UpdatetoksPQuatreh{arg}#S
\UpdatetoksPQuatrev{arg}#S
\Updatetoksproba{arg1}#S
\Updatetoksprobaechelle{arg1}#S
\Updatetoksprobapdf{arg}#S
\updatetokspropor#S
\UpdatetoksPyramide{arg1}#S
\UpdatetoksPyramideMul{arg}#S
\Updatetoksq{arg1}#S
\Updatetoksrepere{arg1}#S
\UpdatetoksRLE{arg}#S
\UpdatetoksTriomino{arg1}#S
\UpdatetoksVueCube{arg}#S
\UpdateTraces{arg1}#S
\valabsdeno#S
\valabsnum#S
\ValeurEchange#S
\ValeurTest#S
\Verification{arg1}{arg2}{arg3}{arg4}{arg5}#S
\WidthRapido#S
\xcnt#S
\xxx#S
\yyy#S
\zzpar#S
\zzz#S
