# pst-abspos package
# Matthew Bertucci 2/20/2022 for v0.2

#include:pstricks
#include:pst-node
#include:pst-xkey

#keyvals:\usepackage/pst-abspos#c
notitlepage
absolute
lowerleft
relative
PostScript
#endkeyvals

\pstSetRelativeOrigin(x,y)
\pstSetAbsoluteOrigin
\pstSetPostScriptOrigin
\pstPutAbs(x,y){stuff}
\pstPutAbs[options%keyvals](x,y){stuff}
\PSTabsposLoaded#S