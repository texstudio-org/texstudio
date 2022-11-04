# scripture package
# Matthew Bertucci 2022/11/04 for v1.2

\ch{chapter number}
\ch*{chapter number}
\extraskip
\name{divine name}
\LORD
\GOD
\nohang
\redletteron
\redletteroff
\scripturecurrentchapter
\scripturecurrentverse
\selah
\scripturesetup{options%keyvals}
\textright{text}
\vs{verse number}

\begin{center}[options%keyvals]
\begin{flushright}[options%keyvals]
\begin{hanging}
\begin{hanging}[options%keyvals]
\end{hanging}
\begin{midparachap}
\begin{midparachap}[options%keyvals]
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
chapter/colour=#%color
chapter/color=#%color
chapter/drop#true,false
chapter/font=%<font commands%>
chapter/format=%<macro%>
chapter/hide#true,false
chapter/nodrop#true,false
chapter/sep=##L
chapter/show#true,false
colour=#%color
color=#%color
compact#true,false
extraskip=##L
font=%<font commands%>
indent#true,false
language=%<language name%>
language/variant=%<language variant name%>
leftmargin=##L
name/font=%<font commands%>
name/format=%<macro%>
noindent#true,false
parindent=##L
parskip=##L
redletter#true,false
redletter/colour=#%color
redletter/color=#%color
reference/colour=#%color
reference/color=#%color
reference/delim=%<delim%>
reference/font=%<font commands%>
reference/format=%<macro%>
reference/sep=##L
rightmargin=##L
selah/font=%<font commands%>
selah/format=%<macro%>
selah/sep=##L
selah/text=%<text%>
textright/sep=##L
verse/colour=#%color
verse/color=#%color
verse/font=%<font commands%>
verse/format=%<macro%>
verse/hide#true,false
verse/sep=##L
verse/show#true,false
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
midparachap/hideverse#true,false
midparachap/showverse#true,false
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
poetry/verse/left#true,false
poetry/verse/right#true,false
poetry/verse/sep=##L
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

#keyvals:\begin{midparachap}
hideverse#true,false
showverse#true,false
#endkeyvals

#keyvals:\begin{poetry}
bigindent=##L
indent=##L
#endkeyvals
