# extpfeil package
# Matthew Bertucci 4/17/2022 for v0.4

#include:amsmath
#include:amssymb
#include:mathtools
# loads stmaryrd symbols \shortleftarrow and \shortrightarrow
\shortleftarrow#m
\shortrightarrow#m

\xlongequal[sub]{sup}#m
\xtwoheadleftarrow[sub]{sup}#m
\xtwoheadrightarrow[sub]{sup}#m
\xtofrom[sub]{sup}#m
\newextarrow{cmd}{space}{arrow}#d
\twoarrowsleft{arrow1}{arrow2}#*m
\twoarrowsright{arrow1}{arrow2}#*m
\bigtwoarrowsleft{arrow1}{arrow2}#*m
\bigtwoarrowsright{arrow1}{arrow2}#*m
\bigRelbar#*
\bigRelbar[dimen%l]#*
