# lua-list-hyphen package
# Matthew Bertucci 2026/07/26 for v0.42.7

#include:luatex

#keyvals:\usepackage/lua-list-hyphen#c
output-prefix=%<prefix%>
output-extension=%<extension%>
division-dict-path=%<path%>
allowlist-path=%<path%>
validation-preprocessor={%<keyvals%>}
validation-case-sensitive#true,false
flag-mode=#none,all,non-valid
output-mode=#all,non-valid
output-non-typeset#true,false
output-header#true,false
output-verbose#true,false
context=%<integer%>
context-before=%<integer%>
context-after=%<integer%>
unique=#none,case,nocase
sort=#none,case,nocase
%<language%>={%<options%>}
#endkeyvals