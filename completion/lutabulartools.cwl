# lutabulartools package
# Matthew Bertucci 4/24/2022 for release 2022-11-29

#include:booktabs
#include:multirow
#include:makecell
#include:array
#include:xcolor
#include:colortbl
#include:luacode
#include:penlight

\settabular{options%keyvals}

#keyvals:\settabular
nopad#true,false
tbrule#true,false
rowsep=%<integer%>
colsep=%<integer%>
#endkeyvals

\lttdebugON
\lttdebugOFF
\lttdebugprt

\MC{contents%text}#t
\MC[cell spec]{contents%text}#t
\MC[cell spec][override multicol]<cell format>{contents%text}#t
\MC*{contents%text}#t
\MC*[cell spec]{contents%text}#t
\MC*[cell spec][override multicol]<cell format>{contents%text}#t

\setMCrepl{column}{spec}
\setMChordef{column}{alignments}
\setMCverdef{column}{alignments}
\addMCsicol{column}

\midrulesat{row1,row2,...}

\gmidrule{colspecs}#t
\gmidrule(trim){colspecs}#t
\gcmidrule{colspecs}#t
\gcmidrule(trim){colspecs}#t
\gcmidrules{colspecs}#t
\gcmidrules(trim){colspecs}#t
\cmidrules{colspecs}#t
\cmidrules(trim){colspecs}#t

\midruleX{keyvals}
\midruleX[o|n|f]{keyvals}
\midruleX*{keyvals}
\midruleX*[o|n|f]{keyvals}

#keyvals:\midruleX,\midruleX*
step=%<integer%>
rule=
reset#true,false
resetnum=%<integer%>
cntr=%<integer%>
#endkeyvals

\resetmidruleX
\resetmidruleX[counter]

# not documented
\forcecolspec{arg}#S
\oldgcmidrule#S
\oldcmidrule#S
