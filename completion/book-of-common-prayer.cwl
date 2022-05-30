# book-of-common-prayer package
# Matthew Bertucci 2022/05/30 for v1.1.0

#include:fontspec
#include:geometry
#include:titlesec
#include:graphicx
#include:titling
#include:alltt
#include:paracol
#include:framed
#include:makecell
#include:xtab
#include:tocloft
#include:xcolor
#include:pgfornament
#include:enumitem
#include:pgf
#include:pgfopts
#include:bilingualpages
#include:changepage

#keyvals:\usepackage/book-of-common-prayer#c
sabon
#endkeyvals

\versicle
\response
\cross
\scross
\gl
\gr
\blankline
\deleteline
\tab
\spacer
\instruct{instructions%text}
\instructsmall{instructions%text}
\bibleref{reference}
\bibleverse{text}{reference}
\monarch{name}
\boxaround{text}
\begin{responses}
\end{responses}
\priest{text}
\deacon{text}
\subdeacon{text}
\officiant{text}
\lector{text}
\epistoler{text}
\people{text}
\servers{text}
\contd{text}
\pretre{text}#*
\diacre{text}#*
\peuple{text}#*
\servants{text}#*
\begin{vresponses}
\end{vresponses}
\V{versicle%text}
\R{response%text}
\rlong{text}
\begin{vresponsesdouble}
\begin{vresponsesdouble}[width factor]
\end{vresponsesdouble}
\VR{versicle%text}{response%text}
\begin{prayer}
\end{prayer}
\begin{twocolprayer}#\tabular
\end{twocolprayer}
\begin{threecolprayer}#\tabular
\end{threecolprayer}
\psalmverse{text1%text}{text2%text}
\begin{responsesex}#\tabular
\end{responsesex}
\begin{vresponsesex}
\end{vresponsesex}
\begin{vresponsesdoubleex}
\begin{vresponsesdoubleex}[width factor]
\end{vresponsesdoubleex}
\continued
\sabon{text}

# not documented
\betweenLilyPondSystem{arg}#*
\boxit{arg}#*
\crossfont#*
\header{text}#*
\hist{text}#*
\makesectionline{color}{number}#*
\munepsfig[options]{imagefile}{rule thickness}#*g
\munepsfig{imagefile}{rule thickness}#*g
\sectionline#*
\smallcapsheader{text}#*
\textjuni{text}#*
\textuni{text}#*
\versiclefont#*