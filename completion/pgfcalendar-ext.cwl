# pgfcalendar-ext package
# Matthew Bertucci 2022/10/02 for v0.3

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
yesterday={%<tests%>}
week=%<num%>
#endkeyvals