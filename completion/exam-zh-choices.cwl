# exam-zh-choices package
# Matthew Bertucci 2023/06/02 for v0.1.25

#keyvals:\examsetup,\ExamPrintAnswerSet
choices={%<键值列表%>}
choices/index=%<integer%>
choices/column-sep=##L
choices/columns=%<integer%>
choices/label=%<label%>
choices/label-pos=#auto,top-left,left,bottom
choices/label-align=#left,center,right
choices/label-sep=##L
choices/label-width=##L
choices/max-columns=%<integer%>
choices/top-sep=##L
choices/bottom-sep=##L
choices/linesep=##L
#endkeyvals

\begin{choices}
\begin{choices}[键值列表%keyvals]
\end{choices}
\setchoices{键值列表%keyvals}

#keyvals:\begin{choices},\setchoices
index=%<integer%>
column-sep=##L
columns=%<integer%>
label=%<label%>
label-pos=#auto,top-left,left,bottom
label-align=#left,center,right
label-sep=##L
label-width=##L
max-columns=%<integer%>
top-sep=##L
bottom-sep=##L
linesep=##L
#endkeyvals

\AddChoicesCounter{LaTeX command%cmd}{internal command%definition}#d
