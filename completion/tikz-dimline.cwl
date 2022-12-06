# tikz-dimline package
# Matthew Bertucci 9/1/2021 for v1.0

#include:tikz
#include:pgfplots
#include:ifthen
#include:tikzlibrarycalc
#include:tikzlibrarydecorations.markings

\dimline[options%keyvals]{start}{end}{label}

#keyvals:\dimline
color=#%color
line style=
label style=
extension start length=##L
extension end length=##L
extension start angle=%<degrees%>
extension end angle=%<degrees%>
extension start style=
extension end style=
extension start path=
extension end path=
arrows=#dimline-dimline,dimline reverse-dimline reverse
#endkeyvals
