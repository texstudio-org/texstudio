# ligtype package
# Matthew Bertucci 2022/06/12 for v0.1a

#include:ifluatex
#include:luatexbase

#keyvals:\usepackage/ligtype#c
noshortf
allshortf
makemarks
kerntest
nodefault
#endkeyvals

\nolig{string}{string with |}
\keeplig{string}{string with |}
\ligtypeon
\ligtypeoff