# numerica package
# Matthew Bertucci 11/6/2021 for v1.0.0

#include:xparse
#include:l3keys2e
#include:amsmath
#include:mathtools

#ifOption:plus
\iter{expression}
\iter[settings%keyvals]{expression}
\iter{expression}[vv-list]
\iter[settings%keyvals]{expression}[vv-list]#*
\iter{expression}[vv-list][num format]#*
\iter[settings%keyvals]{expression}[vv-list][num format]#*
\iter*{expression}
\iter*[settings%keyvals]{expression}
\iter*{expression}[vv-list]
\iter*[settings%keyvals]{expression}[vv-list]#*
\iter*{expression}[vv-list][num format]#*
\iter*[settings%keyvals]{expression}[vv-list][num format]#*
\nmcIterate{expression}#*
\nmcIterate[settings%keyvals]{expression}#*
\nmcIterate{expression}[vv-list]v
\nmcIterate[settings%keyvals]{expression}[vv-list]#*
\nmcIterate{expression}[vv-list][num format]#*
\nmcIterate[settings%keyvals]{expression}[vv-list][num format]#*
\nmcIterate*{expression}#*
\nmcIterate*[settings%keyvals]{expression}#*
\nmcIterate*{expression}[vv-list]#*
\nmcIterate*[settings%keyvals]{expression}[vv-list]#*
\nmcIterate*{expression}[vv-list][num format]#*
\nmcIterate*[settings%keyvals]{expression}[vv-list][num format]#*

#keyvals:\iter,\iter*,\nmcIterate,\nmcIterate*
var=%<variable name%>
+=%<integer%>
max=%<integer%>
do=%<integer%>
see=%<integer%>
#endkeyvals

\solve{expression}
\solve[settings%keyvals]{expression}
\solve{expression}[vv-list]
\solve[settings%keyvals]{expression}[vv-list]#*
\solve{expression}[vv-list][num format]#*
\solve[settings%keyvals]{expression}[vv-list][num format]#*
\solve*{expression}
\solve*[settings%keyvals]{expression}
\solve*{expression}[vv-list]
\solve*[settings%keyvals]{expression}[vv-list]#*
\solve*{expression}[vv-list][num format]#*
\solve*[settings%keyvals]{expression}[vv-list][num format]#*
\nmcSolve{expression}#*
\nmcSolve[settings%keyvals]{expression}#*
\nmcSolve{expression}[vv-list]#*
\nmcSolve[settings%keyvals]{expression}[vv-list]#*
\nmcSolve{expression}[vv-list][num format]#*
\nmcSolve[settings%keyvals]{expression}[vv-list][num format]#*
\nmcSolve*{expression}#*
\nmcSolve*[settings%keyvals]{expression}#*
\nmcSolve*{expression}[vv-list]#*
\nmcSolve*[settings%keyvals]{expression}[vv-list]#*
\nmcSolve*{expression}[vv-list][num format]#*
\nmcSolve*[settings%keyvals]{expression}[vv-list][num format]#*

#keyvals:\solve,\solve*,\nmcSolve,\nmcSolve*
var=%<variable name%>
dvar=%<real number%>
+=%<integer%>
max=%<integer%>
#endkeyvals

\recur{expression}
\recur[settings%keyvals]{expression}
\recur{expression}[vv-list]
\recur[settings%keyvals]{expression}[vv-list]#*
\recur{expression}[vv-list][num format]#*
\recur[settings%keyvals]{expression}[vv-list][num format]#*
\recur*{expression}
\recur*[settings%keyvals]{expression}
\recur*{expression}[vv-list]
\recur*[settings%keyvals]{expression}[vv-list]#*
\recur*{expression}[vv-list][num format]#*
\recur*[settings%keyvals]{expression}[vv-list][num format]#*
\nmcRecur{expression}#*
\nmcRecur[settings%keyvals]{expression}#*
\nmcRecur{expression}[vv-list]#*
\nmcRecur[settings%keyvals]{expression}[vv-list]#*
\nmcRecur{expression}[vv-list][num format]#*
\nmcRecur[settings%keyvals]{expression}[vv-list][num format]#*
\nmcRecur*{expression}#*
\nmcRecur*[settings%keyvals]{expression}#*
\nmcRecur*{expression}[vv-list]#*
\nmcRecur*[settings%keyvals]{expression}[vv-list]#*
\nmcRecur*{expression}[vv-list][num format]#*
\nmcRecur*[settings%keyvals]{expression}[vv-list][num format]#*

#keyvals:\recur,\recur*,\nmcRecur,\nmcRecur*
do=%<integer%>
see1=%<integer%>
see2=%<integer%>
...
#endkeyvals
#endif

