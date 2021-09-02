# thatlittleboy/2018-11-25 for enumitem v3.5.2
# muzimuzhi/15 Sep 2020 for enumitem v3.9

#ifOption:inline
\begin{enumerate*}
\begin{enumerate*}[keyvals]
\end{enumerate*}
\begin{itemize*}
\begin{itemize*}[keyvals]
\end{itemize*}
\begin{description*}
\begin{description*}[keyvals]
\end{description*}
#endif

#ifOption:shortlabels
#keyvals:\setlist
A
a
I
i
1
#endkeyvals
#endif

\begin{enumerate}[keyvals]
\begin{itemize}[keyvals]
\begin{description}[keyvals]

\newlist{name%envname}{type}{max-depth}#N
\renewlist{name%envname}{type}{max-depth}#N
\setlist{%<options%>}
\setlist*{%<options%>}
\setlist[%<names%>, %<levels%>]{%<options%>}
\setlist*[%<names%>, %<levels%>]{%<options%>}
\restartlist{list name}

\EnumitemId#*
\SetLabelAlign{value}{commands}#*
\SetEnumerateShortLabel{key%plain}{replacement}#*
\setlistdepth{integer}
\AddEnumerateCounter{LaTeX-cmd}{internal-cmd}{widest label}#*
\AddEnumerateCounter*{LaTeX-cmd}{internal-cmd}{integer}#*
\SetEnumitemKey{key%plain}{replacement}#*
\SetEnumitemValue{key%plain}{string-value}{replacement}#*
\SetEnumitemSize{name}{selector}#*
\DrawEnumitemLabel#*

#keyvals:\setlist
topsep=
partopsep=
parsep=
itemsep=
leftmargin=
rightmargin=
listparindent=
labelwidth=
labelsep=
itemindent=
label=
label*=
ref=
font=
format=
align=#left,right,parleft
labelindent=
left=%<labelindent%>
left=%<labelindent%> .. %<leftmargin%>
widest
widest=
widest*=
labelsep*=
labelindent*=
start=
resume=
resume*=
series=
beginpenalty=
midpenalty=
endpenalty=
before=
before*=
after=
after*=
first=
first*=
style=#standard,unboxed,nextline,sameline,multiline
noitemsep
nosep
wide
wide=
itemjoin=
itemjoin*=
afterlabel=
mode=#unboxed,boxed
#endkeyvals
