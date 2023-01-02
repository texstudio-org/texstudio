# luaset package
# Matthew Bertucci 2022/12/28 for v1.0

#include:xkeyval
#include:amsmath
#include:luacode
#include:luamaths

\luaSetNew{name}{set}
\luaSetPrint{name}
\luaSetUnion{name}{name1}{name2}
\luaSetIntersection{name}{name1}{name2}
\luaSetDifference{name}{name1}{name2}
\luaSetCardinal{name}
\luaSetBelongsto{element}{set}
\luaSetSubseteq{name1}{name2}
\luaSetSubset{name1}{name2}
\luaSetEqual{name1}{name2}