# datenumber package
# Matthew Bertucci 2/7/2022 for v0.03

#keyvals:\usepackage/datenumber#c
english
USenglish
french
italian
spanish
german
ngerman
#endkeyvals

\setstartyear{year}
\thestartyear
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

\fileversion#S
\filedate#S
