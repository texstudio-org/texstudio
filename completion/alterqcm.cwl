# alterqcm package
# Matthew Bertucci 9/17/2021 for v4.42c

#include:xkeyval
#include:calc
#include:ifthen
#include:array
#include:multirow
#include:pifont

#keyvals:\usepackage/alterqcm#c
french
english
german
greek
russian
italian
chinese
unknown
#endkeyvals

\begin{alterqcm}
\begin{alterqcm}[options%keyvals]
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
size=%<fontsize cmd%>
afterpreskip=
long#true,false
sep#true,false
pre#true,false
VF#true,false
numprop#true,false
num#true,false
nosquare#true,false
title#true,false
correction#true,false
alea#true,false
tone=%<text%>
ttwo=%<text%>
language=#english,german,greek,italian,russian,chinese,unknown
transparent
#endkeyvals

\AQquestion{%<question%>}{%<{prop1},{prop2},...%>}#/alterqcm
\AQquestion[%<options%>]{%<question%>}{%<{prop1},{prop2},...%>}#/alterqcm

#keyvals:\AQquestion
pq=##L
br=
#endkeyvals

\AQmessage{text}#/alterqcm

\AQms(height,depth)#*/alterqcm

\InputQuestionList{filepath%file}{prefix}{num1,num2,...}#/alterqcm

\AQannexe{start}{end}{number of props}
\AQannexe[options%keyvals]{start}{end}{number of props}

#keyvals:\AQannexe
VF
propstyle=
#endkeyvals

\AQpoints{number}

\dingsquare
\dingchecksquare

\aqlabelforquest#*
\aqlabelforrep#*
\aqfoottext#*
\nextrandom#*
\setrannum{register}{min}{max}#*
\points{points}#*
\aqheightadvance#*
\aqdepthadvance#*
\aqpretxt#*
\aqpretxtVF#*
\aqtextfortrue#*
\aqtextforfalse#*
\addtotoks{arg1}\to{arg2}#*
\to{arg}#S
