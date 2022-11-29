# pagecolor package
# Matthew Bertucci 2022/11/27 for v1.2a

#include:hardwrap
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
