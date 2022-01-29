# bidicontour package
# Matthew Bertucci 1/28/2022 for v0.1

#include:color
#include:trig

#keyvals:\usepackage/bidicontour#c
auto
outline
copies
#endkeyvals

\bidicontourlength{length}#*
\bidicontournumber{number}#*

\bidicontour{color}{length}
\bidicontour[number]{color}{length}