# spacingtricks package
# Matthew Bertucci 2023/12/06 for v1.8

#include:ifthen
#include:setspace
#include:calc
#include:xspace
#include:centeredline

#keyvals:\usepackage/spacingtricks#c
pifont
#endkeyvals

#ifOption:pifont
#include:pifont
#endif

\centered{text}
\footnotespace#*
\footnoteindent#*
\footnt{text}#*
\footnt[number]{text}#*
\strutheight#*
\strutdepth#*
\vstrut{height}
\vstrut[depth]{height}
\cstrut{height}
\parindentlength#*
\begin{indentblock}
\begin{indentblock}[length]
\end{indentblock}
\begin{compactlist}
\begin{compactlist}[symbol]
\end{compactlist}
\bul#*
\dash#*
\ddash#*
\aster#*
\hand#*
\checksymb#*
\arrowsymb#*
\compactlistindent#*
\ie
\eg
\dualboxes{left}{right}
\dualboxes[pos]{left}{right}
\dualboxes*{left}{right}
\dualboxes*[pos]{left}{right}
\begin{juxtapose}
\begin{juxtapose}[left-ratio]
\end{juxtapose}
\otherside
\juxtopskip#*
\juxbottomskip#*
\juxsepspace#*
