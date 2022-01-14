# bxnewfont package
# Matthew Bertucci 1/12/2022 for v0.2b

#include:etoolbox

#keyvals:\usepackage/bxnewfont#c
newfont
#endkeyvals

\newfontx%<\macro%>{%<<tfm-name><at-clause>%>}
\newfontx%<\macro%>[%<encoding%>]{%<<tfm-name><at-clause>%>}
\newfontx{cmd}#Sd

\newfontx*%<\macro%>{%<tfm-name%>}
\newfontx*%<\macro%>[%<encoding%>]{%<tfm-name%>}
\newfontx*{cmd}#Sd

\bxDebug{arg}#*
\newfontjascale{arg}#*