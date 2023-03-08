# nicematrix package
# Matthew Bertucci 2023/03/07 for v6.16

#include:amsmath
#include:array
#include:l3keys2e
#include:pgfcore
#include:xparse

#keyvals:\usepackage/nicematrix#c
renew-dots#true,false
renew-matrix#true,false
footnote#true,false
footnotehyper#true,false
no-test-for-array#true,false
#endkeyvals

#ifOption:footnote
#include:footnote
#endif
#ifOption:footnote=true
#include:footnote
#endif

#ifOption:footnotehyper
#include:footnotehyper
#endif
#ifOption:footnotehyper=true
#include:footnotehyper
#endif

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
baseline=%<row number%>
standard-cline
vlines
vlines=
hlines
hlines=
hvlines
hvlines-except-borders
corners
corners=#NW,SW,NE,SE
custom-line={%<keyvals%>}
code-before=%<code%>
columns-width=##L
first-row
last-row
first-col
last-col
last-row=%<number%>
last-col=%<number%>
code-for-first-row=%<code%>
code-for-last-row=%<code%>
code-for-first-col=%<code%>
code-for-last-col=%<code%>
nullify-dots
renew-dots
xdots/color=#%color
xdots/radius=##L
xdots/shorten-start=##L
xdots/shorten-end=##L
xdots/shorten=##L
xdots/inter=##L
xdots/line-style=#standard,solid,dotted,densely dotted,loosely dotted,dashed,densely dashed,loosely dashed
code-after=%<code%>
cell-space-top-limit=##L
cell-space-bottom-limit=##L
cell-space-limits=##L
tabularnote=%<text%>
notes/para
notes/bottomrule
small
light-syntax
name=%<name%>
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
vlines-in-sub-matrix=%<letter%>
colortbl-like
#endkeyvals

#keyvals:\NiceMatrixOptions,\begin{NiceTabular}
width=##L
#endkeyvals

#keyvals:\begin{NiceTabular},\begin{NiceTabular*},\begin{NiceTabularX}
caption=%<text%>
short-caption=%<text%>
label=##l
#endkeyvals

#keyvals:\begin{NiceMatrix},\begin{pNiceMatrix},\begin{bNiceMatrix},\begin{BNiceMatrix},\begin{vNiceMatrix},\begin{VNiceMatrix}
l
c
r
columns-type=#l,c,r
#endkeyvals

#keyvals:\NiceMatrixOptions
notes={%<specs%>}
notes/style=
notes/label-in-tabular=
notes/label-in-list=
notes/enumitem-keys={%<enumitem keys%>}
notes/enumitem-keys-para={%<enumitem keys%>}
matrix/columns-type=#l,c,r
notes/code-before=%<code%>
letter-for-dotted-lines=
renew-matrix
exterior-arraycolsep
caption-above
#endkeyvals

\Block{i-j}{content}#t
\Block{i-j}<code>{content}#t
\Block[options%keyvals]{i-j}{content}#t
\Block[options%keyvals]{i-j}<code>{content}#t

#keyvals:\Block
l
c
r
fill=#%color
draw
draw=#%color
color=#%color
line-width=##L
rounded-corners
rounded-corners=##L
borders={%<borders options%>}
hvlines
v-center
t
b
T
B
L
R
C
tikz={%<TikZ options%>}
name=%<name%>
respect-arraystretch
transparent
#endkeyvals

\Hline#t
\Hline[options%keyvals]#t

#keyvals:\Hline
command=%<csname%>
ccommand=%<csname%>
letter=%<letter%>
multiplicity=%<integer%>
color=#%color
sep-color=#%color
tikz={%<TikZ keys%>}
total-width=##L
dotted
#endkeyvals

\diagbox{lower}{upper}#t

\hdottedline#t
\cdottedline{linespec}#t

\CodeBefore#t
\CodeBefore[options%keyvals]#t

#keyvals:\CodeBefore
create-cell-nodes
#endkeyvals

