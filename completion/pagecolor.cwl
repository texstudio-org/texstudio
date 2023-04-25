# pagecolor package
# Matthew Bertucci 2023/04/18 for v1.2c

#include:kvoptions
#include:xcolor

#keyvals:\usepackage/pagecolor#c
pagecolor=#%color
nopagecolor
#endkeyvals

\thepagecolor
\thepagecolornone
\newpagecolor{color}
\restorepagecolor

# require crop package loaded
\backgroundpagecolor{color}#*
\newbackgroundpagecolor{color}#*
\restorebackgroundpagecolor#*
