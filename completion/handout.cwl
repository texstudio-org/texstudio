# handout package
# Matthew Bertucci 2/8/2022 for v1.6.0

#include:kvoptions
#include:etoolbox
#include:suffix

#keyvals:\usepackage/handout#c
disabled#true,false
numbering#true,false
sectioning#true,false
printing#true,false
dir=%<folder%>
#endkeyvals

#ifOption:numbering
\thehandoutnumber
#endif
#ifOption:numbering=true
\thehandoutnumber
#endif

\handout{file}#i

\nothandout{content%text}
\onlyhandout{content%text}
\forhandout{content%text}
\forhandout*{content%text}

\handoutnumberintxt{position}#*
\handoutnumber{position}#*