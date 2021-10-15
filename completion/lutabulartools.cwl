# lutabulartools package
# Matthew Bertucci 10/14/2021

#include:booktabs
#include:multirow
#include:makecell
#include:xparse
#include:array
#include:xcolor
#include:colortbl
#include:luacode
#include:penlight

\MC{contents%text}#t
\MC[cell spec]<cell format>(override multicolumn col){contents%text}#t
\MC*{contents%text}#t
\MC*[cell spec]<cell format>(override multicolumn col){contents%text}#t

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

\TabColNum#t
\NumTabCols#t

\midruleXaux#*
\ifmidruleX
\midruleXtrue#*
\midruleXfalse#*

\oldgcmidrule#S
\oldcmidrule#S