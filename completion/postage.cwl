# postage package
# Matthew Bertucci 2023/02/27 for v1.0

#include:graphicx
#include:tikz
#include:calc
#include:keyval

\includestamp{imagefile}#g
\includestamp[options%keyvals]{imagefile}#g

#keyvals:\includestamp
style=#normal,compact
normal
compact
page=%<number%>
row=%<number%>
column=%<number%>
#endkeyvals