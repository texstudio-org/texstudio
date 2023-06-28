# optidef package
# Matthew Bertucci 12/16/2021 for v3.1

#include:calc
#include:environ
#include:etoolbox
#include:mathtools
#include:xifthen

#keyvals:\usepackage/optidef#c
short
long
nocomma
c1
c2
c3
#endkeyvals

\begin{mini}{variable}{function}{label code}{result}#\math
\begin{mini}[constraint format%keyvals]{variable}{function}{label code}{result}#*\math
\begin{mini}|%<l or s%>|[%<constraint format%>]<%<break%>>{%<variable%>}{%<function%>}{%<label code%>}{%<result%>}#\math
\end{mini}
\begin{mini*}{variable}{function}{label code}{result}#\math
\begin{mini*}[constraint format%keyvals]{variable}{function}{label code}{result}#*\math
\begin{mini*}|%<l or s%>|[%<constraint format%>]<%<break%>>{%<variable%>}{%<function%>}{%<label code%>}{%<result%>}#\math
\end{mini*}
\begin{mini!}{variable}{function}{label code}{result}#\math
\begin{mini!}[constraint format%keyvals]{variable}{function}{label code}{result}#*\math
\begin{mini!}|%<l or s%>|[%<constraint format%>]<%<break%>>{%<variable%>}{%<function%>}{%<label code%>}{%<result%>}#\math
\end{mini!}
\begin{minie}{variable}{function}{label code}{result}#*\math
\begin{minie}[constraint format%keyvals]{variable}{function}{label code}{result}#*\math
\begin{minie}|%<l or s%>|[%<constraint format%>]<%<break%>>{%<variable%>}{%<function%>}{%<label code%>}{%<result%>}#*\math
\end{minie}#*

\begin{maxi}{variable}{function}{label code}{result}#\math
\begin{maxi}[constraint format%keyvals]{variable}{function}{label code}{result}#*\math
\begin{maxi}|%<l or s%>|[%<constraint format%>]<%<break%>>{%<variable%>}{%<function%>}{%<label code%>}{%<result%>}#\math
\end{maxi}
\begin{maxi*}{variable}{function}{label code}{result}#\math
\begin{maxi*}[constraint format%keyvals]{variable}{function}{label code}{result}#*\math
\begin{maxi*}|%<l or s%>|[%<constraint format%>]<%<break%>>{%<variable%>}{%<function%>}{%<label code%>}{%<result%>}#\math
\end{maxi*}
\begin{maxi!}{variable}{function}{label code}{result}#\math
\begin{maxi!}[constraint format%keyvals]{variable}{function}{label code}{result}#*\math
\begin{maxi!}|%<l or s%>|[%<constraint format%>]<%<break%>>{%<variable%>}{%<function%>}{%<label code%>}{%<result%>}#\math
\end{maxi!}
\begin{maxie}{variable}{function}{label code}{result}#*\math
\begin{maxie}[constraint format%keyvals]{variable}{function}{label code}{result}#*\math
\begin{maxie}|%<l or s%>|[%<constraint format%>]<%<break%>>{%<variable%>}{%<function%>}{%<label code%>}{%<result%>}#*\math
\end{maxie}#*

\begin{argmini}{variable}{function}{label code}{result}#\math
\begin{argmini}[constraint format%keyvals]{variable}{function}{label code}{result}#*\math
\begin{argmini}|%<l or s%>|[%<constraint format%>]<%<break%>>{%<variable%>}{%<function%>}{%<label code%>}{%<result%>}#\math
\end{argmini}
\begin{argmini*}{variable}{function}{label code}{result}#\math
\begin{argmini*}[constraint format%keyvals]{variable}{function}{label code}{result}#*\math
\begin{argmini*}|%<l or s%>|[%<constraint format%>]<%<break%>>{%<variable%>}{%<function%>}{%<label code%>}{%<result%>}#\math
\end{argmini*}
\begin{argmini!}{variable}{function}{label code}{result}#\math
\begin{argmini!}[constraint format%keyvals]{variable}{function}{label code}{result}#*\math
\begin{argmini!}|%<l or s%>|[%<constraint format%>]<%<break%>>{%<variable%>}{%<function%>}{%<label code%>}{%<result%>}#\math
\end{argmini!}
\begin{argminie}{variable}{function}{label code}{result}#\math
\begin{argminie}[constraint format%keyvals]{variable}{function}{label code}{result}#*\math
\begin{argminie}|%<l or s%>|[%<constraint format%>]<%<break%>>{%<variable%>}{%<function%>}{%<label code%>}{%<result%>}#\math
\end{argminie}#*

