# analogclock package
# Matthew Bertucci 2022/07/25 for v1.0

#include:hyperref
#include:xcolor
#include:xkeyval
#include:tikz

#keyvals:\usepackage/analogclock#c
timeinterval=%<integer%>
#endkeyvals

\initclock
\analogclock
\clocksizefactor{factor}
\faceclock{integer}{color}

# not documented
\kk#S
\sizebox#S
\uu#S
\colocafield{arg}#S
\facebg#S
\faceframe#S
\face#S
\clockskin#S
\startclock#S