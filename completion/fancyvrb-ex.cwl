# fancyvrb-ex package
# Matthew Bertucci 9/27/2021 for v0.01

#include:fancyvrb
#include:xcolor
#include:hbaw

#ifOption:pstricks
#include:pstricks
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

#keyvals:\begin{Example},\begin{CenterExample},\begin{SideBySideExample}
commentchar=%<character%>
gobble=%<integer%>
formatcom=%<command%>
fontfamily=
fontsize=
fontshape=
fontseries=
frame=#none,leftline,topline,botomline,lines,single
framerule=##L
framesep=##L
rulecolor=#%color
fillcolor=#%color
label=
labelposition=#none,topline,bottomline,all
numbers=#none,left,right
numbersep=##L
firstnumber=#auto,last,integer
stepnumber=%<integer%>
numberblanklines#true,false
firstline=%<integer%>
lastline=%<integer%>
showspaces#true,false
showtabs#true,false
obeytabs#true,false
tabsize=%<integer%>
baselinestretch=
commandchars=
xleftmargin=##L
xrightmargin=##L
resetmargins#true,false
hfuzz=##L
samepage#true,false
codes=
defineactive=
reflabel=##l
#endkeyvals