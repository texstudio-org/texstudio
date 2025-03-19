# ext.calendar-plus tikzlibrary
# 2025/03/19 for v0.6

#include:tikzlibrarycalendar
#include:pgfcalendar-ext

\pgfmathextweeksinmonthofyear{first weekday}{month}{year}#*
\pgfmathextlastdayinmonthofyear{month}{year}#*

#keyvals:\calendar#c
day xshift=##L
day yshift=##L
month xshift=##L
month yshift=##L
ext/week code=%<code%>
ext/week text=%<text%>
ext/every week/.append style={%<TikZ keys%>}
ext/week label left
#endkeyvals

# not documented
\tikzextweekcode#*
\tikzextweektext#*
