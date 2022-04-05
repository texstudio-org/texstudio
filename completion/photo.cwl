# photo package
# Matthew Bertucci 4/4/2022 for v2.1f

#keyvals:\usepackage/photo#c
shortlop
left
right
in
out
top
center
bottom
under
side
#endkeyvals

\ifoddpage{true}{false}
\ifoddpage[label]{true}{false}
\ifoddpagelabel#*
\boxbaset{LR material%text}
\boxbasec{LR material%text}
\boxbaseb{LR material%text}
\begin{photo}
\begin{photo}[float pos]
\end{photo}
\begin{photo*}
\begin{photo*}[float pos]
\end{photo*}
\defaultphotoplacement{float pos}
\thephoto#*
\photoname#*
\listphotoname#*
\listofphotos
\putphoto{label}{photographer}{photo}{caption%text}
\putphoto{label}{photographer}{photo}[toc-caption%text]{caption%text}
\putphoto[pos]{label}{photographer}{photo}{caption%text}
\putphoto[pos]{label}{photographer}{photo}[toc-caption%text]{caption%text}
\oecaptionsep#*
\minoecaptionwidth#*
\photographerfont#*
\begin{Photo}{label}{photographer}{caption%text}
\begin{Photo}{label}{photographer}[toc-caption%text]{caption%text}
\begin{Photo}[pos]{label}{photographer}{caption%text}
\begin{Photo}[pos]{label}{photographer}[toc-caption%text]{caption%text}
\end{Photo}
\phref{label}#r
\Phref{label}#r