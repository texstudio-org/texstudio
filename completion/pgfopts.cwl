# pgfopts package
# Matthew Bertucci 12/13/2021 for v2.1a

#include:pgfkeys

\ProcessPgfOptions{path}#*
\ProcessPgfOptions*{path}#*
\ProcessPgfPackageOptions{path}#*
\ProcessPgfPackageOptions*{path}#*