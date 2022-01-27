# isomath package
# Matthew Bertucci 1/25/2022 for v0.6.1

#include:fixmath
#include:kvoptions

#keyvals:\usepackage/isomath#c
rmdefault=%<font family%>
sfdefault=#cmbr,fav,hvm,iwona,jkpss,llcmss
scaled=%<factor%>
reuseMathAlphabets#true,false
OMLmathrm#true,false
OMLmathbf#true,false
OMLmathsf#true,false
OMLmathsfit#true,false
OMLmathtt#true,false
OMLmathsans#true,false
#endkeyvals

\mathbfit{text%plain}#m
\mathsfbfit{text%plain}#m
\mathbold{text%plain}#*m
\mathboldsans{text%plain}#*m

#ifOption:OMLmathsfit
\mathsfit{text%plain}#m
\mathsans{text%plain}#*m
#endif
#ifOption:OMLmathsfit=true
\mathsfit{text%plain}#m
\mathsans{text%plain}#*m
#endif

\vectorsym{symbol}#m
\matrixsym{symbol}#m
\tensorsym{symbol}#m