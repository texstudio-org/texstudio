# schemabloc package
# Matthew Bertucci 2023/10/04 for v1.9

#include:ifthen
#include:tikz
#include:tikzlibraryshapes
#include:tikzlibrarypositioning
#include:tikzlibraryfit

\sbStyleLienDefaut
\sbStyleLien{options}
\sbStyleBloc{options}
\sbStyleBlocDefaut
\sbEntree{nom}
\sbEntree[at]{nom}#S
\sbSortie{nom}{bloc-nom}
\sbSortie[distance]{nom}{bloc-nom}
\sbBloc{nom}{contenu}{bloc precédent}
\sbBloc[distance]{nom}{contenu}{bloc précédent}
\sbBlocr{nom}{contenu}{bloc precédent}
\sbBlocr[distance]{nom}{contenu}{bloc précédent}
\sbBlocL{nom}{contenu}{bloc precédent}
\sbBlocL[distance]{nom}{contenu}{bloc précédent}
\sbBlocrL{nom}{contenu}{bloc precédent}
\sbBlocrL[distance]{nom}{contenu}{bloc précédent}
\sbBlocseul{nom}{contenu}{bloc precédent}
\sbBlocseul[distance]{nom}{contenu}{bloc précédent}
\sbRelier{b1}{b2}
\sbRelier[nom]{b1}{b2}
\sbRelieryx{nom1}{nom2}
\sbRelierxy{bloc-nom}{comp-nom}
\sbRelierxy[label]{bloc-nom}{comp-nom}
\sbRenvoi{nom1}{nom2}{label}
\sbRenvoi[distance]{nom1}{nom2}{label}
\sbNomLien{nom}{label}
\sbNomLien[distance]{nom}{label}
\sbCompSum{nom}{E1}{a}{b}{c}{d}
\sbCompSum[distance]{nom}{E1}{a}{b}{c}{d}
\sbCompSumr{nom}{E1}{a}{b}{c}{d}
\sbCompSumr[distance]{nom}{E1}{a}{b}{c}{d}
\sbComp{nom}{bloc précédent}
\sbComp[distance]{nom}{bloc précédent}
\sbComp*{nom}{bloc précédent}
\sbComp*[distance]{nom}{bloc précédent}
\sbCompr{nom}{bloc précédent}
\sbCompr[distance]{nom}{bloc précédent}
\sbCompr*{nom}{bloc précédent}
\sbCompr*[distance]{nom}{bloc précédent}
\sbCompL{nom}{bloc précédent}
\sbCompL[distance]{nom}{bloc précédent}
\sbCompL*{nom}{bloc précédent}
\sbCompL*[distance]{nom}{bloc précédent}
\sbComph{nom}{bloc précédent}
\sbComph[distance]{nom}{bloc précédent}
\sbComph*{nom}{bloc précédent}
\sbComph*[distance]{nom}{bloc précédent}
\sbSumh{nom}{bloc précédent}
\sbSumh[distance]{nom}{bloc précédent}
\sbSumh*{nom}{bloc précédent}
\sbSumh*[distance]{nom}{bloc précédent}
\sbSumb{nom}{bloc précédent}
\sbSumb[distance]{nom}{bloc précédent}
\sbSumb*{nom}{bloc précédent}
\sbSumb*[distance]{nom}{bloc précédent}
\sbDecaleNoeudy{N1}{N2}
\sbDecaleNoeudy[distance]{N1}{N2}
\sbDecaleNoeudx{N1}{N2}
\sbDecaleNoeudx[distance]{N1}{N2}
\sbChaine{noeud depart}{liste blocs nom/Fonction}
\sbChaine[pas]{noeud depart}{liste blocs nom/Fonction}
\sbChaineRetour{noeud depart}{liste blocs nom/Fonction}
\sbChaineRetour[pas]{noeud depart}{liste blocs nom/Fonction}
\sbBoucleSeule{noeud depart}{liste blocs}{sortie}
\sbBoucleSeule[pas]{noeud depart}{liste blocs}{sortie}
\sbBoucle{noeud depart}{liste blocs chaine directe}
\sbBoucle[pas]{noeud depart}{liste blocs chaine directe}
\sbBoucleRetour{noeud depart}{liste chaine directe}{liste chaine de retour}
\sbBoucleRetour[pas]{noeud depart}{liste chaine directe}{liste chaine de retour}


