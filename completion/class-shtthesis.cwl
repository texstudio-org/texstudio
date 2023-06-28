# shtthesis class
# Matthew Bertucci 2022/08/12 for v0.3.3

#include:iftex
#include:kvdefinekeys
#include:kvsetkeys
#include:kvoptions
#include:datetime
#include:class-ctexbook
#include:xeCJK
#include:xcolor
# loads table option of xcolor
#include:geometry
#include:calc
#include:verbatim
#include:etoolbox
#include:ifthen
#include:graphicx
#include:indentfirst
#include:ulem
#include:fancyhdr
#include:lastpage
#include:tocvsec2
#include:letltxmacro
#include:fontspec
#include:caption
#include:enumitem
# loads shortlabels and inline options of enumitem
#include:mathtools
#include:amsthm
#include:unicode-math
#include:biblatex
# loads natbib=true option of biblatex
#include:hyperref

#keyvals:\documentclass/shtthesis#c
bachelor
master
doctor
anonymous#true,false
print#true,false
comfort#true,false
#endkeyvals

\shtsetup{options%keyvals}

#keyvals:\shtsetup
degree-name={%<您要申请什么学位%>}
degree-name*={%<English degree name%>}
language=#chinese,english
secret-level={%<秘密%>}
secret-year=%<year%>
title={%<论文中文题目%>}
title*={%<English thesis title%>}
keywords={%<关键词 1, 关键词 2%>}
keywords*={%<keyword1,keyword2,...%>}
author={%<中文姓名%>}
author*={%<name in Pinyin%>}
author-id={%<id%>}
entrance-year=%<year%>
supervisor={%<导师姓名, 教授%>}
supervisor*={%<Professor Supervisor Name%>}
supervisor-institution={%<机构%>}
supervisor-institution*={%<institution%>}
institution={%<机构%>}
institution*={%<institution%>}
discipline={%<学科名称%>}
discipline*={%<English discipline name%>}
discipline-level-1={%<流动站（一级学科）名称%>}
discipline-level-1*=
discipline-level-2={%<专业（二级学科）名称%>}
discipline-level-2*=
date={%<中文日期%>}
date*={%<English date%>}
clc={%<分类号%>}
udc={%<udc%>}
id={%<id%>}
anonymous-str=
bib-resource={%<bib file%>}
#endkeyvals

\begin{abstract}[flattitle]%|
\begin{abstract*}
\begin{abstract*}[flattitle]%|
\end{abstract*}
\begin{nomenclatures}
\begin{nomenclatures}[标题%text]
\end{nomenclatures}
\begin{theorem}
\begin{theorem}[heading%text]
\end{theorem}
\begin{lemma}
\begin{lemma}[heading%text]
\end{lemma}
\begin{corollary}
\begin{corollary}[heading%text]
\end{corollary}
\begin{proposition}
\begin{proposition}[heading%text]
\end{proposition}
\begin{conjecture}
\begin{conjecture}[heading%text]
\end{conjecture}
\begin{definition}
\begin{definition}[heading%text]
\end{definition}
\begin{axiom}
\begin{axiom}[heading%text]
\end{axiom}
\begin{example}
\begin{example}[heading%text]
\end{example}
\begin{problem}
\begin{problem}[heading%text]
\end{problem}
\begin{exercise}
\begin{exercise}[heading%text]
\end{exercise}
\begin{remark}
\begin{remark}[heading%text]
\end{remark}
\begin{acknowledgement}
\end{acknowledgement}
\begin{resume}
\end{resume}
\begin{publications}
\end{publications}
\begin{publications*}
\end{publications*}
\begin{patents}
\end{patents}
\begin{patents*}
\end{patents*}
\begin{projects}
\end{projects}

