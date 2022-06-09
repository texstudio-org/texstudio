# datetime2-en-fulltext package
# Matthew Bertucci 2022/06/07 for v1.0

#include:datetime2
#include:fmtcount

# passes all options to datetime2
#keyvals:\usepackage/datetime2-en-fulltext#c
yearmonthsep=%<separator%>
monthdaysep=%<separator%>
dayyearsep=%<separator%>
datesep=%<separator%>
hourminsep=%<separator%>
minsecsep=%<separator%>
timesep=%<separator%>
datetimesep=%<separator%>
timezonesep=%<separator%>
showseconds#true,false
showdate#true,false
showzone#true,false
showzoneminutes#true,false
showisoZ#true,false
useregional=#false,text,numeric,num
showdow#true,false
warn#true,false
style=%<style name%>
calc
%<language%>
#endkeyvals

#ifOption:calc
#include:datetime2-calc
#endif
#ifOption:calc=true
#include:datetime2-calc
#endif

#ifOption:showdow
#include:datetime2-calc
#endif
#ifOption:showdow=true
#include:datetime2-calc
#endif

#keyvals:\DTMsetdatestyle#c,\DTMsettimestyle#c
en-fulltext
en-FullText
en-FULLTEXT
#endkeyvals

#keyvals:\DTMsettimestyle#c
en-Fulltext
#endkeyvals

\DTMAfterNoonstring#*
\DTMafternoonstring#*
\DTMenfulltextmonthyearsep#*
\DTMHalfPaststring#*
\DTMhalfpaststring#*
\DTMMinutePaststring#*
\DTMminutepaststring#*
\DTMMinutesPaststring#*
\DTMminutespaststring#*
\DTMMinutesTostring#*
\DTMminutestostring#*
\DTMMinuteTostring#*
\DTMminutetostring#*
\DTMMorningstring#*
\DTMmorningstring#*
\DTMOClockstring#*
\DTMoclockstring#*
\DTMQuarterPaststring#*
\DTMquarterpaststring#*
\DTMQuarterTostring#*
\DTMquartertostring#*