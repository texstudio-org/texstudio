# alterqcm package
# Matthew Bertucci 2026/10/29 for v5.00c

#include:pgfkeys
#include:calc
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

#keyvals:\begin{alterqcm},\AQset
lq=##L
pq=##L
bonus=%<number%>
malus=%<number%>
numbreak=%<number%>
points=%<number%>
symb=%<symbol%>
corsymb=%<symbol%>
numstyle=%<command%>
propstyle=%<command%>
size=%<fontsize cmd%>
afterpreskip=##L
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
language=#french,english,german,greek,italian,russian,chinese,unknown
transparent
#endkeyvals

\AQquestion{%<question%>}{%<{prop1},{prop2},...%>}#/alterqcm
\AQquestion[%<options%>]{%<question%>}{%<{prop1},{prop2},...%>}#/alterqcm

#keyvals:\AQquestion
pq=##L
br={%<list%>}
#endkeyvals

\AQmessage{text}#/alterqcm

\AQms(height,depth)#*/alterqcm

\InputQuestionList{filepath%file}{prefix}{num1,num2,...}#/alterqcm

\AQannexe{start}{end}{number of props}
\AQannexe[options%keyvals]{start}{end}{number of props}

#keyvals:\AQannexe
VF#true,false
propstyle=%<command%>
#endkeyvals

\altersquare
\dingsquare
\dingchecksquare

\alterblacksquare#*
\aqdepthadvance#*
\aqfoottext#*
\aqheightadvance#*
\aqlabelforquest#*
\aqlabelforrep#*
\AQpoints{number}#*
\aqpretxt#*
\aqpretxtVF#*
\AQset{options%keyvals}#*
\aqtextforfalse#*
\aqtextfortrue#*
\points{points}#S