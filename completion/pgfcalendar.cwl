# pgfcalendar package
# Matthew Bertucci 10/24/2021

#include:pgfrcs
#include:pgfkeys

\pgfcalendardatetojulian{date}{counter}#*
\pgfcalendarjuliantodate{Julian day}{year cmd%cmd}{month cmd%cmd}{day cmd%cmd}#*d
\pgfcalendarjuliantoweekday{Julian day}{week day cmd%cmd}#*d
\pgfcalendareastersunday{year}{cmd}#*d

\pgfcalendarifdate{date}{tests%keyvals}{code}{else code}#*

#keyvals:\pgfcalendarifdate#c,\ifdate#c
all
Monday
Tuesday
Wednesday
Thursday
Friday
Saturday
Sunday
workday
weekend
equals=%<reference%>
at least=%<reference%>
at most=%<reference%>
between=%<start%> and %<end%>
day of month=%<number%>
end of month=%<number%>
Easter=%<number%>
#endkeyvals

\pgfcalendarifdatejulian#*
\pgfcalendarifdateweekday#*
\pgfcalendarifdateyear#*
\pgfcalendarifdatemonth#*
\pgfcalendarifdateday#*

\pgfcalendarweekdayname{week day number}#*
\pgfcalendarweekdayshortname{week day number}#*
\pgfcalendarmonthname{month number}#*
\pgfcalendarmonthshortname{month number}#*

\pgfcalendar{prefix}{start date}{end date}{rendering code}#*

\pgfcalendarprefix#*
\pgfcalendarbeginiso#*
\pgfcalendarbeginjulian#*
\pgfcalendarendiso#*
\pgfcalendarendjulian#*
\pgfcalendarcurrentjulian#*
\pgfcalendarcurrentweekday#*
\pgfcalendarcurrentyear#*
\pgfcalendarcurrentmonth#*
\pgfcalendarcurrentday#*

\ifdate{test%keyvals}{code}{else code}#*

\pgfcalendarshorthand{kind}{representation}#*
\pgfcalendarsuggestedname#*

\ifpgfcalendarmatches#*
\pgfcalendarmatchestrue#*
\pgfcalendarmatchesfalse#*

### from pgfint.code.tex
\pgfinteval{arg}#*
\pgfintabs{arg}#*
\pgfintmax{arg1}{arg2}#*
\pgfintmin{arg1}{arg2}#*
\pgfintdivtruncate{arg1}{arg2}#*
\pgfintdivfloor{arg1}{arg2}#*
\pgfintdivround{arg1}{arg2}#*
\pgfintmod{arg1}{arg2}#*
\pgfintset{arg1}{arg2}#*