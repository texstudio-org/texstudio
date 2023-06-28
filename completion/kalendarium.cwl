# kalendarium package
# Matthew Bertucci 12/26/2021 for v1.0

\KalDate{year}{month}{day}
\KalDate[options%keyvals]{year}{month}{day}
\KalDateStr{format}{delimiter}{date string}
\KalDateStr[options%keyvals]{format}{delimiter}{date string}
\KalToday
\KalToday[options%keyvals]
\KalWeekday{year}{month}{day}
\KalWeekday[options%keyvals]{year}{month}{day}

#keyvals:\usepackage/kalendarium#c,\KalDate,\KalDateStr,\KalToday,\KalWeekday
abbreviate#true,false
periods#true,false
era=#ad,adshort,auc,secular,none
julian#true,false
dayfmt=#roman,latin,arabic
yearfmt=#roman,arabic
antediem#true,false
bissextum#true,false
oldmonths#true,false
#endkeyvals

\KalAbbrFormat{abbreviation}#*
\KalDayFormat{day}#*
\KalYearFormat{year}#*