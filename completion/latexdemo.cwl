# latexdemo package
# Matthew Bertucci 10/12/2021

#include:listings
#include:xspace
#include:etoolbox
#include:filecontents
#include:mdframed
#include:framed
#include:xcolor
#include:kvoptions
#include:pdftexcmds

\democodefile
\democodeprefix
\demoresultprefix

\PrintDemo{style%keyvals}

#keyvals:\PrintDemo
style=#parallel,stacked,lines,none,page
#endkeyvals

\command{arg}
\cs{arg}
\arg{arg}
\marg{arg}
\oarg{arg}
\environment{envname}
\env{envname}
\package{package}
\DemoError{text}

\PrintDemoUsingKeys#*
\preResultSkip#*
\begin{latexresult}#*
\end{latexresult}#*
\resultline#*
\printlatexcode{arg}#*
\printlatexresult{arg}#*
\printlatexresultlines#*
\PrintCodeAndResultsParallel#*
\PrintCodeAndResultsStacked#*
\PrintCodeAndResultsStackedLines#*
\PrintCodeAndResultsNone#*
\PrintCodeAndResultsPage#*