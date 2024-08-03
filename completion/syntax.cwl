# syntax package
# Matthew Bertucci 2024/07/21 for v1.07

#keyvals:\usepackage/syntax#c
rounded
square
nounderscore
#endkeyvals

\shortverb{\%<<char>%>}
\begin{shortverb}{\%<<char>%>}
\end{shortverb}
\unverb{\%<<char>%>}
\synt{text}
\lit{text}
\lit*{text}
\syntax{syntax}
\synshorts
\begin{synshorts}
\end{synshorts}
\synshortsoff
\begin{grammar}
\end{grammar}
\alt
\grammarparsep#*L
\grammarindent#*L
\grammarlabel#*
\begin{syntdiag}
\begin{syntdiag}[commands]
\end{syntdiag}
\begin{syntdiag*}
\begin{syntdiag*}[commands]
\end{syntdiag*}
\tok{text}
\begin{stack}
\end{stack}
\begin{rep}
\end{rep}
\sdsize#*
\sdlengths#*
\sdstartspace#*L
\sdendspace#*L
\sdmidskip#*L
\sdtokskip#*L
\sdfinalskip#*L
\sdrulewidth#*L
\sdcirclediam#*L
\syntleft#*
\syntright#*
\litleft#*
\litright#*
\ulitleft#*
\ulitright#*

# not documented
\addspecial{arg1}#S
\readupto{arg1}{arg2}{arg3}#S
\remspecial{arg1}#S
\begin{sdbox}{arg1}#S
\end{sdbox}#S
\syntaxShortcuts{arg1}{arg2}#S
\ttthickspace#S
\ttthinspace#S