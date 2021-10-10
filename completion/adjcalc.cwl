# adjcalc package
# Matthew Bertucci 10/5/2021 for v1.1

#ifOption:calc
#include:calc
#endif

#ifOption:pgfmath
#include:pgf
#endif

\adjcalcset{options%keyvals}

#keyvals:\adjcalcset
etex
calc
pgfmath
overwrite
defaultunit=%<unit%>
#endkeyvals

\adjsetlength{length macro}{length}
\adjaddtolength{length macro}{length}
\adjsetcounter{counter}{integer}
\adjaddtocounter{counter}{integer}
\adjsetlengthdefault{length macro}{length}