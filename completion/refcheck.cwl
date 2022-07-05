# refcheck package
# Matthew Bertucci 2022/07/04 for v1.9.1

#keyvals:\usepackage/refcheck#c
showrefs
showcites
msgs
chckunlbld
norefs
nocites
nomsgs
ignoreunlbld
#endkeyvals

\showrefnames
\norefnames
\showcitenames
\nocitenames
\refcheckxrdoc{file}
\refcheckxrdoc[prefix]{file}
\setonmsgs
\setoffmsgs
\checkunlbld
\ignoreunlbld

# not documented
\cleanprefix{arg1}{arg2}#*
\usedref{arg}#*
\wrtusdrf{arg}#*
\btoks{arg}#S
\filedate#S
\filename#S
\fileversion#S