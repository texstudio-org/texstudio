# mfirstuc package
# Matthew Bertucci 10/5/2021 for v2.06

#include:etoolbox

\makefirstuc{text}
\xmakefirstuc{text}
\emakefirstuc{text}
\glsmakefirstuc{text}
\capitalisewords{text}
\MFUcapword{word%text}
\ifMFUhyphen#*
\MFUhyphentrue#*
\MFUhyphenfalse#*
\capitalisefmtwords{phrase%text}
\xcapitalisewords{text}
\ecapitalisewords{text}
\xcapitalisefmtwords{text}
\ecapitalisefmtwords{text}
\MFUnocap{word%text}
\gMFUnocap{word%text}
\MFUclear