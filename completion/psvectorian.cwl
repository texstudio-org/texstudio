# psvectorian package
# Matthew Bertucci 2022/06/13 for v0.41

#include:graphicx
#include:pstricks

\psvectorian{number}
\psvectorian[options%keyvals]{number}

#keyvals:\psvectorian
scale=%<factor%>
opacity=%<factor%>
width=##L
height=##L
color=#%color
flip#true,false
mirror#true,false
#endkeyvals

\psvectorianDefaultColor#*