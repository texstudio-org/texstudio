# enotez package
# Matthew Bertucci 9/19/2021 for v0.10c

#include:l3keys2e
#include:xtemplate
#include:translations

\endnote{text}
\endnote[mark]{text}

\endnotemark#*
\endnotemark[mark]#*
\endnotetext{text}#*
\enotezwritemark#*
\enmarkstyle#*

\printendnotes
\printendnotes[style%keyvals]
\printendnotes*#*
\printendnotes*[style%keyvals]#*

#keyvals:\printendnotes#c,\printendnotes*#c
description
itemize
#endkeyvals

\AtEveryEndnotesList{text}#*
\AtNextEndnotesList{text}#*
\AfterEveryEndnotesList{text}#*
\AfterNextEndnotesList{text}#*

\setenotez{options%keyvals}

#keyvals:\setenotez
list-name=
reset#true,false
counter-format=#arabic,alph,Alph,roman,Roman,symbols
mark-format={%<code%>}
mark-cs={%<command%>}
backref#true,false
totoc=#subsection,section,chapter,part,auto,false
list-heading=
list-style=
list-preamble-skip=
list-postamble-skip=
split=#section,chapter,false
split-sectioning={%<csname%>}
split-heading=
split-title={%<token list%>}
#endkeyvals

\enmark{arg}#*

\AtEveryListSplit{code}#*
\AfterEveryListSplit{code}#*
\EnotezCurrentSplitTitle#*
\NewSplitTitleTag{tag}{replacement}#*

\enotezlistheading{text}#*
\enotezsplitlistheading#*
\enotezdisable#*
\theendnote#*
