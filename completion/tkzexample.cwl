# tkzexample package
# Matthew Bertucci 10/8/2021 for v1.43c

#include:calc
#include:mdframed
#include:fancyvrb

\iftkzcodesaved#*
\tkzcodesavedtrue#*
\tkzcodesavedfalse#*

graphicbackground#B
codebackground#B
codeonlybackground#B
numbackground#B
textcodecolor#B
numcolor#B

\begin{tkzexample}[options%keyvals]
\end{tkzexample}
\begin{tkzltxexample}[options%keyvals]#V
\end{tkzltxexample}

#keyvals:\begin{tkzexample}#c
execute code
show num
overhang
code only
width=##L
code=
graphic=
overhang=
num=
numcolor=#%color
numbkgcolor=#%color
global num=
code style=
normal
small
very small
right margin=##L
left margin=##L
inner left margin=##L
inner right margin=##L
inner top margin=##L
inner bottom margin=##L
line frame width=##L
frame code=
frame tex=
above skip=##L
below skip=##L
hsep=##L
pre=
post=
latex=
#endkeyvals

\tkzexamplewidth#*
\tkzexamplebox#*
\tkzref#*
\tkzFileSavedPrefix#*
\tkzltxexamplewidth#*
\tkzltxexamplebox#*
\killienc#*
\tkzSavedCode#*