# linguistix-languages package
# Matthew Bertucci 2026/05/18 for v1.0

#include:linguistix-base
#include:babel
#include:setspace

#keyvals:\linguistix
languages={%<list of languages%>}
native numbering=#strict,logical,off
#endkeyvals

\loadlanguages{list of languages}
\providelanguage{language options}{language name}