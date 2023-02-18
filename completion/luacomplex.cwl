# luacomplex package
# Matthew Bertucci 2023/02/14 for v1.2

#include:xkeyval
#include:amsmath
#include:luacode
#include:luamaths

\cpxNew{name}{x,y}
\cpxPrint{name}
\cpxAdd{name}{name1}{name2}
\cpxSub{name}{name1}{name2}
\cpxMul{name}{name1}{name2}
\cpxDiv{name}{name1}{name2}
\cpxInv{name}{orig-name}
\cpxRe{name}{orig-name}
\cpxIm{name}{orig-name}
\cpxMod{name}{orig-name}
\cpxPrinArg{name}{orig-name}
\cpxOp{name}{expression%definition}
\imgUnit
