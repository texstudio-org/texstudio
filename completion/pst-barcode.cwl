# pst-barcode package
# Matthew Bertucci 2/22/2022 for v0.18

#include:pstricks
#include:pst-xkey
#include:marginnote

\psbarcode{text or filename%file}{PS options}{barcode type}
\psbarcode[options%keyvals]{text or filename%file}{PS options}{barcode type}

#keyvals:\psbarcode#c
fontstyle=%<font commands%>
transx=%<number%>
transy=%<number%>
scalex=%<factor%>
scaley=%<factor%>
rotate=%<degrees%>
file#true,false
linecolor=#%color
#endkeyvals

\QR{URL}#U
\QR<label>{URL}#U
\QR[scale]{URL}#U
\QR[scale]<label>{URL}#U

\PSTBarcodeLoaded#S
