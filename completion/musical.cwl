# musical package
# Matthew Bertucci 2/15/2022

#include:ifthen
#include:fancyhdr
#include:etoolbox
#include:xspace
#include:titlesec
#include:footmisc
#include:tcolorbox
#include:tcolorboxlibrarybreakable
#include:tcolorboxlibraryskins

\scripttitles#*
\themusicalpage#*

#keyvals:\pagestyle#c,\thispagestyle#c
scriptheader
#endkeyvals

\begin{script}
\end{script}
\theactcounter#*
\thescenecounter#*
\act
\scene{setting%text}
\scene[title]{setting%text}
\sectionname#*
\setdescription#*
\rehearsalmark{mark}
\transition
\transition[name]
\speechmargin#*
\begin{spokentext}#*
\end{spokentext}#*
\begin{lyrictext}#*
\end{lyrictext}#*
\dialogfootnote{text}#*
\dialog{character}{text}
\charactername#*
\lyrics{character}{lyrics%text}
\spacer{text%plain}
\stdir{direction%text}
\music{title%text}
\dance{title%text}
\pause
\dialogue{character}{text}#*
\listofsongs
\listofdances
\addcharacter{name}{description%text}
\addcharacter[nickname]{name}{description%text}
\character{name}
\comment{comment%text}#*
