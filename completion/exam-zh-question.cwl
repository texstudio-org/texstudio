# exam-zh-question package
# Matthew Bertucci 2023/06/02 for v0.1.25

#include:amsthm
#include:tcolorbox
#include:tcolorboxlibrarymost
#include:xeCJKfntef
#include:enumitem
#include:linegoal
#include:tikzlibraryshapes.misc

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
question/points-prelabel=%<points 前面的内容%>
question/points-postlabel=%<points 后面的内容%>
question/label-align=#left,center,right
problem={%<键值列表%>}
problem/show-answer#true,false
problem/points=%<number%>
problem/show-points=#true,auto,false
problem/points-separate-par#true,false
problem/top-sep=##L
problem/bottom-sep=##L
problem/index=%<integer%>
problem/label=%<label%>
problem/points-prelabel=%<points 前面的内容%>
problem/points-postlabel=%<points 后面的内容%>
problem/label-align=#left,center,right
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
fillin/depth=##L
solution={%<键值列表%>}
solution/show-solution#true,false
solution/show-answer#true,false
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
points-prelabel=%<points 前面的内容%>
points-postlabel=%<points 后面的内容%>
label-align=#left,center,right
#endkeyvals

#keyvals:\begin{question},\questionsetup
combine-fillin#true,false
combine-fillin-args=%<\fillin 命令的参数%>
hang#true,false
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
width-type=#fill,normal
color=#%color
text-color=#%color
paren-type=#banjiao,quanjiao
depth=##L
#endkeyvals

\AddFillinCounter{LaTeX command%cmd}{internal command%definition}#d

\begin{solution}
\begin{solution}[键值列表%keyvals]
\end{solution}

#keyvals:\begin{solution}
show-solution#true,false
show-answer#true,false
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
