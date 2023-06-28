# numerica package
# Matthew Bertucci 12/14/2021 for v2.0.0

#include:l3keys2e
#include:amsmath
#include:mathtools

\eval{expression}
\eval[settings%keyvals]{expression}
\eval{expression}[vv-list%formula]
\eval[settings%keyvals]{expression}[vv-list%formula]#*
\eval{expression}[vv-list%formula][num format]#*
\eval[settings%keyvals]{expression}[vv-list%formula][num format]#*
\eval*{expression}
\eval*[settings%keyvals]{expression}
\eval*{expression}[vv-list%formula]
\eval*[settings%keyvals]{expression}[vv-list%formula]#*
\eval*{expression}[vv-list%formula][num format]#*
\eval*[settings%keyvals]{expression}[vv-list%formula][num format]#*
\nmcEvaluate{expression}#*
\nmcEvaluate[settings%keyvals]{expression}#*
\nmcEvaluate{expression}[vv-list%formula]#*
\nmcEvaluate[settings%keyvals]{expression}[vv-list%formula]#*
\nmcEvaluate{expression}[vv-list%formula][num format]#*
\nmcEvaluate[settings%keyvals]{expression}[vv-list%formula][num format]#*
\nmcEvaluate*{expression}#*
\nmcEvaluate*[settings%keyvals]{expression}#*
\nmcEvaluate*{expression}[vv-list%formula]#*
\nmcEvaluate*[settings%keyvals]{expression}[vv-list%formula]#*
\nmcEvaluate*{expression}[vv-list%formula][num format]#*
\nmcEvaluate*[settings%keyvals]{expression}[vv-list%formula][num format]#*

#keyvals:\eval,\eval*,\nmcEvaluate,\nmcEvaluate*,\macros,\macros*,\nmcMacros,\nmcMacros*,\constants,\constants*,\nmcConstants,\nmcConstants*,\reuse,\reuse*,\nmcReuse,\nmcReuse*
dbg=%<integer%>
view
reuse=#0,1
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

\info{type}
\info[settings%keyvals]{type}
\info*{type}
\info*[settings%keyvals]{type}
\nmcInfo{type}#*
\nmcInfo[settings%keyvals]{type}#*
\nmcInfo*{type}#*
\nmcInfo*[settings%keyvals]{type}#*

#keyvals:\info#c,\info*#c,\nmcInfo#c,\nmcInfo*#c
view
#endkeyvals

\macros{command list}
\macros[settings%keyvals]{command list}
\macros{command list}[vv-list%formula]
\macros[settings%keyvals]{command list}[vv-list%formula]#*
\macros*{command list}
\macros*[settings%keyvals]{command list}
\macros*{command list}[vv-list%formula]
\macros*[settings%keyvals]{command list}[vv-list%formula]#*
\nmcMacros{command list}
\nmcMacros[settings%keyvals]{command list}
\nmcMacros{command list}[vv-list%formula]
\nmcMacros[settings%keyvals]{command list}[vv-list%formula]#*
\nmcMacros*{command list}
\nmcMacros*[settings%keyvals]{command list}
\nmcMacros*{command list}[vv-list%formula]
\nmcMacros*[settings%keyvals]{command list}[vv-list%formula]#*

#keyvals:\macros,\macros*,\nmcMacros,\nmcMacros*
free
#endkeyvals

\constants{name1=val1,name2=val2,...%formula}
\constants[settings%keyvals]{name1=val1,name2=val2,...%formula}
\constants{name1=val1,name2=val2,...%formula}[vv-list%formula]
\constants[settings%keyvals]{name1=val1,name2=val2,...%formula}[vv-list%formula]#*
\nmcConstants{name1=val1,name2=val2,...%formula}#*
\nmcConstants[settings%keyvals]{name1=val1,name2=val2,...%formula}#*
\nmcConstants{name1=val1,name2=val2,...%formula}[vv-list%formula]#*
\nmcConstants[settings%keyvals]{name1=val1,name2=val2,...%formula}[vv-list%formula]#*

#keyvals:\constants,\constants*,\nmcConstants,\nmcConstants*
add
#endkeyvals

\reuse{csname}
\reuse[settings%keyvals]{csname}
\reuse*{csname}
\reuse*[settings%keyvals]{csname}
\nmcReuse{csname}#*
\nmcReuse[settings%keyvals]{csname}#*
\nmcReuse*{csname}#*
\nmcReuse*[settings%keyvals]{csname}#*

#keyvals:\reuse,\reuse*,\nmcReuse,\nmcReuse*
delete
renew
#endkeyvals
