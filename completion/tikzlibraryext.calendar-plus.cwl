# ext.calendar-plus tikzlibrary
# 2022/12/09 for v0.4.2

#include:tikzlibrarycalendar
#include:pgfcalendar-ext

\pgfmathweeksinmonthofyear{first weekday}{month}{year}#*
\pgfmathlastdayinmonthofyear{month}{year}#*

#keyvals:\calendar#c
week code=%<code%>
week text=%<text%>
every week/.append style={%<TikZ keys%>}
week label left
#endkeyvals

# not documented
\tikzweekcode#*
\tikzweektext#*