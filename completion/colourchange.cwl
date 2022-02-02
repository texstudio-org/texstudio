# colourchange package
# Matthew Bertucci 2/1/2022 for v1.22

#include:etoolbox 
#include:calc

#keyvals:\usepackage/colourchange#c
defaultstyle
slidechange
framechange
draft
final
#endkeyvals

\selectmanualcolour{color}
\selectmanualcolor{color}#*

\selectcolourchanges{first color}{second color}
\selectcolourchanges{color}{color}#S
\selectcolorchanges{first color}{second color}#*
\selectcolorchanges{color}{color}#S

\setcolours#*
\fractionate#*
dred#B
\setstruccol{number}#*
\setstruccolx#*
\inserttotalslidenumber#*