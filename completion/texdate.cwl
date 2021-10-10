# texdate package
# Matthew Bertucci 10/5/2021 for v2.0

#include:padcount
#include:modulus
#include:iflang

\printdate
\initcurrdate
\initdate{year}{month}{day}
\printfdate{format%keyvals}

#keyvals:\printfdate#c
ISO
ISOext
american
shamerican
british
shbritish
shbritishdots
#endkeyvals

\setdateformat#*
\nameddateformat{name}{format string}#*
\texdatenumformat#*

\advancebydays{number}
\advancebyweeks{number}
\advancebymonths{number}
\regressbydays{number}
\regressbyweeks{number}
\regressbymonths{number}

\savedate{name}
\restoredate{name}

\texdcal{year}{month}
\texdcalyear{year}