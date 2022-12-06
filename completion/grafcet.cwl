# grafcet package
# Matthew Bertucci 12/26/2021 for v1.3.5

#include:ifsym
#include:ifthen
#include:tikz
#include:tikzlibraryshapes

\Etape{nom}
\Etape[pos]{nom}
\EtapeInit{nom}
\EtapeInit[pos]{nom}
\EtapeActive{nom}
\MacroEtape{nom}
\MacroEtape[pos]{nom}
\MacroEtapeE{nom}
\MacroEtapeE[pos]{nom}
\MacroEtapeS{nom}
\MacroEtapeS[pos]{nom}
\EtapeEncapsulante{nom}
\EtapeEncapsulante[pos]{nom}
\EtapeEncapsulanteInit{nom}
\EtapeEncapsulanteInit[pos]{nom}
\LienActivation{nom}
\begin{Encap}{pos}{etape}{Grafcet}
\begin{Encap}[nom]{pos}{etape}{Grafcet}
\end{Encap}
\Transition{nom}
\Transition[pos]{nom}
\Recept{T%<nnn%>}{%<condition%>}
\Recepts{1/r1,2/r2,...}
\TransitionSource{nom}
\TransitionSource[pos]{nom}
\TransitionPuits{nom}
\TransitionPuits[pos]{nom}
\TransitionRecept{nom}{condition}
\TransitionRecept[pos]{nom}{condition}
\ActionX{X%<nnn%>}{%<action%>}
\ActionX[%<dist%>]{X%<nnn%>}{%<action%>}
\Action{X%<nnn%>}{%<action%>}
\ActionCond{X%<nnn%>}{%<condition%>}
\ActionActiv{X%<nnn%>}
\ActionDesactiv{X%<nnn%>}
\ActionEvenement{X%<nnn%>}{%<condition%>}
\ActionFranchissement{T%<nnn%>}{%<action%>}
\ActionXV{etape}{liste actions}
\ActionXV[dist]{etape}{liste actions}
\Actions{1/A1,2/A2,...}
\ForcageX{X%<nnn%>}{%<forçage%>}
\ForcageXV{etape}{liste forçage}
\ForcageXV[dist]{etape}{liste forçage}
\EtapeTransition{nom}{action}{recept}
\EtapeTransition[pos]{nom}{action}{recept}
\EtapeInitTransition{nom}{action}{recept}
\EtapeInitTransition[pos]{nom}{action}{recept}
\SequenceET{liste}
\SequenceET[pos]{liste}
\SequenceEE{liste}{derniere etape}
\SequenceEE[pos]{liste}{derniere etape}
\SequenceTE{nom trans}{liste}{derniere etape}
\SequenceTE[pos]{nom trans}{liste}{derniere etape}
\SequenceTT{trans init}{liste}
\SequenceTT[pos]{trans init}{liste}
\ActionRecept{1/A1/r1,2/A2/r2,...}
\Graphe{1/A1/r1,2/A2/r2,...}
\Graphe[pos]{1/A1/r1,2/A2/r2,...}
\GrapheBoucle{1/A1/r1,2/A2/r2,...}
\GrapheBoucle[pos]{1/A1/r1,2/A2/r2,...}
\DivOU{X%<nnn%>}{%<d1/nom1,d2/nom2,...%>}
\ConvOU{T%<nnn%>}{%<liste%>}{%<nom%>}
\ConvOU[%<dist%>]{T%<nnn%>}{%<liste%>}{%<nom%>}
\SautEtapes{X%<nnn%>}{%<liste%>}{%<nom%>}
\SautEtapes[%<dist%>]{X%<nnn%>}{%<liste%>}{%<nom%>}
\RepriseEtapes{T%<nnn%>}{%<liste%>}{%<nom%>}
\RepriseEtapes[%<dist%>]{T%<nnn%>}{%<liste%>}{%<nom%>}
\DeplaceNoeudx{ni}{nf}
\DeplaceNoeudx[dist]{ni}{nf}
\DeplaceNoeudy{ni}{nf}
\DeplaceNoeudy[dist]{ni}{nf}
\DecaleNoeudx{ni}{nf}
\DecaleNoeudx[dist]{ni}{nf}
\DecaleNoeudy{ni}{nf}
\DecaleNoeudy[dist]{ni}{nf}
\DivET{T%<nnn%>}{%<d1/br1,d2/br2,...%>}
\ConvET{T%<nnn%>}{%<liste%>}{%<nom%>}
\ConvET[%<dist%>]{T%<nnn%>}{%<liste%>}{%<nom%>}
\LienRetour{T%<nnn%>}{X%<nnn%>}
\LienRetour[%<dist%>]{T%<nnn%>}{X%<nnn%>}
\Lien{NoeudGraf}{noeud2}{noeud3}
\Lien[dist]{NoeudGraf}{noeud2}{noeud3}
\LienET{X%<nnn%>}
\LienET[%<long%>]{X%<nnn%>}
\LienTE{X%<nnn%>}
\LienTE[%<long%>]{X%<nnn%>}
\Comment{pos}{commentaire}
\Comment[dist]{pos}{commentaire}

# not documented
\ActionEfface[opt]{arg1}#S
\BrancheOU[opt]{arg1}#S
\CadreEncap{arg1}{arg2}{arg3}{arg4}#S
\EspaceV[opt]{arg1}#S
\EtapeAction[opt]{arg1}{arg2}#S
\EtapeInitAction[opt]{arg1}{arg2}#S
\EtapeSeule[opt]{arg1}#S
\FinBrancheOU[opt]{arg1}{arg2}#S
\FinBrancheOUa[opt]{arg1}{arg2}#S
\Forcage[opt]{arg1}{arg2}#S
\LienRetourN[opt]{arg1}{arg2}#S
\LienRetourOU[opt]{arg1}{arg2}#S
\LienRetourUp[opt]{arg1}{arg2}{arg3}#S
\LienRetoura[opt]{arg1}{arg2}#S
\encap#S
\nometape#S
\nomgraphe#S
