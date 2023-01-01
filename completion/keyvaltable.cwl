# keyvaltable package
# Matthew Bertucci 2023/01/01 for v2.3

#include:etoolbox
#include:xkeyval
#include:trimspaces
#include:colortbl
#include:xcolor
#include:booktabs

#keyvals:\usepackage/keyvaltable#c
compat=%<version%>
#endkeyvals

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

\MidRule
\MidRule[width]
\CMidRule{columns}
\CMidRule[width]{columns}

\kvtRuleTop{color}
\kvtRuleTop[width]{color}
\kvtRuleBottom{color}
\kvtRuleBottom[width]{color}
\kvtRuleMid{color1}{color2}
\kvtRuleMid[width]{color1}{color2}
\kvtRuleMid{color}{color}#S
\kvtRuleMid[width]{color}{color}#S
\kvtRuleCMid{a-b}{color1}{color2}
\kvtRuleCMid(trim){a-b}{color1}{color2}
\kvtRuleCMid[width](trim){a-b}{color1}{color2}
\kvtRuleCMid{a-b}{color}{color}#S
\kvtRuleCMid(trim){a-b}{color}{color}#S
\kvtRuleCMid[width](trim){a-b}{color}{color}#S
\kvtRulesCMid{rlist}{color1}{color2}
\kvtRulesCMid[width]{rlist}{color1}{color2}
\kvtRulesCMid{rlist}{color}{color}#S
\kvtRulesCMid[width]{rlist}{color}{color}#S

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
HeadCell/underline#true,false
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
