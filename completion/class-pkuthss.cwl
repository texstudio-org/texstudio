# pkuthss class
# Matthew Bertucci 2022/07/03 for v1.9.2

#include:amsmath
#include:class-ctexbook
#include:xeCJK
#include:ifpdf
#include:ifxetex
#include:keyval
#include:graphicx
#include:geometry
#include:fancyhdr
#include:ulem
#include:hyperref
#include:unicode-math
#include:latexsym
#include:tikz
#include:scrextend
#include:tocloft
#include:caption
#include:subcaption
#include:setspace
#include:enumitem

#keyvals:\documentclass/pkuthss#c
uppermark
nouppermark
pkufont
nopkufont
pkufoot
nopkufoot
pkuspace
nopkuspace
spacing
nospacing
spechap
nospechap
pdftoc
nopdftoc
pdfprop
nopdfprop
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

#ifOption:pdfprop
\setpdfproperties
#endif

\ctitle{中文标题%text}
\etitle{English title%text}
\cauthor{中文名}
\eauthor{English name}
\date{date}
\studentid{number}
\school{school%text}
\cmajor{中文专业%text}
\emajor{English major%text}
\direction{text}
\cmentor{中文导师}
\ementor{English mentor}
\ckeywords{中文关键词%text}
\ekeywords{English keywords%text}
\blindid{number}
\discipline{discipline%text}

\makeblind

\cuniversity#*
\euniversity#*
\cthesisname#*
\ethesisname#*
\thesiscover#*
\mentorlines#*
\cabstractname#*
\eabstractname#*

\pkuthssinfo{options%keyvals}

#keyvals:\pkuthssinfo
ctitle={%<中文标题%>}
etitle={%<English title%>}
cauthor={%<中文名%>}
eauthor={%<English name%>}
date={%<date%>}
studentid={%<number%>}
school={%<school%>}
cmajor={%<中文专业%>}
emajor={%<English major%>}
direction={%<text%>}
cmentor={%<中文导师%>}
ementor={%<English mentor%>}
ckeywords={%<中文关键词%>}
ekeywords={%<English keywords%>}
blindid={%<number%>}
discipline={%<discipline%>}
cuniversity={%<text%>}
euniversity={%<text%>}
cthesisname={%<text%>}
ethesisname={%<text%>}
thesiscover={%<text%>}
mentorlines={%<text%>}
cabstractname={%<text%>}
eabstractname={%<text%>}
#endkeyvals

\begin{cabstract}
\end{cabstract}
\begin{eabstract}
\end{eabstract}
\begin{beabstract}
\end{beabstract}

\specialchap{title}#L1
\thssnl

\prodop#*m
\sumop#*m
\titlepagename#*