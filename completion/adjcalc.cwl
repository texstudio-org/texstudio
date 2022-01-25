# adjcalc package
# Matthew Bertucci 10/5/2021 for v1.1

#ifOption:calc
#include:calc
#endif

#ifOption:pgfmath
#include:pgf
#endif

\adjcalcset{options%keyvals}

#keyvals:\adjcalcset,\usepackage/adjcalc#c
etex
calc
pgfmath
overwrite
defaultunit=%<unit%>
#endkeyvals

#keyvals:\usepackage/adjcalc#c
none
#endkeyvals

\adjsetlength{length macro}{length}
\adjaddtolength{length macro}{length}
\adjsetcounter{counter}{integer}
\adjaddtocounter{counter}{integer}
\adjsetlengthdefault{length macro}{length}
