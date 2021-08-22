# symbolpalette package
# Matthew Bertucci 8/19/2021 for v1.1.0

#include:xcolor
#include:macrolist

\newsuitetheme{theme}
\addsymboltotheme{theme}{symbol}
\newsuite{theme}{suite}
\setsuitesymbol{theme}{suite}{symbol}{icon}
\activesuite{theme}{suite}
\printsymbol{theme}{symbol}