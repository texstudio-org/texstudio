# lutabulartools package
# Matthew Bertucci 4/24/2022 for release 2022-04-16

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

\lttdebugON
\lttdebugOFF

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
\setmidruleX{keyvals}
\setmidruleX[o|n|f]{keyvals}
\setmidruleX*{keyvals}
\setmidruleX*[o|n|f]{keyvals}

#keyvals:\setmidruleX,\setmidruleX*
step=%<integer%>
rule=
reset#true,false
resetnum=%<integer%>
cntr=%<integer%>
#endkeyvals

\resetmidruleX
\midruleXreset#S

# not documented
\forcecolspec{arg}#S
\oldgcmidrule#S
\oldcmidrule#S
