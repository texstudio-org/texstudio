# ProfMaquette package
# Matthew Bertucci 2023/06/05 for v0.15

#include:verbatim
#include:calc
#include:xlop
#include:tcolorbox
#include:tcolorboxlibrarymost
#include:varwidth
#include:xinttools
#include:listofitems
#include:array
#include:datatool
#include:simplekv

\begin{Maquette}{clés%keyvals}
\begin{Maquette}[type]{clés%keyvals}
\end{Maquette}

# repeats for each type not listed
#keyvals:\begin{Maquette}
# type DM
Numero=%<numero%>
Date=%<date%>
Classe=%<texte%>
Niveau=%<nombre%>
Code=%<code%>
# type DS
Calculatrice#true,false
Sujet=%<texte%>
# type IE
Theme=%<texte%>
Nom=%<texte%>
# type Fiche
NomExercice=%<texte%>
# type Parcours
# no new keys
# type PdT
# no new keys
# type ParcoursPerso
Fichier=%<.csv file%>
#endkeyvals

\TikzDM#*
\TikzDMCor{clés}#*
\TikzDS#*
\TikzDSCor{clés}#*
\TikzIE#*
\TikzIECor{clés}#*
\TikzFiche#*
\TikzFicheCor{clés}#*
\TikzParcours#*
\TikzParcoursCor{clés}#*
\TikzPdT#*
\TikzPdTCor{clés}#*

\Competences{texte1/texte2/...%text}
\Competences[N]{col1§...§colN/texte1/texte2/...%text}

\PfMCompNA#*
\PfMCompECA#*
\PfMCompA#*

\begin{exercice}
\begin{exercice}[clés%keyvals]
\end{exercice}

#keyvals:\begin{exercice}
BaremeTotal#true,false
BaremeDetaille#true,false
MotPoint=%<texte%>
Source=%<texte%>
Titre=%<texte%>
Competence=%<texte%>
Oral#true,false
Calculatrice#true,false
Trajet={%<parcour1,parcour2,...%>}
PasCorrige#true,false
Pouce#true,false
Direct#true,false
#endkeyvals

\brm{nombre}

\AfficheParcours{parcour}
\AfficheParcours[clés%keyvals]{parcour}#*

\begin{SOS}
\end{SOS}
\CheminVrai{noeud départ/noeud arrivée}
\CheminFaux{noeud départ/noeud arrivée}

\begin{Solution}
\end{Solution}
\begin{Reponse}
\end{Reponse}
\begin{Indice}
\end{Indice}

# not documented
\begin{CRNote}#S
\begin{CRRemarque}#S
\begin{exerciceBase}#S
\begin{exerciceBase}[clés%keyvals]#S
\begin{exerciceBaseHTML}#S
\begin{exerciceBaseHTML}[clés%keyvals]#S
\begin{exerciceDM}#S
\begin{exerciceDM}[clés%keyvals]#S
\begin{exerciceDS}#S
\begin{exerciceDS}[clés%keyvals]#S
\begin{exerciceFiche}#S
\begin{exerciceFiche}[clés%keyvals]#S
\begin{exerciceKholle}#S
\begin{exerciceKholle}[clés%keyvals]#S
\begin{exerciceParcours}#S
\begin{exerciceParcours}[clés%keyvals]#S
\begin{exercicePdT}#S
\begin{exercicePdT}[clés%keyvals]#S
\begin{ExerciceRecapBrevet}#S
\begin{ExerciceRecapBrevet}[clés%keyvals]#S
\Brm{arg}#S
\brouillon#S
\BuildParcoursTikz{arg1}{arg2}#S
\BuildParcoursTikzV{arg1}{arg2}#S
\buildtabcompetences#S
\Buildtabcompetences{arg1}{arg2}#S
\CRRHauteur#S
\definelist{cmd}{def}#Sd
\end{CRNote}#S
\end{CRRemarque}#S
\end{exerciceBase}#S
\end{exerciceBaseHTML}#S
\end{exerciceDM}#S
\end{exerciceDS}#S
\end{exerciceFiche}#S
\end{exerciceKholle}#S
\end{exerciceParcours}#S
\end{exercicePdT}#S
\end{ExerciceRecapBrevet}#S
\endexerciceParcoursPerso#S
\endIndiceNow#S
\endIndiceWrite#S
\endReponseNow#S
\endReponseWrite#S
\endSolutionNow#S
\endSolutionWrite#S
\endSolutionWritePP#S
\exerciceParcoursPerso#S
\extract{arg1}{arg2}{arg3}#S
\FranPt{arg}#S
\GazSerreEu#S
\getalpha#S
\getcarre#S
\getGazSerre#S
\gethepta#S
\gethexa#S
\getnonna#S
\getocto#S
\getpenta#S
\getpremier#S
\getPremier#S
\getpytha#S
\getquad#S
\gettreize#S
\gettri#S
\GetValeurDe{arg}#S
\getVehiculesINSEE#S
\getwidth{arg1}{arg2}#S
\IndiceNow#S
\IndiceWrite#S
\initalpha#S
\initcarre#S
\initEnsemblede#S
\initpremiers#S
\initPremiers#S
\initrandomlist[opt]{arg}#S
\initrandomlist{arg}#S
\initsommet#S
\initsommetrep#S
\NoteFinale#S
\NoteTotale#S
\Orientation#S
\PfMAffichageCorrige#S
\PfMChoixAffichageCorrection#S
\PfMChoixCorrection#S
\PfMfiledate#S
\PfMfileversion#S
\PfMHauteurAppreciation#S
\PfMHauteurRemarque#S
\PfMIEClasse#S
\PfMIENom#S
\PfMIEPrenom#S
\PfMLargeurComp#S
\PfMLargeurSchemaParcours#S
\pop{arg1}{arg2}#S
\push{arg1}{arg2}#S
\quadruplets#S
\Quadruplets#S
\randomextract{arg1}{arg2}#S
\randomlistcompile#S
\randomlistseed#S
\Recapitulatif{arg}#S
\RecapitulatifCorrection{arg}#S
\RemplisParcours{arg}#S
\ReponseNow#S
\ReponseWrite#S
\SolutionNow#S
\SolutionWrite#S
\SolutionWritePP#S
\TableauRecapitulatif#S
\theMaquette#S
\thePfMAlea#S
\thePfMCorrigeParcoursPerso#S
\thePfMExo#S
\thePfMNbLogo#S
\thePfMSOS#S
\theRetiensInd#S
\theRetiensRep#S
\theRetiensSol#S
\TikzKholle#S
\TikzKholleCor{arg}#S
\TikzRecapBrevet#S
\TikzRecapBrevetCor{arg}#S
\total{arg}#S
\tripletspytha#S
\tripletspythaentier#S
\VehiculesINSEE#S

# from random.tex
\randomi#S
\nextrandom#S
\setrannum{count register}{min}{max}#S
\setrandim{dimen register}{min}{max}#S
\pointless#S
\PoinTless#S
\ranval#S