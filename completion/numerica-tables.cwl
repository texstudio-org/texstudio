# numerica-tables package
# Matthew Bertucci 2023/09/06 for v3.1.0

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
# table settings
rvar=%<tokens%>
rstep=%<real number%>
rstop=%<real number%>
rows=%<integer%>
rspec={%<csv list%>}
rdata={%<csv list%>}
rfile=%<file%>
rverb=#0,1
rfunc=%<function%>
rround=%<integer%>
ralign=#r,c,l
rfont=#bf,it,sf,tt,frak,rm
rhead=%<tokens%>
rhnudge=%<integer%>
rpos=#0,1,2,3,4
rvar'=%<tokens%>
rhead'=%<tokens%>
rhnudge'=%<integer%>
rfrac=#0,1,2,3,4,5
cvar=%<tokens%>
cstep=%<real number%>
cstop=%<real number%>
cols=%<integer%>
cspec={%<csv list%>}
chstyle=#0,1,2,3,4
ctitle=%<tokens%>
csubttl=%<tokens%>
chead=%<tokens%>
calign=#r,c,l
chnudge=%<integer%>
chround=%<integer%>
headless=#0,1
rules=%<chars%>
foot=%<tokens%>
rbloc={%<csv list%>}
rblocsep=##L
(pad)=%<integer%>
signs=#-2,-1,0,1,2
diffs=%<integer%>
round=%<function%>
Q?=%<tokens%>
A!=%<tokens%>
valign=#t,m,b
#endkeyvals
