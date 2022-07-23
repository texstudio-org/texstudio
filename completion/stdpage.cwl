# stdpage package
# Matthew Bertucci 2022/07/20 for v0.6

#include:typearea
#include:ragged2e
#include:ifthen
#include:keyval
#include:lineno
#include:hyphenat
#include:titlesec

#keyvals:\usepackage/stdpage#c
just#true,false
noindent#true,false
linenumbers#true,false
hyphen#true,false
parskip#true,false
chars=%<integer%>
lines=%<integer%>
baselinestretch
baselinestretch=%<factor%>
typewriter#true,false
#endkeyvals

\CharsX#*
\CharsI#*
\zeichenzahl#*
\zeilenzahl#*
\ProcessOptionsWithKV{family}#S