# blkarray package
# Matthew Bertucci 10/20/2021 for v0.07


\BAnewcolumntype{name%cmd}{argument}#d
\BAnewcolumntype[args]{name%cmd}{argument}#d
\begin{blockarray}{cols}#\tabular
\end{blockarray}
\BAmulticolumn{cols}{pos}{text}
\begin{block}{cols}#\tabular
\end{block}
\begin{block*}{cols}#\tabular
\end{block*}
\Left{text}{delim}
\Right{text}{delim}
\BAenum
\theBAenumi
\testBAtablenotes{arg1}{arg2}#*
\BAtablenotestrue
\BAtablenotesfalse
\BAparfootnotes
\BAnoalign{text}
\BAnoalign*{text}
\BAmultirow{dimen%l}
\BAmultirow{dimen%l}{text}
\BAhline#t
\BAhhline{colspec}#t
\BAextraheightafterhline#*
\BAextrarowheight#*
\BAtracing#*
\BAarrayrulewidth#*
\BAdoublerulesep#*
\plain#S