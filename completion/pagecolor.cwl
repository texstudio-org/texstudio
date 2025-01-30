# pagecolor package
# Matthew Bertucci 2025/01/30 for v1.2d

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
