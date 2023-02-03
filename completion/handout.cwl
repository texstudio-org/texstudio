# handout package
# Matthew Bertucci 12/12/2021 for v1.6.0

#include:kvoptions
#include:etoolbox
#include:suffix

#keyvals:\usepackage/handout#c
dir=%<file path%>
sectioning#true,false
disabled#true,false
printing#true,false
numbering#true,false
#endkeyvals

\handout{file path%file}

\thehandoutnumber#*
\handoutnumber{arg}#*
\handoutnumberintxt{arg}#*

\disablehandout
\enablehandout

\onlyhandout{contents%text}
\nothandout{contents%text}
\forhandout{contents%text}
\forhandout*{contents%text}
