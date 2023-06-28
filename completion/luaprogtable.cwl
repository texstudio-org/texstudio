# luaprogtable package
# Matthew Bertucci 2/4/2022 for v1.0

#include:iftex
#include:luatexbase

\LPTNewTable{name%specialDef}{num cols}{preamble}#s#%LPTtablename
\LPTNewTable{name%specialDef}{num cols}{preamble}[options%keyvals]#s#%LPTtablename

#keyvals:\LPTNewTable
backend=%<envname%>
default before line=%<code%>
default after line=%<code%>
default after spacing=%<code%>
input method=#file,stringbuffer
nrows=%<integer%>
#endkeyvals

\LPTSetCurrentTable{table name%keyvals}
#keyvals:\LPTSetCurrentTable#c,\LPTDeleteTable#c
%LPTtablename
#endkeyvals

\LPTGetCurrentTable

\LPTAddRow
\LPTAddRow[options%keyvals]
\LPTSetRowProp{index expr}{row options%keyvals}

#keyvals:\LPTAddRow,\LPTSetRowProp
before line
after line
after spacing
#endkeyvals

\begin{lptview}{index expr}
\end{lptview}
\begin{lptfill}{index expr}
\end{lptfill}

\LPTUseTable
\LPTDeleteTable{table name%keyvals}

\LPTSetCell{index expr}{content}
\LPTSetCell{index expr}[shape]{content}
\LPTFill{index expr}{content}
\LPTGetTableNames
\LPTGetTableShape
\LPTGetCellData{index expr}
\LPTGetCellShape{index expr}
\LPTGetCellParent{index expr}
\LPTGetCellMetaIndex{arg1}{arg2}#*