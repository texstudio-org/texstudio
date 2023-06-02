# exam-zh class
# Matthew Bertucci 2023/06/02 for v0.1.25

#include:filehook
#include:class-ctexbook
#include:etoolbox
#include:geometry
#include:fontspec
#include:xeCJK
#include:xeCJKfntef
#include:fancyhdr
#include:lastpage
#include:amsmath
#include:enumitem
#include:varwidth
#include:tikzpagenodes
#include:tikzlibrarydecorations.markings
#include:tikzlibrarydecorations.text
#include:exam-zh-question
#include:exam-zh-font
#include:exam-zh-choices
#include:exam-zh-symbols
#include:exam-zh-chinese-english
#include:exam-zh-textfigure
#include:hyperref
#include:pifont

# all options passed to ctexbook
#keyvals:\documentclass/exam-zh#c
GBK
UTF8
zhmap=#true,false,zhmCJK
zihao=#-4,5,false
heading#true,false
sub3section
sub4section
scheme=#chinese,plain
linespread=%<number%>
fontset=#adobe,fandol,founder,mac,macnew,macold,ubuntu,windows,none
punct=#quanjiao,banjiao,kaiming,CCT,plain
space=#true,false,auto
autoindent=
# options passed to book class
a4paper
a5paper
b5paper
letterpaper
legalpaper
executivepaper
landscape
10pt
11pt
12pt
oneside
twoside
draft
final
titlepage
notitlepage
openright
openany
onecolumn
twocolumn
leqno
fleqn
openbib
#endkeyvals

\ExamPrintAnswerSet{keyvals}
\ExamPrintAnswerSet[cmd list]{keyvals}
\ExamPrintAnswer
\examsetup{键值列表%keyvals}

