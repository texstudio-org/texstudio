# bib2qr package
# Matthew Bertucci 2024/08/01 for v0.2

#include:biblatex
#include:ifthen
#include:qrcode
#include:xstring

#keyvals:\usepackage/bib2qr#c
doiurlbase=%<string%>
qrdelimiter=%<sep code%>
qrversion=%<version%>
qrwidth=##L
#endkeyvals

\qrcite{bibid}#C
\qrfullcite{bibid}#C
\qrfullcite[option%keyvals]{bibid}#C

#keyvals:\qrfullcite
noindent
#endkeyvals