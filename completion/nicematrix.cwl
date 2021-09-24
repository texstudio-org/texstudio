# nicematrix package
# Matthew Bertucci 9/15/2021 for v6.2

#include:amsmath
#include:array
#include:l3keys2e
#include:pgfcore
#include:xparse

\NiceMatrixOptions{keyvals}

\begin{NiceTabular}{preamble}#\tabular
\begin{NiceTabular}[options%keyvals]{preamble}#\tabular
\begin{NiceTabular}[options%keyvals]{preamble}[options%keyvals]#S\tabular
\end{NiceTabular}
\begin{NiceTabular*}{preamble}#\tabular
\begin{NiceTabular*}[options%keyvals]{preamble}#\tabular
\begin{NiceTabular*}[options%keyvals]{preamble}[options%keyvals]#S\tabular
\end{NiceTabular*}
\begin{NiceTabularX}{width}{preamble}#\tabular
\begin{NiceTabularX}{width}[options%keyvals]{preamble}#\tabular
\begin{NiceTabularX}{width}[options%keyvals]{preamble}[options%keyvals]#S\tabular
\end{NiceTabularX}
\begin{NiceArray}{preamble}#m\array
\begin{NiceArray}[options%keyvals]{preamble}#m\array
\begin{NiceArray}[options%keyvals]{preamble}[options%keyvals]#Sm\array
\end{NiceArray}#m
\begin{pNiceArray}{preamble}#m\array
\begin{pNiceArray}[options%keyvals]{preamble}#m\array
\begin{pNiceArray}[options%keyvals]{preamble}[options%keyvals]#Sm\array
\end{pNiceArray}#m
\begin{bNiceArray}{preamble}#m\array
\begin{bNiceArray}[options%keyvals]{preamble}#m\array
\begin{bNiceArray}[options%keyvals]{preamble}[options%keyvals]#Sm\array
\end{bNiceArray}#m
\begin{BNiceArray}{preamble}#m\array
\begin{BNiceArray}[options%keyvals]{preamble}#m\array
\begin{BNiceArray}[options%keyvals]{preamble}[options%keyvals]#Sm\array
\end{BNiceArray}#m
\begin{vNiceArray}{preamble}#m\array
\begin{vNiceArray}[options%keyvals]{preamble}#m\array
\begin{vNiceArray}[options%keyvals]{preamble}[options%keyvals]#Sm\array
\end{vNiceArray}#m
\begin{VNiceArray}{preamble}#m\array
\begin{VNiceArray}[options%keyvals]{preamble}#m\array
\begin{VNiceArray}[options%keyvals]{preamble}[options%keyvals]#Sm\array
\end{VNiceArray}#m
\begin{NiceMatrix}#m\array
\begin{NiceMatrix}[options%keyvals]#m\array
\end{NiceMatrix}#m
\begin{pNiceMatrix}#m\array
\begin{pNiceMatrix}[options%keyvals]#m\array
\end{pNiceMatrix}#m
\begin{bNiceMatrix}#m\array
\begin{bNiceMatrix}[options%keyvals]#m\array
\end{bNiceMatrix}#m
\begin{BNiceMatrix}#m\array
\begin{BNiceMatrix}[options%keyvals]#m\array
\end{BNiceMatrix}#m
\begin{vNiceMatrix}#m\array
\begin{vNiceMatrix}[options%keyvals]#m\array
\end{vNiceMatrix}#m
\begin{VNiceMatrix}#m\array
\begin{VNiceMatrix}[options%keyvals]#m\array
\end{VNiceMatrix}#m

