# lltjp-listings package
# Matthew Bertucci 2022/07/04 for release 2022-05-22

#include:etoolbox
#include:listings
#include:luatexbase

#keyvals:\lstset,\lstinline,\begin{lstlisting},\lstinputlisting,\lstMakeShortInline,\lstdefinelanguage,\lstdefinestyle
vsraw#true,false
vscmd=%<cmd%>
doubleletterspace=
#endkeyvals

\ltjlistingsvsstdcmd{arg}
\CatcodeTableLTJlistings#*