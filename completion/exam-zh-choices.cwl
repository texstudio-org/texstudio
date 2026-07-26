# exam-zh-choices package
# Matthew Bertucci 2026/07/24 for v0.3.0

#include:xcolor
#include:exam-zh-counter

#keyvals:\examsetup,\ExamPrintAnswerSet
choices={%<键值列表%>}
choices/index=%<integer%>
choices/show-answer#true,false
choices/answer-color=#%color
choices/column-sep=##L
choices/left-indent=##L
choices/right-indent=##L
choices/margin=##L
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
choices/item-linesep=##L
#endkeyvals

\begin{choices}
\begin{choices}[键值列表%keyvals]
\end{choices}
\setchoices{键值列表%keyvals}

#keyvals:\begin{choices},\setchoices
index=%<integer%>
show-answer#true,false
answer-color=#%color
column-sep=##L
left-indent=##L
right-indent=##L
margin=##L
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
item-linesep=##L
#endkeyvals

\AddChoicesCounter{LaTeX command%cmd}{internal command%definition}#d