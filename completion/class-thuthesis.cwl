# thuthesis class
# Matthew Bertucci 2023/05/16 for v7.4.0

#include:iftex
#include:kvdefinekeys
#include:kvsetkeys
#include:kvoptions
#include:class-ctexbook
#include:etoolbox
#include:filehook
#include:geometry
#include:fancyhdr
#include:titletoc
#include:notoccite
#include:amsmath
#include:graphicx
#include:subcaption
#include:pdfpages
#include:enumitem
# loads shortlabels option of enumitem
#include:environ
#include:footmisc
#include:xeCJKfntef
#include:array
#include:booktabs
#include:url
#include:natbib
#include:unicode-math

#keyvals:\documentclass/thuthesis#c
degree=#bachelor,master,doctor,postdoc
degree-type=#academic,professional
fontset=#auto,windows,mac,ubuntu,fandol,none
openright#true,false
openany
raggedbottom#true,false
# options passed to ctexbook class
GBK
UTF8
zhmap=#true,false,zhmCJK
zihao=#-4,5,false
heading#true,false
sub3section
sub4section
scheme=#chinese,plain
linespread=%<number%>
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
onecolumn
twocolumn
leqno
fleqn
openbib
#endkeyvals

#ifOption:degree=bachelor
#include:bibunits
#endif

#ifOption:math-font=newtx
#include:newtxmath
#include:bm
#endif

#ifOption:font=newtx
#include:newtxtext
#endif

\thusetup{options%keyvals}

#keyvals:\thusetup
thesis-type=#thesis,proposal
title={%<论文中文题目%>}
title*={%<English thesis title%>}
degree-category={%<您要申请什么学位%>}
degree-category*={%<English degree name%>}
department={%<系名全称%>}
discipline={%<学科名称%>}
discipline*={%<English discipline name%>}
professional-field={%<专业领域%>}
professional-field*={%<English field name%>}
author={%<中文姓名%>}
author*={%<name in Pinyin%>}
student-id={%<id number%>}
supervisor={%<导师姓名, 教授%>}
supervisor*={%<Professor Supervisor Name%>}
associate-supervisor={%<副导师姓名, 副教授%>}
associate-supervisor*={%<Professor Assoc-Supervisor Name%>}
co-supervisor={%<联合导师姓名, 教授%>}
co-supervisor*={%<Professor Co-Supervisor Name%>}
date={%<YYYY-MM-DD%>}
secret-year=%<number%>
secret-level={%<秘密%>}
clc={%<分类号%>}
udc={%<udc%>}
id={%<id%>}
discipline-level-1={%<流动站（一级学科）名称%>}
discipline-level-2={%<专业（二级学科）名称%>}
start-date={%<YYYY-MM-DD%>}
end-date={%<YYYY-MM-DD%>}
keywords={%<关键词 1, 关键词 2%>}
keywords*={%<keyword1,keyword2,...%>}
toc-chapter-style=#arial,times
figure-number-separator={%<separator%>}
table-number-separator={%<separator%>}
equation-number-separator={%<separator%>}
number-separator={%<separator%>}
math-style=#GB,ISO,TeX
uppercase-greek=#italic,upright
less-than-or-equal=#slanted,horizontal
integral=#upright,slanted
integral-limits#true,false
partial=#upright,italic
math-ellipsis=#centered,lower,AMS
real-part=#roman,fraktur
math-font=#auto,stix,xits,libertinus,newcm,lm,newtx,none
cite-style=#super,inline,author-year
toc-depth=%<integer%>
spine-font={%<font commands%>}
spine-title={%<书脊的标题%>}
spine-author={%<书脊的作者姓名%>}
include-spine#true,false
appendix-figure-in-lof#true,false
# not in main documentation
main-language=#chinese,english
language=#chinese,english
system=#auto,mac,unix,windows
font=#auto,times,termes,stix,xits,libertinus,newcm,lm,newtx,none
cjk-font=#auto,windows,mac,mac-world,noto,fandol,none
output=#print,electronic
statement-page-style=#auto,empty,plain
#endkeyvals

## 前言部分 ##
\begin{committee}
\begin{committee}[options%keyvals]
\end{committee}

#keyvals:\begin{committee}
name={%<学位论文公开评阅人和答辩委员会名单%>}
file=%<file path%>
#endkeyvals

\copyrightpage
\copyrightpage[file=%<PDF file%>]
\begin{abstract}
\end{abstract}
\begin{abstract*}
\end{abstract*}
\listoffigures*
\listoftables*
\listofequations
\listofequations*
\listofalgorithms*
\equcaption{text}
\begin{denotation}
\begin{denotation}[width]
\end{denotation}

## 正文部分 ##
\begin{axiom}
\begin{axiom}[heading%text] 
\end{axiom}
\begin{theorem}
\begin{theorem}[heading%text]
\end{theorem}
\begin{definition}
\begin{definition}[heading%text]
\end{definition}
\begin{proposition}
\begin{proposition}[heading%text]
\end{proposition}
\begin{lemma}
\begin{lemma}[heading%text]
\end{lemma}
\begin{conjecture}
\begin{conjecture}[heading%text]
\end{conjecture}
\begin{proof}
\begin{proof}[heading%text]
\end{proof}
\begin{corollary}
\begin{corollary}[heading%text]
\end{corollary}
\begin{example}
\begin{example}[heading%text]
\end{example}
\begin{exercise}
\begin{exercise}[heading%text]
\end{exercise}
\begin{assumption}
\begin{assumption}[heading%text]
\end{assumption}
\begin{remark}
\begin{remark}[heading%text]
\end{remark}
\begin{problem}
\begin{problem}[heading%text]
\end{problem}

\inlinecite{keylist}#c

## 其他部分 ##
#keyvals:\bibliographystyle#c
thuthesis-numeric
thuthesis-author-year
thuthesis-bachelor
#endkeyvals

\begin{acknowledgements}
\end{acknowledgements}

\statement
\statement[options%keyvals]

#keyvals:\statement
page-style=#auto,empty,plain
file=%<PDF file%>
#endkeyvals

\begin{survey}
\end{survey}
\begin{translation}
\end{translation}
\begin{translation-index}
\end{translation-index}
\begin{resume}
\end{resume}
\begin{achievements}
\end{achievements}
\record{file=%<PDF file%>}

## 书脊 ##
\spine

# miscellaneous
\begin{comments}
\begin{comments}[name={%<name%>}]
\end{comments}
\begin{resolution}
\end{resolution}

\blacksquare
\bm{text%plain}#m
\checkmark
\cls{class}
\cs{csname}
\env{envname}
\file{filename%file}
\pkg{package}
\square

\CJKmove#*
\CJKmovesymbol{symbol}#*
\CJKpunctsymbol{symbol}#*
\CJKsymbol{symbol}#*
\listequationname#*
\listoffiguresandtables#*
\thuthesis#*
\version#*

# compatibility
\begin{acknowledgement}#S
\end{acknowledgement}#S
\begin{publications}#S
\end{publications}#S
\onlinecite{keylist}#Sc

# from shortlabels option of enumitem
#keyvals:\begin{enumerate}#c,\begin{itemize}#c,\begin{description}#c,\begin{enumerate*}#c,\begin{itemize*}#c,\begin{description*}#c
A
a
I
i
1
#endkeyvals
