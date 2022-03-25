# xsavebox package
# Matthew Bertucci 3/14/2022 for v0.17

#include:l3keys2e
#include:pdfbase

#keyvals:\usepackage/xsavebox#c
margin=##L
#endkeyvals

\xsbox{name}{content%text}
\xsavebox{name}{content%text}
\xsavebox{name}[width]{content%text}
\xsavebox{name}[width][position]{content%text}
\xsavebox*{name}{content%text}
\xsavebox*{name}[width]{content%text}
\xsavebox*{name}[width][position]{content%text}
\begin{xlrbox}{name}
\end{xlrbox}
\begin{xlrbox*}{name}
\end{xlrbox*}
\xusebox{name}
