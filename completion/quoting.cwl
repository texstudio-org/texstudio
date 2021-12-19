# quoting package
# Matthew Bertucci 12/12/2021 for v0.1c

#include:etoolbox
#include:kvoptions

\begin{quoting}
\begin{quoting}[options%keyvals]
\end{quoting}

\quotingsetup{options%keyvals}

#keyvals:\begin{quoting},\quotingsetup,\usepackage/quoting#c
indentfirst=#auto,true,false
font={%<format names%>}
font+={%<format names%>}
begintext=%<text%>
endtext=%<text%>
leftmargin=##L
rightmargin=##L
vskip=##L
listvskip#true,false
noorphanfirst#true,false
noorphanafter#true,false
noorphans#true,false
#endkeyvals

\quotingfont#*