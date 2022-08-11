# chronosys package
# Matthew Bertucci 2022/08/08 for v1.2

#include:tikz

\begin{chronology}
\begin{chronology}[options%keyvals]
\end{chronology}
\chronology#S
\chronology[options%keyvals]#S
\endchronology#S
\startchronology#*
\startchronology[options%keyvals]#*
\stopchronology#*

\chronoevent{%<year%>}{%<label text%>}
\chronoevent{%<month%>/%<year%>}{%<label text%>}
\chronoevent{%<day%>/%<month%>/%<year%>}{%<label text%>}
\chronoevent[%<options%>]{%<year%>}{%<label text%>}
\chronoevent[%<options%>]{%<month%>/%<year%>}{%<label text%>}
\chronoevent[%<options%>]{%<day%>/%<month%>/%<year%>}{%<label text%>}

\chronoperiode{start-year}{end-year}{label text%text}
\chronoperiode[options%keyvals]{start-year}{end-year}{label text%text}

\chronoperiodecoloralternation{color1,color2,...}
# for color completion
\chronoperiodecoloralternation{color}#S

\restartchronoperiodecolor
\restartchronoperiodecolor[color]

\chronograduation{integer}
\chronograduation[periode|event]{integer}#*
\chronograduation[periode|event][options%keyvals]{integer}

\definechronoevent{name}
\definechronoevent{name}[options%keyvals]
\definechronoperiode{name}
\definechronoperiode{name}[options%keyvals]

\setupchronology{options%keyvals}
\setupchronoevent{options%keyvals}
\setupchronoevent[name]{options%keyvals}
\setupchronoperiode{options%keyvals}
\setupchronoperiode[name]{options%keyvals}
\setupchronograduation{options%keyvals}
\setupchronograduation[periode|event]{options%keyvals}

\chronoperiodcolor

#keyvals:\begin{chronology},\chronology,\startchronology,\setupchronology,\setupchronology
startyear=%<number%>
stopyear=%<number%>
color=#%color
height=##L
width=##L
datesstyle=%<command%>
dateselevation=##L
startdate#true,false
stopdate#true,false
dates#true,false
arrow#true,false
arrowheight=##L
arrowwidth=##L
arrowcolor=#%color
box#true,false
align=#right,center,left
#endkeyvals

#keyvals:\chronoevent,\chronograduation,\definechronoevent,\setupchronoevent,\setupchronograduation
barre#true,false
date#true,false
conversionmonth#true,false
mark#true,false
year#true,false
icon=%<symbol%>
markdepth=##L
iconheight=##L
textstyle=%<command%>
datesseparation=%<symbol%>
datestyle=%<command%>
datesstyle=%<command%>
colorbox=#%color
ifcolorbox#true,false
textwidth=##L
#endkeyvals

#keyvals:\chronoperiode,\chronograduation,\definechronoperiode,\setupchronoperiode,\setupchronograduation
startdate#true,false
stopdate#true,false
dates#true,false
datesstyle=%<command%>
textstyle=%<command%>
color=#%color
dateselevation=##L
textdepth=##L
colorbox=#%color
ifcolorbox#true,false
topheight=##L
bottomdepth=##L
#endkeyvals

# not documented
\dochronoevent#S
\dochronograduation#S
\dochronoperiode#S
\dorestartchronoperiodecolor#S
\dosetupchronoeventandperiode#S
\dosetupchronograduation#S
\dostartchronology#S
\dostartchronologyfinal#S
\ifnexttoken#S
\savefirsttwoarg#S
\todoafterarg#S