\Body#t
\cellcolor{color}{i-j,k-l,...}#t
\cellcolor[color_model]{color}{i-j,k-l,...}#t
\rectanglecolor{color}{i-j}{k-l}#t
\rectanglecolor[color_model]{color}{i-j}{k-l}#t
\arraycolor{color}#t
\arraycolor[color_model]{color}#t
\chessboardcolors{color1}{color2}#t
\chessboardcolors[color_model]{color1}{color2}#t
\rowcolor{color}{i,j-k,l-,...}#t
\rowcolor[color_model]{color}{i,j-k,l-,...}#t
\columncolor{color}{i,j-k,l-,...}#t
\columncolor[color_model]{color}{i,j-k,l-,...}#t

\rowcolors{row}{color1}{color2}#t
\rowcolors[color model]{row}{color1}{color2}[options%keyvals]#t

#keyvals:\rowcolors
cols=
restart
respect-blocks
#endkeyvals

\rowlistcolors{row}{color1,color2,...}#t
\rowlistcolors[color model]{row}{color1,color2,...}#t

\RowStyle{code}#t
\RowStyle[options%keyvals]{code}#t

#keyvals:\RowStyle
nb-rows=%<number%>
cell-space-top-limit=##L
cell-space-bottom-limit=##L
cell-space-limits=##L
rowcolor=#%color
color=#%color
bold
#endkeyvals

\begin{NiceMatrixBlock}
\begin{NiceMatrixBlock}[options%keyvals]
\end{NiceMatrixBlock}

#keyvals:\begin{NiceMatrixBlock}
auto-columns-width
#endkeyvals

\Ldots#t
\Ldots[options%keyvals]#t
\Cdots#t
\Cdots[options%keyvals]#t
\Vdots#t
\Vdots[options%keyvals]#t
\Ddots#t
\Ddots[options%keyvals]#t
\Iddots#t
\Iddots[options%keyvals]#t
\iddots#m
\line[options%keyvals]{i-j}{k-l}#t

#keyvals:\Ldots,\Cdots,\Vdots,\Ddots,\Iddots,\line
color=#%color
radius=##L
shorten-start=##L
shorten-end=##L
shorten=##L
inter=##L
line-style=#standard,solid,dotted,densely dotted,loosely dotted,dashed,densely dashed,loosely dashed
#endkeyvals

#keyvals:\Ddots,\Iddots
draw-first
#endkeyvals

\Hspace{length}#t
\Hspace*{length}#t

\Hdotsfor{number}#t
\Vdotsfor{number}#t

\CodeAfter#t
\CodeAfter[options%keyvals]#t

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

\SubMatrix{delim1}{i-j}{k-l}{delim2}#t
\SubMatrix{delim1}{i-j}{k-l}{delim2}[options%keyvals]#t

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
name=%<name%>
code=%<code%>
#endkeyvals

\OverBrace{i-j}{k-l}{label}#t
\OverBrace[options%keyvals]{i-j}{k-l}{label}#t
\UnderBrace{i-j}{k-l}{label}#t
\UnderBrace[options%keyvals]{i-j}{k-l}{label}#t

#keyvals:\OverBrace,\UnderBrace
left-shorten
right-shorten
shorten
yshift=##L
color=#%color
#endkeyvals

\tabularnote{note%text}
\begin{TabularNote}
\end{TabularNote}
\rotate
\ShowCellNames#t

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
columns-type=#l,c,r
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
name=%<name%>
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
vlines-in-sub-matrix=%<letter%>
colortbl-like
#endkeyvals

\begin{NiceArrayWithDelims}{delim1}{delim2}{preamble}#*m\array
\begin{NiceArrayWithDelims}{delim1}{delim2}{preamble}[options%keyvals]#*m\array
\end{NiceArrayWithDelims}#*

\NiceMatrixLastEnv#*
\OnlyMainNiceMatrix{code}#*
\NotEmpty#*t

\myfileversion#S
\myfiledate#S
