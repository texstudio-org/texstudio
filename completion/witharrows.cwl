# witharrows package
# Matthew Bertucci 9/8/2021 for v2.6c

#include:expl3
#include:l3keys2e
#include:varwidth
#include:tikz
#include:xparse

\begin{WithArrows}#m\array
\begin{WithArrows}[options%keyvals]#m\array
\end{WithArrows}
\begin{DispWithArrows}#\math,array
\begin{DispWithArrows}[options%keyvals]#\math,array
\begin{DispWithArrows}<left-brace-content>[options%keyvals]#*\math,array
\end{DispWithArrows}
\begin{DispWithArrows*}#\math,array
\begin{DispWithArrows*}[options%keyvals]#\math,array
\begin{DispWithArrows*}<left-brace-content>[options%keyvals]#*\math,array
\end{DispWithArrows*}
\WithArrowsOptions{options%keyvals}

#keyvals:\begin{WithArrows},\WithArrowsOptions
c
b
#endkeyvals

#keyvals:\begin{WithArrows},\begin{DispWithArrows},\begin{DispWithArrows*},\WithArrowsOptions
tikz=
xoffset=##L
command-name=
code-before=
code-after=
format=%<cols%>
show-nodes
show-node-names
displaystyle
ll
lr
rl
rr
i
group
groups
up-and-down={%<options%>}
jot=##L
interline=##L
tikz-code={%<code%>}
start-adjust=##L
end-adjust=##L
ygap=##L
ystart=##L
max-length-of-arrow=##L
#endkeyvals

#keyvals:\begin{WithArrows},\begin{DispWithArrows},\begin{DispWithArrows*}
name=
#endkeyvals

#keyvals:\begin{DispWithArrows},\begin{DispWithArrows*},\WithArrowsOptions
wrap-lines
tagged-lines=
fleqn
mathindent=##L
subequations
standard-behaviour-with-items
#endkeyvals

#keyvals:\begin{DispWithArrows},\begin{DispWithArrows*}
left-brace
left-brace={%<content%>}
replace-left-brace-by=
#endkeyvals

#keyvals:\WithArrowsOptions
xoffset-for-o-arrows=##L
up-and-down/width=##L
up-and-down/radius=##L
no-arrows
#endkeyvals

\Arrow{label%plain}#/WithArrows,DispWithArrows,DispWithArrows*
\Arrow[options%keyvals]{label%plain}#/WithArrows,DispWithArrows,DispWithArrows*

#keyvals:\Arrow
jump=%<integer%>
xoffset=##L
tikz=
tikz-code={%<code%>}
ll
lr
rl
rr
i
new-group
o
up
up={%<options%>}
down
down={%<options%>}
#endkeyvals

\MultiArrow{row1,row2,...}{label%plain}#*
\WithArrowsLastEnv#*
\tag{label%plain}#m
\tag*{label%plain}#m
\notag#m
\tagnextline#/DispWithArrows,DispWithArrows*
\WithArrowsRightX#*
\WithArrowsNewStyle{style name}{options}#*

#ifOption:footnote
#include:footnote
#endif

#ifOption:footnotehyper
#include:footnotehyper
#endif

\WithArrowsNbLines#*