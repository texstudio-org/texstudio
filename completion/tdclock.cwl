# tdclock package
# Matthew Bertucci 2022/07/25 for v2.3

#include:hyperref
#include:xcolor
#include:xkeyval

#keyvals:\usepackage/tdclock#c
font=#Helv,HelvB,HelvI,HelvBI,Times,TimesB,TimesI,TimesBI,Cour,CourB,CourI,CourBI
timeinterval=%<integer%>
timeduration=%<minutes%>
timewarningfirst=%<integer 0-100%>
timewarningsecond=%<integer 0-100%>
timedeath=%<0|1%>
colorwarningfirst=#%color
colorwarningsecond=#%color
fillcolorwarningfirst=#%color
fillcolorwarningsecond=#%color
resetatpages=#none,all,%<integer%>,{%<list of integers%>}
pageresetcontrol=#pdfpagelabels,pdfpagenumbers
#endkeyvals

\initclock
\tdclock
\tdtime
\tddate
\tdday
\tdmonth
\tdyear
\tdhours
\tdminutes
\tdseconds
\crono
\cronohours
\cronominutes
\cronoseconds
\resetcrono{button text}
\toggleclock{button text}
\factorclockfont{factor}
\hhmmss
\hhmm
\timeseparator#*
\ddmmyyyy
\mmddyyyy
\dateseparator#*
\pdfslash#*
\pdfcolon#*

# not documented
\colorninety#S
\colorninetyfive#S
\fillcolorninety#S
\fillcolorninetyfive#S
\auxiliar#S
\resetclock#S
\tdwarningbox{arg}#S
\mm#S
\sizebox#S
\clockfield{field}#S
\initfields#S
\startclock#S