# gtrlib.largetrees package
# Matthew Bertucci 1/18/2022 for v1.2b

#include:genealogytree
#include:etoolbox

#keyvals:\genealogytree#c,\genealogytreeinput#c,\begin{genealogypicture}#c,\gtrset#c,\gtrkeysappto#c,\gtrkeysgappto#c,\gtrsetoptionsfornode#c,\gtrsetoptionsforfamily#c,\gtrsetoptionsforsubtree#c,\gtrparserdebug#c,\gtrparserdebuginput#c,\gtrprocessordebug#c,\gtrprocessordebuginput#c,\gtrfanchart#c,\gtrfanchartinput#c
sparse display
sparse node size from=%<min%> to %<max%>
sparse max fields=%<integer%>
sparse inner from level=%<integer%>
sparse leaf from level=%<integer%>
sparse inner never
#endkeyvals

\gtrDBspouse#*
\gtrifspousedefined{true}{false}#*
\gtrPrintSpouse
\gtrPrintSpouseDetails
\gtrDBchildren#*
\gtrDBdaughters#*
\gtrDBsons#*
\gtrifchildrendefined{true}{false}#*
\gtrPrintChildren
\gtrltSparseNodeProcessor#*
\gtrltIfSparseEnabled{true}{false}#*
\gtrltFieldCount#*
\gtrltIfSparse{true}{false}#*
\gtrltDeclareFieldCount{db-format}{macro}#*
\gtrltFieldCountByConditionals{cond-list}#*