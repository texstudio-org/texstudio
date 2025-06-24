# biblatex-ext-oasymb-tikz package
# Matthew Bertucci 2025/06/24 for v0.20

#include:etoolbox
#include:kvoptions
#include:xsavebox
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
