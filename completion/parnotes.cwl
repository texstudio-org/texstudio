# parnotes package
# Matthew Bertucci 11/3/2021 for v3b

#keyvals:\usepackage/parnotes#c
restart
reset
roman
alph
symbol
breakwithin
indentafter
narrower
nomultiple
notesrm
notesit
notessf
#endkeyvals

\parnote{text}
\parnote[label]{text}#l
\begin{autopn}
\end{autopn}
\parnotes
\parnotereset
\parnoteclear
\parnoteref{label}#r
\parnotemark{text}

\parnotefmt{text}#*
\theparnotemark#*
\parnotevskip#*
\parnoteintercmd#*
\parnotecusmarkfmt{mark}#*
