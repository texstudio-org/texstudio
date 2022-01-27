# calculation package
# Matthew Bertucci 10/8/2021 for v1.0

#include:delarray

#keyvals:\usepackage/calculation#c
fleqn
leqno
block
#endkeyvals

\begin{calculation}#\math
\begin{calculation}[symbol]#\math
\end{calculation}
\begin{subcalculation}#\math
\begin{subcalculation}[symbol]#\math
\end{subcalculation}

\step{text}#m
\step*{text}#m
\step[symbol]{text}#m
\step*[symbol]{text}#m
\comment{text}#m
\doNumber#m

\stepsymbol#*
\Hblockopen#*
\Hblockclose#*
\Hlineopen#*
\Hlineclose#*
\Hindent#*
\Hsep#*
\calculcolsep#*
\Hposv#*
