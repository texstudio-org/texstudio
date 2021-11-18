# pagegrid package
# Matthew Bertucci 11/17/2021 for v1.5

#include:tikz
#include:atbegshi
#include:kvoptions

\pagegridsetup{options%keyvals}

#keyvals:\pagegridsetup
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
#endkeyvals

\pagegridShipoutDoubleBegin#*
\pagegridShipoutDoubleEnd#*