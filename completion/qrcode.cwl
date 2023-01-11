# qrcode package
# Matthew Bertucci 9/27/2021 for v1.51

#include:xcolor

\qrcode{URL}#U
\qrcode[options%keyvals]{URL}#U
\qrcode*{URL}#U
\qrcode*[options%keyvals]{URL}#U
\qrset{options%keyvals}

#keyvals:\qrcode,\qrset,\qrcode*
height=##L
level=#L,M,Q,H
version=
tight
padding
draft
#endkeyvals

#keyvals:\qrcode,\qrset
link
nolink
hyperlink
#endkeyvals
