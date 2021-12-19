# ladder package
# Matthew Bertucci 12/14/2021

#include:calc
#include:ifthen
#include:tikz

\ladderLine
\startParallel
\setParallel
\unsetParallel

\ladderNO{name}{mnemonic}
\ladderNO[type]{name}{mnemonic}
\ladderNC{name}{mnemonic}
\ladderNC[type]{name}{mnemonic}
\ladderC{name}{mnemonic}
\ladderC[type]{name}{mnemonic}
\ladderText{name}{mnemonic}#*
\ladderText[type]{name}{mnemonic}#*

\thecurrentX#*
\thecurrentY#*
\thememCurrentX#*
\thememCurrentY#*
\thenextX#*
\thenextY#*
\thenextYPar#*
\thestartPar#*
\thestopPar#*
\thetempCurrentY#*