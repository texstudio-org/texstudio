# figlatex package
# Matthew Bertucci 2022/07/21 for v2.4.3

#include:ifthen
#include:ifpdf
#include:graphicx
#include:xstring
#include:color
#include:epstopdf

#keyvals:\usepackage/figlatex#c
debug
#endkeyvals

\debug#S

#keyvals:\includegraphics
subfig=%<name%>
#endkeyvals