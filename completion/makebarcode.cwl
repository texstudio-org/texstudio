# makebarcode package
# Matthew Bertucci 11/13/2021 for v1.0

#include:kvoptions

\barcode{code}
\barcode[options%keyvals]{code}

#keyvals:\usepackage/makebarcode#c
help#true,false
#endkeyvals

#keyvals:\usepackage/makebarcode#c,\barcode
X=##L
H=##L
bcorr=##L
ratio=%<ratio%>
K=%<number%>
MtoXratio=%<ratio%>
code=#2/5-Industrial,2/5-IATA,2/5-Matrix,2/5-Datalogic,2/5-Inverted,2/5-Interleaved,Code39
S1.2
S1.1
S1
S.9
S.8
S.7
S.6
lines#true,false
frame
#endkeyvals

\HPlabel{code}

\ITFbarcode{code}
\ITFbarcode[options%keyvals]{code}

#keyvals:\ITFbarcode
lines#true,false
frame
S1.2
S1.1
S1
S.9
S.8
S.7
S.6
#endkeyvals

\BarcodeSanitize#*