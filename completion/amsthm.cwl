# amsthm package
# Ryan Reich/2007-11-03
# muzimuzhi/1 Sep 2019, amsthm v2.20.3

\newtheorem*{envname}{caption}#N
\theoremstyle{style%keyvals}
#keyvals:\theoremstyle#c
plain
definition
remark
%theoremstyle
#endkeyvals
\swapnumbers
\newtheoremstyle{style name%specialDef}{space above}{space below}{body font}{indent amount}{head font}{head punct}{after head space}{head spec}#s#%theoremstyle
\thmname{arg}
\thmnumber{arg}
\thmnote{arg}
\begin{proof}
\begin{proof}[heading]
\end{proof}
\qedsymbol
\qedhere
\qed
\proofname
\nopunct#*
\thmhead{arg1}{arg2}{arg3}#*
\swappedhead{arg1}{arg2}{arg3}#*
\mathqed#*
\pushQED{arg}#*
\popQED#*
\openbox
\textsquare
\thmheadnl#*
