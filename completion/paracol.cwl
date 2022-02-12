# mode: paracol.sty
# denisbitouze, 27.10.2012
# Matthew Bertucci updated 11.02.2022 for v1.35

\switchcolumn#/paracol
\switchcolumn[column]#/paracol
\switchcolumn*[text]#/paracol
\switchcolumn[column]*[text]#/paracol
\begin{paracol}{number}#n
\begin{paracol}{number}[text]#n
\begin{paracol}[numleft]{number}#*n
\begin{paracol}[numleft]{number}[text]#*n
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
\thecolumn#n
\definecolumnpreamble{column}{preamble}#n
\ensurevspace{length}#n
\columnratio{ratio 0,...,ratio k}#n
\columnratio{ratio 0,...,ratio k}[ratio' 0,...,ratio' k]#n
\setcolumnwidth{gap 0,...,gap k}#n
\setcolumnwidth{gap 0,...,gap k}[gap' 0,...,gap' k]#n
\twosided#n
\twosided[t1t2...tk]#n
\marginparthreshold{columns}#n
\marginparthreshold{columns}[columns']#n
\globalcounter{counter}#n
\globalcounter*#n
\localcounter{counter}#n
\definethecounter{counter}{column}{definition}#n
\synccounter{counter}#n
\syncallcounters#n
\footnotelayout{layout}#n
\footnote*{text}#n
\footnote*[number]{text}#n
\footnotemark*#*n
\footnotemark*[number]#*n
\footnotetext*{text}#n
\footnotetext*[number]{text}#n
\fncounteradjustment#n
\nofncounteradjustment#n
\belowfootnoteskip#n
\columncolor{color}#n
\columncolor{color}[column]#n
\columncolor[mode]{color}#n
\columncolor[mode]{color}[column]#n
\normalcolumncolor#n
\normalcolumncolor[column]#n
\coloredwordhyphenated#n
\nocoloredwordhyphenated#n
\colseprulecolor{color}#n
\colseprulecolor{color}[column]#n
\colseprulecolor[mode]{color}#n
\colseprulecolor[mode]{color}[column]#n
\normalcolseprulecolor#n
\normalcolseprulecolor[column]#n
\backgroundcolor{region}{color}#n
\backgroundcolor{region}[mode]{color}#n
\nobackgroundcolor{region}#n
\resetbackgroundcolor#n
\pagerim#n
\addcontentsonly{file%keyvals}{column}#n
#keyvals:\addcontentsonly
toc
lof
lot
#endkeyvals
\flushpage#n
