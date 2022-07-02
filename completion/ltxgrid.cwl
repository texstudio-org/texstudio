# ltxgrid package
# Matthew Bertucci 2022/07/01 for v4.2e

#include:ltxutil

\begin{turnpage}
\end{turnpage}

\addstuff{penalty}{glue}#*
\footsofar#*
\linefoot{label}#*
\lineloop{number}#*
\onecolumngrid#*
\pagesofar#*
\removephantombox#*
\removestuff#*
\replacestuff{penalty}{glue}#*
\restorecolumngrid#*
\thelinecount#*
\thepagegrid#*
\twocolumngrid#*

# only available if longtable loaded
\begin{longtable*}{preamble}#S\tabular
\end{longtable*}#S
\endfirstfoot#S/longtable,longtable*
\endlastfoot#S/longtable,longtable*
\endfirsthead#S/longtable,longtable*
\endfoot#S/longtable,longtable*
\endhead#S/longtable,longtable*