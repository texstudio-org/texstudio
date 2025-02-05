# beamerbaseboxes package
# Matthew Bertucci 2025/02/05 for v3.72

\beamerboxesdeclarecolorscheme{name}{upper color}{lower color}#*
\begin{beamerboxesrounded}{head%text}
\begin{beamerboxesrounded}[options%keyvals]{head%text}
\end{beamerboxesrounded}
\beamerboxesrounded#S
\endbeamerboxesrounded#S

#keyvals:\begin{beamerboxesrounded}
scheme=%<scheme name%>
upper=%<beamer color%>
lower=%<beamer color%>
width=##L
shadow#true,false
bgopacity=%<factor%>
#endkeyvals
