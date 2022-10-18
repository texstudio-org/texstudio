# pgfcalendar-ext package
# Matthew Bertucci 2022/10/16 for v0.4

#include:pgfcalendar

# from pgfcalendar-ext.code.tex
\pgfcalendarjulianyeartoweek{Julian day}{year}{week counter}
\pgfcalendarcurrentweek
\pgfcalendarifdateweek
\pgfcalendarendjulianplus#S

#keyvals:\pgfcalendarifdate#c,\ifdate#c
Jan
Feb
Mar
Apr
May
Jun
Jul
Aug
Sep
Oct
Nov
Dec
leap year
leap year=%<year%>
and={%<tests%>}
not={%<tests%>}
week of month=%<num%>
week of month'=%<num%>
calendar week of month=%<num%>
calendar week of month'=%<num%>
yesterday={%<tests%>}
week=%<num%>
#endkeyvals
