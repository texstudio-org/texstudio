# uassign package
# Matthew Bertucci 1/22/2022 for v1.01

#include:ifthen
#include:hyperref
#include:bookmark
#include:color
#include:enumerate
#include:amsmath
#include:fancyhdr
#include:titlesec
#include:amsthm

#keyvals:\usepackage/uassign#c
hideanswers
hidequestions
assignheader
notesheader
links
#endkeyvals

\ebox{}#*
\ientry{entry%text}
\thequestioncounter#*
\thesolutioncounter#*
\trashcan#*
\begin{question}
\end{question}
\begin{solution}
\begin{solution}[length]#*
\end{solution}
\theexamplecounter#*
\theexsolutioncounter#*
\thedefcounter#*
\begin{example}
\end{example}
\begin{exsolution}
\end{exsolution}
\begin{definition}
\end{definition}