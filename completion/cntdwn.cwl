# cntdwn package
# Matthew Bertucci 2/7/2022 for v.6

#include:xkeyval

#keyvals:\usepackage/cntdwn#c
shortcount
longcount
#endkeyvals

\cntdwnlTimers#*
\cntdwnaTimers#*
\cntdwnYear#*
\cntdwnYears#*
\cntdwnDay#*
\cntdwnDays#*
\cntdwnHour#*
\cntdwnHours#*
\cntdwnMinute#*
\cntdwnMinutes#*
\cntdwnSecond#*
\cntdwnSeconds#*
\CDO#*

# from shrtcnt.def (loaded by default)
\setShortCntDwn{name}{options%keyvals}
\seconds#*
\minutes#*
\hours#*

#keyvals:\setShortCntDwn
length=%<time%>
stopwatch#true,false
onfinish=#stop,continue
endmsg=%<text%>
notify1=%<time%>
notify2=%<time%>
notify3=%<time%>
event1=%<JavaScript function%>
event2=%<JavaScript function%>
event3=%<JavaScript function%>
endEvent=%<JavaScript function%>
startcolor=%<JavaScript color%>
pausecolor=%<JavaScript color%>
stopcolor=%<JavaScript color%>
autorun#true,false
refreshrate=%<number%>
#endkeyvals

\cntdwnDisplay{name}{width}{height}
\cntdwnDisplay[eforms options]{name}{width}{height}
\cntdwnStartT{name}{width}{height}
\cntdwnStartT[eforms options]{name}{width}{height}
\cntdwnPauseT{name}{width}{height}
\cntdwnPauseT[eforms options]{name}{width}{height}
\cntdwnStopT{name}{width}{height}
\cntdwnStopT[eforms options]{name}{width}{height}

\cntdwnEndTarget{name}{width}{height}
\cntdwnEndTarget[eforms options]{name}{width}{height}

\cntdwnStart{name}{width}{height}
\cntdwnStart[eforms options]{name}{width}{height}
\cntdwnPause{name}{width}{height}
\cntdwnPause[eforms options]{name}{width}{height}
\cntdwnStop{name}{width}{height}
\cntdwnStop[eforms options]{name}{width}{height}

\cntdwnopts{arg}#*
\thetimername{arg}#*
\isStopwatch#*
\cnddwnDefaultEndMsg#*

#ifOption:longcount
# from lngcnt.def
\setLongCntDwn{name}{options%keyvals}
\days#*
\weeks#*
\years#*

#keyvals:\setLongCntDwn
date=%<YYYY/MM/DD%>
time=%<HH:mm:SS%>
tzoffset=
refreshrate=%<number%>
autorun#true,false
autopause#true,false
autorunenabled#true,false
notify1=%<time%>
notify2=%<time%>
notify3=%<time%>
notify5=%<time%>
notify6=%<time%>
notify7=%<time%>
eventhandler=
endtimecolor=%<JavaScript color%>
displayfunc=%<JavaScript function%>
onfinish=#stop,continue
endmsg=%<text%>
#endkeyvals

\lcntdwnDisplay{name}{width}{height}
\lcntdwnDisplay[eforms options]{name}{width}{height}
\lcntdwnToggle{name}{width}{height}
\lcntdwnToggle[eforms options]{name}{width}{height}

\setClockTimer{name}{options%keyvals}

#keyvals:\setClockTimer
tzoffset=
refreshrate=%<number%>
autorun#true,false
autopause#true,false
currtimefunc=
#endkeyvals

\cntdwnclocktime{name}{width}{height}
\cntdwnclocktime[eforms options]{name}{width}{height}
\cntdwnclockdate{name}{width}{height}
\cntdwnclockdate[eforms options]{name}{width}{height}

\clockToggle{name}{width}{height}
\clockToggle[eforms options]{name}{width}{height}

\lcnddwnDefaultEndMsg#*
#endif