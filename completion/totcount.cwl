# totcount package
# Matthew Bertucci 7/26/2021

#include:keyval

\regtotcounter{counter}
\newtotcounter[option%keyvals]{counter}

#keyvals:\newtotcounter
auxfile=
#endkeyvals

\total{counter}
\totvalue{counter}
\usetotcountfile{file}