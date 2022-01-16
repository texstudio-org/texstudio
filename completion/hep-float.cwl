# hep-float package
# Matthew Bertucci 11/13/2021 for v1.0

#include:kvoptions
#include:subcaption
#include:booktabs
#include:multirow
#include:graphicx

#keyvals:\usepackage/hep-float#c
manualplacement#true,false
#endkeyvals

\begin{panels}{width%plain}
\begin{panels}[alignment]{width%plain}
\end{panels}
\panel{width}
\graphic{imagefile}#g
\graphic[width]{imagefile}#g
\graphics{file path}

\tikzsetnextfilename{arg}#*