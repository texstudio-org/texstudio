# numerica package
# Matthew Bertucci 2023/08/22 for v3.0.0

#include:amsmath
#include:mathtools

#keyvals:\usepackage/numerica#c
comma#true,false
rounding=%<integer%>
approx
#endkeyvals

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
\arsinh#*m
\arcosh#*m
\artanh#*m
\arcsch#*m
\arsech#*m
\arcoth#*m
\arcsinh#*m
\arccosh#*m
\arctanh#*m
\arccsch#*m
\arcsech#*m
\arccoth#*m
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
\comma#*
\equals#*
\degree#*
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
save
renew
load
delete
#endkeyvals
