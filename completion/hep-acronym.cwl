# hep-acronym package
# Matthew Bertucci 2023/07/14 for v1.2

#include:kvoptions
#include:glossaries-extra
#include:everyhook
#include:xspace
#include:amstext

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

\resetacronym{key%plain}
\dummyacronym{key%plain}

\acronymalternative{arg1}{arg2}{arg3}#*
\acronymalternative{arg1}{arg2}*{arg3}#*

\mathdef{cmd}{def}#*d
\mathdef{cmd}[args]{def}#*d
\acronyms{name}#*
\acronyms[opt]{name}#*
