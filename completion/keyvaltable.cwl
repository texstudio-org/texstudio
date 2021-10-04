# keyvaltable package
# Matthew Bertucci 10/1/2021 for v2.2

#include:etoolbox
#include:trimspaces
#include:xcolor
#include:booktabs

\NewKeyValTable{table name}{colspecs}
\NewKeyValTable[options%keyvals]{table name}{colspecs}
\NewKeyValTable{table name}{colspecs}[layout]#*
\NewKeyValTable[options%keyvals]{table name}{colspecs}[layout]#*

\begin{KeyValTable}{table name}
\begin{KeyValTable}[options%keyvals]{table name}
\end{KeyValTable}

\Row{col=text,...}
\Row[options%keyvals]{col=text,...}

\NewCollectedTable{collection name}{table name}
\CollectRow{collection name}{col=text,...}
\CollectRow[options%keyvals]{collection name}{col=text,...}
\ShowCollectedTable{collection name}
\ShowCollectedTable[options%keyvals]{collection name}

\ShowKeyValTableFile{table name}{file}
\ShowKeyValTableFile[options%keyvals]{table name}{file}

\AddKeyValRow{table name}{col=text,...}#*
\AddKeyValRow{table name}[options%keyvals]{col=text,...}#*
\ShowKeyValTable{table name}#*
\ShowKeyValTable[options%keyvals]{table name}#*
\begin{KeyValTableContent}{table name}#*
\end{KeyValTableContent}#*

\thekvtRow
\thekvtTypeRow
\thekvtTotalRow

\kvtlabel{counter}{label}
\kvtlabel[options]{counter}{label}#*

\kvtDeclareTableMacros{macro list}
\kvtDeclareTableCounters{counter list}
\kvtDeclareCtrFormatters{macro list}

\kvtNewTableStyle{name}{options%keyvals}
\kvtRenewTableStyle{name}{options%keyvals}

\kvtStrutted{arg}
\kvtStrutted[inner]{arg}

\kvtNewRowStyle{name}{options%keyvals}
\kvtRenewRowStyle{name}{options%keyvals}

\kvtTableOpt{option}#*

\kvtSet{options%keyvals}

#keyvals:\Row,\CollectRow,\AddKeyValRow,\kvtNewRowStyle,\kvtRenewRowStyle
uncounted#true,false
hidden#true,false
align=
bg=#%color
format=%<cmd%>
format*=%<cmd%>
format!=%<cmd%>
headlike#true,false
above=##L
below=##L
around=##L
style=
#endkeyvals

#keyvals:\begin{KeyValTable}
resume#true,false
resume*#true,false
caption=%<text%>
caption/lot=%<text%>
caption/alt=%<text%>
label=##l
captionpos=#t,b
#endkeyvals

#keyvals:\NewKeyValTable,\begin{KeyValTable},\ShowCollectedTable,\ShowKeyValTableFile,\ShowKeyValTable,\kvtSet,\kvtNewTableStyle,\kvtRenewTableStyle
backend=#tabular,tabularx,longtable,xltabular,tabu,longtabu
shape=#multipage,onepage
width=##L
valign=#t,c,b
halign=#l,c,r
showhead#true,false
showrules#true,false
norules#true,false
headalign=
headbg=#%color
headformat=%<cmd%>
rowbg=#%color
norowbg#true,false
nobg#true,false
style=
#endkeyvals