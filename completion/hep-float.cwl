# hep-float package
# Matthew Bertucci 2022/11/03 for v1.1

#include:kvoptions
#include:subcaption
#include:calc
#include:etoolbox
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

\panelhspace#*
\panelvspace#*
\tikzsetnextfilename{imagefile}#*g
