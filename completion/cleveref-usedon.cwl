# cleveref-usedon package
# Matthew Bertucci 2023/04/12 for v0.2.0

#include:cleveref

#keyvals:\usepackage/cleveref-usedon#c
# passes options to cleveref
poorman
sort
compress
sort&compress
nosort
capitalise
capitalize
nameinlink
noabbrev
english
german
ngerman
dutch
french
spanish
italian
russian
ukrainian
norsk
danish
esperanto
swedish
brazilian
catalan
#endkeyvals

\cref[UsedOn]{labellist}#r
\cref*[UsedOn]{labellist}#r
\Cref[UsedOn]{labellist}#r
\Cref*[UsedOn]{labellist}#r

\UsedOnMessage#*