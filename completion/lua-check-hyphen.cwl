# lua-check-hyphen package
# Matthew Bertucci 11/26/2021 for v0.7a

#include:ifluatex
#include:luatexbase
#include:keyval

\LuaCheckHyphen{options%keyvals}

#keyvals:\LuaCheckHyphen,\usepackage/lua-check-hyphen
compact#true,false
mark#true,false
nofile#true,false
final#true,false
whitelist={%<files%>}
#endkeyvals

\luachekchyphendothings#S
\luachekchyphenpkgdate#S
\luachekchyphenversion#S