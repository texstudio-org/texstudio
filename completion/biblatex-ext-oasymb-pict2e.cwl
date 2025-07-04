# biblatex-ext-oasymb-pict2e package
# Matthew Bertucci 2025/06/24 for v0.20

#include:etoolbox
#include:kvoptions
#include:xsavebox
#include:pict2e
#include:xcolor

#keyvals:\usepackage/biblatex-ext-oasymb-pict2e#c
symbol=#plos,oanet
#endkeyvals

\oasymbol

\DefineOASymbol
\DefineOASymbol[symbol%keyvals]

#keyvals:\DefineOASymbol#c
plos
oanet
#endkeyvals
