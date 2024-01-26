# non-decimal-units package
# Matthew Bertucci 2024/01/25

#keyvals:\usepackage/non-decimal-units#c
british
danish
german
#endkeyvals

\nduKeys{options%keyvals}
\nduValue{unit group}{value}
\nduValue{unit group}[options%keyvals]{value}
\VALUE
\SYMBOL
\nduMath{unit group}{variable}{operator}{value}
\nduMath{unit group}[options%keyvals]{variable}{operator}{value}
\nduResult{unit group}{variable}
\nduResult{unit group}[options%keyvals]{variable}
\nduNormalize{unit group}{amount}{unit}
\nduNormalize{unit group}[options%keyvals]{amount}{unit}

#keyvals:\nduKeys#c,\nduValue#c,\nduMath#c,\nduResult#c,\nduNormalize#c
display=#values only,formatted,symbols only
format=%<code%>
replace nil with=%<code%>
treat zero as nil
unit depth=%<unit name%>
unit separator=%<symbol%>
use numprint
add to variable=%<code%>
subtract from variable=%<code%>
normalize
#endkeyvals

\nduHeader{unit name}
\nduHeader{unit name}[options%keyvals]

#keyvals:\nduKeys#c,\nduHeader#c
aligned
cell widths=##L
set aligned for environment=%<name%>
tabularray column type=%<letter%>
#endkeyvals

\nduSymbol{unit group}
\nduFactor{unit group}{unit name}
\nduNewBaseUnit{unit group}{keyvals}
\nduNewUnitGroup{unit group}{base units}
\nduNewUnitGroup{unit group}{base units}[cmd]
\nduNewUnitGroup[keyvals]{unit group}{base units}
\nduNewUnitGroup[keyvals]{unit group}{base units}[cmd]
