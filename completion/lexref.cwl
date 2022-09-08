# lexref package
# Matthew Bertucci 2022/09/08 for v1.1a

#include:etoolbox
#include:xargs
#include:xstring
#include:nomencl
#include:splitidx
#include:ifthen
#include:stringstrings

#keyvals:\usepackage/lexref#c
noprint
indexing
nomencl
shortcutstolist
CHfr
CHde
DE
#endkeyvals

\DeclareLex{csname}{abbrev}
\DeclareLex{csname}{abbrev}[full name]
\DeclareLex{%<csname%>}{%<abbrev%>}[%<full name%>][alt]

\sq
\sqq
\bis
\ter
\quater
\quinquies
\sexies
\septies
\octies
\nonies

\RenewLexShortcut{shortcut}{redefinition}
\RenewLexShortcut{shortcut}{redefinition}[nomenclature]

# not documented
\lexciteindextempone#S
\thelexcitecountinteger#S
\NewLexShortcut{shortcut}{definition}#*
\NewLexShortcut{shortcut}{definition}[nomenclature]#*
\LexRefPrefixTests{arg}#*
\LexRef{name}{art. num}#*
\LexRef{name}{art. num}[para num][num][letter]#*
\LexRefns{name}{art. num}#*
\LexRefns{name}{art. num}[para num][num][letter]#*
\npLexRef{name}{art. num}#*
\npLexRef{name}{art. num}[para num][num][letter]#*
\npLexRefns{name}{art. num}#*
\npLexRefns{name}{art. num}[para num][num][letter]#*
\LexIndex{csname}{art. num}{abbrev}#*
\LexIndex{csname}{art. num}[para num][num][letter]{abbrev}#*