# geradwp package
# Matthew Bertucci 2022/06/01 for v1.1

#include:ifthen
#include:amssymb
#include:amsmath
#include:amsthm
#include:amsfonts
#include:latexsym
#include:graphicx
#include:mathrsfs
#include:geometry
#include:fancyhdr
#include:booktabs
#include:multirow
#include:array
#include:caption
#include:xcolor
#include:enumitem

#keyvals:\documentclass/geradwp#c
gdweb
gdpaper
gdplain
gdsmallhead
gdfinal
gdpostpub
gdsupplement
gdrevised
gdminitabs
# options passed to article class
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

#ifOption:gdminitabs
#include:float
#endif

#keyvals:\theoremstyle#c
gerad
#endkeyvals

\begin{GDabstract}{title}#L5
\end{GDabstract}
\begin{GDacknowledgements}
\end{GDacknowledgements}
\begin{GDaffillist}
\begin{GDaffillist}[options%keyvals]
\end{GDaffillist}
\begin{GDauthlist}
\begin{GDauthlist}[options%keyvals]
\end{GDauthlist}
\begin{GDemaillist}
\begin{GDemaillist}[options%keyvals]
\end{GDemaillist}
\begin{GDpagetitre}#*
\end{GDpagetitre}#*
\begin{GDtitlepage}
\end{GDtitlepage}
\begin{proof}
\begin{proof}[heading%text]
\end{proof}

\GDabstracts
\GDaffilitem{label}{text}#l
\GDannee{year}#*
\GDarticlestart
\GDauteursCopyright{authors}#*
\GDauteursCourts{authors}#*
\GDauthitem{text}
\GDauthorsCopyright{authors}
\GDauthorsShort{authors}
\GDcoverpage
\GDcoverpagewhitespace{length}
\GDemailitem{text}
\GDmois{French month}{English month}#*
\GDmonth{French month}{English month}
\GDnumber{number}
\GDnumero{number}#*
\GDpageCouverture#*
\GDpostpubcitation{text}{URL}#U
\GDrefsep
\GDrevised{French month}{English month}{year}
\GDsupplementname{text}
\GDtitle{text}
\GDtitre{text}#*
\GDyear{year}

#keyvals:\begin{GDaffillist}#c,\begin{GDauthlist}#c,\begin{GDemaillist}#c
topsep=##L
partopsep=##L
parsep=##L
itemsep=##L
leftmargin=##L
rightmargin=##L
listparindent=##L
labelwidth=##L
labelsep=##L
itemindent=##L
label=%<commands%>
label*=%<commands%>
ref=%<commands%>
font=%<commands%>
format=%<commands%>
align=#left,right,parleft
labelindent=##L
left=%<labelindent%>
left=%<labelindent%> .. %<leftmargin%>
widest
widest=%<string%>
widest*=%<integer%>
labelsep*=##L
labelindent*=##L
start=%<integer%>
resume
resume=%<series name%>
resume*
resume*=%<series name%>
series=%<series name%>
beginpenalty=%<integer%>
midpenalty=%<integer%>
endpenalty=%<integer%>
before=%<code%>
before*=%<code%>
after=%<code%>
after*=%<code%>
first=%<code%>
first*=%<code%>
style=#standard,unboxed,nextline,sameline,multiline
noitemsep
nosep
wide
wide=%<parindent%>
itemjoin=%<string%>
itemjoin*=%<string%>
afterlabel=%<string%>
mode=#unboxed,boxed
#endkeyvals