# fancyvrb-ex package
# Matthew Bertucci 9/27/2021 for v0.01

#include:fancyvrb
#include:xcolor
#include:hbaw

#keyvals:\usepackage/fancyvrb-ex#c
pstricks
color
#endkeyvals

#ifOption:pstricks
#include:pstricks
\showgrid
\begin{PCenterExample}(x1,y1)(x2,y2)#\pictureHighlight
\begin{PCenterExample}[options%keyvals](x1,y1)(x2,y2)
\end{PCenterExample}
\begin{PSideBySideExample}(x1,y1)(x2,y2)#\pictureHighlight
\begin{PSideBySideExample}[options%keyvals](x1,y1)(x2,y2)
\end{PSideBySideExample}
#endif

\begin{Example}#V
\begin{Example}[options%keyvals]#V
\end{Example}
\begin{CenterExample}#V
\begin{CenterExample}[options%keyvals]#V
\end{CenterExample}
\begin{SideBySideExample}#V
\begin{SideBySideExample}[options%keyvals]#V
\end{SideBySideExample}

#keyvals:\begin{Example},\begin{CenterExample},\begin{SideBySideExample},\begin{PCenterExample},\begin{PSideBySideExample}
commentchar=%<single char%>
gobble=%<integer%>
formatcom=%<commands%>
formatcom*=%<commands%>
fontfamily=%<family%>
fontsize=%<size macro%>
fontshape=%<shape%>
fontseries=%<series%>
frame=#none,leftline,topline,bottomline,lines,single
framerule=##L
framesep=##L
rulecolor=%<color cmd%>
fillcolor=%<color cmd%>
label=%<label text%>
labelposition=#none,topline,bottomline,all
numbers=#none,left,right
numbersep=##L
firstnumber=%<auto|last|<integer>%>
stepnumber=%<integer%>
numberblanklines#true,false
firstline=%<integer%>
lastline=%<integer%>
showspaces#true,false
showtabs#true,false
obeytabs#true,false
tabsize=%<integer%>
baselinestretch=%<factor%>
commandchars=%<three chars%>
xleftmargin=##L
xrightmargin=##L
resetmargins#true,false
hfuzz=##L
samepage#true,false
codes={%<code%>}
codes*={%<code%>}
defineactive={%<code%>}
defineactive*={%<code%>}
reflabel=##l
fileext=%<extension%>
vspace=##L
listparameters={%<code%>}
#endkeyvals

# only available if pstricks loaded
\showgrid#S
\begin{PCenterExample}(x1,y1)(x2,y2)#S\pictureHighlight
\begin{PCenterExample}[options%keyvals](x1,y1)(x2,y2)#S
\end{PCenterExample}#S
\begin{PSideBySideExample}(x1,y1)(x2,y2)#S\pictureHighlight
\begin{PSideBySideExample}[options%keyvals](x1,y1)(x2,y2)#S
\end{PSideBySideExample}#S
