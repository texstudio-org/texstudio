# icite package
# Matthew Bertucci 11/17/2021 for v1.3a

#include:xkeyval
#include:datatool
#include:usebib

\SetTitleStyle{style code}
\AuthorTitleDelim{delim}
\TitlePageDelim{delim}

\icite{bibid}#C
\icite[pre]{bibid}#C
\icite[pre][post]{bibid}#C
\icite[pre][post]{bibid}[csname]#C

\IndexSubtypeAs{subtype}{index name}