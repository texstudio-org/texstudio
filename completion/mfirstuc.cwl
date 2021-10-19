# mfirstuc package
# Matthew Bertucci 10/19/2021 for v2.07

#include:etoolbox

\makefirstuc{text}
\MFUskippunc{punctuation}
\xmakefirstuc{text}
\emakefirstuc{text}
\glsmakefirstuc{text}
\capitalisewords{text}
\MFUcapword{word%text}
\ifMFUhyphen#*
\MFUhyphentrue#*
\MFUhyphenfalse#*
\MFUwordbreak{puncutation}
\capitalisefmtwords{phrase%text}
\xcapitalisewords{text}
\ecapitalisewords{text}
\xcapitalisefmtwords{text}
\ecapitalisefmtwords{text}
\MFUnocap{word%text}
\gMFUnocap{word%text}
\MFUclear
