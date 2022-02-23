# pst-stru package
# Matthew Bertucci 2/22/2022 for v0.13

#include:pstricks
#include:multido
#include:pst-node
#include:pst-plot
#include:pst-xkey

\arrow
\circput(nodeA)(nodeB){stuffA}{stuffB}#*
\clockCouple
\debut#*
\fin#*
\fixedend
\guide
\hinge
\interhinge
\noclockCouple
\node(name)
\nStart#S
\PAS#*
\Position#*
\psArrowCivil(nodeA)(nodeB){stuff}
\psArrowCivil[options%keyvals](nodeA)(nodeB){stuff}
\roller
\Start#*
\triload
\triload[options%keyvals]