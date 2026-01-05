# linguistix-languages package
# Matthew Bertucci 2026/01/05 for v0.6a

#include:linguistix-base
#include:babel

#keyvals:\linguistix
languages={%<list of languages%>}
native numbering=#strict,logical,off
#endkeyvals

\loadlanguages{list of languages}
\providelanguage{language options}{language name}