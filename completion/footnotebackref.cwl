# footnotebackref package
# Matthew Bertucci 11/29/2021 for v1.0

#include:letltxmacro
#include:hyperref
#include:kvoptions

#keyvals:\usepackage/footnotebackref#c
symbol=%<symbol%>
numberlinked#true,false
#endkeyvals

\BackrefFootnoteTag#*
\theBackrefHyperFootnoteCounter#*
