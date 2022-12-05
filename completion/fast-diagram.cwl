# fast-diagram package
# Matthew Bertucci 4/14/2022 for v1.1

#include:tikz
#include:ifthen
#include:relsize
#include:xargs
#include:tikzlibrarycalc
#include:tikzlibraryfit
#include:tikzlibraryshapes

#keyvals:\usepackage/fast-diagram#c
raccourcis
#endkeyvals

#ifOption:raccourcis
\FT{Fonction technique%text}{Descendance%text}
\FT[option%keyvals]{Fonction technique%text}{Descendance%text}
\ST{Solution technique%text}
\ST{Solution technique%text}[Descendance%text]
\ST[option%keyvals]{Solution technique%text}
\ST[option%keyvals]{Solution technique%text}[Descendance%text]
\FV{text}
\FV{text}[Descendance%text]
\trait{Descendance%text}
#endif

\begin{fast}{Fonction de Service%text}#\pictureHighlight
\end{fast}

\fastFT{Fonction technique%text}{Descendance%text}
\fastFT[option%keyvals]{Fonction technique%text}{Descendance%text}
\fastST{Solution technique%text}
\fastST{Solution technique%text}[Descendance%text]
\fastST[option%keyvals]{Solution technique%text}
\fastST[option%keyvals]{Solution technique%text}[Descendance%text]

#keyvals:\fastFT,\fastST,\FT,\ST,\fastTraceConnecteurs
tempo
ou
#endkeyvals

\fastVide{text}
\fastVide{text}[Descendance%text]
\fastTrait{Descendance%text}
\fastReset

\fastInterligne#*
\fastLargeurBoite#*
\fastHauteurBoite#*
\fastEspaceColonne#*
\fastDecalageTrait#*
\fastEpaisseurTraits#*
\fastDecalageOuVertical#*
\fastDecalageOuHorizontal#*

fastCouleurTexteFS#B
fastCouleurBorduresFS#B
fastCouleurFondFS#B
fastCouleurTexteFT#B
fastCouleurBorduresFT#B
fastCouleurFondFT#B
fastCouleurTexteST#B
fastCouleurBorduresST#B
fastCouleurFondST#B
fastCouleurTexteFV#B
fastCouleurConnecteurs#B

\fastSetCouleurBordures{color}
\fastSetCouleurBordures[type]{color%plain}
\fastSetCouleurTexte{color}
\fastSetCouleurTexte[type]{color%plain}
\fastSetCouleurFond{color}
\fastSetCouleurFond[type]{color%plain}
\fastSetCouleurConnecteurs{color}
\fastSetCouleurConnecteurs[type]{color%plain}
\fastSetCouleurTraits{color}
\fastSetCouleurTraits[type]{color%plain}

\fastAvanceColonne#*
\fastEnregistreMinimum#*
\fastFSStyle#*
\fastFSarrondi#*
\fastFStexteStyle#*
\fastFTStyle#*
\fastFTarrondi#*
\fastFTtexteStyle#*
\fastFVStyle#*
\fastFVtexteStyle#*
\fastReculeColonne#*
\fastSTStyle#*
\fastSTarrondi#*
\fastSTtexteStyle#*
\fastTraceConnecteurs#*
\fastTraceConnecteurs[option%keyvals]#*
\posX#*
\thecptAbscisse#*
\thecptAbscisseParent#*
\thecptBoite#*
\ttt#*
