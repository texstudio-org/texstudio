# contour package
# Matthew Bertucci 8/19/2021 for v2.14

#include:color

#keyvals:\usepackage/contour#c
auto
dvips
xdvi
pdftex
vtex
dvipsone
outline
copies
#endkeyvals

\contour{color}{text}
\contour*{color}{text}
\contour[number]{color}{text}

\contourlength{length}#*
\contournumber{number}#*
