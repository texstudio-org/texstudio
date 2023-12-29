# xkeymask package
# Matthew Bertucci 2023/12/26 for v1.0

#include:kvoptions
#include:xkeyval

#keyvals:\usepackage/xkeymask#c
prefix=%<prefix%>
#endkeyvals

\appendmask[prefix]{key%plain}[values]#*
\ifinmask[prefix]{key%plain}[values]{true}{false}#*
\clearmask#*