# tkz-fct package
# Matthew Bertucci 9/17/2021 for v1.4c

#include:tkz-base
#include:fp

\tkzFct{gnuplot expression}#/tikzpicture
\tkzFct[options%keyvals]{gnuplot expression}#/tikzpicture

#keyvals:\tkzFct#c
domain=
samples=
id=
color=#%color
line width=##L
style=
#endkeyvals

\tkzDefPointByFct(number)#/tikzpicture
\tkzDefPointByFct[options%keyvals](number)#/tikzpicture

#keyvals:\tkzDefPointByFct#c
draw
with=
ref=
#endkeyvals

\tkzDrawTangentLine(number)#/tikzpicture
\tkzDrawTangentLine[options%keyvals](number)#/tikzpicture

#keyvals:\tkzDrawTangentLine#c
draw
with=
kr=
kl=
#endkeyvals

\tkzDrawArea[options%keyvals]#/tikzpicture

#keyvals:\tkzDrawArea#c
domain=
with=
color=
opacity=
style=
#endkeyvals

\tkzDrawAreafg[options%keyvals]#/tikzpicture

#keyvals:\tkzDrawAreafg#c
between=
domain=
opacity=
#endkeyvals

\tkzDrawRiemannSum[options%keyvals]#/tikzpicture
\tkzDrawRiemannSumInf[options%keyvals]#/tikzpicture
\tkzDrawRiemannSumSup[options%keyvals]#/tikzpicture
\tkzDrawRiemannSumMid[options%keyvals]#/tikzpicture

#keyvals:\tkzDrawRiemannSum#c,\tkzDrawRiemannSumInf#c,\tkzDrawRiemannSumSup#c,\tkzDrawRiemannSumMid#c
interval=
number=
#endkeyvals

\tkzFctPar{%<x(t)%>}{%<y(t)%>}#/tikzpicture
\tkzFctPar[%<options%>]{%<x(t)%>}{%<y(t)%>}#/tikzpicture
\tkzFctPolar{%<f(t)%>}#/tikzpicture
\tkzFctPolar[%<options%>]{%<f(t)%>}#/tikzpicture

#keyvals:\tkzFctPar#c,\tkzFctPolar#c
domain=
samples=
id=
color=#%color
line width=##L
style=
#endkeyvals