#keyvals:\NiceMatrixOptions,\begin{NiceTabular},\begin{NiceTabular*},\begin{NiceTabularX},\begin{NiceArray},\begin{pNiceArray},\begin{bNiceArray},\begin{BNiceArray},\begin{vNiceArray},\begin{VNiceArray},\begin{NiceMatrix},\begin{pNiceMatrix},\begin{bNiceMatrix},\begin{BNiceMatrix},\begin{vNiceMatrix},\begin{VNiceMatrix},\begin{NiceArrayWithDelims}
t
b
c
baseline=
standard-cline
vlines
vlines=
hlines
hlines=
hvlines
hvlines-except-borders
corners
corners=#NW,SW,NE,SE
code-before=
columns-width=
first-row
last-row
first-col
last-col
last-row=
last-col=
code-for-first-row=%<code%>
code-for-last-row=%<code%>
code-for-first-col=%<code%>
code-for-last-col=%<code%>
nullify-dots
renew-dots
xdots/color=#%color
xdots/shorten=##L
xdots/line-style=#standard,solid,dotted,densely dotted,loosely dotted,dashed,densely dashed,loosely dashed
code-after=
cell-space-top-limit=##L
cell-space-bottom-limit=##L
cell-space-limits=##L
tabularnote=
notes/para
notes/bottomrule
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
delimiters/max-width
vlines-in-sub-matrix=
colortbl-like
#endkeyvals

#keyvals:\begin{NiceTabular}
width=##L
#endkeyvals

#keyvals:\begin{NiceMatrix},\begin{pNiceMatrix},\begin{bNiceMatrix},\begin{BNiceMatrix},\begin{vNiceMatrix},\begin{VNiceMatrix}
l
r
#endkeyvals

#keyvals:\NiceMatrixOptions
notes={%<specs%>}
notes/style=
notes/label-in-tabular=
notes/label-in-list=
notes/enumitem-keys={%<enumitem keys%>}
notes/enumitem-keys-para={%<enumitem keys%>}
notes/code-before=%<code%>
letter-for-dotted-lines=
renew-matrix
exterior-arraycolsep
#endkeyvals

\Block{i-j}{content}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\Block[options%keyvals]{i-j}<code>{content}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims

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

\Hline#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims

\diagbox{lower}{upper}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims

\hdottedline#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\hdashline#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims

\CodeBefore#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\CodeBefore[options%keyvals]#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims

#keyvals:\CodeBefore
create-cell-nodes
#endkeyvals

\Body#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\cellcolor{color}{i-j,k-l,...}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\cellcolor[color_model]{color}{i-j,k-l,...}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\rectanglecolor{color}{i-j}{k-l}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\rectanglecolor[color_model]{color}{i-j}{k-l}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\arraycolor{color}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\arraycolor[color_model]{color}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\chessboardcolors{color1}{color2}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\chessboardcolors[color_model]{color1}{color2}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\rowcolor{color}{i,j-k,l-,...}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\rowcolor[color_model]{color}{i,j-k,l-,...}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\columncolor{color}{i,j-k,l-,...}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\columncolor[color_model]{color}{i,j-k,l-,...}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims

\rowcolors{row}{color1}{color2}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\rowcolors[color_model]{row}{color1}{color2}[options%keyvals]#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims

#keyvals:\rowcolors
cols=
restart
respect-blocks
#endkeyvals

\rowlistcolors{row}{color1,color2,...}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\rowlistcolors[color_model]{row}{color1,color2,...}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims

\RowStyle{code}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\RowStyle[options%keyvals]{code}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims

#keyvals:\RowStyle
cell-space-top-limit=##L
cell-space-bottom-limit=##L
cell-space-limits=##L
color=#%color
#endkeyvals

\begin{NiceMatrixBlock}
\begin{NiceMatrixBlock}[options%keyvals]
\end{NiceMatrixBlock}

#keyvals:\begin{NiceMatrixBlock}
auto-columns-width
#endkeyvals

\Ldots#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\Ldots[options%keyvals]#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\Cdots#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\Cdots[options%keyvals]#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\Vdots#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\Vdots[options%keyvals]#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\Ddots#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\Ddots[options%keyvals]#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\Iddots#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\Iddots[options%keyvals]#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\iddots#m
\line[options%keyvals]{i-j}{k-l}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims

