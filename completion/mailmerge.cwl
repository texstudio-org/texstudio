# mailmerge package
# Matthew Bertucci 12/30/2021 for v1.0

#include:ifthen

\mailfields{name1,name2,...}
\mailrepeat{text}
\field{name}
\numberoffields
\numberofentries
\entrynumber
\mailentry{value1,value2,...}
\mailnewdata

\MAILMcurrtag#*
\MAILMtok#*
\theMAILMcount#*
\theMAILMentry#*
\MAILMrepetition#*
\MAILMsetnumfields{tag}{number}#*
\MAILMsetnumentries{tag}{number}#*
\MAILMaux#*