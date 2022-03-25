# lutabulartools package
# Matthew Bertucci 3/8/2022 for release 2022-02-07

#include:booktabs
#include:multirow
#include:makecell
#include:xparse
#include:array
#include:xcolor
#include:colortbl
#include:luacode
#include:penlight

#keyvals:\usepackage/lutabulartools#c
notrim
#endkeyvals

\MC{contents%text}#t
\MC[cell spec]{contents%text}#t
\MC[cell spec]<cell format>(override multicolumn col){contents%text}#t
\MC*{contents%text}#t
\MC*[cell spec]{contents%text}#t
\MC*[cell spec]<cell format>(override multicolumn col){contents%text}#t

\setMCrepl{column}{spec}
\setMChordef{column}{alignments}
\setMCverdef{column}{alignments}
\addMCsicol{column}

\gmidrule{colspecs}#t
\gmidrule(trim){colspecs}#t
\gcmidrule{colspecs}#t
\gcmidrule(trim){colspecs}#t
\gcmidrules{colspecs}#t
\gcmidrules(trim){colspecs}#t
\cmidrules{colspecs}#t
\cmidrules(trim){colspecs}#t

\midruleX
\resetmidruleX#t
\midruleXstep#*
\midruleXrule#*
\themidruleX#*
\midruleXaux#*
\ifmidruleX#*
\midruleXtrue#*
\midruleXfalse#*

\oldgcmidrule#S
\oldcmidrule#S
