# pgf-pie package
# Matthew Bertucci 9/21/2021 for v0.6

#include:tikz
#include:scalefnt

\pie{num1/text1,num2/text2,...}
\pie[options%keyvals]{num1/text1,num2/text2,...}

#keyvals:\pie
pos={%<x,y%>}
rotate=%<degrees%>
radius=
color=#%color
explode=
sum=
before number=
after number=
hide number
scale font
text=#label,pin,inside,legend
style=
polar
square
cloud
#endkeyvals
