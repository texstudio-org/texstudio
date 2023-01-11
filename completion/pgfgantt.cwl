# pgfgantt package
# Matthew Bertucci 2/9/2022 for v5.0

#include:tikz
#include:pgfcalendar
#include:tikzlibrarybackgrounds
#include:tikzlibrarycalc
#include:tikzlibrarypatterns
#include:tikzlibrarypositioning
#include:tikzlibraryshapes.geometric

\ganttset{options%keyvals}
\begin{ganttchart}{start tss}{end tss}
\begin{ganttchart}[options%keyvals]{start tss}{end tss}
\end{ganttchart}
\newgantttimeslotformat{name}{converter code}#*
\ganttnewline
\ganttnewline[TikZ options]
\ganttalignnewline
\gantttitle{label}{number of time slots}
\gantttitle[options%keyvals]{label}{number of time slots}
\gantttitlelist{pgffor list}{length of each element}
\gantttitlelist[options%keyvals]{pgffor list}{length of each element}
\gantttitlecalendar{calendar lines}
\gantttitlecalendar[options%keyvals]{calendar lines}
\gantttitlecalendar*{start tss}{end tss}{calendar lines}
\gantttitlecalendar*[options%keyvals]{start tss}{end tss}{calendar lines}
\currentweek
\startyear
\startmonth
\startday
\ganttvrule{label%text}{tss}
\ganttvrule[options%keyvals]{label%text}{tss}
\ganttbar{label%text}{start tss}{end tss}
\ganttbar[options%keyvals]{label%text}{start tss}{end tss}
\ganttgroup{label%text}{start tss}{end tss}
\ganttgroup[options%keyvals]{label%text}{start tss}{end tss}
\ganttmilestone{label%text}{tss}
\ganttmilestone[options%keyvals]{label%text}{tss}
\ganttlinkedbar{label%text}{start tss}{end tss}
\ganttlinkedbar[options%keyvals]{label%text}{start tss}{end tss}
\ganttlinkedgroup{label%text}{start tss}{end tss}
\ganttlinkedgroup[options%keyvals]{label%text}{start tss}{end tss}
\ganttlinkedmilestone{label%text}{tss}
\ganttlinkedmilestone[options%keyvals]{label%text}{tss}
\newganttchartelement{name}{new default keyvals}
\newganttchartelement*{name}{new default keyvals}
\ganttlink{start element name}{end element name}
\ganttlink[options%keyvals]{start element name}{end element name}
\newganttlinktype{type%specialDef}{TikZ code}#s#%ganttlinktype
\ganttsetstartanchor{anchor}
\ganttsetendanchor{anchor}
\xLeft
\yUpper
\xRight
\yLower
\ganttlinklabel
\ganttvalueof{key%plain}
\newganttlinktypealias{new type%specialDef}{existing type}#s#%ganttlinktype
\setganttlinklabel{type%keyvals}{label%text}
#keyvals:\setganttlinklabel#c
%ganttlinktype
#endkeyvals
\endofdecade#*
\querydecade#*

#keyvals:\ganttset#c,\begin{ganttchart}#c,\gantttitle#c,\gantttitlelist#c,\gantttitlecalendar#c,\gantttitlecalendar*#c,\ganttvrule#c,\ganttbar#c,\ganttgroup#c,\ganttmilestone#c,\ganttlinkedbar#c,\ganttlinkedgroup#c,\ganttlinkedmilestone#c,\ganttlink#c
time slot format=#simple.isodate,isodate-yearmonth,isodate-year,little-endian,middle-endian,big-endian
time slot format/base century=%<year%>
time slot format/start date=%<ISO-standard date%>
canvas/.style={%<TikZ options%>}
x unit=##L
y unit title=##L
y unit chart=##L
expand chart=##L
hgrid=#true,false,{%<style list%>}
hgrid style/.style={%<TikZ options%>}
vgrid=#true,false,{%<style list%>}
today=%<tss%>
today offset=%<number%>
today rule/.style={%<TikZ options%>}
today label=%<text%>
today label font=%<font commands%>
today label node/.style={%<TikZ options%>}
newline shortcut#true,false
title list options={%<pgffor options%>}
calendar week text={%<format%>}
time slot unit=#day,month,year
title/.style={%<TikZ options%>}
title label font=%<font commands%>
title label node/.style={%<TikZ options%>}
title label text=%<text%>
title left shift=%<factor%>
title right shift=%<factor%>
title top shift=%<factor%>
title height=%<factor%>
include title in canvas#true,false
vrule offset=%<number%>
vrule/.style={%<TikZ options%>}
vrule label font=%<font commands%>
vrule label node/.style={%<TikZ options%>}
chart element start border=#left,right
bar/.style={%<TikZ options%>}
group/.style={%<TikZ options%>}
milestone/.style={%<TikZ options%>}
bar label text=%<text%>
group label text=%<text%>
milestone label text=%<text%>
bar label font=%<font commands%>
group label font=%<font commands%>
milestone label font=%<font commands%>
bar label node/.style={%<TikZ options%>}
group label node/.style={%<TikZ options%>}
milestone label node/.style={%<TikZ options%>}
inline#true,false
bar inline label anchor=%<anchor%>
group inline label anchor=%<anchor%>
milestone inline label anchor=%<anchor%>
bar inline label node/.style={%<TikZ options%>}
group inline label node/.style={%<TikZ options%>}
milestone inline label node/.style={%<TikZ options%>}
bar left shift=%<factor%>
bar right shift=%<factor%>
bar top shift=%<factor%>
bar height=%<factor%>
group left shift=%<factor%>
group right shift=%<factor%>
group top shift=%<factor%>
group height=%<factor%>
milestone left shift=%<factor%>
milestone right shift=%<factor%>
milestone top shift=%<factor%>
milestone height=%<factor%>
group right peak tip position=%<fraction%>
group right peak width=%<factor%>
group right peak height=%<factor%>
group left peak tip position=%<fraction%>
group left peak width=%<factor%>
group left peak height=%<factor%>
group peaks tip position=%<fraction%>
group peaks width=%<factor%>
group peaks height=%<factor%>
progress=#none,today,%<number%>
bar incomplete/.style={%<TikZ options%>}
group incomplete/.style={%<TikZ options%>}
milestone incomplete/.style={%<TikZ options%>}
progress label text=%<text%>
bar progress label anchor=%<anchor%>
bar progress label font=%<font commands%>
bar progress label node/.style={%<TikZ options%>}
group progress label anchor=%<anchor%>
group progress label font=%<font commands%>
group progress label node/.style={%<TikZ options%>}
milestone progress label anchor=%<anchor%>
milestone progress label font=%<font commands%>
milestone progress label node/.style={%<TikZ options%>}
on top fraction=%<fraction%>
on bottom fraction=%<fraction%>
on left fraction=%<fraction%>
on right fraction=%<fraction%>
name=%<name%>
link/.style={%<TikZ options%>}
link type=#%ganttlinktype
link mid=%<factor%>
link bulge=%<factor%>
link tolerance=%<factor%>
link label=%<text%>
link label font=%<font commands%>
link label node/.style={%<TikZ options%>}
#endkeyvals
