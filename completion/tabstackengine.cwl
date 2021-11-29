# tabstackengine package
# Matthew Bertucci 11/27/2021 for v2.10

#include:stackengine
#include:listofitems
#include:etoolbox

#keyvals:\usepackage/tabstackengine#c
TABcline
#endkeyvals

\TABstackText
\TABstackMath
\TABstackMathstyle{style}
\TABstackTextstyle{style}
\clearTABstyle
\fixTABwidth{T or F}
\setstacktabbedgap{gap%l}
\setstackaligngap{gap%l}
\setstacktabulargap{gap%l}
\TABrule
\TABrule[v-shift%l]
\TABruleshift#*
\TABcline{cols1,cols2,...}

#ifOption:TABcline
\relaxTABsyntax
#endif

\tabbedVectorstack{array%formula}
\tabbedCenterstack{array}
\tabbedLongunderstack{array}
\tabbedLongstack{array}
\tabbedShortunderstack{array}
\tabbedShortstack{array}

\alignVectorstack{array%formula}
\alignVectorstack[align%keyvals]{array%formula}
\alignCenterstack{array}
\alignCenterstack[align%keyvals]{array}
\alignLongunderstack{array}
\alignLongunderstack[align%keyvals]{array}
\alignLongstack{array}
\alignLongstack[align%keyvals]{array}
\alignShortunderstack{array}
\alignShortunderstack[align%keyvals]{array}
\alignShortstack{array}
\alignShortstack[align%keyvals]{array}

\Matrixstack{array}#m
\Matrixstack[align%keyvals]{array}#m
\parenMatrixstack{array}#m
\parenMatrixstack[align%keyvals]{array}#m
\braceMatrixstack{array}#m
\braceMatrixstack[align%keyvals]{array}#m
\bracketMatrixstack{array}#m
\bracketMatrixstack[align%keyvals]{array}#m
\vertMatrixstack{array}#m
\vertMatrixstack[align%keyvals]{array}#m

#keyvals:\alignVectorstack,\alignCenterstack,\alignLongunderstack,\alignLongstack,\alignShortunderstack,\alignShortstack,\Matrixstack,\parenMatrixstack,\braceMatrixstack,\bracketMatrixstack,\vertMatrixstack,\TABcellBox
l
c
r
#endkeyvals

\tabularVectorstack{cols}{array%formula}
\tabularCenterstack{cols}{array%formula}
\tabularLongunderstack{cols}{array}
\tabularLongstack{cols}{array}
\tabularShortunderstack{cols}{array}
\tabularShortstack{cols}{array}

\tabbedstackon{tabbed anchor}{tabbed arg}
\tabbedstackon[gap%l]{tabbed anchor}{tabbed arg}
\tabbedstackunder{tabbed anchor}{tabbed arg}
\tabbedstackunder[gap%l]{tabbed anchor}{tabbed arg}
\tabbedstackanchor{tabbed anchor}{tabbed arg}
\tabbedstackanchor[gap%l]{tabbed anchor}{tabbed arg}

\alignstackon{tabbed anchor}{tabbed arg}
\alignstackon[gap%l]{tabbed anchor}{tabbed arg}
\alignstackunder{tabbed anchor}{tabbed arg}
\alignstackunder[gap%l]{tabbed anchor}{tabbed arg}
\alignstackanchor{tabbed anchor}{tabbed arg}
\alignstackanchor[gap%l]{tabbed anchor}{tabbed arg}

\tabularstackon{cols}{tabbed anchor}{tabbed arg}
\tabularstackon[gap%l]{cols}{tabbed anchor}{tabbed arg}
\tabularstackunder{cols}{tabbed anchor}{tabbed arg}
\tabularstackunder[gap%l]{cols}{tabbed anchor}{tabbed arg}
\tabularstackanchor{cols}{tabbed anchor}{tabbed arg}
\tabularstackanchor[gap%l]{cols}{tabbed anchor}{tabbed arg}

\ensureTABstackMath{formula}
\setstackTAB{tabbing char}
\TABunaryLeft
\TABbinaryRight
\TABunaryRight
\TABbinaryLeft
\TABbinary
\readTABstack{array}
\TABwd{column}
\TABht{row}
\TABdp{row}
\TABcellRaw[row,column]
\TABcell{row}{column}
\TABstrut{row}
\TABcellBox{row}{column}
\TABcellBox[align%keyvals]{row}{column}
\getTABcelltoks[row,column]
\TABcelltoks
\TABcells{row or blank}

\maxTABwd#*
\setTABrulecolumn{integer}#*

\tabstackengineversionnumber#S