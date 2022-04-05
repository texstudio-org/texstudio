# luakeys-debug package
# Matthew Bertucci 11/8/2021 for v0.5

#include:luatex

\LuaKeysIfNextChar%<<char>%>{%<true%>}{%<false%>}
\luakeysdebug{kv-string}
\luakeysdebug[options%keyvals]{kv-string}
#keyvals:\luakeysdebug#c
unpack single array values#true,false
convert dimensions#true,false
standalone as true#true,false
case insensitive keys#true,false
#endkeyvals
