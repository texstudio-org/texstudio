# regulatory-attachments package
# Matthew Bertucci 2026/09/12 for v1.0.0

#include:regulatory-ref
#include:regulatory-defs

\attachdocument[description%text]{file}{link text%text}
\attachdocument{file}{link text%text}
\documentattachment{label%plain}{link text%text}
\documentfootnote[link text%text]{label%plain}
\documentfootnote{label%plain}
\documentlabel{label%plain}
\loadextdefs[category]{bib file}
\loadextdefs{bib file}
\masterdocument[prefix]{name}{keyvals}
\masterdocument{name}{keyvals}
\refdocument[prefix]{name}{keyvals}
\refdocument{name}{keyvals}

\artifactauthor{arg}#*
\artifactdefs{arg}#*
\artifactdescription{arg}#*
\artifactfilename{arg}#*
\artifactfootnote{arg}#*
\artifactfullfilename{arg}#*
\artifactfullname{arg}#*
\artifactname{arg}#*
\artifactreferred{arg}#*
\artifactsubject{arg}#*
\artifacturl{arg}#*
\newartifact{name}{keyvals}#*