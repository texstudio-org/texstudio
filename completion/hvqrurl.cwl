# hvqrurl package
# Matthew Bertucci 2024/02/04 for v0.06

#include:qrcode
#include:xcolor
#include:marginnote
#include:url

#keyvals:\usepackage/hvqrurl#c
nohyperref
#endkeyvals

\hvqrset{options%keyvals}
\hvqrurl{URL}#U
\hvqrurl[options%keyvals]{URL}#U
\hvqrurl*{URL}#U
\hvqrurl*[options%keyvals]{URL}#U

#keyvals:\hvqrset,\hvqrurl,\hvqrurl*
qrlink=#nolink,link
qrcolor=#%color
qradjust=##L
qrheight=##L
qrlevel=#L,M,Q,H
qrreverse
linktext=%<text%>
#endkeyvals
