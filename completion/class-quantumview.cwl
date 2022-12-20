# quantumview class
# Matthew Bertucci 4/7/2022 for v5.1

#include:xkeyval
#include:etoolbox
#include:soul
#include:fancyhdr
#include:caption
#include:lmodern
#include:bbm
#include:xcolor
#include:xstring
#include:tikz
#include:tikzlibrarycalc
#include:hyperref

#keyvals:\documentclass/quantumview#c
html
#endkeyvals

#ifOption:html
#include:verbatim
#include:graphicx
#endif

\acknowledgments{text}#S
\acknowledgmentsname#*
\addauthortolabel{arg1}{arg2}#*
\address[id]{affiliation}#*
\address{affiliation}#*
\affil[id]{affiliation}
\affil{affiliation}
\affiliation{affiliation}
\altaffiliation{affiliation}#*
\author[id]{name}
\begin{acknowledgements}
\end{acknowledgements}
\collaboration{name}#*
\corr{text1%text}{text2%text}
\ead[url]{%<URL%>}#*
\ead{email%URL}#*U
\email[prefix]{email%URL}#*U
\email{email%URL}#U
\homepage[prefix]{URL}#*U
\homepage{URL}#U
\ins{text}
\keywords{keywords}#*
\nocontentsline{arg1}{arg2}{arg3}#*
\openone#m
\orcid[prefix]{ORCID}#*
\orcid{ORCID}
\Quantum
\quantumarticleversion#*
\thanks[prefix]{text}#*

quantumviolet#B
quantumgray#B
