# getitems package
# Matthew Bertucci 11/22/2021 for v1.0

#include:environ
#include:trimspaces

\gatheritems{text to parse%text}
\thenumgathereditems#*
\gathereditem{item number}
\loopthroughitemswithcommand{macro}
\thecurrentitemnumber#*
\ifgatherbeginningofloop#*
\gatherbeginningoflooptrue#*
\gatherbeginningofloopfalse#*