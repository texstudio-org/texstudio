# se2thesis class
# Matthew Bertucci 2023/04/18 for v3.0.0

#include:graphicx
#include:translations
#include:class-scrbook
#include:se2colors
#include:se2fonts
#include:scrlayer-scrpage
#include:ifthen
#include:ntheorem
#include:tcolorbox

#keyvals:\documentclass/se2thesis#c
class=#scrreprt,scrartcl,scrbook
paper=#a4,b5
logofile={%<path-to-file%>}
thesistype=#bachelor,bachelorproposal,master,masterproposal,phd,phdproposal
colormode=#cmyk,rgb,bw
#endkeyvals

#ifOption:class=scrartcl
#include:class-scrartcl
#endif
#ifOption:class=scrreprt
#include:class-scrreprt
#endif

\version{version}
\degreeprogramme{programme-name}
\matrnumber{matriculation-number}
\supervisor{name}
\cosupervisor{name}
\advisor{name}
\coadvisor{name}
\department{name}
\institute{name}
\institute[short-name]{name}
\external{name}
\location{name-of-town}
\begin{abstract}[language]
\begin{acknowledgements}
\begin{acknowledgements}[language]
\end{acknowledgements}
\authorshipDeclaration
\authorshipDeclaration[location]#*
\signatureBox{signature-name}
\signatureBox[width]{signature-name}
\begin{resq}
\begin{resq}[heading%text]
\end{resq}
\begin{hyp}
\begin{hyp}[heading%text]
\end{hyp}
\begin{summary}{label text%text}
\end{summary}
\headingdot#*
