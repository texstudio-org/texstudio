# drawstack package
# Matthew Bertucci 3/29/2022 for release 2010/08/06

#include:tikz
#include:tikzlibraryshapes
#include:ifthen

#keyvals:\usepackage/drawstack#c
nocolor
#endkeyvals

\begin{drawstack}#\pictureHighlight
\begin{drawstack}[TikZ options]
\end{drawstack}

\bcell{text}
\cell[TikZ options]{text}
\cell{text}
\cellcom{text}
\cellcomL{text}
\cellptr{text}
\cellround{text}
\drawstruct{(x,y)}
\ebp
\esp
\finishframe{text}
\padding{number}{text}
\separator
\separator[TikZ options]
\stackbottom[TikZ options]{text}
\stackbottom{text}
\stacktop[TikZ options]{text}
\stacktop{text}
\startframe
\structcell[TikZ options]{text}
\structcell{text}
\structname{text}

# not documented
\bigcell{number}{text}#*
\bstackbottom#*
\bstacktop#*
\cellptrnext{text}#*
\llcell{number}{TikZ options}{text}#*
\llstructcell{number}{TikZ options}{text}#*
\stackframe{num1}{num2}{text}#*
\thecellnb#*
\theptrnb#*
\thestartframe#*
\thestructnb#*
