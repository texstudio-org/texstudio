# shapes.callouts tikzlibrary
# 2022/11/20 for v3.1.9a

# loads shapes.callouts pgflibrary

#keyvals:\node#c,\coordinate#c,\nodepart#c,\pic#c
rectangle callout
ellipse callout
cloud callout
#endkeyvals

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c,\node#c,\coordinate#c,\nodepart#c,\pic#c
callout relative pointer=%<coordinate%>
callout absolute pointer=%<coordinate%>
callout pointer shorten=##L
callout pointer width=##L
callout pointer arc=%<degrees%>
callout pointer start size=##L
callout pointer end size=##L
callout pointer segments=%<integer%>
#endkeyvals