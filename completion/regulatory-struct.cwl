# regulatory-struct package
# Matthew Bertucci 2026/09/12 for v1.0.0

#include:ifthen
#include:xcolor
#include:enumitem
#include:fmtcount
#include:scrextend
#include:zref-user
#include:zref-counter
#include:zref-hyperref
#include:zref-xr
#include:zref-clever
#include:hyperref
#include:translations

\regulatorysetup{options%keyvals}

#keyvals:\usepackage/regulatory-struct#c,\regulatorysetup
md#true,false
bib2gls#true,false
legacy#true,false
alldefs#true,false
nameinlink#true,false
defstyle=%<glossary style%>
sourcestyle=#full,short,voluit,verkort
attachmentlink=#goto,annotation
bronstijl=#full,short,voluit,verkort
#endkeyvals

#ifOption:md
#include:regulatory-md
#endif
#ifOption:md=true
#include:regulatory-md
#endif

\begin{paras}
\end{paras}
\begin{provisions}
\end{provisions}

\ProvidesRegulatoryLanguage{language}#*
\RegulatoryLoadLanguage{language}#*

\thearticle#S
\thepara#S
\theprovisions#S