\artxaux{arg}#S
\artxmaincnt#S
\bm{text%plain}#m
\checkmark
\currentfontset#S
\header[单位表头%text]{符号表头%text}{描述表头%text}
\header{符号表头%text}{描述表头%text}
\inlinecite{bibid}#C
\intobmk*[level]{extra commands}{title}#*
\intobmk*{extra commands}{title}#*
\intobmk[level]{section-type}{*}{title}#*
\intobmk{section-type}{*}{title}#*
\intobmknostar[level]{section-type}{*}{title}#S
\intobmknostar{section-type}{*}{title}#S
\intobmkstar[level]{extra commands}{title}#S
\intobmkstar{extra commands}{title}#S
\intotoc*[section-type]{extra commands}{title}#*
\intotoc*{extra commands}{title}#*
\intotoc{section-type}{*}{title}#*
\intotocnostar{section-type}{*}{title}#S
\intotocstar[section-type]{extra commands}{title}#S
\intotocstar{extra commands}{title}#S
\makebiblio
\makedeclarations#*
\makeindices
\OriginCleardoublepage#S
\ShtThesis#*
\shtthesis#*
\square#*
\TmpFrontmatter#S
\TmpMainmatter#S
\version#S
\versiondate#S

# from table option of xcolor
#include:colortbl

# from shortlabels option of enumitem
#keyvals:\begin{enumerate}#c,\begin{itemize}#c,\begin{description}#c,\begin{enumerate*}#c,\begin{itemize*}#c,\begin{description*}#c
A
a
I
i
1
#endkeyvals

# from inline option of enumitem
\begin{enumerate*}
\begin{enumerate*}[options%keyvals]
\end{enumerate*}
\begin{itemize*}
\begin{itemize*}[options%keyvals]
\end{itemize*}
\begin{description*}
\begin{description*}[options%keyvals]
\end{description*}

# from natbib=true option of biblatex
# from blx-natbib.def
\citet[prenote][postnote]{bibid}#C
\citet[postnote]{bibid}#C
\citet{bibid}#C
\citet*[prenote][postnote]{bibid}#C
\citet*[postnote]{bibid}#C
\citet*{bibid}#C
\citep[prenote][postnote]{bibid}#C
\citep[postnote]{bibid}#C
\citep{bibid}#C
\citep*[prenote][postnote]{bibid}#C
\citep*[postnote]{bibid}#C
\citep*{bibid}#C
\citealt[prenote][postnote]{bibid}#C
\citealt[postnote]{bibid}#C
\citealt{bibid}#C
\citealt*[prenote][postnote]{bibid}#C
\citealt*[postnote]{bibid}#C
\citealt*{bibid}#C
\citealp[prenote][postnote]{bibid}#C
\citealp[postnote]{bibid}#C
\citealp{bibid}#C
\citealp*[prenote][postnote]{bibid}#C
\citealp*[postnote]{bibid}#C
\citealp*{bibid}#C
\citeauthor[prenote][postnote]{bibid}#C
\citeauthor[postnote]{bibid}#C
\citeauthor{bibid}#C
\citeauthor*[prenote][postnote]{bibid}#C
\citeauthor*[postnote]{bibid}#C
\citeauthor*{bibid}#C
\citeyearpar[prenote][postnote]{bibid}#C
\citeyearpar[postnote]{bibid}#C
\citeyearpar{bibid}#C
\Citet[prenote][postnote]{bibid}#C
\Citet[postnote]{bibid}#C
\Citet{bibid}#C
\Citet*[prenote][postnote]{bibid}#C
\Citet*[postnote]{bibid}#C
\Citet*{bibid}#C
\Citep[prenote][postnote]{bibid}#C
\Citep[postnote]{bibid}#C
\Citep{bibid}#C
\Citep*[prenote][postnote]{bibid}#C
\Citep*[postnote]{bibid}#C
\Citep*{bibid}#C
\Citealt[prenote][postnote]{bibid}#C
\Citealt[postnote]{bibid}#C
\Citealt{bibid}#C
\Citealt*[prenote][postnote]{bibid}#C
\Citealt*[postnote]{bibid}#C
\Citealt*{bibid}#C
\Citealp[prenote][postnote]{bibid}#C
\Citealp[postnote]{bibid}#C
\Citealp{bibid}#C
\Citealp*[prenote][postnote]{bibid}#C
\Citealp*[postnote]{bibid}#C
\Citealp*{bibid}#C
\citefullauthor[prenote][postnote]{bibid}#C
\citefullauthor[postnote]{bibid}#C
\citefullauthor{bibid}#C
\Citefullauthor[prenote][postnote]{bibid}#C
\Citefullauthor[postnote]{bibid}#C
\Citefullauthor{bibid}#C
\citetext{text}
\defcitealias{bibid}{alias}
\citetalias{bibid}
\citepalias{bibid}