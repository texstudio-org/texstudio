# doncherry/2013-04-25 for lipsum v1.2
# thatlittleboy/2018-11-30 for lipsum v2.0
# muzimuzhi/11 Aug 2019 for lipsum v2.2
# Matthew Bertucci 9/22/2021 for v2.7

#include:l3keys2e

\lipsum
\lipsum[num]
\lipsum[num][num]
\lipsum[%<num%>-%<num%>]
\lipsum[%<num%>-%<num%>][%<num%>-%<num%>]
\lipsum*
\lipsum*[num]
\lipsum*[num][num]
\lipsum*[%<num%>-%<num%>]
\lipsum*[%<num%>-%<num%>][%<num%>-%<num%>]

\unpacklipsum#*
\unpacklipsum[num]#*
\unpacklipsum*#*
\unpacklipsum*[num]#*
\lipsumexp#*

\setlipsum{keyvals}

#keyvals:\setlipsum#c,\usepackage/lipsum#c
nopar#true,false
text=#lipsum,cicero,lipsum-cs
language=%<language%>
auto-lang#true,false
default-range=%<i-j%>
par-before=%<tokens%>
par-begin=%<tokens%>
par-sep=%<tokens%>
par-end=%<tokens%>
par-after=%<tokens%>
sentence-before=%<tokens%>
sentence-begin=%<tokens%>
sentence-sep=%<tokens%>
sentence-end=%<tokens%>
sentence-after=%<tokens%>
par-before*=%<tokens%>
par-begin*=%<tokens%>
par-sep*=%<tokens%>
par-end*=%<tokens%>
par-after*=%<tokens%>
sentence-before*=%<tokens%>
sentence-begin*=%<tokens%>
sentence-sep*=%<tokens%>
sentence-end*=%<tokens%>
sentence-after*=%<tokens%>
#endkeyvals

\SetLipsumText{lipsum text definition filename%file}#*
\SetLipsumDefault{num}#*
\SetLipsumDefault{%<num%>-%<num%>}#*
\LipsumPar{num}#*

\SetLipsumParListStart{tokens}#*
\SetLipsumParListStart*{tokens}#*
\SetLipsumParListEnd{tokens}#*
\SetLipsumParListEnd*{tokens}#*
\SetLipsumSentenceListStart{tokens}#*
\SetLipsumSentenceListStart*{tokens}#*
\SetLipsumSentenceListEnd{tokens}#*
\SetLipsumSentenceListEnd*{tokens}#*

\SetLipsumParListSurrounders{start}{end}#*
\SetLipsumParListSurrounders*{start}{end}#*
\SetLipsumSentenceListSurrounders{start}{end}#*
\SetLipsumSentenceListSurrounders*{start}{end}#*

\SetLipsumParListItemStart{tokens}#*
\SetLipsumParListItemStart*{tokens}#*
\SetLipsumParListItemEnd{tokens}#*
\SetLipsumParListItemEnd*{tokens}#*
\SetLipsumSentenceListItemStart{tokens}#*
\SetLipsumSentenceListItemStart*{tokens}#*
\SetLipsumSentenceListItemEnd{tokens}#*
\SetLipsumSentenceListItemEnd*{tokens}#*

\SetLipsumParListItemSurrounders{start}{end}#*
\SetLipsumParListItemSurrounders*{start}{end}#*
\SetLipsumSentenceListItemSurrounders{start}{end}#*
\SetLipsumSentenceListItemSurrounders*{start}{end}#*

\SetLipsumParListItemSeparator{tokens}#*
\SetLipsumParListItemSeparator*{tokens}#*
\SetLipsumSentenceListItemSeparator{tokens}#*
\SetLipsumSentenceListItemSeparator*{tokens}#*

\LipsumProtect{tokens}#*
\LipsumRestoreParList#*
\LipsumRestoreSentenceList#*
\LipsumRestoreAll#*

\NewLipsumPar{paragrph}#*
\SetLipsumLanguage{language}#*
