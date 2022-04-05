# pagerange package
# Matthew Bertucci 4/2/2022 for v0.5

#include:lastpage
#include:xkeyval

\pagerangeoptions{options%keyvals}

#keyvals:\usepackage/pagerange#c,\pagerangeoptions
tie=%<character%>
acceptempty#true,false
defaultfirstpage=%<number%>
defaultlastpage=%<number%>
#endkeyvals

\pagerange{page range}
\pagestart
\pageend
\getpagenumber{label}#r