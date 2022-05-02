# biblatex-ext-tabular package
# Matthew Bertucci 4/23/2022 for v0.15

\printbibtabular
\printbibtabular[options%keyvals]

#keyvals:\printbibtabular
env=%<name%>
heading=%<name%>
title=%<text%>
label=##l
block=#none,space,par,nbpar,ragged
prenote=%<name%>
postnote=%<name%>
section=%<integer%>
segment=%<integer%>
type=%<entrytype%>
nottype=%<entrytype%>
subtype=%<subtype%>
notsubtype=%<subtype%>
keyword=%<keyword%>
notkeyword=%<keyword%>
category=%<category%>
notcategory=%<category%>
filter=%<name%>
check=%<name%>
resetnumbers=
omitnumbers#true,false
locallabelwidth#true,false
#endkeyvals

\defbibtabular{name}{begin code%definition}{end code%definition}{row code%definition}

\plain{code}
\plainlang{code}
\anchor{code}
\anchorlang{code}
\driver{precode}

\defbibtabulartwocolumn{name}{begin code%definition}{end code%definition}{anchor code%definition}{driver code%definition}