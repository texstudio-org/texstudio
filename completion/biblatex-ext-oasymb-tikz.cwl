# biblatex-ext-oasymb-tikz package
# Matthew Bertucci 4/23/2022 for v0.15

#include:etoolbox
#include:kvoptions
#include:tikz

#keyvals:\usepackage/biblatex-ext-oasymb-tikz#c
symbol=#plos,oanet
#endkeyvals

\oasymbol

\DefineOASymbol
\DefineOASymbol[symbol%keyvals]

#keyvals:\DefineOASymbol#c
plos
oanet
#endkeyvals