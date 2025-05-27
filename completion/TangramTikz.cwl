# TangramTikz package
# Matthew Bertucci 2025/05/27 for v0.2.2

#include:tikz
#include:simplekv
#include:xstring
#include:listofitems
#include:tikzlibrarycalc
#include:tikzlibraryshapes.geometric

\begin{EnvTangramTikz}#\pictureHighlight
\begin{EnvTangramTikz}[options%keyvals]
\begin{EnvTangramTikz}[options%keyvals]<TikZ options>
\end{EnvTangramTikz}
\TangramTikz{tangram name}
\TangramTikz<TikZ options>{tangram name}
\TangramTikz[options%keyvals]{tangram name}
\TangramTikz[options%keyvals]<TikZ options>{tangram name}

#keyvals:\begin{EnvTangramTikz},\TangramTikz
Puzzle#true,false
Correction#true,false
Color=#%color
Couleur=#%color
Solution#true,false
ColorSolution#true,false
CorrectionCouleur#true,false
ColorList={%<color1,color2,...%>}
ListeCouleurs={%<couleur1,couleur2,...%>}
Sep=##L
NoirBlanc
BlackWhite
#endkeyvals

\PieceTangram[options%keyvals](x,y){piece name}
\PieceTangram[options%keyvals]<TikZ options>(x,y){piece name}

#keyvals:\PieceTangram#c
TangPuzz
TangPuzz={%<color%>}
TangSol
TangSol={%<color%>}
#endkeyvals

\TangramTikzHelp
\TangramTikzHelp<TikZ keys>
\TangramTikzHelp[keyvals]
\TangramTikzHelp[keyvals]<TikZ keys>
\TangramTikzAide
\TangramTikzAide<TikZ keys>
\TangramTikzAide[keyvals]
\TangramTikzAide[keyvals]<TikZ keys>
