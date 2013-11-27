# mode: paracol.sty
# denisbitouze, 27.10.2012
\switchcolumn#/paracol
\switchcolumn[column]#/paracol
\switchcolumn[column]*[text]#/paracol
\begin{paracol}{number}#n
\begin{paracol}{number}[text]#n
\end{paracol}#n
\begin{column}#n
\begin{column*}#n
\begin{column*}[text]#n
\end{column}#n
\end{column*}#n
\begin{nthcolumn}{column}#n
\begin{nthcolumn*}{column}#n
\begin{nthcolumn*}{column}[text]#n
\end{column}#n
\end{column*}#n
\begin{leftcolumn}#n
\begin{leftcolumn*}#n
\begin{leftcolumn*}[text]#n
\end{leftcolumn}#n
\end{leftcolumn*}#n
\begin{rightcolumn}#n
\begin{rightcolumn*}#n
\begin{rightcolumn*}[text]#n
\end{rightcolumn}#n
\end{rightcolumn*}#n
\columnratio{ratio 0,...,ratio k}#n
\globalcounter{counter}#n
\definethecounter{counter}{column}{definition}#n
\synccounter{counter}#n
\syncallcounters#n
\addcontentsonly{file}{column}#n
\flushpage#n
\clearpage#n