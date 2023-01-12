# witharrows package
# Matthew Bertucci 2023/01/01 for v2.8

#include:l3keys2e
#include:varwidth
#include:tikz
#include:tikzlibrarybending

#keyvals:\usepackage/witharrows#c
footnote
footnotehyper
#endkeyvals

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

#keyvals:\begin{WithArrows},\WithArrowsOptions,\WithArrowsNewStyle
c
b
right-overlap#true,false
#endkeyvals

#keyvals:\begin{WithArrows},\begin{DispWithArrows},\begin{DispWithArrows*},\WithArrowsOptions,\WithArrowsNewStyle
tikz={%<TikZ options%>}
xoffset=##L
command-name=%<csname%>
code-before=%<code%>
code-after=%<code%>
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
adjust=##L
ygap=##L
ystart=##L
max-length-of-arrow=##L
%witharrowsstyle
#endkeyvals

#keyvals:\begin{WithArrows},\begin{DispWithArrows},\begin{DispWithArrows*},\WithArrowsNewStyle
name=%<node name%>
#endkeyvals

#keyvals:\begin{DispWithArrows},\begin{DispWithArrows*},\WithArrowsOptions,\WithArrowsNewStyle
wrap-lines
tagged-lines={%<line1,line2,...%>}
fleqn
mathindent=##L
subequations
standard-behaviour-with-items
#endkeyvals

#keyvals:\begin{DispWithArrows},\begin{DispWithArrows*},\WithArrowsNewStyle
left-brace
left-brace={%<content%>}
replace-left-brace-by=
#endkeyvals

#keyvals:\WithArrowsOptions,\WithArrowsNewStyle
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

\WithArrowsNewStyle{style name%specialDef}{options%keyvals}#s#%witharrowsstyle

#ifOption:footnote
#include:footnote
#endif

#ifOption:footnotehyper
#include:footnotehyper
#endif

\WithArrowsNbLines#*

\WithArrows#S
\endWithArrows#S
\DispWithArrows#S
\endDispWithArrows#S
\myfileversion#S
\myfiledate#S
