# xinttools package
# Matthew Bertucci 11/16/2021 for v1.4j

#include:xintkernel

\xintgodef#*
\xintgodef{cmd}#Sd
\xintgoodef#*
\xintgoodef{cmd}#Sd
\xintgfdef#*
\xintgfdef{cmd}#Sd

\xintRevWithBraces{list}
\xintrevwithbraces{list}#S
\xintRevWithBracesNoExpand{list}
\xintrevwithbracesnoexpand{list}#S

\xintZapFirstSpaces{content}
\xintzapfirstspaces{content}#S
\xintZapLastSpaces{content}
\xintzaplastspaces{content}#S
\xintZapSpaces{content}
\xintzapspaces{content}#S
\xintZapSpacesB{content}
\xintzapspacesb{content}#S

\xintCSVtoList{csv list}
\xintcsvtolist{csv list}#S
\xintCSVtoListNoExpand{csv list}
\xintcsvtolistnoexpand{csv list}#S
\xintCSVtoListNonStripped{csv list}#*
\xintcsvtolistnonstripped{csv list}#S
\xintCSVtoListNonStrippedNoExpand{csv list}#*
\xintcsvtolistnonstrippednoexpand{csv list}#S

\xintNthElt{integer}{list}
\xintnthelt{integer}{list}#S
\xintNthEltNoExpand{integer}{list}
\xintntheltnoexpand{integer}{list}#S
\xintNthOnePy{integer}{list}
\xintnthonepy{integer}{list}#S
\xintNthOnePyNoExpand{integer}{list}
\xintnthonepynoexpand{integer}{list}#S

\xintKeep{integer}{list}
\xintkeep{integer}{list}#S
\xintKeepNoExpand{integer}{list}
\xintkeepnoexpand{integer}{list}#S
\xintKeepUnbraced{integer}{list}
\xintkeepunbraced{integer}{list}#S
\xintKeepUnbracedNoExpand{integer}{list}
\xintkeepunbracednoexpand{integer}{list}#S

\xintTrim{integer}{list}
\xinttrim{integer}{list}#S
\xintTrimNoExpand{integer}{list}
\xinttrimnoexpand{integer}{list}#S
\xintTrimUnbraced{integer}{list}
\xinttrimunbraced{integer}{list}#S
\xintTrimUnbracedNoExpand{integer}{list}
\xinttrimunbracednoexpand{integer}{list}#S

\xintListWithSep{sep}{list}
\xintlistwithsep{sep}{list}#S
\xintListWithSepNoExpand{sep}{list}
\xintlistwithsepnoexpand{sep}{list}#S

\xintApply{macro}{list}
\xintapply{macro}{list}#S
\xintApplyNoExpand{macro}{list}
\xintapplynoexpand{macro}{list}#S
\xintApplyUnbraced{macro}{list}
\xintapplyunbraced{macro}{list}#S
\xintApplyUnbracedNoExpand{macro}{list}#*
\xintapplyunbracednoexpand{macro}{list}#S

\xintSeq{start-integer}{stop-integer}
\xintSeq[step]{start-integer}{stop-integer}

\xintloop#*
\xintbreakloop#*
\xintbreakloopanddo#*
\xintloopskiptonext#*
\xintiloop#*
\xintiloopindex#*
\xintbracediloopindex#*
\xintouteriloopindex#*
\xintbracedouteriloopindex#*
\xintbreakiloop#*
\xintbreakiloopanddo#*
\xintiloopskiptonext#*
\xintiloopskipandredo#*

\xintApplyInline{macro}{list}

\xintFor %<<param>%> in {%<csv list%>} \do {%<code%>}
\xintFor* %<<param>%> in {%<csv list%>} \do {%<code%>}

\xintifForFirst{YES branch}{NO branch}
\xintifForLast{YES branch}{NO branch}

\xintBreakFor
\xintBreakForAndDo{code}

\xintegers#*
\xintintegers
\xintdimensions
\xintrationals

\xintForpair %<params%> in {%<csv pair list%>} \do {%<code%>}
\xintForthree %<params%> in {%<csv triple list%>} \do {%<code%>}
\xintForfour %<params%> in {%<csv 4-tuple list%>} \do {%<code%>}

\xintAssign %<<braced things>%> \to %<<cmd list>%>
\xintAssign[%<options%>] %<<braced things>%> \to %<<cmd list>%>
\to{cmd}#Sd

#keyvals:\xintAssign
g
e
x
o
go
oo
goo
f
gf
#endkeyvals

\xintAssignArray %<<braced things>%> \to %<<cmd>%>
\xintAssignArray[%<options%>] %<<braced things>%> \to %<<cmd>%>
\xintDigitsOf %<<braced things>%> \to %<<cmd>%>
\xintDigitsOf[%<options%>] %<<braced things>%> \to %<<cmd>%>

#keyvals:\xintAssignArray,\xintDigitsOf
o
oo
f
#endkeyvals

\xintRelaxArray%<<array macro>%>

\xintNthEltPy#S
\xintReverse#S
\xintZip#S
\xintCSVLength#S
\xintCSVKeep#S
\xintCSVKeepx#S
\xintCSVTrim#S
\xintCSVNthEltPy#S
\xintCSVReverse#S
\xintCSVFirstItem#S
\xintCSVLastItem#S
