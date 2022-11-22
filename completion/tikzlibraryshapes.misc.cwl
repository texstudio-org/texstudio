# shapes.misc tikzlibrary
# 2022/11/21 for v3.1.9a

# loads shapes.misc pgflibrary

#keyvals:\node#c,\coordinate#c,\nodepart#c,\pic#c
cross out
strike out
rounded rectangle
chamfered rectangle
#endkeyvals

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c,\node#c,\coordinate#c,\nodepart#c,\pic#c
rounded rectangle arc length=%<degrees%>
rounded rectangle west arc=#concave,convex,none
rounded rectangle east arc=#concave,convex,none
chamfered rectangle angle=%<degrees%>
chamfered rectangle xsep=##L
chamfered rectangle ysep=##L
chamfered rectangle sep=##L
chamfered rectangle corners={%<list%>}
#endkeyvals