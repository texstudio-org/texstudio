# hep-acronym package
# Matthew Bertucci 2026/08/19 for v1.5

#include:kvoptions
#include:glossaries-extra
#include:everyhook
#include:xspace
#include:amstext
#include:titlesec
#include:enumitem

#keyvals:\usepackage/hep-acronym#c
hyper#true,false
#endkeyvals

\acronym{abbr}{def%text}
\acronym[typeset abbr]{abbr}{def%text}
\acronym{abbr}{def%text}[plural def%text]
\acronym[typeset abbr]{abbr}{def%text}[plural def%text]#*
\acronym*{abbr}{def%text}#*
\acronym*[typeset abbr]{abbr}{def%text}#*
\acronym*{abbr}{def%text}[plural def%text]#*
\acronym*[typeset abbr]{abbr}{def%text}[plural def%text]#*

\sentence

\shortacronym{abbr}{def%text}
\shortacronym[typeset abbr]{abbr}{def%text}
\shortacronym{abbr}{def%text}[plural def%text]
\shortacronym[typeset abbr]{abbr}{def%text}[plural def%text]#*
\shortacronym*{abbr}{def%text}#*
\shortacronym*[typeset abbr]{abbr}{def%text}#*
\shortacronym*{abbr}{def%text}[plural def%text]#*
\shortacronym*[typeset abbr]{abbr}{def%text}[plural def%text]#*

\longacronym{abbr}{def%text}
\longacronym[typeset abbr]{abbr}{def%text}
\longacronym{abbr}{def%text}[plural def%text]
\longacronym[typeset abbr]{abbr}{def%text}[plural def%text]#*
\longacronym*{abbr}{def%text}#*
\longacronym*[typeset abbr]{abbr}{def%text}#*
\longacronym*{abbr}{def%text}[plural def%text]#*
\longacronym*[typeset abbr]{abbr}{def%text}[plural def%text]#*

\acronymalternative{acronym}{name}{alt long form}
\acronymalternative{acronym}{name}*{alt long form}
\resetacronym{key%plain}
\dummyacronym{key%plain}
\acronyms{title%text}
\acronyms[key%plain]{title%text}

\mathdef{cmd}{def}#Sd
\mathdef{cmd}[args]{def}#Sd
\descriptionsitem#S