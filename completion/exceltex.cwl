# exceltex package
# Matthew Bertucci 1/26/2022 for v0.5.1

#include:ulem
#include:color

#keyvals:\usepackage/exceltex#c
cellrefs
#endkeyvals

#ifOption:cellrefs
\cellrefs#*
#endif

\theexceltexCounterC#*
\theexceltexCounterT#*

\inccell{%<file!sheet!cell%>}
\inctab{%<file!sheet!cell1!cell2%>}