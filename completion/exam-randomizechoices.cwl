# exam-randomizechoices package
# Matthew Bertucci 1/12/2021 for v0.2

#include:environ
#include:etoolbox
#include:pgffor

#keyvals:\usepackage/exam-randomizechoices#c
randomize
norandomize
keeplast
nokeeplast
overload
nooverload
debug
#endkeyvals

\begin{randomizechoices}
\begin{randomizechoices}[options%keyvals]
\end{randomizechoices}
\begin{randomizeoneparchoices}
\begin{randomizeoneparchoices}[options%keyvals]
\end{randomizeoneparchoices}
\begin{randomizecheckboxes}
\begin{randomizecheckboxes}[options%keyvals]
\end{randomizecheckboxes}
\begin{randomizeoneparcheckboxes}
\begin{randomizeoneparcheckboxes}[options%keyvals]
\end{randomizeoneparcheckboxes}

#keyvals:\begin{randomizechoices},\begin{randomizeoneparchoices},\begin{randomizecheckboxes},\begin{randomizeoneparcheckboxes}
randomize
norandomize
keeplast
nokeeplast
#endkeyvals

\setrandomizerseed{integer}
\printkeytable
\printkeytable[range]
\keylistquestionname{text}
\keylistkeyname{text}
\savekeylist
\savekeylist[macro%cmd]#d
\writekeylist{command}#d
\writekeylist[file]{command}#d