#keyvals:\Ldots,\Cdots,\Vdots,\Ddots,\Iddots,\line
color=#%color
shorten=##L
line-style=#standard,solid,dotted,densely dotted,loosely dotted,dashed,densely dashed,loosely dashed
#endkeyvals

#keyvals:\Ddots,\Iddots
draw-first
#endkeyvals

\Hspace{length}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\Hspace*{length}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims

\Hdotsfor{number}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\Vdotsfor{number}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims

\CodeAfter#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\CodeAfter[options%keyvals]#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims

#keyvals:\CodeAfter,\NiceMatrixOptions,\begin{NiceTabular},\begin{NiceTabular*},\begin{NiceTabularX},\begin{NiceArray},\begin{pNiceArray},\begin{bNiceArray},\begin{BNiceArray},\begin{vNiceArray},\begin{VNiceArray},\begin{NiceMatrix},\begin{pNiceMatrix},\begin{bNiceMatrix},\begin{BNiceMatrix},\begin{vNiceMatrix},\begin{VNiceMatrix},\begin{NiceArrayWithDelims}
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
rules/width=##L
rules/color=#%color
#endkeyvals

\SubMatrix{delim1}{i-j}{k-l}{delim2}#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
\SubMatrix{delim1}{i-j}{k-l}{delim2}[options%keyvals]#/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims

#keyvals:\SubMatrix
left-xshift=##L
right-xshift=##L
xshift=##L
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

\tabularnote{note}
\rotate

\AutoNiceMatrix{i-j}{pattern}#m
\AutoNiceMatrix[options%keyvals]{i-j}{pattern}#m
\pAutoNiceMatrix{i-j}{pattern}#m
\pAutoNiceMatrix[options%keyvals]{i-j}{pattern}#m
\bAutoNiceMatrix{i-j}{pattern}#m
\bAutoNiceMatrix[options%keyvals]{i-j}{pattern}#m
\BAutoNiceMatrix{i-j}{pattern}#m
\BAutoNiceMatrix[options%keyvals]{i-j}{pattern}#m
\vAutoNiceMatrix{i-j}{pattern}#m
\vAutoNiceMatrix[options%keyvals]{i-j}{pattern}#m
\VAutoNiceMatrix{i-j}{pattern}#m
\VAutoNiceMatrix[options%keyvals]{i-j}{pattern}#m

#keyvals:\AutoNiceMatrix,\pAutoNiceMatrix,\bAutoNiceMatrix,\BAutoNiceMatrix,\vAutoNiceMatrix,\VAutoNiceMatrix
l
r
c
t
b
baseline=
standard-cline
vlines
vlines=
hlines
hlines=
hvlines
hvlines-except-borders
corners
corners=#NW,SW,NE,SE
code-before=%<code%>
columns-width=##L
first-row
last-row
first-col
last-col
last-row=
last-col=
code-for-first-row=%<code%>
code-for-last-row=%<code%>
code-for-first-col=%<code%>
code-for-last-col=%<code%>
nullify-dots
renew-dots
code-after=%<code%>
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
margin=
extra-left-margin=##L
extra-right-margin=##L
extra-margin=##L
parallelize-diags#true,false
delimiters/max-width
vlines-in-sub-matrix=
colortbl-like
#endkeyvals

\begin{NiceArrayWithDelims}{delim1}{delim2}{preamble}#*m\array
\begin{NiceArrayWithDelims}{delim1}{delim2}{preamble}[options%keyvals]#*m\array
\end{NiceArrayWithDelims}#*

\NiceMatrixLastEnv#*
\OnlyMainNiceMatrix{code}#*
\NotEmpty#*/NiceTabular,NiceTabular*,NiceTabularX,NiceArray,pNiceArray,bNiceArray,BNiceArray,vNiceArray,VNiceArray,NiceMatrix,pNiceMatrix,bNiceMatrix,BNiceMatrix,vNiceMatrix,VNiceMatrix,NiceArrayWithDelims
