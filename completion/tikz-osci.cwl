# tikz-osci package
# Matthew Bertucci 2023/10/09 for v0.3.0

#include:xcolor
#include:pgfkeys
#include:pgfplots
#include:tikz
#include:tikzlibraryshapes
#include:tikzlibrarypositioning
#include:tikzlibrarydecorations.markings
#include:tikzlibrarydecorations.pathmorphing
#include:tikzlibrarydecorations.pathreplacing
#include:tikzlibrarycalc
#include:tikzlibrarycalc
#include:tikzlibrarypatterns
#include:tikzlibraryshapes.geometric

\osci
\osci[options%keyvals]

#keyvals:\osci#c
scale=%<factor%>
rounded corners=%<radius%>
second channel=#0,1
screen offset one=%<offset%>
screen offset two=%<offset%>
time div=%<milliseconds%>
voltage div one=%<volts%>
voltage div two=%<volts%>
sample rate=%<rate%>
xy mode=#0,1
math mode=#0,1,2,3,4
math mode hide source=#0,1
func one=%<function%>
func two=%<function%>
indicators=#0,1
color one=%<hexadecimal%>
color text one=%<hexadecimal%>
color two=%<hexadecimal%>
color text two=%<hexadecimal%>
color three=%<hexadecimal%>
color text three=%<hexadecimal%>
graph back color=%<hexadecimal%>
info back color=%<hexadecimal%>
main axis color=%<hexadecimal%>
grid color=%<hexadecimal%>
#endkeyvals