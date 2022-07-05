# buctthesis class
# Matthew Bertucci 2022/07/04 for v1.2

#include:ifxetex
#include:kvoptions
#include:class-ctexbook
#include:xeCJK
#include:geometry
#include:fancyhdr
#include:titletoc
#include:amsmath
#include:amsthm
#include:amssymb
#include:unicode-math
#include:pifont
#include:enumitem
#include:siunitx
#include:mhchem
#include:float
#include:longtable
#include:threeparttable
#include:tabularx
#include:multirow
#include:booktabs
#include:graphicx
#include:subcaption
#include:caption
#include:bicaption
#include:tikz
#include:listings
#include:gbt7714
#include:xcolor
#include:pdfpages
#include:footmisc
#include:xpatch
#include:hyperref

#keyvals:\documentclass/buctthesis#c
type=#bachelor,master,doctor
submit#true,false
openright#true,false
openany#true,false
debugger#true,false
# options passed to ctexbook
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
onecolumn
twocolumn
leqno
fleqn
openbib
#endkeyvals

#ifOption:debugger
#include:fgruler
#include:lineno
#endif
#ifOption:debugger=true
#include:fgruler
#include:lineno
#endif

\buctsetup{options%keyvals}

#keyvals:\buctsetup
ctitle={%<中文标题%>}
etitle={%<English title%>}
cauthor={%<中文名%>}
class={%<class%>}
studentid={%<id number%>}
school={%<学院%>}
major={%<专业%>}
supervisor={%<导师姓名, 教授%>}
msupervisor={%<导师姓名, 教授%>}
ckeywords={%<关键词 1, 关键词 2%>}
ekeywords={%<keyword1,keyword2,...%>}
#endkeyvals

\ctitle{中文标题%text}
\etitle{English title%text}
\cauthor{中文名}
\class{class}
\studentid{id number}
\school{学院}
\major{专业%text}
\supervisor{导师姓名, 教授}
\msupervisor{导师姓名, 教授}
\ckeywords{关键词 1, 关键词 2%text}
\ekeywords{keyword1,keyword2,...%text}

\makedeclare
\makedeclare[imagefile]#g

\begin{cabstract}
\end{cabstract}
\begin{eabstract}
\end{eabstract}

\begin{taskbook}
\end{taskbook}
\taskinfo
\taskinfo*
\taskitem
\begin{bibenumerate}
\end{bibenumerate}

\tableofcontentsEN
\listofdesignfigures

\begin{denotation}
\begin{denotation}[width]
\end{denotation}
\begin{foreword}
\end{foreword}

\echapter{title}#L1
\esection{title}#L2
\esubsection{title}#L3
\esubsubsection{title}#L4
\bichapter{title}{English title%title}#L1
\bichapter[short title]{title}{English title%title}#L1
\bisection{title}{English title%title}#L2
\bisection[short title]{title}{English title%title}#L2
\bisubsection{title}{English title%title}#L3
\bisubsection[short title]{title}{English title%title}#L3
\bisubsubsection{title}{English title%title}#L4
\bisubsubsection[short title]{title}{English title%title}#L4

\begin{dfigure}
\begin{dfigure}[placement]
\end{dfigure}
\dcaption{text}

\begin{conclusion}
\end{conclusion}
\begin{translation}
\end{translation}
\begin{acknowledgement}
\end{acknowledgement}
\begin{achievements}
\end{achievements}
\begin{resume}
\end{resume}

\begin{axiom}
\begin{axiom}[heading%text]
\end{axiom}
\begin{theorem}
\begin{theorem}[heading%text]
\end{theorem}
\begin{corollary}
\begin{corollary}[heading%text]
\end{corollary}
\begin{remark}
\begin{remark}[heading%text]
\end{remark}
\begin{assumption}
\begin{assumption}[heading%text]
\end{assumption}
\begin{definition}
\begin{definition}[heading%text]
\end{definition}
\begin{property}
\begin{property}[heading%text]
\end{property}
\begin{proposition}
\begin{proposition}[heading%text]
\end{proposition}
\begin{lemma}
\begin{lemma}[heading%text]
\end{lemma}
\begin{proof}
\begin{proof}[heading%text]
\end{proof}

# not documented
\bfhei#*
\bfsong#*
\econtentsname#*
\equationname#*
\thetaskitemcnt#*
\begin{oldlongtable}#S
\end{oldlongtable}#S