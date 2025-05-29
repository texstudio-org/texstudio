# qrcodetikz package
# Matthew Bertucci 2025/05/28 for v1.0

#include:qrcode
#include:tikz

#keyvals:\usepackage/qrcodetikz#c
# options passes to qrcode
nolinks
draft
final
forget
#endkeyvals

\qrcodeFillOptions{TikZ keys}

\qrcodetikzOn#*
\qrcodetikzOff#*

\QRTZgetTikzPathMaybeSaved{arg1}{arg2}#S
\QRTZBinaryToTikzPath#S
\QRTZprintQRmatrix#S
\QRTZprintBinaryString{arg}#S