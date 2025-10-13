# atableau package
# Matthew Bertucci 2025/10/13 for v2.2.0

#include:tikz
#include:tikzlibrarymatrix
#include:tikzlibraryshapes.geometric
#include:tikzlibraryshapes.misc
#include:amsfonts

\Abacus{number of runners}{bead spec}
\Abacus[options%keyvals]{number of runners}{bead spec}
\Abacus(x,y){number of runners}{bead spec}
\Abacus(x,y)[options%keyvals]{number of runners}{bead spec}
\Diagram{partition spec}
\Diagram[options%keyvals]{partition spec}
\Diagram(x,y){partition spec}
\Diagram(x,y)[options%keyvals]{partition spec}
\Multidiagram{multipartition spec}
\Multidiagram[options%keyvals]{multipartition spec}
\Multidiagram(x,y){multipartition spec}
\Multidiagram(x,y)[options%keyvals]{multipartition spec}
\Multitableau{multitableau spec}
\Multitableau[options%keyvals]{multitableau spec}
\Multitableau(x,y){multitableau spec}
\Multitableau(x,y)[options%keyvals]{multitableau spec}
\NewATableauCommand{command}{type}{options%keyvals}#d
\RibbonTableau{ribbon spec}
\RibbonTableau[options%keyvals]{ribbon spec}
\RibbonTableau(x,y){ribbon spec}
\RibbonTableau(x,y)[options%keyvals]{ribbon spec}
\ShiftedDiagram{partition spec}
\ShiftedDiagram[options%keyvals]{partition spec}
\ShiftedDiagram(x,y){partition spec}
\ShiftedDiagram(x,y)[options%keyvals]{partition spec}
\ShiftedTableau{tableau spec}
\ShiftedTableau[options%keyvals]{tableau spec}
\ShiftedTableau(x,y){tableau spec}
\ShiftedTableau(x,y)[options%keyvals]{tableau spec}
\SkewDiagram{skew shape}{partition spec}
\SkewDiagram[options%keyvals]{skew shape}{partition spec}
\SkewDiagram(x,y){skew shape}{partition spec}
\SkewDiagram(x,y)[options%keyvals]{skew shape}{partition spec}
\SkewTableau{skew shape}{tableau spec}
\SkewTableau[options%keyvals]{skew shape}{tableau spec}
\SkewTableau(x,y){skew shape}{tableau spec}
\SkewTableau(x,y)[options%keyvals]{skew shape}{tableau spec}
\Tableau{tableau spec}
\Tableau[options%keyvals]{tableau spec}
\Tableau(x,y){tableau spec}
\Tableau(x,y)[options%keyvals]{tableau spec}
\Tabloid{partition spec}
\Tabloid[options%keyvals]{partition spec}
\Tabloid(x,y){partition spec}
\Tabloid(x,y)[options%keyvals]{partition spec}
\aTabset{options%keyvals}

aTableauMain#B
aTableauInner#B
aTableauSkew#B
aTableauStar#B
aTableauFill#B
aTableauRod#B