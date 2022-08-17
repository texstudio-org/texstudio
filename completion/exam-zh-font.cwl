# exam-zh-font package
# Matthew Bertucci 2022/08/17 for v0.1.18

#include:expl3
#include:xparse
#include:unicode-math
#include:filehook
#include:etoolbox

#keyvals:\examsetup,\ExamPrintAnswerSet
font=#newcm,lm,times,termes,stix,xits,libertinus,garamond,pala,none
math-font=#newcm,lm,termes,stix,xits,libertinus,cambria,garamond,pala,asana,none
#endkeyvals

\bm{arg}#m
\square#m
\blacksquare#m
\checkmark
