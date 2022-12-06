# reflectgraphics package
# Matthew Bertucci 11/22/2021 for v0.2c

#include:kvoptions
#include:keyval
#include:graphicx
#include:calc
#include:tikz
#include:tikzlibraryfadings

\reflectgraphics{imagefile}#g
\reflectgraphics[options%keyvals]{imagefile}#g

#keyvals:\reflectgraphics
width=##L
height=##L
scale=%<factor%>
angle=%<degrees%>
trim=%<<left> <bot> <up> <right>%>
distance=##L
length=%<percent%>
opacity=%<percent%>
#endkeyvals
