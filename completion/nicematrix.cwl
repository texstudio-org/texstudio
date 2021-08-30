# nicematrix package
# Matthew Bertucci 8/29/2021, v6.1

#include:amsmath
#include:array
#include:l3keys2e
#include:pgfcore
#include:xparse

\NiceMatrixOptions{keyvals}

\begin{NiceTabular}[options%keyvals]{preamble}#\tabular
\begin{NiceTabular}[options%keyvals]{preamble}[options%keyvals]#S\tabular
\end{NiceTabular}
\begin{NiceTabular*}[options%keyvals]{preamble}#\tabular
\begin{NiceTabular*}[options%keyvals]{preamble}[options%keyvals]#S\tabular
\end{NiceTabular*}
\begin{NiceTabularX}{width}[options%keyvals]{preamble}#\tabular
\begin{NiceTabularX}{width}[options%keyvals]{preamble}[keyvals]#S\tabular
\end{NiceTabularX}
\begin{NiceArray}[options%keyvals]{preamble}#m\array
\begin{NiceArray}[options%keyvals]{preamble}[options%keyvals]#S\array
\end{NiceArray}
\begin{pNiceArray}[options%keyvals]{preamble}#m\array
\begin{pNiceArray}[options%keyvals]{preamble}[options%keyvals]#S\array
\end{pNiceArray}
\begin{bNiceArray}[options%keyvals]{preamble}#m\array
\begin{bNiceArray}[options%keyvals]{preamble}[options%keyvals]#S\array
\end{bNiceArray}
\begin{BNiceArray}[options%keyvals]{preamble}#m\array
\begin{BNiceArray}[options%keyvals]{preamble}[options%keyvals]#S\array
\end{BNiceArray}
\begin{vNiceArray}[options%keyvals]{preamble}#m\array
\begin{vNiceArray}[options%keyvals]{preamble}[options%keyvals]#S\array
\end{vNiceArray}
\begin{VNiceArray}[options%keyvals]{preamble}#m\array
\begin{VNiceArray}[options%keyvals]{preamble}[options%keyvals]#S\array
\end{VNiceArray}
\begin{NiceMatrix}[options%keyvals]#m\array
\end{NiceMatrix}
\begin{pNiceMatrix}[options%keyvals]#m\array
\end{pNiceMatrix}
\begin{bNiceMatrix}[options%keyvals]#m\array
\end{bNiceMatrix}
\begin{BNiceMatrix}[options%keyvals]#m\array
\end{BNiceMatrix}
\begin{vNiceMatrix}[options%keyvals]#m\array
\end{vNiceMatrix}
\begin{VNiceMatrix}[options%keyvals]#m\array
\end{VNiceMatrix}

\Block[options%keyvals]{i-j}<code>{arg}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims

\Hline#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims

\diagbox{arg1}{arg2}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims

\hdottedline#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\hdashline#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims

\CodeBefore[keyvals]#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\Body#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\cellcolor[opt_color_model]{color}{i-j,k-l,...}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\rectanglecolor[opt_color_model]{color}{i-j}{k-l}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\arraycolor[opt_color_model]{color}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\chessboardcolors[opt_color_model]{color1}{color2}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\rowcolor[opt_color_model]{color}{i,j-k,l-,...}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\columncolor[opt_color_model]{color}{i,j-k,l-,...}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\rowcolors[opt_color_model]{row}{color1}{color2}[keyvals]#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\rowlistcolors[opt_color_model]{row}{color1,color2,...}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\RowStyle[options%keyvals]{formatting}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims

\begin{NiceMatrixBlock}[options%keyvals]
\end{NiceMatrixBlock}

\Ldots[keyvals]#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\Cdots[keyvals]#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\Vdots[keyvals]#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\Ddots[keyvals]#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\Iddots[keyvals]#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\iddots#m

\Hspace{length}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\Hspace*{length}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims

\Hdotsfor{number}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\Vdotsfor{number}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims

\CodeAfter[keyvals]#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\line[options%keyvals]{i-j}{k-l}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\SubMatrix%<delim1%>{i-j}{k-l}%<delim2%>[keyvals]#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims

\tabularnote{note}

\rotate#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims

