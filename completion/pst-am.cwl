# pst-am package
# Matthew Bertucci 2/25/2022 for v1.02

#include:pstricks
#include:pst-plot
#include:pst-node
#include:pst-xkey
#include:numprint
#include:multido

\psAM
\psAM[options%keyvals]

#keyvals:\psAM
BW#true,false
C=%<capacitance in F%>
Centering#true,false
enveloppe#true,false
frequenceAudio=%<modulated signal frequency in Hz%>
frequencePorteuse=%<carrier frequency in Hz%>
linewidth=##L
R=%<resistance in Ω%>
SignalDemodule#true,false
SignalFinal#true,false
SignalModulant#true,false
SignalModule#true,false
SignalPorteuse#true,false
SignalRedresse#true,false
timeDiv=%<time base in s/div%>
title=%<text%>
traceU#true,false
U0=%<offset in V%>
Um=%<modulated signal amplitude in V%>
UMandUm#true,false
Up=%<carrier amplitude in V%>
values#true,false
voltDivY1=%<coeff in V/div%>
voltDivY2=%<coeff in V/div%>
XY#true,false
#endkeyvals

Bleu#B