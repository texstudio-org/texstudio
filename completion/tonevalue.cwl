# tonevalue package
# Matthew Bertucci 1/25/2022 for v1.0

#include:contour
#include:etoolbox
#include:listofitems
#include:tikz
#include:tikzlibrarypositioning
#include:tikzlibrarydecorations.markings
#include:xcolor
#include:xkeyval
#include:xstring

#keyvals:\usepackage/tonevalue#c
fontcmd=%<font commands%>
draft
contourlength=##L
contournumber=%<integer%>
defaultcolors
#endkeyvals

#ifOption:defaultcolors
1#B
2#B
3#B
4#B
5#B
6#B
7#B
8#B
#endif

\begin{untVisualisation}#\pictureHighlight
\begin{untVisualisation}[options%keyvals]
\end{untVisualisation}

#keyvals:\begin{untVisualisation}#c
minmax={%<min,max%>}
scale=%<factor%>
showlabels#true,false
#endkeyvals

\untpoint{tone value}{tone name}
\untpoint[options%keyvals]{tone value}{tone name}

#keyvals:\untpoint#c
stem#true,false
label=#above,below,left,right,above left,above right,below left,below right
bgcolor=#%color
xshift=##L
yshift=##L
scale=%<factor%>
tikzoptions={%<TikZ options%>}
#endkeyvals

\linkuntpoints{{%<toneval1%>}{%<tonename1%>}}{{%<toneval2%>}{%<tonename2%>}}
\linkuntpoints[%<options%>]{{%<toneval1%>}{%<tonename1%>}}{{%<toneval2%>}{%<tonename2%>}}

#keyvals:\linkuntpoints#c
color=#%color
bend=#bend left,bend right
#endkeyvals

\drawuntpoint{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}{arg7}{arg8}#*
\drawuntpoint[opt]{arg1}{arg2}{arg3}{arg4}{arg5}{arg6}{arg7}{arg8}#*
\len#*
\sendiauToListStr{arg}#*
\sendiaulistStr#*
\sendiaulist#*
\thesumOfPitchHeights#*
\toneVisualisationFontCmd#*
\xend#*
\xjoinbycomma#*
\xstart#*
\yend#*
\ystart#*
