# notes2bib package
# Matthew Bertucci 1/18/2021 for v2.0m

#include:l3keys2e

\bibnote{text}
\bibnote[name]{text}
\bibnotemark
\bibnotemark[name]
\bibnotetext{text}
\bibnotetext[name]{text}
\printbibnotes

\bibnotesetup{options%keyvals}

#keyvals:\bibnotesetup,\usepackage/notes2bib#c
note-name=%<text%>
refsection-name=%<text%>
refsection-separator=%<symbol%>
cite-function=%<cite command%>
file-name=%<file name%>
record-type=%<type%>
note-field=%<field%>
keyword-entry=%<text%>
placement=#before,after,mixed
presort-before=%<string%>
presort-mixed=%<string%>
presort-after=%<string%>
sort-key-before=%<string%>
sort-key-mixed=%<string%>
sort-key-after=%<string%>
convert-endnotes#true,false
convert-footnotes#true,false
use-sort-key#true,false
#endkeyvals

\recordnotes#*
\TotalNotes{number}#*
\NotesAfterCitations{note-list}#*
\NotesBeforeCitations{note-list}#*