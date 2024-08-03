# doibanner package
# Matthew Bertucci 2024/07/29 for v0.3

#include:adjustbox
#include:hyperref
#include:tikz

#keyvals:\usepackage/doibanner#c
label=%<string%>
urlbase=%<string%>
width=##L
#endkeyvals

\doibanner{DOI}
\doibanner[options]{DOI}
\doibanner*{DOI}
\doibanner*[options]{DOI}
\doiurl{DOI}
\doiurl*{DOI}