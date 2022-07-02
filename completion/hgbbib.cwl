# hgbbib package
# Matthew Bertucci 2022/07/01

#include:csquotes
#include:biblatex

\AddBibFile{bib file}#*
\MakeBibliography
\MakeBibliography[nosplit]%|
\begin{bibhyphenation}#*
\end{bibhyphenation}#*
\mcite{bibid}{bibid}#C
\mcite(post){bibid}{bibid}#*C
\mcite(pre)(post){bibid}{bibid}#C
\mcite(pre)(post)[post]{bibid}[post]{bibid}#*C
\mcite[post]{bibid}[post]{bibid}#*C
\mcite[pre][post]{bibid}[pre][post]{bibid}#*C
\mcite(pre)(post)[pre][post]{bibid}[pre][post]{bibid}#C
\citenobr{bibid}#C
\citenobr[postnote]{bibid}#C
\citenobr[prenote][postnote]{bibid}#C