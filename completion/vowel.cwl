# vowel package
# Matthew Bertucci 9/21/2021 for v1.1

\begin{vowel}
\begin{vowel}[options%keyvals]
\end{vowel}

#keyvals:\begin{vowel}
plain
simple
standard
ipanew
rectangle
triangle
three
#endkeyvals

\putcvowel{symbol}{num}#/vowel
\putcvowel[dot pos%keyvals]{symbol}{num}#/vowel
\putvowel{symbol}{x%l}{y%l}#/vowel
\putvowel[dot pos%keyvals]{symbol}{x%l}{y%l}#/vowel

#keyvals:\putcvowel,\putvowel
l
r
#endkeyvals

\super{text}#*
\vowelhunit#*
\vowelvunit#*
\vowelsep#*
\vowelline#*
\vowelsymbol#*
\diagrate#*
\ifrectdgm#*
\rectdgmtrue#*
\rectdgmfalse#*
\iftriangledgm#*
\triangledgmtrue#*
\triangledgmfalse#*
\ifthreelevel#*
\threeleveltrue#*
\threelevelfalse#*
\ifnoerase#*
\noerasetrue#*
\noerasefalse#*
\diagline{arg1}{arg2}#*
