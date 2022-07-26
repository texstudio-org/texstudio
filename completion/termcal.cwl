# termcal package
# Matthew Bertucci 2022/07/24 for v1.8

#include:longtable
#include:ifthen

\begin{calendar}{mm/dd/yyyy}{number of weeks}
\end{calendar}

\skipday
\calday{option list}
\calday[head%text]{option list}
\classday
\noclassday
\weeklytext{text}
\options{day}{option list}
\caltext{day}{text}
\caltexton{day}{text}
\caltextnext{text}
\calboxdepth#L
\calwidth#L
\calprintdate#*
\calprintclass#*

\addtotoks{token box}{new tokens}#*
\advancedate#*
\advancemonth#*
\classdayfalse#*
\classdaytrue#*
\curdate#*
\ifclassday#*
\ifleap#*
\ifnewmonth#*
\leapfalse#*
\leaptrue#*
\monthlength#*
\monthname#*
\newmonthfalse#*
\newmonthtrue#*
\ordinal{register}#*
\ordinaldate#*
\setdate{mm/dd/yyyy}#*
\setleap#*
\theclassnum#*
\thedate#*
\themonth#*
\thetextdaycount#*
\theyear#*

\RCSID#S
\docdate#S
\fileversion#S
\filedate#S