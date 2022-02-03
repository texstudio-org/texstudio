# regstats package
# Matthew Bertucci 2/2/2022 for v1.0h

#include:kvoptions
#include:atveryend
#include:ltxcmds

#keyvals:\usepackage/regstats#c
proof#true,false
left#true,false
timer#true,false
#endkeyvals

#ifOption:timer
#include:intcalc
#include:ifluatex
#include:ifpdf
#endif
#ifOption:timer=true
#include:intcalc
#include:ifluatex
#include:ifpdf
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