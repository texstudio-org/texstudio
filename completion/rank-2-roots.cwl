# rank-2-roots package
# Matthew Bertucci 9/10/2021 for v1.0

#include:tikz
#include:xparse
#include:xstring
#include:etoolbox
#include:expl3
#include:pgfkeys
#include:pgfopts

\begin{rootSystem}{type%keyvals}
\end{rootSystem}

#keyvals:\begin{rootSystem}
A
B
C
G
#endkeyvals

\roots#/rootSystem
\wt{x}{y}#/rootSystem
\wt[options%keyvals]{x}{y}#/rootSystem

#keyvals:\wt#c
multiplicity=%<integer%>
root
#endkeyvals

\WeylChamber#/rootSystem
\positiveRootHyperplane#/rootSystem
\parabolic{integer}#/rootSystem
\parabolicgrading#/rootSystem
\weightLattice{integer}#/rootSystem
\weight{x}{y}#/rootSystem

\weightLength#*
\weightRadius#*
\AutoSizeWeightLatticetrue#*
\AutoSizeWeightLatticefalse#*