# efbox package
# Matthew Bertucci 9/9/2021 for v1.0

#include:color
#include:pgfkeys

\efbox{text}
\efbox[options%keyvals]{text}
\efboxsetup{options%keyvals}

#keyvals:\efbox,\efboxsetup
leftline#true,false
rightline#true,false
topline#true,false
bottomline#true,false
hidealllines#true,false
backgroundcolor=#%color
linecolor=#%color
linewidth=##L
margin=##L
font=
baselinestretch=
#endkeyvals