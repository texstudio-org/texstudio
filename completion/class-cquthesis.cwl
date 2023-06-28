# cquthesis class
#Written by Zhennan Li 2016/06/10
# updated Matthew Bertucci 2022/06/04 for v1.40

#include:kvoptions
#include:class-ctexbook
#include:xeCJK
#include:etoolbox
#include:environ
#include:calc
#include:ifxetex
#include:fontspec
#include:amsmath
#include:amssymb
#include:amsfonts
#include:newtxtext
#include:pifont
#include:xeCJKfntef
#include:newfloat
#include:caption
#include:subcaption
#include:bicaption
#include:array
#include:tabularx
#include:booktabs
#include:longtable
#include:multirow
#include:diagbox
#include:tabu
#include:courier
#include:graphicx
#include:pdfpages
#include:enumitem
# loads shortlabels and inline options of enumitem
#include:ntheorem
# loads thmmarks option of ntheorem
#include:changepage
#include:afterpage
#include:footmisc
#include:varwidth
#include:xcolor
#include:metalogo
#include:xspace
#include:natbib
#include:hyperref
#include:tocloft
#include:geometry
#include:totcount
#include:fancyhdr
#include:mhchem
#include:siunitx
#include:upgreek
#include:listings

#keyvals:\documentclass/cquthesis#c
type=#bachelor,master,doctor
liberalformat
academic
proffesionalmaster#true,false
openany
openright
blankleft
abstractopenright
blindtrail
printmode=#oneside,twoside,auto
secret
seriftoc
continuoustoc
bilinguallist=#off,combined,apart
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

\begin{cabstract}
\end{cabstract}
\begin{Cplus}#V
\end{Cplus}
## the ++ in envname with #V does not work
## \begin{C++}#V
\begin{C++}
\end{C++}
\begin{eabstract}
\end{eabstract}
\begin{denotation}
\begin{denotation}[indent%l]
\begin{denotation}[indent%l][labelwidth%l]
\end{denotation}
\begin{Python}#V
\end{Python}
\begin{secretizeEnv}
\end{secretizeEnv}

\begin{proof}#n
\end{proof}#n
\begin{assumption}#n
\begin{assumption}[heading%text]#n
\end{assumption}#n
\begin{definition}#n
\begin{definition}[heading%text]#n
\end{definition}#n
\begin{proposition}#n
\begin{proposition}[heading%text]#n
\end{proposition}#n
\begin{lemma}#n
\begin{lemma}[heading%text]#n
\end{lemma}#n
\begin{theorem}#n
\begin{theorem}[heading%text]#n
\end{theorem}#n
\begin{axiom}#n
\begin{axiom}[heading%text]#n
\end{axiom}#n
\begin{corollary}#n
\begin{corollary}[heading%text]#n
\end{corollary}#n
\begin{exercise}#n
\begin{exercise}[heading%text]#n
\end{exercise}#n
\begin{example}#n
\begin{example}[heading%text]#n
\end{example}#n
\begin{remark}#n
\begin{remark}[heading%text]#n
\end{remark}#n
\begin{problem}#n
\begin{problem}[heading%text]#n
\end{problem}#n
\begin{conjecture}#n
\begin{conjecture}[heading%text]#n
\end{conjecture}#n

\bigcell{content}#t
\cdate#*
\cec{molecule1,molecule2,...}
\cftafterequENtitle#*
\cftafterequtitle#*
\cftequationsENnumwidth#*
\cftequationsnumwidth#*
\cftequENtitlefont#*
\cftequtitlefont#*
\chapterstar{title}#*L1
\ckeywords{关键词 1,关键词 2,...%text}#n
\colsep
\colsep[length]
\cquauthpage#n
\cquauthpage[scannedFile]#n
\cqueqshortname#*
\cquthesis#n
\edate#*
\ekeywords{keyword1,keyword2,...%text}#n
\eqlist{中文 name}#n
\eqlist{中文 name}[English name]#n
\headcell{content}#t
\inlinecite{bibid}#c
\listeq{中文 name}#n
\listeq{中文 name}[English name]#n
\listofequations#n
\listofequationsEN#n
\listofequationsname#*
\listofequationsnameEN#*
\listoffiguresEN#n
\listoffiguresnameEN#*
\listoftablesEN#n
\listoftablesnameEN#*
\makeabstract#n
\makecover#n
\MONTH#*
\onlinecite{bibid}#c
\parenthesesthis{text}#*
\resetrownum#n
\resetxuhao#n
\rownum#n
\rownum[1]#n
\rownumseparator#n
\rownumtype[1-6]#n
\secretize{text}
\setxuhao#S
\shortfigurename#*
\shortfigurenameEN#*
\shorttablename#*
\shorttablenameEN#*
\thecquXuHao#*
\thecquXuHaoType#*
\version#n
\xuhao#n
\xuhao[1]%|#n
\xuhaoseparator#n
\xuhaotype[1-6]#n

\cqusetup{options%keyvals}#n

#keyvals:\cqusetup
ctitle={%<论文中文题目%>}
etitle={%<English title%>}
cauthor={%<中文名字%>}
eauthor={%<English name%>}
csupervisor={%<中文名字%>}
esupervisor={%<English name%>}
cpsupervisor={%<中文名字%>}
epsupervisor={%<English name%>}
cassistsupervisor={%<中文名字%>}
cextrasupervisor={%<中文名字%>}
eassistsupervisor={%<English name%>}
cmajor={%<中文专业%>}
emajor={%<English major%>}
mycdate={%<中文日期%>}
myedate={%<English date%>}
ckeywords={%<关键词 1,关键词 2,...%>}
ekeywords={%<keyword1,keyword2,...%>}
cclass={%<中文学科%>}
edgree={%<English degree%>}
cdepartment={%<中文系%>}
edepartment={%<English department%>}
studentid={%<id%>}
#endkeyvals

\ctitle{论文中文题目%text}#*
\etitle{English title%text}#*
\cauthor{中文名字}#*
\eauthor{English name}#*
\csupervisor{中文名字}#*
\esupervisor{English name}#*
\cpsupervisor{中文名字}#*
\epsupervisor{English name}#*
\cassistsupervisor{中文名字}#*
\cextrasupervisor{中文名字}#*
\eassistsupervisor{English name}#*
\cmajor{中文专业%text}#*
\emajor{English major%text}#*
\mycdate{中文日期}#*
\myedate{English date}#*
\ckeywords{关键词 1,关键词 2,...%text}#*
\ekeywords{keyword1,keyword2,...%text}#*
\cclass{中文学科%text}#*
\edgree{English degree%text}#*
\cdepartment{中文系%text}#*
\edepartment{English department%text}#*
\studentid{id}#*

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

# from thmmarks option of ntheorem
\theoremsymbol{symbol}
