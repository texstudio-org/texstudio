# grundgesetze package
# Matthew Bertucci 10/8/2021 for v1.03

#include:kvoptions

#ifOption:bguq
#include:bguq
#endif

\GGhorizontal
\GGnot
\GGconditional{arg1%formula}{arg2%formula}
\GGquant{arg%formula}
\GGjudge
\GGdef
\GGbracket{arg%formula}
\GGsqbracket{arg%formula}
\GGterm{arg%formula}
\GGjudgelong
\GGjudgevar{length}
\GGdeflong
\GGdefvar{length}
\GGnotalone
\GGdnot
\GGall{arg%formula}
\GGnoboth
\GGnonotalone
\GGnodnot
\GGnoquant
\GGnonot

### Synonyms ###
\GGcontent#*
\GGassert#*
\GGjudgealone#*
\GGassertlong#*
\GGassertalone#*
\GGassertvar{length}#*
\GGdefalone#*
\GGneg#*
\GGoddspace#*
\GGtinyspace#*
\GGtiniestspace#*

### Lengths ###
\GGthickness#*
\GGquantthickness#*
\beforelen#*
\GGafterlen#*
\GGspace#*
\GGlift#*
\GGlinewidth#*