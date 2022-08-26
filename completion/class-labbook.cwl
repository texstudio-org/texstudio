# labbook class
# Matthew Bertucci 2022/08/21 for v1.1

#include:class-scrbook
#include:makeidx

#keyvals:\documentclass/labbook#c
hyperref
#endkeyvals

#ifOption:hyperref
\theHexperiment#*
\theHlabday#*
\theHsubexperiment#*
\theHsubfigure#*
#endif

\labday#L1
\experiment{title}#L2
\experiment[short title]{title}#L2
\experiment*{title}#L2
\subexperiment{title}#L3
\subexperiment[short title]{title}#L3
\subexperiment*{title}#L3
\newexperiment{abbrev}{long form%text}
\newexperiment{abbrev}[short form%text]{long form%text}
\newsubexperiment{abbrev}{long form%text}
\newsubexperiment{abbrev}[short form%text]{long form%text}

# not in main documentation
\experimentmark{code}#*
\subexperimentmark{code}#*
\theexperiment#*
\thelabday#*
\thesubexperiment#*