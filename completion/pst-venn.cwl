# pst-venn package
# Matthew Bertucci 2/23/2022 for v0.01

#include:pstricks
#include:pst-xkey

\psVenn(x1,y1)(x2,y2)(x3,y3){radius}{segments}
\psVenn[options%keyvals](x1,y1)(x2,y2)(x3,y3){radius}{segments}

#keyvals:\psVenn#c
bgcircle#true,false
bgcolor=#%color
bgradius=##L
fgcolor=#%color
vennfill=#solid,hlines,dots
#endkeyvals