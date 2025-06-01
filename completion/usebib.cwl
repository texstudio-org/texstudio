# usebib package
# Matthew Bertucci 11/17/2021 for v1.0a

#include:url
#include:keyval

\bibinput{bib file}
\newbibfield{field%specialDef}#s#%usebibfield
\newbibignore{type}
\usebibentry{bibid}{field%keyvals}#c
#keyvals:\usebibentry#c
title
year
note
isbn
%usebibfield
#endkeyvals
\usebibentryurl{bibid}#c
\usebibentryurl[delim]{bibid}#*c
