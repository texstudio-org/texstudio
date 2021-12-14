# idxlayout package
# Matthew Bertucci 12/12/2021 for v0.4d

#include:etoolbox
#include:kvoptions
#include:multicol
#include:ragged2e

\idxlayout{options%keyvals}

#keyvals:\idxlayout,\usepackage/idxlayout#c
columns=%<integer%>
unbalanced#true,false
columnsep=##L
rule=##L
itemlayout=#abshang,relhang,singlepar
indentunit=##L
hangindent=##L
subindent=##L
subsubindent=##L
initsep=##L
notesep=##L
columnnote#true,false
minspace=##L
font=%<format csnames%>
justific=#standard,raggedright,RaggedRight
totoc#true,false
#endkeyvals

\setindexprenote{text}
\noindexprenote

\indexfont#*
\indexjustific#*
\indexsubsdelim#*
\indexstheadcase#*
\theidxcols#*
\indexcolsep#*
\indexrule#*