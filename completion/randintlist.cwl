# randintlist package
# Matthew Bertucci 2025/05/25 for v0.1.4

#include:simplekv
#include:listofitems
#include:randomlist
#include:xintexpr
#include:xstring
#include:ifthen

\randintlist{command}#d
\randintlist[keyvals]{command}#d
\getitemfromrandintlist{command}{index}
\getitemfromrandintlist{command}{index}[\macro]
\getitemfromrandintlist[sep]{command}{index}
\getitemfromrandintlist[sep]{command}{index}[\macro]

\ListeRandint{command}#d
\ListeRandint[keyvals]{command}#d
\ExtraireEltListeRandint{command}{index}
\ExtraireEltListeRandint{command}{index}[\macro]
\ExtraireEltListeRandint[sep]{command}{index}
\ExtraireEltListeRandint[sep]{command}{index}[\macro]