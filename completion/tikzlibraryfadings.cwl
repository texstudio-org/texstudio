# fadings tikzlibrary
# 2022/11/21 for v3.1.9a

#keyvals:\begin{tikzpicture}#c,\tikz#c,\begin{scope}#c,\tikzset#c,\scoped#c,\path#c,\draw#c,\fill#c,\filldraw#c,\pattern#c,\shade#c,\shadedraw#c,\clip#c,\node#c,\coordinate#c,\nodepart#c,\pic#c,\matrix#c,\calendar#c,\chainin#c,\arrow#c,\arrowreversed#c
path fading
path fading=%<name%>
fit fading#true,false
fading transform={%<options%>}
fading angle=%<degrees%>
scope fading=%<name%>
#endkeyvals

\begin{tikzfadingfrompicture}
\begin{tikzfadingfrompicture}[options%keyvals]
\end{tikzfadingfrompicture}
\tikzfadingfrompicture#S
\tikzfadingfrompicture[options%keyvals]#S
\endtikzfadingfrompicture#S

#keyvals:\begin{tikzfadingfrompicture}#c,\tikzfadingfrompicture#c
name=%<name%>
#endkeyvals

\tikzfading[options%keyvals]

#keyvals:\tikzfading#c
name=%<name%>
left color=#%color
right color=#%color
inner color=#%color
outer color=#%color
top color=#%color
bottom color=#%color
middle color=#%color
#endkeyvals