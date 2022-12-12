# clickable pgfplotslibrary
# 2022/12/11 for v1.18.1

#include:insdljs
#include:eforms

#keyvals:\begin{axis}#c,\begin{loglogaxis}#c,\begin{semilogxaxis}#c,\begin{semilogyaxis}#c,\addplot#c,\addplot3#c,\addplot+#c,\pgfplotsset#c,\begin{groupplot}#c,\nextgroupplot#c,\begin{smithchart}#c,\begin{polaraxis}#c,\begin{ternaryaxis}#c
clickable coords={%<displayed text%>}
clickable coords code={%<TeX code%>}
clickable coords size=%<max chars%>
clickable#true,false
annot/js fillColor=%<JavaScript color%>
annot/point format={%<sprintf-format%>}
annot/point format 3d={%<sprintf-format%>}
annot/slope format={%<sprintf-format%>}
annot/printable#true,false
annot/font=%<JavaScript font name%>
annot/textSize=%<size in pts%>
annot/popup size generic=%<number%>
annot/popup size snap=%<number%>
annot/popup size=%<number%>
annot/snap dist=%<size in pts%>
annot/richtext#true,false
#endkeyvals

\pgfplotsclickablecreate[keyvals]

#keyvals:\pgfplotsclickablecreate#c
js fillColor=%<JavaScript color%>
point format={%<sprintf-format%>}
point format 3d={%<sprintf-format%>}
slope format={%<sprintf-format%>}
printable#true,false
font=%<JavaScript font name%>
textSize=%<size in pts%>
popup size generic=%<number%>
popup size snap=%<number%>
popup size=%<number%>
snap dist=%<size in pts%>
richtext#true,false
width=##L
height=##L
jsname=%<string%>
xmin=%<number%>
xmax=%<number%>
ymin=%<number%>
ymax=%<number%>
collected plots
#endkeyvals

# not documented
\pgfplotscatcodeDQ#S