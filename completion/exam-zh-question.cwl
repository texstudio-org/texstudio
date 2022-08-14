# exam-zh-question package
# Matthew Bertucci 2022/08/14 for v0.1.17

#include:expl3
#include:xparse
#include:amsthm
#include:tcolorbox
# loads most option of tcolorbox
#include:xeCJKfntef
#include:linegoal
# loads shapes.misc tikzlibrary

#keyvals:\examsetup,\ExamPrintAnswerSet
question={%<键值列表%>}
question/show-answer#true,false
question/points=%<number%>
question/show-points=#true,auto,false
question/points-separate-par#true,false
question/top-sep=##L
question/bottom-sep=##L
question/index=%<integer%>
question/label=%<label%>
question/combine-fillin#true,false
question/combine-fillin-args=%<\fillin 命令的参数%>
question/hang#true,false
question/label-align=#left,center,right
paren={%<键值列表%>}
paren/show-answer#true,false
paren/show-paren#true,false
paren/text-color=#%color
paren/type=#hfill,none
fillin={%<键值列表%>}
fillin/type=#line,paren,circle,rectangle,blank
fillin/no-answer-type=#blacktriangle,counter,none
fillin/no-answer-counter-index=%<integer%>
fillin/no-answer-counter-label=%<label%>
fillin/show-answer#true,false
fillin/width=##L
fillin/width-type=#fill,normal
fillin/color=#%color
fillin/text-color=#%color
fillin/paren-type=#banjiao,quanjiao
solution={%<键值列表%>}
solution/show-solution#true,false
solution/parbreak#true,false
solution/show-qed#true,false
solution/qedsymbol=%<symbol%>
solution/label-content=%<content%>
solution/label-punct=%<punct%>
solution/score-pre-content=%<content%>
solution/score-post-content=%<content%>
solution/score-format=%<风格设置%>
solution/score-showleader#true,false
solution/text-color=#%color
solution/top-sep=##L
solution/bottom-sep=##L
solution/blank-type=#none,manual,hide
solution/blank-vsep=##L
#endkeyvals

\begin{question}
\begin{question}[键值列表%keyvals]
\end{question}
\begin{problem}
\begin{problem}[键值列表%keyvals]
\end{problem}
\questionsetup{键值列表%keyvals}

#keyvals:\begin{question},\begin{problem},\questionsetup
show-answer#true,false
points=%<number%>
show-points=#true,auto,false
points-separate-par#true,false
top-sep=##L
bottom-sep=##L
index=%<integer%>
label=%<label%>
combine-fillin#true,false
combine-fillin-args=%<\fillin 命令的参数%>
hang#true,false
label-align=#left,center,right
#endkeyvals

\paren
\paren[答案]
\AddQuestionCounter{LaTeX command%cmd}{internal command%definition}#d
\circlednumber{数字或计数器名字}
\circlednumber*{数字或计数器名字}
\tikzcirclednumber{数字或计数器名字}#S
\tikzcirclednumber*{数字或计数器名字}#S

\fillin
\fillin[答案]
\fillin[键值列表%keyvals][答案]
\fillin*
\fillin*[答案]
\fillin*[键值列表%keyvals][答案]
\fillinsetup{键值列表%keyvals}

# need #c because of odd syntax for \fillin
#keyvals:\fillin#c,\fillin*#c,\fillinsetup
type=#line,paren,circle,rectangle,blank
no-answer-type=#blacktriangle,counter,none
no-answer-counter-index=%<integer%>
no-answer-counter-label=%<label%>
show-answer#true,false
width=##L
color=#%color
text-color=#%color
#endkeyvals

\AddFillinCounter{LaTeX command%cmd}{internal command%definition}#d

\begin{solution}
\begin{solution}[键值列表%keyvals]
\end{solution}

#keyvals:\begin{solution}
show-solution#true,false
parbreak#true,false
show-qed#true,false
qedsymbol=%<symbol%>
label-content=%<content%>
label-punct=%<punct%>
score-pre-content=%<content%>
score-post-content=%<content%>
score-format=%<风格设置%>
score-showleader#true,false
text-color=#%color
top-sep=##L
bottom-sep=##L
blank-type=#none,manual,hide
blank-vsep=##L
#endkeyvals

\score{分数}

# from most option of tcolorbox
#include:amsmath
#include:incgraph
#include:listings
#include:listingsutf8
#include:pdftexcmds
#include:shellesc
#include:tikz
#include:pdfcol
