# ext.calendar-plus tikzlibrary
# 2023/03/19 for v0.5.0

#include:tikzlibrarycalendar
#include:pgfcalendar-ext

\pgfmathweeksinmonthofyear{first weekday}{month}{year}#*
\pgfmathlastdayinmonthofyear{month}{year}#*

#keyvals:\calendar#c
day xshift=##L
day yshift=##L
month xshift=##L
month yshift=##L
week code=%<code%>
week text=%<text%>
every week/.append style={%<TikZ keys%>}
week label left
#endkeyvals

# not documented
\tikzweekcode#*
\tikzweektext#*
