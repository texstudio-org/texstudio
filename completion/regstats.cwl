# regstats package
# Matthew Bertucci 2023/04/07 for v1.1a

#include:kvoptions

#keyvals:\usepackage/regstats#c
left#true,false
timer#true,false
#endkeyvals

#ifOption:timer
#include:intcalc
#include:iftex
#endif
#ifOption:timer=true
#include:intcalc
#include:iftex
#endif

\regstatselapsedtime#*
\regstatsseconds#*
\theregstatscount#*
\regstatsdimen#*
\regstatsskip#*
\regstatsmuskip#*
\regstatsbox#*
\regstatstoks#*
\regstatsread#*
\regstatswrite#*
\regstatsfam#*
\regstatslanguage#*
\regstatsinsert#*
