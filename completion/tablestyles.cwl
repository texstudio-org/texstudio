# tablestyles package
# Matthew Bertucci 1/27/2022 for v0.1

#include:array
#include:etoolbox
#include:xcolor
# xcolor loaded with table option
#include:ragged2e

\tablestyle
\tablestyle[style%keyvals]

#keyvals:\tablestyle
default
roman
sansbold
sansboldbw
%tablestyle
#endkeyvals

\tbegin#t
\tend#t
\tbody#t
\theadstart#t
\tsubheadstart#t
\theadend#t
\tsubheadend#t
\thead#t
\tsubhead#t
\theadrow{number of cells}{text}#t
\tsubheadrow{number of cells}{text}#t
\tlinetop#*t
\tlinemid#*t
\tlinebottom#*t

\setuptablefontsize{name}{size definition}
\tablefontsize{name}
\setuptablecolor{color name%specialDef}{definition}#s#%color
\tablecolor{color}
\tablealtcolored
\disablealternatecolors

\coloredhline{color}#t
\coloredvline{color}#t

\setuptablestyle{style name%specialDef}{definition}#s#%tablestyle
\resettablestyle

\tableitemize

# from table option of xcolor
#include:colortbl
