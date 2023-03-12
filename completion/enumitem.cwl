# thatlittleboy/2018-11-25 for enumitem v3.5.2
# muzimuzhi/15 Sep 2020 for enumitem v3.9

#keyvals:\usepackage/enumitem#c
shortlabels
inline
sizes
ignoredisplayed
includedisplayed
series=override
loadonly
#endkeyvals

#ifOption:inline
\begin{enumerate*}
\begin{enumerate*}[options%keyvals]
\end{enumerate*}
\begin{itemize*}
\begin{itemize*}[options%keyvals]
\end{itemize*}
\begin{description*}
\begin{description*}[options%keyvals]
\end{description*}
#endif

#ifOption:shortlabels
#keyvals:\begin{enumerate}#c,\begin{itemize}#c,\begin{description}#c,\begin{enumerate*}#c,\begin{itemize*}#c,\begin{description*}#c
A
a
I
i
1
#endkeyvals
#endif

#ifOption:sizes
\setlist<%<size%>>[%<names%>, %<levels%>]{%<options%>}
#endif

\begin{enumerate}[options%keyvals]
\begin{itemize}[options%keyvals]
\begin{description}[options%keyvals]

\newlist{name%envname}{type%keyvals}{max-depth}#N
\renewlist{name%envname}{type%keyvals}{max-depth}
#keyvals:\newlist#c,\renewlist#c
enumerate
itemize
description
enumerate*
itemize*
description*
#endkeyvals
\setlist{%<options%>}
\setlist*{%<options%>}
\setlist[%<names%>, %<levels%>]{%<options%>}
\setlist*[%<names%>, %<levels%>]{%<options%>}
\restartlist{list name}

\EnumitemId#*
\SetLabelAlign{value}{commands}#*
\labelindent#*
\SetEnumerateShortLabel{key%plain}{replacement}#*
\setlistdepth{integer}
\AddEnumerateCounter{LaTeX-cmd}{internal-cmd}{widest label}#*
\AddEnumerateCounter*{LaTeX-cmd}{internal-cmd}{integer}#*
\SetEnumitemKey{key%specialDef}{replacement options%keyvals}#*s#%enumitemkey
\SetEnumitemValue{key%plain}{string-value}{replacement}#*
\SetEnumitemSize{name}{selector}#*
\DrawEnumitemLabel#*

#keyvals:\setlist,\setlist*,\SetEnumitemKey,\begin{enumerate}#c,\begin{itemize}#c,\begin{description}#c,\begin{enumerate*}#c,\begin{itemize*}#c,\begin{description*}#c
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
%enumitemkey
#endkeyvals
