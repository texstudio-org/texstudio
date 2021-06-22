# alterqcm package
# Matthew Bertucci 6/21/2021

#include:calc
#include:array
#include:multirow
#include:pifont

\begin{alterqcm}[keyvals]
\end{alterqcm}

#keyvals:\begin{alterqcm}
lq=##L
pq=##L
bonus=
malus=
numbreak=
points=
symb=
corsymb=
numstyle=
propstyle=
size=
afterpreskip=
long#true,false
sep#true,false
pre
VF
numprop
num#true,false
nosquare
title#true,false
correction
alea
tone=
ttwo=
language=#english,german,greek,italian,russian,chinese,unknown
transparent
#endkeyvals

\AQquestion[keyvals]{question}{{prop1},{prop2},...}#/alterqcm

#keyvals:\AQquestion
pq=##L
br=
#endkeyvals

\AQmessage{text}#/alterqcm

\AQms(height,depth)#*/alterqcm

\InputQuestionList{filepath}{prefix}{num1,num2,...}#/alterqcm

\AQannexe[keyvals]{start}{end}{number of props}

#keyvals:\AQannexe
VF
propstyle=
#endkeyvals

\AQpoints{number}