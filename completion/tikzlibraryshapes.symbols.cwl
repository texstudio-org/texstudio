# shapes.symbols tikzlibrary
# 2022/11/20 for v3.1.9a

# loads shapes.symbols pgflibrary

#keyvals:\node#c,\coordinate#c,\nodepart#c,\pic#c
correct forbidden sign
forbidden sign
magnifying glass
cloud
starburst
signal
tape
magnetic tape
#endkeyvals

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c,\node#c,\coordinate#c,\nodepart#c,\pic#c
magnifying glass handle angle fill=%<degrees%>
magnifying glass handle angle aspect=%<factor%>
cloud puffs=%<integer%>
cloud puff arc=%<degrees%>
cloud ignores aspect#true,false
starburst points=%<integer%>
starburst point height=##L
random starburst=%<integer%>
signal pointer angle=%<degrees%>
signal from=%<direction%>
signal from=%<direction%> and %<opposite direction%>
signal to=%<direction%>
signal to=%<direction%> and %<opposite direction%>
tape bend top=#in and out,out and in,none
tape bend bottom=#in and out,out and in,none
tape bend height=##L
magnetic tape tail extend=##L
magnetic tape tail=%<proportion%>
#endkeyvals