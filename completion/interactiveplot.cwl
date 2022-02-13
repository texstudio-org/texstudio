# interactiveplot package
# Matthew Bertucci 2/12/2022 for v1.2

#include:datetime
#include:xstring
#include:stack
#include:ifthen
#include:forloop
#include:calc
#include:etoolbox

\begin{iplotdd}
\begin{iplotdd}[options%keyvals]
\end{iplotdd}
\begin{iplotddd}
\begin{iplotddd}[options%keyvals]
\end{iplotddd}

#keyvals:\begin{iplotdd},\begin{iplotddd}
width=%<number%>
height=%<number%>
#endkeyvals

\iplot{function%definition}
\iplot[options%keyvals]{function%definition}

#keyvals:\iplot
var={%<name,start,end%>}
param={%<name,value,step,start,end%>}
frange={%<name,start,end%>}
color=#black,white,red,green,blue,cyan,magenta,yellow,dark-gray,gray,light-gray
resolution=%<resolution%>
#endkeyvals

\Special{arg1}[arg2]#S
\border#S
\decimalaux#S
\resolution#S
\simbolaction#S
\theauxverifunari#S
\thect#S
\thelen#S
\val#S
\validateS{arg1}[arg2]#S