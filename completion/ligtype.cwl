# ligtype package
# Matthew Bertucci 2023/07/10 for v0.3

#include:ifluatex
#include:luatexbase

#keyvals:\usepackage/ligtype#c
noshortf
allshortf
makemarks
kerntest
nodefault
liglist
connotes
#endkeyvals

\nolig{string}{string with |}
\keeplig{string}{string with |}
\ligtypeon
\ligtypeoff

# not documented
\noligs#S
\ligs#S
