# setspace package, v6.7a

#keyvals:\usepackage/setspace#c
nodisplayskipstretch
singlespacing
onehalfspacing
doublespacing
#endkeyvals

\singlespacing
\onehalfspacing
\doublespacing
\SetSinglespace{factor}
\begin{singlespace}
\begin{singlespace*}#*
\begin{doublespace}
\begin{onehalfspace}
\begin{spacing}{factor}
\end{singlespace}
\end{singlespace*}#*
\end{doublespace}
\end{onehalfspace}
\end{spacing}
\setstretch{factor}
\displayskipstretch#*
\setdisplayskipstretch{factor}
