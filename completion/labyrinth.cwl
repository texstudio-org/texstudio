# labyrinth package
# Matthew Bertucci 2/4/2022 for v1.0

#include:calc
#include:xkeyval
#include:picture

\begin{labyrinth}{width%plain}{height%plain}#\picture
\begin{labyrinth}[options%keyvals]{width%plain}{height%plain}#\picture
\end{labyrinth}
\h#*

\labyrinthset{options%keyvals}

#keyvals:\begin{labyrinth},\labyrinthset
unit=##L
thickness=##L
centered#true,false
#endkeyvals

\putsymbol(x,y){symbol}#/picture
\plus#*
\minus#*
\ast#*

\labyrinthsolution(x,y){solution code}#/picture
\labyrinthsolution[options%keyvals](x,y){solution code}#/picture
\solutionset{options%keyvals}
\autosolution(x1,y1)(x2,y2){first direction}#/picture
\autosolution[options%keyvals](x1,y1)(x2,y2){first direction}#/picture
\solutionpath#*

#keyvals:\labyrinthsolution,\solutionset,\autosolution
hidden#true,false
thicklines#true,false
up=%<symbol%>
left=%<symbol%>
down=%<symbol%>
right=%<symbol%>
hcorr=##L
vcorr=##L
font=%<font commands%>
#endkeyvals

\truncdiv{num1}{num2}#*