# circuits.ee.IEC tikzlibrary
# 2022/11/21 for v3.1.9a

#include:tikzlibrarycircuits.ee
#include:tikzlibraryshapes.gates.ee.IEC

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c
circuit ee IEC
#endkeyvals

#keyvals:\node#c,\coordinate#c,\nodepart#c
current direction
current direction'
resistor
resistor={%<options%>}
inductor
inductor={%<options%>}
capacitor
capacitor={%<options%>}
battery
battery={%<options%>}
bulb
bulb={%<options%>}
current source
current source={%<options%>}
voltage source
voltage source={%<options%>}
ac source
ac source={%<options%>}
dc source
dc source={%<options%>}
ground
ground={%<options%>}
diode
diode={%<options%>}
Zener diode
Zener diode={%<options%>}
Schottky diode
Schottky diode={%<options%>}
tunnel diode
tunnel diode={%<options%>}
backward diode
backward diode={%<options%>}
breakdown diode
breakdown diode={%<options%>}
contact
contact={%<options%>}
make contact
make contact={%<options%>}
break contact
break contact={%<options%>}
amperemeter
amperemeter={%<options%>}
voltmeter
voltmeter={%<options%>}
ohmmeter
ohmmeter={%<options%>}
ampere=%<value%>
volt=%<value%>
ohm=%<value%>
siemens=%<value%>
henry=%<value%>
farad=%<value%>
coulomb=%<value%>
voltampere=%<value%>
watt=%<value%>
hertz=%<value%>
#endkeyvals