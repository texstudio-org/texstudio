# paralist package
# Matthew Bertucci 2022/05/10 for v2.7

#keyvals:\usepackage/paralist#c
newitem
olditem
newenum
oldenum
alwaysadjust
neveradjust
neverdecrease
defblank
pointlessenum
pointedenum
flushright
flushleft
cfg
nocfg
#endkeyvals

\begin{itemize}[label]
\end{itemize}
\begin{enumerate}[label]
\end{enumerate}
\begin{asparaenum}
\begin{asparaenum}[label]
\end{asparenum}
\begin{inparaenum}
\begin{inparaenum}[label]
\end{inparaenum}
\begin{compactenum}
\begin{compactenum}[label]
\end{compactenum}
\begin{asparaitem}
\begin{asparaitem}[label]
\end{asparitem}
\begin{inparaitem}
\begin{inparaitem}[label]
\end{inparaitem}
\begin{compactitem}
\begin{compactitem}[label]
\end{compactitem}
\begin{asparadesc}
\end{aspardesc}
\begin{inparadesc}
\end{inparadesc}
\begin{compactdesc}
\end{compactdesc}

#ifOption:defblank
\begin{asparablank}
\end{asparablank}
\begin{inparablank}
\end{inparablank}
#endif

\setdefaultitem{label1}{label2}{label3}{label4}
\setdefaultenum{label1}{label2}{label3}{label4}
\setdefaultleftmargin{length1}{length2}{length3}{length4}{length5}{length6}

\pointedenum#*
\pointlessenum#*
\paradescriptionlabel#*
\pltopsep#*
\plpartopsep#*
\plitemsep#*
\plparsep#*
