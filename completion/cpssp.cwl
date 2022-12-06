# cpssp package
# Matthew Bertucci 2/10/2022 for v1.0

#include:ifthen
#include:calc
#include:kvoptions
#include:tikz
#include:tikzlibrarypositioning
#include:tikzlibrarydecorations.pathmorphing

\cpsspformat{options%keyvals}
\cpsspinput{file}#i
\cpsspinput[options%keyvals]{file}#i
\begin{cpsspimage}{file}#i
\begin{cpsspimage}[options%keyvals]{file}#i
\end{cpsspimage}

#keyvals:\usepackage/cpssp#c,\cpsspformat,\cpsspinput,\begin{cpsspimage}
style=#small,large,graylines,pdb
labels#true,false
numbers#true,false
labelformat=%<font commands%>
numberformat=%<font commands%>
threehelixname=%<name%>
pihelixname=%<name%>
#endkeyvals

\cpsspGap{y}{x1}{x2}
\cpsspBridge{y}{x1}{x2}
\cpsspCoil{y}{x1}{x2}
\cpsspSheet{y}{x1}{x2}
\cpsspSheetT{y}{x1}{x2}
\cpsspThreeTenHelix{y}{x1}{x2}
\cpsspAlphaHelix{y}{x1}{x2}
\cpsspPiHelix{y}{x1}{x2}
\cpsspBend{y}{x1}{x2}
\cpsspTurn{y}{x1}{x2}

\cpsspLabel{y}{text}

\cpsspStartRes{y}{x}{text}
\cpsspEndRes{y}{x}{text}

CpsspColorX#B
CpsspColorB#B
CpsspColorC#B
CpsspColorE#B
CpsspColorG#B
CpsspColorH#B
CpsspColorI#B
CpsspColorS#B
CpsspColorT#B
CpsspColorPdbX#B
CpsspColorPdbB#B
CpsspColorPdbC#B
CpsspColorPdbE#B
CpsspColorPdbG#B
CpsspColorPdbH#B
CpsspColorPdbI#B
CpsspColorPdbS#B
CpsspColorPdbT#B
