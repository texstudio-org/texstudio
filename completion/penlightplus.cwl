# penlightplus package
# Matthew Bertucci 2023/08/28

#include:luacode
#include:luakeys
#include:penlight
#include:etoolbox

#keyvals:\usepackage/penlightplus#c
globals
pl
#endkeyvals

\MakeluastringCommands{spec}
\MakeluastringCommands[def]{spec}
\splitToComma{text%plain}{text to split on}
\splitToComma[expansion level]{text%plain}{text to split on}
\splitToItems{text%plain}{text to split on}
\splitToComma[expansion level]{text%plain}{text to split on}
\luastringT{string}
\luastringF{string}
\ifluax{Lua expr%definition}{true}
\ifluax{Lua expr%definition}{true}[false]
\ifluaxv{Lua expr%definition}{true}
\ifluaxv{Lua expr%definition}{true}[false]
\newtbl{name}
\chgtbl{name}
\tblfrkv{name}{key-val string}
\tblfrkv{name}{key-val string}[luakeys opts]
\settbl{index}{value}
\gettbl{index}
\deftbl{index}{csname}
\gdeftbl{index}{csname}
\iftbl{index}{true}
\iftbl{index}{true}[false]
\iftblv{index}{true}
\iftblv{index}{true}[false]

# not documented
\writePDFmetadata#S
\writePDFmetadatakv{arg}#S
\writePDFmetadatakv*{arg}#S
