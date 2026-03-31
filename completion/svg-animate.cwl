# svg-animate package
# Matthew Bertucci 2026/03/20 for v1.0

#include:tikz
#include:graphicx
#include:tikzlibraryanimations

\begin{animate}
\begin{animate}[options%keyvals]
\end{animate}

\animstep
\animstep[options%keyvals]
\reveal{content%text}
\reveal[options%keyvals]{content%text}
\noanimate{content%text}

#keyvals:\begin{animate},\animstep,\reveal
duration=%<seconds%>
active opacity=%<value%>
inactive opacity=%<value%>
loop#true,false
blink=%<seconds%>
blink on opacity=%<value%>
blink off opacity=%<value%>
static
step=%<spec%>
noanimate
#endkeyvals

\svganimateversion#S
\svganimatedate#S