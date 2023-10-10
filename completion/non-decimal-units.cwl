# non-decimal-units package
# Matthew Bertucci 2023/10/10

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
\nduMath{unit name}{variable}{operator}{value}
\nduMath{unit name}[options%keyvals]{variable}{operator}{value}
\nduResult{unit name}{variable}
\nduResult{unit name}[options%keyvals]{variable}

#keyvals:\nduKeys#c,\nduValue#c,\nduMath#c,\nduResult#c
display=#values only,formatted,symbols only,numprint
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

\nduSymbol{unit name}
\nduFactor{unit name}{unit name}
\nduNewBaseUnit{unit name}{keyvals}
\nduNewUnitGroup{unit name}{base units}
\nduNewUnitGroup{unit name}{base units}[cmd]
\nduNewUnitGroup[keyvals]{unit name}{base units}
\nduNewUnitGroup{[keyvals]unit name}{base units}[cmd]
