# datetime2-calc package
# Matthew Bertucci 11/11/2021 for v1.5.7

#include:pgfkeys
#include:pgfcalendar

\DTMsavejulianday{name}{number}
\DTMsaveddatetojulianday{name}{register}
\DTMsaveddateoffsettojulianday{name}{offset}{register}
\DTMifdate{name}{test}{true}{false}
\DTMsaveddatediff{name1}{name2}{register}
\DTMsaveaszulutime{name}{YYYY}{MM}{DD}{hh}{mm}{ss}{TZh}{TZm}
\DTMtozulu{name1}{name2}
\DTMcomputedayofweekindex{%<YYYY%>-%<MM%>-%<DD%>}{cmd}#d
\DTMweekdayname{day}
\DTMWeekdayname{day}
\DTMshortweekdayname{day}
\DTMshortWeekdayname{day}
\DTMordinal{number}

\dtmnamewarning{cmd}#*
\dtmSundayIndex#*
\dtmMondayIndex#*
\dtmTuesdayIndex#*
\dtmWednesdayIndex#*
\dtmThursdayIndex#*
\dtmFridayIndex#*
\dtmSaturdayIndex#*