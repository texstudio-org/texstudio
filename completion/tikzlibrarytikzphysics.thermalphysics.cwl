# tikzphysics.thermalphysics tikzlibrary
# Matthew Bertucci 2026/10/01 for v1.7.0

#include:tikzlibrarytikzphysics.core
#include:tikzlibrarycalc

#keyvals:\begin{tikzpicture}#c,\tikz#c,\node#c
thermal liquid color=#%color
conduction width=##L
conduction height=##L
composite width=##L
composite height=##L
composite split=%<factor%>
thermal plate width=##L
thermal plate thickness=##L
thermal fluid height=##L
thermal flow direction=%<number%>
fin length=##L
fin base height=##L
fin base thickness=##L
fin thickness=##L
radiation radius=##L
radiation ray length=##L
thermal flow direction=%<number%>
thermometer height=##L
thermometer bulb radius=##L
thermometer stem width=##L
thermometer level=%<factor%>
calorimeter width=##L
calorimeter height=##L
calorimeter insulation
calorimeter level=%<factor%>
expansion rod length=##L
expansion rod thickness=##L
expansion separation=##L
thermal expansion ratio=%<factor%>
#endkeyvals

#keyvals:\node#c
conduction slab
composite wall
convection surface
cooling fin
radiating body
thermometer
calorimeter
expansion rod
#endkeyvals