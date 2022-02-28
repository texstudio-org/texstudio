# pst-geometrictools package
# Matthew Bertucci 2/23/2022 for v1.3

#include:pstricks
#include:pst-xkey
#include:pst-node

\psProtractor{angle}(x,y)
\psProtractor[options%keyvals]{angle}(x,y)
\ProLineCol#*
\ProFillCol#*

\psPencil{angle}(x,y)
\psPencil[options%keyvals]{angle}(x,y)
\pencilColA#*
\pencilColB#*

\psRuler{angle}(x,y)
\psRuler[options%keyvals]{angle}(x,y)
\RulerFillCol#*

\psCompass{radius}(x,y)
\psCompass[options%keyvals]{radius}(x,y)
\PoCFillCol#*
\PoCMineCol#*

\psDistAB(A)(B){name}#*
\psAngleAB(A)(B){name}#*
\psAngleAOB(A)(O)(B){name}#*

\psParallels(A)(B)(C)
\psParallels[options%keyvals](A)(B)(C)

\PSTgeometrictoolsLoaded#S
HolzCol#B
PoCRed#B