# keyvaltable package
# Matthew Bertucci 10/1/2021 for v2.2

#include:etoolbox
#include:xkeyval
#include:trimspaces
#include:xcolor
# loads table option of xcolor
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

\kvtLabel{counter}{label}#l
\kvtLabel[options]{counter}{label}#*l

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

#keyvals:\kvtSet
align=%<coltype%>
default=%<content%>
format=%<single-arg macro%>
head=%<content%>
hidden#true,false
#endkeyvals

#keyvals:\Row,\CollectRow,\AddKeyValRow,\kvtNewRowStyle,\kvtRenewRowStyle
uncounted#true,false
hidden#true,false
align=%<coltype%>
bg=#%color
format=%<cmd%>
format*=%<cmd%>
format!=%<cmd%>
headlike#true,false
above=##L
below=##L
around=##L
style=%<list of style names%>
expandonce#true,false
expand#true,false
#endkeyvals

#keyvals:\kvtSet
Row/uncounted#true,false
Row/hidden#true,false
Row/align=%<coltype%>
Row/bg=#%color
Row/format=%<cmd%>
Row/format*=%<cmd%>
Row/format!=%<cmd%>
Row/headlike#true,false
Row/above=##L
Row/below=##L
Row/around=##L
Row/style=%<list of style names%>
Row/expandonce#true,false
Row/expand#true,false
HeadCell/align=%<coltype%>
HeadCell/head=%<text%>
ColGroup/span=%<+ separated columns%>
ColGroup/align=%<coltype%>
ColGroup/format=%<single-arg macro%>
#endkeyvals

#keyvals:\begin{KeyValTable}
resume#true,false
resume*#true,false
caption=%<text%>
caption/lot=%<text%>
caption/alt=%<text%>
label=##l
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
headalign=%<coltype%>
headbg=#%color
headformat=%<cmd%>
rowbg=#%color
norowbg#true,false
nobg#true,false
style=%<list of style names%>
captionpos=#t,b
#endkeyvals

# not in main documentation
\metatblRegisterEnv{envname}{properties}#*
\metatblRegistered{envname}{true}{false}#*
\metatblIsLong{envname}{true}{false}#*
\metatblIsTabu{envname}{true}{false}#*
\metatblHasWidth{envname}{true}{false}#*
\metatblHasCaption{envname}{true}{false}#*
\metatblCanVAlign{envname}{true}{false}#*
\metatblCanHAlign{envname}{true}{false}#*
\metatblUsePackage{envnames}#*
\metatblRequire{envnames}#*
\metatblAtEnd{envname}{code}#*

# from table option of xcolor
#include:colortbl
## double command as workaround for color args to be recognized properly as colors
\rowcolors{row}{odd-row-color}{even-row-color}
\rowcolors[commands]{row}{odd-row-color}{even-row-color}
\rowcolors{row}{color}{color}#S
\rowcolors[commands]{row}{color}{color}#S
\rowcolors*{row}{odd-row-color}{even-row-color}
\rowcolors*[commands]{row}{odd-row-color}{even-row-color}
\rowcolors*{row}{color}{color}#S
\rowcolors*[commands]{row}{color}{color}#S
\showrowcolors
\hiderowcolors
\rownum
