# scripture package
# Matthew Bertucci 2022/07/28 for v1.0

#include:l3keys2e

\ch{chapter number}
\ch*{chapter number}
\extraskip
\nohang
\scripturesetup{options%keyvals}
\vs{verse number}

\begin{center}[options%keyvals]
\begin{flushright}[options%keyvals]
\begin{hanging}
\begin{hanging}[options%keyvals]
\end{hanging}
\begin{midparachap}
\end{midparachap}
\begin{narrow}
\begin{narrow}[options%keyvals]
\end{narrow}
\begin{poetry}
\begin{poetry}[options%keyvals]
\end{poetry}
\begin{scripture}
\begin{scripture}[reference]
\begin{scripture}[reference][options%keyvals]
\end{scripture}

#keyvals:\usepackage/scripture#c,\scripturesetup,\begin{scripture}
aboveskip=##L
belowskip=##L
leftmargin=##L
rightmargin=##L
chapter/font=%<font commands%>
chapter/drop#true,false
chapter/nodrop#true,false
chapter/sep=##L
extraskip=##L
font=%<font commands%>
indent#true,false
noindent#true,false
parindent=##L
parskip=##L
reference/delim=%<delim%>
reference/font=%<font commands%>
reference/format=%<macro%>
reference/sep=##L
verse/font=%<font commands%>
verse/format=%<macro%>
version=%<version%>
version/delim=%<delim%>
version/format=%<macro%>
center/aboveskip=##L
center/belowskip=##L
center/leftmargin=##L
center/rightmargin=##L
flushright/aboveskip=##L
flushright/belowskip=##L
flushright/leftmargin=##L
flushright/rightmargin=##L
hanging/aboveskip=##L
hanging/belowskip=##L
hanging/hang=##L
hanging/leftmargin=##L
hanging/rightmargin=##L
narrow/aboveskip=##L
narrow/belowskip=##L
narrow/leftmargin=##L
narrow/rightmargin=##L
poetry/aboveskip=##L
poetry/belowskip=##L
poetry/bigindent=##L
poetry/indent=##L
poetry/leftmargin=##L
poetry/rightmargin=##L
#endkeyvals

#keyvals:\begin{center},\begin{flushright},\begin{hanging},\begin{narrow},\begin{poetry}
aboveskip=##L
belowskip=##L
leftmargin=##L
rightmargin=##L
#endkeyvals

#keyvals:\begin{hanging}
hang=##L
#endkeyvals

#keyvals:\begin{poetry}
bigindent=##L
indent=##L
#endkeyvals