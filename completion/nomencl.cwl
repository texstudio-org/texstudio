# nomencl.sty
# A. Weder 2010/07/10
# http://sarovar.org/projects/nomencl
# http://www.ctan.org/tex-archive/macros/latex/contrib/nomencl/
# Version: 4.2 2005/09/21
# Matthew Bertucci 11/6/2021 for v5.5

#include:xkeyval
#include:ifthen
#include:tocbasic

\makenomenclature
\printnomenclature
\printnomenclature[space%l]
\nomenclature[prefix]{symbol}{description}
\nomenclature{symbol}{description}

\nomrefeq
\nomrefpage
\nomrefeqpage
\nomnorefeq
\nomnorefpage
\nomnorefeqpage

#ifOption:nomentbl
#include:array
#include:longtable
#include:siunitx
\nomenclature[prefix]{symbol}{description}{units}{note}
\nomenclature{symbol}{description}{units}{note}
\setnomtableformat{column format}
#endif

\nomlabelwidth#*
\begin{thenomenclature}#*
\end{thenomenclature}#*
\nomname#*
\nomAname#*
\nomGname#*
\nomXname#*
\nomZname#*
\nomgroup#*
\nompreamble#*
\nompostamble#*
\nomitemsep#*
\nomprefix#*
\nomlabel#*
\nomentryend#*
\eqdeclaration#*
\pagedeclaration#*
\nomeqref{arg}#*
\nomeqref{arg}#*
\nompageref{arg}#*

#ifOption:compatible
\makeglossary
\printglossary
#endif
