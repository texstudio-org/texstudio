# tkz-bernoulli package
# Matthew Bertucci 2023/10/10 for v0.1.1

#include:tikz
#include:pgffor
#include:xstring
#include:simplekv
#include:xintexpr
#include:xintbinhex
#include:tikzlibrarycalc

\tkzSchemBernoulli
\tkzSchemBernoulli[clés%keyvals]
\tkzSchemBernoulli<options TikZ>
\tkzSchemBernoulli[clés%keyvals]<options TikZ>
\tkzSchemBernoulli*
\tkzSchemBernoulli*[clés%keyvals]
\tkzSchemBernoulli*<options TikZ>
\tkzSchemBernoulli*[clés%keyvals]<options TikZ>
\tkzEpreuvBernoulli
\tkzEpreuvBernoulli[clés%keyvals]
\tkzEpreuvBernoulli*
\tkzEpreuvBernoulli*[clés%keyvals]

#keyvals:\tkzSchemBernoulli,\tkzSchemBernoulli*,\tkzEpreuvBernoulli,\tkzEpreuvBernoulli*
EspNiv=%<nombre%>
EspFeuil=%<nombre%>
Evts=%<Succès/Échec%>
Probas=%<probabilités%>
Grille#true,false
AffProbas#true,false
Racine=%<nom%>
Aide#true,false
Notice#true,false
Var=%<nom%>
N=%<nombre%>
#endkeyvals

\tkzSchemBernStyleDefaut#*

\tkzBernoulliTree
\tkzBernoulliTree[keyvals]
\tkzBernoulliTree<TikZ options>
\tkzBernoulliTree[keyvals]<TikZ options>
\tkzBernoulliTree*
\tkzBernoulliTree*[keyvals]
\tkzBernoulliTree*<TikZ options>
\tkzBernoulliTree*[keyvals]<TikZ options>
\tkzBernoulliTrial
\tkzBernoulliTrial[keyvals]
\tkzBernoulliTrial*
\tkzBernoulliTrial*[keyvals]

#keyvals:\tkzBernoulliTree,\tkzBernoulliTree*,\tkzBernoulliTrial,\tkzBernoulliTrial*
LevelSep=%<number%>
NodeSep=%<number%>
Events=
Probs=
Grid#true,false
ShowProbs#true,false
Root=%<name%>
Help#true,false
Guide#true,false
Var=%<name%>
N=%<number%>
#endkeyvals

\tkzBernTreeStyleDefault#*
