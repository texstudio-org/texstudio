# dateplot pgfplotslibrary
# 2022/12/11 for v1.18.1

#include:pgfcalendar

#keyvals:\begin{axis}#c,\begin{loglogaxis}#c,\begin{semilogxaxis}#c,\begin{semilogyaxis}#c,\addplot#c,\addplot3#c,\addplot+#c,\pgfplotsset#c,\begin{groupplot}#c,\nextgroupplot#c,\begin{smithchart}#c,\begin{polaraxis}#c,\begin{ternaryaxis}#c
date coordinates in=%<coordinate%>
date ZERO=%<year-month-day%>
#endkeyvals

\year
\month
\day
\hour
\Hour
\minute
\Minute
\lowlevel
\Second

# not documented
\julianto#S
\hourto#S
\minuteto#S
\pgfplotstempjuliandate#S
\pgfplotstemptime#S
\pgfplotstempjuliandatenumeric#S