# not documented
\sbStyleSum{options}#S
\sbStyleSumDefaut#S
\sbEntrees{nom}#S
\sbEntrees[at]{nom}#S
\sbSortieL{nom}{bloc-nom}#S
\sbSortieL[distance]{nom}{bloc-nom}#S
\sbBlocPatate{nom}{contenu}{bloc precédent}#S
\sbBlocPatate[distance]{nom}{contenu}{bloc precédent}#S
\sbCompSumUsuel{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}#S
\sbCompSumUsuel[opt]{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}#S
\sbCompSumUsuelr{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}#S
\sbCompSumUsuelr[opt]{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}#S
\sbCompSumNorm{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}#S
\sbCompSumNorm[opt]{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}#S
\sbCompSumNormr{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}#S
\sbCompSumNormr[opt]{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}#S
\sbSum{arg1}{arg2}{arg3}{arg4}{arg5}#S
\sbSum[opt]{arg1}{arg2}{arg3}{arg4}{arg5}#S
\sbCompUsuel{arg1}{arg2}#S
\sbCompUsuel[opt]{arg1}{arg2}#S
\sbCompNorm{arg1}{arg2}#S
\sbCompNorm[opt]{arg1}{arg2}#S
\sbCompUsuelr{arg1}{arg2}#S
\sbCompUsuelr[opt]{arg1}{arg2}#S
\sbCompNormr{arg1}{arg2}#S
\sbCompNormr[opt]{arg1}{arg2}#S
\sbCompUsuelL{arg1}{arg2}#S
\sbCompUsuelL[opt]{arg1}{arg2}#S
\sbCompNormL{arg1}{arg2}#S
\sbCompNormL[opt]{arg1}{arg2}#S
\sbCompUsuelLr{arg1}{arg2}#S
\sbCompUsuelLr[opt]{arg1}{arg2}#S
\sbCompNormLr{arg1}{arg2}#S
\sbCompNormLr[opt]{arg1}{arg2}#S
\sbComphUsuel{arg1}{arg2}#S
\sbComphUsuel[opt]{arg1}{arg2}#S
\sbComphNorm{arg1}{arg2}#S
\sbComphNorm[opt]{arg1}{arg2}#S
\sbComphUsuelr{arg1}{arg2}#S
\sbComphUsuelr[opt]{arg1}{arg2}#S
\sbComphNormr{arg1}{arg2}#S
\sbComphNormr[opt]{arg1}{arg2}#S
\sbSumhUsuel{arg1}{arg2}#S
\sbSumhUsuel[opt]{arg1}{arg2}#S
\sbSumhNorm{arg1}{arg2}#S
\sbSumhNorm[opt]{arg1}{arg2}#S
\sbSumhUsuelr{arg1}{arg2}#S
\sbSumhUsuelr[opt]{arg1}{arg2}#S
\sbSumhNormr{arg1}{arg2}#S
\sbSumhNormr[opt]{arg1}{arg2}#S
\sbSumbUsuel{arg1}{arg2}#S
\sbSumbUsuel[opt]{arg1}{arg2}#S
\sbSumbNorm{arg1}{arg2}#S
\sbSumbNorm[opt]{arg1}{arg2}#S
\sbSumbUsuelr{arg1}{arg2}#S
\sbSumbUsuelr[opt]{arg1}{arg2}#S
\sbSumbNormr{arg1}{arg2}#S
\sbSumbNormr[opt]{arg1}{arg2}#S
\sbCompLr{arg1}{arg2}#S
\sbCompLr[opt]{arg1}{arg2}#S
\sbCompLr*{arg1}{arg2}#S
\sbCompLr*[opt]{arg1}{arg2}#S
\sbComphr{arg1}{arg2}#S
\sbComphr[opt]{arg1}{arg2}#S
\sbComphr*{arg1}{arg2}#S
\sbComphr*[opt]{arg1}{arg2}#S
\sbSumhr{arg1}{arg2}#S
\sbSumhr[opt]{arg1}{arg2}#S
\sbSumhr*{arg1}{arg2}#S
\sbSumhr*[opt]{arg1}{arg2}#S
\sbSumbr{arg1}{arg2}#S
\sbSumbr[opt]{arg1}{arg2}#S
\sbSumbr*{arg1}{arg2}#S
\sbSumbr*[opt]{arg1}{arg2}#S
\sbDecaleNoeudyZ{arg1}{arg2}#S
\sbDecaleNoeudyZ[opt]{arg1}{arg2}#S
\sbDecaleNoeudxy{arg1}{arg2}{arg3}{arg4}#S
\sbChaineComp{arg1}{arg2}#S
\sbChaineComp[opt]{arg1}{arg2}#S