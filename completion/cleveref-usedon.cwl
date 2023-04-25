# cleveref-usedon package
# Matthew Bertucci 2023/04/24 for v0.4.0

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

\cref[option%keyvals]{labellist}#r
\cref*[option%keyvals]{labellist}#r
\Cref[option%keyvals]{labellist}#r
\Cref*[option%keyvals]{labellist}#r

#keyvals:\cref#c,\cref*#c,\Cref#c,\Cref*#c
UsedOn
UsedBy
UsedByAndOn
#endkeyvals

\UsedByAndOnMessage{arg1}{arg2}#S
\UsedByMessage{arg}#S
\UsedOnMessage{arg}#S
\UsedOnPackageDate#S
\UsedOnPackageVersion#S
