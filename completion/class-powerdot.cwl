# powerdot class
# Matthew Bertucci 2022/06/03 for v1.7

#include:xkeyval
#include:geometry
#include:ifxetex
#include:hyperref
#include:graphicx
#include:pstricks
#include:pst-ovl
#include:xcolor
#include:enumitem
#include:verbatim
#include:powerdot-default

#keyvals:\documentclass/powerdot#c
mode=#present,print,handout
nohandoutpagebreaks
nohandoutframes
paper=#screen,a4paper,letterpaper,smartboard,169
orient=#landscape,portrait
display=#slides,slidesnotes,notes
size=#8pt,9pt,10pt,11pt,12pt,14pt,17pt,20pt
style=%<style name%>
fleqn
leqno
nopsheader
hlentries#true,false
hlsections#true,false
pauseslide
clock
#endkeyvals

#ifOption:clock
#include:pdfbase
#endif
#ifOption:clock=true
#include:pdfbase
#endif

#ifOption:style=aggie
#include:powerdot-aggie
#endif
#ifOption:style=BerlinFU
#include:powerdot-BerlinFU
#endif
#ifOption:style=bframe
#include:powerdot-bframe
#endif
#ifOption:style=ciment
#include:powerdot-ciment
#endif
#ifOption:style=elcolors
#include:powerdot-elcolors
#endif
#ifOption:style=fyma
#include:powerdot-fyma
#endif
#ifOption:style=horatio
#include:powerdot-horatio
#endif
#ifOption:style=husky
#include:powerdot-husky
#endif
#ifOption:style=ikeda
#include:powerdot-ikeda
#endif
#ifOption:style=jefka
#include:powerdot-jefka
#endif
#ifOption:style=klope
#include:powerdot-klope
#endif
#ifOption:style=paintings
#include:powerdot-paintings
#endif
#ifOption:style=pazik
#include:powerdot-pazik
#endif
#ifOption:style=sailor
#include:powerdot-sailor
#endif
#ifOption:style=simple
#include:powerdot-simple
#endif
#ifOption:style=tuliplab
#include:powerdot-tuliplab
#endif
#ifOption:style=tycja
#include:powerdot-tycja
#endif
#ifOption:style=upen
#include:powerdot-upen
#endif

\pdsetup{options%keyvals}

# global-only options
#keyvals:\pdsetup
theslide=%<code%>
thenote=%<code%>
counters={%<counter1,counter2,...%>}
list={%<enumitem options%>}
enumerate={%<enumitem options%>}
itemize={%<enumitem options%>}
clockformat=%<format%>
clockrefresh=%<milliseconds%>
#endkeyvals

# local or global options
#keyvals:\pdsetup,\maketitle,\begin{titleslide},\begin{basic},\begin{wideslide},\begin{slide},\begin{sectionslide},\begin{sectionwideslide},\section
palette=%<palette name%>
lf=%<text%>
cf=%<text%>
rf=%<text%>
trans=%<transition%>
method=#normal,direct,file
logohook=#tl,t,tr,r,Br,br,b,bl,Bl,l,B,c
logopos={%<width,height%>}
logocmd={%<code%>}
randomdots#true,false
dmindots=%<integer%>
dmaxdots=%<integer%>
dminsize=##L
dmaxsize=##L
dminwidth=##L
dmaxwidth=##L
dminheight=##L
dmaxheight=##L
dbright=%<integer%>
dprop={%<pstricks options%>}
#endkeyvals

\maketitle[options%keyvals]

# slide-only options
#keyvals:\begin{titleslide},\begin{basic},\begin{wideslide},\begin{slide},\begin{sectionslide},\begin{sectionwideslide},\section
toc=%<TOC entry%>
bm=%<bookmark entry%>
#endkeyvals

\pause
\pause[number]

\begin{enumerate}[type=%<0|1%>,][enumitem options]
\begin{itemize}[type=%<0|1%>][enumitem options]

\item<overlays>
\item[label]<overlays>

\onslide{overlays}{text}
\onslide+{overlays}{text}
\onslide*{overlays}{text}

\section{title}#L2
\section[options%keyvals]{title}#L2

#keyvals:\section
tocsection=#true,false,hidden
slide#true,false
template=%<template name%>
#endkeyvals

\tableofcontents[options%keyvals]

#keyvals:\tableofcontents
type=#0,1
content=#all,sections,currentsection,future,futuresections
#endkeyvals

\begin{note}{title}
\end{note}
\begin{emptyslide}{title}
\end{emptyslide}
\begin{pauseslide}{title}#*
\end{pauseslide}#*

\slidewidth#L
\slideheight#L
\thenote#*
\theslide#*

\twocolumn{left%text}{right%text}
\twocolumn[options%keyvals]{left%text}{right%text}

#keyvals:\twocolumn
lineheight=##L
lineprop={%<pstricks options%>}
lfrheight=##L
lfrprop={%<pstricks options%>}
rfrheight=##L
rfrprop={%<pstricks options%>}
lcolwidth=##L
rcolwidth=##L
frsep=##L
colsep=##L
topsep=##L
bottomsep=##L
indent=##L
#endkeyvals

\pddefinepalettes{%<name1%>}{%<cmds1%>}%<{name2}{cmds2}...%>#*
\pddefinetemplate{envname}{options}{commands}#*N
\pddefinetemplate[basis]{envname}{options}{commands}#*N
\pdifsetup{desired}{true}{false}#*
\pddefinelyxtemplate%<\cmd%>{%<template%>}#*
\pddefinelyxtemplate{cmd}#Sd
\lyxend#S
\lyxnote#S
\lyxslide#S
\lyxwideslide#S
\lyxemptyslide#S

\pdbookmark{arg1}{arg2}{arg3}{arg4}#*
\pdcontentsline{arg1}{arg2}{arg3}#*