# luavlna package
# Matthew Bertucci 1/21/2022 for v0.1i

#include:luatex
#include:kvoptions

#keyvals:\usepackage/luavlna#c
noinitials
nounits
nopredegrees
nosufdegrees
noprocess
debug
defaults#true,false
#endkeyvals

\nosingledefaults
\singlechars{language}{letters}
\compoundinitials{language}{compounds}
\enablesplithyphens{language}
\disablesplithyphens{language}

# from luavlna.tex
\singlecharsgetlang{language}#*
\preventsingledebugon
\preventsinglelang{language}
\preventsinglestatus#*
\preventsingleon
\preventsingleoff
\preventsingledebugoff
\nopredegrees
\nosufdegrees
\nounits
\noinitials