#ifOption:tables
#include:booktabs
\tabulate[settings%keyvals]{expression}[vv-list]
\tabulate[settings%keyvals]{expression}[vv-list][num format]
\tabulate*[settings%keyvals]{expression}[vv-list]
\tabulate*[settings%keyvals]{expression}[vv-list][num format]
\nmcTabulate[settings%keyvals]{expression}[vv-list]#*
\nmcTabulate[settings%keyvals]{expression}[vv-list][num format]#*
\nmcTabulate*[settings%keyvals]{expression}[vv-list]#*
\nmcTabulate*[settings%keyvals]{expression}[vv-list][num format]#*

#keyvals:\tabulate,\tabulate*,\nmcTabulate,\nmcTabulate*
rvar=%<tokens%>
rstep=%<real number%>
rstop=%<real number%>
rows=%<integer%>
rspec={%<csv list%>}
rround=%<integer%>
ralign=#r,c,l
rfont=%<chars%>
rhead=%<tokens%>
rhnudge=%<integer%>
rpos=%<integer%>
rvar'=%<tokens%>
rhead'=%<tokens%>
rhnudge'=%<integer%>
chstyle=%<integer%>
ctitle=%<tokens%>
chead=%<tokens%>
calign=#r,c,l
chnudge=%<integer%>
chround=%<integer%>
(pad)=%<integer%>
signs=%<integer%>
diffs=%<integer%>
Q?=%<tokens%>
A!=%<tokens%>
rules=%<chars%>
foot=%<tokens%>
rbloc={%<csv list%>}
rblocsep=##L
valign=#t,b
#endkeyvals
#endif

\eval{expression}
\eval[settings%keyvals]{expression}
\eval{expression}[vv-list]
\eval[settings%keyvals]{expression}[vv-list]#*
\eval{expression}[vv-list][num format]#*
\eval[settings%keyvals]{expression}[vv-list][num format]#*
\eval*{expression}
\eval*[settings%keyvals]{expression}
\eval*{expression}[vv-list]
\eval*[settings%keyvals]{expression}[vv-list]#*
\eval*{expression}[vv-list][num format]#*
\eval*[settings%keyvals]{expression}[vv-list][num format]#*

\nmcEvaluate{expression}#*
\nmcEvaluate[settings%keyvals]{expression}#*
\nmcEvaluate{expression}[vv-list]#*
\nmcEvaluate[settings%keyvals]{expression}[vv-list]#*
\nmcEvaluate{expression}[vv-list][num format]#*
\nmcEvaluate[settings%keyvals]{expression}[vv-list][num format]#*
\nmcEvaluate*{expression}#*
\nmcEvaluate*[settings%keyvals]{expression}#*
\nmcEvaluate*{expression}[vv-list]#*
\nmcEvaluate*[settings%keyvals]{expression}[vv-list]#*
\nmcEvaluate*{expression}[vv-list][num format]#*
\nmcEvaluate*[settings%keyvals]{expression}[vv-list][num format]#*

#keyvals:\eval,\eval*,\nmcEvaluate,\nmcEvaluate*,\iter,\iter*,\nmcIterate,\nmcIterate*,\solve,\solve*,\nmcSolve,\nmcSolve*,\recur,\recur*,\nmcRecur,\nmcRecur*,\tabulate,\tabulate*,\nmcTabulate,\nmcTabulate*
dbg=%<integer%>
reuse=%<integer%>
^=%<char%>
xx=%<integer%>
()=%<integer%>
o
log=%<number%>
vvmode=%<integer%>
vvi=%<specification%>
vvd=%<specification%>
*
p
p=%<chars%>
S+=%<integer%>
S?=%<integer%>
P+=%<integer%>
P?=%<integer%>
#endkeyvals

\csch#m
\sech#m
\arccsc#m
\arcsec#m
\arccot#m
\asinh#m
\acosh#m
\atanh#m
\acsch#m
\asech#m
\acoth#m
\lb#m
\sgn#m
\abs{arg}#m
\abs[opt]{arg}#*m
\abs*{arg}#m
\abs*[opt]{arg}#m
\floor{arg}#m
\floor[opt]{arg}#*m
\floor*{arg}#m
\floor*[opt]{arg}#m
\ceil{arg}#m
\ceil[opt]{arg}#*m
\ceil*{arg}#m
\ceil*[opt]{arg}#m

\q#m
\Q#m

\info{type%keyvals}
\info*{type%keyvals}
\nmcInfo{type%keyvals}#*
\nmcInfo*{type%keyvals}#*

#keyvals:\info,\nmcInfo
sum
prod
#endkeyvals

\reuse
\reuse[csname]
\reuse*
\reuse*[csname]
\nmcReuse#*
\nmcReuse[csname]#*
\nmcReuse*#*
\nmcReuse*[csname]#*