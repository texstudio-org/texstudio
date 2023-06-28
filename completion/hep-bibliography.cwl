# hep-bibliography package
# Matthew Bertucci 2022/06/10 for v1.0

#include:kvoptions
#include:biblatex
#include:relsize

#keyvals:\usepackage/hep-bibliography#c
style=#authoryear,authortitle,alphabetic,numeric,alphabetic-verb,authortitle-comp,authortitle-ibid,authortitle-icomp,authortitle-tcomp,authortitle-terse,authortitle-ticomp,authoryear-comp,authoryear-ibid,authoryear-icomp,debug,draft,numeric-comp,numeric-verb,reading,verbose,verbose-ibid,verbose-inote,verbose-note,verbose-trad1,verbose-trad2,verbose-trad3
#endkeyvals

\online{text}{URL}#*U
\email{email%URL}#*U
\begin{commalist}#*
\begin{commalist}[opt]#*
\end{commalist}#*
\commalistbody#*
\relateddelimerratum#*

\ccite[prenote][postnote]{bibid}#C
\ccite[postnote]{bibid}#C
\ccite{bibid}#C
\Ccite[prenote][postnote]{bibid}#C
\Ccite[postnote]{bibid}#C
\Ccite{bibid}#C