# numerica-tables package
# Matthew Bertucci 12/14/2021 for v2.0.0

#include:numerica
#include:booktabs

\tabulate[settings%keyvals]{expression}[vv-list%formula]
\tabulate[settings%keyvals]{expression}[vv-list%formula][num format]
\tabulate*[settings%keyvals]{expression}[vv-list%formula]
\tabulate*[settings%keyvals]{expression}[vv-list%formula][num format]
\nmcTabulate[settings%keyvals]{expression}[vv-list%formula]#*
\nmcTabulate[settings%keyvals]{expression}[vv-list%formula][num format]#*
\nmcTabulate*[settings%keyvals]{expression}[vv-list%formula]#*
\nmcTabulate*[settings%keyvals]{expression}[vv-list%formula][num format]#*

#keyvals:\tabulate,\tabulate*,\nmcTabulate,\nmcTabulate*
dbg=%<integer%>
view
reuse=%<integer%>
^=%<char%>
xx=#0,1
()=#0,1,2
o
log=%<number%>
vvmode=#0,1
vv@=#0,1
vvi=%<specification%>
vvd=%<specification%>
*
p
p=%<chars%>
S+=%<integer%>
S?=%<integer%>
P+=%<integer%>
P?=%<integer%>
rvar=%<tokens%>
rstep=%<real number%>
rstop=%<real number%>
rows=%<integer%>
rspec={%<csv list%>}
rround=%<integer%>
ralign=#r,c,l
rfont=#bf,it,sf,tt,frak,rm
rhead=%<tokens%>
rhnudge=%<integer%>
rpos=#0,1,2,3,4
rvar'=%<tokens%>
rhead'=%<tokens%>
rhnudge'=%<integer%>
cvar=%<tokens%>
cstep=%<real number%>
cstop=%<real number%>
cols=%<integer%>
cspec={%<csv list%>}
chstyle=#0,1,2,3,4
ctitle=%<tokens%>
chead=%<tokens%>
calign=#r,c,l
chnudge=%<integer%>
chround=%<integer%>
cmidrow=%<tokens%>
rules=%<chars%>
foot=%<tokens%>
rbloc={%<csv list%>}
rblocsep=##L
(pad)=%<integer%>
signs=#-2,-1,0,1,2
diffs=%<integer%>
Q?=%<tokens%>
A!=%<tokens%>
valign=#t,m,b
multifn
multifn=%<char%>
#endkeyvals