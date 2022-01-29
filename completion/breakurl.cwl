# breakurl package
# Matthew Bertucci 1/28/2022 for v1.40

#include:xkeyval
#include:ifpdf

#keyvals:\usepackage/breakurl#c
hyphenbreaks
anythingbreaks
preserveurlmacro
vertfit=%<criterion%>
#endkeyvals

\burl{URL}#U
\burlalt{URL}{text%plain}#U
\urlalt{URL}{text%plain}#*U
\UrlRight{arg%URL}#*
\UrlLeft{arg%URL}#*