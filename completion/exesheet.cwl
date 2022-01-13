# exesheet package
# Matthew Bertucci 1/12/2021 for v1.3

#include:ifthen
#include:xcolor
#include:enumitem
# enumitem loaded with shortlabels option
#include:tasks
#include:versions
#include:geometry
#include:fancybox
#include:translations

#keyvals:\usepackage/exesheet#c
notoc
nosetlist
#endkeyvals

\exercise#L3
\exercise[text]#L3
\exercisename#*
\labelexercise#*
\theexercise#*
\labelexercisestyle#*
\exercise*{label%text}
\exercise*[text]{label%text}
\subpart#L4
\subpart[text]#L4
\thesubpart#*
\subpartname#*
\labelsubpart#*
\labelsubpartstyle#*
\subpart*{label%text}
\subpart*[text]{label%text}
\annex
\annex[text]
\annexname#*
\annexstyle#*
\exe
\exname#*
\exlabel#*
\exsepmark#*
\exe*
\points{number}
\pointsname#*
\pointname#*
\pointsstyle#*
\pointscolor#*

\begin{exenumerate}
\begin{exenumerate}[options%keyvals]
\end{exenumerate}
\begin{colsenum}{cols}
\begin{colsenum}[options%keyvals]{cols}
\end{colsenum}
\begin{colsenum*}{cols}
\begin{colsenum*}[options%keyvals]{cols}
\end{colsenum*}
\begin{colsitem}{cols}
\begin{colsitem}[options%keyvals]{cols}
\end{colsitem}
\begin{colsitem*}{cols}
\begin{colsitem*}[options%keyvals]{cols}
\end{colsitem*}

#keyvals:\begin{exenumerate}#c,\begin{colsenum}#c,\begin{colsenum*}#c,\begin{colsitem}#c,\begin{colsitem*}
topsep=##L
partopsep=##L
parsep=##L
itemsep=##L
leftmargin=##L
rightmargin=##L
listparindent=##L
labelwidth=##L
labelsep=##L
itemindent=##L
label=%<commands%>
label*=%<commands%>
ref=%<commands%>
font=%<commands%>
format=%<commands%>
align=#left,right,parleft
labelindent=##L
left=%<labelindent%>
left=%<labelindent%> .. %<leftmargin%>
widest
widest=%<string%>
widest*=%<integer%>
labelsep*=##L
labelindent*=##L
start=%<integer%>
resume
resume=%<series name%>
resume*
resume*=%<series name%>
series=%<series name%>
beginpenalty=%<integer%>
midpenalty=%<integer%>
endpenalty=%<integer%>
before=%<code%>
before*=%<code%>
after=%<code%>
after*=%<code%>
first=%<code%>
first*=%<code%>
style=#standard,unboxed,nextline,sameline,multiline
noitemsep
nosep
wide
wide=%<parindent%>
itemjoin=%<string%>
itemjoin*=%<string%>
afterlabel=%<string%>
mode=#unboxed,boxed
#endkeyvals

\begin{tablenum1}
\begin{tablenum1}(cols)
\begin{tablenum1}[options%keyvals](cols)
\end{tablenum1}
\begin{tablenuma}
\begin{tablenuma}(cols)
\begin{tablenuma}[options%keyvals](cols)
\end{tablenuma}
\begin{tablitem}
\begin{tablitem}(cols)
\begin{tablitem}[options%keyvals](cols)
\end{tablitem}

#keyvals:\begin{tablenum1}
style=#itemize,enumerate
label-format=%<code%>
label=%<code%>
ref=%<code%>
label-width=##L
label-offset=##L
item-format=%<code%>
item-indent=##L
column-sep=##L
label-align=#left,right,center
before-skip=##L
after-skip=##L
after-item-skip=##L
resume#true,false
start=%<integer%>
counter=%<counter%>
debug#true,false
#endkeyvals

\begin{questions}
\end{questions}
\begin{answers}
\begin{answers}[level]
\end{answers}
\begin{answers*}
\end{answers*}

\questionsonly
\answersonly

\correctionstyle#*
correctioncolor#B
\correctionname#*

\question{question%text}{answer%text}

\pts{number}
\ptsname#*
\ptname#*
ptscolor#B
\ptsstyle#*
\displaypts
\totalexe{number}
\note{comment%text}
\note[points]{comment%text}
\note*{points}
markingcolor#B
\markingstyle#B
\ptsboxlength#B
notecolor#B
\notestyle#B
\noteragged#B
\displaypoints
\displaynotes
\displaynotes[align cmd]
\displaynotesright
\displaynotesright[align cmd]
\totalpoints{number}

# from shortlabels option of enumitem
#keyvals:\begin{enumerate}#c,\begin{itemize}#c,\begin{description}#c,\begin{enumerate*}#c,\begin{itemize*}#c,\begin{description*}#c,\begin{exenumerate}#c
A
a
I
i
1
#endkeyvals