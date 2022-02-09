# csvmerge package
# Matthew Bertucci 2/7/2022 for v1.0

#include:etoolbox
#include:stringstrings
#include:trimspaces

\mergeFields{specification}
\Field{field name}
\ifFieldEmpty{field name}{true}{false}
\setDelimitersCommaQuote
\setDelimitersTabQuote
\makeMePublic