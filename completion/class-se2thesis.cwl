# se2thesis class
# Matthew Bertucci 2023/01/27 for v2.1.0

#include:graphicx
#include:translations
#include:class-scrreprt
#include:se2colors
#include:se2fonts
#include:microtype
#include:lua-widow-control
#include:selnolig
#include:scrlayer-scrpage
#include:ifthen
#include:ntheorem
#include:tcolorbox

#keyvals:\documentclass/se2thesis#c
class=#scrreprt,scrartcl,scrbook
paper=#a4,a5,b5
logofile={%<path-to-file%>}
thesistype=#bachelor,bachelorproposal,master,masterproposal,phd,phdproposal
biblatex#true,false
colormode=#cmyk,rgb,bw
#endkeyvals

#ifOption:class=scrartcl
#include:class-scrartcl
#endif
#ifOption:class=scrbook
#include:class-scrbook
#endif

#ifOption:biblatex
#include:biblatex
#endif
#ifOption:biblatex=true
#include:biblatex
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
