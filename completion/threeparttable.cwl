# threeparttable package
# Matthew Bertucci 10/24/2021 for v3.0

#keyvals:\usepackage/threeparttable#c
para
flushleft
online
normal
#endkeyvals

\begin{threeparttable}
\begin{threeparttable}[pos%keyvals]
\end{threeparttable}
\begin{measuredfigure}
\begin{measuredfigure}[pos%keyvals]
\end{measuredfigure}

#keyvals:\begin{threeparttable},\begin{measuredfigure}
t
b
c
#endkeyvals

\begin{tablenotes}
\begin{tablenotes}[options%keyvals]
\end{tablenotes}

#keyvals:\begin{tablenotes}
para
flushleft
online
normal
#endkeyvals

\tnote{label}

\TPTminimum#*
\TPToverlap#*
\TPTrlap#*
\TPTtagStyle#*
\TPTnoteLabel#*
\TPTnoteSettings#*
\TPTdoTablenotes#*
