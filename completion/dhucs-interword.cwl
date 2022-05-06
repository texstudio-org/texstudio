# dhucs-interword package
# Matthew Bertucci 2022/05/04

#include:dhucs
#include:verbatim

#keyvals:\usepackage/dhucs-interword#c
HWP
default
nonfrench
wider
narrower
#endkeyvals

\interhchar{space%l}
\interHchar{space%l}#S
\interhword{skip}{plus}{minus}
\interhword[xskip]{skip}{plus}{minus}

# not documented
\begin{engtext}#*
\end{engtext}#*
\DEFAULTskips#*
\HWPinterwordskip#*
\narrowerhangul#*
\setinterwordskip{skip}{plus}{minus}#*
\setinterwordskip[xskip]{skip}{plus}{minus}#*
\ucsfninterwordhook#*
\widerhangul#*