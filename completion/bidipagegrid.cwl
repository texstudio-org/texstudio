# bidipagegrid package
# Matthew Bertucci 2022/07/18 for v0.2

#include:tikz
#include:atbegshi
#include:kvoptions

\bidipagegridsetup{options%keyvals}

#keyvals:\bidipagegridsetup,\usepackage/bidipagegrid#c
enable
disable
left-top
lt
top-left
tl
tr
top-right
rt
right-top
left-bottom
lb
bottom-left
bl
br
bottom-right
rb
right-bottom
step=##L
firstcolor=#%color
secondcolor=#%color
arrows#true,false
arrowlength=##L
double=#false,first,last,true
foreground#true,false
direction=#LTR,RTL
#endkeyvals

\setLTRpagegrid
\setRTLpagegrid

\bidipagegridShipoutDoubleBegin#*
\bidipagegridShipoutDoubleEnd#*