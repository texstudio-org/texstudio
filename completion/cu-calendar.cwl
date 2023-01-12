# cu-calendar package
# Matthew Bertucci 2022/07/23 for v1.0

#include:intcalc
#include:cu-num

\cuDate{YYYY-MM-DD}
\cuDateJulian{date}
\cuDefineDateFormat{name%specialDef}{format}#s#%cudateformat
\cuYEAR#*
\cuYEARAM#*
\cuMONTH#*
\cuDAY#*
\cuDOW#*
\cuINDICTION#*
\cuDISPLAYDATE#*
\cuUseDateFormat{format name%keyvals}
#keyvals:\cuUseDateFormat#c
default
%cudateformat
#endkeyvals
\cuMonthName{number}
\cuDayName{number}
\cuDayNameAccusative{number}
\cuToday
\cuTodayJulian
\cuAsJulian
\cuAsGregorian