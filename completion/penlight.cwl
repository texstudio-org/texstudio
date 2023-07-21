# penlight package
# Matthew Bertucci 2023/07/19 for v2023/07/18

#include:luacode

#keyvals:\usepackage/penlight#c
pl
penlight
stringx
format
func
extras
extrasnoglobals
#endkeyvals

\writePDFmetadata
\writePDFmetadatakv{keyvals}
\writePDFmetadatakv*{keyvals}

\luastringT{string}#S
\luastringF{string}#S
\MakeluastringCommands{spec}
\MakeluastringCommands[def]{spec}
\splitToComma{text}{text to split on%text}
\splitToComma[expansion level]{text}{text to split on%text}
\splitToItems{text}{text to split on%text}
\splitToItems[expansion level]{text}{text to split on%text}
