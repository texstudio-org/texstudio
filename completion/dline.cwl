# dline package
# Matthew Bertucci 2022/05/09 for v1.01

#include:lineno

# passes all options to lineno
#keyvals:\usepackage/dline#c
addpageno
mathrefs
edtable
longtable
nolongtablepatch
left
right
switch
switch*
columnwise
pagewise
running
modulo
modulo*
mathlines
#endkeyvals

#ifOption:addpageno
#include:vplref
#endif

#ifOption:mathrefs
#include:ednmath0
#endif

#ifOption:edtable
#include:edtable
#endif

#ifOption:longtable
#include:edtable
#include:longtable
#include:ltabptch
#endif

#ifOption:nolongtablepatch
#include:edtable
#include:longtable
#endif

\begin{dline}
\end{dline}

\dlinebox#*
\dlinerule#*
\ddlinerule#*
\dlinesep#*
\ddlinesep#*