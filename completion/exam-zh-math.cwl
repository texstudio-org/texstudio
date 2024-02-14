# exam-zh-math package
# Matthew Bertucci 2024/02/13 for v0.2.1

#include:tabularray
#include:varwidth
#include:graphicx
#include:filehook
#include:wrapstuff

#keyvals:\examsetup,\ExamPrintAnswerSet
calculations=%<{〈键值列表〉}%>
calculations/index=%<integer%>
calculations/columns=%<integer%>
calculations/fig-pos=#top,above,bottom,below,left,right,left-top
calculations/top-sep=##L
calculations/bottom-sep=##L
calculations/hsep=##L
calculations/vsep=##L
calculations/align=#t,m,b
calculations/xshift=##L
calculations/hshift=##L
calculations/yshift=##L
calculations/vshift=##L
calculations/label-xshift=##L
calculations/label-hshift=##L
calculations/label-yshift=##L
calculations/label-vshift=##L
#endkeyvals

\begin{calculations}
\begin{calculations}[键值列表%keyvals]
\end{calculations}

#keyvals:\begin{calculations}
label=%<code%>
index=%<integer%>
columns=%<integer%>
fig-pos=#top,above,bottom,below,left,right,left-top
top-sep=##L
bottom-sep=##L
hsep=##L
vsep=##L
align=#t,m,b
xshift=##L
hshift=##L
yshift=##L
vshift=##L
label-xshift=##L
label-hshift=##L
label-yshift=##L
label-vshift=##L
#endkeyvals

\AddCalculationsCounter{arg1}{arg2}#S