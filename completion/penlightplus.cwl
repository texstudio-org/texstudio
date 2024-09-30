# penlightplus package
# Matthew Bertucci 2024/09/30

#include:luacode
#include:luakeys
#include:penlight
#include:etoolbox
#include:tokcycle

#keyvals:\usepackage/penlightplus#c
globals
pl
#endkeyvals

\MakeluastringCommands{spec}
\MakeluastringCommands[def]{spec}
\splittocomma{text%plain}{text to split on}
\splittocomma[expansion level]{text%plain}{text to split on}
\splittoitems{text%plain}{text to split on}
\splittoitems[expansion level]{text%plain}{text to split on}
\luastringT{string}
\luastringF{string}
\ifluax{Lua expr%definition}{true}
\ifluax{Lua expr%definition}{true}[false]
\ifluaxv{Lua expr%definition}{true}
\ifluaxv{Lua expr%definition}{true}[false]
\tblnew{name}
\tblchg{name}
\tblfrkv{name}{key-val string}
\tblfrkv{name}{key-val string}[luakeys opts]
\tblfrkvN{name}{key-val string}
\tblfrkvN{name}{key-val string}[luakeys opts]
\tblfrkvCD{name}{key-val string}
\tblfrkvCD{name}{key-val string}[luakeys opts]
\tblfrkvNCD{name}{key-val string}
\tblfrkvNCD{name}{key-val string}[luakeys opts]
\tblfrcsv{name}{key-val string}
\tblfrcsv{name}{key-val string}[luakeys opts]
\tblset{index}{value}
\tblsetN{index}{value}
\tblget{index}
\tbldef{index}{csname}
\tbldefall{table}{csname}
\tblgdef{index}{csname}
\tbldefxy{index}{csname}
\tblif{index}{true}
\tblif{index}{true}[false]
\tblifv{index}{true}
\tblifv{index}{true}[false]
\tblkvundefcheck
\tblfrcsvN{name}{csv}
\tblapp{name}{value}
\tblappN{name}{value}
\tblcon{name}{csv}
\tblconN{name}{csv}
\tbladd{index}{value}
\tbladdN{index}{value}
\tblprt{name}
\caseswitch{case}{key-val choices}
\caseswitch*{case}{key-val choices}
\writePDFmetadatakv{keyvals}
\writePDFmetadatakv[expansion type]{keyvals}
\writePDFmetadatakv*{keyvals}
\writePDFmetadatakv*[expansion type]{keyvals}
\writePDFmetadata

# not documented
\tbladdo{arg1}{arg2}{arg3}#S
\tbladdNo{arg1}{arg2}{arg3}#S
