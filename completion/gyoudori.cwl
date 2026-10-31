# gyoudori package
# Matthew Bertucci 2026/10/29 for v20261026.0

#keyvals:\usepackage/gyoudori#c
displaymath#true,false
float#true,false
indent#true,false
floatsep=##L
textfloatsep=##L
intextsep=##L
dblfloatsep=##L
dbltextfloatsep=##L
overflow=#warning,error
displaymathextra=%<integer%>
#endkeyvals

\begin{gyoudori}{lines}
\begin{gyoudori}[options%keyvals]{lines}
\end{gyoudori}

\gyoudoriarea{lines}{content%text}
\gyoudoriarea[options%keyvals]{lines}{content%text}

#keyvals:\begin{gyoudori},\gyoudoriarea
t
c
b
local
indent
noindent
#endkeyvals