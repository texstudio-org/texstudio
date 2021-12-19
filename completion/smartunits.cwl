# smartunits package
# Matthew Bertucci 12/10/2021 for v1.2

#include:siunitx
#include:pgfmath
#include:pgfkeys

\SmartUnit{keyvals}
\SmartUnitSettings{settings%keyvals}

#keyvals:\SmartUnit,\SmartUnitSettings
metric
imperial
metric imperial
imperial metric
figures=%<integer%>
places=%<integer%>
uk
usa
#endkeyvals

#keyvals:\SmartUnit
km=%<number%>
miles=%<number%>
mi=%<number%>
cm=%<number%>
inches=%<number%>
feet=%<number%>
celsius=%<number%>
C=%<number%>
fahrenheit=%<number%>
F=%<number%>
hours=%<number%>
minutes=%<number%>
seconds=%<number%>
am
pm
L=%<number%>
l=%<number%>
gal=%<number%>
gallons=%<number%>
kg=%<number%>
pounds=%<number%>
pound=%<number%>
lbs=%<number%>
#endkeyvals