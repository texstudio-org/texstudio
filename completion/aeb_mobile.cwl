# aeb_mobile package
# Matthew Bertucci 2022/05/10 for v1.4

#include:web
#include:eforms

#keyvals:\usepackage/aeb_mobile#c
smartphone
nomaketitle
useforms
scalefigures
!scalefigures
#endkeyvals

\scalefiguresOn
\scalefiguresOff
\mobPrint{text}
\mobPrintTip#*
\mobToggleCols{text}
\mobToggleColsTip#*
\mobFormPresets{commands}
\ifsmartphone#*
\smartphonetrue#*
\smartphonefalse#*

# not documented
\ifmobscalefigures#S
\mobscalefigurestrue#S
\mobscalefiguresfalse#S
\generateEvenPage#*
\mobPrintIt#*
\mobPrintIt[opt]#*
\mobTwoCols#*
\mobTwoCols[opt]#*