# projlib-datetime package
# Matthew Bertucci 2022/06/17 for 2022/06/15 release

#include:l3keys2e
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

\ProjLibdate{date}
\ProjLibdate[options%keyvals]{date}
\ProjLibDate{date}
\ProjLibDate[options%keyvals]{date}

#keyvals:\ProjLibtoday,\ProjLibToday,\ProjLibdate,\ProjLibDate
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

\Thedate
\TheDate
