# memorygraphs package
# Matthew Bertucci 12/14/2021 for v0.1.1

#include:tikz
#include:tikzlibrarycalc
#include:tikzlibrarypositioning
#include:tikzlibraryshapes

#keyvals:\begin{tikzpicture}#c,\tikz#c,\tikzset#c
memory graph
#endkeyvals

#keyvals:\node#c
block
arity=%<n%>
block mark north east
block mark north east={%<options%>}
block mark north west
block mark north west={%<options%>}
block mark south east
block mark south east={%<options%>}
block mark south west
block mark south west={%<options%>}
#endkeyvals

#keyvals:\tikzset#c
every block/.style={%<options%>}
#endkeyvals

#keyvals:\draw#c
ref
#endkeyvals

\arg{i}

\pgfaddtoshape{name}{code}#*
