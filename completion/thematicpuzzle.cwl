# thematicpuzzle package
# Matthew Bertucci 2025/05/25 for v0.1.2

#include:tikz
#include:simplekv
#include:xstring
#include:xintexpr
#include:listofitems
#include:fontawesome5

#keyvals:\usepackage/thematicpuzzle#c
fa6
#endkeyvals

#ifOption:fa6
#include:fontawesome6
#endif

\ThematicPuzzle{symbol list}
\ThematicPuzzle<TikZ keys>{symbol list}
\ThematicPuzzle[keyvals]{symbol list}
\ThematicPuzzle[keyvals]<TikZ keys>{symbol list}

\PuzzleThemes{symbol list}
\PuzzleThemes<TikZ keys>{symbol list}
\PuzzleThemes[keyvals]{symbol list}
\PuzzleThemes[keyvals]<TikZ keys>{symbol list}

\ThemProbas
\ThemStats
\ThemChimie
\ThemArithm
\ThemGraphes
\ThemComplexes
\ThemMPM
\ThemCalculs
\ThemMatrices
\ThemGeometrie
\ThemEspace
\ThemPhysique
\ThemFonctions
\ThemSuites
\ThemTableur
\ThemAlgo
\ThemEco
\ThemPython
\ThemLogique