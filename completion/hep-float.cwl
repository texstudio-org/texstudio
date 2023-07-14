# hep-float package
# Matthew Bertucci 2023/07/14 for v1.2

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

\begin{figures}{width%plain}
\begin{figures}[alignment]{width%plain}
\end{figures}
\begin{panels}{width%plain}
\begin{panels}[alignment]{width%plain}
\end{panels}
\begin{tables}{width%plain}
\begin{tables}[alignment]{width%plain}
\end{tables}
\panel{width}
\graphic{imagefile}#g
\graphic[width]{imagefile}#g
\graphics{file path}

\figurehspace#*
\figurevspace#*
\panelhspace#*
\panelvspace#*
\tablehspace#*
\tablevspace#*
\tikzsetnextfilename{imagefile}#*g
