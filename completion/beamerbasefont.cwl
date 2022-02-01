# beamerbasefont package
# Matthew Bertucci 1/30/2022 for v3.65

#include:amssymb
#include:sansmathaccent

\setbeamerfont{beamer-font name}{attributes%keyvals}
\setbeamerfont*{beamer-font name}{attributes%keyvals}

#keyvals:\setbeamerfont,\setbeamerfont*
size=%<size command%>
size*={%<size in pt%>}{%<baselineskip%>}
shape=%<shape command%>
shape*={%<shape attribute abbreviation%>}
series=%<series command%>
series*={%<series attribute abbreviation%>}
family=%<family command%>
family*={%<family name%>}
parent={%<parent list%>}
#endkeyvals

\usebeamerfont{beamer-font name}
\usebeamerfont*{beamer-font name}

\Tiny
\TINY