# pgfornament-han package
# Matthew Bertucci 2/12/2022 for v0.33

#include:xpatch
#include:pgfornament

\pgfornamenthan{ornament number}
\pgfornamenthan[options%keyvals]{ornament number}

#keyvals:\pgfornamenthan#c
scale=%<factor%>
width=##L
height=##L
color=#%color
opacity=%<factor%>
ydelta=##L
symmetry=#v,h,c,none
anchor=%<anchor%>
#endkeyvals

\pgfOrnamentsHanObject#*