# exam-zh-font package
# Matthew Bertucci 2022/07/29 for v0.1.13

#include:expl3
#include:xparse
#include:unicode-math
#include:filehook

#keyvals:\examsetup,\ExamPrintAnswerSet
font=#newcm,lm,times,termes,stix,xits,libertinus,none
math-font=#newcm,lm,termes,stix,xits,libertinus,cambria,none
#endkeyvals

\bm{arg}#m
\square#m
\blacksquare#m
\checkmark