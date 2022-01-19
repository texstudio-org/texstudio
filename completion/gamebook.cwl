# gamebook package
# Matthew Bertucci 1/18/2021 for v1.0

#include:ifthen
#include:fancyhdr
#include:extramarks
#include:titlesec
#include:enumitem

#ifOption:draft
#include:draftwatermark
#include:scrtime
#include:prelim2e
#endif

#keyvals:\usepackage/gamebook#c
debug
draft
#endkeyvals

\gbsection{id%labeldef}#l
\gbturn{id%ref}#r
\gbturntext#*

\begin{gbturnoptions}
\begin{gbturnoptions}[options%keyvals]
\end{gbturnoptions}

#keyvals:\begin{gbturnoptions}
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

\gbitem{text}{id%ref}#r
\gbvillain{name}{skill%text}{skill level%text}{life%text}{life level%text}
\gbheader
\gbheadtext#*

\begin{gbtabbing}#*
\end{gbtabbing}#*
\gbdebugx{arg}#*
\gbdebug{arg}#*