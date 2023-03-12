# cnltx-tools package
# Matthew Bertucci 10/18/2021 for v0.15

#include:cnltx-base
#include:accsupp
#include:cnltx-translations

\cnltxacronym{string}{acronym}

\newabbr{cmd}{definition}#d
\newabbr*{cmd}{definition}#d
\renewabbr{cmd}{definition}
\renewabbr*{cmd}{definition}
\defabbr{cmd}{definition}#d
\defabbr*{cmd}{definition}#d

\cnltxlatin{abbreviation}
\ie
\eg
\cf
\etc
\vs
\zB
\ZB
\usw
\usf
\uswusf
\bzw
\dsh
\Dsh
\vgl
\Vgl

\cnltxtimeformat{abbreviation}
\PM
\AM
\BC
\AD

#keyvals:\setcnltx#c
acronym-format={%<definition%>}
name-format={%<formatting cmds%>}
last-name-format={%<formatting cmds%>}
first-name-format={%<formatting cmds%>}
#endkeyvals

\nohyperpage{arg}#*
\texorpdfstring{TEXstring}{PDFstring}#*