# NOTE: other keys for \examsetup listed in cwls for support packages exam-zh-question etc.
#keyvals:\ExamPrintAnswerSet,\examsetup
notice={%<键值列表%>}
notice/label=%<label%>
notice/label-format=%<format%>
notice/top-sep=##L
notice/bottom-sep=##L
style={%<键值列表%>}
style/fullwidth-stop=#catcode,false
style/footnote-style=#plain,libertinus,libertinus*,libertinus-sans,pifont,pifont*,pifont-sans,pifont-sans*,xits,xits-sans,xits-sans*
style/student-version-suffix=%<suffix%>
style/student-version-cleanaux#true,false
page={%<键值列表%>}
page/size=%<a3paper|a4paper%>
page/show-head#true,false
page/head-content=%<页眉格式%>
page/show-foot#true,false
page/foot-type=#common,separate
page/foot-content=%<页脚格式%>
page/show-columnline#true,false
page/columnline-width=##L
page/show-chapter#true,false
sealline={%<键值列表%>}
sealline/show#true,false
sealline/scope=#firstpage,oddpage,everypage,first-and-last,mod-2,mod-3,mod-4,mod-6
sealline/type=#firstpage,oddpage,everypage,first-and-last,mod-2,mod-3,mod-4,mod-6
sealline/line-thickness=##L
sealline/odd-line-thickness=##L
sealline/even-line-thickness=##L
sealline/line-xshift=##L
sealline/odd-line-xshift=##L
sealline/even-line-xshift=##L
sealline/line-yshift=##L
sealline/odd-line-yshift=##L
sealline/even-line-yshift=##L
sealline/line-type=#solid,dotted,densely-dotted,loosely-dotted,dashed,densely-dashed,loosely-dashed,dash-dot,densely-dash-dot,loosely-dash-dot,dash-dot-dot,densely-dash-dot-dot,loosely-dash-dot-dot
sealline/odd-line-type=#solid,dotted,densely-dotted,loosely-dotted,dashed,densely-dashed,loosely-dashed,dash-dot,densely-dash-dot,loosely-dash-dot,dash-dot-dot,densely-dash-dot-dot,loosely-dash-dot-dot
sealline/even-line-type=#solid,dotted,densely-dotted,loosely-dotted,dashed,densely-dashed,loosely-dashed,dash-dot,densely-dash-dot,loosely-dash-dot,dash-dot-dot,densely-dash-dot-dot,loosely-dash-dot-dot
sealline/text=%<content%>
sealline/odd-text=%<content%>
sealline/even-text=%<content%>
sealline/text-width=##L
sealline/odd-text-width=##L
sealline/even-text-width=##L
sealline/text-format=%<font commands%>
sealline/odd-text-format=%<font commands%>
sealline/even-text-format=%<font commands%>
sealline/text-xshift=##L
sealline/odd-text-xshift=##L
sealline/even-text-xshift=##L
sealline/text-yshift=##L
sealline/odd-text-yshift=##L
sealline/even-text-yshift=##L
sealline/text-xscale=%<float point%>
sealline/odd-text-xscale=%<float point%>
sealline/even-text-xscale=%<float point%>
sealline/text-yscale=%<float point%>
sealline/odd-text-yscale=%<float point%>
sealline/even-text-yscale=%<float point%>
sealline/text-direction-vertical#true,false
sealline/odd-text-direction-vertical#true,false
sealline/even-text-direction-vertical#true,false
sealline/circle-show#true,false
sealline/odd-circle-show#true,false
sealline/even-circle-show#true,false
sealline/circle-start=%<float point%>
sealline/odd-circle-start=%<float point%>
sealline/even-circle-start=%<float point%>
sealline/circle-end=%<float point%>
sealline/odd-circle-end=%<float point%>
sealline/even-circle-end=%<float point%>
sealline/circle-step=##L
sealline/odd-circle-step=##L
sealline/even-circle-step=##L
sealline/circle-diameter=##L
sealline/odd-circle-diameter=##L
sealline/even-circle-diameter=##L
sealline/circle-xshift=##L
sealline/odd-circle-xshift=##L
sealline/even-circle-xshift=##L
sealline/odd-info-content={%<comma list%>}
sealline/odd-info-separator=%<separator%>
sealline/odd-info-align=#left,center,right
sealline/odd-info-xshift=##L
sealline/odd-info-yshift=##L
square={%<键值列表%>}
square/x-length=##L
square/y-length=##L
square/baseline=##L
square/linewidth=##L
square/xshift=##L
title={%<键值列表%>}
title/title-format=%<格式命令%>
title/subject-format=%<格式命令%>
title/top-sep=##L
title/bottom-sep=##L
list={%<键值列表%>}
list/step-name=%<step 环境 label 名%>
list/method-name=%<method 环境 label 名%>
list/case-name=%<case 环境 label 名%>
list/step-punct=%<step 环境 label 后的标点%>
list/method-punct=%<method 环境 label 后的标点%>
list/case-punct=%<case 环境 label 后的标点%>
draft={%<键值列表%>}
draft/watermark-size=##L
draft/show-watermark#true,false
draft/show-draft=#auto,manual
scoringbox={%<键值列表%>}
scoringbox/type=#onecolumn,twocolumn,none
scoringbox/position=#left,right
#endkeyvals

\information{信息内容%text}
\information[分隔符]{信息内容%text}
\warning{警告%text}
\secret
\secret[格式命令]

\begin{notice}
\begin{notice}[键值列表 1%keyvals]
\begin{notice}[键值列表 1%keyvals][键值列表 2]
\end{notice}

#keyvals:\begin{notice}
label=%<label%>
label-format=%<format%>
top-sep=##L
bottom-sep=##L
#endkeyvals

\subject{科目%text}
\subject[宽度]{科目%text}

\begin{step}
\end{step}
\begin{method}
\end{method}
\begin{case}
\end{case}

\draftpaper
\draftpaper[参数列表%keyvals]

#keyvals:\draftpaper
watermark-size=##L
show-watermark#true,false
show-draft=#auto,manual
#endkeyvals

\examsquare{方格个数}
\examsquare[参数列表%keyvals]{方格个数}

#keyvals:\examsquare
x-length=##L
y-length=##L
baseline=##L
linewidth=##L
xshift=##L
#endkeyvals

\scoringbox
\scoringbox*

\examzholdsection{title}#SL2
