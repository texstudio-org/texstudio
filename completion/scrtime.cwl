# mode: scrtime.sty
# dani/2006-02-21
# Matthew Bertucci updated 2022/05/18 for v3.36

#include:scrkbase
#include:scrlogo

#keyvals:\KOMAoptions#c
12h=#true,on,yes,false,off,no
#endkeyvals

\thistime
\thistime[delimiter]
\thistime*
\thistime*[delimiter]

\settime{time}
