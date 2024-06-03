# hvqrurl package
# Matthew Bertucci 2024/05/26 for v0.09

#include:qrcode
#include:xcolor
#include:marginnote
#include:url

#keyvals:\usepackage/hvqrurl#c
nohyperref
forget
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
