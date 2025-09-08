# envelope-letter package
# Matthew Bertucci 2025/08/29 for v1.1

#include:tikz
#include:pgfopts
#include:geometry
#include:graphics
#include:pifont
#include:fp

\envelopesetup{options%keyvals}
\makeenvelope
\makeenvelope[options%keyvals]

#keyvals:\usepackage/envelope-letter#c,\envelopesetup,\makeenvelope
grammage=%<number%>
fold lines mode=#0,1,2
no lines
ticks
lines
steps
no steps
instructions
no instructions
full
eco
empty
auto
manual
to=%<text%>
from=%<text%>
#endkeyvals

\setstamp{code}

# not documented
\theletter#S