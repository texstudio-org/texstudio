# jwjournal class
# Matthew Bertucci 2023/08/29

#include:class-einfart
#include:ProjLib
#include:tcolorbox
#include:tcolorboxlibrarymany
#include:needspace
#include:enumitem

#keyvals:\documentclass/jwjournal#c
paperstyle=#lightyellow,yellow,parchment,green,lightgray,gray,nord,dark
scroll
color entry
#endkeyvals

jwjournal-color-1#B
jwjournal-color-2#B
jwjournal-color-3#B
jwjournal-color-4#B
jwjournal-color-5#B
jwjournal-color-6#B
jwjournal-color-7#B
jwjournal-entry#B

\JWJournalEntry{date}{text}#S
\JWJournalItem{text}#S
\begin{jwjournal}#S
\end{jwjournal}#S
\JWJournalSkip#S
\JWJournalSkip[factor]#S
\JWJournalBack#S
\JWJournalBack[factor]#S
\begin{JWJournalCompactCenter}#S
\end{JWJournalCompactCenter}#S
\begin{JWJournalCenter}#S
\end{JWJournalCenter}#S
\begin{JWJournalLeft}#S
\end{JWJournalLeft}#S
\begin{JWJournalRight}#S
\end{JWJournalRight}#S
\JWJournalCompactCenterText{text}#S
\JWJournalShowImageCenter{imagefile}#Sg
\JWJournalShowImageCenter[options]{imagefile}#Sg
\JWJournalShowImageLeft{imagefile}#Sg
\JWJournalShowImageLeft[options]{imagefile}#Sg
\JWJournalShowImageRight{imagefile}#Sg
\JWJournalShowImageRight[options]{imagefile}#Sg
