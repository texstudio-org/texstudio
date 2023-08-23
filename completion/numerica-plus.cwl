# numerica-plus package
# Matthew Bertucci 2023/08/22 for v3.0.0

#include:numerica

\iter{expression}
\iter[settings%keyvals]{expression}
\iter{expression}[vv-list%formula]
\iter[settings%keyvals]{expression}[vv-list%formula]#*
\iter{expression}[vv-list%formula][num format]#*
\iter[settings%keyvals]{expression}[vv-list%formula][num format]#*
\iter*{expression}
\iter*[settings%keyvals]{expression}
\iter*{expression}[vv-list%formula]
\iter*[settings%keyvals]{expression}[vv-list%formula]#*
\iter*{expression}[vv-list%formula][num format]#*
\iter*[settings%keyvals]{expression}[vv-list%formula][num format]#*
\nmcIterate{expression}#*
\nmcIterate[settings%keyvals]{expression}#*
\nmcIterate{expression}[vv-list%formula]v
\nmcIterate[settings%keyvals]{expression}[vv-list%formula]#*
\nmcIterate{expression}[vv-list%formula][num format]#*
\nmcIterate[settings%keyvals]{expression}[vv-list%formula][num format]#*
\nmcIterate*{expression}#*
\nmcIterate*[settings%keyvals]{expression}#*
\nmcIterate*{expression}[vv-list%formula]#*
\nmcIterate*[settings%keyvals]{expression}[vv-list%formula]#*
\nmcIterate*{expression}[vv-list%formula][num format]#*
\nmcIterate*[settings%keyvals]{expression}[vv-list%formula][num format]#*

#keyvals:\iter,\iter*,\nmcIterate,\nmcIterate*,\solve,\solve*,\nmcSolve,\nmcSolve*,\recur,\recur*,\nmcRecur,\nmcRecur*
# functional settings
dbg=#0,1,2,3,5,7,11
view
^=%<char%>
xx=#0,1
ff=%<char%>
1s2=#0,1
/min=%<integer%>
/max=%<integer%>
vv@=#0,1
vvmode=#0,1
o=#0,1
log=%<number%>
S+=%<integer%>
S?=%<integer%>
P+=%<integer%>
P?=%<integer%>
# display settings
f=#0,1
p=%<punctuation%>
pp=%<punctuation%>
env=%<envname%>
arg=%<arg%>
eq=%<symbol%>
vv=%<spec%>
sep=%<separator%>
\}=%<<space><r-delim>%>
#endkeyvals

#keyvals:\iter,\iter*,\nmcIterate,\nmcIterate*
var=%<variable name%>
+=%<integer%>
max=%<integer%>
do=%<integer%>
see=%<integer%>
#endkeyvals

\solve{expression}
\solve[settings%keyvals]{expression}
\solve{expression}[vv-list%formula]
\solve[settings%keyvals]{expression}[vv-list%formula]#*
\solve{expression}[vv-list%formula][num format]#*
\solve[settings%keyvals]{expression}[vv-list%formula][num format]#*
\solve*{expression}
\solve*[settings%keyvals]{expression}
\solve*{expression}[vv-list%formula]
\solve*[settings%keyvals]{expression}[vv-list%formula]#*
\solve*{expression}[vv-list%formula][num format]#*
\solve*[settings%keyvals]{expression}[vv-list%formula][num format]#*
\nmcSolve{expression}#*
\nmcSolve[settings%keyvals]{expression}#*
\nmcSolve{expression}[vv-list%formula]#*
\nmcSolve[settings%keyvals]{expression}[vv-list%formula]#*
\nmcSolve{expression}[vv-list%formula][num format]#*
\nmcSolve[settings%keyvals]{expression}[vv-list%formula][num format]#*
\nmcSolve*{expression}#*
\nmcSolve*[settings%keyvals]{expression}#*
\nmcSolve*{expression}[vv-list%formula]#*
\nmcSolve*[settings%keyvals]{expression}[vv-list%formula]#*
\nmcSolve*{expression}[vv-list%formula][num format]#*
\nmcSolve*[settings%keyvals]{expression}[vv-list%formula][num format]#*

#keyvals:\solve,\solve*,\nmcSolve,\nmcSolve*
var=%<variable name%>
dvar=%<real number%>
+=%<integer%>
max=%<integer%>
#endkeyvals

\recur{expression}
\recur[settings%keyvals]{expression}
\recur{expression}[vv-list%formula]
\recur[settings%keyvals]{expression}[vv-list%formula]#*
\recur{expression}[vv-list%formula][num format]#*
\recur[settings%keyvals]{expression}[vv-list%formula][num format]#*
\recur*{expression}
\recur*[settings%keyvals]{expression}
\recur*{expression}[vv-list%formula]
\recur*[settings%keyvals]{expression}[vv-list%formula]#*
\recur*{expression}[vv-list%formula][num format]#*
\recur*[settings%keyvals]{expression}[vv-list%formula][num format]#*
\nmcRecur{expression}#*
\nmcRecur[settings%keyvals]{expression}#*
\nmcRecur{expression}[vv-list%formula]#*
\nmcRecur[settings%keyvals]{expression}[vv-list%formula]#*
\nmcRecur{expression}[vv-list%formula][num format]#*
\nmcRecur[settings%keyvals]{expression}[vv-list%formula][num format]#*
\nmcRecur*{expression}#*
\nmcRecur*[settings%keyvals]{expression}#*
\nmcRecur*{expression}[vv-list%formula]#*
\nmcRecur*[settings%keyvals]{expression}[vv-list%formula]#*
\nmcRecur*{expression}[vv-list%formula][num format]#*
\nmcRecur*[settings%keyvals]{expression}[vv-list%formula][num format]#*

#keyvals:\recur,\recur*,\nmcRecur,\nmcRecur*
do=%<integer%>
see1=%<integer%>
see2=%<integer%>
...
#endkeyvals

\clitem%<\macro <number>%>
