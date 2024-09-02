# interlinear package
# Matthew Bertucci 2024/08/26 for v1.0

#include:marginnote
#include:xifthen
#include:xkeyval
#include:etoolbox
#include:enumitem

\begin{interlinear}
\begin{interlinear}[options%keyvals]
\end{interlinear}

\ct
\DeclareInterlinearStyle{name}{options%keyvals}
\ft
\gj
\gl
\interlinearstyle{options%keyvals}
\li
\lt
\mb
\nt
\ps
\rf
\tx
\UseInterlinearStyle{name}

# not documented
\ifnoglosslines#S
\ifnotdone#S
\IfValueArgTF{arg1}{arg2}{arg3}{arg4}#S
\langinfo#S
\noglosslinesfalse#S
\noglosslinestrue#S
\notdonefalse#S
\notdonetrue#S
\switchlwsyntaxoff#S
\switchlwsyntaxon#S
\usedoublespacing#S
\useonehalfspacing#S
\usesinglespacing#S