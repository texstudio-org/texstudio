# arydshln package
# Matthew Bertucci 10/5/2021 for v1.76

\hdashline#t
\hdashline[%<dash%>/%<gap%>]#t
\cdashline{i-j}#t
\cdashline{i-j}[%<dash%>/%<gap%>]#t
\firsthdashline#t
\lasthdashline#t

\dashlinedash#*
\dashlinegap#*
\ADLnullwide#*
\ADLsomewide#*
\ADLdrawingmode{mode number%keyvals}#*
#keyvals:\ADLdrawingmode
1
2
3
#endkeyvals
\ADLinactivate#*
\ADLactivate#*

\begin{Array}{cols}#m\array
\begin{Array}[pos]{cols}#m\array
\end{Array}#m
\begin{Tabular}{cols}#\tabular
\begin{Tabular}[pos]{cols}#\tabular
\end{Tabular}
\begin{Tabular*}{width}[pos]{cols}#\tabular
\begin{Tabular*}{width}{cols}#\tabular
\end{Tabular*}

\ADLnoshorthanded#*
\ADLnullwidehline#*
\ADLsomewidehline#*
\dashgapcolor{color}#*
\dashgapcolor[model]{color specs}#*
\nodashgapcolor#*

\begin{Longtable}{cols}#*\tabular
\begin{Longtable}[pos]{cols}#*\tabular
\end{Longtable}#*