\begin{argmaxi}{variable}{function}{label code}{result}#\math
\begin{argmaxi}[constraint format%keyvals]{variable}{function}{label code}{result}#*\math
\begin{argmaxi}|%<l or s%>|[%<constraint format%>]<%<break%>>{%<variable%>}{%<function%>}{%<label code%>}{%<result%>}#\math
\end{argmaxi}
\begin{argmaxi*}{variable}{function}{label code}{result}#\math
\begin{argmaxi*}[constraint format%keyvals]{variable}{function}{label code}{result}#*\math
\begin{argmaxi*}|%<l or s%>|[%<constraint format%>]<%<break%>>{%<variable%>}{%<function%>}{%<label code%>}{%<result%>}#\math
\end{argmaxi*}
\begin{argmaxi!}{variable}{function}{label code}{result}#\math
\begin{argmaxi!}[constraint format%keyvals]{variable}{function}{label code}{result}#*\math
\begin{argmaxi!}|%<l or s%>|[%<constraint format%>]<%<break%>>{%<variable%>}{%<function%>}{%<label code%>}{%<result%>}#\math
\end{argmaxi!}
\begin{argmaxie}{variable}{function}{label code}{result}#*\math
\begin{argmaxie}[constraint format%keyvals]{variable}{function}{label code}{result}#*\math
\begin{argmaxie}|%<l or s%>|[%<constraint format%>]<%<break%>>{%<variable%>}{%<function%>}{%<label code%>}{%<result%>}#*\math
\end{argmaxie}#*

#keyvals:\begin{mini}#c,\begin{mini*}#c,\begin{mini!}#c,\begin{maxi}#c,\begin{maxi*}#c,\begin{maxi!}#c
0
1
2
3
#endkeyvals

\addConstraint{left}
\addConstraint{left}{right}
\addConstraint{left}{right}{extra}
\labelOP{label}#l
\breakObjective{argument}

\defaultConstraintFormat#*
\defaultOCPConstraint#*
\defaultProblemFormat#*
\equalsNothing{string}{true}{false}#*
\spanit#*
\bodySubjectTo#*
\BelowAddConstraint{left}{right}{extra}#*
\BelowAddConstraintMult{left}{right}{extra}#*
\oneAlignAddConstraint{left}{right}{extra}#*
\oneAlignBelowAddConstraint{left}{right}{extra}#*
\oneAlignBelowAddConstraintMult{left}{right}{extra}#*
\standardAddConstraint{left}{right}{extra}#*
\selectConstraint{constraint format%keyvals}#*
\selectConstraintMult{constraint format%keyvals}#*
\setStandardMini#*
\setFormatShort{problem type}{arg}#*
\setFormatLong{problem type}{arg}#*
\localProblemFormat#*
\localOptimalVariable#*
\localProblemType#*
\bodyBreakObjectiveDefinition#*
\bodyBreakObjective#*
\begin{BaseMini}#S\math
\end{BaseMini}#S
\BaseMini#S
\endBaseMini#S
\begin{BaseMiniStar}#S\math
\end{BaseMiniStar}#S
\BaseMiniStar#S
\endBaseMiniStar#S
\begin{BaseMiniExclam}#S\math
\end{BaseMiniExclam}#S
\BaseMiniExclam#S
\endBaseMiniExclam#S
\widthInit#*
\bodyobjLong{arg1}{arg2}{arg3}{arg4}#*
\bodyobjShort{arg1}{arg2}{arg3}{arg4}#*
\bodyobj{arg1}{arg2}{arg3}{arg4}#*
\bodyconstBelowMult{arg1}{arg2}#*
\bodyconstBelow{arg1}{arg2}#*
\bodyconstOneAlignBelowMult{arg1}{arg2}#*
\bodyconstOneAlignBelow{arg1}{arg2}#*
\bodyconstOneAlign{arg1}{arg2}#*
\bodyconstRight{arg1}{arg2}#*
\bodyconst{arg1}{arg2}#*
\bodySubjectToDefinition#*