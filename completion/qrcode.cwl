# qrcode package
# Matthew Bertucci 2024/05/26 for v1.51

#include:xcolor

#keyvals:\usepackage/qrcode#c
nolinks
draft
final
forget
#endkeyvals

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
