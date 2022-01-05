# PJLdate package
# Matthew Bertucci 12/30/2021

#include:kvoptions
#include:etoolbox
#include:PJLlang
#include:silence
#include:datetime2
#include:zhnumber

#keyvals:\usepackage/PJLdate#c
draft#true,false
fast#true,false
#endkeyvals

\TheDate{%<YYYY%>-%<MM%>-%<DD%>}
\PLdate{%<YYYY%>-%<MM%>-%<DD%>}

\PJLdate{%<YYYY%>-%<MM%>-%<DD%>}#*