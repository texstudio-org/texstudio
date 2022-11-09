# luacas package
# Matthew Bertucci 2022/11/06 for v1.0

#include:iftex
#include:luacode
#include:pgfkeys
#include:verbatim
#include:tikz
#include:xcolor
#include:mathtools

\begin{CAS}
\end{CAS}

\fetch{name}
\store{name}[alt-name]

\print{expr}
\print*{expr}
\vprint{expr}
\vprint*{expr}
\lprint{expr}
\lprint{expr}[low,upp]#*

\parseforest{expr}
\parseforest*{expr}
\forestresult
\parseshrub{expr}
\parseshrub*{expr}
\shrubresult

\whatis{expr}

# not in main documentation
\get{arg}#S
\get[opt]{arg}#S
\yoink{arg}#S
\yoink{arg}[opt]#S
\printshrub{expr}#*
\printshrub*{expr}#*
\printtree{expr}#*
\printtree*{expr}#*
\freeof{arg1}{arg2}#S
\freeof*{arg1}{arg2}#S
\isatomic{arg}#S
\isatomic*{arg}#S
\isconstant{arg}#S
\isconstant*{arg}#S