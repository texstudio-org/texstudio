# ezedits package
# Matthew Bertucci 2024/11/18 for v1.1

#include:ulem
#include:xcolor

#keyvals:\usepackage/ezedits#c
accept
pdfcomment
arrows
nosout
#endkeyvals

#ifOption:pdfcomment
#include:pdfcomment
#endif

\draftnote{text}
\definEdit{prefix}{omitted style}{added style}
\setnotestyle{style}
\makeeditreport