# pgfcalendar-ext package
# Matthew Bertucci 2025/03/18 for v0.6

#include:pgfcalendar

# from pgfcalendar-ext.code.tex
\pgfextcalendarjulianyeartoweek{Julian day}{year}{week counter}
\pgfextcalendarcurrentweek
\pgfextcalendarifdateweek

#keyvals:\pgfcalendarifdate#c,\ifdate#c
ext/Jan
ext/Feb
ext/Mar
ext/Apr
ext/May
ext/Jun
ext/Jul
ext/Aug
ext/Sep
ext/Oct
ext/Nov
ext/Dec
ext/leap year
ext/leap year=%<year%>
ext/and={%<tests%>}
ext/not={%<tests%>}
ext/week of month=%<num%>
ext/week of month'=%<num%>
ext/calendar week of month=%<num%>
ext/calendar week of month'=%<num%>
ext/yesterday={%<tests%>}
ext/week=%<num%>
#endkeyvals

# deprecated
\pgfcalendarjulianyeartoweek{Julian day}{year}{week counter}#S
\pgfcalendarcurrentweek#S
\pgfcalendarifdateweek#S

# from tikzext-util.tex
\tikzextversion#S
\tikzextversionnumber#S
\tikzextset{options%keyvals}
\pgfextset{options%keyvals}
