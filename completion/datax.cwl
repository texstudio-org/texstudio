# datax package
# Matthew Bertucci 1/18/2022 for v1.1.2

#include:pgfkeys
#include:pgfopts

#keyvals:\usepackage/datax#c
dataxfile=%<file%>
siunitxoptions={%<options%>}
#endkeyvals

\datax{tag}

\dataxfile#*
\ifhassiunitx#*
\hassiunitxtrue#*
\hassiunitxfalse#*