# exesheet package
# Matthew Bertucci 2023/01/18 for v2.0

#include:kvoptions
#include:ifthen
#include:geometry
#include:xcolor
#include:enumitem
# loads shortlabels option of enumitem
#include:tasks
#include:versions
#include:fancybox
#include:translations
#include:ragged2e

\exesheetset{options%keyvals}

#keyvals:\exesheetset,\usepackage/exesheet#c
exetoc#true,false
setlist#true,false
output=#questions,answers,both
display=#none,pts,notes
answerspace#true,false
marginpos=#left,right,inner,outer
marginwidth=#standard,expand,unset
noteragged=#left,right,center,justify,twoside
checkpts#true,false
correct=#true,false,conditional
#endkeyvals

\exercise#L3
\exercise[text]#L3
\exercisename#*
\labelexercise#*
\theexercise#*
\labelexercisestyle#*
\exercise*{label%text}#L3
\exercise*[text]{label%text}#L3
\subpart#L4
\subpart[text]#L4
\thesubpart#*
\subpartname#*
\labelsubpart#*
\labelsubpartstyle#*
\subpart*{label%text}#L4
\subpart*[text]{label%text}#L4
\annex
\annex[text]
\annexname#*
\annexstyle#*
\exe
\exname#*
\exlabel#*
\exsepmark#*
\exe*

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

#keyvals:\begin{exenumerate}#c,\begin{colsenum}#c,\begin{colsenum*}#c,\begin{colsitem}#c,\begin{colsitem*}#c
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
%enumitemkey
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

\correctionstyle#*
correctioncolor#B
\correctionname#*

\question{question%text}
\answer{answer%text}
\answerspace{height}
\points{number}
\pointsname#*
\pointname#*
\pointsstyle#*
pointscolor#B
\pts{number}
\ptsname#*
\ptname#*
ptscolor#B
\ptsstyle#*

\totalexe{number}
\note{comment%text}
\note[points]{comment%text}
\note*{points}
markingcolor#B
\markingstyle#*
\ptsboxlength#*
notecolor#B
\notestyle#*
\totalpoints{number}
\totalsheet{number}

# from shortlabels option of enumitem
#keyvals:\begin{enumerate}#c,\begin{itemize}#c,\begin{description}#c,\begin{enumerate*}#c,\begin{itemize*}#c,\begin{description*}#c,\begin{exenumerate}#c,\begin{colsenum}#c,\begin{colsenum*}#c
A
a
I
i
1
#endkeyvals

# not documented
\gaddtolength{register}{length}#S
\gsetlength{register}{length}#S
\largemarginwidthfactor#S
\leftnotemarginwidth{length}#S
\noteragged#S
\noteraggedleft#S
\noteraggedright#S
\ptsmark#S
\rightnotemarginwidth{length}#S
\standardfrenchlists#S
\standardmarginwidthfactor#S

# deprecated
\questionsonly#S
\answersonly#S
\displaypts#S
\displaypoints#S
\displaynotes#S
\displaynotes[align cmd]#S
\displaynotesright#S
\displaynotesright[align cmd]#S
