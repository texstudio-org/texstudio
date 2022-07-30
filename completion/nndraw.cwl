# nndraw package
# Matthew Bertucci 2022/07/30 for v1.0

#include:tikz

\begin{fullyconnectednn}#\pictureHighlight
\begin{fullyconnectednn}[options%keyvals]
\end{fullyconnectednn}

#keyvals:\begin{fullyconnectednn}#c
input=
output=
layersep=%<number%>
biasx=%<number%>
biasy=%<number%>
titley=%<number%>
inout#true,false
text width=##L
#endkeyvals

\nnlayer{number}
\nnlayer[options%keyvals]{number}

#keyvals:\nnlayer#c
title=%<text%>
text=%<text%>
hasbias#true,false
bias=
color=#%color
biascolor=#%color
#endkeyvals

\nnlayerNoText{arg}#*
\ifnnlayerHasBias#*
\nnlayerHasBiastrue#*
\nnlayerHasBiasfalse#*
\nnlayerTitle#*
\nnlayerText#*
\nnlayerBias#*
\nnlayerColor#*
\nnlayerBiasColor#*
\thenumlayers#*
\thenninputlayer#*
\thelastnnsize#*
\iffullyconnectednnInout#*
\fullyconnectednnInouttrue#*
\fullyconnectednnInoutfalse#*
\fullyconnectednnInput#*
\fullyconnectednnOutput#*
\fullyconnectednnLayersep#*
\fullyconnectednnBiasX#*
\fullyconnectednnBiasY#*
\fullyconnectednnTitleY#*
\fullyconnectednnTextWidth#*