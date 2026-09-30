# xjyutping package
# Matthew Bertucci 2026/04/20 for v3.15.0

\xjyutpingsetup{options%keyvals}

\begin{jyutpingscope}
\begin{jyutpingscope}[options%keyvals]
\end{jyutpingscope}

\xjyutping{text}{readings}
\xjyutping[options%keyvals]{text}{readings}
\xjyutping*{text}
\xjyutping*[options%keyvals]{text}

#keyvals:\xjyutpingsetup,\begin{jyutpingscope},\xjyutping,\xjyutping*
ratio=%<factor%>
vsep=##L
hsep=##L
width=##L
font=%<font commands%>
format=%<commands%>
multiple=%<commands%>
fancy#true,false
linebreak#true,false
debug#true,false
#endkeyvals

\enablejyutping
\disablejyutping
\setjyutping{word}{reading}