\AutoNiceMatrix[options%keyvals]{i-j}{pattern}#m
\pAutoNiceMatrix[options%keyvals]{i-j}{pattern}#m
\bAutoNiceMatrix[options%keyvals]{i-j}{pattern}#m
\BAutoNiceMatrix[options%keyvals]{i-j}{pattern}#m
\vAutoNiceMatrix[options%keyvals]{i-j}{pattern}#m
\VAutoNiceMatrix[options%keyvals]{i-j}{pattern}#m

\begin{NiceArrayWithDelims}{delim1}{delim2}{preamble}[options%keyvals]#m\array
\end{NiceArrayWithDelims}

\NiceMatrixLastEnv#*
\OnlyMainNiceMatrix{arg}#*

\NotEmpty#*/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims

#keyvals:\begin{NiceTabular},\begin{NiceTabular*},\begin{NiceTabularX},\begin{NiceArray},\begin{pNiceArray},\begin{bNiceArray},\begin{BNiceArray},\begin{vNiceArray},\begin{VNiceArray},\begin{NiceMatrix},\begin{pNiceMatrix},\begin{bNiceMatrix},\begin{BNiceMatrix},\begin{vNiceMatrix},\begin{VNiceMatrix},\begin{NiceArrayWithDelims}
t
b
c
baseline
standard-cline
rules/width=##L
rules/color=#%color
vlines
vlines=
hlines
hlines=
hvlines
hvlines-except-borders
corners
corners=#NW,SW,NE,SE
letter-for-dotted-lines
code-before=
columns-width=
first-row
last-row
first-col
last-col
last-row=
last-col=
code-for-first-row=
code-for-last-row=
code-for-first-col=
code-for-last-col=
nullify-dots
renew-dots
renew-matrix
xdots/color=#%color
xdots/shorten=##L
xdots/line-style=#standard,solid,dotted,densely dotted,loosely dotted,dashed,densely dashed,loosely dashed
code-after=
delimiters/color=#%color
tabularnote=
notes/para
notes/bottomrule
notes/style=
notes/label-in-tabular=
notes/label-in-list=
notes/enumitem-keys=
notes/enumitem-keys-para=
notes/code-before=
notes=
small
light-syntax
name=
create-medium-nodes
create-large-nodes
create-extra-nodes
left-margin
left-margin=##L
right-margin
right-margin=##L
margin=##L
extra-left-margin=##L
extra-right-margin=##L
extra-margin=##L
parallelize-diags#true,false
exterior-arraycolsep
letter-for-dotted-lines=
delimiters/max-width
colortbl-like
#endkeyvals

#keyvals:\begin{NiceTabular}
width=##L
#endkeyvals

#keyvals:\Block
l
c
r
fill=#%color
draw
draw=#%color
color=#%color
line-width=##L
rounded-corners=##L
borders=#left,right,top,bottom
hvlines
t
b
L
R
C
tikz=
#endkeyvals

#keyvals:\CodeBefore
create-cell-nodes
#endkeyvals

#keyvals:\rowcolors
cols=
restart
respect-blocks
#endkeyvals

#keyvals:\RowStyle
cell-space-top-limit=##L
cell-space-bottom-limit=##L
cell-space-limits=##L
color=#%color
#endkeyvals

#keyvals:\begin{NiceMatrixBlock}
auto-columns-width
#endkeyvals

#keyvals:\Ldots,\Cdots,\Vdots,\Ddots,\Iddots,\line
color=#%color
shorten=##L
line-style=#standard,solid,dotted,densely dotted,loosely dotted,dashed,densely dashed,loosely dashed
#endkeyvals

#keyvals:\Ddots
draw-first
#endkeyvals

#keyvals:\CodeAfter
delimiters/color=#%color
sub-matrix/left-xshift=##L
sub-matrix/right-xshift=##L
sub-matrix/extra-height=##L
sub-matrix/slim
sub-matrix/vlines
sub-matrix/vlines=
sub-matrix/hlines
sub-matrix/hlines=
sub-matrix/hvlines
#endkeyvals

#keyvals:\SubMatrix
left-xshift=##L
right-xshift=##L
extra-height=##L
delimiters/color=#%color
slim
vlines
vlines=
hlines
hlines=
hvlines
name=
#endkeyvals

#keyvals:\AutoNiceMatrix,\pAutoNiceMatrix,\bAutoNiceMatrix,\BAutoNiceMatrix,\vAutoNiceMatrix,\VAutoNiceMatrix
l
r
c
#endkeyvals
