# rank-2-roots package
# Matthew Bertucci 9/10/2021 for v1.0

#include:tikz
#include:xstring
#include:etoolbox
#include:pgfkeys
#include:pgfopts
#include:tikzlibrarycalc
#include:tikzlibrarydecorations.markings
#include:tikzlibrarypositioning
#include:tikzlibraryfadings
#include:tikzlibrarybackgrounds
#include:tikzlibrarydecorations.pathreplacing
#include:tikzlibraryshadings
#include:tikzlibraryfadings

\begin{rootSystem}{type%keyvals}
\end{rootSystem}

#keyvals:\begin{rootSystem}
A
B
C
G
#endkeyvals

\roots#/rootSystem
\roots[TikZ options]#/rootSystem
\wt{x}{y}#/rootSystem
\wt[TikZ options%keyvals]{x}{y}#/rootSystem
\hexwt{x}{y}#*/rootSystem
\hexwt[TikZ options%keyvals]{x}{y}#*/rootSystem
\squarewt{x}{y}#*/rootSystem
\squarewt[TikZ options%keyvals]{x}{y}#*/rootSystem

#keyvals:\wt#c,\hexwt#c,\squarewt#c
multiplicity=%<integer%>
root
%color
#endkeyvals

\WeylChamber#/rootSystem
\WeylChamber[TikZ options]#/rootSystem
\positiveRootHyperplane#/rootSystem
\positiveRootHyperplane[TikZ options]#/rootSystem
\parabolic{integer}#/rootSystem
\parabolic[TikZ options]{integer}#/rootSystem
\parabolicgrading#/rootSystem
\weightLattice{integer}#/rootSystem
\weightLattice[TikZ options]{integer}#/rootSystem
\weight{x}{y}#/rootSystem
\hexgrid{lattice size}#*/rootSystem
\hexgrid[TikZ options]{lattice size}#*/rootSystem
\hexclip#*/rootSystem

\weightLength#*
\weightRadius#*
\gradingDot#*
\defaultWeightLatticeSize#*
\ifAutoSizeWeightLattice#*
\AutoSizeWeightLatticetrue#*
\AutoSizeWeightLatticefalse#*
