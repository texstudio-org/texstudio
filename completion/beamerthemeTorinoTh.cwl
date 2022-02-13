# TorinoTh beamertheme
# Matthew Bertucci 2/12/2022 for v2.2

#include:ifxetex
#include:pifont
#include:fontspec
#include:xunicode
#include:xltxtra
#include:metalogo
#include:xkeyval
#include:polyglossia

#keyvals:\usetheme/TorinoTh#c
language=%<language%>
titlepagelogo=%<imagefile%>
bullet=#square,diamond,triangle,circle
pageofpages=%<text%>
titleline#true,false
color=#%color
secondcandidate#true,false
secondsupervisor#true,false
secondlogo#true,false
thirdlogo#true,false
assistantsupervisor#true,false
secondassistantsupervisor#true,false
notshowauthor
coding=#utf8x,utf8,latin1
#endkeyvals

\begin{tframe}{title%text}
\end{tframe}
\titlepageframe
\highlight{text}
\highlightbf{text}
\setsubject{subject%text}

# from TorinoTh outertheme
\headerheight#*

# from TorinoTh innertheme
\ateneo{institute%text}
\insertateneo#*
\rel{supervisor}
\begin{adv}
\end{adv}
\begin{disadv}
\end{disadv}
\options#*
\optiond#*
\optiont#*
\optionc#*

# from TorinoTh colortheme
navyblue#B
cerulean#B
processblue#B
forestgreen#B
yellowgreen#B
redorange#B
apricot#B

# from TorinoTh fonttheme
# no user commands