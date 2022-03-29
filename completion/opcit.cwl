# opcit package
# Matthew Bertucci 3/28/2022 for v2.0

#include:xspace

#keyvals:\usepackage/opcit#c
custombst
nocustombst
hyperref
nohyperref
omitting
noomitting
idem
noidem
checkidem
nocheckidem
#endkeyvals

#ifOption:hyperref
#include:hyperref
#endif

\bibcase{word}
\bibhereafter{style}
\biblastnames{last names}
\bibpunctuation#*
\bibref{bibid}#C
\cite*{bibid}#C
\cited{keylist}#C
\hereafter
\idemtext#*
\newBibCommand{command}{footnote style}{list style}#d
\nobibliography{bib file}
\opcitends
\opcitstart
\opcittext#*
\opcitwarning{warning%text}#*
\QuoteOrNot#*
\resetcites
\sameauthors
\sameauthorsrule#*
\toomit{text}
\with{field}