# penlightplus package
# Matthew Bertucci 2023/08/22

#include:luacode
#include:luakeys
#include:penlight

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

# not documented
\writePDFmetadata#S
\writePDFmetadatakv{arg}#S
\writePDFmetadatakv*{arg}#S