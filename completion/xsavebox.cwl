# xsavebox package
# Matthew Bertucci 11/10/2021 for v0.16

#include:l3keys2e

#keyvals:\usepackage/xsavebox#c
margin=##L
#endkeyvals

\xsbox{name}{content}
\xsavebox{name}{content}
\xsavebox{name}[width]{content}
\xsavebox{name}[width][position]{content}
\xsavebox*{name}{content}
\xsavebox*{name}[width]{content}
\xsavebox*{name}[width][position]{content}
\begin{xlrbox}{name}
\end{xlrbox}
\begin{xlrbox*}{name}
\end{xlrbox*}
\xusebox{name}
