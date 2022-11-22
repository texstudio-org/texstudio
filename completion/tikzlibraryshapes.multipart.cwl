# shapes.multipart tikzlibrary
# 2022/11/20 for v3.1.9a

# loads shapes.multipart pgflibrary

#keyvals:\node#c,\coordinate#c,\nodepart#c,\pic#c
circle split
circle solidus
ellipse split
rectangle split
#endkeyvals

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c,\node#c,\coordinate#c,\nodepart#c,\pic#c
rectangle split allocate boxes=%<number%>
rectangle split parts=%<number%>
rectangle split empty part width=##L
rectangle split empty part height=##L
rectangle split empty part depth=##L
rectangle split part align={%<list%>}
rectangle split draw splits#true,false
rectangle split use custom fill#true,false
rectangle split part fill={%<list%>}
#endkeyvals