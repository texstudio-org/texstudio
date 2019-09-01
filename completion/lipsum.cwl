# doncherry/2013-04-25 for lipsum v1.2
# thatlittleboy/2018-11-30 for lipsum v2.0
# muzimuzhi/11 Aug 2019 for lipsum v2.2

#include:expl3
#include:xparse

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

\SetLipsumDefault{num}#*
\SetLipsumDefault{%<num%>-%<num%>}#*
\LipsumPar{num}#*
\unpacklipsum#*
\unpacklipsum[num]#*
\unpacklipsum*#*
\unpacklipsum*[num]#*
\lipsumexp#*

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
\SetLipsumText{lipsum text definition filename}
