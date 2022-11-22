# shapes.geometric tikzlibrary
# 2022/11/20 for v3.1.9a

# loads shapes.geometric pgflibrary

#keyvals:\node#c,\coordinate#c,\nodepart#c,\pic#c
diamond
ellipse
trapezium
semicircle
regular polygon
star
isosceles triangle
kite
dart
circular sector
cylinder
#endkeyvals

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c,\node#c,\coordinate#c,\nodepart#c,\pic#c
aspect=%<value%>
trapezium left angle=%<degrees%>
trapezium right angle=%<degrees%>
trapezium angle=%<degrees%>
trapezium stretches#true,false
trapezium stretches body#true,false
regular polygon sides=%<integer%>
star points=%<integer%>
star point height=##L
star point ratio=%<number%>
isosceles triangle apex angle=%<degrees%>
isosceles triangle stretches#true,false
kite upper vertex angle=%<degrees%>
kite lower vertex angle=%<degrees%>
kite vertex angles=%<degrees%>
dart tip angle=%<degrees%>
dart tail angle=%<degrees%>
circular sector angle=%<degrees%>
cylinder uses custom fill#true,false
cylinder end fill=#%color
cylinder body fill=#%color
#endkeyvals