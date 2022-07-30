# exam-zh-choices package
# Matthew Bertucci 2022/07/29 for v0.1.13

#include:expl3
#include:xparse

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
#endkeyvals

\AddChoicesCounter{LaTeX command%cmd}{internal command%definition}#d