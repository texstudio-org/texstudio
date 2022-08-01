# hfutthesis class
# Matthew Bertucci 2022/08/01 for v1.0.4

#include:iftex
#include:kvdefinekeys
#include:kvsetkeys
#include:kvoptions
#include:class-ctexbook
#include:xeCJK
#include:etoolbox
#include:amsmath
#include:fontspec
#include:geometry
#include:graphicx
#include:fancyhdr
#include:color
#include:titletoc
#include:caption
#include:footmisc
#include:url
#include:calc
#include:ulem
#include:multirow
#include:enumitem
#include:bicaption
#include:natbib
#include:filehook
#include:unicode-math

#keyvals:\documentclass/hfutthesis#c
degree=#bachelor,master,doctor
degree-type=#academic,professional
language=#chinese,english
fontset=#auto,windows,mac,ubuntu,fandol,none
output=#print,electronic
section-style=#chinese,arabic
cite-style=#super,inline,authoryear
#endkeyvals

#ifOption:font=newtx
#include:newtxtext
#endif

#ifOption:math-font=newtx
#include:newtxmath
#include:bm
#endif

#ifOption:math-font=cm
#include:amssymb
#include:bm
#endif

#ifOption:math-font=none
#include:amssymb
#include:bm
#endif

\hfutsetup{options%keyvals}

#keyvals:\hfutsetup#c
font=#auto,times,termes,stix,xits,libertinus,newcm,lm,newtx,none
cjk-font=#auto,windows,mac,noto,fandol,none
math-font=#auto,stix,xits,libertinus,newcm,cm,lm,newtx,none
math-style=#GB,ISO,TeX
uppercase-greek=#italic,upright
less-than-or-equal=#slanted,horizontal
integral=#upright,slanted
integral-limits#true,false
partial=#upright,italic
math-ellipsis=#centered,lower,AMS
real-part=#roman,fraktur
cite-style=#super,inline,authoryear
badge-color=#red,black
title={%<论文中文题目%>}
title*={%<thesis English title%>}
ugtype=#设计,论文
author={%<中文名%>}
author*={%<name%>}
stuID={%<学号%>}
clc={%<分类号%>}
speciality={%<学科专业%>}
hfuteryear={%<入学年份%>}
research={%<研究方向%>}
supervisor={%<中文名%>}
department={%<学院名称%>}
advisor={%<中文名%>}
advisor*={%<name%>}
applydegree={%<申请学位%>}
school={%<默认培养单位%>}
phdchairman={%<中文名%>}
phdmember={%<中文名%>}
date={%<yyyy-mm%>}
defensedate={%<答辩时间%>}
professional-type={%<%>}
professional-type*={%<%>}
secret-level=#绝密,机密,秘密,内部交流
secret-year={%<%保密年限>}
signchairman={%<专家工作单位，职称，姓名%>}
signmember={%<text%>}
signsupervisor={%<text%>}
keywords={%<关键词 1; 关键词 2; ...%>}
keywords*={%<English keywords%>}
#endkeyvals

\begin{abstract*}
\end{abstract*}
\begin{acknowledgements}
\end{acknowledgements}
\begin{notation}
\end{notation}
\begin{notationlist}{width}
\end{notationlist}
\begin{publications}
\end{publications}

\begin{theorem}
\begin{theorem}[heading%text]
\end{theorem}
\begin{assertion}
\begin{assertion}[heading%text]
\end{assertion}
\begin{axiom}
\begin{axiom}[heading%text]
\end{axiom}
\begin{corollary}
\begin{corollary}[heading%text]
\end{corollary}
\begin{lemma}
\begin{lemma}[heading%text]
\end{lemma}
\begin{proposition}
\begin{proposition}[heading%text]
\end{proposition}
\begin{assumption}
\begin{assumption}[heading%text]
\end{assumption}
\begin{definition}
\begin{definition}[heading%text]
\end{definition}
\begin{example}
\begin{example}[heading%text]
\end{example}
\begin{remark}
\begin{remark}[heading%text]
\end{remark}
\begin{proof}[heading%text]

\blacksquare#m
\bm{text%plain}#m
\checkmark
\copyrightpage
\hfutthesisversion#*
\inlinecite{bibid}#c
\lwtm#*
\notationlabel{text}#*
\note{notes%text}
\signaturepage
\square#m
\titleBox{text}#*
\titleLRExtraWd#*
\titleMultiLineMaxWd#*
\titleSepWd#*
\titleSingleLineMaxWd#*
\titleUnderline#*
\underlineFixlen[width]{text}#*
\underlineFixlen{text}#*

# deprecated
\begin{acknowledgments}#S
\end{acknowledgments}#S
\begin{enabstract}#S
\end{enabstract}#S
\cosupervisor{arg1}#S
\endate{arg1}#S
\enkeywords{arg1}#S
\keywords{arg1}#S
\makestatement#S