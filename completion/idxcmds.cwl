# idxcmds package
# Matthew Bertucci 10/18/2021 for v0.2c

#include:etoolbox
#include:pgfopts
#include:ltxcmds

\newidxcmd{cmd}{definition}#d
\newidxcmd[index cmd]{cmd}{definition}#d
\newidxcmd{cmd}{definition}[append]#*d
\newidxcmd[index cmd]{cmd}{definition}[append]#*d

\newsubidxcmd{cmd}{main entry}{definition}#d
\newsubidxcmd[index cmd]{cmd}{main entry}{definition}#d
\newsubidxcmd{cmd}{main entry}{definition}[append]#*d
\newsubidxcmd[index cmd]{cmd}{main entry}{definition}[append]#*d
\newsubidxcmd*{cmd}{main entry}{definition}#d
\newsubidxcmd*[index cmd]{cmd}{main entry}{definition}#d
\newsubidxcmd*{cmd}{main entry}{definition}[append]#*d
\newsubidxcmd*[index cmd]{cmd}{main entry}{definition}[append]#*d

\newsubmainidxcmd{cmd}{definition}#d
\newsubidxcmd[index cmd]{cmd}{definition}#d
\newsubidxcmd{cmd}{main entry}[append]#*d
\newsubidxcmd[index cmd]{cmd}{definition}[append]#*d

\setidxcmds{options%keyvals}

#keyvals:\setidxcmds
sort-sep={%<symbol%>}
sub-sep={%<symbol%>}
idx-cmd={%<cmd%>}
#endkeyvals