# TeXstudio autocompletition file for metrix.sty
# Tobias Weh 14.8.2013; Matthew Bertucci 10/5/2021 for v1.5
# www.tobias-weh.de

#include:tikz
#include:tikzlibrarycalc
#include:xpatch

\metricsymbols{symbols}
\metricsymbols*{symbols}
\metricsymbols[%<number%>=%<higlighting%>]{symbols}
\metricsymbols*[%<number%>=%<higlighting%>]{symbols}

\metrics{symbols}{syllables}
\metrics[%<number%>=%<higlighting%>]{symbols}{syllables}

\acct{vowel}
\brv{vowel}
\lng{vowel}
\bow{syllables}

\begin{symbolline}
\end{symbolline}
\begin{metricverses}
\begin{metricverses}[source]
\end{metricverses}
\verseref{reference}#/metricverses

\setmetrixvar{variable%keyvals}{value}
\usemetrixvar{variable%keyvals}

#keyvals:\setmetrixvar,\usemetrixvar
symbollinewidth
bigsymbollinewidth
accentlinewidth
bowlinewidth
symbolsep
baseunit
bigbaseunit
shortsyllablelimit
gap
symbolshift
lngshift
lngshortening
lngminlength
brvshift
dotshift
itcorrection
accentxshift
bowshift
bowshortening
bowlooseness
symbolcolor
accentcolor
bowcolor
highlightcolor
fillcolor
arrow
breakgap
emptywidth
acute
grave
#endkeyvals
