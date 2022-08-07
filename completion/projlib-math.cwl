# projlib-math package
# Matthew Bertucci 2022/08/06 for 2022/08/05 release

#include:mathtools
#include:mathrsfs
#include:amssymb

\DefineMathOperator{name}
\DefineMathOperator[style=%<code%>]{%<name%>}
\DefineMathOperator*{name}
\DefineMathOperator*[style=%<code%>]{%<name%>}
\DefineOperator{name}#*
\DefineOperator[style=%<code%>]{%<name%>}#*
\DefineOperator*{name}#*
\DefineOperator*[style=%<code%>]{%<name%>}#*
\ProjLibDefineMathOperator{name}#S
\ProjLibDefineMathOperator[style=%<code%>]{%<name%>}#S
\ProjLibDefineMathOperator*{name}#S
\ProjLibDefineMathOperator*[style=%<code%>]{%<name%>}#S

\DefineMathSymbol{name}
\DefineMathSymbol[%<options%>]{%<name%>}
\DefineMathSymbol*{name}
\DefineMathSymbol*[%<options%>]{%<name%>}
\DefineShortcut{name}#*
\DefineShortcut[%<options%>]{%<name%>}#*
\DefineShortcut*{name}#*
\DefineShortcut*[%<options%>]{%<name%>}#*
\ProjLibDefineMathSymbol{name}#S
\ProjLibDefineMathSymbol[%<options%>]{%<name%>}#S
\ProjLibDefineMathSymbol*{name}#S
\ProjLibDefineMathSymbol*[%<options%>]{%<name%>}#S

#keyvals:\DefineMathSymbol,\DefineMathSymbol*,\DefineShortcut,\DefineShortcut*,\ProjLibDefineMathSymbol,\ProjLibDefineMathSymbol*
prefix=
type=
style=
#endkeyvals

\RedefineInMathMode{cmd}{def}
\ProjLibRedefineInMathMode{cmd}{def}#S

\ListOfSymbols{keyvals}
\ListOfSymbols[colwidth1]{keyvals}#*
\ListOfSymbols[colwidth1][colwidth2]{keyvals}
\ProjLibListOfSymbols{keyvals}#S
\ProjLibListOfSymbols[colwidth1]{keyvals}#S
\ProjLibListOfSymbols[colwidth1][colwidth2]{keyvals}#S

\ProvideCommandCopy{cmd}{def}#*d
