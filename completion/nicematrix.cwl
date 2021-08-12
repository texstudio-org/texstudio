# nicematrix package
# Matthew Bertucci 8/12/2021, v6.0

#include:amsmath
#include:array
#include:l3keys2e
#include:pgfcore
#include:xparse

\NiceMatrixOptions{keyvals}

\begin{NiceTabular}[keyvals]{preamble}#\tabular
\begin{NiceTabular}[keyvals]{preamble}[keyvals]#S\tabular
\end{NiceTabular}
\begin{NiceTabular*}[keyvals]{preamble}#\tabular
\begin{NiceTabular*}[keyvals]{preamble}[keyvals]#S\tabular
\end{NiceTabular*}
\begin{NiceTabularX}{width}[keyvals]{preamble}#\tabular
\begin{NiceTabularX}{width}[keyvals]{preamble}[keyvals]#S\tabular
\end{NiceTabularX}
\begin{NiceArray}[keyvals]{preamble}#m\array
\begin{NiceArray}[keyvals]{preamble}[keyvals]#S\array
\end{NiceArray}
\begin{pNiceArray}[keyvals]{preamble}#m\array
\begin{pNiceArray}[keyvals]{preamble}[keyvals]#S\array
\end{pNiceArray}
\begin{bNiceArray}[keyvals]{preamble}#m\array
\begin{bNiceArray}[keyvals]{preamble}[keyvals]#S\array
\end{bNiceArray}
\begin{BNiceArray}[keyvals]{preamble}#m\array
\begin{BNiceArray}[keyvals]{preamble}[keyvals]#S\array
\end{BNiceArray}
\begin{vNiceArray}[keyvals]{preamble}#m\array
\begin{vNiceArray}[keyvals]{preamble}[keyvals]#S\array
\end{vNiceArray}
\begin{VNiceArray}[keyvals]{preamble}#m\array
\begin{VNiceArray}[keyvals]{preamble}[keyvals]#S\array
\end{VNiceArray}
\begin{NiceMatrix}[keyvals]#m\array
\end{NiceMatrix}
\begin{pNiceMatrix}[keyvals]#m\array
\end{pNiceMatrix}
\begin{bNiceMatrix}[keyvals]#m\array
\end{bNiceMatrix}
\begin{BNiceMatrix}[keyvals]#m\array
\end{BNiceMatrix}
\begin{vNiceMatrix}[keyvals]#m\array
\end{vNiceMatrix}
\begin{VNiceMatrix}[keyvals]#m\array
\end{VNiceMatrix}

\Block[keyvals]{i-j}<code>{arg}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims

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

\begin{NiceMatrixBlock}[keyvals]
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
\line[keyvals]{i-j}{k-l}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\SubMatrix%<delim1%>{i-j}{k-l}%<delim2%>[keyvals]#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims

\tabularnote{note}

\rotate#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims

\AutoNiceMatrix[keyvals]{i-j}{pattern}#m
\pAutoNiceMatrix[keyvals]{i-j}{pattern}#m
\bAutoNiceMatrix[keyvals]{i-j}{pattern}#m
\BAutoNiceMatrix[keyvals]{i-j}{pattern}#m
\vAutoNiceMatrix[keyvals]{i-j}{pattern}#m
\VAutoNiceMatrix[keyvals]{i-j}{pattern}#m

\begin{NiceArrayWithDelims}%<delim1%>%<delim2%>{preamble}[keyvals]#m
\end{NiceArrayWithDelims}

\NiceMatrixLastEnv

\OnlyMainNiceMatrix{arg}

\NotEmpty#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims

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
