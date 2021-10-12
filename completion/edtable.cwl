# edtable package
# Matthew Bertucci 10/4/2021 for v1.3c

#ifOption:longtable
#include:longtable
#include:ltabptch
#endif

#ifOption:nolongtablepatch
#include:longtable
#endif

\begin{edtable}{table envname}{preamble}#\tabular
\begin{edtable}[$ or $$%plain]{array envname}{preamble}#\tabular
\end{edtable}