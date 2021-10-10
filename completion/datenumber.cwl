# datenumber package
# Matthew Bertucci 10/5/2021 for v0.02

\setstartyear{year}
\thedatenumber
\thedateyear
\thedatemonth
\thedateday
\thedatedayname
\setdatenumber{year}{month}{day}
\setdatebynumber{number}
\nextdate
\prevdate
\setdate{year}{month}{day}
\setdatetoday
\datemonthname
\datedayname
\datedate
\setmydatenumber{numbercount}{year}{month}{day}
\setmydatebynumber{number}{yearcount}{monthcount}{daycount}
\mynextdate{yearcount}{monthcount}{daycount}
\mynextdate{yearcount}{monthcount}{daycount}
\setmonthname{number}
\setdayname{number}
\setdaynamebynumber{number}
\dateselectlanguage{language%keyvals}

#keyvals:\dateselectlanguage#c
english
USenglish
french
spanish
german
ngerman
#endkeyvals

\ifleapyear{year}
\ifvaliddate{year}{month}{day}