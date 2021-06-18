# tkz-fct package
# Matthew Bertucci 6/17/2021

#include:tkz-base
#include:fp

\tkzFct[local options%keyvals]{gnuplot expression}#/tikzpicture

#keyvals:\tkzFct#c
domain=
samples=
id=
color=#%color
line width=##L
style=
#endkeyvals

\tkzDefPointByFct[local options%keyvals](number)#/tikzpicture

#keyvals:\tkzDefPointByFct#c
draw
with=
ref=
#endkeyvals

\tkzDrawTangentLine[local options%keyvals](number)#/tikzpicture

#keyvals:\tkzDrawTangentLine#c
draw
with=
kr=
kl=
#endkeyvals

\tkzDrawArea[local options%keyvals]#/tikzpicture

#keyvals:\tkzDrawArea#c
domain=
with=
color=
opacity=
style=
#endkeyvals

\tkzDrawAreafg[local options%keyvals]#/tikzpicture

#keyvals:\tkzDrawAreafg#c
between=
domain=
opacity=
#endkeyvals

\tkzDrawRiemannSum[local options%keyvals]#/tikzpicture
\tkzDrawRiemannSumInf[local options%keyvals]#/tikzpicture
\tkzDrawRiemannSumSup[local options%keyvals]#/tikzpicture
\tkzDrawRiemannSumMid[local options%keyvals]#/tikzpicture

#keyvals:\tkzDrawRiemannSum#c,\tkzDrawRiemannSumInf#c,\tkzDrawRiemannSumSup#c,\tkzDrawRiemannSumMid#c
interval=
number=
#endkeyvals

\tkzFctPar[local options%keyvals]{x(t)}{y(t)}#/tikzpicture
\tkzFctPolar[local options%keyvals]{f(t)}#/tikzpicture

#keyvals:\tkzFctPar#c,\tkzFctPolar#c
domain=
samples=
id=
color=#%color
line width=##L
style=
#endkeyvals

