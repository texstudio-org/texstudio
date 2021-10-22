# Package empheq
# http://www.ctan.org/tex-archive/macros/latex/contrib/mh
# By astroscion: 2012-03-10
# updated Matthew Bertucci 10/20/2021 for v2.16

#include:mathtools

\begin{empheq}{AMS env name}#\math,array
\begin{empheq}[markup instructions%keyvals]{AMS env name}#\math,array
\end{empheq}
\empheqset{markup instructions%keyvals}

#keyvals:\begin{empheq},\empheqset
box=%<box cmd%>
innerbox=%<box cmd%>
left=%<math%>
right=%<math%>
outerbox=%<box cmd%>
marginbox=%<box cmd%>
#endkeyvals

\empheqlbrace#m
\empheqrbrace#m
\empheqbiglbrace#m
\empheqbigrbrace#m
\empheqlbrack#m
\empheqrbrack#m
\empheqbiglbrack#m
\empheqbigrbrack#m
\empheqlangle#m
\empheqrangle#m
\empheqbiglangle#m
\empheqbigrangle#m
\empheqlparen#m
\empheqrparen#m
\empheqbiglparen#m
\empheqbigrparen#m
\empheqlvert#m
\empheqrvert#m
\empheqbiglvert#m
\empheqbigrvert#m
\empheqlVert#m
\empheqrVert#m
\empheqbiglVert#m
\empheqbigrVert#m
\empheqlfloor#m
\empheqrfloor#m
\empheqbiglfloor#m
\empheqbigrfloor#m
\empheqlceil#m
\empheqrceil#m
\empheqbiglceil#m
\empheqbigrceil#m

#ifOption:oldmultline
\begin{MTmultlined}#m
\begin{MTmultlined}[pos][width]#m
\end{MTmultlined}#m
#endif

#ifOption:overload
\begin{align}[markup instructions%keyvals]#\math,array
\begin{align*}[markup instructions%keyvals]#\math,array
\begin{alignat}{ncols}[markup instructions%keyvals]#\math,array
\begin{alignat*}{ncols}[markup instructions%keyvals]#\math,array
\begin{equation}[markup instructions%keyvals]#\math
\begin{equation*}[markup instructions%keyvals]#\math
\begin{flalign}[markup instructions%keyvals]#\math,array
\begin{flalign*}[markup instructions%keyvals]#\math,array
\begin{gather}[markup instructions%keyvals]#\math
\begin{gather*}[markup instructions%keyvals]#\math
\begin{multline}[markup instructions%keyvals]#\math
\begin{multline*}[markup instructions%keyvals]#\math
#keyvals:\begin{align},\begin{align*},\begin{alignat}{ncols},\begin{alignat*}{ncols},\begin{equation},\begin{equation*},\begin{flalign},\begin{flalign*},\begin{gather},\begin{gather*},\begin{multline},\begin{multline*}
box=%<box cmd%>
innerbox=%<box cmd%>
left=%<math%>
right=%<math%>
outerbox=%<box cmd%>
marginbox=%<box cmd%>
#endkeyvals
\begin{AmSalign}#*\math,array
\begin{AmSalign*}#*\math,array
\begin{AmSalignat}{ncols}#*\math,array
\begin{AmSalignat*}{ncols}#*\math,array
\begin{AmSequation}#*\math
\begin{AmSequation*}#*\math
\begin{AmSflalign}#*\math,array
\begin{AmSflalign*}#*\math,array
\begin{AmSgather}#*\math
\begin{AmSgather*}#*\math
\begin{AmSmultline}#*\math
\begin{AmSmultline*}#*\math
\end{AmSalign}#*
\end{AmSalign*}#*
\end{AmSalignat}#*
\end{AmSalignat*}#*
\end{AmSflalign}#*
\end{AmSflalign*}#*
\end{AmSgather}#*
\end{AmSgather*}#*
\end{AmSmultline}#*
\end{AmSmultline*}#*
#endif

#ifOption:overload2
\begin{align}[markup instructions%keyvals]#\math,array
\begin{align*}[markup instructions%keyvals]#\math,array
\begin{alignat}{ncols}[markup instructions%keyvals]#\math,array
\begin{alignat*}{ncols}[markup instructions%keyvals]#\math,array
\begin{equation}[markup instructions%keyvals]#\math
\begin{equation*}[markup instructions%keyvals]#\math
\begin{flalign}[markup instructions%keyvals]#\math,array
\begin{flalign*}[markup instructions%keyvals]#\math,array
\begin{gather}[markup instructions%keyvals]#\math
\begin{gather*}[markup instructions%keyvals]#\math
\begin{multline}[markup instructions%keyvals]#\math
\begin{multline*}[markup instructions%keyvals]#\math
#keyvals:\begin{align},\begin{align*},\begin{alignat}{ncols},\begin{alignat*}{ncols},\begin{equation},\begin{equation*},\begin{flalign},\begin{flalign*},\begin{gather},\begin{gather*},\begin{multline},\begin{multline*}
box=%<box cmd%>
innerbox=%<box cmd%>
left=%<math%>
right=%<math%>
outerbox=%<box cmd%>
marginbox=%<box cmd%>
#endkeyvals
\begin{AmSalign}#*\math,array
\begin{AmSalign*}#*\math,array
\begin{AmSalignat}{ncols}#*\math,array
\begin{AmSalignat*}{ncols}#*\math,array
\begin{AmSequation}#*\math
\begin{AmSequation*}#*\math
\begin{AmSflalign}#*\math,array
\begin{AmSflalign*}#*\math,array
\begin{AmSgather}#*\math
\begin{AmSgather*}#*\math
\begin{AmSmultline}#*\math
\begin{AmSmultline*}#*\math
\end{AmSalign}#*
\end{AmSalign*}#*
\end{AmSalignat}#*
\end{AmSalignat*}#*
\end{AmSflalign}#*
\end{AmSflalign*}#*
\end{AmSgather}#*
\end{AmSgather*}#*
\end{AmSmultline}#*
\end{AmSmultline*}#*
#endif

\shadowbox*{arg}#*
\mintagvsep#*
\DeclareLeftDelimiter{delimiter}#*
\DeclareLeftDelimiter[space adjustment]{delimiter}#*
\DeclareRightDelimiter{delimiter}#*
\DeclareRightDelimiter[space adjustment]{delimiter}#*
\EmphEqdelimitershortfall#*
\EmphEqdelimiterfactor#*
\EmphEqdisplayheight#*
\EmphEqdisplaydepth#*
\EmphEqMainEnv#*
\endEmphEqMainEnv#*
