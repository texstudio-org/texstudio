# exam-zh-textfigure package
# Matthew Bertucci 2023/06/02 for v0.1.25

#include:wrapstuff
#include:tabularray
#include:varwidth
#include:graphicx
#include:filehook

#keyvals:\examsetup,\ExamPrintAnswerSet
multifigures={%<键值列表%>}
multifigures/columns=%<integer%>
multifigures/fig-pos=#top,above,bottom,below,left,right
multifigures/top-sep=##L
multifigures/bottom-sep=##L
multifigures/align=#t,m,b
multifigures/xshift=##L
multifigures/hshift=##L
multifigures/yshift=##L
multifigures/vshift=##L
multifigures/label-xshift=##L
multifigures/label-hshift=##L
multifigures/label-yshift=##L
multifigures/label-vshift=##L
textfigure={%<键值列表%>}
textfigure/fig-pos=#left,right,top,bottom,top-left,top-right,top-center,top-flushright,bottom-flushright,bottom-left,bottom-right,bottom-center,right-top,right-bottom,right-center,left-top,left-bottom,left-center
textfigure/figure-xshift=##L
textfigure/figure-hshift=##L
textfigure/figure-yshift=##L
textfigure/figure-vshift=##L
textfigure/xshift=##L
textfigure/hshift=##L
textfigure/yshift=##L
textfigure/vshift=##L
textfigure/top-sep=##L
textfigure/bottom-sep=##L
textfigure/text-width=##L
textfigure/figure-width=##L
textfigure/ratio=%<比例%>
textfigure/text-ratio=%<比例%>
textfigure/top=%<integer%>
textfigure/parindent=##L
#endkeyvals

\begin{multifigures}
\begin{multifigures}[键值列表%keyvals]
\end{multifigures}

#keyvals:\begin{multifigures}
columns=%<integer%>
fig-pos=#top,above,bottom,below,left,right
top-sep=##L
bottom-sep=##L
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

\textfigure{文本%text}{图片}
\textfigure[参数列表%keyvals]{文本%text}{图片}

#keyvals:\textfigure
fig-pos=#left,right,top,bottom,top-left,top-right,top-center,top-flushright,bottom-flushright,bottom-left,bottom-right,bottom-center,right-top,right-bottom,right-center,left-top,left-bottom,left-center
figure-xshift=##L
figure-hshift=##L
figure-yshift=##L
figure-vshift=##L
xshift=##L
hshift=##L
yshift=##L
vshift=##L
top-sep=##L
bottom-sep=##L
text-width=##L
figure-width=##L
ratio=%<比例%>
text-ratio=%<比例%>
top=%<integer%>
parindent=##L
#endkeyvals
