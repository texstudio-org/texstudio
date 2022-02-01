# jigsaw package
# Matthew Bertucci 1/31/2022 for v0.1a

#include:tikz
#include:ifluatex
#include:ifxetex

\piece{bottom}{right}{top}{left}
\piece[color]{bottom}{right}{top}{left}
\tile{bottom}{right}{top}{left}
\tile[color]{bottom}{right}{top}{left}
\jigsaw{rows}{columns}

\side{number}#*
\bottom#*
\halfpiece{num1}{num2}#*
\tmp#S
\xmax#*
\ymax#*