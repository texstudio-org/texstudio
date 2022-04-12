# meetingmins class
# Matthew Bertucci 4/11/2022 for v1.6

#include:geometry
#include:fontenc
# loads T1 option of fontenc
#include:lmodern
#include:fancyhdr
#include:enumitem
#include:environ

#keyvals:\documentclass/meetingmins#c
agenda
chair
notes
# options passed to article class
a4paper
a5paper
b5paper
letterpaper
legalpaper
executivepaper
landscape
10pt
11pt
12pt
oneside
twoside
draft
final
titlepage
notitlepage
onecolumn
twocolumn
leqno
fleqn
openbib
#endkeyvals

#ifOption:chair
#include:mathabx
#include:xstring
#endif

\begin{items}
\end{items}
\begin{subitems}
\end{subitems}
\begin{subsubitems}
\end{subsubitems}
\begin{hiddenitems}
\end{hiddenitems}
\begin{hiddensubitems}
\end{hiddensubitems}
\begin{hiddensubsubitems}
\end{hiddensubsubitems}
\begin{hiddentext}
\end{hiddentext}

\absent{name1,name2,...}
\alsopresent{name1,name2,...}
\chair{name}
\nextmeeting{date}
\priormins
\role{name}{role%text}
\secretary{name}
\setcommittee{name%text}
\setdate{date}
\setmembers{name1,name2,...}
\setpresent{name1,name2,...}

\begin{emptysection}#*
\end{emptysection}#*
\begin{itemlist}#*
\end{itemlist}#*
\begin{subitemlist}#*
\end{subitemlist}#*
\begin{subsubitemlist}#*
\end{subsubitemlist}#*

# from T1 option of fontenc
\DH#n
\dh#n
\dj#n
\DJ#n
\guillemetleft#n
\guillemetright#n
\guillemotleft#*n
\guillemotright#*n
\guilsinglleft#n
\guilsinglright#n
\Hwithstroke#n
\hwithstroke#n
\k{arg}#n
\NG#n
\ng#n
\quotedblbase#n
\quotesinglbase#n
\textogonekcentered{arg}#n
\textquotedbl#n
\th#n
\TH#n