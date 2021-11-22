# mode: scrtime.sty
# dani/2006-02-21
# Matthew Bertucci updated 11/19/2021 for v3.34

#include:scrkbase

#keyvals:\KOMAoptions#c
12h=#true,on,yes,false,off,no
#endkeyvals

\thistime
\thistime[delimiter]
\thistime*
\thistime*[delimiter]

\settime{time}
