# multitoc package
# Matthew Bertucci 11/22/2021 for v2.01

#include:multicol
#include:ifthen

#keyvals:\usepackage/multitoc#c
toc
lot
lof
#endkeyvals

\multicolumntoc
\multicolumnlot
\multicolumnlof

# deprecated
\immediateaddtocontents#S
