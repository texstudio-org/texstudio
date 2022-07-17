# tkzexample package
# Matthew Bertucci 2022/07/16 for v1.45c

#include:calc
#include:mdframed
#include:fancyvrb

#keyvals:\usepackage/tkzexample#c
saved
#endkeyvals

\begin{tkzexample}[options%keyvals]
\end{tkzexample}

#keyvals:\begin{tkzexample}#c
execute code
show num
overhang
code only
width=##L
code=#%color
graphic=#%color
overhang
num
numcolor=#%color
numbkgcolor=#%color
global num
code style=%<font commands%>
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
frame code=#%color
frame tex=#%color
above skip=##L
below skip=##L
hsep=##L
pre=%<code%>
post=%<code%>
latex=##L
vbox
#endkeyvals

\begin{tkzltxexample}[options%keyvals]#V
\end{tkzltxexample}

#keyvals:\begin{tkzltxexample}#c
width=##L
code=#%color
show num
num
global num
numcolor=#%color
numbkgcolor=#%color
normal
small
very small
right margin
left margin=##L
inner left margin=##L
inner right margin=##L
inner top margin=##L
inner bottom margin=##L
line frame width=##L
hsep=##L
typeset listing
frame code=#%color
ignorespaces
leave comments
vbox
#endkeyvals

\commenthandler#S
\fileexample#S
\iftkzcodesaved#S
\killienc#S
\tkzcodesavedfalse#S
\tkzcodesavedtrue#S
\tkzexamplebox#*
\tkzexamplewidth#*
\tkzFileSavedPrefix#*
\tkzltxexamplebox#*
\tkzltxexamplewidth#*
\tkzref#*
\tkzSavedCode#*
\tkzSavedCode[prefix=%<prefix%>]#*
\typesetcomment#S
\typesetcommentnum#S

graphicbackground#B
codebackground#B
codeonlybackground#B
numbackground#B
textcodecolor#B
numcolor#B
