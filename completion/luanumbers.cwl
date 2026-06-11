# luanumbers package
# Matthew Bertucci 2026/06/10 for v0.5.0

#include:iftex
#include:luatexbase

\begin{luanumbersexclude}
\end{luanumbersexclude}

\LuaNumbersOff
\LuaNumbersOn
\LuaNumbersProtectCommands{csname1,csname2,...}
\LuaNumbersProtectCommand{csname}
\LuaNumbersProtectEnvironments{envname1,envname2,...}
\LuaNumbersProtectEnvironment{envname}
\LuaNumbersSetup{options%keyvals}
\LuaNumbersUnprotectCommands{csname1,csname2,...}
\LuaNumbersUnprotectCommand{csname}
\LuaNumbersUnprotectEnvironments{envname1,envname2,...}
\LuaNumbersUnprotectEnvironment{envname}
\LuaNumber{number}

#keyvals:\LuaNumbersSetup
decimals=%<integer%>
rounding=#half-up,half-even,truncate,floor,ceil
pad-zeroes#true,false
integers#true,false
preserve-exponent#true,false
normalize-negative-zero#true,false
input-decimal=#dot,comma,both
auto-protect#true,false
warnings=#off,once,all,error
#endkeyvals