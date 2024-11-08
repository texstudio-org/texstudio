# enumext package
# Matthew Bertucci 2024/11/04 for v1.0

#include:multicol
#include:scontents

\begin{enumext}
\begin{enumext}[keyvals]
\end{enumext}
\begin{enumext*}
\begin{enumext*}[keyvals]
\end{enumext*}

\item*
\item*[symbol]
\item*[symbol][offset]
\item(columns)
\item(columns)[label%text]
\item(columns)*
\item(columns)*[symbol]
\item(columns)*[symbol][offset]

\setenumext{keyvals}
\setenumext[type,levels]{keyvals}
\setenumextmeta{key name%specialDef}{keyvals}#s#%enumextmetakey
\setenumextmeta[type,levels]{key name%specialDef}{keyvals}#s#%enumextmetakey

\miniright

\anskey{content%text}
\anskey[keyvals]{content%text}

\begin{anskey*}
\begin{anskey*}[keyvals]
\end{anskey*}

\begin{keyans}
\begin{keyans}[keyvals]
\end{keyans}
\begin{keyans*}
\begin{keyans*}[keyvals]
\end{keyans*}

\begin{keyanspic}
\begin{keyanspic}[keyvals]
\end{keyanspic}

\anspic{graphics%text}
\anspic[content%text]{graphics%text}
\anspic*{graphics%text}
\anspic*[content%text]{graphics%text}

\getkeyans{%<store name%>}
\getkeyans{%<store name%>:%<position%>}
\foreachkeyans{store name}
\foreachkeyans[keyvals]{store name}

\printkeyans{store name}
\printkeyans[keyvals]{store name}
\printkeyans*{store name}
\printkeyans*[keyvals]{store name}

\theenumXi#*
\theenumXii#*
\theenumXiii#*
\theenumXiv#*

\itemwidth#L

#keyvals:\begin{enumext},\begin{enumext*},\setenumext,\setenumextmeta,\printkeyans,\printkeyans*
item-sym*=%<symbol%>
item-pos*=##L
%enumextmetakey
#endkeyvals

#keyvals:\begin{enumext},\begin{enumext*},\setenumext,\setenumextmeta,\begin{keyans},\begin{keyans*},\printkeyans,\printkeyans*
mode-box
label=%<code%>
labelsep=##L
labelwidth=##L
widest=%<integer|string%>
font=%<font commands%>
align=#left,right,center
wrap-label={%<code%>}
wrap-label*={%<code%>}
ref=%<code%>
show-length#true,false
topsep=##L
parsep=##L
partopsep=##L
itemsep=##L
noitemsep
nosep
base-fix
above=##L
above*=##L
below=##L
below*=##L
list-offset=##L
list-indent=##L
itemindent=##L
rightmargin=##L
listparindent=##L
before={%<code%>}
before*={%<code%>}
first={%<code%>}
after={%<code%>}
start=%<integer expr%>
start*=%<integer|string%>
columns=%<integer%>
columns-sep=##L
mini-env=##L
mini-sep=##L
#endkeyvals

#keyvals:\begin{enumext},\begin{enumext*}
series=%<series name%>
resume=%<series name%>
resume*
#endkeyvals

#keyvals:\begin{enumext},\begin{enumext*},\setenumext,\setenumextmeta,\printkeyans,\printkeyans*
save-ans=%<store name%>
save-key={%<key list%>}
save-sep={%<text symbol%>}
save-ref#true,false
mark-ref=%<symbol%>
wrap-ans={%<code%>}
wrap-opt={%<code%>}
show-ans#true,false
mark-ans=%<symbol%>
mark-pos=#left,right
show-pos#true,false
check-ans#true,false
no-store
#endkeyvals

#keyvals:\begin{enumext*},\begin{keyans*},\printkeyans*
mini-right=%<content%>
mini-right*=%<content%>
#endkeyvals

#keyvals:\anskey,\begin{anskey*}
break-col
item-join=%<columns%>
item-star
item-sym*=%<symbol%>
item-pos*=%<symbol%>
#endkeyvals

#keyvals:\begin{anskey*}
write-env=%<file.ext%>
overwrite#true,false
force-eol#true,false
#endkeyvals

#keyvals:\begin{keyanspic}
label-pos=#above,below
label-sep=##L
layout-sty={%<num upper,num lower%>}
layout-sep=##L
layout-top=##L
#endkeyvals

#keyvals:\foreachkeyans
sep=%<code%>
step=%<integer%>
start=%<integer%>
stop=%<integer%>
before={%<code%>}
after={%<code%>}
wrapper={%<code%>}
#endkeyvals