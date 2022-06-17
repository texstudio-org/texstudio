# pgf-pie package
# Matthew Bertucci 2022/06/17 for v0.7

#include:tikz
#include:scalefnt

\pie{num1/text1,num2/text2,...}
\pie[options%keyvals]{num1/text1,num2/text2,...}

#keyvals:\pie#c
pos={%<x,y%>}
rotate=%<degrees%>
radius=%<number%>
color=#%<color%>,{%<color1,color2,...%>}
explode=%<number%>
sum=#auto,%<number%>
change direction#true,false
before number={%<code%>}
after number={%<code%>}
hide number
scale font
text=#label,pin,inside,legend
style={%<TikZ options%>}
polar
square
cloud
#endkeyvals
