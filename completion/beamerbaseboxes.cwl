# beamerbaseboxes package
# Matthew Bertucci 1/30/2022 for v3.65

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
#endkeyvals