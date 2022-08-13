# xsavebox package
# Matthew Bertucci 2022/08/12 for v0.18

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
