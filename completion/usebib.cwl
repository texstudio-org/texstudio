# usebib package
# Matthew Bertucci 11/17/2021 for v1.0a

#include:url
#include:keyval

\bibinput{bib file}
\newbibfield{field}
\newbibignore{type}
\usebibentry{citekey}{field%keyvals}
#keyvals:\usebibentry#c
title
year
note
isbn
#endkeyvals
\usebibentryurl{citekey}
\usebibentryurl[delim]{citekey}#*