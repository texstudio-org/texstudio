# broydensolve package
# Matthew Bertucci 2025/07/25 for v0.1

\ang(coordinates)
\BroydenIterations
\BroydenRoot{variable}
\BroydenRoot[iteration]{variable}
\BroydenRoots
\BroydenSetup{keyvals}
\BroydenSolve{keyvals}
\col(coordinates)
\dis(coordinates)

#keyvals:\BroydenSetup,\BroydenSolve
abs-approx-error=%<value%>
coordinates#true,false
func={%<list%>}
func-error=%<value%>
init={%<list%>}
iterations=%<integer%>
rel-approx-error=%<value%>
stop-crit=#abs-approx-error,func-error,iterations,rel-approx-error
var={%<list%>}
#endkeyvals