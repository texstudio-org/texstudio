# cmsendnotes package
# Matthew Bertucci 4/21/2022 for v3.16

#include:kvoptions
#include:endnotes
#include:etoolbox
#include:nameref

#keyvals:\usepackage/cmsendnotes#c
split=#part,chapter,section,subsection
headername=%<name%>
subheadername=%<name%>
runningname=%<name%>
hyper#true,false
enotelinks#true,false
noheader#true,false
nosubheader#true,false
blocknotes#true,false
#endkeyvals

\enoteheader#*
\enotepartheader#*
\enoteskip#*
\enotesubheader#*
\intropartheader#*
\introsubheader#*
\savedhref{URL}{text%plain}#SU
\savedurl{URL}#SU
\theendnotesbypart
\theendnotesbypart*
\theendnotesbypart*[number]
\theendnotesbypart[number]
\theHendnote#*