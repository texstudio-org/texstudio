# projlib-datetime package
# Matthew Bertucci 2022/07/04 for 2022/07/03 release

#include:relsize

#keyvals:\usepackage/projlib-datetime#c
plain
year-month-day
month-day-year
day-month-year
year-month
month-day
month-year
day-month
#endkeyvals

\ProjLibSetDatetimeInputFormat{type%keyvals}
#keyvals:\ProjLibSetDatetimeInputFormat
year-month-day
month-day-year
day-month-year
#endkeyvals

\ProjLibtoday
\ProjLibtoday[options%keyvals]
\ProjLibToday
\ProjLibToday[options%keyvals]

\Thedate{date}
\Thedate[options%keyvals]{date}
\TheDate{date}
\TheDate[options%keyvals]{date}
\ProjLibdate{date}#*
\ProjLibdate[options%keyvals]{date}#*
\ProjLibDate{date}#*
\ProjLibDate[options%keyvals]{date}#*


#keyvals:\ProjLibtoday,\ProjLibToday,\Thedate,\TheDate,\ProjLibdate,\ProjLibDate
year-month-day=
month-day-year=
day-month-year=
year-month=
month-day=
month-year=
day-month=
only-year-month=
only-month-day=
only-year=
only-month=
only-day=
#endkeyvals
