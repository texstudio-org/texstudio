# totcount package
# Matthew Bertucci 7/26/2021 for v1.2

#include:keyval

\regtotcounter{counter}
\newtotcounter[option%keyvals]{counter}

#keyvals:\newtotcounter
auxfile=
#endkeyvals

\total{counter}
\totvalue{counter}
\usetotcountfile{file}

\totcdocdate#S
\totcfiledate#S
\totcfileversion#S
